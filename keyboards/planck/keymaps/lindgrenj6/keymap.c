/* Copyright 2015-2021 Jack Humbert
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

enum planck_layers {
  _BASE,
  _LOWER,
  _RAISE,
  _ADJUST,
  _NUMPAD,
  _EXTRA,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_planck_grid(
    KC_TAB,         KC_Q,          KC_W,           KC_E,     KC_R,           KC_T,           KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           LT(_BASE, KC_MINUS),
    MT(MOD_LCTL, KC_ESCAPE), KC_A, KC_S,           KC_D,     KC_F,           KC_G,           KC_H,           KC_J,           KC_K,           KC_L,           KC_SEMICOLON,   KC_QUOTE,
    KC_LSFT, MT(MOD_LCTL|MOD_LSFT ,KC_Z), KC_X,  KC_C,     KC_V,           KC_B,           KC_N,           KC_M,           KC_COMMA,       KC_DOT,         KC_SLASH,       KC_INSERT,
    LT(_EXTRA, KC_GRAVE), TG(_NUMPAD), KC_LGUI,    KC_LALT,  LT(_LOWER, KC_BSPC), KC_SPACE,  KC_SPACE, LT(_RAISE, KC_ENTER), KC_LEFT,        KC_DOWN,        KC_UP,          KC_RIGHT
  ),

  [_LOWER] = LAYOUT_planck_grid(
    KC_TILDE, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, LT(KC_LBRC, KC_7), LT(KC_RBRC, KC_8), KC_MINUS,      KC_UNDS,        LT(KC_PGUP, KC_HOME),
    _______, _______, _______, _______, _______, _______, KC_PIPE, KC_LCBR,           KC_RCBR,           KC_PLUS,        KC_EQUAL,       LT(KC_PGDN, KC_END),
    _______, _______, _______, _______, _______, _______, _______, KC_LPRN,           KC_RPRN,           _______,        KC_BSLS,        KC_DELETE,
    _______, _______, _______, _______, _______, _______, _______, _______,           C(S(KC_LEFT)),     C(KC_MINUS),    C(S(KC_PLUS)), C(S(KC_RIGHT))
  ),

  [_RAISE] = LAYOUT_planck_grid(
    KC_GRAVE, KC_1,   KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    LGUI(KC_PGUP),
    _______,  KC_F1,  KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F11,  _______, _______, _______, _______, LGUI(KC_PGDN),
    _______,  KC_F6,  KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12,  _______, _______, _______, KC_BSLS, _______,
    _______, _______, _______, _______, _______, KC_PSCR, KC_PSCR, _______, _______, _______, _______, KC_MPLY
  ),

  [_ADJUST] = LAYOUT_planck_grid(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, AU_ON,   AU_OFF,  AU_TOGG, RGB_SPI, _______, RGB_TOG, RGB_VAI, RGB_HUI, KC_BRIGHTNESS_UP,   QK_BOOT,
    _______, _______, MU_ON,   MU_OFF,  MU_TOGG, RGB_SPD, _______, RGB_MOD, RGB_VAD, RGB_HUD, KC_BRIGHTNESS_DOWN, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

  [_NUMPAD] = LAYOUT_planck_grid(
    _______, _______, _______, _______, _______, _______, KC_CALCULATOR, KC_KP_7, KC_KP_8, KC_KP_9,   KC_KP_MINUS, KC_KP_SLASH,
    _______, _______, _______, _______, _______, _______, _______,       KC_KP_4, KC_KP_5, KC_KP_6,   KC_KP_PLUS,  KC_KP_ASTERISK,
    _______, _______, _______, _______, _______, _______, _______,       KC_KP_1, KC_KP_2, KC_KP_3,   KC_KP_ENTER, _______,
    _______, _______, _______, _______, _______, _______, _______,       KC_KP_0, _______, KC_KP_DOT, KC_KP_ENTER, _______
  ),

  [_EXTRA] = LAYOUT_planck_grid(
    G(KC_L), KC_SLEP, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, KC_LEFT,        KC_DOWN,        KC_UP,          KC_RIGHT,       _______, _______,
    _______, _______, KC_LCTL,       _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_AUDIO_MUTE, KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP, LT(_EXTRA, KC_MPLY)
  ),

};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
      case(LT(_BASE,KC_MINUS)):
          if (record->tap.count && record->event.pressed) {
              return true;
          } else if(record->event.pressed) {
              tap_code(KC_BSLS);
              return false;
          }
          break;

      case(LT(KC_LBRC, KC_7)):
          if (record->tap.count && record->event.pressed) {
              tap_code(KC_LBRC);
              return false;
          } else if(record->event.pressed) {
              tap_code16(KC_AMPERSAND);
              return false;
          }
          break;

      case(LT(KC_RBRC, KC_8)):
          if (record->tap.count && record->event.pressed) {
              tap_code(KC_RBRC);
              return false;
          } else if(record->event.pressed) {
              tap_code16(KC_ASTERISK);
              return false;
          }
          break;

      case(LT(KC_PGUP, KC_HOME)):
          if (record->tap.count && record->event.pressed) {
              tap_code(KC_PGUP);
              return false;
          } else if(record->event.pressed) {
              tap_code(KC_HOME);
              return false;
          }
          break;

      case(LT(KC_PGDN, KC_END)):
          if (record->tap.count && record->event.pressed) {
              tap_code(KC_PGDN);
              return false;
          } else if(record->event.pressed) {
              tap_code(KC_END);
              return false;
          }
          break;

      case(LT(_EXTRA, KC_MPLY)):
          if (record->tap.count == 2 && record->event.pressed) {
              tap_code(KC_MNXT);
              return false;
          } else if(record->event.pressed) {
              tap_code(KC_MPLY);
              return false;
          }
          break;
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
                layer_on(_ADJUST);
            } else {
#ifdef AUDIO_ENABLE
                if (play_sound) { PLAY_SONG(plover_gb_song); }
#endif
                layer_off(_ADJUST);
            }
#ifdef AUDIO_ENABLE
            play_sound = true;
#endif
            break;
        }
        case 1:
            muse_mode = false;
    }
    return true;
}

void matrix_scan_user(void) {
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case LT(_RAISE, KC_ENTER):
    case LT(_LOWER, KC_BSPC):
      return false;
    default:
      return true;
  }
}
