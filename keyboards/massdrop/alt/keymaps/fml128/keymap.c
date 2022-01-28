/*
Copyright 2021 Merlin Jehli <merlin@jeh.li> @fml128

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

#include QMK_KEYBOARD_H


#ifdef RGB_MATRIX_ENABLE
static uint16_t idle_timer;
static uint8_t minute_counter;
static bool led_on;
#endif


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_65_ansi_blocker(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,  \
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME, \
        _______, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGUP, \
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_PGDN, \
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(1),   KC_LEFT, KC_DOWN, KC_RGHT  \
    ),
    [1] = LAYOUT_65_ansi_blocker(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______,_______,_______, _______, _______, _______, _______, _______, \
        RESET, _______,_______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
        _______, _______, _______,                            _______,                            KC_RCTL, _______, _______, _______, _______  \
    ),
    /*
    [X] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______  \
    ),
    */
};

void keyboard_post_init_user(void) {
    #ifdef RGB_MATRIX_ENABLE
        rgblight_enable_noeeprom();
        rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
        rgb_matrix_set_flags(LED_FLAG_ALL);
        rgblight_sethsv(COLOR);

        led_on = true;
        idle_timer = timer_read();
        minute_counter = 0;
    #endif
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    #ifdef RGB_MATRIX_ENABLE
            rgblight_enable_noeeprom();
            led_on = true;
            idle_timer = timer_read();
            minute_counter = 0;
    #endif

    switch (keycode) {
        //case SWITCH_USB:
        //    switch_usb();
        //    return false;
        #ifdef RGB_MATRIX_ENABLE
            case MO(1):
                if(record->event.pressed) {
                    rgblight_sethsv(HSV_PURPLE);
                    return true;
                } else {
                    rgblight_sethsv(COLOR);
                }
        #endif
        default:
            return true;
        }
}

void matrix_scan_user(void) {
    #ifdef RGB_MATRIX_ENABLE
        if (led_on) {
            if (timer_elapsed(idle_timer) >= 60000) {
                minute_counter++;
                idle_timer = timer_read();

                if (minute_counter >= BACKLIGHT_TIMEOUT) {
                    rgblight_disable_noeeprom();
                    led_on = false;
                    minute_counter = 0;
                    idle_timer = timer_read();
                }
            }
        }
    #endif
}

