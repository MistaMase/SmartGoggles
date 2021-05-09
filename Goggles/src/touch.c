#include "touch.h"

/* Set up I2C */
void touch_setup() {
    // Configure I2C1 as 50 KHz
    i2c_init(i2c1, 50 * 1000);

    // Configure the T_SDA and T_SCK pins as I2C pins
    gpio_set_function(T_SDA, GPIO_FUNC_I2C);
    gpio_set_function(T_SCK, GPIO_FUNC_I2C);

    // Set the pull up resistors because I2C
    gpio_pull_up(T_SDA);
    gpio_pull_up(T_SCK);

    // Make the I2C pins availible to picotool
    bi_decl(bi_2pins_with_func(T_SDA, T_SCK, GPIO_FUNC_I2C));
}

/* Read the data from the capacitive touch panel */
void touch_read_data(uint16_t touchX[2], uint16_t touchY[2], uint16_t touchID[2], uint8_t *num_touches){
    uint8_t buf[16];

    // Write to the bus - True to keep master control of bus
    i2c_write_blocking(i2c1, CAP_TOUCH_I2C_ADDR, (uint8_t)0, 1, true);

    // Read from the bus
    i2c_read_blocking(i2c1, CAP_TOUCH_I2C_ADDR, buf, 16, false);

    // Determine the number of touches
    uint8_t touches = buf[0x02];
    *num_touches = touches;
    if ((touches > 2) || (touches == 0)) {
    touches = 0;
    }

    // Read and parse the data
    for(uint8_t i = 0; i < 2; i++){
        touchX[i] = buf[0x03 + i * 6] & 0x0F;
        touchX[i] <<= 8;
        touchX[i] |= buf[0x04 + i * 6];
        touchY[i] = buf[0x05 + i * 6] & 0x0F;
        touchY[i] <<= 8;
        touchY[i] |= buf[0x06 + i * 6];
        touchID[i] = buf[0x05 + i * 6] >> 4;
    }
}

/* Configures an interrupt on the touch I2C interrupt pin */
void touch_setup_interrupt() {
    // Set up the interrupt
    gpio_set_irq_enabled_with_callback(T_IRQ, GPIO_IRQ_EDGE_RISE, true, service_interrupts);
}