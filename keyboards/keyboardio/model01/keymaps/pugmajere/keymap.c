/* Copyright 2022 Ryan Anderson <ryan@michonline.com>
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

/* layer constants */
enum {
    DEF = 0,
    FUN,
};

enum custom_keycode {
    MACRO_CTRL_PAGE_UP = SAFE_RANGE,
    KC_MT_LCBRC,
    KC_MT_RCBRC,
    KC_MT_LPAR,
    KC_MT_RPAR,
    MACRO_KVM_1,
    MACRO_KVM_2,
    MACRO_KVM_3,
    MACRO_KVM_4,
    MACRO_KVM_TG,
};

// Work around limitations in mod-tapping
static uint16_t space_cadet_control_timer    = 0;
static bool     space_cadet_key_pressed_flag = false;

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[DEF] = LAYOUT(
  QK_BOOT  , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                      KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , MACRO_CTRL_PAGE_UP,
  KC_GRV , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , RGB_MOD,    MACRO_KVM_TG, KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_EQL ,
  LCTL_T(KC_PGUP), KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_TAB ,    KC_ENT , KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,
  KC_PGDN, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_ESC ,    KC_RALT, KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_MINS,
                                  LCTL_T(KC_LBRC),                                 RCTL_T(KC_RBRC),
                                            KC_BSPC,                                     KC_SPC ,
                                          KC_MT_LCBRC,                              KC_MT_RCBRC,
                                             KC_MT_LPAR,                           KC_MT_RPAR,
                                                   MO(FUN),                         MO(FUN)
  ),
[FUN] = LAYOUT(
  _______, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,                      KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 ,
  KC_TAB , _______, KC_MS_U, KC_WH_U, KC_BTN3, MACRO_KVM_1, RGB_TOG,    KC_MPRV, KC_MNXT, KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, KC_F12 ,
  KC_HOME, KC_MS_L, KC_MS_D, KC_MS_R, KC_BTN1, MACRO_KVM_2, RGB_SPI,    KC_MPLY, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, _______, _______,
  KC_END , KC_PSCR, KC_INS , KC_WH_D, KC_BTN2, MACRO_KVM_4, RGB_SPD,    _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, KC_BSLS, KC_PIPE,
                                         _______,                                 _______,
                                            KC_DEL ,                           KC_ENT ,
                                               _______,                     _______,
                                                  _______,               _______,
                                      _______,                                        _______
  )
};

/* template for new layouts:
LAYOUT(
  _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______,
                                         _______,                                 _______,
                                            _______,                           _______,
                                               _______,                     _______,
                                                  _______,               _______,
                                      _______,                                        _______
  )
*/
// clang-format on

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        space_cadet_key_pressed_flag = true;
    }
    switch (keycode) {
        case MACRO_CTRL_PAGE_UP:
            if (record->event.pressed) {
                // send some data
                SEND_STRING(SS_LCTL(SS_TAP(X_PGUP)));
            } else {
                // when keycode MACRO_CTRL_PAGE_UP is pressed
            }
            break;

            // These next two cases duplicate mod-tap functionality by hand to
            // work around the lack of support for shifted/modded keys as
            // "tap" side of things.
        case KC_MT_LCBRC:
            if (record->event.pressed) {
                space_cadet_control_timer    = timer_read();
                space_cadet_key_pressed_flag = false;
                register_mods(MOD_BIT(KC_LGUI));
            } else {
                unregister_mods(MOD_BIT(KC_LGUI));
                if (timer_elapsed(space_cadet_control_timer) < TAPPING_TERM && !space_cadet_key_pressed_flag) {
                    tap_code16(LSFT(KC_LBRC));
                }
            }
            return false;
            break;
        case KC_MT_RCBRC:
            if (record->event.pressed) {
                space_cadet_control_timer    = timer_read();
                space_cadet_key_pressed_flag = false;
                register_mods(MOD_BIT(KC_LALT));
            } else {
                unregister_mods(MOD_BIT(KC_LALT));
                if (timer_elapsed(space_cadet_control_timer) < TAPPING_TERM && !space_cadet_key_pressed_flag) {
                    tap_code16(LSFT(KC_RBRC));
                }
            }
            return false;
            break;
        case KC_MT_LPAR:
            if (record->event.pressed) {
                space_cadet_control_timer    = timer_read();
                space_cadet_key_pressed_flag = false;
                register_mods(MOD_BIT(KC_LSFT));
            } else {
                unregister_mods(MOD_BIT(KC_LSFT));
                if (timer_elapsed(space_cadet_control_timer) < TAPPING_TERM && !space_cadet_key_pressed_flag) {
                    tap_code16(LSFT(KC_9));
                }
            }
            return false;
            break;
        case KC_MT_RPAR:
            if (record->event.pressed) {
                space_cadet_control_timer    = timer_read();
                space_cadet_key_pressed_flag = false;
                register_mods(MOD_BIT(KC_RSFT));
            } else {
                unregister_mods(MOD_BIT(KC_RSFT));
                if (timer_elapsed(space_cadet_control_timer) < TAPPING_TERM && !space_cadet_key_pressed_flag) {
                    tap_code16(LSFT(KC_0));
                }
            }
            return false;
            break;
        case MACRO_KVM_1:
            if (record->event.pressed) {
                tap_code(KC_SCRL);
                tap_code(KC_SCRL);
                tap_code(KC_1);
            }
            break;
        case MACRO_KVM_2:
            if (record->event.pressed) {
                tap_code(KC_SCRL);
                tap_code(KC_SCRL);
                tap_code(KC_2);
            }
            break;
        case MACRO_KVM_3:
            if (record->event.pressed) {
                tap_code(KC_SCRL);
                tap_code(KC_SCRL);
                tap_code(KC_3);
            }
            break;
        case MACRO_KVM_4:
            if (record->event.pressed) {
                tap_code(KC_SCRL);
                tap_code(KC_SCRL);
                tap_code(KC_4);
            }
            break;
        case MACRO_KVM_TG:
            if (record->event.pressed) {
                register_code(KC_LSFT);
                tap_code(KC_NUM);
                tap_code(KC_NUM);
                unregister_code(KC_LSFT);
                tap_code(KC_LCTL);
            }
            break;
    }
    return true;
};

/* vim: set ts=2 sw=2 et: */
