#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

extern volatile bool isLeftHand;

#ifdef MASTER_CHECK_USB_ENUMERATED
    extern volatile bool contacted_by_master;
    extern void keyboard_master_setup(void);
    extern void keyboard_slave_setup(void);
#endif


void matrix_master_OLED_init (void);
