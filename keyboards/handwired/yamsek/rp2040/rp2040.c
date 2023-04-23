/* SPDX-License-Identifier: GPL-2.0-or-later */

#include <gpio.h>

/** Waveshare RP2040-Zero

               ┌─────── USB ──────┐
              ─┤5V               0├─
        trrS  ─┤Gnd              1├─
        Trrs  ─┤3.3              2├─ I2C1 SDA  trRs
     Column 6 ─┤29               3├─ I2C1 SCL  tRrs
       "    5 ─┤28 Boot    Reset 4├─
       "    4 ─┤27  ██  ╔╗  ██   5├─ Row 1
       "    3 ─┤26  ██  ╚╝  ██   6├─  "  2
       "    2 ─┤15      16       7├─  "  3
       "    1 ─┤14 13 12 11 10 9 8├─  "  4
               └───┬──┬──┬──┬──┬──┘

    Rows 0-2 are on the top-shell/half
    Row 3 is the thumb-cluster
*/

const pin_t row_pins_MCU[MATRIX_ROWS / 2] = {GP5, GP6, GP7, GP8};
const pin_t col_pins_MCU[MATRIX_COLS]     = {GP14, GP15, GP26, GP27, GP28, GP29};
