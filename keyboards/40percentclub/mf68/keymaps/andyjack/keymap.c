/*
Copyright 2020 Andy Jack

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

enum layers {
    _QWERTY,
    _L1,
    _L2
};

#define CTL_ESC LCTL_T(KC_ESC)

/* these key combos are mapped to shell commands in my .keylaunchrc */
#define MUT_IN LALT(KC_F10)
#define MUT_OUT LALT(KC_F11)
#define MUT_MIC LALT(KC_F12)
#define SCN_LCK LCTL(KC_SCRL)

extern keymap_config_t keymap_config;

enum custom_keycodes {
    AJ_FN = SAFE_RANGE,
    AJ_RCTL,
    AJ_MSWP,
    AJ_MLCK,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_68_ansi(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_INS,  KC_PGUP,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_DEL,  KC_PGDN,
    CTL_ESC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                   KC_RSFT,          KC_UP,
    KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, AJ_FN,   AJ_RCTL,          KC_LEFT, KC_DOWN, KC_RGHT
  ),
  [_L1] = LAYOUT_68_ansi(
    KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_BSPC,          KC_VOLU, KC_HOME,
    _______, _______, KC_HOME, KC_UP,   KC_END,  _______, _______, MUT_IN , MUT_OUT, MUT_MIC, _______, _______, BL_STEP, _______,          KC_VOLD, KC_END,
    _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, SCN_LCK, _______, _______,          _______,
    _______, _______, _______, _______, KC_BTN3, _______, _______, KC_MUTE, _______, _______, _______,                   _______,          KC_MUTE,
    _______, AJ_MLCK, AJ_MSWP,                            _______,                            _______, _______, _______,          KC_MPRV, KC_MPLY, KC_MNXT
  ),
  [_L2] = LAYOUT_68_ansi(
    KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_BSPC,          KC_VOLU, KC_HOME,
    _______, _______, _______, KC_UP,   _______, _______, _______, KC_7,    KC_8,    KC_9,    _______, _______, _______, _______,          KC_VOLD, KC_END,
    _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, KC_4,    KC_5,    KC_6,    _______, _______,          _______,
    _______, _______, _______, _______, _______, _______, KC_0,    KC_1,    KC_2,    KC_3,    _______,                   _______,          KC_MUTE,
    _______, _______, _______,                            _______,                            _______, _______, _______,          KC_MPRV, KC_MPLY, KC_MNXT
  )
};
// clang-format on

static bool    aj_fn_down   = false;
static bool    aj_rctl_down = false;
static uint8_t keycode_for_aj_rctl;

/* My version of:
  https://www.reddit.com/r/olkb/comments/8eticz/how_to_activate_a_layer_with_a_combination/dxygw0f/
* AJ_FN by itself turns on layer 1
* AJ_RCTL by itself acts as a control key
* pressing FN and RCTL together, in any order, turns on layer 2
*/
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case AJ_FN:
            if (record->event.pressed) {
                if (aj_rctl_down) {
                    layer_on(_L2);
                } else {
                    layer_on(_L1);
                }
                aj_fn_down = true;
            } else {
                layer_off(_L1);
                layer_off(_L2);
                aj_fn_down = false;
            }
            return false;
            break;
        case AJ_RCTL:
            if (record->event.pressed) {
                if (aj_fn_down) {
                    layer_on(_L2);
                } else {
                    register_code(keycode_for_aj_rctl);
                }
                aj_rctl_down = true;
            } else {
                layer_off(_L2);
                unregister_code(keycode_for_aj_rctl);
                aj_rctl_down = false;
            }
            return false;
            break;
        case AJ_MSWP:
        case AJ_MLCK:
            if (record->event.pressed) {
                if (!eeconfig_is_enabled()) {
                    eeconfig_init();
                }
                keymap_config.raw = eeconfig_read_keymap();
                switch (keycode) {
                    case AJ_MSWP:
                        keymap_config.swap_lalt_lgui = !keymap_config.swap_lalt_lgui;
                        keymap_config.swap_ralt_rgui = keymap_config.swap_lalt_lgui;
                        keycode_for_aj_rctl          = keymap_config.swap_lalt_lgui ? KC_RALT : KC_RCTL;
                        break;
                    case AJ_MLCK:
                        keymap_config.no_gui = !keymap_config.no_gui;
                        break;
                }
                eeconfig_update_keymap(keymap_config.raw);
                clear_keyboard();  // clear to prevent stuck keys
            }
            return false;
            break;
    }
    return true;
}

void keyboard_post_init_user(void) {
    if (!eeconfig_is_enabled()) {
        eeconfig_init();
    }
    keymap_config.raw   = eeconfig_read_keymap();
    keycode_for_aj_rctl = keymap_config.swap_lalt_lgui ? KC_RALT : KC_RCTL;
    eeconfig_update_keymap(keymap_config.raw);
    clear_keyboard();  // clear to prevent stuck keys
}
