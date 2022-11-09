/* Copyright 2021 Cedrik Lussier @cedrikl
.* Directly inspired from the work of jonavin https://github.com/qmk/qmk_firmware/tree/master/keyboards/gmmk/pro/ansi/keymaps/jonavin
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
#include "rgb_matrix_map.h"
#include "cedrikl.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//      ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	     Prt           Rotary(Mute)
//      ~        1        2        3        4        5        6        7        8        9        0         -       (=)	     BackSpc           Del
//      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        \                 PgUp
//      Caps     A        S        D        F        G        H        J        K        L        ;        "                 Enter             PgDn
//      Sh_L              Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       End
//      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right


    // The FN key by default maps to a momentary toggle to layer 1 to provide access to the QK_BOOT key (to put the board into bootloader mode). Without
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
    [0] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,           KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_HOME,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGUP,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_PGDN,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(1),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [1] = LAYOUT(
        EE_CLR,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  QK_BOOT,          KC_MUTE,
        KC_NUM,  KC_P1,   KC_P2,   KC_P3,   KC_P4,   KC_P5,   KC_P6,   KC_P7,   KC_P8,   KC_P9,   KC_P0,   KC_PMNS, KC_PPLS, KC_BSPC,          KC_PSCR,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_PSLS, KC_PAST, KC_BSLS,          KC_PGUP,
        KC_CAPS, RGB_VAD, RGB_TOG, RGB_VAI, KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_PENT,          KC_PGDN,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_PDOT, KC_SLSH,          KC_RSFT, KC_UP,   KC_INS,
        KC_LCTL, KC_RGUI, KC_LALT,                            KC_SPC,                             KC_RALT, KC_NO,   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    )
};
// clang-format on

#ifdef ENCODER_ENABLE
    bool encoder_update_user(uint8_t index, bool clockwise) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
        //return true; //set to return false to counteract enabled encoder in pro.c
        return false;
    }
#endif // ENCODER_ENABLE


#ifdef RGB_MATRIX_ENABLE
//void set_layer_rgb(uint8_t led_min, uint8_t led_max, int layer) {
//    const ledmap *l = &(ledmaps[layer]);
//
//
//
//    for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
//        HSV hsv = {
//            .h = (*l)[i][0],
//            .s = (*l)[i][1],
//            .v = val,
//        };
//
//        if (hsv.h || hsv.s) {
//            RGB rgb = hsv_to_rgb(hsv);
//            RGB_MATRIX_INDICATOR_SET_COLOR(i, rgb.r, rgb.g, rgb.b);
//        }
//    }
//}

    // These shorthands are used below to set led colors on each matrix cycle
    void loop_colorset(const uint8_t *indices, int array_size, const HSV target_color) {
        HSV work_color = target_color;
        work_color.v = rgb_matrix_get_val();

        RGB final_color = hsv_to_rgb(work_color);

        for (int i = 0; i < array_size; i++) {
            rgb_matrix_set_color(indices[i], final_color.r, final_color.g, final_color.b); // Set color A here
        }
    }

    // Capslock, Scroll lock and Numlock  indicator on Left side lights.
    bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
        loop_colorset(LED_REGION_A,      ARRAY_SIZE(LED_REGION_A),
                                 hsv_cl_blue);
        loop_colorset(LED_REGION_B,      ARRAY_SIZE(LED_REGION_B),
                                 hsv_cl_purple);
        loop_colorset(LED_REGION_L_SIDE, ARRAY_SIZE(LED_REGION_L_SIDE),
                      hsv_cl_purple);
        loop_colorset(LED_REGION_R_SIDE, ARRAY_SIZE(LED_REGION_R_SIDE),
                      hsv_cl_purple);

        switch(get_highest_layer(layer_state)){  // special handling per layer
            case 1:  //layer 1
                //rgb_matrix_set_color_all(RGB_AZURE);
                loop_colorset(LED_REGION_NUMPAD,
                              ARRAY_SIZE(LED_REGION_NUMPAD), hsv_cl_numpad);
                loop_colorset(LED_REGION_OTHER,  ARRAY_SIZE(LED_REGION_OTHER),
                                 hsv_cl_mods);
            break;
            default: //layer 0
                //
              break;
            break;
        }

        HSV bad_hsv = hsv_cl_bad;
        bad_hsv.v   = rgb_matrix_get_val();
        RGB bad_rgb = hsv_to_rgb(bad_hsv);
        led_t led_state = host_keyboard_led_state();

        if (!led_state.num_lock) {   // on if NUM lock is OFF
            rgb_matrix_set_color(LED_R1,   bad_rgb.r, bad_rgb.g, bad_rgb.b);
            rgb_matrix_set_color(LED_R2,   bad_rgb.r, bad_rgb.g, bad_rgb.b);
            rgb_matrix_set_color(LED_R3,   bad_rgb.r, bad_rgb.g, bad_rgb.b);
            rgb_matrix_set_color(LED_R4,   bad_rgb.r, bad_rgb.g, bad_rgb.b);
            rgb_matrix_set_color(LED_R5,   bad_rgb.r, bad_rgb.g, bad_rgb.b);
            rgb_matrix_set_color(LED_R6,   bad_rgb.r, bad_rgb.g, bad_rgb.b);
            rgb_matrix_set_color(LED_R7,   bad_rgb.r, bad_rgb.g, bad_rgb.b);
            rgb_matrix_set_color(LED_R8,   bad_rgb.r, bad_rgb.g, bad_rgb.b);
        }
        if (led_state.caps_lock) {
            rgb_matrix_set_color(LED_L1,   bad_rgb.r, bad_rgb.g, bad_rgb.b);
            rgb_matrix_set_color(LED_L2,   bad_rgb.r, bad_rgb.g, bad_rgb.b);
            rgb_matrix_set_color(LED_L3,   bad_rgb.r, bad_rgb.g, bad_rgb.b);
            rgb_matrix_set_color(LED_L4,   bad_rgb.r, bad_rgb.g, bad_rgb.b);
            rgb_matrix_set_color(LED_L5,   bad_rgb.r, bad_rgb.g, bad_rgb.b);
            rgb_matrix_set_color(LED_L6,   bad_rgb.r, bad_rgb.g, bad_rgb.b);
            rgb_matrix_set_color(LED_L7,   bad_rgb.r, bad_rgb.g, bad_rgb.b);
            rgb_matrix_set_color(LED_L8,   bad_rgb.r, bad_rgb.g, bad_rgb.b);
            loop_colorset(LED_REGION_CAPS, ARRAY_SIZE(LED_REGION_CAPS),
                          hsv_cl_bad);
        }
    return false;
    }
#endif
