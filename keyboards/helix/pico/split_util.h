#pragma once

#include <stdbool.h>
#include "eeconfig.h"

#define SLAVE_I2C_ADDRESS           0x32

extern volatile bool isLeftHand;

// slave version of matix scan, defined in matrix.c
void matrix_slave_scan(void);

void split_keyboard_setup(void);
bool is_helix_master(void);

void matrix_master_OLED_init (void);

// stubs as this is handled by legacy code
static inline void split_pre_init(void){}
static inline void split_post_init(void){}
