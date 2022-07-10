/* Copyright 2020 shela
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
#include "keymap_jis2us.h"
#include "action_pseudo.h"

// clang-format off
enum keyboard_layers {
    _QWERTY = 0,
    _DVORAK,
    _COLEMAK,
    _PSEUDO,
    _TENKEY,
    _MOUSE,
    _HHKB,
    _SPACE_FN
};

enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    DVORAK,
    COLEMAK,
    PSEUDO,
    TENKEY,
    MOUSE,
    L_INNER,
    R_INNER,
    L_OUTER,
    R_OUTER,
    PSE_FN,
    MACMODE,
    DYNAMIC_MACRO_RANGE
};
// clang-format on

/* Additional custom keycodes */
#define MO_HHKB MO(_HHKB)
#define LT_SPFN LT(_SPACE_FN, KC_SPC)
#define DM_STA1 DYN_REC_START1
#define DM_PLY1 DYN_MACRO_PLAY1

/* User settings structure for the EEPROM */
typedef union {
    uint32_t raw;
    struct {
        uint8_t base_layer : 8;
        bool    mac_mode : 1;
    };
} user_config_t;

user_config_t   user_config;
static uint8_t  base_layer     = _QWERTY;
static bool     mac_mode       = false;
static bool     l_long_pressed = false;
static bool     l_pressed      = false;
static uint16_t l_time         = 0;
static bool     r_long_pressed = false;
static bool     r_pressed      = false;
static uint16_t r_time         = 0;

static uint16_t l_inner = KC_NO;
static uint16_t l_outer = KC_NO;
static uint16_t r_inner = KC_NO;
static uint16_t r_outer = KC_NO;

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Qwerty Layer
     * ,-----------------------------------------------------------------------------------------.
     * | Esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |  `  | BS  |
     * |-----------------------------------------------------------------------------------------|
     * |  Tab   |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |   \    |
     * |-----------------------------------------------------------------------------------------|
     * | LControl |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |   Enter    |
     * |-----------------------------------------------------------------------------------------|
     * |   LShift    |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  | RShift  |HHKB |
     * `-----------------------------------------------------------------------------------------'
     *           |LOutr| LInner |              SpaceFN              | RInner |ROutr|
     *           `-----------------------------------------------------------------'
     */
    [_QWERTY] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_GRV,  KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, MO_HHKB,
        L_OUTER, L_INNER, LT_SPFN, R_INNER, R_OUTER
        ),

    /* Dvorak Layer
     * ,-----------------------------------------------------------------------------------------.
     * | Esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  [  |  ]  |  `  | BS  |
     * |-----------------------------------------------------------------------------------------|
     * |  Tab   |  '  |  ,  |  .  |  P  |  Y  |  F  |  G  |  C  |  R  |  L  |  /  |  =  |   \    |
     * |-----------------------------------------------------------------------------------------|
     * | LControl |  A  |  O  |  E  |  U  |  I  |  D  |  H  |  T  |  N  |  S  |  -  |   Enter    |
     * |-----------------------------------------------------------------------------------------|
     * |   LShift    |  ;  |  Q  |  J  |  K  |  X  |  B  |  M  |  W  |  V  |  Z  | RShift  |HHKB |
     * `-----------------------------------------------------------------------------------------'
     *           |LOutr| LInner |              SpaceFN              | RInner |ROutr|
     *           `-----------------------------------------------------------------'
     */
    [_DVORAK] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_LBRC, KC_RBRC, KC_GRV,  KC_BSPC,
        KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH, KC_EQL,  KC_BSLS,
        KC_LCTL, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS, KC_ENT,
        KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT, MO_HHKB,
        L_OUTER, L_INNER, LT_SPFN, R_INNER, R_OUTER
        ),

    /* Colemak Layer
     * ,-----------------------------------------------------------------------------------------.
     * | Esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |  `  | BS  |
     * |-----------------------------------------------------------------------------------------|
     * |  Tab   |  Q  |  W  |  F  |  P  |  G  |  J  |  L  |  U  |  Y  |  ;  |  [  |  ]  |   \    |
     * |-----------------------------------------------------------------------------------------|
     * | LControl |  A  |  R  |  S  |  T  |  D  |  H  |  N  |  E  |  I  |  O  |  '  |   Enter    |
     * |-----------------------------------------------------------------------------------------|
     * |   LShift    |  Z  |  X  |  C  |  V  |  B  |  K  |  M  |  ,  |  .  |  /  | RShift  |HHKB |
     * `-----------------------------------------------------------------------------------------'
     *           |LOutr| LInner |              SpaceFN              | RInner |ROutr|
     *           `-----------------------------------------------------------------'
     */
    [_COLEMAK] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_GRV,  KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_LBRC, KC_RBRC, KC_BSLS,
        KC_LCTL, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT, KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, MO_HHKB,
        L_OUTER, L_INNER, LT_SPFN, R_INNER, R_OUTER
        ),

    /* Pseudo Layer
     * ,-----------------------------------------------------------------------------------------.
     * | Esc |PseFn|PseFn|PseFn|PseFn|PseFn|PseFn|PseFn|PseFn|PseFn|PseFn|PseFn|PseFn|PseFn| BS  |
     * |-----------------------------------------------------------------------------------------|
     * |  Tab   |PseFn|PseFn|PseFn|PseFn|PseFn|PseFn|PseFn|PseFn|PseFn|PseFn|PseFn|PseFn| PseFn  |
     * |-----------------------------------------------------------------------------------------|
     * | Control  |PseFn|PseFn|PseFn|PseFn|PseFn|PseFn|PseFn|PseFn|PseFn|PseFn|PseFn|   Enter    |
     * |-----------------------------------------------------------------------------------------|
     * |    Shift    |PseFn|PseFn|PseFn|PseFn|PseFn|PseFn|PseFn|PseFn|PseFn|PseFn|  Shift  |HHKB |
     * `-----------------------------------------------------------------------------------------'
     *           |LOutr| LInner |              SpaceFN              | RInner |ROutr|
     *           `-----------------------------------------------------------------'
     */
    [_PSEUDO] = LAYOUT(
        KC_ESC,  PSE_FN,  PSE_FN,  PSE_FN,  PSE_FN,  PSE_FN,  PSE_FN,  PSE_FN,  PSE_FN,  PSE_FN,  PSE_FN,  PSE_FN,  PSE_FN,  PSE_FN,  KC_BSPC,
        KC_TAB,  PSE_FN,  PSE_FN,  PSE_FN,  PSE_FN,  PSE_FN,  PSE_FN,  PSE_FN,  PSE_FN,  PSE_FN,  PSE_FN,  PSE_FN,  PSE_FN,  PSE_FN,
        KC_LCTL, PSE_FN,  PSE_FN,  PSE_FN,  PSE_FN,  PSE_FN,  PSE_FN,  PSE_FN,  PSE_FN,  PSE_FN,  PSE_FN,  PSE_FN,  KC_ENT,
        KC_LSFT, PSE_FN,  PSE_FN,  PSE_FN,  PSE_FN,  PSE_FN,  PSE_FN,  PSE_FN,  PSE_FN,  PSE_FN,  PSE_FN,  KC_RSFT, MO_HHKB,
        L_OUTER, L_INNER, LT_SPFN, R_INNER, R_OUTER
        ),

    /* Tenkey layer
     * ,-----------------------------------------------------------------------------------------.
     * | Esc |     |     |     |     |     |     |     |     |     |  /  |  *  |  -  |     | BS  |
     * |-----------------------------------------------------------------------------------------|
     * |  Tab   |     |     |     |     |     |     |     |     |  7  |  8  |  9  |  +  |        |
     * |-----------------------------------------------------------------------------------------|
     * | LControl |     |     |     |     |     |     |     |     |  4  |  5  |  6  |   Enter    |
     * |-----------------------------------------------------------------------------------------|
     * |   LShift    |     |     |     |     |     |     |     |  1  |  2  |  3  |    +    |HHKB |
     * `-----------------------------------------------------------------------------------------'
     *           |LOutr| LInner |              SpaceFN              |   0    |  .  |
     *           `-----------------------------------------------------------------'
     */
    [_TENKEY] = LAYOUT(
        KC_ESC,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PSLS, KC_PAST, KC_PMNS, XXXXXXX, KC_BSPC,
        KC_TAB,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_P7,   KC_P8,   KC_P9,   KC_PPLS, XXXXXXX,
        KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_P4,   KC_P5,   KC_P6,   KC_PENT,
        KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_P1,   KC_P2,   KC_P3,   KC_PPLS, MO_HHKB,
        L_OUTER, L_INNER, LT_SPFN, KC_P0,   KC_PDOT
        ),

    /* Mouse layer
     * ,-----------------------------------------------------------------------------------------.
     * | Esc | F1  | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9  | F10 | F11 | F12 |     | BS  |
     * |-----------------------------------------------------------------------------------------|
     * |  Tab   |     |     |     |     |     | WhL | WhD | WhU | WhR |     |     |     |        |
     * |-----------------------------------------------------------------------------------------|
     * | LControl |     |     |     |     |     | MsL | MsD | MsU | MsR |     |     |   Enter    |
     * |-----------------------------------------------------------------------------------------|
     * |   LShift    |     |     |     |     |     | Mb1 | Mb2 | Mb3 |     |     | RShift  |HHKB |
     * `-----------------------------------------------------------------------------------------'
     *           |LOutr| LInner |                Mb1                | RInner |ROutr|
     *           `-----------------------------------------------------------------'
     */
    [_MOUSE] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  XXXXXXX, KC_BSPC,
        KC_TAB,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, XXXXXXX, XXXXXXX, KC_ENT,
        KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BTN1, KC_BTN2, KC_BTN3, XXXXXXX, XXXXXXX, KC_RSFT, MO_HHKB,
        L_OUTER, L_INNER, KC_BTN1, R_INNER, R_OUTER
        ),

    /* HHKB Layer
     * ,-----------------------------------------------------------------------------------------.
     * |Power| F1  | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9  | F10 | F11 | F12 | Ins | Del |
     * |-----------------------------------------------------------------------------------------|
     * |  Caps  |Qwert|Dvork|Colmk|Psedo|Tenky|Mouse|     |PScr |SLck |Paus | Up  |     | Clear  |
     * |-----------------------------------------------------------------------------------------|
     * |          |VolD |VolU |Mute |Ejct |     |  *  |  /  |Home |PgUp |Left |Rght |   Enter    |
     * |-----------------------------------------------------------------------------------------|
     * |             |Sta1 |Ply1 |     | Mac |     |  +  |  -  | End |PgDn |Down |         |     |
     * `-----------------------------------------------------------------------------------------'
     *           |     |        |               Space               |        |     |
     *           `-----------------------------------------------------------------'
     */
    [_HHKB] = LAYOUT(
        KC_PWR,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_INS,  KC_DEL,
        KC_CAPS, QWERTY,  DVORAK,  COLEMAK, PSEUDO,  TENKEY,  MOUSE,   XXXXXXX, KC_PSCR, KC_SLCK, KC_PAUS, KC_UP,   XXXXXXX, KC_NLCK,
        _______, KC_VOLD, KC_VOLU, KC_MUTE, KC_EJCT, XXXXXXX, KC_PAST, KC_PSLS, KC_HOME, KC_PGUP, KC_LEFT, KC_RGHT, KC_PENT,
        _______, DM_STA1, DM_PLY1, XXXXXXX, MACMODE, XXXXXXX, KC_PPLS, KC_PMNS, KC_END,  KC_PGDN, KC_DOWN, _______, _______,
        _______, _______, KC_SPC,  _______, _______
        ),

    /* SpaceFN Layer
     * ,-----------------------------------------------------------------------------------------.
     * |     | F1  | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9  | F10 | F11 | F12 |     | Del |
     * |-----------------------------------------------------------------------------------------|
     * |        |Home | Up  | End |     |     |     |Home | End |     |PScr |SLck |Paus |  Ins   |
     * |-----------------------------------------------------------------------------------------|
     * |          |Left |Down |Rght |PgUp |     |Left |Down | Up  |Rght |     |     |            |
     * |-----------------------------------------------------------------------------------------|
     * |             |     |     |PgDn |     | Spc |     |PgDn |PgUp |     |     |         |     |
     * `-----------------------------------------------------------------------------------------'
     *           |     |        |                                   |        |     |
     *           `-----------------------------------------------------------------'
     */
    [_SPACE_FN] = LAYOUT(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  XXXXXXX, KC_DEL,
        _______, KC_HOME, KC_UP,   KC_END,  XXXXXXX, XXXXXXX, XXXXXXX, KC_HOME, KC_END,  XXXXXXX, KC_PSCR, KC_SLCK, KC_PAUS, KC_INS,
        _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGUP, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, XXXXXXX, _______,
        _______, XXXXXXX, XXXXXXX, KC_PGDN, XXXXXXX, KC_SPC,  XXXXXXX, KC_PGDN, KC_PGUP, XXXXXXX, XXXXXXX, _______, XXXXXXX,
        _______, _______, _______, _______, _______
        ),
};
// clang-format on

void set_mac_mode_keys(bool mac_mode) {
    if (mac_mode) {
        l_inner = KC_LCMD;
        l_outer = KC_LOPT;
        r_inner = KC_RCMD;
        r_outer = KC_ROPT;
    } else {
        l_inner = KC_LALT;
        l_outer = KC_LGUI;
        r_inner = KC_RALT;
        r_outer = KC_RGUI;
    }
}

void keyboard_post_init_user(void) {
    user_config.raw = eeconfig_read_user();
    mac_mode        = user_config.mac_mode;
    base_layer      = user_config.base_layer;
    set_mac_mode_keys(mac_mode);
}

/* Set default values for the EEPROM */
void eeconfig_init_user(void) {
    user_config.raw        = 0;
    user_config.base_layer = _QWERTY;
    user_config.mac_mode   = false;
    eeconfig_update_user(user_config.raw);
    base_layer = _QWERTY;
    mac_mode   = false;
    set_mac_mode_keys(mac_mode);
}

void persistent_default_layer_set(uint8_t layer) {
    set_single_persistent_default_layer(layer);
    user_config.base_layer = layer;
    eeconfig_update_user(user_config.raw);
    base_layer = layer;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QWERTY:
            if (record->event.pressed) {
                persistent_default_layer_set(_QWERTY);
            }
            return false;
        case DVORAK:
            if (record->event.pressed) {
                persistent_default_layer_set(_DVORAK);
            }
            return false;
        case COLEMAK:
            if (record->event.pressed) {
                persistent_default_layer_set(_COLEMAK);
            }
            return false;
        case PSEUDO:
            if (record->event.pressed) {
                if (l_pressed && !l_long_pressed) {
                    register_code(l_inner);
                    l_long_pressed = true;
                }
                if (r_pressed && !r_long_pressed) {
                    register_code(r_inner);
                    r_long_pressed = true;
                }
                // set_single_persistent_default_layer(_PSEUDO);
            }
            return false;
        case TENKEY:
            if (record->event.pressed) {
                default_layer_set(1U << _TENKEY);
            }
            return false;
        case MOUSE:
            if (record->event.pressed) {
                default_layer_set(1U << _MOUSE);
            }
            return false;
        case L_INNER:
            if (record->event.pressed) {
                l_pressed = true;
                l_time    = record->event.time;
            } else {
                if (l_pressed) {
                    if (l_long_pressed) {
                        unregister_code(l_inner);
                        l_long_pressed = false;
                    } else {
                        if (TIMER_DIFF_16(record->event.time, l_time) < TAPPING_TERM) {
                            if (mac_mode) {
                                register_code(KC_LANG2);
                                unregister_code(KC_LANG2);
                            } else {
                                register_code(KC_MHEN);
                                unregister_code(KC_MHEN);
                            }
                        } else {
                            register_code(l_inner);
                            unregister_code(l_inner);
                        }
                    }
                    l_pressed = false;
                }
            }
            return false;
        case R_INNER:
            if (record->event.pressed) {
                r_pressed = true;
                r_time    = record->event.time;
            } else {
                if (r_pressed) {
                    if (r_long_pressed) {
                        unregister_code(r_inner);
                        r_long_pressed = false;
                    } else {
                        if (TIMER_DIFF_16(record->event.time, r_time) < TAPPING_TERM) {
                            if (mac_mode) {
                                register_code(KC_LANG1);
                                unregister_code(KC_LANG1);
                            } else {
                                register_code(KC_KANA);
                                unregister_code(KC_KANA);
                            }
                        } else {
                            register_code(r_inner);
                            unregister_code(r_inner);
                        }
                    }
                    r_pressed = false;
                }
            }
            return false;
        case L_OUTER:
            if (record->event.pressed) {
                register_code(l_outer);
            } else {
                unregister_code(l_outer);
            }
            return false;
        case R_OUTER:
            if (record->event.pressed) {
                register_code(r_outer);
            } else {
                unregister_code(r_outer);
            }
            return false;
        case MACMODE:
            if (record->event.pressed) {
                /* Toggle Mac mode value */
                mac_mode             = !mac_mode;
                user_config.mac_mode = mac_mode;
                eeconfig_update_user(user_config.raw);
                set_mac_mode_keys(mac_mode);
            }
            return false;
        case PSE_FN:
            if (record->event.pressed) {
                if (l_pressed && !l_long_pressed) {
                    register_code(l_inner);
                    l_long_pressed = true;
                }
                if (r_pressed && !r_long_pressed) {
                    register_code(r_inner);
                    r_long_pressed = true;
                }
            }
            action_pseudo_process(record, base_layer, keymap_jis2us);
            return false;
        default:
            if (record->event.pressed) {
                if (l_pressed && !l_long_pressed) {
                    register_code(l_inner);
                    l_long_pressed = true;
                }
                if (r_pressed && !r_long_pressed) {
                    register_code(r_inner);
                    r_long_pressed = true;
                }
            }
    }
    return true;
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT_SPFN:
            return SPFN_TAPPING_TERM;
        default:
            return TAPPING_TERM;
    }
}
