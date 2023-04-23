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
    K16,
    K17,
    K18,
    K19,
    K20,
    K21,
    K22,
    K23,
    K24
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        K00, K01, K02, K03, K04,
        K05, K06, K07, K08, K09,
        K10, K11, K12, K13, K14,
        K15, K16, K17, K18, K19,
        K20, K21, K22, K23, K24
    )
};

uint8_t tiles[5][5] = {
    {0,0,0,0,0},
    {0,0,0,0,0},
    {0,0,0,0,0},
    {0,0,0,0,0},
    {0,0,0,0,0},
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
            if (tiles[x][y] == 1) {
                return false;
            }
        }
    }
    return true;
}

void do_move(uint8_t x, uint8_t y) {
    tiles[x][y] ^= 1;
    if (x > 0) {
        tiles[x - 1][y] ^= 1;
    }
    if (y > 0) {
        tiles[x][y - 1] ^= 1;
    }
    if (x < 4) {
        tiles[x + 1][y] ^= 1;
    }
    if (y < 4) {
        tiles[x][y + 1] ^= 1;
    }
}

void refresh_leds(void) {
    for (uint8_t y = 0; y < 5; y++) {
        for (uint8_t x = 0; x < 5; x++) {
            uint8_t tile  = tiles[x][y];
            uint8_t index = (y * 5) + x;
            if (tile == 1) {
                setrgb(RGB_RED, &led[remap[index]]);
            } else {
                setrgb(RGB_WHITE, &led[remap[index]]);
            }
        }
    }
    rgblight_set();
}

#define INITIAL_MOVES 1

void start_game(void) {
    rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
    for (uint8_t i = 0; i < INITIAL_MOVES; i++) {
        do_move(random() % 5, random() % 5);
    }
    refresh_leds();
}

void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();
    start_game();
}

uint8_t led_index = 0;
bool    won       = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        if (won) {
            won = false;
            start_game();
        } else {
            uint8_t offset = keycode - K00;
            div_t   coords = div(offset, 5);
            uint8_t x      = coords.rem;
            uint8_t y      = coords.quot;
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
