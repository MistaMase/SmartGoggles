#ifndef TOUCH_H
#define TOUCH_H

#include "pins.h"                       // Constants for pin defs
#include "hardware/i2c.h"               // Allows for access to I2C
#include "pico/stdlib.h"                // Gives the pico stdlib
#include "pico/binary_info.h"           // Allows for the I2C pins to be mapped
#include "hardware/gpio.h"              // Allows access to the GPIOs
#include "flags.h"                      // Sets the flag for a touch interrupt
#include <stdio.h>                      // Should be removed - Prints values of touch data

#define CAP_TOUCH_I2C_ADDR      0x38    // I2C address for the touch IC

void touch_setup(void);
void touch_read_data(uint16_t touchX[2], uint16_t touchY[2], uint16_t touchID[2]);
void touch_setup_interrupt(void);
void touch_callback(void);

#endif