// Copyright 2022 thewerther (@thewerther)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

#define _DEFAULT_LAYER 0
#define _NON_FUNC_LAYER 1
#define _FUNC_LAYER 2
#define _SETTINGS_LAYER 3

enum custom_keycodes {
  BASE_LAYER_CHANGE = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
     * │ESC│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ Backsp│ ` │
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
     * │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │  \  │DEL│
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
     * │ Caps │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │  Enter │APP│
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
     * │ Shift  │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │ Shift│ ↑ │   │
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┼───┼───┤
     * │Ctrl│GUI │Alt │                        │Alt│GUI│Ctl│ ← │ ↓ │ → │
     * └────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┴───┘
     */
    [_DEFAULT_LAYER] = LAYOUT_all(
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC,        KC_GRV,
        KC_TAB,   KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC,              KC_DEL,
        KC_RALT,    KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_BSLS, KC_ENT, KC_NO,
        KC_LSFT,      KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,    KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT,  LT(_FUNC_LAYER, KC_SPC), MO(_SETTINGS_LAYER), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_NON_FUNC_LAYER] = LAYOUT_all(
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC,        KC_GRV,
        KC_TAB,   KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC,              KC_DEL,
        KC_F1,    KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_BSLS, KC_ENT, KC_NO,
        KC_LSFT,      KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,    KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT,          KC_SPC,          MO(_SETTINGS_LAYER), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_FUNC_LAYER] = LAYOUT_all(
        _______, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, _______,                _______,
        _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,
        _______,    _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, _______, _______, _______, _______, _______,
        _______,      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,_______,
        _______, _______, _______,                         _______,                       _______, _______, _______, _______, _______
    ),
    [_SETTINGS_LAYER] = LAYOUT_all(
        KC_ESC, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  XXXXXXX,           BASE_LAYER_CHANGE,
        XXXXXXX,     RGB_TOG, RGB_MOD,  RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, XXXXXXX, KC_MPLY, KC_MPRV, KC_MNXT, XXXXXXX,     KC_HOME,
        XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,            KC_END,
        XXXXXXX,           RESET,  XXXXXXX,  XXXXXXX, XXXXXXX, KC_VOLD, KC_MUTE, KC_VOLU, XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,   XXXXXXX,   XXXXXXX,                      XXXXXXX,                              XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,    XXXXXXX
    ),
};

static bool shift_space_pressed = false;

void keyboard_post_init_user(void) {
#   if defined(COMMAND_ENABLE) || defined(CONSOLE_ENABLE)
    // Customise these values to desired behaviour
    debug_enable=true;
    debug_matrix=true;
    //debug_keyboard=true;
    //debug_mouse=true;
#   endif
    // Call the post init code.
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom(HSV_MAGENTA);
    rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_MOOD);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // If console is enabled, it will print the matrix position and status
    // of each key pressed.
#   if defined(CONSOLE_ENABLE)
    uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n",
            keycode,
            record->event.key.col,
            record->event.key.row,
            record->event.pressed);
#   endif
    switch (keycode) {
        case LT(_FUNC_LAYER, KC_SPC):
            if (record->event.pressed) { // key pressed
                // disable the hold action of LT(FUNC_LAYER, KC_SPC) when
                // pressing LSFT
                // TODO: There is probably a better way of doing this
                if ((get_mods() & MOD_BIT(KC_LSFT)) == MOD_BIT(KC_LSFT)) {
                    // On LSHIFT down we set this to false again to avoid
                    // getting space "stuck" and keep sending down events.
                    shift_space_pressed = true;
                    register_code(KC_SPC);
                    return false;
                } else {
                    return true;
                }
            } else { // key released
                if ((get_mods() & MOD_BIT(KC_LSFT)) == MOD_BIT(KC_LSFT)) {
                    if (shift_space_pressed) {
                        unregister_code(KC_SPC);
                        return true;
                    }
                } else {
                    return true;
                }
            }
            return true;

        case KC_LSHIFT:
            if (!record->event.pressed) {
                if (shift_space_pressed) {
                    unregister_code(KC_SPC);
                    shift_space_pressed = false;
                }
            }
            return true;
        case BASE_LAYER_CHANGE:
            if (record->event.pressed) {
                if (get_highest_layer(default_layer_state) == _DEFAULT_LAYER) {
                    set_single_persistent_default_layer(_NON_FUNC_LAYER);
                }
                else {
                    set_single_persistent_default_layer(_DEFAULT_LAYER);
                }
                return false;
            }
        default:
            return true;
    }
    return true;
}

void matrix_scan_user(void) {
#   ifdef RGBLIGHT_ENABLE
    // Set GRAVE key to red when _NON_FUNC_LAYER is active
    if (get_highest_layer(default_layer_state) == _NON_FUNC_LAYER) {
        rgblight_sethsv_noeeprom(HSV_RED);
        rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    }
#   endif
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(_FUNC_LAYER, KC_SPC):
            // When pressing shift and space set tapping term to 0 in order to
            // be able to press space faster consecutively
            if ((get_mods() & MOD_BIT(KC_LSFT)) == MOD_BIT(KC_LSFT)) {
                return 0;
            } else {
                return TAPPING_TERM;
            }
        default:
            return TAPPING_TERM;
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
#   ifdef RGBLIGHT_ENABLE
    switch (get_highest_layer(state)) {
        case _NON_FUNC_LAYER:
            rgblight_sethsv_noeeprom(HSV_RED);
            rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
            break;
        case _FUNC_LAYER:
            rgblight_sethsv_noeeprom(HSV_PURPLE);
            rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
            break;
        case _SETTINGS_LAYER:
            rgblight_sethsv_noeeprom(HSV_WHITE);
            rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
            break;
        case _DEFAULT_LAYER:
            rgblight_sethsv_noeeprom(HSV_MAGENTA);
            rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_MOOD);
            break;
    }
#   endif
    return state;
}

