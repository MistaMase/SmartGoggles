#ifndef INTERRUPT_H
#define INTERRUPT_H

#include "pico/stdlib.h"
#include "pins.h"

// Touch flags 
// B7-B1: Unused
// B0: Touch interrupt for I2C
volatile unsigned char touch_flags;


void service_gpio_interrupts(uint gpio, uint32_t events);

#endif