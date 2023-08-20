 /* Copyright 2020 Josef Adamcik
  * Modification for VIA support and RGB underglow by Jens Bonk-Wiltfang
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
#define L1_SPC LT(2, KC_SPC)
#define L2_BSPC LT(3, KC_BSPC)
#define DF_GAMES DF(GAMES)
#define DF_QWERT DF(QWERT)
#define MT_LSHN MT(MOD_LSFT, KC_ENT)
#define MT_RSHN MT(MOD_RSFT, KC_ENT)
#define MS_BTN1 KC_MS_BTN1
#define MS_BTN2 KC_MS_BTN2
#define MS_BTN3 KC_MS_BTN3
#define MS_W_UP KC_MS_WH_UP
#define MS_W_DN KC_MS_WH_DOWN
#define MS_UP KC_MS_UP
#define MS_DOWN KC_MS_DOWN
#define MS_LEFT KC_MS_LEFT
#define MS_RGHT KC_MS_RIGHT

enum LAYERS {
  QWERT, // All the bells and whistles for coding.
  GAMES, // Simpler control scheme for games (e.g. space is just space).
  FUNCS, // Function keys (e.g. screen brightness, media keys).
  CNTRL, // Controls for the keyboard (e.g. brightness, colours) and mouse (buttons and movement).
};

#include "os_detection.h" // Detect which OS we're talking to.
#include "state.h"   // Include the global state that the pet looks at.
#include "luna.h"    // Include the pet you want.
#include "pet.h"     // Include the pet library.
#include "oled.h"    // Include the oled (call the pet from here).

enum custom_keycodes {
    NONE = SAFE_RANGE,
};

enum combo_events {
  USR_CUT,
  USR_COPY,
  USR_PASTE,
};

// Set up combos with modifiers.
const uint16_t PROGMEM cut_combo[] = {KC_LCTL, KC_X, COMBO_END};
const uint16_t PROGMEM copy_combo[] = {KC_LCTL, KC_C, COMBO_END};
const uint16_t PROGMEM paste_combo[] = {KC_LCTL, KC_V, COMBO_END};

combo_t key_combos[] = {
  [USR_CUT] = COMBO_ACTION(cut_combo),
  [USR_COPY] = COMBO_ACTION(copy_combo),
  [USR_PASTE] = COMBO_ACTION(paste_combo),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [QWERT] = { ENCODER_CCW_CW(KC_VOLU, KC_VOLD), ENCODER_CCW_CW(KC_DOWN, KC_UP) },
    [GAMES] = { ENCODER_CCW_CW(KC_VOLU, KC_VOLD), ENCODER_CCW_CW(KC_DOWN, KC_UP) },
    [FUNCS] = { ENCODER_CCW_CW(MS_RGHT, MS_LEFT), ENCODER_CCW_CW(MS_DOWN, MS_UP) },
    [CNTRL] = { ENCODER_CCW_CW(KC_RGHT, KC_LEFT), ENCODER_CCW_CW(KC_DOWN, KC_UP) },
};
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[QWERT] = LAYOUT(
   KC_GRV,     KC_1,     KC_2,     KC_3,     KC_4,     KC_5,                         KC_6,     KC_7,     KC_8,     KC_9,     KC_0,  KC_MINS,
   KC_TAB,     KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,                         KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,   KC_EQL,
   KC_ESC,     KC_A,     KC_S,     KC_D,     KC_F,     KC_G,                         KC_H,     KC_J,     KC_K,     KC_L,  KC_SCLN,  KC_QUOT,
  MT_LSHN,     KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,  KC_MUTE,  MS_BTN1,     KC_N,     KC_M,  KC_COMM,   KC_DOT,  KC_SLSH,  MT_RSHN,
                      KC_BSLS,  KC_LALT,  KC_LCTL,  KC_LGUI,   L1_SPC,  L2_BSPC,   L1_SPC,  KC_PGUP,  KC_PGDN,  KC_BSLS
),
[GAMES] = LAYOUT(
   KC_GRV,     KC_1,     KC_2,     KC_3,     KC_4,     KC_5,                         KC_6,     KC_7,     KC_8,     KC_9,     KC_0,  KC_MINS,
   KC_TAB,     KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,                         KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,   KC_EQL,
   KC_ESC,     KC_A,     KC_S,     KC_D,     KC_F,     KC_G,                         KC_H,     KC_J,     KC_K,     KC_L,  KC_SCLN,  KC_QUOT,
  KC_LSFT,     KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,  KC_MUTE,  MS_BTN1,     KC_N,     KC_M,  KC_COMM,   KC_DOT,  KC_SLSH,   KC_ENT,
                      KC_BSLS,  KC_LALT,  KC_LCTL,  KC_LGUI,   KC_SPC,  KC_BSPC,   L1_SPC,  KC_PGUP,  KC_PGDN,  KC_BSLS
),
[FUNCS] = LAYOUT(
  _______,    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,                        KC_F6,    KC_F7,    KC_F8,    KC_F9,   KC_F10,   KC_F11,
  _______,  XXXXXXX,    KC_UP,  XXXXXXX,  KC_LBRC,  KC_RBRC,                      MS_W_DN,  MS_W_UP,  XXXXXXX,  XXXXXXX,  XXXXXXX,   KC_F12,
  _______,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_HOME,   KC_END,                      MS_LEFT,  MS_DOWN,    MS_UP,  MS_RGHT,  XXXXXXX,  XXXXXXX,
  _______,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MINS,   KC_EQL, DF_QWERT,  MS_BTN1,  MS_BTN1,  MS_BTN3,  MS_BTN2,  XXXXXXX,  KC_BSLS,  _______,
                      _______,  _______,  _______,  _______,  _______,   KC_DEL,  _______,  _______,  _______,  _______
),
[CNTRL] = LAYOUT(
  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                      XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_LBRC,  KC_RBRC,  XXXXXXX,
  XXXXXXX,  XXXXXXX,    MS_UP,  XXXXXXX,  XXXXXXX,  XXXXXXX,                      XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  XXXXXXX,  MS_LEFT,  MS_DOWN,  MS_RGHT,  XXXXXXX,  XXXXXXX,                      KC_LEFT,  KC_DOWN,    KC_UP,  KC_RGHT,  XXXXXXX,  XXXXXXX,
  MT_LSHN,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, DF_GAMES,  MS_BTN1,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  MT_RSHN,
                      XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX
)
};

void tap_super_with_key(uint16_t keycode, bool pressed) {
  os_variant_t host_os = detected_host_os();
  uint16_t to_tap = C(keycode);
  if (host_os == OS_MACOS || host_os == OS_IOS) {
    to_tap = G(keycode);
  }
  if (pressed) {
    register_code(to_tap);
  } else {
    unregister_code(to_tap);
  }
}

void process_combo_event(uint16_t combo_index, bool pressed) {
  // Map combos to custom keys.
  switch(combo_index) {
    case USR_CUT:
      tap_super_with_key(KC_X, pressed);
      break;
    case USR_COPY:
      tap_super_with_key(KC_C, pressed);
      break;
    case USR_PASTE:
      tap_super_with_key(KC_V, pressed);
      break;
  }
}

bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    /* Disable combos when gaming layer is the default */
    return default_layer_state != GAMES;
}

bool data_reset;
uint16_t data_in;
uint16_t message_counter = 0;

uint16_t data_index = 0;

bool led_update_user(led_t led_state) {
  // I can now send two bits of data at a time!
  // caps + num 0 = 0
  // caps + num 1 = 1
  // no caps = ignore (i.e. it's a clock).
  /*
  data_str[0] = led_state.num_lock    ? 'n' : ' ';
  data_str[1] = led_state.caps_lock   ? 'C' : ' ';
  data_str[2] = led_state.scroll_lock ? 's' : ' ';
  data_str[3] = led_state.kana        ? 'k' : ' ';
  data_str[4] = led_state.compose     ? 'c' : ' ';
  data_str[5] = '\0';
  */
  if (led_state.num_lock) {
    uint16_t signal = led_state.caps_lock;
    if (data_reset) {
      if (signal == 1) {
        data_reset = false;
      }
      return true;
    }
    data_in = (data_in << 1) | signal;
    message_counter++;

    if (message_counter == 8) {
      if (data_in == 0) { // reset.
        for(int i = 0; i < DATA_LEN; i++) {
          data_str[i] = ' ';
        }
        data_index = 0;
        message_counter = 0;
        data_reset = true;
      } else {
        data_str[data_index] = data_in;
        data_in = 0;
        data_index++;
        data_index = data_index%(DATA_LEN-1);
        message_counter = 0;
      }
    }
  }

  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
            /* Smart Backspace Delete */
        case KC_RSFT:
        case KC_LSFT:
            // Set shift status for other modules to use.
            if (record->event.pressed) {
              shift_held++;
            } else {
              shift_held--;
            }
            break;
        case KC_LCTL:
        case KC_RCTL:
            update_pet_sneaking(record->event.pressed);
            break;
        case L1_SPC:
        case KC_SPC:
            if (record->event.pressed) {
              fn_held++;
            } else {
              fn_held--;
            }
            update_pet_jump(record->event.pressed);
            break;
    }
    return true;
}
