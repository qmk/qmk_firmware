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

// layer keys
#define NUM LT(_NUM, KC_DEL)
#define ARROW LT(_ARROW, KC_F)
#define MOUSE LT(_MOUSE, KC_V)
#define S_SPC LT(_SYMB, KC_SPC)
#define S_BSPC LT(_SYMB, KC_BSPC)
#define MEDIA LT(_MEDIA, KC_DEL)
#define ADJUST LT(_ADJUST, KC_ESC)
#define QWERTY DF(_QWERTY)
#define DEFAULT DF(_DEFAULT)
// i3
#define GQUOT GUI_T(KC_QUOT)
#define GTAB GUI_T(KC_TAB)
#define SGENT SGUI_T(KC_ENT)
// mods
#define LCTLZ LCTL_T(KC_Z)
#define RCTLS LCTL_T(KC_SLSH)
#define RALTD RALT_T(KC_DOT)
#define LALTX LALT_T(KC_X)
#define ESC_CTL LCTL_T(KC_ESC)
#define CTL_NUM LT(_MEDIA, KC_LCTL)
// homerow mods
#define S_A LSFT_T(KC_A)
#define S_SCLN RSFT_T(KC_SCLN)

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layers {
  _DEFAULT,
  _SYMB,
  _ARROW,
  _MOUSE,
  _MEDIA,
  _NUM,
  _ADJUST,
  _QWERTY
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_DEFAULT] = LAYOUT_split_3x6_3( \
 //,-----------------------------------------.                ,-----------------------------------------.
     MEDIA, KC_Q, KC_W, KC_E, KC_R, KC_T,                       KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      GTAB, KC_A, KC_S, KC_D, ARROW, KC_G,                        KC_H, KC_J, KC_K, KC_L, KC_SCLN, GQUOT,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      SC_LSPO, LCTLZ, LALTX, KC_C, MOUSE, KC_B,                 KC_N, KC_M, KC_COMM, RALTD, RCTLS, SC_RSPC,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                ESC_CTL, NUM, S_SPC,    S_BSPC,  SGENT, ADJUST \
                             //`-----------------------'  `----------------------'
  ),


  [_SYMB] = LAYOUT_split_3x6_3( \
 //,-----------------------------------------.                ,-----------------------------------------.
      _______, KC_QUES, KC_CIRC, KC_PERC, KC_HASH, KC_ASTR,                  KC_EQUAL, KC_LCBR, KC_RCBR, KC_AT, KC_EXLM, _______, \
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _______, KC_SLASH, KC_AMPR, KC_LBRC, KC_RBRC, KC_MINUS,           KC_UNDS, KC_LPRN, KC_RPRN, KC_DLR, KC_COLN, KC_DQUO,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _______, KC_QUOT,  KC_COMMA,  KC_DOT,  KC_GRAVE,  KC_PLUS,                KC_TILD, KC_PIPE, KC_LABK, KC_RABK, KC_SLASH, _______,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                          _______,  _______, KC_SPC,      KC_SPC, _______, _______ \
                              //`--------------------'  `--------------------'
  ),

  [_ARROW] = LAYOUT_split_3x6_3( \
 //,-----------------------------------------.                ,-----------------------------------------.
    _______, _______, _______, _______, _______, _______,                 _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, \
    //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    _______, _______, _______, _______, _______, _______,                  _______, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, _______, \
    //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    _______, _______, _______, _______, _______, _______,                 KC_INS, KC_CAPS_LOCK, _______, _______, _______, _______, \
    //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                _______, _______, _______,     _______, _______, _______\
                             //`-----------------------'  `----------------------'
  ),

  [_MOUSE] = LAYOUT_split_3x6_3( \
 //,-----------------------------------------.                ,-----------------------------------------.
    _______, _______, _______, _______, _______, _______,            _______, MS_WHLL, MS_WHLD, MS_WHLU, MS_WHLR, _______,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    _______, MS_ACL0, MS_ACL1, MS_ACL2, _______, _______,    _______, MS_LEFT, MS_DOWN, MS_UP, MS_RGHT, _______,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    _______, _______, _______, _______, _______, _______,             _______, _______, _______, _______, _______, _______, \
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                             _______,  _______, MS_BTN2,             MS_BTN1, MS_BTN3, _______  \
                             //`-----------------------'  `----------------------'
  ),



  [_MEDIA] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------.                ,-----------------------------------------.
XXXXXXX, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,                  KC_F6, KC_F7, KC_F8, KC_F9, KC_F10,  XXXXXXX, \
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_F11,      KC_F12, KC_MPRV, KC_MSTP, KC_MPLY, KC_MNXT, XXXXXXX, \
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_AUDIO_MUTE, \
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                             XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, KC_VOLD, KC_VOLU \
                             //`-----------------------'  `----------------------'
  ),



  [_NUM] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------.                ,-----------------------------------------.
  _______, KC_QUES, KC_CIRC, KC_PERC, KC_HASH, KC_ASTR,        KC_EQUAL,KC_7, KC_8,  KC_9, KC_EXLM, _______, \
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
_______, KC_SLASH, KC_AMPR, KC_LBRC, KC_RBRC, KC_MINUS,  KC_UNDS, KC_4, KC_5, KC_6, KC_COLN, KC_DQUO, \
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
_______, KC_QUOT, KC_COMMA, KC_DOT, KC_GRAVE, KC_PLUS,     KC_0, KC_1, KC_2, KC_3, _______, _______, \
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                               _______, _______, _______,     KC_SPC, KC_0, _______ \
                             //`-----------------------'  `----------------------'
  ),



  [_ADJUST] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------.                ,-----------------------------------------.
    QK_BOOT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                 KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, QK_BOOT,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    RM_TOGG, RM_HUEU, RM_SATU, RM_VALU, RM_SPDU, KC_NO,           KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    RM_NEXT, RM_HUED, RM_SATD, RM_VALD, RM_SPDD, RM_TOGG,          KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                             QWERTY, KC_NO, KC_NO,                KC_NO, KC_NO, KC_NO \
  ),
     [_QWERTY] = LAYOUT_split_3x6_3( \
 //,-----------------------------------------.                ,-----------------------------------------.
     KC_DEL, KC_Q, KC_W, KC_E, KC_R, KC_T,                     KC_Y, KC_U, KC_I, KC_O, KC_P, DEFAULT,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
     KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G,          KC_H, KC_J, KC_K, KC_L, KC_SCLN, GQUOT,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B,           KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
              KC_LCTL, KC_SPC, KC_ENT,            KC_BSPC,  KC_ENT, KC_ESC \
                                       //`--------------------'  `--------------------'
     )
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
  [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [1] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [2] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [3] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
};
#endif


#ifdef OLED_ENABLE
bool oled_task_user(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (biton32(layer_state)) {
        case _DEFAULT:
            oled_write_ln_P(PSTR("DEFAULT"), false);
            break;
        case _SYMB:
            oled_write_ln_P(PSTR("SYMBOL"), false);
            break;
        case _ARROW:
            oled_write_ln_P(PSTR("ARROW"), false);
            break;
        case _MOUSE:
            oled_write_ln_P(PSTR("MOUSE"), false);
            break;
        case _MEDIA:
            oled_write_ln_P(PSTR("MEDIA"), false);
            break;
        case _NUM:
            oled_write_ln_P(PSTR("NUM"), false);
            break;
        case _ADJUST:
            oled_write_ln_P(PSTR("RGB"), false);
            break;
        case _QWERTY:
            oled_write_ln_P(PSTR("GAMING"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Unknown"), false);
            break;
    }
        // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);

    // oled_write(read_logo(), false);
    return false;
}

#endif
