#ifndef DISPLAY_H
#define DISPLAY_H

#include "hardware/pwm.h"
#include "pico/stdlib.h"
#include "hardware/gpio.h" 
#include "pico/binary_info.h"
#include "hardware/spi.h"
#include "pins.h"
#include <stdio.h>

void display_setup(void);
void display_initialize_settings(void);
void display_set_addr_window(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void display_send_command(uint8_t cmd);
void display_send_command_and_params8(uint8_t cmd, uint8_t *data, size_t num_params);
void display_send_command_and_params16(uint8_t cmd, uint16_t *data, size_t num_params);
void display_set_command(void);
void display_set_data(void);
void display_enable_cs(void);
void display_disable_cs(void);
void display_draw_screen(uint16_t color);
void display_setup_backlight(void);
void display_set_backlight(unsigned char backlight);

// Display constants
#define ILI9341_TFTWIDTH    240         // TFT Max Width
#define ILI9341_TFTHEIGHT   320         // TFT Max Height

#define ILI9341_SOFTRESET       0x01    // Software reset
#define ILI9341_SLEEPIN         0x10    //
#define ILI9341_SLEEPOUT        0x11    // Leave sleep mode
#define ILI9341_NORMALDISP      0x13
#define ILI9341_INVERTOFF       0x20
#define ILI9341_INVERTON        0x21
#define ILI9341_GAMMASET        0x26
#define ILI9341_DISPLAYOFF      0x28    // Disable frame output
#define ILI9341_DISPLAYON       0x29    // Enable frame output
#define ILI9341_COLADDRSET      0x2A
#define ILI9341_PAGEADDRSET     0x2B
#define ILI9341_MEMORYWRITE     0x2C
#define ILI9341_PIXELFORMAT     0x3A    // Define interface and MCU pixel depth 
#define ILI9341_FRAMECONTROL    0xB1    // Set the framerate
#define ILI9341_DISPLAYFUNC     0xB6
#define ILI9341_ENTRYMODE       0xB7    // Set the logic output voltage and endable/disable low voltage control
#define ILI9341_POWERCONTROL1   0xC0    // Set the display voltage level 
#define ILI9341_POWERCONTROL2   0xC1    // Set the power step-up factor
#define ILI9341_VCOMCONTROL1    0xC5    // Set the VCOM high and low voltage
#define ILI9341_VCOMCONTROL2    0xC7    // Set the VCOM offset 
#define ILI9341_MEMCONTROL      0x36    // Set the memory-to-display mapping
#define ILI9341_MADCTL          0x36

#define ILI9341_MADCTL_MY       0x80
#define ILI9341_MADCTL_MX       0x40
#define ILI9341_MADCTL_MV       0x20
#define ILI9341_MADCTL_ML       0x10
#define ILI9341_MADCTL_RGB      0x00
#define ILI9341_MADCTL_BGR      0x08
#define ILI9341_MADCTL_MH       0x04

#endif
