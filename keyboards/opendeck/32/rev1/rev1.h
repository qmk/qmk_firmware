/* Copyright 2020 cmdremily
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "quantum.h"

#define POWER_LED_PIN F1
#define RGB_DISABLE_N_PIN D2
#define RGB_IRQ_N_PIN D3

// If you want something similar to what Taran from LMG does in https://github.com/TaranVH/2nd-keyboard
// you can create a "wrapper key" by uncommenting the row below and chosing your wrapper keycode.
// You can then change the keymap in ../keymaps/default/keymap.c to adjust what key is sent inside the
// wrapper.
// Note: The default is to not wrap and to send F13-F24 with combinations of shift/control/alt as these
// are immediately usable in most software (e.g. OBS and DCSB for streaming) without using AHK.
//#define KC_WRAPPER_KEY KC_F24

// clang-format off
#define LAYOUT_ortho_4x8( \
    Q00, Q01, Q02, Q03, Q04, Q05, Q06, Q07, \
    Q10, Q11, Q12, Q13, Q14, Q15, Q16, Q17, \
    Q20, Q21, Q22, Q23, Q24, Q25, Q26, Q27, \
    Q30, Q31, Q32, Q33, Q34, Q35, Q36, Q37  \
) { \
    {Q00, Q01, Q02, Q03, Q04, Q05, Q06, Q07}, \
    {Q10, Q11, Q12, Q13, Q14, Q15, Q16, Q17}, \
    {Q20, Q21, Q22, Q23, Q24, Q25, Q26, Q27}, \
    {Q30, Q31, Q32, Q33, Q34, Q35, Q36, Q37}  \
}
// clang-format on
