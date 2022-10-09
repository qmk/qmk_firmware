/* Copyright 2019 ashlar 2021 peepeetee, deadolus
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
#include "keymap.h"

#ifdef TAP_DANCE_ENABLE
enum {
  TD_HOME_END,
};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //tap once for home, twice for end
  [TD_HOME_END] = ACTION_TAP_DANCE_DOUBLE(KC_HOME, KC_END)
};
#endif


// // Defines names for use in layer keycodes and the keymap
enum  layers {
  _BL,
  _RED_,
  _GREEN_,
  _BLUE_,
  _CYAN_,
  _MAGENTA_,
  _YELLOW_
};



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /*
   * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
   * │   │   │   │   │   │   │   │   │   │   │   │   │   │       │   │
   * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
   * │     │   │   │   │   │   │   │   │   │   │   │   │   │     │   │
   * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    ├───┤
   * │      │   │   │   │   │   │   │   │   │   │   │   │   │    │   │
   * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┼───┤
   * │    │   │   │   │   │   │   │   │   │   │   │   │      │   │   │
   * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┼───┼───┤
   * │    │    │    │                        │   │   │   │   │   │   │
   * └────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┴───┘
   */
#ifdef TAP_DANCE_ENABLE
  /* 0: ISO qwerty */
  [_BL] = LAYOUT_65_iso_blocker(
      KC_CAPS, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,      KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,      KC_LBRC, KC_RBRC,          TD(TD_HOME_END),
      KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,   KC_QUOT, KC_NUHS, KC_ENT,  KC_PGUP,
      KC_LSPO, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,    KC_SLSH, KC_RSPC, KC_UP,   KC_PGDN,
      KC_LCTL, KC_LGUI, KC_LAPO,                   KC_SPC,                             KC_RAPC, MO(_RED_),          KC_LEFT, KC_DOWN, KC_RGHT

      ),
#else
  [_BL] = LAYOUT_65_iso_blocker(
      KC_CAPS, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,      KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,      KC_LBRC, KC_RBRC,          KC_HOME,
      KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,   KC_QUOT, KC_NUHS, KC_ENT,  KC_PGUP,
      KC_LSPO, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,    KC_SLSH, KC_RSPC, KC_UP,   KC_PGDN,
      KC_LCTL, KC_LGUI, KC_LAPO,                   KC_SPC,                             KC_RAPC, MO(_RED_),          KC_LEFT, KC_DOWN, KC_RGHT

      ),
#endif

  [_RED_] = LAYOUT_65_iso_blocker(
      KC_GRV,  KC_F1,       KC_F2,      KC_F3,      KC_F4,         KC_F5,        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, LGUI(KC_END),
      _______, _______,     _______,    _______,    _______,       _______,      _______, _______, _______, _______, _______, _______, _______,          LGUI(KC_PAUSE),
      _______, TO(_GREEN_), TO(_BLUE_), TO(_CYAN_), TO(_MAGENTA_), TO(_YELLOW_), _______, _______, _______, _______, _______, _______, _______, TO(0),   _______,
      _______, _______,     _______,    _______,    _______,       _______,      _______, _______, _______, _______, _______, _______, _______, KC_VOLU, _______,
      QK_BOOT, _______,     _______,                               KC_LEAD,                                 _______, _______,          KC_MPLY, KC_VOLD, KC_MUTE
      ),


  [_GREEN_] = LAYOUT_65_iso_blocker(
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, KC_PGDN, KC_PGUP, KC_PSCR, _______, _______, _______,          _______,
      _______, KC_ACL0, KC_ACL1, KC_ACL2, _______, _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_BTN1, KC_BTN2, _______, TO(0),   _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_END,  _______, _______, _______, _______,
      _______, _______, _______,                   _______,                            _______, _______,          _______, _______, _______
      ),


  [_BLUE_] = LAYOUT_65_iso_blocker(
      _______, DM_PLY1, DM_PLY2, _______, _______, _______, _______, _______, KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS, _______, _______, _______,
      _______, DM_REC1, DM_REC2, _______, _______, _______, _______, _______, _______, KC_P7,   KC_P8,   KC_P9,   KC_PMNS,          _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_P4,   KC_P5,   KC_P6,   KC_PPLS, TO(0),   _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_P1,   KC_P2,   KC_P3,   KC_PENT, _______, _______,
      _______, _______, _______,                   _______,                            KC_0,    KC_PCMM,          _______, _______, _______
      ),
  [_CYAN_] = LAYOUT_65_iso_blocker(
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, TO(0),   _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______,                   _______,                            _______, _______,          _______, _______, _______
      ),
  [_MAGENTA_] = LAYOUT_65_iso_blocker(
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, TO(0),   _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______,                   _______,                            _______, _______,          _______, _______, _______
      ),
  [_YELLOW_] = LAYOUT_65_iso_blocker(
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, TO(0),   _______,
      _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, _______, _______, _______, _______, _______,
      _______, _______, _______,                   _______,                            _______, _______,          _______, _______, _______
      ),

  /*template
    [_UL] = LAYOUT_65_iso_blocker(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, TO(0),   _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______,                   _______,                            _______, _______,          _______, _______, _______
    )
    */
};

#ifdef _______
#undef _______
#define _______ {0, 0, 0}

const uint8_t PROGMEM ledmap[][3] = {
  [_BL] = _______,
  [_RED_] = RED,
  [_GREEN_] = GREEN,
  [_BLUE_] = BLUE,
  [_CYAN_] = CYAN,
  [_MAGENTA_] = MAGENTA,
  [_YELLOW_] = YELLOW
};

#undef _______
#define _______ KC_TRNS
#endif



void keyboard_post_init_user(void) {
  // Call the post init code.
#ifdef CONSOLE_ENABLE
  debug_enable=true;
  debug_matrix=true;
#endif
  rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef CONSOLE_ENABLE
  //useful for getting matrix right
  uprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif

  switch (keycode) {
    case RGB_TOG:
      if (record->event.pressed) {
        switch (rgb_matrix_get_flags()) {
          case LED_FLAG_ALL: {
                               rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR);
                               rgb_matrix_set_color_all(0, 0, 0);
                             }
                             break;
          case (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR): {
                                                                               rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                                                                               rgb_matrix_set_color_all(0, 0, 0);
                                                                             }
                                                                             break;
          case LED_FLAG_UNDERGLOW: {
                                     rgb_matrix_set_flags(LED_FLAG_NONE);
                                     rgb_matrix_disable_noeeprom();
                                   }
                                   break;
          default: {
                     rgb_matrix_set_flags(LED_FLAG_ALL);
                     rgb_matrix_enable_noeeprom();
                   }
                   break;
        }
      }
      return false;
    default:
      return true; // Process all other keycodes normally
  }
}

void setCapsLock(void) {
  led_t host_leds = host_keyboard_led_state();
  if (host_leds.caps_lock) {
    rgb_matrix_set_color(30, 0xFF, 0xFF, 0xFF);

  } else {
    //if capslock is not pressed don't clear it, it might be used for displaying led pattern
    if((rgb_matrix_get_flags() != LED_FLAG_ALL)) {
      rgb_matrix_set_color(30, 0x0, 0x0, 0x0);
    }
  }
}

void set_layer_color(int layer) {
  int ledkey=0;
  for(int i=0; i<MATRIX_COLS*MATRIX_ROWS;i++) {
    uint8_t row = i/MATRIX_COLS;
    uint8_t col=(i-(i/MATRIX_COLS)*MATRIX_COLS);
    uint16_t key=pgm_read_word(&keymaps[layer][row][col]);
    //continue if this is not a valid key
    if(key==KC_NO) { continue; }
    //clear key if it is only a transition
    if ((key == KC_TRNS)) {
      if(rgb_matrix_get_flags() != LED_FLAG_ALL){
        rgb_matrix_set_color(ledkey, 0, 0, 0);
      }
    }else {
      //this key does something - light it up
      HSV hsv = {
        .h = pgm_read_byte(&ledmap[layer][0]),
        .s = pgm_read_byte(&ledmap[layer][1]),
        .v = pgm_read_byte(&ledmap[layer][2]),
      };

      RGB rgb = hsv_to_rgb(hsv);
      float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
      if( (layer != 0) || (rgb_matrix_get_flags() != LED_FLAG_ALL))
        rgb_matrix_set_color(ledkey, f * rgb.r, f * rgb.g, f * rgb.b);
    }
    //if we are on layer 0 set capslock to correct status
    if(layer==0 && i==30) { setCapsLock(); }
    ledkey++;
  }
  return;
}

void rgb_matrix_indicators_user(void) {
  set_layer_color(get_highest_layer(layer_state));

}

#ifdef LEADER_ENABLE
LEADER_EXTERNS();

//SEND_STRING seems to be local dependent.
//For swiss-german layout I have to send "ctrl+." to get ":"
void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    SEQ_ONE_KEY(KC_F) {
      // Anything you can do in a macro.
      SEND_STRING("QMK is awesome.");
    }
    SEQ_TWO_KEYS(KC_D, KC_D) {
      SEND_STRING(SS_LCTL("a") SS_LCTL("c"));
    }
    SEQ_THREE_KEYS(KC_D, KC_D, KC_S) {
      SEND_STRING("https");
      register_code(KC_LSFT);
      SEND_STRING(".77");
      unregister_code(KC_LSFT);
      SEND_STRING("start.duckduckgo.com\n");
    }
  }
}
#endif
