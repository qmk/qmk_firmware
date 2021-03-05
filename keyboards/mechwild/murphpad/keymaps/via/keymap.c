/* Copyright 2021 Kyle McCreery
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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN1,
	_FN2,
	_FN3
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
                 KC_F1,    KC_F2,   KC_F3,   KC_F4,
                 KC_NLCK,  KC_PSLS, KC_PAST, KC_PMNS,
                 KC_P7,    KC_P8,   KC_P9,   KC_PPLS,
        KC_MUTE, KC_P4,    KC_P5,   KC_P6,   KC_NO,
        MO(_FN1), KC_P1,    KC_P2,   KC_P3,   KC_PENT,
        KC_BSPC, KC_P0,    KC_NO,   KC_PDOT, KC_NO
    ),
    [_FN1] = LAYOUT(
                 _______,  _______, _______, _______,
                 _______,  _______, _______, _______,
                 RGB_HUD,  RGB_SPI, RGB_HUI, _______,
        _______, RGB_RMOD, RGB_TOG, RGB_MOD, KC_NO,
        _______, RGB_VAD,  RGB_SPD, RGB_VAI, _______,
        _______, RGB_SAD,  KC_NO,   RGB_SAI, KC_NO
    ),
	[_FN2] = LAYOUT(
                 _______,  _______, _______, _______,
                 _______,  _______, _______, _______,
                 _______,  _______, _______, _______,
        _______,  _______, _______, _______, KC_NO,
        _______,  _______, _______, _______, _______,
        _______,  _______, _______, _______, KC_NO
    ),
	[_FN3] = LAYOUT(
                 _______,  _______, _______, _______,
                 _______,  _______, _______, _______,
                 _______,  _______, _______, _______,
        _______,  _______, _______, _______, KC_NO,
        _______,  _______, _______, _______, _______,
        _______,  _______, _______, _______, KC_NO
    )
};


#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise) {
    switch (index) {
        case 0:
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
        break;
    }
    
}
#endif

#ifdef OLED_DRIVER_ENABLE
    oled_rotation_t oled_init_user(oled_rotation_t rotation) {
        return OLED_ROTATION_180;       // flips the display 180 degrees if offhand
    }
    

static void render_logo(void) {     // Render MechWild "MW" Logo
    static const char PROGMEM logo_1[] = {0x97, 0x98, 0x99, 0x9A,0x00};
    static const char PROGMEM logo_2[] = {0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0x00};
    static const char PROGMEM logo_3[] = {0xD7, 0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xB6, 0x00};
    static const char PROGMEM logo_4[] = {0xB6, 0xB6, 0xB6, 0x9B, 0x9C, 0x9D, 0x9E, 0x00};
    oled_set_cursor(0,0);
    oled_write_P(logo_1, false);
    oled_set_cursor(0,1);
    oled_write_P(logo_2, false);
    oled_set_cursor(0,2);
    oled_write_P(logo_3, false);
    oled_set_cursor(0,3);
    oled_write_P(logo_4, false);
}
void oled_task_user(void) {
    render_logo(); 
}
#endif