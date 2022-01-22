/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>

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



//      ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	     Prt           Rotary(Mute)
//      ~        1        2        3        4        5        6        7        8        9        0         -       (=)	     BackSpc           Del
//      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        \                 PgUp
//      Caps     A        S        D        F        G        H        J        K        L        ;        "                 Enter             PgDn
//      Sh_L              Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       End
//      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right


    // The FN key by default maps to a momentary toggle to layer 1 to provide access to the RESET key (to put the board into bootloader mode). Without
    // this mapping, you have to open the case to hit the button on the bottom of the PCB (near the USB cable attachment) while plugging in the USB
    // cable to get the board into bootloader mode - definitely not fun when you're working on your QMK builds. Remove this and put it back to KC_RGUI
    // if that's your preference.
    //
    // To put the keyboard in bootloader mode, use FN+backslash. If you accidentally put it into bootloader, you can just unplug the USB cable and
    // it'll be back to normal when you plug it back in.
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,           KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_HOME,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_END,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_PGUP,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_PGDN,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(1),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RIGHT
    ),

    [1] = LAYOUT(
        KC_WFAV, KC_MYCM, KC_WHOM, KC_MAIL, KC_MSEL, KC_WBAK, KC_WFWD, KC_MPLY, KC_MSTP, KC_MPRV, KC_MNXT, KC_FIND, KC_CALC, _______,          KC_WREF,
        BL_TOGG, KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_F21,  KC_F22,  KC_F23,  KC_F24,  _______,          KC_INS,
        RGB_TOG, PB_1,    PB_2,    PB_3,    PB_4,    PB_5,    PB_6,    PB_7,    PB_8,    PB_9,    PB_10,   PB_11,   PB_12,   RESET,            KC_PSCR,
        GUI_ON,  PB_13,   PB_14,   PB_15,   PB_16,   PB_18,   PB_19,   PB_20,   PB_21,   PB_22,   PB_23,   PB_24,            _______,          KC_SCRL,
        GUI_OFF,          PB_25,   PB_26,   PB_27,   PB_28,   PB_29,   PB_30,   PB_31,   PB_32,   DM_REC1, DM_RSTP,          DM_PLY1, _______, KC_PAUS,
        KC_WAKE, OSL(2),  KC_LOCK,                            _______,                            KC_UNDO,  KC_TRNS, KC_AGIN, _______, _______, _______
    ),
    [2] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_HUI,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_SAI,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, RGB_VAI, _______,
        _______, _______, _______,                            _______,                            _______, KC_TRNS, _______, NK_TOGG, RGB_SPI, RGB_MOD
    ),
};
bool encoder_update_user(uint8_t index, bool clockwise) {

  if (index == 0) {
    switch(biton32(layer_state)){
        case 1:
            if (clockwise){
                tap_code16(KC_MS_WH_UP);
            } else{
                tap_code16(KC_MS_WH_DOWN);
            }
            break;
        default:
            if (clockwise) {
                tap_code16(KC_VOLU);
            } else {
                tap_code16(KC_VOLD);
            }
            break;
        }
    }
    return true;
}
void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {

if (IS_HOST_LED_ON(USB_LED_CAPS_LOCK)) {
        RGB_MATRIX_INDICATOR_SET_COLOR(3, 255, 255, 255); //capslock key
    }
    if (IS_HOST_LED_ON(USB_LED_SCROLL_LOCK)) {
        RGB_MATRIX_INDICATOR_SET_COLOR(67, 0, 0, 255); //side led 01
        RGB_MATRIX_INDICATOR_SET_COLOR(70, 0, 0, 255); //side led 02
        RGB_MATRIX_INDICATOR_SET_COLOR(73, 0, 0, 255); //side led 03
        RGB_MATRIX_INDICATOR_SET_COLOR(83, 255, 0, 255); //side led 06
	    RGB_MATRIX_INDICATOR_SET_COLOR(87, 255, 0, 255); //side led 07
        RGB_MATRIX_INDICATOR_SET_COLOR(91, 255, 0, 255); //side led 08
    }
}
