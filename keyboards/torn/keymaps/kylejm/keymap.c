/* Copyright 2021 Kyle McAlpine 
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

enum torn_layers { _QWERTY, _NUMBERS, _NAV_MEDIA, _SYM_1, _SYM_2 };

enum torn_keycodes {
    KL_TOG = SAFE_RANGE,
    KL_BUP,
    KL_BDN,
    KL_TUP,
    KL_TDN,
    HASH,
    POUND,
    SCRNSH,
    CLPHST,
    COPY,
    PASTE
};

#define HL(k1, k2, k3, k4, k5) LCTL_T(k1), LALT_T(k2), LCMD_T(k3), LSFT_T(k4),  MT(MOD_HYPR, k5),
#define HR(k1, k2, k3, k4, k5) MT(MOD_HYPR, k1), RSFT_T(k2), RCMD_T(k3), RALT_T(k4), RCTL_T(k5)
#define THUMB_LEFT KC__MUTE, KC_ESC, LT(_NAV_MEDIA, KC_ENT), LT(_NUMBERS, KC_TAB)
#define THUMB_RIGHT LT(_SYM_2, KC_SPC), LT(_SYM_1, KC_BSPC), KC_DEL, KL_TOG

#define TRANSPARENT_ROW _______, _______, _______, _______, _______, _______
#define TRANSPARENT_THUMB _______, _______, _______, _______

#define PLYPSE KC_MEDIA_PLAY_PAUSE
#define PRVTRK KC_MEDIA_REWIND
#define NXTTRK KC_MEDIA_FAST_FORWARD
#define VOLDWN KC__VOLDOWN
#define VOLUP  KC__VOLUP
#define VOLMUT KC__MUTE

#define LAYOUT_WRAP(...) LAYOUT_split_3x6_4(__VA_ARGS__)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Qwerty
    * ,-----------------------------------.    ,-----------------------------------.
    * |COPY |  Q  |  W  |  E  |  R  |  T  |    |  Y  |  U  |  I  |  O  |  P  |  -  |
    * |-----+-----+-----+-----+-----+-----|    |-----+-----+-----+-----+-----+-----|
    * |     | Ctl | Alt | CMD |Shift|Hyper|    |Hyper|Shift| CMD | Alt | Ctl |     |
    * |PASTE|  A  |  S  |  D  |  F  |  G  |    |  H  |  J  |  K  |  L  |  ;  |  '  |
    * |-----+-----+-----+-----+-----+-----|    |-----+-----+-----+-----+-----+-----|
    * |SCRSH|  Z  |  X  |  C  |  V  |  B  |    |  N  |  M  |  ,  |  .  |  /  |CLPHS|
    * |-----+-----+-----+-----+-----+-----|    |-----+-----+-----+-----+-----+-----|
    *             |     |     | Nav | Num |    | Sym | Sym |     |     |
    *             |Mute | Esc |Enter| Tab |    |Space|Bcksp| Del |Keyli|
    *            `------------------------'    `-----------------------'
    */    
    [_QWERTY] = LAYOUT_WRAP(
          COPY,    KC_Q, KC_W, KC_E, KC_R, KC_T,      KC_Y, KC_U, KC_I,    KC_O,   KC_P,     KC_MINS, 
         PASTE, HL(KC_A, KC_S, KC_D, KC_F, KC_G)   HR(KC_H, KC_J, KC_K,    KC_L,   KC_SCLN), KC_QUOT,
        SCRNSH,    KC_Z, KC_X, KC_C, KC_V, KC_B,      KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,  CLPHST, 
                                    THUMB_LEFT,       THUMB_RIGHT
    ),

    /* Navigation & Media
    * ,-----------------------------------.    ,------------------------------------.
    * |  C  |  H  |  O  |  R  |  D  |  S  |    |     | L+A | R+A | L+C | R+C |
    * |-----+-----+-----+-----+-----+-----|    |-----+-----+-----+-----+-----+------|
    * |  A  |  R  |  E  |     |     |     |    |Caps |Left |Right| Up  |Down |      |
    * |-----+-----+-----+-----+-----+-----|    |-----+-----+-----+-----+-----+------|
    * |  B  |  A  |  D  |     |     |     |    |     |Pause|Prev.|Next |     |      |
    * |-----+-----+-----+-----+-----+-----|    |-----+-----+-----+-----+-----+------|
    *             |     |     | Nav | Num |    | Sym | Sym |     |     |
    *             |Mute | Esc |Enter| Tab |    |Space|Bcksp| Del |Keyli|
    *            `------------------------'    `-----------------------'
    */
    [_NAV_MEDIA] = LAYOUT_WRAP(
          TRANSPARENT_ROW,      _______, A(KC_LEFT), A(KC_RIGHT), C(KC_LEFT), C(KC_RIGHT), _______,
          TRANSPARENT_ROW,      KC_CAPS, KC_LEFT,    KC_RGHT,     KC_UP,      KC_DOWN,     _______, 
          TRANSPARENT_ROW,      _______, PLYPSE,     PRVTRK,      NXTTRK,     _______,     _______, 
        TRANSPARENT_THUMB,      TRANSPARENT_THUMB
    ),

    /* Numbers
    * ,-----------------------------------.    ,------------------------------------.
    * |  C  |  H  |  O  |  R  |  D  |  S  |    |  *  |  7  |  8  |  9  |     |      |
    * |-----+-----+-----+-----+-----+-----|    |-----+-----+-----+-----+-----+------|
    * |  A  |  R  |  E  |     |     |     |    |  +  |  4  |  5  |  6  |  0  |      |
    * |-----+-----+-----+-----+-----+-----|    |-----+-----+-----+-----+-----+------|
    * |  B  |  A  |  D  |     |     |     |    |     |  1  |  2  |  3  |     |      |
    * |-----+-----+-----+-----+-----+-----|    |-----+-----+-----+-----+-----+------|
    *             |     |     | Nav | Num |    | Sym | Sym |     |     |
    *             |Mute | Esc |Enter| Tab |    |Space|Bcksp| Del |Keyli|
    *            `------------------------'    `-----------------------'
    */    
   [_NUMBERS] = LAYOUT_WRAP(
          TRANSPARENT_ROW,      KC_ASTR, KC_7, KC_8, KC_9, _______, _______,
          TRANSPARENT_ROW,      KC_PPLS, KC_4, KC_5, KC_6, KC_0,    _______, 
          TRANSPARENT_ROW,      _______, KC_1, KC_2, KC_3, _______, _______, 
        TRANSPARENT_THUMB,      TRANSPARENT_THUMB
    ),

    /* Symbols 1
    * ,-----------------------------------.    ,-----------------------------------.
    * |     |     |     |     |     |     |    |  C  |  H  |  O  |  R  |  D  |  S  |
    * |-----+-----+-----+-----+-----+-----|    |-----+-----+-----+-----+-----+-----|
    * |     |  [  |  ]  |  (  |  )  |  $  |    |     |     |     |  A  |  R  |  E  |
    * |-----+-----+-----+-----+-----+-----|    |-----+-----+-----+-----+-----+-----|
    * |     |     |  \  |  {  |  }  |     |    |     |     |     |  B  |  A  |  D  |
    * |-----+-----+-----+-----+-----+-----|    |-----+-----+-----+-----+-----+-----|
    *             |     |     | Nav | Num |    | Sym | Sym |     |     |
    *             |Mute | Esc |Enter| Tab |    |Space|Bcksp| Del |Keyli|
    *            `------------------------'    `-----------------------'
    */
    [_SYM_1] = LAYOUT_WRAP(
        _______, _______, _______, _______, _______, _______,     TRANSPARENT_ROW,
        _______, KC_LBRC, KC_RBRC, KC_LPRN, KC_RPRN,  KC_DLR,     TRANSPARENT_ROW, 
        _______, _______, KC_BSLS, KC_LCBR, KC_RCBR, _______,     TRANSPARENT_ROW, 
                                           TRANSPARENT_THUMB,     TRANSPARENT_THUMB
    ),

    /* Symbols 2
    * ,-----------------------------------.    ,-----------------------------------.
    * |     |  !  |  @  |  #  |     |     |    |  C  |  H  |  O  |  R  |  D  |  S  |
    * |-----+-----+-----+-----+-----+-----|    |-----+-----+-----+-----+-----+-----|
    * |     |  ~  |  *  |  £  |  =  |  &  |    |     |     |     |  A  |  R  |  E  |
    * |-----+-----+-----+-----+-----+-----|    |-----+-----+-----+-----+-----+-----|
    * |     |  `  |     |  ^  |  %  |  |  |    |     |     |     |  B  |  A  |  D  |
    * |-----+-----+-----+-----+-----+-----|    |-----+-----+-----+-----+-----+-----|
    *             |     |     | Nav | Num |    | Sym | Sym |     |     |
    *             |Mute | Esc |Enter| Tab |    |Space|Bcksp| Del |Keyli|
    *            `------------------------'    `-----------------------'
    */
    [_SYM_2] = LAYOUT_WRAP(
        _______, KC_EXLM,   KC_AT,    HASH, _______, _______,     TRANSPARENT_ROW,
        _______, KC_TILD,   POUND, KC_ASTR,  KC_EQL, KC_AMPR,     TRANSPARENT_ROW, 
        _______,  KC_GRV, _______, KC_CIRC, KC_PERC, KC_PIPE,     TRANSPARENT_ROW, 
                                           TRANSPARENT_THUMB,     TRANSPARENT_THUMB
    )
};

const uint16_t PROGMEM encoder_keymaps[][2][2] = {
    [_QWERTY]        =  { { VOLDWN,  VOLUP   },  { KL_BDN,  KL_BUP  } },
    [_NAV_MEDIA]  =  { { _______, _______ },  { KL_TDN,  KL_TUP } },
    [_NUMBERS] =  { { _______, _______ },  { _______, _______ } },
    [_SYM_1] =  { { _______, _______ },  { _______, _______ } },
    [_SYM_2] =  { { _______, _______ },  { _______, _______ } },
};
// clang-format on

void hyper_tap(const char *letter) {
    SEND_STRING(SS_DOWN(X_LSFT)SS_DOWN(X_LGUI)SS_DOWN(X_LCTL)SS_DOWN(X_LALT));
    for (int i = 0; letter[i] != 0x0; i++) {
        register_code(letter[i]);
        unregister_code(letter[i]);
    }
    SEND_STRING(SS_UP(X_LSFT)SS_UP(X_LGUI)SS_UP(X_LCTL)SS_UP(X_LALT));
}

layer_state_t layer_state_set_user(layer_state_t state) {
    torn_set_led(0, IS_LAYER_ON_STATE(state, _NAV_MEDIA) || IS_LAYER_ON_STATE(state, _SYM_2));
    torn_set_led(1, IS_LAYER_ON_STATE(state, _NUMBERS));
    torn_set_led(2, IS_LAYER_ON_STATE(state, _SYM_1) || IS_LAYER_ON_STATE(state, _SYM_2));
    return state;
};

uint16_t key_timer;
bool process_record_user(uint16_t keycode, keyrecord_t *record) { 
    switch (keycode) {
    case KL_TOG:
        if (record->event.pressed) { 
            hyper_tap("d");
        } 
        return false;
    case HASH:
        if (record->event.pressed) { 
            key_timer = timer_read(); 
            register_code(KC_LSFT); 
        } else { 
            unregister_code(KC_LSFT); 
            if (timer_elapsed(key_timer) < TAPPING_TERM) {
                SEND_STRING(SS_DOWN(X_LALT)"3"SS_UP(X_LALT));
            } 
        } 
        return false;
    case POUND:
        if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LSFT)"3"SS_UP(X_LSFT));
        }
        return false;
    case SCRNSH:
        if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LSFT)SS_DOWN(X_LGUI)"4"SS_UP(X_LSFT)SS_UP(X_LGUI));
        }
        return false;
    case CLPHST:
        if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LGUI)SS_DOWN(X_LCTL)SS_DOWN(X_LALT));
            SEND_STRING("c");
            SEND_STRING(SS_UP(X_LGUI)SS_UP(X_LCTL)SS_UP(X_LALT));
        }
    case COPY:
        if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LGUI)"c"SS_UP(X_LGUI));
        }
        return false;
    case PASTE:
        if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LGUI)"v"SS_UP(X_LGUI));
        }
        return false;
    default:
        return true;
    }
};

bool encoder_update_user(uint16_t keycode, bool clockwise) {
    switch (keycode) {
    case KL_BDN:
        hyper_tap("p");
        break;
    case KL_BUP:
        hyper_tap("u");
        break;
    case KL_TDN:
        hyper_tap("e");
        break;
    case KL_TUP:
        hyper_tap("y");
        break;
    default:
        return false;
    }
    
    return true;
}
