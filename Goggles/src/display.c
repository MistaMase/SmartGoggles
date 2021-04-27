#include "display.h"

void display_setup() {
    printf("Starting display setup");
    // Set up the backlight
    display_setup_backlight();

    // Set up SPI0 at 80 MHz for 
    spi_init(spi0, 80 * 1000 * 1000);
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

    gpio_put(D_CS, 0);

    // Set up the data/command pin
    gpio_init(D_DorC);
    gpio_set_dir(D_DorC, GPIO_OUT);
    display_set_command();
    bi_decl(bi_1pin_with_name(D_DorC, "SPI D/C"));


    /* Load the configuration variables */
    // Soft Reset
    display_send_command(0x01);
    sleep_ms(100);

    // Set Gamma
    display_send_command(ILI9341_GAMMASET);
    display_send_command_param(0x01);

    // Positive Gamma Correction
    display_send_command(ILI9341_GMCTRP1);
    display_write_data((uint8_t[15]){ 0x0f, 0x31, 0x2b, 0x0c, 0x0e, 0x08, 0x4e, 0xf1, 0x37, 0x07, 0x10, 0x03, 0x0e, 0x09, 0x00 }, 15);
    
    // Negative Gamma Correction
    display_send_command(ILI9341_GMCTRN1);
    display_write_data((uint8_t[15]){ 0x00, 0x0e, 0x14, 0x03, 0x11, 0x07, 0x31, 0xc1, 0x48, 0x08, 0x0f, 0x0c, 0x31, 0x36, 0x0f }, 15);

    // Memory Access Control
    display_send_command(ILI9341_MADCTL);
    display_send_command_param(0x48);

    // Pixel Format
    display_send_command(ILI9341_PIXFMT);
    display_send_command_param(0x55);   // 16 bit TODO Change

    // Frame Rate - default - 70 Hz
    display_send_command(ILI9341_FRMCTR1);
    display_send_command_param(0x00);
    display_send_command_param(0x1B);

    // Exit Sleep
    display_send_command(ILI9341_SLPOUT);
    
    // Display On
    display_send_command(ILI9341_DISPON);

    // Set the display column and page address
    display_set_column_page_addr();

    // ???
    display_send_command(ILI9341_MEMWR);
}

void display_set_column_page_addr() {
    // Column Address Set
    display_send_command(ILI9341_CASET);
    display_send_command_param(0x00);
    display_send_command_param(0x00);
    display_send_command_param(0x00);
    display_send_command_param(0xEF); // End column -> 239

    // Page Address Set
    display_send_command(ILI9341_PASET);
    display_send_command_param(0x00);
    display_send_command_param(0x00);
    display_send_command_param(0x01);
    display_send_command_param(0x0F);   // Was 0x3F
}

void display_send_command(uint8_t cmd) {
    // Start the display reading over SPI
    display_enable_cs();

    // Set to command mode
    display_set_command();

    // Write command
    spi_write_blocking(spi0, &cmd, 1);

    // Swap to data mode
    display_set_data();

    // Stop the display reading over SPI
    display_disable_cs();
}

void display_send_command_param(uint8_t param) {
    // Enable to display reading over SPI
    display_enable_cs();

    // Write the parameter
    spi_write_blocking(spi0, &param, 1);

    // Disable to display reading over SPI
    display_disable_cs();
}

void display_write_data(void *buffer, int bytes) {
    // Enable the display to read over SPI
    display_enable_cs();

    // Write the contents of the buffer to the display
    spi_write_blocking(spi0, buffer, bytes);

    // Disable the display to read over SPI
    display_disable_cs();
}

/* Enables the display SPI by setting the CS pin to low (low-active) */
void display_enable_cs() {
    asm volatile("nop \n nop \n nop");
    // Low active, display reads data over SPI bus
    gpio_put(D_CS, 0);
    asm volatile("nop \n nop \n nop");
}

/* Disables the display SPI by setting the CS pin to high (low-active) */
void display_disable_cs() {
    asm volatile("nop \n nop \n nop");
    // Low active, disables SPI on display
    gpio_put(D_CS, 1);
    asm volatile("nop \n nop \n nop");
}

/* Set the display SPI data mode to data */
void display_set_data() {
    // 1 for command, 0 for data
    gpio_put(D_DorC, 0);        
}

/* Set the display SPI data mode to command */
void display_set_command() {
    // 1 for command, 0 for data
    gpio_put(D_DorC, 1);
}

void display_draw_screen(uint8_t color[2]) {
    // Enable the display to listen over SPI
    display_enable_cs();

    // Set the memory column and page address
    display_set_column_page_addr();

    // Send the command to write to memory
    display_send_command(ILI9341_MEMWR);

    // Switch to data mode
    display_set_data();

    uint8_t buffer[ILI9341_TFTHEIGHT * ILI9341_TFTWIDTH * 2];
    for(int i = 0; i < ILI9341_TFTHEIGHT * ILI9341_TFTWIDTH * 2; i++) {
        if(i % 2 == 0)
            buffer[i] = color[0];
        else
            buffer[i] = color[1];
    }


    // Send the display data
    display_write_data(buffer, ILI9341_TFTHEIGHT * ILI9341_TFTWIDTH * 2);

    // Disable the display to listen over SPI
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
