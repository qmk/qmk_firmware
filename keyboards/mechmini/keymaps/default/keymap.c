/*
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "mechmini.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    KEYMAP(
        TAB,  Q,    W,    E,    R,    T,    Y,    U,   I,    O,    P,    BSLS,
        LCTL, A,    S,    D,    F,    G,    H,    J,   K,    L,    SCLN,
        LSFT, Z,    X,    C,    V,    B,    N,    M,   COMM, DOT,  SLSH,
        GRV,  LALT, LGUI,       SPC,        ENT,       RGUI, RALT, RCTL
    )
};

const uint16_t PROGMEM fn_actions[] = {
};
