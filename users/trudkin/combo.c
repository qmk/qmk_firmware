/* Copyright 2020 Terence Rudkin
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
#include QMK_KEYBOARD_H
#include "trudkin.h"



/* early attempt to may CUA cut&paste */
/* TO DO make a combo header then move lines below */
enum combo_events { AX_CUT, AC_COPY, AV_PASTE };

const uint16_t PROGMEM cut_combo[]   = {KC_A, KC_X, COMBO_END};
const uint16_t PROGMEM copy_combo[]  = {KC_A, KC_C, COMBO_END};
const uint16_t PROGMEM paste_combo[] = {KC_A, KC_V, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    [AX_CUT]   = COMBO_ACTION(cut_combo),
    [AC_COPY]  = COMBO_ACTION(copy_combo),
    [AV_PASTE] = COMBO_ACTION(paste_combo),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
    switch (combo_index) {
        case AX_CUT:
            if (pressed) {
                tap_code16(RSFT(KC_DEL));
            }
            break;
        case AC_COPY:
            if (pressed) {
                tap_code16(RCTL(KC_INS));
            }
            break;
        case AV_PASTE:
            if (pressed) {
                tap_code16(RSFT(KC_INS));
            }
            break;
    }
}


