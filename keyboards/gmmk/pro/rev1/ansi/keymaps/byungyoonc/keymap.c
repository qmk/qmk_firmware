/* Copyright 2021 Choi Byungyoon <byungyoonc@gmail.com>

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
#include "byungyoonc.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//      ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12      Prt           Rotary(Mic Mute)
//      ~        1        2        3        4        5        6        7        8        9        0         -       (=)      BackSpc           TaskMgr
//      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        \                 Del
//      Caps     A        S        D        F        G        H        J        K        L        ;        "                 Enter             Home
//      Sh_L              Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       End
//      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right

    [0] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR,          KC_MMUT,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_TASK,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_DEL,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_HOME,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(1),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [1] = LAYOUT(
        _______, KC_BRID, KC_BRIU, KC_CALC, KC_MSEL, RGB_VAD, RGB_VAI, KC_MRWD, KC_MPLY, KC_MFFD, KC_MUTE, KC_VOLD, KC_VOLU, _______,          _______,
        _______, KC_SEC1, KC_SEC2, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, DB_TOGG,          _______,
        _______, _______, _______, RGB_SAI, _______, _______, _______, _______, _______, _______, _______, _______, _______, QK_BOOT,          _______,
        _______, _______, _______, RGB_SAD, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, RGB_HUI, RGB_HUD, _______, _______, NK_TOGG, _______, _______, _______, _______,          _______, RGB_MOD, _______,
        _______, GUI_TOG, _______,                            _______,                            _______, _______, _______, RGB_SPD, RGB_RMOD, RGB_SPI
    ),


};
// clang-format on

bool process_record_user_kb(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        rgblight_increase_hue();
    }
    return true;
}

#if defined(ENCODER_ENABLE)
bool encoder_update_user(uint8_t index, bool clockwise) {
    uint8_t mod_state = get_mods();
    if (mod_state & MOD_MASK_CTRL) {
        unregister_mods(MOD_MASK_CTRL);
        if (clockwise) {
            tap_code16(LCTL(KC_RGHT));
        } else {
            tap_code16(LCTL(KC_LEFT));
        }
        set_mods(mod_state);
    } else {
        if (clockwise) {
            tap_code16(KC_VOLU);
        } else {
            tap_code16(KC_VOLD);
        }
    }
    //return true; //set to return false to counteract enabled encoder in pro.c
    return false;
}
#endif  // ENCODER_ENABLE

static void set_rgb_caps_leds(void);

static void set_rgb_caps_leds(void) {
    rgb_matrix_set_color(73, 0xFF, 0x77, 0x77);  // Left side LED 3
    rgb_matrix_set_color(74, 0xFF, 0x77, 0x77);  // Right side LED 3
    rgb_matrix_set_color(76, 0xFF, 0x77, 0x77);  // Left side LED 4
    rgb_matrix_set_color(77, 0xFF, 0x77, 0x77);  // Right side LED 4
    rgb_matrix_set_color(80, 0xFF, 0x77, 0x77);  // Left side LED 5
    rgb_matrix_set_color(81, 0xFF, 0x77, 0x77);  // Right side LED 5
    rgb_matrix_set_color(83, 0xFF, 0x77, 0x77);  // Left side LED 6
    rgb_matrix_set_color(84, 0xFF, 0x77, 0x77);  // Right side LED 6
    rgb_matrix_set_color(3, 0xFF, 0x77, 0x77);   // CAPS LED
}

static void set_rgb_nlck_notset_leds(void);

static void set_rgb_wlck_leds(void);

static void set_rgb_nlck_notset_leds(void) {
    rgb_matrix_set_color(67, 0x77, 0x77, 0xFF);  // Left side LED 1
    rgb_matrix_set_color(68, 0x77, 0x77, 0xFF);  // Right side LED 1
    rgb_matrix_set_color(70, 0x77, 0x77, 0xFF);  // Left side LED 2
    rgb_matrix_set_color(71, 0x77, 0x77, 0xFF);  // Right side LED 2
}

static void set_rgb_wlck_leds(void) {
    rgb_matrix_set_color(87, 0x77, 0xFF, 0x77);  // Left side LED 7
    rgb_matrix_set_color(88, 0x77, 0xFF, 0x77);  // Right side LED 7
    rgb_matrix_set_color(91, 0x77, 0xFF, 0x77);  // Left side LED 8
    rgb_matrix_set_color(92, 0x77, 0xFF, 0x77);  // Right side LED 8
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    led_t led_state = host_keyboard_led_state();
    if (led_state.caps_lock) {
        set_rgb_caps_leds();
    }
    if (!led_state.num_lock) {
        set_rgb_nlck_notset_leds();
    }
    if (keymap_config.no_gui) {
        set_rgb_wlck_leds();
    }
    return false;
}

void matrix_output_unselect_delay(uint8_t line, bool key_pressed) {
    for (int i = 0; i < 20; i++) {
        wait_cpuclock(STM32_SYSCLK / 1000000L);
    }
}
