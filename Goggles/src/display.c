#include "display.h"

void display_setup() {
    printf("Starting display setup");
    // Set up the backlight
    display_setup_backlight();

    // Pico max SPI clock is SYS_CLK / 2, so we'll set it to 40 MHz to be safe
    // Set up SPI0 at 40 MHz for 
    spi_init(spi0, 10 * 1000 * 1000);
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
    display_set_command();
    bi_decl(bi_1pin_with_name(D_DorC, "SPI D/C"));

    // Configure the display settings properly
    display_initialize_settings();
}

void display_initialize_settings() {
    uint8_t params8[1];
    uint16_t params16[1];

    // Soft restart the display
    display_send_command(ILI9341_SOFTRESET);
    sleep_ms(50);

    // Disable display output
    display_send_command(ILI9341_DISPLAYOFF);

    // Set power to 4.6V
    params8[0] = 0x23;
    display_send_command_and_params8(ILI9341_POWERCONTROL1, params8, 1);

    // Set the step-up factor
    params8[0] = 0x10;
    display_send_command_and_params8(ILI9341_POWERCONTROL2, params8, 1);

    // Set the VCOMH voltage level to 3.775V and VCOML voltage level to -1.425V
    params16[0] = 0x2B2B;
    display_send_command_and_params16(ILI9341_VCOMCONTROL1, params16, 1);

    // Enable the VCOM offset and set its offset to 0 and 0
    params8[0] = 0xC0;
    display_send_command_and_params8(ILI9341_POWERCONTROL2, params8, 1);

    // Set memory read order to Row Address (Rows are outer loop) and color mode to BGR
    params8[0] = (ILI9341_MADCTL_MY | ILI9341_MADCTL_BGR);
    display_send_command_and_params8(ILI9341_MEMCONTROL, params8, 1);

    // Set interface to 16-bit pixels, set MCU to 16-bit pixels -> Direct 16 bit to 16 bit mapping
    params8[0] = 0x55;
    display_send_command_and_params8(ILI9341_PIXELFORMAT, params8, 1);

    // Set frame rate to 70Hz with no division -> 27 display clocks per line
    params16[0] = 0x001B;
    display_send_command_and_params16(ILI9341_FRAMECONTROL, params16, 1);

    // Set the transistor output voltages to normal and enable low voltage detection control
    params8[0] = 0x07;
    display_send_command_and_params8(ILI9341_ENTRYMODE, params8, 1);

    // Enable the display internal logic
    display_send_command(ILI9341_SLEEPOUT);
    sleep_ms(150);

    // Enable the display output
    display_send_command(ILI9341_DISPLAYON);
    sleep_ms(150);
}

// New
void display_set_addr_window(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
    // Get the X and Y for the column address
    uint16_t col_addrs[2] = {x1, y1};

    // Get the X and Y for the page address
    uint16_t page_addrs[2] = {x2, y2};

    // Send the column address using the COLADDRSET command
    display_send_command_and_params16(ILI9341_COLADDRSET, col_addrs, 2);

    // Send the page address using the PAGEADDRSET command
    display_send_command_and_params16(ILI9341_PAGEADDRSET, page_addrs, 2);
}
// New
void display_send_command(uint8_t cmd) {
    // Start the display reading over SPI
    display_enable_cs();

    // Set to command mode
    display_set_command();

    // Write command
    spi_write_blocking(spi0, &cmd, 1);

    // Stop the display reading over SPI
    display_disable_cs();
}
// New
void display_send_command_and_params8(uint8_t cmd, uint8_t *data, size_t num_params) {
    // Start the display reading over SPI
    display_enable_cs();

    // Set to command mode
    display_set_command();

    // Write command
    spi_write_blocking(spi0, &cmd, 1);

    // Swap to data mode 
    display_set_data();

    // Write parameters
    spi_write_blocking(spi0, data, num_params);

    // Stop the display reading over SPI
    display_disable_cs();
}
// New
void display_send_command_and_params16(uint8_t cmd, uint16_t *data, size_t num_params) {
    // Start the display reading over SPI
    display_enable_cs();

    // Set to command mode
    display_set_command();

    // Write command
    spi_write_blocking(spi0, &cmd, 1);

    // Swap to data mode
    display_set_data();

    // Write parameters
    spi_write16_blocking(spi0, data, num_params);

    // Stop the display reading over SPI
    display_disable_cs();
}

// New
/* Enables the display SPI by setting the CS pin to low (low-active) */
void display_enable_cs() {
    // Low active, display reads data over SPI bus
    gpio_put(D_CS, 0);
}

// New
/* Disables the display SPI by setting the CS pin to high (low-active) */
void display_disable_cs() {
    // Low active, disables SPI on display
    gpio_put(D_CS, 1);
}

// New
/* Set the display SPI data mode to data */
void display_set_data() {
    // 0 for command, 1 for data
    gpio_put(D_DorC, 1);        
}

// New
/* Set the display SPI data mode to command */
void display_set_command() {
    // 0 for command, 1 for data
    gpio_put(D_DorC, 0);
}

void display_draw_screen(uint16_t color) {

    // Set the memory window to the entire frame buffer
    display_set_addr_window(0, 0, ILI9341_TFTWIDTH-1, ILI9341_TFTHEIGHT-1);

    // Start the display reading over SPI
    display_enable_cs();

    // Set to command mode
    display_set_command();

    // Send write to memory command
    uint8_t command = ILI9341_MEMORYWRITE;
    spi_write_blocking(spi0, &command, 1);

    // Swap to data mode
    display_set_data();

    for(uint8_t row = 0; row < ILI9341_TFTWIDTH; row++) {
        for(uint col = 0; col < ILI9341_TFTHEIGHT; col++) {
            spi_write16_blocking(spi0, &color, 1);
        }
    }

    // Stop the display reading over SPI
    display_disable_cs();
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
