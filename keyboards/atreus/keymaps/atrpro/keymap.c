// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _DV 0
#define _DL 1
#define _DR 2
#define _DA 3
#define _QW 4
#define _QR 5
#define _QL 6

#define _____   KC_TRNS

#define ALBSPC  ALT_T(KC_BSPC)
#define ALT_ENT ALT_T(KC_ENT)
#define ALT_ESC ALT_T(KC_ESC)
#define CT_A    CTL_T(KC_A)
#define CT_ENT  CTL_T(KC_ENT)
#define CT_ESC  CTL_T(KC_ESC)
#define CT_QUOT CTL_T(KC_QUOT)
#define CT_Z    CTL_T(KC_Z)
#define DL_BSPC LT(_DL, KC_BSPC)
#define DR_SPC  LT(_DR, KC_SPC)
#define GI_Q    LGUI_T(KC_Q)
#define QR_SPC  LT(_QR, KC_SPC)
#define SH_ENT  SFT_T(KC_ENT)
#define SH_ESC  SFT_T(KC_ESC)
#define SH_Z    SFT_T(KC_Z)
#define SH_SLSH SFT_T(KC_SLSH)
#define TAB_ALT MT(MOD_LALT,KC_TAB)
#define ESC_SHIFT MT(MOD_LSFT,KC_ESC)
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /*
   *  q        w        e         r        t             ||          y        u       i         o        p
   *  a        s        d         f        g             ||          h        j       k         l        ;
   *  z        x        c         v        b             ||          n        m       ,         .        \
   * Esc/shift Tab/alt   ctrl      raise    gui   enter   ||bkspace   space    rsise   [        ]         \
   */
  [_DV] = LAYOUT(
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,   KC_U,    KC_I,    KC_O,    KC_P   ,
    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN   ,
    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH   ,
    ESC_SHIFT,TAB_ALT,  KC_LCTL, MO(_DR), KC_LGUI, KC_BSPC, KC_ENT,  KC_SPC, MO(_DR), KC_LBRC, KC_RBRC, KC_BSLS ),

  [_DL] = LAYOUT( /* [> LOWER <] */
    KC_ESC,  KC_PSCR, KC_PAUS, KC_F1, KC_F2,                    KC_F3,  KC_F4,  KC_INS,  KC_DELT, KC_BSPC ,
    KC_CLCK, KC_TAB,  KC_PGUP, KC_F5, KC_F6,                    KC_F7,  KC_F8,  KC_HOME, KC_LALT, KC_ENT  ,
    KC_LSFT, KC_SLCK, KC_PGDN, KC_F9, KC_F10,                   KC_F11, KC_F12, KC_END,  KC_MINS, KC_SLSH ,
    _____,   _____,   _____,   _____, _____,  KC_LCTL, KC_LALT, _____,  _____,  KC_APP,  _____,   _____   ),

  /*
   *  1        2       3        4         5             ||           6        7       8       9         0
   *  esc      Left     Down     Right    $             ||           left     down    up      right     ;
   *  [        ]        (        )        &             ||           `        1       2       3         backtic
   * shift      Ins      Win     Shift     gui   enter    || bkspacr   Spc     ALT/Ent   -       =         mod
   */
  [_DR] = LAYOUT( /* [> RAISE <] */
    KC_1, KC_2,   KC_3,   KC_4, KC_5,                              KC_6, KC_7,    KC_8,   KC_9,   KC_0 ,
    KC_ESC, KC_LEFT, KC_DOWN, KC_RGHT, KC_DLR,                    KC_LEFT, KC_DOWN, KC_UP,  KC_RGHT,KC_QUOT ,
    KC_LBRC, KC_RBRC, KC_LPRN, KC_RPRN, KC_AMPR,                   KC_GRV,  KC_1,    KC_2,   KC_3,   KC_GRV ,
    KC_LSFT, KC_INS,  KC_LGUI, KC_LSFT, KC_LGUI, KC_ENT, KC_BSPC, KC_SPC,  ALT_ENT, KC_MINUS,   KC_EQUAL, MO(_QR) ),

  /*
   *  Ins    Home       Up       End      PgUp          ||          Up       F7       F8       F9      F10
   *  Del    Left      Down      Right    PgDown        ||         Down      F4       F5       F6      F11
   *         VolUp                        RESET         ||        QWERTY     F1       F2       F3      F12
   *         VolDn      Win      Shift    Bspc   DVORAK || Ctrl    space   ALT/Ent   PrtSc   ScrLk    Pause
   */
  [_DA] = LAYOUT( /* [> ADJUST <] */
    KC_INS,  KC_HOME, KC_UP,   KC_END,  KC_PGUP,                   KC_UP,   KC_F7,   KC_F8,   KC_F9,   KC_F10  ,
    KC_DELT, KC_LEFT, KC_DOWN, KC_RGHT, KC_DOWN,                   KC_DOWN, KC_F4,   KC_F5,   KC_F6,   KC_F11  ,
    KC_NO,   KC_VOLU, KC_NO,   KC_NO,   RESET,                     TO(_QW), KC_F1,   KC_F2,   KC_F3,   KC_F12  ,
    KC_NO,   KC_VOLD, KC_LGUI, KC_LSFT, KC_BSPC, KC_LCTL, TO(_DV), KC_SPC,  ALT_ENT, KC_PSCR, KC_SLCK, KC_PAUS ),

  [_QW] = LAYOUT(
    KC_Q,   KC_W,   KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P    ,
    KC_A,   KC_S,   KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN ,
    CT_Z,   KC_X,   KC_C,    KC_V,    KC_B,                     KC_N,    KC_M,    KC_COMM, KC_DOT,  SH_SLSH ,
    KC_ESC, KC_TAB, KC_LGUI, SH_ESC,  ALBSPC, KC_LCTL, MO(_QR), QR_SPC,  ALT_ENT, KC_MINS, KC_SLSH, KC_ENT ),

  [_QR] = LAYOUT(
    RESET, KC_AT,   KC_UP,   KC_LCBR, KC_RCBR,                   KC_BSLS, KC_7,    KC_8,   KC_9,   KC_ASTR ,
    KC_HASH, KC_LEFT, KC_DOWN, KC_RGHT, KC_DLR,                    KC_EQL,  KC_4,    KC_5,   KC_6,   KC_PLUS ,
    KC_LBRC, KC_RBRC, KC_LPRN, KC_RPRN, KC_AMPR,                   KC_GRV,  KC_1,    KC_2,   KC_3,   KC_PGUP ,
    TO(_QL), KC_INS,  KC_LGUI, KC_LSFT, KC_DELT, KC_LCTL, KC_TRNS, KC_SPC,  ALT_ENT, KC_0,   KC_DOT, KC_PGDN ),

  [_QL] = LAYOUT(
    _____,   _____,   _____,   _____, _____,                  _____,   _____,   TO(_DV),   _____, _____,  
    _____,   _____,   _____,   _____, _____,                  KC_LEFT, KC_DOWN, KC_UP,  KC_RGHT  _____ ,
    _____,   _____,   _____,   _____, _____,                  _____,   _____,   _____,   _____, _____,  
   ESC_SHIFT,_____,   _____,   _____, _____, _____,   _____,  _____,   _____,   _____,   _____, _____, ),
};

const uint16_t PROGMEM fn_actions[] = {

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  // MACRODOWN only works in this function
  switch(id) {
    case 0:
      if (record->event.pressed) {
        register_code(KC_RSFT);
      } else {
        unregister_code(KC_RSFT);
      }
    break;
  }
  return MACRO_NONE;
};
