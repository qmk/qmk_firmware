/* Copyright 2021 qpockets
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

// CAGS - Homerow mods - QWERTY
#define KC_CA  MT(MOD_LCTL, KC_A)
#define KC_AS  MT(MOD_LALT, KC_S)
#define KC_GD  MT(MOD_LGUI, KC_D)
#define KC_SF  MT(MOD_LSFT, KC_F)

#define KC_SJ  MT(MOD_RSFT, KC_J)
#define KC_GK  MT(MOD_RGUI, KC_K)
#define KC_AL  MT(MOD_RALT, KC_L)
#define KC_SS  MT(MOD_RCTL, KC_SCLN)

// CAGS - Homerow mods - COLEMAK
#define KC_AR  MT(MOD_LALT, KC_R)
#define KC_GS  MT(MOD_LGUI, KC_S)
#define KC_ST  MT(MOD_LSFT, KC_T)

#define KC_SN  MT(MOD_RSFT, KC_N)
#define KC_GE  MT(MOD_RGUI, KC_E)
#define KC_AI  MT(MOD_RALT, KC_I)
#define KC_SO  MT(MOD_RCTL, KC_O)

// Bottom Row
#define KC_DN_BSPC LT(_NUMNAV, KC_BSPC)
#define KC_UP_ENT LT(_SYM, KC_ENT)

// Tap Dance declarations
enum {
  TD_BRC, TD_ARR, TD_CRT, TD_PRN, TD_LNE
};

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_BRC] = ACTION_TAP_DANCE_DOUBLE(KC_LCBR, KC_RCBR),
  [TD_ARR] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_RBRC),
  [TD_CRT] = ACTION_TAP_DANCE_DOUBLE(KC_LT, KC_GT),
  [TD_PRN] = ACTION_TAP_DANCE_DOUBLE(KC_LPRN, KC_RPRN),
  [TD_LNE] = ACTION_TAP_DANCE_DOUBLE(KC_MINUS, KC_UNDS),
};

enum space_layers {
  _QWERTY,
  _COLEMAK,
  _NUMNAV,
  _SYM,
  _FUNCT
};

enum space_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK
};

enum combo_events {
 COMBO_BSPC,
 COMBO_ENT,
 COMBO_TAB,
 COMBO_ESC,
 COMBO_DEL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_default(
    KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   XXXXXXX,  KC_Y,   KC_U,   KC_I,    KC_O,   KC_P,
    KC_CA,  KC_AS,  KC_GD, KC_SF,   KC_G,   XXXXXXX,  KC_H,   KC_SJ,  KC_GK,   KC_AL,  KC_SS,
    KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   XXXXXXX,  KC_N,   KC_M,   KC_COMM, KC_DOT, KC_SLSH,
                  KC_LGUI, KC_BSPC, KC_DN_BSPC, KC_UP_ENT, KC_LEAD,   KC_MPLY
  ),

  [_COLEMAK] = LAYOUT_2u(
    KC_Q,   KC_W,   KC_F,   KC_P,   KC_G,   XXXXXXX,  KC_J,   KC_L,   KC_U,    KC_Y,   KC_SCLN,
    KC_CA,  KC_AR,  KC_GS,  KC_ST,  KC_D,   XXXXXXX,  KC_H,   KC_SN,  KC_GE,   KC_AI,  KC_SO,
    KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   XXXXXXX,  KC_K,   KC_M,   KC_COMM, KC_DOT, KC_SLSH,
                  KC_LGUI, KC_BSPC, KC_DN_BSPC, KC_UP_ENT, KC_LEAD,   KC_MPLY
  ),

  [_NUMNAV] = LAYOUT_2u(
    KC_BTN1, KC_BTN2, KC_7, KC_8, KC_9,   XXXXXXX,   KC_HOME, KC_PGDN, KC_PGUP,  KC_END,   XXXXXXX,
    KC_WH_U, XXXXXXX, KC_4, KC_5, KC_6,   XXXXXXX,   KC_LEFT, KC_DOWN, KC_UP,    KC_RIGHT, XXXXXXX,
    KC_WH_D, XXXXXXX, KC_1, KC_2, KC_3,   XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,
                  KC_TRNS, KC_0,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS
  ),

  [_SYM] = LAYOUT_2u(
    XXXXXXX, XXXXXXX, KC_AMPR, KC_ASTR, KC_LPRN,     KC_PIPE,    KC_TILD,    XXXXXXX, XXXXXXX,    XXXXXXX,
    XXXXXXX, XXXXXXX, KC_DLR,  KC_PERC, KC_CIRC,     TD(TD_BRC), TD(TD_PRN), KC_EQL,  TD(TD_CRT), KC_QUOT,
    XXXXXXX, XXXXXXX, KC_EXLM, KC_AT,   KC_HASH,     TD(TD_ARR), TD(TD_LNE), KC_PLUS, KC_GRV,     KC_BSLS,
                  KC_TRNS, KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS
  ),

  [_FUNCT] = LAYOUT_2u(
    XXXXXXX, XXXXXXX, XXXXXXX, RESET,   XXXXXXX,  XXXXXXX,   KC_F1,   KC_F2,  KC_F3,   KC_F4,  KC_F5,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DEBUG,    XXXXXXX,   KC_F6,   KC_F7,  KC_F8,   KC_F9,  KC_F10,
    DM_REC1, DM_RSTP, DM_PLY1, XXXXXXX, XXXXXXX,  XXXXXXX,   KC_F11,  KC_F12, XXXXXXX, QWERTY, COLEMAK,
                  KC_TRNS, KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS
  )
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _NUMNAV, _SYM, _FUNCT);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
        case QWERTY:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_QWERTY);
          }
          return false;
          break;
        case COLEMAK:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_COLEMAK);
          }
          return false;
          break;
        case _NUMNAV:
          if (record->event.pressed) {
            layer_on(_NUMNAV);
            update_tri_layer(_NUMNAV, _SYM, _FUNCT);
          } else {
            layer_off(_NUMNAV);
            update_tri_layer(_NUMNAV, _SYM, _FUNCT);
          }
          return false;
          break;
        case _SYM:
          if (record->event.pressed) {
            layer_on(_SYM);
            update_tri_layer(_NUMNAV, _SYM, _FUNCT);
          } else {
            layer_off(_SYM);
            update_tri_layer(_NUMNAV, _SYM, _FUNCT);
          }
          return false;
          break;
      }
    return true;
};

LEADER_EXTERNS();

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    SEQ_ONE_KEY(KC_C) {
      // copy
      SEND_STRING(SS_LGUI("c"));
    }
    SEQ_ONE_KEY(KC_X) {
      // cut
      SEND_STRING(SS_LGUI("x"));
    }
    SEQ_ONE_KEY(KC_V) {
      // paste
      SEND_STRING(SS_LGUI("v"));
    }
    SEQ_TWO_KEYS(KC_I, KC_I) {
      // open browser dev tools
      SEND_STRING(SS_LGUI(SS_LALT("i")));
    }
  }
}

#ifdef COMBO_ENABLE
const uint16_t PROGMEM combo_bspc[] = {KC_O, KC_P, COMBO_END};
const uint16_t PROGMEM combo_ent[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM combo_tab[] = {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM combo_esc[] = {KC_T, KC_Y, COMBO_END};
const uint16_t PROGMEM combo_del[] = {KC_Q, KC_W, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [COMBO_BSPC] = COMBO(combo_bspc,KC_BSPC),
  [COMBO_ENT] = COMBO(combo_ent,KC_ENT),
  [COMBO_TAB] = COMBO(combo_tab,KC_TAB),
  [COMBO_ESC] = COMBO(combo_esc,KC_ESC),
  [COMBO_DEL] = COMBO(combo_del,KC_DEL)
};
#endif
