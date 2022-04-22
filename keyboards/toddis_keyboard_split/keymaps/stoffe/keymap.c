// Copyright 2021 torbjorn rasmusson (@torbjorn rasmuss
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "keymap_swedish.h"


enum layers { BASE, LAY0, LAY1, LAY2, LAY3, LAY4, LAY5, LAY6 };

enum custom_keycodes {
  M_NAME = SAFE_RANGE,
  COMM,     // , | <
  DOT,      // . | >
  SLSH,     // / | ?
  SCLN,     // ; | :
  QUOT,     // ' | "
  M_CD_DOT,
  M_GIT_ST,
  O_LINECMD,
};


enum unicode_names {
  UKB,
  UCOFFEE,
  UVOLT,
  UBEER,
  UTHMUP,
  USMIL,
  UBIC,
  UNERD,
  UBUG,
  UPARTY,
  UORHEART,
  UWHALE,
  UBOMB,
  UFACE_ROLLING_EYES,
  THNK,
  PARTY,
  O_LINE
};

const uint32_t PROGMEM unicode_map[] = {
  [UKB]     = 0x2328,   // ⌨
  [UCOFFEE] = 0x2615,   // ☕
  [UVOLT]   = 0x26A1,   // ⚡
  [UBEER]   = 0x1F37B,  // 🍻
  [UTHMUP]  = 0x1F44D,  // 👍
  [USMIL]   = 0x1F642,  // 🙂
  [UBIC]    = 0x1F6B2,  // 🚲
  [UNERD]   = 0x1F913,  // 🤓
  [UBUG]    = 0x1F41B,  // 🐛
  [UPARTY]  = 0x1F389,  // 🎉
  [UORHEART] = 0x1F9E1, // 🧡
  [UWHALE] = 0x1F433,   // 🐳
  [UBOMB] = 0x1F4A3,    // 💣
  [UFACE_ROLLING_EYES] = 0x1F644, // 🙄
  [THNK] = 0x1F914, // 🤔
  [PARTY] = 0x1F973, // 🥳
  [O_LINE] = 0x235C, // ⍜
};

// SWEDISH LETTERS AND SYMBOLS
// Letters
#define KC_SE_AA KC_LBRC               // Å
#define KC_SE_AE KC_QUOT               // Ä
#define KC_SE_OE KC_SCLN               // Ö
#define KC_SE_QUO KC_BSLS              // '
#define KC_SE_COL S(KC_DOT)            // :
#define KC_SE_SEMI S(KC_COMM)          // ;
#define KC_SE_EXCL S(KC_1)             // !
#define KC_SE_DQUO S(KC_2)             // "
#define KC_SE_HASH S(KC_3)             // #
#define KC_SE_PERC S(KC_5)             // %
#define KC_SE_AMPR S(KC_6)             // &
#define KC_SE_SLSH S(KC_7)             // /
#define KC_SE_LPRN S(KC_8)             // (
#define KC_SE_RPRN S(KC_9)             // )
#define KC_SE_EQAL S(KC_0)             // =
#define KC_SE_CIRC S(KC_RBRACKET)      // ^
#define KC_SE_AT RALT(KC_2)            // @
#define KC_SE_DLR RALT(KC_4)           // $
#define KC_SE_LCBR RALT(KC_7)          // {
#define KC_SE_LBRC RALT(KC_8)          // [
#define KC_SE_RBRC RALT(KC_9)          // ]
#define KC_SE_RCBR RALT(KC_0)          // }
#define KC_SE_TILD RALT(KC_RBRACKET)   // ~
#define KC_SE_DIAE KC_RBRACKET         // ¨
#define KC_SE_ACUT KC_EQL              // ´
#define KC_SE_MINS KC_SLASH            // -
#define KC_SE_GRAV KC_PLUS             // `
#define KC_SE_LESS KC_NUBS             // <
#define KC_SE_MORE S(KC_NUBS)          // >
#define KC_SE_PLUS KC_MINS             // +
#define KC_SE_ASTR S(KC_BSLS)          // *
#define KC_SE_QUES S(KC_MINS)          // ?
#define KC_SE_BSLH RALT(KC_MINS)       /* \ */
#define KC_SE_PIPE RALT(KC_NUBS)       // |


#define CTL_KC_I RCTL_T(KC_I)
#define CTL_KC_R LCTL_T(KC_R)

#define SHFT_KC_A LSFT_T(KC_A)
#define SHFT_KC_O RSFT_T(KC_O)

#define CTLZ LCTL(KC_Z)
#define CTLX LCTL(KC_X)
#define CTLC LCTL(KC_C)
#define CTLV LCTL(KC_V)

#define U_RDO C(KC_Y)
#define U_PST S(KC_INS)
#define U_CPY C(KC_INS)
#define U_CUT S(KC_DEL)
#define U_UND C(KC_Z)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//   __  _   _____
//  / _)/_| ( (_
// /(_)(  |__)/__

    [BASE] = LAYOUT(
    // left hand
    KC_ESC,  KC_Q, KC_W, KC_F, KC_P, KC_B,
    KC_LALT,  SHFT_KC_A, CTL_KC_R, KC_S, KC_T, KC_G,
    KC_LWIN,  KC_Z, KC_X, KC_C, KC_D, KC_V,
      LT(LAY0, KC_BSPC ),LT(LAY1, KC_DEL ),LT(LAY2, KC_TAB),

    // right hand
    KC_J,  KC_L, KC_U, KC_Y, SCLN, QUOT,
    KC_M,  KC_N, KC_E, CTL_KC_I, SHFT_KC_O, KC_RALT,
    KC_K,  KC_H, COMM, DOT, SLSH, KC_LWIN,
    LT(LAY3, KC_ENT),  LT(LAY4, KC_SPC ), LT(LAY5, KC_LWIN )
    ),
//      _        __
//  /  /_|(__/  /  )
// (__(  | /   (__/

    [LAY0] = LAYOUT(
    // left hand6
    RESET,  _______, _______, _______, _______, _______,
    _______,  KC_LSPO, KC_LCTL, KC_LALT, _______, _______,
    _______,  _______, _______, _______, _______, _______,
    _______, _______, _______,

    // right hand
    KC_SE_PLUS,  KC_7, KC_8, KC_9, SLSH, _______,
    KC_SE_MINS,  KC_4, KC_5, KC_6, COMM, _______,
    KC_SE_EQAL,  KC_1, KC_2, KC_3, DOT, _______,
    KC_SE_LPRN,  KC_0, KC_SE_RPRN
    ),
//      _
//  /  /_|(__/ -/
// (__(  | /   /

    [LAY1] = LAYOUT(
    // left hand
    _______,  _______, _______, _______,_______ ,_______ ,
    _______,  KC_LSPO, KC_LCTL, KC_LALT,_______ , _______,
    _______,  _______, _______, _______,_______, _______,
    _______, _______, _______,

    // right hand
    KC_PGUP, KC_HOME, KC_UP, KC_END, KC_INS, _______,
    KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, M_GIT_ST, _______,
    U_CUT,   U_CPY, U_PST, U_RDO ,U_UND, M_CD_DOT,
    KC_SE_LCBR,  _______, KC_SE_RCBR
    ),
//      _
//  /  /_|(__/  _)
// (__(  | /   /__

    [LAY2] = LAYOUT(
    // left hand
    _______,  _______, _______, _______, KC_SE_DQUO, _______,
    _______,  KC_LSPO, KC_LCTL, KC_LALT, KC_SE_DIAE, KC_SE_ACUT,
    _______,  _______, _______, _______, _______, _______,
    _______, _______, _______,
    // right hand
    KC_SE_QUO,  KC_SE_AMPR, KC_SE_ASTR, KC_SE_BSLH, _______, KC_SE_GRAV,
    KC_SE_COL,  KC_SE_DLR,  KC_SE_PERC, KC_SE_CIRC, _______, _______,
    KC_SE_TILD, KC_SE_EXCL, KC_SE_AT, KC_SE_HASH, KC_SE_PIPE, _______,
    KC_SE_LBRC, KC_SE_MINS, KC_SE_RBRC
    ),
//      _       _
//  /  /_|(__/  _)
// (__(  | /   __)

    [LAY3] = LAYOUT(
    // left hand
    _______,  _______, _______, KC_MUTE, _______, KC_VOLU,
    _______,  _______, KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLD,
    _______,  _______, _______, _______, _______, _______,
    	               _______, _______, _______,
    // right hand
    _______,KC_F9, KC_F10, KC_F11, KC_F12, _______,
    _______,KC_F5, KC_F6 , KC_F7 , KC_F8 , _______,
    _______,KC_F1, KC_F2 , KC_F3 , KC_F4 , _______,
    KC_TAB,  KC_SPC, KC_ESC

    ),
//      _
//  /  /_|(__/ (_/
// (__(  | /    /

    [LAY4] = LAYOUT(
    // left hand
    _______,  _______, _______, _______, _______, _______,
    _______,  _______, KC_SE_AA, KC_SE_AE, KC_SE_OE, _______,
    _______,  _______, _______, _______, _______, _______,
    	               _______, _______, _______,

    // right hand
    _______,  _______, _______, _______, _______, _______,
    _______,  KC_LSPO, KC_LCTL, KC_LALT, _______, _______,
    _______,  _______, _______, _______, _______, _______,
    	               _______, _______, _______
    ),
//      _       __
//  /  /_|(__/ /_
// (__(  | /   __)

    [LAY5] = LAYOUT(
    // left hand
    X(USMIL),  X(UKB), X(UCOFFEE), X(UVOLT), X(UBEER), X(UTHMUP),
    X(THNK),  X(PARTY), KC_SE_AA, KC_SE_AE, KC_SE_OE, TG(LAY6),
    X(UBOMB),   X(UORHEART), X(UBIC), X(UNERD),   X(UBUG), X(UPARTY),
    _______, _______, _______,

    // right hand
    O_LINECMD,  X(O_LINE), _______, _______, _______, RESET,
    _______, X(UWHALE), X(UBOMB), X(UFACE_ROLLING_EYES), X(THNK), _______,
    _______,  _______, _______, _______, _______, _______,
    _______,  _______, _______
    ),

//    LAY 6

    [LAY6] = LAYOUT(
    // left hand
    _______,  KC_PGUP, _______, KC_UP, _______, _______,
    _______,  KC_PGDN, KC_LEFT, KC_DOWN , KC_RGHT, TG(LAY6),
    _______,  _______, _______, _______, _______, _______,
    _______,  _______, _______,

    // right hand
    KC_SE_PLUS,  KC_7, KC_8, KC_9, _______, _______,
    KC_SE_MINS,  KC_4, KC_5, KC_6, COMM, _______,
    KC_SE_EQAL,  KC_1, KC_2, KC_3, DOT, _______,
    _______,  KC_0, _______
    )

};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//   #ifdef CONSOLE_ENABLE
//     uprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
//   #endif
switch (keycode) {
    case M_NAME:
      if (record->event.pressed) {
          SEND_STRING("Kristoffer");
      }
      return false;
      break;
    case M_CD_DOT:
      if (record->event.pressed) {
          SEND_STRING("cd .."SS_TAP(X_ENTER)"");
      }
      return false;
      break;
    case O_LINECMD:
      if (record->event.pressed) {
          send_unicode_string("TH⍜SE");
      }
      return false;
      break;
    case M_GIT_ST:
      if (record->event.pressed) {
          SEND_STRING("git status"SS_TAP(X_ENTER)"");
      }
      return false;
      break;
    case COMM:    // , | <
      if (record->event.pressed){
        if (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT)){
            unregister_code16(KC_LSFT);  // Remove shift before sending the keycode
            register_code16(SE_LABK);
            register_code16(KC_LSFT);
        } else {
          register_code16(KC_COMM);
        }
      } else {
        unregister_code16(KC_GRV);
        unregister_code16(SE_LABK);
        unregister_code16(KC_COMM);
      }
      return false;
      break;

    case DOT:    // . | >
      if (record->event.pressed){
        if (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT)){
            register_code16(SE_RABK);
        } else {
          register_code16(KC_DOT);
        }
      } else {
        unregister_code16(KC_GRV);
        unregister_code16(SE_RABK);
        unregister_code16(KC_DOT);
      }
      return false;
      break;

    case SLSH:    // / | ?
      if (record->event.pressed){
        if (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT)){
          register_code16(SE_QUES);
        } else {
          register_code16(SE_SLSH);
        }
      } else {
        unregister_code16(SE_QUES);
        unregister_code16(SE_SLSH);
      }
      return false;
      break;

    case SCLN:    // ; | :
      if (record->event.pressed){
        if (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT)){
          register_code16(SE_COLN);
        } else {
          register_code16(SE_SCLN);
        }
      } else {
        unregister_code16(SE_COLN);
        unregister_code16(SE_SCLN);
      }
      return false;
      break;

    case QUOT:    // ' | "
      if (record->event.pressed){
        if (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT)){
          register_code16(SE_DQUO);
        } else {
          register_code16(SE_QUOT);
        }
      } else {
        unregister_code16(SE_DQUO);
        unregister_code16(SE_QUOT);
      }
      return false;
      break;

    }
    return true;
}

const rgblight_segment_t PROGMEM my_base_layer[] = RGBLIGHT_LAYER_SEGMENTS(
		{0,4,HSV_OFF}
	);

const rgblight_segment_t PROGMEM my_layer0_layer[] = RGBLIGHT_LAYER_SEGMENTS(
        {0,4,HSV_GREEN}
	);

const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
		{0,4,HSV_ORANGE}
	);

const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
		{0,4,HSV_BLUE}
	);

const rgblight_segment_t PROGMEM my_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS(
		{0,4,HSV_PURPLE}
	);

const rgblight_segment_t PROGMEM my_layer4_layer[] = RGBLIGHT_LAYER_SEGMENTS(
		{0,4,HSV_TURQUOISE}
	);

const rgblight_segment_t PROGMEM my_layer5_layer[] = RGBLIGHT_LAYER_SEGMENTS(
		{0,4,HSV_RED}
	);

const rgblight_segment_t PROGMEM my_layer6_layer[] = RGBLIGHT_LAYER_SEGMENTS(
		{0,4,HSV_TURQUOISE}
	);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
		my_base_layer,
		my_layer0_layer,
		my_layer1_layer,
		my_layer2_layer,
		my_layer3_layer,
		my_layer4_layer,
		my_layer5_layer,
		my_layer6_layer
	);

//Set the appropriate layer color
layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, BASE));
    rgblight_set_layer_state(1, layer_state_cmp(state, LAY0));
    rgblight_set_layer_state(2, layer_state_cmp(state, LAY1));
    rgblight_set_layer_state(3, layer_state_cmp(state, LAY2));
    rgblight_set_layer_state(4, layer_state_cmp(state, LAY3));
    rgblight_set_layer_state(5, layer_state_cmp(state, LAY4));
    rgblight_set_layer_state(6, layer_state_cmp(state, LAY5));
    rgblight_set_layer_state(7, layer_state_cmp(state, LAY6));
    return state;
}

void keyboard_post_init_user(void) {
	//Enable the LED layers
	rgblight_layers = my_rgb_layers;
}
