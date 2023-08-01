/*
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org/>
*/

#include QMK_KEYBOARD_H

enum layers {
    _DVORAK,
    _QWERTY,
    _CODE,
};

// work in progress simulation of kakoune behavior
bool kak_mode = false;

enum tapdances {
    _LCTLGUI,
};

enum keycodes {
    KC_KAK = SAFE_RANGE,
};

tap_dance_action_t tap_dance_actions[] = {
    [_LCTLGUI] = ACTION_TAP_DANCE_DOUBLE(KC_LCTL, KC_LGUI),
};

// Layers
#define DVORAK DF(_DVORAK)
#define QWERTY DF(_QWERTY)
#define CODE MO(_CODE)

// Modifiers
#define COPY LCTL(KC_C)
#define PASTE LCTL(KC_V)

// Tapdances
#define LCTLGUI TD(_LCTLGUI)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_DVORAK] = LAYOUT(
//  ┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_PSCR, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    QWERTY,
//  ├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,                               KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH,
//  ├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_ESC,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,                               KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS,
//  ├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LGUI, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_PGUP,          KC_PGDN, KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_ENT,
//  └────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    LCTLGUI, KC_LALT, KC_LSFT,                   KC_BSPC, KC_SPC,  CODE
//                                 └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_QWERTY] = LAYOUT(
//  ┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, DVORAK,
//  ├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
//  ├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
//  ├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    _______,          _______, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, _______,
//  └────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, _______
//                                 └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),


  [_CODE] = LAYOUT(
//  ┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
//  ├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_LABK, KC_LCBR, KC_LBRC, KC_LPRN, KC_AMPR,                            KC_AT,   KC_MINS, KC_SLSH, KC_DLR,  KC_EXLM, KC_BSLS,
//  ├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_GRAVE,KC_RABK, KC_RCBR, KC_RBRC, KC_RPRN, KC_PIPE,                            KC_CIRC, KC_PLUS, KC_ASTR, KC_PERC, KC_UP,   KC_EQL,
//  ├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     QK_BOOT, _______, _______, _______, _______, _______, KC_HOME,          KC_END,  KC_KAK,  COPY,    PASTE,   KC_LEFT, KC_DOWN, KC_RIGHT,
//  └────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   KC_DEL,  _______, _______
//                                 └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_KAK: {
            if (record->event.pressed) {
                kak_mode = !kak_mode;
                return false;
            }
        } break;
    }

    if (kak_mode) {
        switch (keycode) {
            case KC_ESC: {
                if (record->event.pressed) {
                    kak_mode = false;
                    return false;
                }
            } break;
            case KC_I: {
                if (record->event.pressed) {
                    kak_mode = false;
                    tap_code(KC_LEFT);
                    return false;
                }
            } break;
            case KC_A: {
                if (record->event.pressed) {
                    kak_mode = false;
                    tap_code(KC_RIGHT);
                    return false;
                }
            } break;
            case KC_W: {
                if (record->event.pressed) {
                    uint8_t mods = get_mods();
                    if ((mods & MOD_MASK_SHIFT) == 0)
                        tap_code(KC_RIGHT);
                    set_mods(MOD_MASK_CS);
                    tap_code(KC_RIGHT);
                    set_mods(mods);
                    return false;
                }
            } break;
            case KC_B: {
                if (record->event.pressed) {
                    uint8_t mods = get_mods();
                    if ((mods & MOD_MASK_SHIFT) == 0)
                        tap_code(KC_LEFT);
                    set_mods(MOD_MASK_CS);
                    tap_code(KC_LEFT);
                    set_mods(mods);
                    return false;
                }
            } break;
            case KC_H: {
                if (record->event.pressed) {
                    if ((get_mods() & MOD_MASK_ALT) == 0)
                        tap_code(KC_LEFT);
                    else
                        tap_code(KC_HOME);
                    return false;
                }
            } break;
            case KC_J: {
                if (record->event.pressed) {
                    tap_code(KC_DOWN);
                    return false;
                }
            } break;
            case KC_K: {
                if (record->event.pressed) {
                    tap_code(KC_UP);
                    return false;
                }
            } break;
            case KC_L: {
                if (record->event.pressed) {
                    if ((get_mods() & MOD_MASK_ALT) == 0)
                        tap_code(KC_RIGHT);
                    else
                        tap_code(KC_END);
                    return false;
                }
            } break;
            case KC_X: {
                if (record->event.pressed) {
                    uint8_t mods = get_mods();
                    tap_code(KC_HOME);
                    set_mods(MOD_MASK_SHIFT);
                    tap_code(KC_END);
                    set_mods(mods);
                    return false;
                }
            } break;
            case KC_Y: {
                if (record->event.pressed) {
                    tap_code16(KC_COPY);
                    return false;
                }
            } break;
            case KC_D: {
                if (record->event.pressed) {
                    tap_code16(KC_COPY);
                    tap_code(KC_BSPC);
                    return false;
                }
            } break;
            case KC_C: {
                if (record->event.pressed) {
                    tap_code(KC_BSPC);
                    kak_mode = false;
                    return false;
                }
            } break;
            case KC_P: {
                if (record->event.pressed) {
                    if ((get_mods() & MOD_MASK_SHIFT) == 0)
                        tap_code(KC_RIGHT);
                    else
                        tap_code(KC_LEFT);
                    tap_code16(KC_PSTE);
                    return false;
                }
            } break;
            case KC_R: {
                if (record->event.pressed) {
                    tap_code16(KC_PSTE);
                    return false;
                }
            } break;
            case KC_U: {
                if (record->event.pressed) {
                    if ((get_mods() & MOD_MASK_SHIFT) == 0)
                        tap_code16(LCTL(KC_Z));
                    else
                        tap_code16(LCTL(KC_Y));
                    return false;
                }
            } break;
        }
    }
    return true;
}
