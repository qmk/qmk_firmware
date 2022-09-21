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

// clang-format off
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
    //
    // This keyboard defaults to 6KRO instead of NKRO for compatibility reasons (some KVMs and BIOSes are incompatible with NKRO).
    // Since this is, among other things, a "gaming" keyboard, a key combination to enable NKRO on the fly is provided for convenience.
    // Press Fn+N to toggle between 6KRO and NKRO. This setting is persisted to the EEPROM and thus persists between restarts.
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,          KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_HOME,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_END,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_PGUP,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_PGDN,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(1),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [1] = LAYOUT(
        _______, KC_MYCM, KC_WHOM, KC_CALC, KC_MSEL, KC_MPRV, KC_MNXT, KC_MPLY, KC_MSTP, KC_MUTE, KC_VOLD, KC_VOLU, _______, RESET,          _______,
        _______, RGB_TOG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, RGB_VAI, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            _______,
        _______, _______, RGB_VAD, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, RGB_HUI, _______, _______, _______, NK_TOGG, _______, _______, _______, _______,          _______, RGB_MOD, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, RGB_SPD, RGB_RMOD, RGB_SPI
    ),

    [2] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),

    [3] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),

};
// clang-format on

/* encoder; start */
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] = { ENCODER_CCW_CW(KC_VOLU, KC_VOLD) },
    [1] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [2] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [3] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) }
};
#endif
/* encoder; end */

void side_lights_off(void){
    //right
    rgb_matrix_set_color(68, 0, 0, 0); //side led 01
    rgb_matrix_set_color(71, 0, 0, 0); //side led 02
    rgb_matrix_set_color(74, 0, 0, 0); //side led 03
    rgb_matrix_set_color(77, 0, 0, 0); //side led 04
    rgb_matrix_set_color(81, 0, 0, 0); //side led 05
    rgb_matrix_set_color(84, 0, 0, 0); //side led 06
    rgb_matrix_set_color(88, 0, 0, 0); //side led 07
    rgb_matrix_set_color(92, 0, 0, 0); //side led 08
    //left
    rgb_matrix_set_color(67, 0, 0, 0); //side led 12
    rgb_matrix_set_color(70, 0, 0, 0); //side led 13
    rgb_matrix_set_color(73, 0, 0, 0); //side led 14
    rgb_matrix_set_color(76, 0, 0, 0); //side led 15
    rgb_matrix_set_color(80, 0, 0, 0); //side led 16
    rgb_matrix_set_color(83, 0, 0, 0); //side led 17
    rgb_matrix_set_color(87, 0, 0, 0); //side led 18
    rgb_matrix_set_color(91, 0, 0, 0); //side led 19;
}
void side_lights_on(int r, int g, int b){
    //right
    rgb_matrix_set_color(68, r, g, b); //side led 01
    rgb_matrix_set_color(71, r, g, b); //side led 02
    rgb_matrix_set_color(74, r, g, b); //side led 03
    rgb_matrix_set_color(77, r, g, b); //side led 04
    rgb_matrix_set_color(81, r, g, b); //side led 05
    rgb_matrix_set_color(84, r, g, b); //side led 06
    rgb_matrix_set_color(88, r, g, b); //side led 07
    rgb_matrix_set_color(92, r, g, b); //side led 08
    //left
    rgb_matrix_set_color(67, r, g, b); //side led 12
    rgb_matrix_set_color(70, r, g, b); //side led 13
    rgb_matrix_set_color(73, r, g, b); //side led 14
    rgb_matrix_set_color(76, r, g, b); //side led 15
    rgb_matrix_set_color(80, r, g, b); //side led 16
    rgb_matrix_set_color(83, r, g, b); //side led 17
    rgb_matrix_set_color(87, r, g, b); //side led 18
    rgb_matrix_set_color(91, r, g, b); //side led 19;
}

int counter = 0;
const int max = 60;
const int LED_R = 255;
const int LED_G = 255;
const int LED_B = 255;

void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    counter = counter + 1;
    if (counter > (max * 2)){
        counter = 0;
    }
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(3, RGB_WHITE);
        if (counter > max){
            
            side_lights_on(LED_R, LED_G, LED_B);
        }
        else{
            side_lights_off();
        }
    }
    else{
        side_lights_off();
    }
}