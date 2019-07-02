#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

extern volatile bool isLeftHand;
extern volatile bool contacted_by_master;

void matrix_master_OLED_init (void);
