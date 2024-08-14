/* Copyright 2020 yushakobo
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
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
    _NUM = 0,
    _KEY,
    _LOWER,
    _ADJUST
};

enum custom_keycodes {
  NUM = SAFE_RANGE,
  KEY,
  LOWER,
  ADJUST,
  MAC_0,
  MAC_1,
  RGBRST,
  M_NLCK
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

//Macros
#define M_SAMPLE M(KC_SAMPLEMACRO)

#if MATRIX_ROWS == 10 // HELIX_ROWS == 5
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* num
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | ESC  | MAC1 |  /   |  *   |  -   |ADJUST|             | ESC  |ADJUST| MAC1 |  /   |  *   |  -   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |  :   |  7   |  8   |  9   |  +   |S+CAPS|             |S+CAPS| :    |  7   |  8   |  9   |  +   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | TAB  |  4   |  5   |  6   |ZK/HK |Lalt  |             |Lalt  | TAB  |  4   |  5   |  6   | ZK/HK|
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | LOWER|  1   |  2   |  3   | BS   |swin+S|Lshift|swin+S|Lshift| LOWER|  1   |  2   |  3   | BS   |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |  0   |  ,   |  .   | ENT  |      |Lctrl |win+R |Lctrl |      |  0   |  ,   |  .   |ENT   |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_NUM] = LAYOUT(\
      KC_ESC,  MAC_1,   KC_PSLS, KC_PAST, KC_PMNS, ADJUST,                          KC_ESC,  ADJUST,  MAC_1,   KC_PSLS, KC_PAST, KC_PMNS, \
      KC_QUOT, KC_P7,   KC_P8,   KC_P9,   KC_PPLS, S(KC_CAPS),                      S(KC_CAPS), KC_QUOT, KC_P7,   KC_P8,   KC_P9,   KC_PPLS, \
      KC_TAB,  KC_P4,   KC_P5,   KC_P6,   KC_ZKHK, KC_LOPT,                         KC_LOPT, KC_TAB,  KC_P4,   KC_P5,   KC_P6,   KC_ZKHK, \
      LOWER,   KC_P1,   KC_P2,   KC_P3,   KC_BSPC, KC_LSFT, SWIN(KC_S), SWIN(KC_S), KC_LSFT, LOWER,   KC_P1,   KC_P2,   KC_P3,   KC_BSPC, \
      _______, KC_P0,   KC_COMM, KC_PDOT, KC_ENT,  KC_LCTL, _______,    LWIN(KC_R), KC_LCTL, MAC_0,   KC_P0,   KC_COMM, KC_PDOT, KC_ENT \
      ),
  [_KEY] = LAYOUT(\
      _______, _______, KC_SLSH, S(KC_QUOT), KC_MINS, ADJUST,                 _______, ADJUST,  _______, KC_SLSH, S(KC_QUOT), KC_MINS, \
      _______, KC_7,    KC_8,    KC_9,    S(KC_SCLN), _______,                _______, _______, KC_7,    KC_8,    KC_9,    S(KC_SCLN), \
      _______, KC_4,    KC_5,    KC_6,    _______, _______,                   _______, _______, KC_4,    KC_5,    KC_6,    _______, \
      _______, KC_1,    KC_2,    KC_3,    _______, _______, _______, _______, _______, _______, KC_1,    KC_2,    KC_3,    _______, \
      _______, KC_0,    _______, KC_DOT,  _______, _______, _______, _______, _______, _______, KC_0,    _______, KC_DOT,  _______ \
      ),
 
  [_LOWER] = LAYOUT(\
      _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
      _______, KC_HOME, KC_UP,   KC_PGUP, _______, _______,                   _______, _______, KC_HOME, KC_UP,   KC_PGUP, _______, \
      _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,                   _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, \
      _______, KC_END,  KC_DOWN, KC_PGDN, KC_DEL,  _______, _______, _______, _______, _______, KC_END,  KC_DOWN, KC_PGDN, KC_DEL,  \
      _______, KC_INS,  _______, KC_DEL,  KC_BTN3, _______, _______, _______, _______, _______, KC_INS,  _______, KC_DEL,  KC_BTN3 \
      ),  
  [_ADJUST] = LAYOUT(\
      _______, KC_NLCK, RESET,   _______, _______, _______,                   _______, _______, KC_NLCK, RESET,   _______, _______, \
      _______, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, KEY,                       _______, KEY,     RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, \
      _______, RGB_TOG, _______, _______, _______, NUM,                       _______, NUM,     RGB_TOG, _______, _______, _______, \
      _______, _______, RGB_HUD, RGB_SAD, RGB_VAD, _______, _______, _______, _______, _______, _______, RGB_HUD, RGB_SAD, RGB_VAD, \
      _______, RGBRST,  _______, _______, _______, _______, _______, _______, _______, _______, RGBRST,  _______, _______, _______\
      ) 
};

#else
#error "undefined keymaps"
#endif


#ifdef AUDIO_ENABLE

float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_plover[][2]     = SONG(PLOVER_SOUND);
float tone_plover_gb[][2]  = SONG(PLOVER_GOODBYE_SOUND);
float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);
#endif

// define variables for reactive RGB
bool TOG_STATUS = false;
int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

/*
// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    #ifdef RGBLIGHT_ENABLE
      //rgblight_mode(RGB_current_mode);
    #endif
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}
*/

//imeONの場合、入力後に「shift+無変換+無変換」で半角英数に変換、imeOFFの場合影響なし
void LSFT_MHEN2(void) {
        register_code(KC_LSFT);
        register_code(KC_MHEN);
        unregister_code(KC_MHEN);
        register_code(KC_MHEN);
        unregister_code(KC_MHEN);
        unregister_code(KC_LSFT);
}

//imeONの時、入力後にLSFT_MHEN2を割り込みさせる配列
const uint16_t leave_ime_on_keys[] = {
  // https://beta.docs.qmk.fm/using-qmk/simple-keycodes/keycodes_basic#letters-and-numbers
  KC_0, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9,
  KC_SLSH, S(KC_QUOT), KC_MINUS, S(KC_SCLN),
  KC_DOT,
  KC_QUOT,KC_COMM
};

int length_of_leave_ime_on_keys = sizeof(leave_ime_on_keys) / sizeof(uint16_t);



bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case NUM:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
//        persistent_default_layer_set(1UL<<_NUM);
          layer_clear();
      }
      return false;
      break;
    case KEY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_colemak);
        #endif
//        persistent_default_layer_set(1UL<<_KEY);
          layer_move(_KEY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        //not sure how to have keyboard check mode and set it to a variable, so my work around
        //uses another variable that would be set to true after the first time a reactive key is pressed.
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          #ifdef RGBLIGHT_ENABLE
            //rgblight_mode(RGBLIGHT_MODE_SNAKE);
          #endif
        }
        layer_on(_LOWER);
        //update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        #ifdef RGBLIGHT_ENABLE
          //rgblight_mode(RGB_current_mode);  // revert RGB to initial mode prior to RGB mode change
        #endif
        layer_off(_LOWER);
        TOG_STATUS = false;
        //update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
        break;
    case M_NLCK:
        if (record->event.pressed) {
          SEND_STRING(SS_TAP(X_NLCK));
        } else {
          SEND_STRING(SS_TAP(X_NLCK));
        }
        return false;
        break;

      //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_get_mode();
        }
      #endif
      return false;
      break;

    case MAC_0:
      if (record->event.pressed) {
        SEND_STRING("0"); //日本語入力ONの場合「わ」になる
        LSFT_MHEN2();
//        SEND_STRING(SS_TAP(X_P0));
      }
      return false;
      break;
    case MAC_1:
      if (record->event.pressed) {
        SEND_STRING("154181"); //日本語入力ONの場合「ぬえうぬゆぬ」になる
        LSFT_MHEN2();
//        SEND_STRING(SS_TAP(X_P1)SS_TAP(X_P5)SS_TAP(X_P4)SS_TAP(X_P1)SS_TAP(X_P8)SS_TAP(X_P1)); //NUMLOCK OFFでカーソル暴走
      }
      return false;
      break;

    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_get_mode();
        }
      #endif
      break;
  }

//キーリリース後にLSFT_MHEN2割り込み
    bool leave_ime_on = false;
    for (int i = 0; i < length_of_leave_ime_on_keys; i++) 
      if (leave_ime_on_keys[i] == keycode) {
        leave_ime_on = true;
        break;
      }
    if (leave_ime_on) {
      if (record->event.pressed) {

      } else {
        LSFT_MHEN2();
      }
    }
  return true;
}



#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

void matrix_init_user(void) {
    #ifdef AUDIO_ENABLE
        startup_user();
    #endif
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_get_mode();
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}


#ifdef AUDIO_ENABLE

void startup_user()
{
    _delay_ms(20); // gets rid of tick
}

void shutdown_user()
{
    _delay_ms(150);
    stop_all_notes();
}

void music_on_user(void)
{
    music_scale_user();
}

void music_scale_user(void)
{
    PLAY_SONG(music_scale);
}

#endif

