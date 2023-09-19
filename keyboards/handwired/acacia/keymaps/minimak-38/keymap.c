/* Copyright 2023 Jens Peter Secher <jpsecher@gmail.com>
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

enum layer_names {
  _ALPHA,
  _NAVI,
  _SYM_NUM,
  _FUNC
};

#define MO_SYM MO(_SYM_NUM)
#define OSM_LSFT OSM(MOD_LSFT)
#define SPC_CHNG LT(_FUNC, KC_SPC)
#define LOCK_ALP TO(_ALPHA)
#define LOCK_NAV TO(_NAVI)
#define NUL_GUI LGUI_T(KC_0)
#define OSM_AGR OSM(MOD_RALT)
#define Z_GUI LGUI_T(KC_Z)
#define X_ALT LALT_T(KC_X)
#define C_SYM LT(_SYM_NUM, KC_C)
#define V_CTL LCTL_T(KC_V)
#define G_AGR RALT_T(KC_G)
#define H_AGR RALT_T(KC_H)
#define M_CTL RCTL_T(KC_M)
#define COMM_SYM LT(_SYM_NUM, KC_COMM)
#define DOT_ALT LALT_T(KC_DOT)
#define SLSH_GUI RGUI_T(KC_SLSH)
#define J_GUI RGUI_T(KC_J)
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
#define CTLJ LCTL(KC_J)
#define CTLG LCTL(KC_G)
#define CTLH LCTL(KC_H)
#define CTLTAB LCTL(KC_TAB)
#define CTLENT LCTL(KC_ENT)
#define BUILD LCTL(KC_B)
#define SWITCH LALT(KC_O)
#define PGDN_CTL RCTL_T(KC_PGDN)
#define PGUP_SYM LT(_SYM_NUM, KC_PGUP)
#define GRV_GUI RGUI_T(KC_GRV)
#define LBRC_ALT LALT_T(KC_LBRC)
#define RBRC_CTL LCTL_T(KC_RBRC)
#define LBRC_GUI LGUI_T(KC_LBRC)
#define RBRC_ALT LALT_T(KC_RBRC)
#define LBRC_AGR RALT_T(KC_LBRC)
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
              Z_GUI,    X_ALT,    C_SYM,    V_CTL,                          M_CTL,    KC_COMM,  DOT_ALT,  J_GUI,
              KC_MNXT,  LOCK_NAV, OSM_LSFT, LOCK_ALP, XXXXXXX,    XXXXXXX,  QK_GESC,  SPC_CHNG, KC_BSPC,  KC_MPLY,  DB_TOGG
  ),
  [_NAVI] = LAYOUT(
    XXXXXXX,  CTLY,     XXXXXXX,  KC_ACL0,  KC_ACL1,  KC_BTN1,    KC_HOME,  KC_WH_D,  KC_WH_U,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    _______,  UNDO,     CUT,      COPY,     PASTE,    KC_BTN2,    KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_END,   _______,
              KC_LGUI,  KC_LALT,  MO_SYM,   KC_LCTL,                        PGDN_CTL, KC_PGUP,  KC_LALT,  KC_LGUI,
              _______,  _______,  _______,  _______,  XXXXXXX,    XXXXXXX,  _______,  _______,  _______,  _______,  EE_CLR
  ),
  [_SYM_NUM] = LAYOUT(
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,    KC_BSLS,  KC_7,     KC_8,     KC_9,     KC_MINS,  XXXXXXX,
    KC_GRV,   XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_DOT,   OSM_AGR,    KC_QUOT,  KC_4,     KC_5,     KC_6,     KC_EQL,   KC_SCLN,
              GRV_GUI,  LBRC_ALT, _______,  RBRC_CTL,                       ONE_CTL,  KC_2,     THRE_ALT, SLSH_GUI,
              KC_VOLD,  KC_LCBR,  _______,  KC_RCBR,  XXXXXXX,    XXXXXXX,  KC_COMM,  _______,  KC_0,     KC_VOLU,  QK_BOOT
  ),
  [_FUNC] = LAYOUT(
    XXXXXXX,  QUIT,     CLOSE,    BUILD,    CTLR,     FIND,       CTLY,     KC_F7,    KC_F8,    KC_F9,    KC_F11,   XXXXXXX,
    CTLTAB,   ALL,      SAVE,     MARK,     CTLE,     CTLG,       CTLH,     KC_F4,    KC_F5,    KC_F6,    KC_F12,   CTLENT,
              KC_LGUI,  KC_LALT,  PREFIX,   KC_LCTL,                        KC_F1,    KC_F2,    KC_F3,    CTLJ,
              KC_MPRV,  SWITCH,   OSM_LSFT, CTLO,     XXXXXXX,    XXXXXXX,  KC_PWR,   _______,  KC_F10,   KC_MNXT,  XXXXXXX
  )
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
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
