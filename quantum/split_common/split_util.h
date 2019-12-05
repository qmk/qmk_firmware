#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

extern volatile bool isLeftHand;

void matrix_master_OLED_init(void);
void set_internal_I2C_pullups(void);
void keyboard_split_setup(void);
