/* Copyright 2022 Jens Peter Secher <jpsecher@gmail.com>
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

// #include "features/layer_lock.h"
// enum custom_keycodes {
//   LAYERLCK = SAFE_RANGE,
// };

enum layer_names {
  _ALPHA,
  _NAVI,
  _SYM_NUM,
  _FUNC
};

#define BASE TO(_ALPHA)
#define LOCK_NAV TO(_NAVI)
#define LOCK_SYM TO(_SYM_NUM)
#define MO_SYM MO(_SYM_NUM)

// Thumbs
#define OSM_SALT OSM(MOD_LSFT|MOD_LALT)
#define OSM_LSFT OSM(MOD_LSFT)
#define OSL_NAV OSL(_NAVI)
#define OSL_SYM OSL(_SYM_NUM)
#define OSM_RSFT OSM(MOD_RSFT)
#define SPC_RSFT RSFT_T(KC_SPACE)
#define TAB_SYM LT(_SYM_NUM, KC_TAB)
#define SPC_NAV LT(_NAVI, KC_SPC)
#define SPC_CHNG LT(_FUNC, KC_SPC)

#define SPC_CTL LCTL_T(KC_SPC)
#define DEL_GUI LGUI_T(KC_DEL)
#define DEL_CTL LCTL_T(KC_DEL)
#define OSM_ALT OSM(MOD_LALT)
#define OSM_CTL OSM(MOD_LCTL)
#define ESC_CTL LCTL_T(KC_ESC)
#define ESC_AGR RALT_T(KC_ESC)
#define BS_GUI LGUI_T(KC_BSPC)
#define BS_CTL LCTL_T(KC_BSPC)
#define BS_NAV LT(_NAVI, KC_BSPC)
#define SPC_SYM LT(_SYM_NUM, KC_SPC)
#define BS_SYM LT(_SYM_NUM, KC_BSPC)
#define SPC_GUI LGUI_T(KC_SPC)
#define NUL_GUI LGUI_T(KC_0)
#define OSM_AGR OSM(MOD_RALT)
#define TAB_ALT LALT_T(KC_TAB)
#define END_ALT LALT_T(KC_END)
#define ENT_CTL LCTL_T(KC_ENT)

// Alpha lower home row mods
#define Z_GUI LGUI_T(KC_Z)
#define X_ALT LALT_T(KC_X)
#define C_SYM LT(_SYM_NUM, KC_C)
#define V_CTL LCTL_T(KC_V)
#define G_AGR RALT_T(KC_G)
#define GRV_AGR RALT_T(KC_GRV)
#define H_AGR RALT_T(KC_H)
#define M_CTL RCTL_T(KC_M)
#define COMM_SYM LT(_SYM_NUM, KC_COMM)
#define COMM_ALT LALT_T(KC_COMM)
#define DOT_SYM LT(_SYM_NUM, KC_DOT)
#define DOT_ALT LALT_T(KC_DOT)
#define SLSH_GUI RGUI_T(KC_SLSH)
#define BSLS_GUI RGUI_T(KC_BSLS)
#define J_GUI RGUI_T(KC_J)

// Navigation macros & lower home row mods
#define UNDO LCTL(KC_Z)
#define CUT LCTL(KC_X)
#define COPY LCTL(KC_C)
#define PASTE LCTL(KC_V)
#define QUIT LCTL(KC_Q)
#define CLOSE LCTL(KC_W)
#define FIND LCTL(KC_F)
#define ALL LCTL(KC_A)
#define SAVE LCTL(KC_S)
#define MARK LCTL(KC_D)
#define CTLU LCTL(KC_U)
#define PREFIX LCTL(KC_K)
#define CTLP LCTL(KC_P)
#define CTLR LCTL(KC_R)
#define CTLL LCTL(KC_L)
#define CTLE LCTL(KC_E)
#define CTLN LCTL(KC_N)
#define CTLM LCTL(KC_M)
#define CTLU LCTL(KC_U)
#define CTLY LCTL(KC_Y)
#define CTLO LCTL(KC_O)
#define BUILD LCTL(KC_B)
#define SWITCH LALT(KC_O)
#define HOME_CTL RCTL_T(KC_HOME)
#define PGDN_SYM LT(_SYM_NUM, KC_PGDN)
#define PGDN_CTL RCTL_T(KC_PGDN)
#define PGUP_ALT LALT_T(KC_PGUP)
#define PGUP_SYM LT(_SYM_NUM, KC_PGUP)
#define END_GUI RGUI_T(KC_END)
#define BSLS_AGR RALT_T(KC_BSLS)
#define SLSH_AGR RALT_T(KC_SLSH)

// Symbols lower home row mods
#define LBRC_GUI LGUI_T(KC_LBRC)
#define RBRC_ALT LALT_T(KC_RBRC)
#define LBRC_AGR RALT_T(KC_LBRC)
#define NULL_AGR RALT_T(KC_0)
#define SCLN_CTL LCTL_T(KC_SCLN)
#define QUOT_AGR RALT_T(KC_QUOT)
#define MINS_AGR RALT_T(KC_MINS)
#define ONE_CTL RCTL_T(KC_1)
#define TWO_AGR RALT_T(KC_2)
#define THRE_ALT LALT_T(KC_3)
#define EQL_GUI RGUI_T(KC_EQL)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_ALPHA] = LAYOUT(
    XXXXXXX,  KC_Q,     KC_W,     KC_B,     KC_R,     KC_F,       KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     XXXXXXX,
    KC_TAB,   KC_A,     KC_S,     KC_D,     KC_T,     G_AGR,      H_AGR,    KC_N,     KC_E,     KC_L,     KC_K,     KC_ENT,
              Z_GUI,    X_ALT,    C_SYM,    V_CTL,                          M_CTL,    COMM_SYM, DOT_ALT,  J_GUI,
              KC_MNXT,  LOCK_NAV, OSM_LSFT, BASE,     XXXXXXX,    XXXXXXX,  QK_GESC,  SPC_CHNG, KC_BSPC,  KC_MPLY,  DB_TOGG
  ),
  [_NAVI] = LAYOUT(
    XXXXXXX,  CTLY,     KC_ACL0,  KC_ACL1,  KC_MS_L,  KC_BTN1,    KC_HOME,  KC_WH_D,  KC_WH_U,  KC_MS_R,  KC_WH_U,  XXXXXXX,
    _______,  UNDO,     CUT,      COPY,     PASTE,    KC_BTN2,    KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_END,   _______,
              KC_LGUI,  KC_LALT,  MO_SYM,   KC_LCTL,                        PGDN_CTL, PGUP_SYM, KC_LALT,  KC_LGUI,
              _______,  _______,  _______,  _______,  XXXXXXX,    XXXXXXX,  _______,  _______,  _______,  _______,  EE_CLR
  ),
  [_SYM_NUM] = LAYOUT(
    XXXXXXX,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,  KC_DQUO,    KC_UNDS,  KC_7,     KC_8,     KC_9,     KC_ASTR,  XXXXXXX,
    KC_EXLM,  KC_LCBR,  KC_RCBR,  KC_LPRN,  KC_RPRN,  QUOT_AGR,   MINS_AGR, KC_4,     KC_5,     KC_6,     KC_PLUS,  KC_SLSH,
              LBRC_GUI, RBRC_ALT, KC_COLN,  SCLN_CTL,                       ONE_CTL,  KC_2,     THRE_ALT, EQL_GUI,
              KC_VOLD,  KC_LT,    KC_COMM,  KC_GT,    XXXXXXX,    XXXXXXX,  KC_QUES,  _______,  KC_0,     KC_VOLU,  QK_BOOT
  ),
  [_FUNC] = LAYOUT(
    XXXXXXX,  QUIT,     CLOSE,    BUILD,    CTLU,     FIND,       KC_CIRC,  KC_F7,    KC_F8,    KC_F9,    KC_F11,   XXXXXXX,
    SWITCH,   ALL,      SAVE,     MARK,     CTLE,     PREFIX,     KC_GRV,   KC_F4,    KC_F5,    KC_F6,    KC_F12,   KC_BSLS,
              KC_LGUI,  KC_LALT,  CTLL,     KC_LCTL,                        KC_F1,    KC_F2,    KC_F3,    KC_DOT,
              KC_MPRV,  KC_PIPE,  OSM_LSFT, KC_AMPR,  XXXXXXX,    XXXXXXX,  KC_PWR,   _______,  KC_F10,   KC_MNXT,  XXXXXXX
  )
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // if (!process_layer_lock(keycode, record, LAYERLCK)) {
  //   return false;
  // }
  // Store the current modifier state in the variable for later reference.
  static uint8_t mod_state;
  mod_state = get_mods();
  switch (keycode) {
    case KC_BSPC:
      {
      // Keep track of whether the delete key status is registered.
      static bool delkey_registered;
      if (record->event.pressed) {
        if (mod_state & MOD_MASK_SHIFT) {
          // Make sure that Shift is not applied to the KC_DEL keycode.
          del_mods(MOD_MASK_SHIFT);
          register_code(KC_DEL);
          // Update the boolean variable to reflect the status of KC_DEL
          delkey_registered = true;
          // Reapplying modifier state so that the held shift key(s)
          // still work even after having tapped the Backspace/Delete key.
          set_mods(mod_state);
          return false;
        }
      } else { // on release of KC_BSPC
        // In case KC_DEL is still being sent even after the release of KC_BSPC
        if (delkey_registered) {
          unregister_code(KC_DEL);
          delkey_registered = false;
          return false;
        }
      }
    }
  }
  return true;
}

// void matrix_scan_user(void) {
//   layer_lock_task();
// }


// layer_state_t layer_state_set_user(layer_state_t state) {
//     switch (get_highest_layer(state)) {
//     case _NAVI:
//         writePin(D1, !led_state.num_lock);
//         break;
//     case _SYM_NUM:
//         break;
//     // How to detect Caps Word?
//     default: //  for any other layers, or the default layer
//         break;
//     }
//   return state;
// }
