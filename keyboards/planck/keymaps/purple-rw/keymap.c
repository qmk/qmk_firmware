/* Copyright 2020-2023 Rhys Wong
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

/*
 * Only 34 keys (3x5+2 each hand) are really needed.
 * Additional keys are for conveninence, but limited by available keycaps.
 * Designed for use with Linux in mind, with US/English layout.
 */

#include QMK_KEYBOARD_H
#include "os_detection.h"
#ifdef AUDIO_ENABLE
#    include "muse.h"
#endif


enum planck_layers {
    _COLEMAK,	// Colemak-DH
    _QWERTY,    // Qwerty
    _HANDSDN,   // Hands Down Neu 30
    _SEMIMAK,   // Semimak JQ
    _RAISE,     // Numbers & Symbols
    _SYMBL,     // Symbols
    _LOWER,     // Navigation & Functions
    _KEYPD,     // Keypad & Functions2
    _MODS,      // Modifiers, Multimedia & Macros
    _MOUSE,     // Mouse
    _MACRO,     // Dynamic Macros
    _PLOVER,    // Plover
    _ADJST      // Adjustment
};

enum planck_keycodes {
    COLEMAK = QK_USER,
    QWERTY,
    HANDSDN,
    SEMIMAK,
    PLOVER,
    EXT_PLV,

    M_UNDO,
    M_CUT,
    M_COPY,
    M_PASTE,
    M_SELAL,    // select all
    M_ZMIN,     // zoom in
    M_ZMOUT     // zoom out
};

/* Converting keycode to layer enum */
const uint16_t PROGMEM keycode2layer[] = {
    _COLEMAK,
    _QWERTY,
    _HANDSDN,
    _SEMIMAK,
    _PLOVER
};

/* Operating system dependent shortcut keys */
const uint16_t PROGMEM osd_keys[][3] = {
                  /*  Linux       Windows     MacOS
                      xfce        Magnifier   accessibility  */
    /* M_UNDO  */   { C(KC_Z),    C(KC_Z),    G(KC_Z)       },
    /* M_CUT   */   { C(KC_X),    C(KC_X),    G(KC_X)       },
    /* M_COPY  */   { C(KC_C),    C(KC_C),    G(KC_C)       },
    /* M_PASTE */   { C(KC_V),    C(KC_V),    G(KC_V)       },
    /* M_SELAL */   { C(KC_A),    C(KC_A),    G(KC_A)       },
    /* M_ZMIN  */   { A(KC_WH_D), G(KC_EQL),  G(A(KC_EQL))  },
    /* M_ZMOUT */   { A(KC_WH_U), G(KC_MINS), G(A(KC_MINS)) }
};

/* Thumb keys */
#define RAISE   TL_LOWR
#define SYMBL   TT(_SYMBL)
#define LOWER   TL_UPPR
#define KEYPD   TT(_KEYPD)

/* Layer keys */
#define MOUSE   TG(_MOUSE)
#define ADJST   TG(_ADJST)
#define MACRO   OSL(_MACRO)

/* One-shot modifier keys */
#define OS_LSFT OSM(MOD_LSFT)
#define OS_LCTL OSM(MOD_LCTL)
#define OS_LALT OSM(MOD_LALT)
#define OS_LGUI OSM(MOD_LGUI)
#define OS_RSFT OSM(MOD_RSFT)
#define OS_RCTL OSM(MOD_RCTL)
#define OS_RALT OSM(MOD_RALT)
#define OS_RGUI OSM(MOD_RGUI)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |  Q   |  W   |  F   |  P   |  B   |  J   |  L   |  U   |  Y   |  ;   |BkSpc |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  -   |  A   |  R   |  S   |  T   |  G   |  M   |  N   |  E   |  I   |  O   |  '   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Shift |  Z   |  X   |  C   |  D   |  V   |  K   |  H   |  ,   |  .   |  /   |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |CapsWd| Ctrl | Alt  | GUI  |LOWER |Shift |Space |RAISE | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_COLEMAK] = LAYOUT_planck_grid(
    KC_ESC,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
    KC_MINS, KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
    CW_TOGG, KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_LSFT, KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |      |  Q   |  W   |  E   |  R   |  T   |  Y   |  U   |  I   |  O   |  P   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  A   |  S   |  D   |  F   |  G   |  H   |  J   |  K   |  L   |  ;   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  Z   |  X   |  C   |  V   |  B   |  N   |  M   |  ,   |  .   |  /   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_grid(
    _______, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    _______,
    _______, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, _______,
    _______, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Hands Down Neu 30
 * ,-----------------------------------------------------------------------------------.
 * |      |  W   |  F   |  M   |  P   |  V   |  /   |  .   |  Q   |  J   |  Z   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  R   |  S   |  N   |  T   |  G   |  ,   |  A   |  E   |  I   |  H   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  X   |  C   |  L   |  D   |  B   |  ;   |  U   |  O   |  Y   |  K   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_HANDSDN] = LAYOUT_planck_grid(
    _______, KC_W,    KC_F,    KC_M,    KC_P,    KC_V,    KC_SLSH, KC_DOT,  KC_Q,    KC_J,    KC_Z,    _______,
    _______, KC_R,    KC_S,    KC_N,    KC_T,    KC_G,    KC_COMM, KC_A,    KC_E,    KC_I,    KC_H,    _______,
    _______, KC_X,    KC_C,    KC_L,    KC_D,    KC_B,    KC_SCLN, KC_U,    KC_O,    KC_Y,    KC_K,    _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Semimak JQ
 * ,-----------------------------------------------------------------------------------.
 * |      |  F   |  L   |  H   |  V   |  Z   |  ;   |  W   |  U   |  O   |  Y   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  S   |  R   |  N   |  T   |  K   |  C   |  D   |  E   |  A   |  I   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  X   |  J   |  B   |  M   |  Q   |  P   |  G   |  ,   |  .   |  /   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_SEMIMAK] = LAYOUT_planck_grid(
    _______, KC_F,    KC_L,    KC_H,    KC_V,    KC_Z,    KC_SCLN, KC_W,    KC_U,    KC_O,    KC_Y,    _______,
    _______, KC_S,    KC_R,    KC_N,    KC_T,    KC_K,    KC_C,    KC_D,    KC_E,    KC_A,    KC_I,    _______,
    _______, KC_X,    KC_J,    KC_B,    KC_M,    KC_Q,    KC_P,    KC_G,    KC_COMM, KC_DOT,  KC_SLSH, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Numbers & Symbols
 * ,-----------------------------------------------------------------------------------.
 * |  ^   |  9   |  5   |  3   |  1   |  7   |  6   |  0   |  2   |  4   |  8   |  `   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  +   |  $   |  =   |  -   |  (   |  .   |  :   |  )   |  _   |  "   |  '   |  !   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  %   |  @   |  |   |  &   |  {   |  [   |  ]   |  }   |  *   |  #   |  \   |  ~   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |(MODS)|SYMBL |      | #### |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
 [_RAISE] = LAYOUT_planck_grid(
    KC_CIRC, KC_9,    KC_5,    KC_3,    KC_1,    KC_7,    KC_6,    KC_0,    KC_2,    KC_4,    KC_8,    KC_GRV,
    KC_PLUS, KC_DLR,  KC_EQL,  KC_MINS, KC_LPRN, KC_DOT,  KC_COLN, KC_RPRN, KC_UNDS, KC_DQT,  KC_QUOT, KC_EXLM,
    KC_PERC, KC_AT,   KC_PIPE, KC_AMPR, KC_LCBR, KC_LBRC, KC_RBRC, KC_RCBR, KC_ASTR, KC_HASH, KC_BSLS, KC_TILD,
    _______, _______, _______, _______, _______, SYMBL,   XXXXXXX, _______, _______, _______, _______, _______
),

/* Symbols
 * ,-----------------------------------------------------------------------------------.
 * |  ^   |  ^   |  %   |  +   |  [   |  ,   |  ;   |  ]   |  !   |  ~   |  `   |  `   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  +   |  $   |  =   |  -   |  (   |  <   |  >   |  )   |  _   |  "   |  '   |  !   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  %   |  @   |  |   |  &   |  {   |  /   |  ?   |  }   |  *   |nonUS#|nonUS\|  ~   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      | #### |      | #### |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
 [_SYMBL] = LAYOUT_planck_grid(
    _______, KC_CIRC, KC_PERC, KC_PLUS, KC_LBRC, KC_COMM, KC_SCLN, KC_RBRC, KC_EXLM, KC_TILD, KC_GRV,  _______,
    _______, _______, _______, _______, _______, KC_LABK, KC_RABK, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, KC_SLSH, KC_QUES, _______, _______, KC_NUHS, KC_NUBS, _______,
    _______, _______, _______, _______, XXXXXXX, _______, XXXXXXX, _______, _______, _______, _______, _______
),

/* Navigation & Functions
 * ,-----------------------------------------------------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |Pause | Ins  | PgUp |  Up  | PgDn | Menu |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F5  |  F6  |  F7  |  F8  |PrScn | Home | Left | Down |Right | End  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F9  | F10  | F11  | F12  |ScrLk | Tab  |BkSpc |Enter | Del  |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      | **** |      |KEYPD |(MODS)|      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
 [_LOWER] = LAYOUT_planck_grid(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_PAUS, KC_INS,  KC_PGUP, KC_UP,   KC_PGDN, KC_APP,  _______,
    _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_PSCR, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,  _______,
    _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_SCRL, KC_TAB,  KC_BSPC, KC_ENT,  KC_DEL,  _______, _______,
    _______, _______, _______, _______, _______, XXXXXXX, KEYPD,   _______, _______, _______, _______, _______
),

/* Keypad & Functions2
 * ,-----------------------------------------------------------------------------------.
 * |      | F13  | F14  | F15  | F16  |NumLck|  *   |  7   |  8   |  9   |  /   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | F17  | F18  | F19  | F20  |  =   |  -   |  4   |  5   |  6   |  +   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | F21  | F22  | F23  | F24  | Ent  |  0   |  1   |  2   |  3   |  .   | Ent  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      | **** |      | **** |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_KEYPD] = LAYOUT_planck_grid(
    _______, KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_NUM,  KC_PAST, KC_P7,   KC_P8,   KC_P9,   KC_PSLS, _______,
    _______, KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_PEQL, KC_PMNS, KC_P4,   KC_P5,   KC_P6,   KC_PPLS, _______,
    _______, KC_F21,  KC_F22,  KC_F23,  KC_F24,  KC_PENT, KC_P0,   KC_P1,   KC_P2,   KC_P3,   KC_PDOT, KC_PENT,
    _______, _______, _______, _______, _______, XXXXXXX, _______, XXXXXXX, _______, _______, _______, _______
),

/* Modifiers, Multimedia & Macros
 * ,-----------------------------------------------------------------------------------.
 * | Esc  | Esc  |      |Zoom- |Zoom+ |Mouse |Adjst | Vol- | Mute | Vol+ |Eject |Eject |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Ctrl | Alt  | Cmd  |Shift |CapsLk|CapsWd|Shift | Cmd  | Alt  | Ctrl |Macro |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Undo | Cut  | Copy |Paste |SelAll| Prev |Rewind| Play | FFwd | Next |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      | **** |      |      | **** |      |      |Reset |BootL |
 * `-----------------------------------------------------------------------------------'
 */
[_MODS] = LAYOUT_planck_grid(
    KC_ESC,  KC_ESC,  XXXXXXX, M_ZMOUT, M_ZMIN,  MOUSE,   ADJST,   KC_VOLD, KC_MUTE, KC_VOLU, KC_EJCT, KC_EJCT,
    XXXXXXX, OS_LCTL, OS_LALT, OS_LGUI, OS_LSFT, KC_CAPS, CW_TOGG, OS_RSFT, OS_RGUI, OS_RALT, OS_RCTL, MACRO,
    XXXXXXX, M_UNDO,  M_CUT,   M_COPY,  M_PASTE, M_SELAL, KC_MRWD, KC_MPRV, KC_MPLY, KC_MNXT, KC_MFFD, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, QK_RBT,  QK_BOOT
),

/* Mouse
 * ,-----------------------------------------------------------------------------------.
 * |      | Acc2 |WhlUp |  Up  |WhlDn | Exit | Exit |WhlUp |  Up  |WhlDn | Acc2 |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |WhlLt | Left | Down |Right |WhlRt |WhlLt | Left | Down |Right |WhlRt |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Acc1 | Btn2 | Btn3 | Btn1 | Acc0 | Acc0 | Btn1 | Btn3 | Btn2 | Acc1 |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      | Btn2 | Btn1 | Btn1 | Btn2 |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_MOUSE] = LAYOUT_planck_grid(
    XXXXXXX, KC_ACL2, KC_WH_U, KC_MS_U, KC_WH_D, MOUSE,   MOUSE,   KC_WH_U, KC_MS_U, KC_WH_D, KC_ACL2, XXXXXXX,
    XXXXXXX, KC_WH_L, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_R, KC_WH_L, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_R, XXXXXXX,
    XXXXXXX, KC_ACL1, KC_BTN2, KC_BTN3, KC_BTN1, KC_ACL0, KC_ACL0, KC_BTN1, KC_BTN3, KC_BTN2, KC_ACL1, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BTN2, KC_BTN1, KC_BTN1, KC_BTN2, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),

/* Dynamic Macros
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |DMrec1|DMrec2|      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |DMply1|DMply2|      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |DMstop|      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_MACRO] = LAYOUT_planck_grid(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DM_REC1, DM_REC2, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DM_PLY1, DM_PLY2, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DM_RSTP, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),

/* Plover
 * ,-----------------------------------------------------------------------------------.
 * |      | q S- | w T- | s P- | r H- | t *  | y *  | u -F | i -P | o -L | p -T | [ -D |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | a S- | s K- | d W- | f R- | g *  | h *  | j -R | k -B | l -G | ; -S | ' -Z |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Exit |      |      | 1 #  | c A- | v O- | n -E | m -U | 1 #  |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_PLOVER] = LAYOUT_planck_grid(
    XXXXXXX, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
    XXXXXXX, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    EXT_PLV, XXXXXXX, XXXXXXX, KC_1,    KC_C,    KC_V,    KC_N,    KC_M,    KC_1,    XXXXXXX, XXXXXXX, XXXXXXX
),

/* Adjust
 * ,-----------------------------------------------------------------------------------.
 * | Exit |Brght+| Sat+ | Hue+ |RGBmod| BL+  |      |      |      |      |      |Debug |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Brght-| Sat- | Hue- | RGB  | BL-  |AGnorm|Colemk|Qwerty|HndsDn|Semimk|Plover|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |  BL  |BLbrth|AGswap|AudOn |AudOff|MusOn |MusNxt|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      | Exit | Exit |      |      |      |Reset |BootL |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJST] = LAYOUT_planck_grid(
    ADJST,   RGB_VAI, RGB_SAI, RGB_HUI, RGB_MOD, BL_UP,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DB_TOGG,
    XXXXXXX, RGB_VAD, RGB_SAD, RGB_HUD, RGB_TOG, BL_DOWN, AG_NORM, COLEMAK, QWERTY,  HANDSDN, SEMIMAK, PLOVER,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, BL_TOGG, BL_BRTG, AG_SWAP, AU_ON,   AU_OFF,  MU_ON,   MU_NEXT, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, ADJST,   ADJST,   XXXXXXX, XXXXXXX, XXXXXXX, QK_RBT,  QK_BOOT
)

};

#ifdef AUDIO_ENABLE
    float plover_song[][2]     = SONG(PLOVER_SOUND);
    float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

void keyboard_post_init_user(void) {
    set_tri_layer_layers(_RAISE, _LOWER, _MODS);
}

void process_osd_keys (uint16_t keycode, keyrecord_t *record, uint8_t os) {
    if (record->event.pressed) {
        register_code16(osd_keys[keycode - M_UNDO][os]);
    } else {
        unregister_code16(osd_keys[keycode - M_UNDO][os]);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef CONSOLE_ENABLE
    if (record->event.pressed) {
        uprintf("0x%04X,%u,%u,%u\n", keycode, record->event.key.row, record->event.key.col,
                get_highest_layer(layer_state));
    }
#endif

    switch (keycode) {
        case COLEMAK:   /* fall thru */
        case QWERTY:    /* fall thru */
        case HANDSDN:   /* fall thru */
        case SEMIMAK:
            if (record->event.pressed) {
                uint16_t layer = keycode2layer[keycode - QK_USER];
                set_single_persistent_default_layer(layer);
                layer_move(layer);
            }
            return false;
        case PLOVER:
            if (record->event.pressed) {
                #ifdef AUDIO_ENABLE
                    stop_all_notes();
                    PLAY_SONG(plover_song);
                #endif
                layer_move(_PLOVER);
                if (!eeconfig_is_enabled()) {
                    eeconfig_init();
                }
                keymap_config.raw = eeconfig_read_keymap();
                keymap_config.nkro = 1;
                eeconfig_update_keymap(keymap_config.raw);
            }
            return false;
        case EXT_PLV:
            if (record->event.pressed) {
                #ifdef AUDIO_ENABLE
                    PLAY_SONG(plover_gb_song);
                #endif
                layer_move(get_highest_layer(default_layer_state));
            }
            return false;
        case DB_TOGG:   /* fall thru */
        case AG_NORM:   /* fall thru */
        case AG_SWAP:   /* fall thru */
        case AU_ON:     /* fall thru */
        case AU_OFF:
            if (!record->event.pressed) {
                layer_off(_ADJST);      /* make ADJST key behaves like one-shot layer */
            }
            break;
        case M_UNDO:    /* fall thru */
        case M_CUT:     /* fall thru */
        case M_COPY:    /* fall thru */
        case M_PASTE:   /* fall thru */
        case M_SELAL:   /* fall thru */
        case M_ZMIN:    /* fall thru */
        case M_ZMOUT:
            switch (detected_host_os()) {
                case OS_LINUX:
                    process_osd_keys(keycode, record, 0);
                    break;
                case OS_IOS:        /* fall thru */
                case OS_MACOS:
                    process_osd_keys(keycode, record, 2);
                    break;
                case OS_WINDOWS:    /* fall thru */
                default:
                    process_osd_keys(keycode, record, 1);
            }
            return false;
    }
    return true;
}

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (muse_mode) {
        if (IS_LAYER_ON(_RAISE)) {
            if (clockwise) {
                muse_offset++;
            } else {
                muse_offset--;
            }
        } else {
            if (clockwise) {
                muse_tempo+=1;
            } else {
                muse_tempo-=1;
            }
        }
    } else {
        if (clockwise) {
            #ifdef MOUSEKEY_ENABLE
                tap_code(KC_MS_WH_DOWN);
            #else
                tap_code(KC_PGDN);
            #endif
        } else {
            #ifdef MOUSEKEY_ENABLE
                tap_code(KC_MS_WH_UP);
            #else
                tap_code(KC_PGUP);
            #endif
        }
    }
    return true;
}

bool dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0: {
#ifdef AUDIO_ENABLE
            static bool play_sound = false;
#endif
            if (active) {
#ifdef AUDIO_ENABLE
                if (play_sound) { PLAY_SONG(plover_song); }
#endif
                layer_on(_ADJST);
            } else {
#ifdef AUDIO_ENABLE
                if (play_sound) { PLAY_SONG(plover_gb_song); }
#endif
                layer_off(_ADJST);
            }
#ifdef AUDIO_ENABLE
            play_sound = true;
#endif
            break;
        }
        case 1:
            if (active) {
                muse_mode = true;
            } else {
                muse_mode = false;
            }
    }
    return true;
}

void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    } else {
        if (muse_counter) {
            stop_all_notes();
            muse_counter = 0;
        }
    }
#endif
}

bool music_mask_user(uint16_t keycode) {
    switch (keycode) {
        case TL_UPPR:   /* fall thru */
        case TL_LOWR:
            return false;
        default:
            return true;
    }
}

