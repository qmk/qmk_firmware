/* Copyright 2020 DmNosachev
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
#include QMK_KEYBOARD_H

#define LAYOUT_debug( \
    K00, K01, K02, K03, K04, K05, K06, K07, \
    K10, K11, K12, K13, K14, K15, K16, K17, \
    K20, K21, K22, K23, K24, K25, K26, K27, \
    K30, K31, K32, K33, K34, K35, K36, K37, \
    K40, K41, K42, K43, K44, K45, K46, K47, \
    K50, K51, K52, K53, K54, K55, K56, K57, \
    K60, K61, K62, K63, K64, K65, K66, K67, \
    K70, K71, K72, K73, K74, K75, K76, K77, \
    K80, K81, K82, K83, K84, K85, K86, K87, \
    K90, K91, K92, K93, K94, K95, K96, K97, \
    KA0, KA1, KA2, KA3, KA4, KA5, KA6, KA7, \
    KB0, KB1, KB2, KB3, KB4, KB5, KB6, KB7, \
    KC0, KC1, KC2, KC3, KC4, KC5, KC6, KC7, \
    KD0, KD1, KD2, KD3, KD4, KD5, KD6, KD7, \
    KE0, KE1, KE2, KE3, KE4, KE5, KE6, KE7 \
) { \
    { K00, K01, K02, K03, K04, K05, K06, K07 }, \
    { K10, K11, K12, K13, K14, K15, K16, K17 }, \
    { K20, K21, K22, K23, K24, K25, K26, K27 }, \
    { K30, K31, K32, K33, K34, K35, K36, K37 }, \
    { K40, K41, K42, K43, K44, K45, K46, K47 }, \
    { K50, K51, K52, K53, K54, K55, K56, K57 }, \
    { K60, K61, K62, K63, K64, K65, K66, K67 }, \
    { K70, K71, K72, K73, K74, K75, K76, K77 }, \
    { K80, K81, K82, K83, K84, K85, K86, K87 }, \
    { K90, K91, K92, K93, K94, K95, K96, K97 }, \
    { KA0, KA1, KA2, KA3, KA4, KA5, KA6, KA7 }, \
    { KB0, KB1, KB2, KB3, KB4, KB5, KB6, KB7 }, \
    { KC0, KC1, KC2, KC3, KC4, KC5, KC6, KC7 }, \
    { KD0, KD1, KD2, KD3, KD4, KD5, KD6, KD7 }, \
    { KE0, KE1, KE2, KE3, KE4, KE5, KE6, KE7 } \
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [0] = LAYOUT_debug(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    uprintf("row: %u, col: %u, pressed: %u\n", record->event.key.row, record->event.key.col, record->event.pressed);
#endif 
  return true;
}