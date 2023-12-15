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
    CW_TOGG, __COLEMAK_MOD_DH_L1________________________,                                     __COLEMAK_MOD_DH_R1_W_QUOT_________________, KC_BSLS,
    HY_ESC,  __COLEMAK_MOD_DH_L2_W_GACS_________________,                                     __COLEMAK_MOD_DH_R2_W_SCAG_________________, KC_QUOT,
    TD_LAYR, __COLEMAK_MOD_DH_L3________________________, KC_LSFT, QK_LEAD, KC_DEL,  KC_TAB,  __COLEMAK_MOD_DH_R3________________________, SC_SENT,
                               KC_MUTE, KC_DEL,  HY_ESC,  LOW_BSP, RAI_ENT, KC_BSPC, NAV_SPC, HY_ESC,  RAI_TAB, KC_RALT
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
 * Lower Layer: Numpad and some symbols
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  ~   |  `   |  (   |  )   | xxxx |                              | / ?  | 7 &  | 8 *  | 9 (  | - _  |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        | LGUI | LALT |LCTL [|LSFT ]| _ -  |                              | *    | 4 $  | 5 %  | 6 ^  | , <  | +      |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        | xxxx | xxxx |  {   |  }   | LSFT |      |      |  |      |      | 0 )  | 1 !  | 2 @  | 3 #  | = +  |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      | Lower|      |      |  |      | Nav  | 0    | .    |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_LOWER] = LAYOUT_wrapper(
      _______, __SYMBOLS_L1_______________________________,                                     __NUMPAD_R1________________________________, _______,
      _______, __SYMBOLS_L2_______________________________,                                     __NUMPAD_R2________________________________, KC_COMM,
      _______, __SYMBOLS_L3_______________________________, _______, _______, _______, _______, __NUMPAD_R3________________________________, KC_DOT,
                                 __BLANK____________________________________, _______, KC_SPC,  KC_0,    KC_DOT,  _______
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
      _______, XXXXXXX, XXXXXXX, KC_GRV,  KC_GRV,  KC_BSLS,                                     __SYMBOLS_R1_______________________________, _______,
      _______, XXXXXXX, XXXXXXX, KC_UNDS, KC_MINS, KC_TILD,                                     __SYMBOLS_R2_______________________________, _______,
      _______, XXXXXXX, XXXXXXX, KC_PLUS, KC_EQL,  KC_GRV,  _______, _______, _______, _______, __SYMBOLS_R3_______________________________, _______,
                                 __BLANK____________________________________, __BLANK____________________________________
    ),
/*
 * Navigation Layer (w/ symbols on left)
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
      _______, __VIM_L1___________________________________,                                     __NAV_R1___________________________________, KC_SCRL,
      _______, __BLANK_W_GACS_____________________________,                                     __NAV_R2___________________________________, KC_CAPS,
      _______, __BLANK____________________________________, _______, _______, _______, _______, __NAV_R3___________________________________, _______,
                                 __BLANK____________________________________, __BLANK____________________________________
    ),
    /*
     * Adjust Layer: Function keys, RGB
     *
     * ,-------------------------------------------.                              ,-------------------------------------------.
     * |  Boot  | Boot |Debug |      |      |      |                              |      | F1   |  F2  | F3   | F4   |        |
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
        QK_BOOT, __ADJUST_L1________________________________,                                     __MEDIA_R1_________________________________, _______,
        _______, __ADJUST_L2________________________________,                                     __MEDIA_R2_________________________________, _______,
        _______, __ADJUST_L3________________________________, _______, _______, _______, _______, __MEDIA_R3_________________________________, _______,
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
}

bool process_record_keymap(uint16_t keycode, keyrecord_t* record) {
    // Regular user keycode case statement
    switch (keycode) {
        default:
            return true;
    }
    return true;
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
#    ifdef MOUSEKEY_ENABLE
        if (clockwise) {
            tap_code(KC_WH_D);
        } else {
            tap_code(KC_WH_U);
        }
#    else
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
#    endif
    }
    return true;
}
#endif

#ifdef RGBLIGHT_ENABLE
void set_layer_hsv(layer_state_t state, HSV* layer_color) {
    uint16_t h = layer_color->h, s = layer_color->s, v = layer_color->v;
    switch (get_highest_layer(state)) {
        case _RAISE:
            h += 3 * RGBLIGHT_HUE_STEP;
            break;
        case _LOWER:
            h += -3 * RGBLIGHT_HUE_STEP;
            break;
        case _NAV:
            h += 2 * RGBLIGHT_HUE_STEP;
            break;
        case _MOUSE:
            h += -8 * RGBLIGHT_HUE_STEP;
            break;
        default:
            break;
    }
    layer_color->h = h % 255;
    layer_color->s = s;
    layer_color->v = v % 255;
    return;
}
#endif
