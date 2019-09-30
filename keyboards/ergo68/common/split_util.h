#pragma once

#include <stdbool.h>
#include "eeconfig.h"
#include "quantum.h"

#define SLAVE_I2C_ADDRESS           0x32

extern volatile bool isLeftHand;
extern volatile bool contacted_by_master;

bool has_usb(void);

// slave version of matix scan, defined in matrix.c
void matrix_slave_scan(void);
