#pragma once

#define USE_I2C

/* Use an extra LED on the right side since it's wider on the 65% PCB. */
#undef RGBLED_NUM
#define RGBLED_NUM 17

/* Set up RGB lighting so it works with either side as master. */
#define RGBLED_SPLIT { 8, 9 }
