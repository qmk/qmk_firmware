// Copyright 2022 MatteoDM <matteodalmo@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"


/* Mask out handedness diode to prevent it
*  from keeping the keyboard awake
* - just mirroring `KC_NO` in the `LAYOUT`
*   macro to keep it simple
*/
const matrix_row_t matrix_mask[] = {
    0b00111111,
    0b00111111,
    0b01111111,
    0b01111111,
    0b01111111,
    0b00111111,
    0b00111111,
    0b01111111,
    0b01111111,
    0b01111111
};
