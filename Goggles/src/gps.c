#include "gps.h"

/* Configure the GPS device to our liking */
void gps_setup() {
    // TODO Remove This
    stdio_init_all();

    // Initialize UART0 for GPS
    uart_init(GPS_UART_ID, GPS_DEFAULT_BAUD_RATE);

    // Set the TX and RX pins for GPS UART
    gpio_set_function(GPS_TX, GPIO_FUNC_UART);
    gpio_set_function(GPS_RX, GPIO_FUNC_UART);

    // Set the current message index to 0
    gps_message_index = 0;

    // Increase the GPS baud rate to 57600
    //gps_raw_send_message(PMTK_SET_NMEA_BAUD_38400);
    //uart_deinit(GPS_UART_ID);

    // Update the Pico's baud rate
    //uart_init(GPS_UART_ID, GPS_BAUD_RATE);

    // Set the GPS to update every second
    gps_raw_send_message(PMTK_SET_NMEA_UPDATE_1_SEC);

    // Set the GPS output to custom
    gps_raw_send_message(PMTK_SET_NMEA_OUTPUT_CUSTOM);

    // Set up interrupts
    gps_setup_interrupt();
}

/* Sends a raw message out over UART using RPI Pico Libraries */
void gps_raw_send_message(char* message) {
    // Sends a string out over UART
    uart_puts(GPS_UART_ID, message);
}

/* Reads over UART using RPI Pico Libraries */
void gps_raw_receive_message(char* buffer) {  
    // Read over UART the data  
    uart_read_blocking(GPS_UART_ID, buffer, 1);
}

/* Calculate the NMEA checksum for outgoing messages by xor-ing each character in the sequence */
char gps_calc_NMEA_checksum(char *start, char* end) {
    char checksum = *start;
    int i = 1;
	
    while(start+i != end && i < 246) {
        checksum ^= start[i];
        i++;
    }
	return checksum;
}

/* Validates the NMEA from the GPS to ensure no errors are present */
int gps_validate_NMEA(char* nmea) {
    char *check_start_addr = strstr(nmea, "*") + 1;
    char calc_checksum_value = gps_calc_NMEA_checksum(nmea+1, check_start_addr-1);
    char calc_checksum[3];
    sprintf(calc_checksum, "%X", calc_checksum_value);
	if (check_start_addr[0] == calc_checksum[0] && check_start_addr[1] == calc_checksum[1])
		return 1;
	return 0;
}

/* Creates a string-based representation of the data from the GPS message */
/* Saves result data into GPS_Str_Data *gps_str_data */
int gps_parse_NMEA(char* message, struct GPS_Str_Data *gps_str_data) {
    char *ptr, *nmeaStart;

	// Ensure the header is right -> data is coming from device
	if ((nmeaStart = strstr(message, "$GPGGA")) == NULL) {
        printf("GPS - Failed Header\n");
		return 0;
    }

	// Validate the checksum -> prevent corrupted data propagation
	if (!gps_validate_NMEA(nmeaStart)) {
        printf("GPS - Failed Checksum\n");
		return 0;
    }

	// Separate the sentence by commas	
	ptr = strtok(nmeaStart, ",");

	// FastFwd to latitude
	ptr = strtok(NULL, ",");
	ptr = strtok(NULL, ",");
	strcpy(gps_str_data->latitude, ptr);

	// Latitude cardinal
	ptr = strtok(NULL, ",");
	strcpy(gps_str_data->latCardinal, ptr);

	// Longitude
	ptr = strtok(NULL, ",");
	strcpy(gps_str_data->longitude, ptr);

	// Longitude cardinal
	ptr = strtok(NULL, ",");
	strcpy(gps_str_data->lonCardinal, ptr);
	
	// Fix
	ptr = strtok(NULL, ",");
	strcpy(gps_str_data->fix, ptr);

    // Return false if we don't have a fix - i.e. valid data
    if (!gps_str_data->fix[0]) {
        printf("GPS - No Fix");
        return 0;
    }

    // Return 1 since we have valid data
    return 1;
}

/* Converts from DDMM.MMMM to decimal */
double gps_mins_to_dec(double coord) {
    int degree = coord / 100;
    return (coord - degree * 100) / 60 + degree;
}

/* Converts the string-based representation to numerical values */
void gps_parse_data(struct GPS_Str_Data *gps_str_data) {
    // Don't save this new data if it doesn't have a fix
    if (!atoi(gps_str_data->fix))
        return;

    /* Latitude */
    current_gps_data.latitude = atof(gps_str_data->latitude);
    // Negate if southern hemisphere
    if (gps_str_data->latCardinal[0] == 'S')
        current_gps_data.latitude *= -1;

    // Convert from NMEA pure form to pure decimal
    current_gps_data.latitude = gps_mins_to_dec(current_gps_data.latitude);

    /* Longitude */
    current_gps_data.longitude = atof(gps_str_data->longitude);
    // Negate if western hemisphere
    if (gps_str_data->lonCardinal[0] == 'W')
        current_gps_data.longitude *= -1;

    // Convert from NMEA pure form to pure decimal
    current_gps_data.longitude = gps_mins_to_dec(current_gps_data.longitude);

    /* Fix */
    current_gps_data.fix = atoi(gps_str_data->fix);
}

struct GPS_Data gps_get_data() {
    return current_gps_data;
}

/* Call to retrieve data from the device and parse it */
void gps_retrieve_data(char* message) {
    // Define data objects
    struct GPS_Str_Data gps_str_data;

    // Get the string-based data object from the message
    int valid;
    valid = gps_parse_NMEA(message, &gps_str_data);

    // Convert the string-based data object to real data
    gps_parse_data(&gps_str_data);
}

/* Configure an interrupt for new receiving data over UART */
void gps_setup_interrupt() {
    // Configure the interrupt to call gps_get_data over UART0_IRQ
    irq_set_exclusive_handler(UART0_IRQ, gps_parse_interrupt);

    // Enable the interrupt handler
    irq_set_enabled(UART0_IRQ, true);

    // Enable UART to trigger interrupts on RX
    uart_set_irq_enables(GPS_UART_ID, true, false);
}

/* Called on UART interrupt */
/* If the last character in the sequence, process the data */
/* Otherwise, add the character to the rolling buffer */
void gps_parse_interrupt() {
    // Receive the raw data - Pointer logic to offset
    gps_raw_receive_message(gps_incoming_message + gps_message_index);

    // If we've reached the end of the message
    if (gps_incoming_message[gps_message_index] == '\n') {
        // Print location data
        if (strstr(gps_incoming_message, "GPGGA")) {
            // Create a temp copy of the string
            char temp_msg[255];
            strcpy(temp_msg, gps_incoming_message);

            // Convert message to proper data
            gps_retrieve_data(temp_msg);
        }

        // Housekeeping
        gps_message_index = 0;
        memset(gps_incoming_message, 0, 255*sizeof(char));
    }

    // If it's an intermediate character in the message
    else {
        // Housekeeping
        gps_message_index++;
    }
}