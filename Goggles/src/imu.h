#ifndef IMU_H
#define IMU_H

#include "pins.h"                       // Constants for pin defs
#include "hardware/i2c.h"               // Allows for access to I2C
#include "pico/stdlib.h"                // Gives the pico stdlib
#include "pico/binary_info.h"           // Allows for the I2C pins to be mapped
#include "hardware/gpio.h"              // Allows access to the GPIOs
#include "interrupt.h"                      // Sets the flag for a imu interrupt

/* Generic Device Info */
#define IMU_I2C_ADDR        0x68                    // I2C address for the IMU (acclerometer and gyro)
#define IMU_MAG_I2C_ADDR    0x48                    // I2C address for the IMU (magnetometer)
#define IMU_ACL_REG_H       0x3B                    // Start of IMU Accleration Registers
#define IMU_GYRO_REG_H      0x43                    // Start of IMU Gyrometer Registers
#define IMU_TEMP_REG_H      0x41                    // Start of IMU Temperature Registers
#define IMU_MAG_REG_H       0x03                    // Start of IMU Magnetometer Registers


/* Interrupt Setup (If Used) */
#define IMU_INT_PIN_CFG     0x37
#define IMU_INT_EN          0x38
#define IMU_INT_CFG         0x37
#define IMU_INT_EN          0x38
#define IMU_WAKE_MT_TH      0x1F
#define IMU_WAKE_MT_EN      0x69

/* Hardware Commands */
#define IMU_PWR_MGMT1       0x6B            // Enable/Disable sleep are reset internal registers
#define IMU_PWR_MGMT2       0x6C   

/* Hardware sensor scale */
#define IMU_GYRO_SET_SCALE  0x1B
#define IMU_ACL_SET_SCALE   0x1C


/* Software scale for reading data */
#define IMU_ACL_SCALE       1.0f / 4096.0f    /* LSB/(g) */  // Set the scale for acceleration to +-8 G
#define IMU_GYRO_SCALE      1.0f / 65.5f      /* LSB/(deg/s) */  // Set the scale for gyrometer to +-500 Deg/s
#define IMU_MAG_SCALE       1.0f / 0.6f       /* LSB/uT */ // Set the scale for the magnetometer

void imu_reset(void);
void imu_setup(void);
void imu_read_data(float acceleration[3], float gyro[3], float mag[3], float *temp);

#endif