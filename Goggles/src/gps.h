#ifndef GPS_H
#define GPS_H

#include "pico/stdlib.h"            // Gives the pico stdlib
#include "hardware/uart.h"          // Allows access to uart
#include "hardware/irq.h"           // Pico Interrupt library
#include "pins.h"                   // Constants for pin definitions
#include <string.h>                 // C String library
#include <stdlib.h>                 // C Stdlib library
#include <math.h>                   // C Math library
#include <stdio.h>                  // C I/O library


/* GPS String Data Struct */
struct GPS_Str_Data
{
	char latitude[16];
	char longitude[16];
	char latCardinal[2];
	char lonCardinal[2];	
	char fix[2];
	
};

/* GPS Data Struct */
struct GPS_Data
{
	float latitude;
	float longitude;
	int fix;
};

volatile static struct GPS_Data current_gps_data;
static size_t gps_message_index;
static char gps_incoming_message[255];

// Configuration Parameters
#define GPS_UART_ID                 uart0
#define GPS_DEFAULT_BAUD_RATE       9600
#define GPS_BAUD_RATE               38400

/* Commands */
// Set Baud Rate - NOT WORKING
#define PMTK_SET_NMEA_BAUD_38400 "$PMTK251,38400*27"        // 38400

// GPS Update Rate
#define PMTK_SET_NMEA_UPDATE_10_SEC  "$PMTK220,10000*2F"    // Every 10 seconds 
#define PMTK_SET_NMEA_UPDATE_5_SEC  "$PMTK220,5000*1B"      // Every 5 seconds
#define PMTK_SET_NMEA_UPDATE_1_SEC  "$PMTK220,1000*1F"      // Every second

// System Commands
#define PMTK_CMD_HOT_START "$PMTK101*32"                    // Reboot
#define PMTK_CMD_STANDBY_MODE "$PMTK161,0*28"               // Standby

// Data Output Format
/* Enable Recommended Minimum Sentence and GPS Fix data ( RMC and GGA ) */
/* 
    Data Format - Preamble($), Talker ID(PMTK), Packet Type(314), 
    Data Field (everything between the ','s and before '*'), End of Data Field (*), 
    Checksum 1(2), Checksum 2(8) 
*/
/* 
    Output Format: Bit #, Meaning
    0 NMEA_SEN_GLL, // GPGLL interval - Geographic Position - Latitude longitude
    1 NMEA_SEN_RMC, // GPRMC interval - Recommended Minimum Specific GNSS Sentence
    2 NMEA_SEN_VTG, // GPVTG interval - Course over Ground and Ground Speed
    3 NMEA_SEN_GGA, // GPGGA interval - GPS Fix Data
    4 NMEA_SEN_GSA, // GPGSA interval - GNSS DOPS and Active Satellites
    5 NMEA_SEN_GSV, // GPGSV interval - GNSS Satellites in View
    6 - 17          // Reserved
    18 NMEA_SEN_MCHN, // PMTKCHN interval – GPS channel status
*/
#define PMTK_SET_NMEA_OUTPUT_CUSTOM "$PMTK314,1,1,1,1,1,5,0,0,0,0,0,0,0,0,0,0,0,0,0*2C" 


void gps_setup(void);
void gps_raw_send_message(char* message);
void gps_raw_receive_message(char* buffer);
char gps_calc_NMEA_checksum(char *start, char *end);
int gps_validate_NMEA(char* nmea);
double gps_mins_to_dec(double coord);
void gps_setup_interrupt();
void gps_parse_interrupt();
void gps_retrieve_data();
struct GPS_Data gps_get_data();
int gps_parse_NMEA(char* message, struct GPS_Str_Data *gps_str_data);
void gps_parse_data(struct GPS_Str_Data *gps_str_data);

#endif