#include "display.h"

void display_setup() {
    // Set up the backlight
    display_setup_backlight();

    // Set up SPI0 at 80 MHz for 
    spi_init(spi0, 20000000);
    gpio_set_function(D_RX, GPIO_FUNC_SPI);
    gpio_set_function(D_SCK, GPIO_FUNC_SPI);
    gpio_set_function(D_TX, GPIO_FUNC_SPI);
    
    // Make the SPI pins availible to picotool
    bi_decl(bi_3pins_with_func(D_RX, D_TX, D_SCK, GPIO_FUNC_SPI));

    // Chip select is active-low, so initialise it to a driven-high state
    gpio_init(D_CS);
    gpio_set_dir(D_CS, GPIO_OUT);
    gpio_put(D_CS, 1);
    
    // Make the CS pin availible to picotool
    bi_decl(bi_1pin_with_name(D_CS, "SPI CS"));

    // Set up the data/command pin
    gpio_init(D_DorC);
    gpio_set_dir(D_DorC, GPIO_OUT);
    gpio_put(D_DorC, 0);        // 1 for data, 0 for command
    bi_decl(bi_1pin_with_name(D_DorC, "SPI D/C"));

    // Load the initial configuration into the display
    uint8_t cmd, x, numArgs;
    const uint8_t *addr = initcmd;
    while ((cmd = *(addr++)) > 0) {
        x = *(addr++);
        numArgs = x & 0x7F;
        spi_write_blocking(spi0, &cmd, numArgs);
        addr += numArgs;
        if (x & 0x80)
            sleep_ms(150);
    }
}

void display_draw_screen(uint8_t color[3]) {
    // Switch to data mode
    gpio_put(D_DorC, 1);
    gpio_put(D_CS, 0);

    // Send the display data
     for(int i = 0; i < ILI9341_TFTHEIGHT * ILI9341_TFTWIDTH; i++) {
        spi_write_blocking(spi0, color, 3);
    }

    // Switch back to command mode
    gpio_put(D_DorC, 0);
    gpio_put(D_CS, 1);

}


/* Set the LCD backlight brighness */
void display_set_backlight(unsigned char brightness) {
    pwm_set_gpio_level(D_LITE, brightness);
}

/* Set up PWM for backlight on display */
void display_setup_backlight() {
    // Configure the backlight pin as PWM
    gpio_set_function(D_LITE, GPIO_FUNC_PWM);

    // Find out which PWM slice is connected to GPIO D_LITE
    uint slice_num = pwm_gpio_to_slice_num(D_LITE);

    // Set period of 255 cycles (0 to 255 inclusive) (unsigned char)
    pwm_set_wrap(slice_num, 255);

    // Set the PWM running
    pwm_set_enabled(slice_num, true);
}