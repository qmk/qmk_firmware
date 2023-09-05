/* Copyright 2020 Sam Reinehr
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
enum my_keycodes {
    K00 = SAFE_RANGE,
    K01,
    K02,
    K03,
    K04,
    K05,
    K06,
    K07,
    K08,
    K09,
    K10,
    K11,
    K12,
    K13,
    K14,
    K15,
};
/* just a simple way to give each key a unique code */
//clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [0] = LAYOUT_ortho_4x4(
        K00, K01, K02, K03,
        K04, K05, K06, K07,
        K08, K09, K10, K11,
        K12, K13, K14, K15
    )
};
/* flags describing current free square/0 */
uint8_t current = 0;
/* r g and b describe the colors for the initial map,
currently blank for free, and evenly spaced hues with maximum sat/value  */
const uint8_t r[16] = {
    0x00, 0xFF, 0xFF, 0xFF,
    0xCC, 0x66, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x66, 0xCC, 0xFF, 0xFF
};
const uint8_t g[16] = {
    0x00, 0x00, 0x66, 0xCC,
    0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xCC, 0x66, 0x00,
    0x00, 0x00, 0x00, 0x00
};
const uint8_t b[16] = {
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x66,
    0xCC, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xCC, 0x66
};
/* pos contains the current positions, could technically be compressed to 4 bits per, but not worth it
   index into pos is the position we're looking at, output is the tile that is currently there */
uint8_t tiles[16] = {
    0, 1, 2, 3,
    4, 5, 6, 7,
    8, 9, 10, 11,
    12, 13, 14, 15
};
/* default led array for super 16 has them in a snake, so we must do some remapping/flipping of the 2nd and 4th rows */
uint8_t remap[16] = {
    0, 1, 2, 3,
    7, 6, 5, 4,
    8, 9, 10, 11,
    15, 14, 13, 12
};
//clang-format on
/* function to refresh the led coloring with the positions with current tiles */
void refresh_leds(void) {
    for (uint8_t index = 0; index < 16; ++index) {
        uint8_t tile = tiles[index];
        setrgb(r[tile], g[tile], b[tile], (rgb_led_t *)&led[remap[index]]);
    }
    rgblight_set();
}
void keyboard_post_init_user(void) {
    rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
    rgblight_enable_noeeprom();
    refresh_leds();
}
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uint8_t offset = keycode - K00;
    uint8_t x      = offset & 0x03;
    uint8_t y      = (offset & 0x0C) >> 2;
    /* if the adjacent space exists and is empty, */
    if ((x > 0 && 0 == tiles[offset - 1]) || (y > 0 && 0 == tiles[offset - 4]) || (x < 3 && 0 == tiles[offset + 1]) || (y < 3 && 0 == tiles[offset + 4])) {
        /* set the currently blank tile to this tile, and make this one blank */
        tiles[current] = tiles[offset];
        tiles[offset]  = 0;
        current        = offset;
    }
    refresh_leds();
    return false;
}
