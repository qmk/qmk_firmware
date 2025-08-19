/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

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

// Left-hand home row mods
#define GUI_A  LGUI_T(KC_A)
#define ALT_S  LALT_T(KC_S)
#define ALT_R  LALT_T(KC_R)
#define SFT_D  LSFT_T(KC_D)
#define SFT_S  LSFT_T(KC_S)
#define CTL_F  LCTL_T(KC_F)
#define CTL_TH LCTL_T(KC_T)

// Right-hand home row mods
#define CTL_J RCTL_T(KC_J)
#define CTL_N RCTL_T(KC_N)
#define SFT_K RSFT_T(KC_K)
#define SFT_E RSFT_T(KC_E)
#define ALT_L RALT_T(KC_L)
#define ALT_I RALT_T(KC_I)
#define GUI_SCLN RGUI_T(KC_SCLN)
#define GUI_O RGUI_T(KC_O)

#define SFT_ENT LSFT_T(KC_ENT)
#define NUM_ALT LT(_NUM, KC_LALT)
#define FN_ALT LT(_FN, KC_LALT)
#define NAV_ESC LT(_NAV, KC_ESC)

enum crkbd_layers {
    _BASE,
    _CLMK, // Colemak DH Matrix
    _SYMB,
    _NAV,
    _NUM,
    _FN,
    _RGB,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_3x6_3_ex2(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T, KC_VOLU,  DF(_CLMK),    KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    GUI_A,   ALT_S,   SFT_D,   CTL_F,   KC_G, KC_VOLD,   MO(_RGB),    KC_H,    CTL_J,   SFT_K,  ALT_L,GUI_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ESC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                            NUM_ALT,    MO(_SYMB), SFT_ENT,              KC_SPC, NAV_ESC,  FN_ALT
                                      //`--------------------------'  `--------------------------'
  ),

    [_CLMK] = LAYOUT_split_3x6_3_ex2(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B, KC_VOLU,  DF(_BASE),    KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,   GUI_A,   ALT_R,   SFT_S,  CTL_TH,    KC_G, KC_VOLD,   MO(_RGB),    KC_M,   CTL_N,   SFT_E,   ALT_I,   GUI_O, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,                         KC_K,    KC_H, KC_COMM,  KC_DOT, KC_SLSH,  KC_ESC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                            NUM_ALT,    MO(_SYMB), SFT_ENT,              KC_SPC, NAV_ESC,  FN_ALT
                                      //`--------------------------'  `--------------------------'
  ),

    [_SYMB] = LAYOUT_split_3x6_3_ex2(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_TAB,  KC_GRV, KC_TILDE, KC_HASH, KC_AMPR, KC_PIPE, KC_VOLU,    _______, KC_CIRC, KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, KC_EXLM, KC_UNDS, KC_COLN,  KC_EQL,  KC_DLR, KC_VOLD,    _______,   KC_AT, KC_LPRN, KC_RPRN, KC_UNDS, XXXXXXX, KC_PIPE,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, KC_PERC, KC_SLSH, KC_ASTR, KC_PLUS, KC_BSLS,                      KC_SLSH, KC_MINS, KC_LABK, KC_RABK, XXXXXXX, KC_ESC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

    [_NAV] = LAYOUT_split_3x6_3_ex2(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, _______, _______,   MS_UP, _______, KC_PSCR, KC_VOLU,    _______, KC_HOME, _______,   KC_UP, _______, KC_PGUP,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, MS_WHLU, MS_LEFT, MS_DOWN, MS_RGHT, KC_CAPS, KC_VOLD,    _______,  KC_END, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,  KC_INS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, MS_WHLD, MS_BTN3, MS_BTN3, MS_BTN2, _______,                      _______, KC_VOLD, KC_MUTE, KC_VOLU, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

    [_NUM] = LAYOUT_split_3x6_3_ex2(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, _______, _______, _______, _______, _______, KC_VOLU,    _______, _______,    KC_7,    KC_8,    KC_9,    KC_0, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, _______, KC_VOLD,    _______, _______,    KC_4,    KC_5,    KC_6, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                         KC_0,    KC_1,    KC_2,    KC_3, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),


    [_FN] = LAYOUT_split_3x6_3_ex2(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, _______,   KC_F7,   KC_F8,   KC_F9,  KC_F12, KC_VOLU,    _______, _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______,   KC_F4,   KC_F5,   KC_F6,  KC_F11, KC_VOLD,    _______, _______, KC_RCTL, KC_RSFT, KC_RALT, KC_RGUI, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______,   KC_F1,   KC_F2,   KC_F3,  KC_F10,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

    [_RGB] = LAYOUT_split_3x6_3_ex2(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RM_TOGG, RM_HUEU, RM_SATU, RM_VALU, XXXXXXX, XXXXXXX, _______,    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RM_NEXT, RM_HUED, RM_SATD, RM_VALD, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_ENT, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'
  )
};

#if 0
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    for (uint8_t i = led_min; i < led_max; i++) {
        switch(get_highest_layer(layer_state|default_layer_state)) {
            case _SYMB:
                rgb_matrix_set_color(i, RGB_GREEN);
                break;
            case _NAV:
                rgb_matrix_set_color(i, RGB_BLUE);
                break;
            case _NUM:
                rgb_matrix_set_color(i, RGB_RED);
                break;
            case _FN:
                rgb_matrix_set_color(i, RGB_ORANGE);
                break;
            default:
                break;
        }
    }
    return false;
}
#endif

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
  [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [1] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [2] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [3] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
};
#endif
