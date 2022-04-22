// Copyright 2022 David Kristoffersen (@davidkristoffersen)
// SPDX-License-Identifier: GPL-3.0-or-later

#include "layouts.h"

const uint16_t PROGMEM keymaps [][MATRIX_ROWS][MATRIX_COLS] = {
    /* QGMLW
     * ,-----------------------------------------------------------------------------------.
     * | Tab  |   Q  |   G  |   M  |   L  |   W  |   B  |   Y  |   U  |   V  |   '" | Bksp |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * | Esc  |   D  |   S  |   T  |   N  |   R  |   I  |   A  |   E  |   O  |  H   |Return|
     * |------+------+------+------+------+------|------+------+------+------+------+------|
     * | Shft |   Z  |   X  |   C  |   F  |   J  |   K  |   P  |  ,;  |  .:  |  -_  |   \| |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Ctrl | Alt  | NmPd | GUI  | Lower| Space|Space |Raise | Left | Down |  Up  | Right|
     * `-----------------------------------------------------------------------------------'
     */
     /* Norwegian Layout */
     [QGMLW_NO] = LAYOUT_ortho_4x12(
         KC_TAB,  KC_Q,    KC_G,    KC_M,    KC_L,    KC_W,    KC_B,    KC_Y,    KC_U,    KC_V,    NO_QUOT, KC_BSPC,
         KC_ESC,  KC_D,    KC_S,    KC_T,    KC_N,    KC_R,    KC_I,    KC_A,    KC_E,    KC_O,    KC_H,    KC_ENT,
         KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_F,    KC_J, 	  KC_K,    KC_P,    KC_COMM, KC_DOT,  NO_MINS, NO_BSLS,
         KC_LCTL, KC_LALT, numpad,  KC_LGUI, QNLower, KC_SPC,  KC_SPC,  QNRaise, KC_LEFT, KC_DOWN, KC_UP,   SPACE_TRI
     ),
    /* English Layout */
    [QGMLW_US] = LAYOUT_ortho_4x12(
        KC_TAB,  KC_Q,    KC_G,    KC_M,    KC_L,    KC_W,    KC_B,    KC_Y,    KC_U,    KC_V,    KC_QUOT, KC_BSPC,
        KC_ESC,  KC_D,    KC_S,    KC_T,    KC_N,    KC_R,    KC_I,    KC_A,    KC_E,    KC_O,    KC_H,    KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_F,    KC_J,    KC_K,    KC_P,    KC_COMM, KC_DOT,  KC_MINS, KC_BSLS,
        KC_LCTL, KC_LALT, numpad,  KC_LGUI, QELower, KC_SPC,  KC_SPC,  QERaise, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
    ),

    /* Qwerty
     * ,-----------------------------------------------------------------------------------.
     * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |  ;:  |Return|
     * |------+------+------+------+------+------|------+------+------+------+------+------|
     * | Shft |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |  ,<  |  .>  |  /?  | Shft |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Ctrl | Alt  | NmPd | GUI  | Lower| Space|Space |Raise | Left | Down | Up   | Right|
     * `-----------------------------------------------------------------------------------'
     */
    [QWERTY] = LAYOUT_ortho_4x12(
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSHIFT,
        KC_LCTL, KC_LALT, numpad,  KC_LGUI, lower,   KC_SPC,  KC_SPC,  raise,   KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT
    ),

    /* Colemak
     * ,-----------------------------------------------------------------------------------.
     * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Bksp |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Esc  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |Return|
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Shft |   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |  "   |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Ctrl | Alt  | NmPd | GUI  | Lower| Space|Space |Raise | Left | Down | Up   | Right|
     * `-----------------------------------------------------------------------------------'
     */
    [COLEMAK] = LAYOUT_ortho_4x12(
        KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
        KC_ESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_QUOT ,
        KC_LCTL, KC_LALT, numpad,  KC_LGUI, lower,   KC_SPC,  KC_SPC,  raise,   KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT
    ),

    /* Dvorak
     * ,-----------------------------------------------------------------------------------.
     * | Tab  |   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | Bksp |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Esc  |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |Return|
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Shft |   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |  \   |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Ctrl | Alt  | NmPd | GUI  | Lower| Space|Space |Raise | Left | Down | Up   | Right|
     * `-----------------------------------------------------------------------------------'
     */
    [DVORAK] = LAYOUT_ortho_4x12(
        KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_BSPC,
        KC_ESC,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_ENT,
        KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_SLSH,
        KC_LCTL, KC_LALT, numpad,  KC_LGUI, lower,   KC_SPC,  KC_SPC,  raise,   KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT
    ),

    /* Lower (Normal)
     * ,-----------------------------------------------------------------------------------.
     * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |  End | Home | XXXX | XXXX |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      | Next | Vol- | Vol+ | Play |
     * `-----------------------------------------------------------------------------------'
    */
    [NORMAL_LOWER] = LAYOUT_ortho_4x12(
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
        KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
        _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_END,  KC_HOME, XXXXXXX, XXXXXXX, _______,
        _______, _______, _______, _______, _______, _______, _______, adjust,  KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
    ),

    /* Raise (Normal)
     * ,-----------------------------------------------------------------------------------.
     * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / |Pg Dn |Pg Up |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      | Next | Vol- | Vol+ | Play |
     * `-----------------------------------------------------------------------------------'
     */
    [NORMAL_RAISE] = LAYOUT_ortho_4x12(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
        KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
        _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_HASH, KC_BSLS, KC_PGDN, KC_PGUP, _______,
        _______, _______, _______, _______, adjust,  _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
    ),

    /* Numpad
     * ,-----------------------------------------------------------------------------------.
     * |      | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX |   7  |   8  |   9  |   /  |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX |   4  |   5  |   6  |   *  |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX |   1  |   2  |   3  |   -  | XXXX |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      | XXXX |      |      |   0  |   ,  |   .  |   +  | XXXX |
     * `-----------------------------------------------------------------------------------'
     */
    [NUMPAD] = LAYOUT_ortho_4x12(
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_7,    KC_8,       KC_9,    KC_KP_SLASH, _______,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_4,    KC_5,       KC_6,    KC_KP_ASTERISK, _______,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_1,    KC_2,       KC_3,    KC_KP_MINUS, XXXXXXX,
        _______, _______, _______, _______, XXXXXXX, _______, _______, KC_0,    KC_COMM,    KC_DOT,  KC_KP_PLUS, XXXXXXX
    ),

    /* Lower - QGMLW
     * ,-----------------------------------------------------------------------------------.
     * |   !  |   %  |   [  |   {  |   (  |   <  |   >  |   )  |   }  |   ]  |   &  |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |  Del | Mute | XXXX | Refr | XXXX | XXXX | XXXX |   =  |   +  |   *  |   /  |  ~   |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |Sleep |ScrLck| Caps |NumLck|PrtScr|  Ins |  End | Home |   æ  |   ø  |  å   |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |Adjust| Bri- | Vol- | Vol+ | Bri+ |
     * `-----------------------------------------------------------------------------------'
     */
     /* Norwegian */
     [QGMLW_NO_LOWER] = LAYOUT_ortho_4x12(
         KC_EXLM, KC_PERC, NO_LBRC,    NO_LCBR,    NO_LPRN, NO_LESS, NO_GRTR,       NO_RPRN, NO_RCBR,    NO_RBRC,    NO_AMPR, _______,
         KC_DEL,  KC_MUTE, XXXXXXX,    KC_WREF,    TEST_0,  TEST_1,  TEST_2,        NO_EQL,  NO_PLUS,    NO_ASTR,    NO_SLSH, NO_TILD,
         _______, KC_SLEP, KC_SLCK,    KC_CAPS,    KC_NLCK, KC_PSCR, KC_INS,        KC_END,  KC_HOME,     NO_AE,     NO_OE,   NO_AA,
         _______, _______, _______,    _______,    _______, _______, _______,       adjust,  KC_BRID,    KC_VOLD,    KC_VOLU, KC_BRIU
     ),
    /* English Same as Nok - without æøå */
    [QGMLW_US_LOWER] = LAYOUT_ortho_4x12(
        KC_EXLM, KC_PERC, KC_LBRC, KC_LCBR, KC_LPRN, KC_LT,   KC_GT,   KC_RPRN, KC_RCBR, KC_RBRC, KC_AMPR, _______,
        KC_DEL,  KC_MUTE, XXXXXXX, KC_WREF, TEST_0,  TEST_1,  TEST_2,  KC_EQL,  KC_PLUS, KC_ASTR, KC_SLSH, KC_TILD,
        _______, KC_SLEP, KC_SLCK, KC_CAPS, KC_NLCK, KC_PSCR, KC_INS,  KC_END,  KC_HOME, XXXXXXX, XXXXXXX, XXXXXXX,
        _______, _______, _______, _______, _______, _______, _______, adjust,  KC_BRID, KC_VOLD, KC_VOLU, KC_BRIU
    ),

    /* Raise - QGMLW
     * ,-----------------------------------------------------------------------------------.
     * |   ?  |   9  |   7  |   5  |   3  |   1  |   0  |  2   |   4  |   6  |   8  |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Del+ |  F1  |  F2  |  F3  |   F4 |   F5 |  F6  |   #  |   @  |   ^  |   $  |   `  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |RShift|  F7  |  F8  | F9   |  F10 |  F11 |  F12 | PgDn | PgUp | XXXX | XXXX | XXXX |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |RCtrl | RAlt |      |      |      |      |      |Adjust| Prev | Stop | Play | Next |
     * `-----------------------------------------------------------------------------------'
     */
     /* Norwegian */
     [QGMLW_NO_RAISE] = LAYOUT_ortho_4x12(
         NO_QUES,      KC_9,    KC_7,    KC_5,    KC_3,    KC_1,    KC_0,    KC_2,    KC_4,       KC_6,         KC_8,       _______,
         LCTL(KC_DEL), KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_HASH, NO_AT,      NO_CIRC, NO_DLR,     NO_GRV,
         KC_RSFT,      KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PGDN, KC_PGUP,    XXXXXXX,      XXXXXXX,    XXXXXXX,
         KC_RCTL,      KC_RALT, _______, _______, adjust,  _______, _______, _______, KC_MPRV,    KC_MSTP,      KC_MPLY,    KC_MNXT
      ),
    /* English */
    [QGMLW_US_RAISE] = LAYOUT_ortho_4x12(
        KC_QUES,      KC_9,    KC_7,    KC_5,    KC_3,    KC_1,    KC_0,    KC_2,    KC_4,    KC_6,    KC_8,    _______,
        LCTL(KC_DEL), KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_HASH, KC_AT,   KC_CIRC, KC_DLR,  KC_GRV,
        KC_RSFT,      KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PGDN, KC_PGUP, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_RCTL,      KC_RALT, _______, _______, adjust,  _______, _______, _______, KC_MPRV, KC_MSTP, KC_MPLY, KC_MNXT
    ),

    /* Adjust, every thing on top row (except backspace) is related to rgb stuff
     * ,-----------------------------------------------------------------------------------.
     * |      |Reset |Debug |RGBTGL|RGBMDE| Hue+ | Hue- | Sat+ | Sat- | BriU | BriD | Bksp |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |MseCly| AudOn|AudOff|AgNorm|AgSwap|Dvorak|Colmak|Qwerty|QgmlwE|QgmlwN|
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |Voice+|Voice-|MusOn |MusOff|MIDIOn|MIDIOF|TermOn|TermOf|      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |             |      |      |      |      |      |
     * `-----------------------------------------------------------------------------------'
     */
    [ADJUST] = LAYOUT_ortho_4x12(
        _______, RESET,   DEBUG,   RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI,    RGB_SAD,     RGB_VAI,    RGB_VAD,       KC_DEL,
        _______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, DF(DVORAK), DF(COLEMAK), DF(QWERTY), DF(QGMLW_US),  DF(QGMLW_NO),
        _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  TERM_ON,    TERM_OFF,    XXXXXXX,    _______,       _______,
        _______, _______, _______, _______, _______, _______, _______, _______,    _______,     _______,    _______,       _______
    )

};
