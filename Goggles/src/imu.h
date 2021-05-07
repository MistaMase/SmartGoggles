#ifndef IMU_H
#define IMU_H

#include "pins.h"                       // Constants for pin defs
#include "hardware/i2c.h"               // Allows for access to I2C
#include "pico/stdlib.h"                // Gives the pico stdlib
#include "pico/binary_info.h"           // Allows for the I2C pins to be mapped
#include "hardware/gpio.h"              // Allows access to the GPIOs
#include "flags.h"                      // Sets the flag for a imu interrupt

#define IMU_I2C_ADDR      0x68    // I2C address for the IMU

void imu_setup(void);

#endif