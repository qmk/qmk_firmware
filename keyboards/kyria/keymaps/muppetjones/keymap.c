/* Copyright 2020 Stephen J. Bush
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
#include "muppetjones.h"
#include "rgblight.h"

#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)

/* Layers from muppetjones.h
    _CLMK_DH = 0,
    _MOUSE,
    _LOWER,
    _RAISE,
    _NAV,
    _ADJUST,
 */

/*
 * Custom Keys
 */

#ifdef ENCODER_ENABLE
bool encoder_update_standard(uint8_t index, bool clockwise);
#endif

#ifdef RGBLIGHT_ENABLE
static rgblight_config_t home_rgb;

void set_rgb_home(void);
void set_rgb_by_layer(layer_state_t);
#endif

/*
 * LAYERS
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off
/*
 * Base Layer: Colemak DH
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |CAPSWORD|   Q  |   W  |   F  |   P  |   B  |                              |   J  |   L  |   U  |   Y  | ;  : |  | \   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |ESC/HYPR|   A  |   R  |  S   |   T  |   G  |                              |   M  |   N  |   E  |   I  |   O  |  ' "   |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   D  |   V  |LShift|Leader|  | Del  | Tab  |   K  |   H  | ,  < | . >  | /  ? | Sft/Ent|
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        | MUTE | Del  | Enter| Space| Enter|  | Bspc | Space| Hyper| Tab  | AltGr|
 *                        |      |      | Alt  | Lower| Raise|  |      | Nav  | Esc  | Raise|      |
 *                        `----------------------------------'  `----------------------------------'
 */
[_CLMK_DH] = LAYOUT_wrapper(
    CAPSWRD, __COLEMAK_MOD_DH_L1________________________,                                     __COLEMAK_MOD_DH_R1________________________, KC_BSLS,
    HY_ESC,  __COLEMAK_MOD_DH_L2_W_GACS_________________,                                     __COLEMAK_MOD_DH_R2_W_SCAG_________________, KC_QUOT,
    TD_LAYR, __COLEMAK_MOD_DH_L3________________________, KC_LSFT, KC_LEAD, KC_DEL,  KC_TAB,  __COLEMAK_MOD_DH_R3________________________, KC_SFTENT,
                               KC_MUTE, KC_DEL,  HY_ESC,  LOW_SPC, RAI_ENT, KC_BSPC, NAV_SPC, HY_ESC,  RAI_TAB, KC_RALT
),
[_QWERTY] = LAYOUT_wrapper(
    _______, __QWERTY_L1________________________________,                                     __QWERTY_R1________________________________, _______,
    _______, __QWERTY_L2________________________________,                                     __QWERTY_R2________________________________, _______,
    _______, __QWERTY_L3________________________________, _______, _______, _______, _______, __QWERTY_R3________________________________, _______,
                               __BLANK____________________________________, __BLANK____________________________________
),
[_MOUSE] = LAYOUT_wrapper(
    _______, __BLANK____________________________________,                                     __BLANK____________________________________, _______,
    _______, __BLANK____________________________________,                                     __BLANK____________________________________, _______,
    _______, __BLANK____________________________________, _______, _______, _______, _______, __BLANK____________________________________, _______,
                               KC_BTN1, _______, _______, _______, _______, _______, _______, _______, _______, KC_BTN2
),
/*
 * Lower Layer: Numpad
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              | / ?  | 7 &  | 8 *  | 9 (  | - _  |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        | GUI  | ALT  | CTL  | SFT  |      |                              | *    | 4 $  | 5 %  | 6 ^  | , <  | +      |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      | 0 )  | 1 !  | 2 @  | 3 #  | = +  |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      | Lower|      |      |  |      | Nav  | 0    | .    |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_LOWER] = LAYOUT_wrapper(
      _______, __BLANK____________________________________,                                     __NUMPAD_R1________________________________, _______,
      _______, __BLANK_W_GACS_____________________________,                                     __NUMPAD_R2________________________________, KC_PLUS,
      _______, __BLANK____________________________________, _______, _______, _______, _______, __NUMPAD_R3________________________________, _______,
                                 __BLANK____________________________________, _______, _______, KC_0,    KC_DOT,  _______
    ),
/*
 * Raise Layer: Symbols
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  !   |  @   |  {   |  }   |  |   |                              |      |  &   |  €   |      |      |  \     |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  #   |  $   |  (   |  )   |  `   |                              |   _  |  -   |  /   |  *   |  %   |  ' "   |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  %   |  ^   |  [   |  ]   |  ~   |      |      |  |      |      |   +  |  =   |  ,   |  .   |  / ? | - _    |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      | Lower|      |      |  |      | Nav  | Raise|      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    // [_RAISE] = LAYOUT(
    //   _______, KC_EXLM, KC_AT,   KC_LPRN, KC_RPRN, KC_PIPE,                                     _______, KC_AMPR, _______, _______, _______, KC_BSLS,
    //   _______, KC_HASH, KC_DLR,  KC_LBRC, KC_RBRC, KC_GRV,                                      KC_UNDS, KC_MINS, KC_SLSH, KC_ASTR, KC_PERC, KC_QUOT,
    //   _______, KC_PERC, KC_CIRC, KC_LCBR, KC_RCBR, KC_TILD, _______, _______, _______, _______, KC_PLUS, KC_EQL,  KC_COMM, KC_DOT,  KC_SLSH, KC_MINS,
    //                              _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    // ),
    [_RAISE] = LAYOUT_wrapper(
      _______, _______, _______, KC_GRV,  KC_GRV,  KC_BSLS,                                     _______, KC_LPRN, KC_RPRN, KC_ASTR, _______, _______,
      _______, _______, _______, KC_UNDS, KC_MINS, KC_TILD,                                     KC_UNDS, KC_LBRC, KC_RBRC, KC_PERC, _______, _______,
      _______, _______, _______, _______, KC_EQL,  _______, _______, _______, _______, _______, _______, KC_LCBR, KC_RCBR, _______, _______, _______,
                                 __BLANK____________________________________, __BLANK____________________________________
    ),
/*
 * Navigation Layer
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              | PgUp | Home | Up   | End  |      | ScrlLk |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        | GUI  | ALT  | CTL  | SFT  |      |                              | PgDn | Left | Down | Up   | Right| CapsLk |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      | Lower|      |      |  |      | Nav  | Raise|      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NAV] = LAYOUT_wrapper(
      _______, __BLANK____________________________________,                                     __NAV_R1___________________________________, KC_SLCK,
      _______, __BLANK_W_GACS_____________________________,                                     __NAV_R2___________________________________, KC_CAPS,
      _______, __BLANK____________________________________, _______, _______, _______, _______, __NAV_R3___________________________________, _______,
                                 __BLANK____________________________________, __BLANK____________________________________
    ),
    /*
     * Adjust Layer: Function keys, RGB
     *
     * ,-------------------------------------------.                              ,-------------------------------------------.
     * | RESET  |      |      |      |      |      |                              |      | F1   |  F2  | F3   | F4   |        |
     * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
     * |        | TOG  | SAI  | HUI  | VAI  | MOD  |                              |      | F5   |  F6  | F7   | F8   |        |
     * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
     * |        |      | SAD  | HUD  | VAD  | RMOD |      |      |  |      |      |      | F9   |  F10 | F11  | F12  |        |
     * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
     *                        |      |      |      |      |      |  |      |      |      |      |      |
     *                        |      |      |      |      |      |  |      |      |      |      |      |
     *                        `----------------------------------'  `----------------------------------'
     */
    [_ADJUST] = LAYOUT_wrapper(
        RESET,   _______, _______, _______, _______, _______,                                     _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______,
        _______, RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI, RGB_MOD,                                     _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   _______,
        _______, _______, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD,_______, _______, _______, _______, _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,
                                   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    )
    // /*
    //  * Layer template
    //  *
    //  * ,-------------------------------------------.                              ,-------------------------------------------.
    //  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
    //  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
    //  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
    //  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
    //  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
    //  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
    //  *                        |      |      |      |      |      |  |      |      |      |      |      |
    //  *                        |      |      |      |      |      |  |      |      |      |      |      |
    //  *                        `----------------------------------'  `----------------------------------'
    //  */
    //     [_LAYERINDEX] = LAYOUT(
    //       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
    //       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
    //       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    //                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    //     ),
    // clang-format on
};

/*
 *
 */

void keyboard_post_init_user(void) {
    // Call the keymap level matrix init.

#ifdef RGBLIGHT_ENABLE
    set_rgb_home();
#endif
}

layer_state_t layer_state_set_user(layer_state_t state) {
#ifdef RGBLIGHT_ENABLE
    set_rgb_by_layer(state);
#endif
    return state;
    // return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    // Regular user keycode case statement
    switch (keycode) {
        default:
            return true;
    }
    return true;
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Regular user keycode case statement
    switch (keycode) {
#ifdef RGBLIGHT_ENABLE
        case RGB_HUD:
        case RGB_HUI:
        case RGB_SAD:
        case RGB_SAI:
        case RGB_VAD:
        case RGB_VAI:
            set_rgb_home();
            break;
#endif
        default:
            break;
    }
}

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
#    ifdef POINTING_DEVICE_ENABLE
    if (IS_LAYER_ON(_MOUSE))
        return encoder_update_mouse(index, clockwise);
    else
#    endif
        return encoder_update_standard(index, clockwise);
}

bool encoder_update_standard(uint8_t index, bool clockwise) {
    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        // Page up/Page down
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    return true;
}
#endif

#ifdef RGBLIGHT_ENABLE

void set_rgb_home(void) {
    home_rgb.raw = eeconfig_read_rgblight();
    // these get the current -- not eeprom
    // home_rgb.hue = rgblight_get_hue();
    // home_rgb.sat = rgblight_get_sat();
    // home_rgb.val = rgblight_get_val();
}

void set_rgb_by_layer(layer_state_t state) {
    if (!rgblight_is_enabled()) {
        return;  // lighting not enabled
    }

    uint8_t offset = 0;
    switch (get_highest_layer(state)) {
        case _RAISE:
            offset = 2 * RGBLIGHT_HUE_STEP;
            break;
        case _LOWER:
            offset = -2 * RGBLIGHT_HUE_STEP;
            break;
        case _NAV:
            offset = 1 * RGBLIGHT_HUE_STEP;
            break;
        case _MOUSE:
            offset = -10 * RGBLIGHT_HUE_STEP;
            break;
        // case _ADJUST:  // layer color not recommended on layer w/ rgb keys
        //     offset = -96;
        //     break;
        default:  //  for any other layers, or the default layer
            break;
    }
    rgblight_sethsv_noeeprom((home_rgb.hue + offset) % 255, home_rgb.sat, home_rgb.val);
}
#endif
