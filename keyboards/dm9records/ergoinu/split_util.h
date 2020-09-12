#pragma once

#include <stdbool.h>
#include "eeconfig.h"

extern volatile bool isLeftHand;

// follower version of matix scan, defined in matrix.c
void matrix_follower_scan(void);

void split_keyboard_setup(void);
bool has_usb(void);
