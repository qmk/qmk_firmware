#pragma once

/*
 * Quefrency lacks I2C resistors on the right PCB, so the right half doesn't
 * work independently. (Presumably the floating I2C lines cause a problem.)
 * Using serial seems sufficiently fast in practice and allows both halves to
 * be used independently.
 */
#define USE_SERIAL

/* Use an extra LED on the right side since it's wider on the 65% PCB. */
#undef RGBLED_NUM
#define RGBLED_NUM 17

/* Set up RGB lighting so it works with either side as master. */
#define RGBLED_SPLIT { 8, 9 }
