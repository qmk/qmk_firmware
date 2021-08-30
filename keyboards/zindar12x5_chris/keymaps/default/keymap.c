/* Copyright 2019 'Erik Bågfors'
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
#include <print.h>
#include "vimmode.h"

#include QMK_KEYBOARD_H

#define GUITAB LGUI(KC_TAB)
#define NXTTAB LCTL(KC_TAB)
#define PRVTAB LCTL(LSFT(KC_TAB))
#define NXTDSK LCTL(KC_RGHT)
#define PRVDSK LCTL(KC_LEFT)
#define NXTECL LALT(LGUI(KC_RGHT))
#define PRVECL LALT(LGUI(KC_LEFT))

// IntelijJ IDEA CE = IJC
#define NXTIJC LGUI(KC_RBRC)
#define PRVIJC LGUI(KC_LBRC)

#define WORDL LALT(KC_LEFT)
#define WORDR LALT(KC_RGHT)

// Specable bindings
#define UPLEFT LCTL(LALT(LGUI(LSFT(KC_LEFT))))
#define LOLEFT LCTL(LALT(LGUI(KC_LEFT)))
#define UPRGHT LCTL(LALT(LGUI(LSFT(KC_RGHT))))
#define LORGHT LCTL(LALT(LGUI(KC_RGHT)))
#define S_CENT LCTL(LALT(LGUI(LSFT(KC_C))))


static uint16_t space_cadet_control_timer = 0;

//Tap Dance Declarations
enum {
  TD_BACKSLASH_SWEAA = 0,
  TD_QUOT_SWEAE,
  TD_SCLN_OE
};

#define BSLH_AA TD(TD_BACKSLASH_SWEAA)
#define QUOT_AE TD(TD_QUOT_SWEAE)
#define SCLN_OE TD(TD_SCLN_OE)


enum layers {
  _COLEMAK,
  _QWERTY,
  _SWE,
  _SWE_CMK,
  _L1,
  _L2,
  _L3,
  _VIM
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Qwerty
 * ,-------------------------------------------------------------------------------------.
 * | ` Esc|   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |  Bksp  |
 * |------+------+------+------+------+------+------+------+------+------+------+--------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  \|    |
 * |------+------+------+------+------+-------------+------+------+------+------+--------|
 * |VimEsc|   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |   '    |
 * |------+------+------+------+------+------|------+------+------+------+------+--------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Sft/Ent |
 * |------+------+------+------+------+------+------+------+------+------+------+--------|
 * | LAY_3| Ctrl | Alt  | GUI  | = /L1| Ctrl |Space |-/L2  | GUI  |ALT/Å |  Ä   |   Ö    |
 * `-------------------------------------------------------------------------------------'
 */
/*
[_QWERTY] = LAYOUT( \
  KC_GESC,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_BSPC, \
  KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_BSLASH,  \
  VIM_ESC,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT, \
  KC_LSFT,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  SFT_ENT,  \
  LAY_3,     KC_LCTL, KC_LALT, KC_LGUI, L1_EQL, KC_LCTRL, KC_SPC,  MIN_L2,  KC_RGUI, ALT_AA  ,SWE_AE,   SWE_OE  \
  ),
 [_COLEMAK] = LAYOUT( \
  _______, _______, _______ , _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______,  KC_F ,   KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y   , KC_SCLN, _______, \
  _______, _______, KC_R ,    KC_S,    KC_T,    KC_D,    KC_H   , KC_N,    KC_E,    KC_I,    KC_O,   _______, \
  _______, _______, _______ , _______, _______, _______, KC_K,    _______, _______, _______, _______, _______, \
  _______, _______, _______ , _______, _______, _______, _______, _______, _______, _______, _______, _______ \
  ),
  */

[_COLEMAK] = LAYOUT( \
  KC_GESC,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_BSPC, \
  KC_TAB,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    SCLN_OE,  BSLH_AA,  \
  VIM_ESC,   KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,     QUOT_AE, \
  KC_LSFT,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  SFT_ENT,  \
  LAY_3,     KC_LCTL, KC_LALT, KC_LGUI, L1_EQL, KC_LCTRL, KC_SPC,  MIN_L2,  KC_RGUI, ALT_AA  ,SWE_AE,   SWE_OE  \
  ),
 [_QWERTY] = LAYOUT( \
  _______, _______, _______ , _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______,  KC_E ,   KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O   , KC_P,    KC_BSLASH, \
  _______, _______, KC_S ,    KC_D,    KC_F,    KC_G,    KC_H   , KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT, \
  _______, _______, _______ , _______, _______, _______, KC_N,    _______, _______, _______, _______, _______, \
  _______, _______, _______ , _______, _______, _______, _______, _______, _______, _______, _______, _______ \
  ),
 /* Swedish locked layer
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |  Å   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |   Ö  |  Ä   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |  \|  |  '"  |  ;:  |
 * `-----------------------------------------------------------------------------------'
 */
[_SWE] = LAYOUT( \
  _______, _______, _______ , _______, _______, _______, _______, _______, _______, _______,   _______,  _______, \
  _______, _______, _______ , _______, _______, _______, _______, _______, _______, _______,   _______,  SWE_AA, \
  _______, _______, _______ , _______, _______, _______, _______, _______, _______, _______,   SWE_OE,   SWE_AE, \
  _______, _______, _______ , _______, _______, _______, _______, _______, _______, _______,   _______,  _______, \
  _______, _______, _______ , _______, _______, _______, _______, _______, _______, KC_BSLASH, KC_QUOT,  KC_SCLN \
  ),
[_SWE_CMK] = LAYOUT( \
  _______, _______, _______ , _______, _______, _______, _______, _______, _______, _______,   _______,  _______, \
  _______, _______, _______ , _______, _______, _______, _______, _______, _______, _______,   SWE_OE,   SWE_AA, \
  _______, _______, _______ , _______, _______, _______, _______, _______, _______, _______,   _______,  SWE_AE, \
  _______, _______, _______ , _______, _______, _______, _______, _______, _______, _______,   _______,  _______, \
  _______, _______, _______ , _______, _______, _______, _______, _______, _______, KC_BSLASH, KC_QUOT,  KC_SCLN \
  ),

 /* Layer 1
 * ,-----------------------------------------------------------------------------------.
 * |   `  |      |      |      |      |      |      |      |      |  -   |  =   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |ALTTAB|      |  MU  |      | MUP  |      |      |      |      |  {   |  }   |   Å  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  ML  |  MD  |  MR  | MDOWN|      | LEFT | DOWN |  UP  |RIGHT |  Ö   |   Ä  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |  MB1 |  MB2 |      |WORDL |      |      |WORDR |      |TGSWE |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      | :(   |  :)  |  :p  | TGSWE|
 * `-----------------------------------------------------------------------------------'
 */
[_L1] = LAYOUT( \
  KC_GRAVE,TG(_QWERTY),  _______  ,  XXXXXXX,     XXXXXXX,    XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX, KC_MINUS, KC_EQL,   KC_DEL, \
  GUITAB,  XXXXXXX,      KC_MS_UP ,  XXXXXXX,     KC_WH_U,    XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX, KC_LCBR,  KC_RCBR,  SWE_AA, \
  XXXXXXX, KC_MS_LEFT,   KC_MS_DOWN, KC_MS_RIGHT, KC_WH_D,    XXXXXXX,   KC_LEFT,   KC_DOWN,   KC_UP,   KC_RGHT,  SWE_OE,   SWE_AE, \
  _______, XXXXXXX,      XXXXXXX ,   KC_MS_BTN1,  KC_MS_BTN2, XXXXXXX,   WORDL,     XXXXXXX,   XXXXXXX, WORDR,    _______,  TG(_SWE_CMK), \
  _______, _______,      _______ ,   _______,     _______,    _______,   _______,   _______,   SAD,     HAPPY,   TONGUE,    TG(_SWE) \
  ),

 /* Layer 2
 * ,-----------------------------------------------------------------------------------.
 * |  ~   |PRVDSK|NXTDSK|      |      |      |      |      |      |  _   |  =   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |PRVTAB|NXTTAB|      |      |      |      |      |      |      |  [   |  ]   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |PRVIJC|NXTIJC|      |      |      |      |      |      |      |      |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      | F12  |
 * `-----------------------------------------------------------------------------------'
 */

[_L2] = LAYOUT( \
  KC_TILD, PRVDSK,  NXTDSK,  _______, _______, _______, _______, _______,   _______,   S(KC_MINUS), S(KC_EQL),  _______, \
  _______, PRVTAB,  NXTTAB,  _______, _______, _______, _______, _______,   _______,   KC_LBRC,     KC_RBRC,    _______, \
  _______, PRVIJC,  NXTIJC,  _______, _______, _______, _______, _______,   _______,   _______,     S(KC_QUOT), _______, \
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,     KC_F8,     KC_F9,       KC_F10,     KC_F11, \
  _______, _______, _______, _______, _______, _______, _______, _______,   _______,   _______,     _______,    KC_F12 \
  ),
 /* Layer 3
 * ,-----------------------------------------------------------------------------------.
 * |RESET |UPLEFT|UPRGHT|S_CENT|      |      |      |      |      |      |      | DEL  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |LOLEFT|LORGHT|      |      |      |      |  7   |  8   |  9   |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |BRIGHT| VOL+ |      |      |      |      |      |  4   |  5   |  6   |   *  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |BRIGHT| VOL- |  <<  |  >|  |  >>  |      |      |  1   |  2   |  3   |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |  0   |  .   |  +   |   -  |Enter |
 * `-----------------------------------------------------------------------------------'
 */
[_L3] = LAYOUT( \
  RESET,   UPLEFT,  UPRGHT, S_CENT , _______, _______, _______, _______, _______,   _______, _______,   KC_DEL, \
  _______, LOLEFT,  LORGHT, _______, _______, _______, _______, KC_KP_7, KC_KP_8,   KC_KP_9, _______,   _______, \
  KC_BRIU, KC_VOLU, _______, _______, _______, _______, _______, KC_KP_4, KC_KP_5,   KC_KP_6, KC_PAST,   _______, \
  KC_BRID, KC_VOLD, KC_MRWD, KC_MPLY, KC_MFFD, _______, _______, KC_KP_1, KC_KP_2,   KC_KP_3, KC_PSLS,   KC_PENT, \
  _______, _______, _______, _______, _______, _______, _______, KC_KP_0, KC_PDOT,   KC_PPLS, KC_PMNS,   KC_PENT \
  ),

[_VIM] = LAYOUT( \
  _______, _______, _______, _______, _______, _______, _______, _______, _______,   _______, _______,   _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______,   _______, _______,   _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______,   _______, _______,   _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______,   _______, _______,   KC_RSFT, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______,   _______, _______,   _______ \
  )
};

/*
void mod_type(uint16_t modcode, uint16_t keycode) {
  register_mods(MOD_BIT(modcode));
  register_code(keycode);
  unregister_code(keycode);
  unregister_mods(MOD_BIT(modcode));
}
*/

void send_oe(void) {
    bool lshift = L_SHIFT_HELD;
    bool rshift = R_SHIFT_HELD;
    if (lshift)
       unregister_mods(MOD_BIT(KC_LSFT));
    if (rshift)
       unregister_mods(MOD_BIT(KC_RSFT));
    if (lshift || rshift)
       SEND_STRING(SS_LALT("u")"O");
    else
       SEND_STRING(SS_LALT("u")"o");
    if (lshift)
       register_mods(MOD_BIT(KC_LSFT));
    if (rshift)
       register_mods(MOD_BIT(KC_RSFT));
}

void send_ae(void) {
    bool lshift = L_SHIFT_HELD;
    bool rshift = R_SHIFT_HELD;
    if (lshift)
      unregister_mods(MOD_BIT(KC_LSFT));
    if (rshift)
      unregister_mods(MOD_BIT(KC_RSFT));
    if (lshift || rshift)
      SEND_STRING(SS_LALT("u")"A");
    else
      SEND_STRING(SS_LALT("u")"a");
    if (lshift)
      register_mods(MOD_BIT(KC_LSFT));
    if (rshift)
      register_mods(MOD_BIT(KC_RSFT));
}

void dance_aa_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code (KC_BSLASH);
  } else {
    SEND_STRING(SS_LALT("a"));
  }
}

void dance_aa_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (KC_BSLASH);
  } else {
  }
}

void dance_ae_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code (KC_QUOT);
  } else {
    send_ae();
  }
}

void dance_ae_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (KC_QUOT);
  } else {
  }
}

void dance_oe_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code (KC_SCLN);
  } else {
    send_oe();
  }
}

void dance_oe_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (KC_SCLN);
  } else {
  }
}


qk_tap_dance_action_t tap_dance_actions[] = {
 [TD_BACKSLASH_SWEAA] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_aa_finished, dance_aa_reset),
 [TD_QUOT_SWEAE] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_ae_finished, dance_ae_reset),
 [TD_SCLN_OE] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_oe_finished, dance_oe_reset)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  bool vim_handled = handle_vim_mode(keycode, record, _VIM);
  if (vim_handled)
    return false;

  switch (keycode) {
    case SWE_OE:
      if (record->event.pressed) {
          send_oe();
      }
      break;
    case SWE_AE:
      if (record->event.pressed) {
          send_ae();
      }
      break;
    case SWE_AA:
      if (record->event.pressed) {
        SEND_STRING(SS_LALT("a"));
      }
      break;
    case ALT_AA:
      if (record->event.pressed) {
        space_cadet_control_timer = timer_read();
        register_mods(MOD_BIT(KC_RALT));
      }
      else {
        unregister_mods(MOD_BIT(KC_RALT));
        if (timer_elapsed(space_cadet_control_timer) < TAPPING_TERM) {
          mod_type(KC_RALT, KC_A);
//          SEND_STRING(SS_LALT("a"));
        }
      }
      break;
    case HAPPY: {
      if (!record->event.pressed) {
        SEND_STRING(":) ");
      }
      return false;
    }
    break;
    case SAD: {
      if (!record->event.pressed) {
        SEND_STRING(":( ");
      }
      return false;
    }
    break;
    case TONGUE: {
      if (!record->event.pressed) {
        SEND_STRING(":p ");
      }
      return false;
    }
    break;
  }
  return true;
}

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}
