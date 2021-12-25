/* Copyright 2021 Jonavin Eng
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

#ifdef RGB_MATRIX_ENABLE

    // Custom RGB Colours
    #define RGB_GODSPEED 0x00, 0xE4, 0xFF // colour for matching keycaps
    #define RGB_NAUTILUS 0x00, 0xA4, 0xA9 // Naurilus Font colours
    #define RGB_PURPLELITE 0x80, 0x00, 0x80 // Purple colours

    // RGB LED locations
    enum led_location_map {
        LED_ESC, // 0
        LED_1,  // 1
        LED_2,  // 2
        LED_3,  // 3
        LED_4,  // 4
        LED_5,  // 5
        LED_6,  // 6
        LED_7,  // 7
        LED_8,  // 8
        LED_9,  // 9
        LED_0,  // 10
        LED_MINS,   // 11
        LED_EQL,    // 12
        LED_BSPC,   // 13
        LED_DEL,    // 14
        LED_TAB,    // 15
        LED_Q,  // 16
        LED_W,  // 17
        LED_E,  // 18
        LED_R,  // 19
        LED_T,  // 20
        LED_Y,  // 21
        LED_U,  // 22
        LED_I,  // 23
        LED_O,  // 24
        LED_P,  // 25
        LED_LBRC,   // 26  [
        LED_RBRC,   // 27  ]
        LED_BSLS,   // 28  |
        LED_PGUP,   // 29
        LED_CAPS,   // 30
        LED_A,  // 31
        LED_S,  // 32
        LED_D,  // 33
        LED_F,  // 34
        LED_G,  // 35
        LED_H,  // 36
        LED_J,  // 37
        LED_K,  // 38
        LED_L,  // 39
        LED_SCLN, // 40    ;
        LED_QUOT, // 41    "
        LED_ENT, // 42
        LED_PGDN,   // 43
        LED_LSFT,   // 44
        LED_Z,  // 45
        LED_X,  // 46
        LED_C,  // 47
        LED_V,  // 48
        LED_B,  // 49
        LED_N,  // 50
        LED_M,  // 51
        LED_COMM, // 52  ,
        LED_DOT,    // 53  .
        LED_SLSH,   // 54 /
        LED_RSFT,   // 55
        LED_UP, // 56
        LED_END, // 57
        LED_LCTL, // 58
        LED_LWIN, // 59
        LED_LALT, // 60
        LED_SPC, // 61
        LED_FN, // 62
        LED_RCTL, // 63
        LED_LEFT, // 64
        LED_DOWN, // 65
        LED_RIGHT // 66
    };

    const uint8_t LED_LIST_WASD[] = { LED_W, LED_A, LED_S, LED_D };

    const uint8_t LED_LIST_ARROWS[] = { LED_LEFT, LED_RIGHT, LED_UP, LED_DOWN };

    const uint8_t LED_LIST_NUMROW[] = { LED_ESC, LED_1, LED_2, LED_3, LED_4, LED_5, LED_6, LED_7, LED_8, LED_9, LED_0, LED_MINS, LED_EQL, LED_BSPC, LED_DEL};
    const uint8_t LED_LIST_QWERTYROW[] = { LED_TAB, LED_Q, LED_W, LED_E, LED_R, LED_T, LED_Y, LED_U, LED_I, LED_O, LED_P, LED_LBRC, LED_RBRC, LED_BSLS, LED_PGUP};

    const uint8_t LED_LIST_NUMPAD[] = {
        LED_7, LED_8, LED_9,
        LED_U, LED_I, LED_O,
        LED_J, LED_K, LED_L,
        LED_M, LED_COMM, LED_DOT
        };

#endif
