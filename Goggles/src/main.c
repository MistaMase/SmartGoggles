#include "main.h"

int main() {
    // Init stdio
    stdio_init_all();

    // Set up the display
    display_setup();
    display_set_backlight(60);

    // Set up the capactive touch
    touch_setup();
    touch_setup_interrupt();

    uint8_t colors[3][3] = {{0xFF, 0, 0}, {0, 0xFF, 0}, {0, 0, 0xFF}};
    uint8_t color_index = 0;

    while (true){

        // If new touch input, read touch data
        if(touch_flags) {
            uint16_t touchX[2], touchY[2], touchID[2];
            touch_read_data(touchX, touchY, touchID);
            touch_flags = touch_flags & ~0b0000001;
        }

        // Draw to the display
        //display_draw_screen(colors[color_index++]);
        //if(color_index == 3)
        //    color_index = 0;
        //printf("Drawing\n");


    }
    return 0;
}