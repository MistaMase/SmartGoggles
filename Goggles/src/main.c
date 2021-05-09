#include "main.h"

int main() {
    // Init stdio
    stdio_init_all();

    // Set up the display
    display_setup();
    display_set_backlight(20);
    sleep_ms(500);
    display_draw_screen(0xF0F0);

    // Set up the capactive touch
    touch_setup();
    touch_setup_interrupt();

    // Set up the IMU
    imu_setup();

    //uint8_t color_index = 0;
    //uint16_t colors[3] = {0xFFFF, 0x0000, 0xF0F0};

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

        /* Read IMU data */
        float accel[3], gyro[3], mag[3], temp;
        imu_read_data(accel, gyro, mag, &temp);
        printf("IMU - Acceleration: %fg, %fg, %fg\nGyro: %fdps, %fdps, %fdps\nMagnetometer: %fuT, %fuT, %fuT\nTemp: %f\n", 
                accel[0], accel[1], accel[2], gyro[0], gyro[1], gyro[2], mag[0], mag[1], mag[2], temp);


        /* Draw to the display */
        //display_draw_screen(colors[color_index++]);
        //if(color_index == 3)
        //    color_index = 0;
        //printf("Drawing\n");
        sleep_ms(500);

    }
    return 0;
}