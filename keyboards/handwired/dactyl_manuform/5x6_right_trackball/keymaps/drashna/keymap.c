/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
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

#include "drashna.h"

#define TG_DBLO TG(_DIABLO)
#define _MOUSE _MEDIA


// clang-format off
#define LAYOUT_5x6_right_trackball_wrapper(...) LAYOUT_5x6_right_trackball(__VA_ARGS__)
#define LAYOUT_5x6_right_trackball_base( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A  \
  ) \
  LAYOUT_5x6_right_trackball_wrapper( \
     KC_GRV,  ________________NUMBER_LEFT________________,            ________________NUMBER_RIGHT_______________, KC_MINS, \
     KC_ESC,  K01,    K02,      K03,     K04,     K05,                K06,     K07,     K08,     K09,     K0A,     KC_BSLS, \
     LALT_T(KC_TAB), K11, K12,  K13,     K14,     K15,                K16,     K17,     K18,     K19,     K1A,     RALT_T(KC_QUOT), \
     OS_LSFT, CTL_T(K21), K22,  K23,     K24,     K25,                K26,     K27,     K28,     K29, RCTL_T(K2A), OS_RSFT, \
                       OS_LALT, OS_LGUI,                                                TG_GAME, TG_DBLO, \
                                OS_LGUI, KC_GRV,                                        OS_RGUI,  \
                                         KC_SPC,  _______,                     KC_ENT,  \
                                         BK_LWER, MO(_MOUSE),      MO(_MOUSE), DL_RAIS  \
  )
#define LAYOUT_5x6_right_trackball_base_wrapper(...)       LAYOUT_5x6_right_trackball_base(__VA_ARGS__)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_5x6_right_trackball_base_wrapper(
        _________________QWERTY_L1_________________, _________________QWERTY_R1_________________,
        _________________QWERTY_L2_________________, _________________QWERTY_R2_________________,
        _________________QWERTY_L3_________________, _________________QWERTY_R3_________________
    ),

    [_COLEMAK] = LAYOUT_5x6_right_trackball_base_wrapper(
        _________________COLEMAK_L1________________, _________________COLEMAK_R1________________,
        _________________COLEMAK_L2________________, _________________COLEMAK_R2________________,
        _________________COLEMAK_L3________________, _________________COLEMAK_R3________________
    ),

    [_DVORAK] = LAYOUT_5x6_right_trackball_base_wrapper(
        _________________DVORAK_L1_________________, _________________DVORAK_R1_________________,
        _________________DVORAK_L2_________________, _________________DVORAK_R2_________________,
        _________________DVORAK_L3_________________, _________________DVORAK_R3_________________
    ),

    [_WORKMAN] = LAYOUT_5x6_right_trackball_base_wrapper(
        _________________WORKMAN_L1________________, _________________WORKMAN_R1________________,
        _________________WORKMAN_L2________________, _________________WORKMAN_R2________________,
        _________________WORKMAN_L3________________, _________________WORKMAN_R3________________
    ),

    [_NORMAN] = LAYOUT_5x6_right_trackball_base_wrapper(
        _________________NORMAN_L1_________________, _________________NORMAN_L1_________________,
        _________________NORMAN_L2_________________, _________________NORMAN_R2_________________,
        _________________NORMAN_L3_________________, _________________NORMAN_R3_________________
    ),

    [_MALTRON] = LAYOUT_5x6_right_trackball_base_wrapper(
        _________________MALTRON_L1________________, _________________MALTRON_R1________________,
        _________________MALTRON_L2________________, _________________MALTRON_R2________________,
        _________________MALTRON_L3________________, _________________MALTRON_R3________________
    ),

    [_EUCALYN] = LAYOUT_5x6_right_trackball_base_wrapper(
        _________________EUCALYN_L1________________, _________________EUCALYN_R1________________,
        _________________EUCALYN_L2________________, _________________EUCALYN_R2________________,
        _________________EUCALYN_L3________________, _________________EUCALYN_R3________________
    ),

    [_CARPLAX] = LAYOUT_5x6_right_trackball_base_wrapper(
        _____________CARPLAX_QFMLWY_L1_____________, _____________CARPLAX_QFMLWY_R1_____________,
        _____________CARPLAX_QFMLWY_L2_____________, _____________CARPLAX_QFMLWY_R2_____________,
        _____________CARPLAX_QFMLWY_L3_____________, _____________CARPLAX_QFMLWY_R3_____________
    ),

    [_MOUSE] = LAYOUT_5x6_right_trackball(
        _______, _______, _______, _______, _______, _______,                     DPI_CONFIG, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                        KC_WH_U, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                        KC_WH_D, KC_BTN1, KC_BTN3, KC_BTN2, _______, _______,
        _______, _______, _______, _______, _______, _______,                        _______, KC_BTN4, KC_BTN5, _______, _______, _______,
                          _______, _______,                                                            _______, _______,
                                            _______, _______,                                 _______,
                                                     _______, _______,               _______,
                                                     _______, _______,      _______, _______
    ),
    [_GAMEPAD] = LAYOUT_5x6_right_trackball(
        KC_ESC,  KC_NO,   KC_1,    KC_2,    KC_3,    KC_4,                        DPI_CONFIG, _______, _______, _______, _______, _______,
        KC_F1,   KC_K,    KC_Q,    KC_W,    KC_E,    KC_R,                           KC_WH_U, _______, _______, _______, _______, _______,
        KC_TAB,  KC_G,    KC_A,    KC_S,    KC_D,    KC_F,                           KC_WH_D, KC_BTN1, KC_BTN3, KC_BTN2, _______, _______,
        KC_LCTL, KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_H,                           _______, KC_BTN4, KC_BTN5, _______, _______, _______,
                          KC_I,    KC_T,                                                               TG_GAME, KC_NO,
                                            KC_V,    KC_O,                                    _______,
                                                     KC_SPC,  KC_P,                  _______,
                                                     KC_H,    KC_LGUI,      _______, _______
    ),
    [_DIABLO] = LAYOUT_5x6_right_trackball(
        KC_ESC,  KC_V,    KC_D,    KC_LALT, KC_NO,   KC_NO,                          KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NO,   KC_NO,
        KC_TAB,  KC_S,    KC_I,    KC_F,    KC_M,    KC_T,                           KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_Q,    KC_1,    KC_2,    KC_3,    KC_4,    KC_G,                           KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_LCTL, KC_D3_1, KC_D3_2, KC_D3_3, KC_D3_4, KC_Z,                           KC_NO,   KC_N,    KC_M,    KC_NO,   KC_NO,   KC_NO,
                          KC_F,    KC_L,                                                               KC_NO,   TG_DBLO,
                                      SFT_T(KC_SPC), KC_F,                                    _______,
                                               ALT_T(KC_Q),   KC_J,                  _______,
                                             KC_DIABLO_CLEAR, KC_LGUI,      _______, _______
    ),
    [_LOWER] = LAYOUT_5x6_right_trackball_wrapper(
        KC_F12,  _________________FUNC_LEFT_________________,                        _________________FUNC_RIGHT________________, KC_F11,
        _______, _________________LOWER_L1__________________,                        _________________LOWER_R1__________________, _______,
        _______, _________________LOWER_L2__________________,                        _________________LOWER_R2__________________, KC_PIPE,
        _______, _________________LOWER_L3__________________,                        _________________LOWER_R3__________________, _______,
                          _______, _______,                                                          _______, _______,
                                            _______, _______,                               _______,
                                                     _______, _______,             _______,
                                                     _______, _______,    _______, _______
    ),
    [_RAISE] = LAYOUT_5x6_right_trackball_wrapper(
        KC_F12,  _________________FUNC_LEFT_________________,                      _________________FUNC_RIGHT________________, KC_F11,
        KC_GRV,  _________________RAISE_L1__________________,                      _________________RAISE_R1__________________, _______,
        _______, _________________RAISE_L2__________________,                      _________________RAISE_R2__________________, KC_BSLS,
        _______, _________________RAISE_L3__________________,                      _________________RAISE_R3__________________, _______,
                          _______, _______,                                                          _______, _______,
                                            _______, _______,                               _______,
                                                     _______, _______,             _______,
                                                     _______, _______,    _______, _______
    ),
    [_ADJUST] = LAYOUT_5x6_right_trackball_wrapper(
        KC_MAKE, ___________________BLANK___________________,                      _________________ADJUST_R1_________________, KC_RST,
        VRSN,    _________________ADJUST_L1_________________,                      _________________ADJUST_R1_________________, EEP_RST,
        _______, _________________ADJUST_L2_________________,                      _________________ADJUST_R2_________________, TG_MODS,
        _______, _________________ADJUST_L3_________________,                      _________________ADJUST_R3_________________, KC_MPLY,
                          HPT_DWLI, HPT_DWLD,                                                        _______, _______,
                                            HPT_TOG, HPT_BUZ,                               KC_NUKE,
                                                     _______, _______,             _______,
                                                     _______, _______,    KC_NUKE, _______
    ),
};
// clang-format off


#ifdef POINTING_DEVICE_ENABLE
static uint16_t mouse_timer = 0;
static uint16_t mouse_debounce_timer = 0;
static uint8_t  mouse_keycode_tracker = 0;

void process_mouse_user(report_mouse_t* mouse_report, int16_t x, int16_t y) {
    if ((x || y) && timer_elapsed(mouse_timer) > 125) {
        mouse_timer = timer_read();
        if (!layer_state_is(_MOUSE) && !layer_state_is(_GAMEPAD) && timer_elapsed(mouse_debounce_timer) > 125) {
            layer_on(_MOUSE);
        }
    }
    if (timer_elapsed(mouse_debounce_timer) > 125 || layer_state_is(_GAMEPAD) ) {
        mouse_report->x = x;
        mouse_report->y = y;
    }
}

void matrix_scan_keymap(void) {
    if (timer_elapsed(mouse_timer) > 750 && layer_state_is(_MOUSE) && !mouse_keycode_tracker) {
        layer_off(_MOUSE);
    }
}

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    switch(keycode){
        case MO(_MOUSE):
        case DPI_CONFIG:
        case KC_MS_UP...KC_MS_WH_RIGHT:
            record->event.pressed ? mouse_keycode_tracker++ : mouse_keycode_tracker--;
            mouse_timer = timer_read();
            break;
        default:
            if (layer_state_is(_MOUSE) && !mouse_keycode_tracker) {
                layer_off(_MOUSE);
            }
            mouse_debounce_timer = timer_read();
            break;
    }
    return true;
}
#endif
