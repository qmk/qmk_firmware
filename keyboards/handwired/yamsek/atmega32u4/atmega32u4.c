/* SPDX-License-Identifier: GPL-2.0-or-later */

#include <gpio.h>

/** Pololu A-Star 32U4 Micro
    micro
                   ┌───USB───┐
    Column 0  PB5 ─┤9      A0├─ PF7 (future: joystick?)
       "   1  PB4 ─┤8      A1├─ PF6 (future: joystick?)
       "   2  PE6 ─┤7      10├─ PB6 Row 0
       "   3  PD7 ─┤6      11├─ PB7 Row 1
       "   4  PC6 ─┤5      12├─ PD6 Row 2
       "   5  PD4 ─┤4        ├─ Reset
     I2C SCL  PD0 ─┤3        ├─ 3V3
     I2C SDA  PD1 ─┤2        ├─ 5V
     RGB LED  PD3 ─┤1  OOO   ├─ Gnd
      Row 3   PD2 ─┤0  ICSP  ├─ Vin
                   └─────────┘

    Rows 0-2 are on the top-shell/half
    Row 3 is the thumb-cluster
*/

const pin_t row_pins_MCU[MATRIX_ROWS / 2] = {B6, B7, D6, D2};
const pin_t col_pins_MCU[MATRIX_COLS]     = {B5, B4, E6, D7, C6, D4};
