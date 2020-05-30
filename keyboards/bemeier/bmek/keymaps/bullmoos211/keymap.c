/* Copyright 2019 bemeier
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

#define _______ KC_TRNS

enum layers_idx {
    _BL = 0, // Base Layer
    _WL,    // Windows Modifiers Layer (Switched around LGUI, LALT, LCTL)
    _MF,   // Function Layer
    _WF,  // OS Layer, switching workspaces, media keys, etc.
    _CL  // Keyboard Config Layer
};

enum custom_keycodes {
    TOG_OS = BM_SAFE_RANGE,
    ATAB_I,
    ATAB_D
};

static bool is_alt_tab_active = false;
static uint16_t alt_tab_timer = 0;

// Space hold function layer
#define MF_SPC LT(_MF, KC_SPC)
#define WF_SPC LT(_WF, KC_SPC)

#define MF_B SCMD_T(KC_B) // GUI + SHIFT, or B WHEN TAPPED
#define WF_B C_S_T(KC_B) // CONTROL + SHIFT, or B WHEN TAPPED

// OS-specific shortucts, macOS
#define MN_UP LCTL(KC_UP)
#define MN_LEFT LCTL(KC_LEFT)
#define MN_RGHT LCTL(KC_RGHT)
#define MN_DOWN LCTL(KC_DOWN)
#define MN_SRCH LGUI(KC_SPC)
#define MN_CESC MT(MOD_LGUI, KC_ESC)
#define MN_UNDO LGUI(KC_Z)
#define MN_COPY LGUI(KC_C)
#define MN_CUT LGUI(KC_X)
#define MN_PASTE LGUI(KC_V)

#define WN_UP LGUI(LCTL(KC_UP))
#define WN_LEFT LGUI(LCTL(KC_LEFT))
#define WN_RGHT LGUI(LCTL(KC_RGHT))
#define WN_DOWN LGUI(LCTL(KC_DOWN))
#define WN_SRCH LGUI(KC_S)
#define WN_CESC MT(MOD_LCTL, KC_ESC)
#define WN_UNDO LCTL(KC_Z)
#define WN_COPY LCTL(KC_C)
#define WN_CUT LCTL(KC_X)
#define WN_PASTE LCTL(KC_V)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
   [_BL] = LAYOUT(\
 KC_MPLY,  KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,  KC_EQL, KC_BSLS,  KC_GRV, \
 KC_PGUP,  KC_TAB,     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,          KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_LBRC, KC_RBRC,   KC_BSPC, \
 KC_PGDN, KC_LCTL,      KC_A,    KC_S,    KC_D,    KC_F,    KC_G,          KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,         KC_ENT, \
 MO(_MF), KC_LSFT,       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,          KC_B,    KC_N,  KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_RSFT,  MO(_MF), \
                     KC_LGUI, KC_LALT,           KC_SPC,                         KC_SPC,          KC_RALT, KC_RCTL \
),
   [_MF] = LAYOUT(\
 _______,   RESET,   KC_F1,  KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,  _______,  _______, \
 _______, _______,   _______,   KC_UP,  _______, KC_MPRV, KC_PSCR,       _______, _______, _______, _______, KC_MPLY, KC_HOME,  KC_END,    KC_DEL, \
 _______, _______,   KC_LEFT,  KC_DOWN, KC_RGHT, KC_MNXT, _______,        _______, _______, _______, _______, _______,     _______,       KC_RCTL, \
 _______, _______,   KC_SLEP,  _______, _______, _______, _______,      _______, _______,  KC_MUTE, KC_VOLD, KC_VOLU, _______, _______,   _______, \
                     _______, _______,          _______,                        _______,          _______, _______ \
) };

// Handling default layers is done here in the _user function.
// In the _kb functions (see bmek.c) the BM_ keycodes are handled.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case ATAB_D: // Handle "alt-tab" behaviour
    case ATAB_I: // see https://beta.docs.qmk.fm/features/feature_macros#super-alt-tab
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          // Use CMD or ALT depending on OS layer
          switch (biton32(default_layer_state)) {
            case _WL:
                    register_code(KC_LALT);
                    break;
            case _BL:
                    register_code(KC_LGUI);
                    break;
          }
        }
        alt_tab_timer = timer_read();
        // Add shift if we cycle backwards.
        if (keycode == ATAB_D) register_code(KC_LSFT);
        register_code(KC_TAB);
      } else {
        if (keycode == ATAB_D) unregister_code(KC_LSFT);
        unregister_code(KC_TAB);
      }
      return true;
    case TOG_OS: // Toggle macOS/windows modifiers
      if (record->event.pressed) break;
      switch (biton32(default_layer_state)) {
      case _BL:
        set_single_persistent_default_layer(_WL);
        return false;
      case _WL:
      default:
        set_single_persistent_default_layer(_BL);
        return false;
      }
    break;
  }
  return true;
}

void matrix_init_user(void) {}

void matrix_scan_user(void) {
  // Alt tab behaviour. Need to release the modifier after some time.
  if (is_alt_tab_active && timer_elapsed(alt_tab_timer) > 500) {
    is_alt_tab_active = false;
    switch (biton32(default_layer_state)) {
      case _WL:
              unregister_code(KC_LALT);
              break;
      case _BL:
              unregister_code(KC_LGUI);
              break;
    }
  }
}
