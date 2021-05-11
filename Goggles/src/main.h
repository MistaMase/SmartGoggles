#include <stdio.h>                      // C stdlib library
#include "tusb.h"                       // Software Serial for USB 
#include "pico/stdlib.h"                // Gives the pico stdlib
#include "display.h"                    // Gives our project display support
#include "touch.h"                      // Gives our project touch support
#include "imu.h"                        // Gives our project imu support
#include "interrupt.h"                  // Gives our project interrupt support
#include "gps.h"                        // Gives our project gps support

#define DEBUG_MODE true                 // Ensures software serial configured before execution