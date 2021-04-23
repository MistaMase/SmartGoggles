#ifndef DISPLAY_H
#define DISPLAY_H

#include "hardware/pwm.h"
#include "pico/stdlib.h"
#include "hardware/gpio.h" 
#include "pico/binary_info.h"
#include "hardware/spi.h"
#include "pins.h"
#include <stdio.h>

void display_set_column_page_addr(void);
void display_send_command(uint8_t cmd);
void display_send_command_param(uint8_t param);
void display_write_data(void *buffer, int bytes);
void display_set_command(void);
void display_set_data(void);
void display_enable_cs(void);
void display_disable_cs(void);
void display_setup(void);
void display_draw_screen(uint8_t color[2]);
void display_setup_backlight(void);
void display_set_backlight(unsigned char backlight);

// Display constants
#define ILI9341_TFTWIDTH    240         // TFT Max Width
#define ILI9341_TFTHEIGHT   360         // TFT Max Height

#define ILI9341_PWCTR1      0xC0        // Power Control 1
#define ILI9341_PWCTR2      0xC1        // Power Control 2
#define ILI9341_VMCTR1      0xC5        // VCOM Control 1
#define ILI9341_VMCTR2      0xC7        // VCOM Control 2
#define ILI9341_MADCTL      0x36        // Memory Address Control
#define ILI9341_VSCRLDEF    0x33        // Vertical Scroll Definition
#define ILI9341_VSCRSADD    0x37        // Vertical Scrolling Start Address
#define ILI9341_PIXFMT      0x3A        // Pixel Format Set
#define ILI9341_FRMCTR1     0xB1        // Framerate Control - Normal, Full Color
#define ILI9341_DFUNCTR     0xB6        // Display Function Control
#define ILI9341_GAMMASET    0x26        // Gamma Set
#define ILI9341_GMCTRP1     0xE0        // Positive Gamma Correction
#define ILI9341_GMCTRN1     0xE1        // Negative Gamma Correction
#define ILI9341_SLPOUT      0x11        // Sleep Out
#define ILI9341_DISPON      0x29        // Display On
#define ILI9341_MEMWR       0x2C        // Write to frame memory
#define ILI9341_CASET       0x2A        // TODO
#define ILI9341_PASET       0x2B        // TODO

// Display init commands
static const uint8_t initcmd[] = {
  0xEF, 3, 0x03, 0x80, 0x02,
  0xCF, 3, 0x00, 0xC1, 0x30,
  0xED, 4, 0x64, 0x03, 0x12, 0x81,
  0xE8, 3, 0x85, 0x00, 0x78,
  0xCB, 5, 0x39, 0x2C, 0x00, 0x34, 0x02,
  0xF7, 1, 0x20,
  0xEA, 2, 0x00, 0x00,
  ILI9341_PWCTR1  , 1, 0x23,             // Power control VRH[5:0]
  ILI9341_PWCTR2  , 1, 0x10,             // Power control SAP[2:0];BT[3:0]
  ILI9341_VMCTR1  , 2, 0x3e, 0x28,       // VCM control
  ILI9341_VMCTR2  , 1, 0x86,             // VCM control2
  ILI9341_MADCTL  , 1, 0x48,             // Memory Access Control
  ILI9341_VSCRLDEF, 4, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0008,     // Set the deadzone of the screen (no dead zone)
  ILI9341_VSCRSADD, 1, 0x00,             // Vertical scroll zero TODO Maybe remove second parameter?
  ILI9341_PIXFMT  , 1, 0x66,             // Set to 18-bit color (6, 6, 6) per pixel
  ILI9341_FRMCTR1 , 2, 0x00, 0x18,
  ILI9341_DFUNCTR , 3, 0x08, 0x82, 0x27, // Display Function Control
  /*0xF2, 1, 0x00,                         // 3Gamma Function Disable
  ILI9341_GAMMASET , 1, 0x01,            // Gamma curve selected
  ILI9341_GMCTRP1 , 15, 0x0F, 0x31, 0x2B, 0x0C, 0x0E, 0x08, // Set Gamma
    0x4E, 0xF1, 0x37, 0x07, 0x10, 0x03, 0x0E, 0x09, 0x00,
  ILI9341_GMCTRN1 , 15, 0x00, 0x0E, 0x14, 0x03, 0x11, 0x07, // Set Gamma
    0x31, 0xC1, 0x48, 0x08, 0x0F, 0x0C, 0x31, 0x36, 0x0F,*/
  ILI9341_SLPOUT, 0, 0x80,               // Exit Sleep
  ILI9341_DISPON, 0, 0x80,               // Display on
  0x00                                   // End of list
};

#endif