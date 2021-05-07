#include "imu.h"

void imu_reset() {
    // Reset the device 
    // TODO Change configuration parameters
    uint8_t buf[] = {0x6B, 0x00};
    i2c_write_blocking(i2c0, IMU_I2C_ADDR, buf, 2, false);
}

void imu_setup() {
    // Set up I2C at 400 KHz
    i2c_init(i2c0, 400 * 1000);
    gpio_set_function(I2)
}