#include "main.h"

int main() {
    // Init stdio
    stdio_init_all();

    // Pause execution until software serial started if in debug mode
    if (DEBUG_MODE)
        while(!tud_cdc_connected()) sleep_ms(250);

    // Set up the capactive touch
    touch_setup();

    // Set up the IMU
    imu_setup();

    // Set up the GPS
    gps_setup();

    // Counter for easily tracking psuedo-accurate timing
    int count = 0;

    while (true){
        /* Handle Interrupts */
        // If new touch input, read touch data
        if(touch_flags) {
            uint16_t touchX[2], touchY[2], touchID[2];
            uint8_t num_touches;
            touch_read_data(touchX, touchY, touchID, &num_touches);
            for (uint8_t i = 0; i < num_touches; i++) {
                printf("ID #: %u\t TouchX: %u\t TouchY: %u\n", touchID[i], touchX[i], touchY[i]);
            }
            touch_flags = touch_flags & ~0x01;
        }

        // Prints every second
        count = (count == 1000) ? 0 : count+1;
        if (!count) {
            /* Print GPS Data */
            struct GPS_Data gps_data = gps_get_data();
            if (gps_data.fix) {
                printf("GPS Latitude: %f\n", gps_data.latitude);
                printf("GPS Longitude: %f\n", gps_data.longitude);
            }

            /* Print IMU data */
            float accel[3], gyro[3], mag[3], temp;
            imu_read_data(accel, gyro, mag, &temp);
            printf("IMU Acceleration: %fg, %fg, %fg\n", accel[0], accel[1], accel[2]);
            printf("IMU Gyro: %fdps, %fdps, %fdps\n", gyro[0], gyro[1], gyro[2]);
            printf("IMU Magnetometer: %fuT, %fuT, %fuT\n", mag[0], mag[1], mag[2]);
        }

        // Quick Sleep
        sleep_ms(1);

    }
    return 0;
}