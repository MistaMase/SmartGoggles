#include "imu.h"

void imu_reset() {
    // Software reset the device (and clear registers)
    uint8_t addr = IMU_PWR_MGMT1;
    uint8_t cmd = 0x80;
    uint8_t buf[2] = {addr, cmd};
    i2c_write_blocking(i2c0, IMU_I2C_ADDR, buf, 2, false);
    sleep_ms(50);

    // Disable sleep mode
    cmd = 0x01;
    buf[1] = cmd;
    i2c_write_blocking(i2c0, IMU_I2C_ADDR, buf, 2, false);
    sleep_ms(50);
}

void imu_setup() {
    // Set up I2C at 400 KHz
    i2c_init(i2c0, 400 * 1000);

    // Configure the IMU's I2C pins 
    gpio_set_function(IMU_SDA, GPIO_FUNC_I2C);
    gpio_set_function(IMU_SCL, GPIO_FUNC_I2C);

    // Set the pull up resistors because I2C
    gpio_pull_up(IMU_SDA);
    gpio_pull_up(IMU_SCL);

    // Make the I2C pins availible to picotool
    bi_decl(bi_2pins_with_func(IMU_SDA, IMU_SCL, GPIO_FUNC_I2C));

    // Software reset the IMU
    imu_reset();

    // Configure the gyro rate to 500 (dps)
    uint8_t addr = IMU_GYRO_SET_SCALE;
    uint8_t cmd = 0x08;
    i2c_write_blocking(i2c0, IMU_I2C_ADDR, &addr, 1, true);
    i2c_write_blocking(i2c0, IMU_I2C_ADDR, &cmd, 1, false);

    // Configure the accelerometer rate to +- 8g
    addr = IMU_ACL_SET_SCALE;
    cmd = 0x10;
    i2c_write_blocking(i2c0, IMU_I2C_ADDR, &addr, 1, true);
    i2c_write_blocking(i2c0, IMU_I2C_ADDR, &cmd, 1, false);

    // /* Configure the IMU for interrupts */
    // // Enable motion interrupts
    // uint8_t addr = IMU_INT_EN;
    // uint8_t config = 0x40;
    // i2c_write_blocking(i2c0, IMU_I2C_ADDR, &addr, 1, true);
    // i2c_write_blocking(i2c0, IMU_I2C_ADDR, &config, 1, false);

    // // Clear any interrupt if a value is read
    // addr = IMU_INT_CFG;
    // config = 0x10;
    // i2c_write_blocking(i2c0, IMU_I2C_ADDR, &addr, 1, true);
    // i2c_write_blocking(i2c0, IMU_I2C_ADDR, &config, 1, false);

    // // Enable the Wake on Motion Logic
    // addr = IMU_WAKE_MT_EN;
    // config = 0xC0;
    // i2c_write_blocking(i2c0, IMU_I2C_ADDR, &addr, 1, true);
    // i2c_write_blocking(i2c0, IMU_I2C_ADDR, &config, 1, false);

    // // Set wake on motion threshold
    // addr = IMU_WAKE_MT_TH;
    // config = 5; // milli gs
    // i2c_write_blocking(i2c0, IMU_I2C_ADDR, &addr, 1, true);
    // i2c_write_blocking(i2c0, IMU_I2C_ADDR, &config, 1, false);
}

void imu_read_data(float acceleration[3], float gyro[3], float mag[3], float *temp) {
    // Buffer for incoming data
    uint8_t buffer[6];

    /* Accelerometer */
    // Gain control of the bus
    uint8_t imu_reg = IMU_ACL_REG_H;
    i2c_write_blocking(i2c0, IMU_I2C_ADDR, &imu_reg, 1, true);

    // Read accelerometer X,Y,Z as 6 8-bit values
    // Each read is 1 byte and the IMU internal registers are auto-incrementing
    i2c_read_blocking(i2c0, IMU_I2C_ADDR, buffer, 6, false);

    // Convert the high/low bytes to 2-byte values
    for(int i = 0; i < 3; i++) {
        int16_t acc = (buffer[i*2] << 8 | buffer[(i*2) + 1]);
        acceleration[i] = IMU_ACL_SCALE * (float)acc;
    }

    /* Gyrometer */
    // Gain control of the bus
    imu_reg = IMU_GYRO_REG_H;
    i2c_write_blocking(i2c0, IMU_I2C_ADDR, &imu_reg, 1, true);

    // Read gyrometer X,Y,Z as 6 8-bit values
    // Each read is 1 byte and the IMU internal registers are auto-incrementing
    i2c_read_blocking(i2c0, IMU_I2C_ADDR, buffer, 6, false);

    // Convert the high/low bytes to 2-byte values
    for(int i = 0; i < 3; i++) {
        int16_t g = (buffer[i*2] << 8 | buffer[(i*2) + 1]);
        gyro[i] = IMU_GYRO_SCALE * (float)g;
    }

    /* Magnetometer */
    // Gain control of the bus
    imu_reg = IMU_MAG_REG_H;
    i2c_write_blocking(i2c0, IMU_MAG_I2C_ADDR, &imu_reg, 1, true);

    // Read magnetometer X,Y,Z as 6 8-bit values
    // Each read is 1 byte and the IMU internal registers are auto-incrementing
    i2c_read_blocking(i2c0, IMU_MAG_I2C_ADDR, buffer, 6, false);

    // Conver the high/low bytes to 2-byte values
    for(int i = 0; i < 3; i++) {
        int16_t m = (buffer[i*2] << 8 | buffer[(i*2) + 1]);
        mag[i] = IMU_MAG_SCALE * (float)m;
    }

    /* Temperature */
    // Gain control of the bus
    imu_reg = IMU_TEMP_REG_H;
    i2c_write_blocking(i2c0, IMU_I2C_ADDR, &imu_reg, 1, true);
    
    // Read temp as 2 8-bit values
    i2c_read_blocking(i2c0, IMU_I2C_ADDR, buffer, 2, false);

    // Convert the high/low bytes to a 2-byte value
    *temp = (buffer[0] << 8 | buffer[1]);

    // TODO Convert to C
}