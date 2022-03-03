#pragma once

#ifdef SPLIT_KEYBOARD
#   error This is helix local split_util.h.
#   error This header file is used only when SPLIT_KEYBOARD=no.
#endif

#include <stdbool.h>
#include "eeconfig.h"

#define SLAVE_I2C_ADDRESS           0x32

extern volatile bool isLeftHand;

// slave version of matix scan, defined in matrix.c
void matrix_slave_scan(void);

void split_keyboard_setup(void);
bool is_helix_master(void);

void matrix_master_OLED_init (void);
