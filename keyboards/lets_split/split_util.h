#ifndef SPLIT_KEYBOARD_UTIL_H
#define SPLIT_KEYBOARD_UTIL_H

#include <stdbool.h>

#ifdef EE_HANDS
	#define EECONFIG_BOOTMAGIC_END      (uint8_t *)10
	#define EECONFIG_HANDEDNESS         EECONFIG_BOOTMAGIC_END
#endif

#define SLAVE_I2C_ADDRESS           0x32

extern volatile bool isLeftHand;

// slave version of matix scan, defined in matrix.c
void matrix_slave_scan(void);

void split_keyboard_setup(void);
bool has_usb(void);
void keyboard_slave_loop(void);

#endif
