#ifndef FLAGS_H
#define FLAGS_H

// Touch flags 
// B7-B1: Unused
// B0: Touch interrupt for I2C
unsigned char touch_flags;


void setup_flags(void);

#endif