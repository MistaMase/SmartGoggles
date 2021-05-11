#include "interrupt.h"

void service_gpio_interrupts(uint gpio, uint32_t events) {
    /* Touch Interrupt */
    if(gpio & T_IRQ)
        touch_flags |= 1;
}


