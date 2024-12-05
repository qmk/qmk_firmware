/* Copyright 2023 Tom Parker-Shemilt <palfrey@tevp.net>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>

#include QMK_KEYBOARD_H

// clang-format off

// Exact keymap is irrelevant as we're using rows/cols
// but we need _something_ set so we're using no-ops
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
    )};

bool tiles[5][5] = {
    {false, false, false, false, false},
    {false, false, false, false, false},
    {false, false, false, false, false},
    {false, false, false, false, false},
    {false, false, false, false, false},
};

/* Because snake pattern of leds */
const uint8_t remap[25] = {
    20,21,22,23,24,
    19,6,7,8,9,
    18,5,0,1,10,
    17,4,3,2,11,
    16,15,14,13,12,
};

// clang-format on

bool is_blank(void) {
    for (uint8_t y = 0; y < 5; y++) {
        for (uint8_t x = 0; x < 5; x++) {
            if (tiles[x][y]) {
                return false;
            }
        }
    }
    return true;
}

void do_move(uint8_t x, uint8_t y) {
    tiles[x][y] ^= true;
    if (x > 0) {
        tiles[x - 1][y] ^= true;
    }
    if (y > 0) {
        tiles[x][y - 1] ^= true;
    }
    if (x < 4) {
        tiles[x + 1][y] ^= true;
    }
    if (y < 4) {
        tiles[x][y + 1] ^= true;
    }
}

void refresh_leds(void) {
    for (uint8_t y = 0; y < 5; y++) {
        for (uint8_t x = 0; x < 5; x++) {
            uint8_t tile  = tiles[x][y];
            uint8_t index = (y * 5) + x;
            if (tile) {
                setrgb(RGB_RED, &led[remap[index]]);
            } else {
                setrgb(RGB_WHITE, &led[remap[index]]);
            }
        }
    }
    rgblight_set();
}

uint8_t initial_moves = 1;

void start_game(void) {
    rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
    srand(timer_read32());
    while (true) {
        for (uint8_t i = 0; i < initial_moves; i++) {
            do_move(rand() % 5, rand() % 5);
        }
        if (!is_blank()) {
            // Catch the "we picked the same location 2*N times" case
            break;
        }
    }
    refresh_leds();
}

void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();
    start_game();
}

bool won = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        if (won) {
            initial_moves++;
            won = false;
            start_game();
        } else {
            uint8_t x = record->event.key.col;
            uint8_t y = record->event.key.row;
            do_move(x, y);
            if (is_blank()) {
                rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL);
                won = true;
            }
        }
    }
    refresh_leds();
    return true;
}
