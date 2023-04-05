/* Copyright 2023 @ Mike Killewald (https://github.com/mkillewald)
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
#include "keychron_common.h"
#include "keymap_user.h"
#include "keymap_user_config.h"
#ifdef RGB_MATRIX_ENABLE
#    include "rgb_matrix_user.h"
#endif

// clang-format off

#ifdef RGB_MATRIX_ENABLE
enum my_bootloader_state {
    BOOTLOADER_INACTIVE,
    BOOTLOADER_PRESSED,
    BOOTLOADER_WAIT,
    BOOTLOADER_DO
} bootloader_state;
#endif

enum my_keycodes {
    KC_LIGHT_TAB_TOGGLE = QK_USER_0,
    KC_LIGHT_ALPHAS_TOGGLE,
    KC_FN_LAYER_TRANSPARENT_KEYS_TOGGLE,
    KC_FN_LAYER_COLOR_TOGGLE,
    KC_LOCK_BLANK_MAC
};

#define KC_LTTOG KC_LIGHT_TAB_TOGGLE
#define KC_LATOG KC_LIGHT_ALPHAS_TOGGLE
#define KC_TKTOG KC_FN_LAYER_TRANSPARENT_KEYS_TOGGLE
#define KC_FCTOG KC_FN_LAYER_COLOR_TOGGLE
#define KC_LBMAC KC_LOCK_BLANK_MAC

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_ansi_67(
        QK_GESC, KC_1,     KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,          KC_MUTE,
        KC_TAB,  KC_Q,     KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,          KC_PGUP,
        KC_CAPS, KC_A,     KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,            KC_ENT,           KC_PGDN,
        KC_LSFT,           KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,   KC_SLSH,            KC_RSFT, KC_UP,
        KC_LCTL, KC_LOPTN, KC_LCMMD,                           KC_SPC,                             KC_RCMMD, MO(_FN1), MO(_FN3), KC_LEFT, KC_DOWN, KC_RGHT),

    [WIN_BASE] = LAYOUT_ansi_67(
        QK_GESC, KC_1,     KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,          KC_MUTE,
        KC_TAB,  KC_Q,     KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,          KC_PGUP,
        KC_CAPS, KC_A,     KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,            KC_ENT,           KC_PGDN,
        KC_LSFT,           KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,   KC_SLSH,            KC_RSFT, KC_UP,
        KC_LCTL, KC_LWIN,  KC_LALT,                            KC_SPC,                             KC_RALT,  MO(_FN2), MO(_FN3), KC_LEFT, KC_DOWN, KC_RGHT),

    // Mac Fn1
    [_FN1] = LAYOUT_ansi_67(
        KC_GRV,  KC_BRID,  KC_BRIU, KC_MCTL, KC_LPAD, RGB_VAD, RGB_VAI, KC_MPRV, KC_MPLY, KC_MNXT,    KC_MUTE,    KC_VOLD,  KC_VOLU,  _______,          G(KC_0),
        _______, KC_LBMAC, _______, _______, _______, _______, _______, _______, _______, _______,    _______,    _______,  _______,  _______,          G(KC_LEFT),
        _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______,    _______,    _______,            _______,          G(KC_RGHT),
        _______,           _______, _______, _______, _______, _______, _______, _______, LCAG(KC_W), LCAG(KC_D), _______,            _______, _______,
        _______, _______,  _______,                            _______,                               _______,    _______,  _______,  _______, _______, _______),

    // Win Fn1
    [_FN2] = LAYOUT_ansi_67(
        KC_GRV,  KC_BRID, KC_BRIU, KC_TASK, KC_FLXP, RGB_VAD, RGB_VAI, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,          C(KC_0),
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______,  _______,          KC_HOME,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,            _______,          KC_END,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,            _______, _______,
        _______, _______, _______,                            _______,                            _______,  _______,  _______,  _______, _______, _______),

    // Combined Mac Win Fn2
    [_FN3] = LAYOUT_ansi_67(
        KC_TILD, KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_F12,   QK_BOOT,          RGB_TOG,
        RGB_TOG, RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______, _______, _______, _______, _______, _______,  _______,  _______,          KC_DEL,
        _______, RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  _______, _______, _______, _______, _______, _______,            _______,          KC_HOME,
        AC_TOGG,           KC_LTTOG, KC_LATOG, KC_TKTOG, KC_FCTOG, _______, _______, _______, _______, _______, _______,            _______, _______,
        _______, _______,  _______,                                _______,                            _______, _______,  _______,  _______, _______, _______)
};

// clang-format on

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [MAC_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [WIN_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_FN1]     = { ENCODER_CCW_CW(G(KC_MINS), G(KC_EQL)) },
    [_FN2]     = { ENCODER_CCW_CW(C(KC_MINS), C(KC_EQL)) },
    [_FN3]     = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI) },
};
#endif

void housekeeping_task_user(void) {
#ifdef RGB_MATRIX_ENABLE
    switch(bootloader_state) {
        case BOOTLOADER_DO:
            // bootloader was pressed two frames ago. RGB should now be off,
            // so we can call the bootloader.
            reset_keyboard();
            break;
        case BOOTLOADER_WAIT:
            // bootloader was pressed on previous frame, we wait this frame and
            // set flag to do bootloader at end of next frame. For some reason, my
            // Q2 needed this extra wait frame.
            bootloader_state = BOOTLOADER_DO;
            break;
        case BOOTLOADER_PRESSED:
            // User pressed bootloader keycode and RGB was disabled earlier in this
            // frame. However RGB changes wont take place immediately, so we set a
            // flag here which will be caught at end of the next frame.
            bootloader_state = BOOTLOADER_WAIT;
            break;
        default:
            break;
        }
#endif

    housekeeping_task_keychron();
}

void matrix_init_user(void) {
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_init_user();
#endif
}

void keyboard_post_init_user(void) {
    user_config_read();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (process_record_keychron(keycode, record)) {
        switch (keycode) {
            case QK_BOOT:
#ifdef RGB_MATRIX_ENABLE
                // We want to turn off LEDs before calling bootloader, so here
                // we call rgb_matrix_disable_noeeprom() and set a flag because
                // the LEDs won't be updated until the next frame.
                rgb_matrix_disable_noeeprom();
                bootloader_state = BOOTLOADER_PRESSED;
                return false;  // Skip all further processing of this key
#endif
                return true;  // Allow further processing of this key
            case KC_LIGHT_TAB_TOGGLE:
                if (record->event.pressed) {
                    user_config_toggle_caps_lock_light_tab();
                }
                return false;  // Skip all further processing of this key
            case KC_LIGHT_ALPHAS_TOGGLE:
                if (record->event.pressed) {
                    user_config_toggle_caps_lock_light_alphas();
                }
                return false;  // Skip all further processing of this key
            case KC_FN_LAYER_TRANSPARENT_KEYS_TOGGLE:
                if (record->event.pressed) {
                    user_config_toggle_fn_layer_transparent_keys_off();
                }
                return false;  // Skip all further processing of this key
            case KC_FN_LAYER_COLOR_TOGGLE:
                if (record->event.pressed) {
                    user_config_toggle_fn_layer_color_enable();
                }
                return false;  // Skip all further processing of this key
            case KC_LOCK_BLANK_MAC:
                if (record->event.pressed) {
                    send_string(SS_LCTL(SS_LGUI("q")) SS_DELAY(225) SS_TAP(X_ESC));
                }
                return false;  // Skip all further processing of this key
            default:
                return true;  // Process all other keycodes normally
        }
    }
    return true;
}
