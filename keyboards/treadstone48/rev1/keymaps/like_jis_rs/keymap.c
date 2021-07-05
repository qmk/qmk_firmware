/* Copyright 2020 marksard
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
#include "../common/oled_helper.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
  _BASE = 0,
  _BASES,
  _LOWER,
  _LOWRS,
  _RAISE,
  _ADJUST,
};

enum custom_keycodes {
  BASE = SAFE_RANGE,
  BASES,
  LOWER,
  LOWRS,
  RAISE,
  ADJUST,
  KANJI,
  RGBRST
};

#define KC_TBSF  LSFT_T(KC_TAB)
#define KC_ALAP  LALT_T(KC_APP)

#define KC_JEQL  LSFT(KC_MINS)
#define KC_SFUC  LSFT(KC_RO)
#define KC_RSBR  LSFT(KC_8)
#define KC_REBR  LSFT(KC_9)

#define KC_ZSFT  LSFT_T(KC_Z)
#define KC_ESCT  LCTL_T(KC_ESC)
#define KC_TBAL  LALT_T(KC_TAB)
#define KC_11SF  LSFT_T(KC_F11)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_rs( \
  // Treadstone48                                                                                                           Rhymestone
  //,--------------------------------------------------------------------------------------------------------------------.  --------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,          KC_BSPC,     KC_P7,   KC_P8,   KC_P9, KC_PSLS, KC_NLCK,\
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+-----------------|  --------+--------+--------+--------+--------|
      KC_TBSF,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,           KC_ENT,     KC_P4,   KC_P5,   KC_P6, KC_PAST,  KC_TAB,\
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------+--------|  --------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,   KC_UP,              KC_P1,   KC_P2,   KC_P3, KC_PMNS, KC_PENT,\
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------+--------|  --------+--------+--------+--------+--------|
      KC_LCTL, KC_LALT, KC_LGUI,   LOWER,          KC_BSPC,           KC_SPC,   RAISE, KC_ALAP, KC_LEFT, KC_DOWN, KC_RGHT,     LOWER,   KC_P0, KC_PDOT, KC_PPLS, KC_BSPC,\
  //`--------------------------------------------------------------------------------------------------------------------'  --------------------------------------------'
       KC_DEL \
  // ExtraKey: This key is an extra key. REV1 is a split back space. REV2 is to the right of the arrow-up key.
  ),

  [_LOWER] = LAYOUT_rs( \
  // Treadstone48                                                                                                           Rhymestone
  //,--------------------------------------------------------------------------------------------------------------------.  --------------------------------------------.
      _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5, KC_MINS,  KC_EQL, KC_JYEN, KC_LBRC, KC_RBRC,           KC_DEL,      KC_A,    KC_B,    KC_C, KC_JYEN, KC_HASH,\
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+-----------------|  --------+--------+--------+--------+--------|
      _______,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, XXXXXXX, XXXXXXX, KC_SCLN, KC_QUOT, KC_BSLS,          _______,      KC_D,    KC_E,    KC_F, KC_PERC, KC_SFUC,\
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------+--------|  --------+--------+--------+--------+--------|
      _______,  KC_F11,  KC_F12,   BASES,   KANJI,  KC_ENT, XXXXXXX, KC_COMM,  KC_DOT, KC_SLSH,   KC_RO, KC_PGUP,            KC_RSBR, KC_REBR, KC_RBRC, KC_QUOT, _______,\
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------+--------|  --------+--------+--------+--------+--------|
      _______, _______, _______, _______,           KC_DEL,          _______, _______, XXXXXXX, KC_HOME, KC_PGDN,  KC_END,   _______, XXXXXXX, KC_COMM, KC_JEQL,  KC_DEL,\
  //`--------------------------------------------------------------------------------------------------------------------'  --------------------------------------------'
      _______ \
  // ExtraKey: This key is an extra key. REV1 is a split back space. REV2 is to the right of the arrow-up key.
  ),

  [_BASES] = LAYOUT_rs( \
  // Treadstone48                                                                                                           Rhymestone
  //,--------------------------------------------------------------------------------------------------------------------.  --------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,          KC_MINS,      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,\
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+-----------------|  --------+--------+--------+--------+--------|
      KC_TBSF,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,           KC_ENT,      KC_A,    KC_S,    KC_D,    KC_F,    KC_G,\
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------+--------|  --------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,   KC_UP,            KC_ZSFT,    KC_X,    KC_C,    KC_V,    KC_B,\
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------+--------|  --------+--------+--------+--------+--------|
      KC_LCTL, KC_LALT, KC_LGUI,   LOWER,          KC_BSPC,           KC_SPC,   RAISE, KC_ALAP, KC_LEFT, KC_DOWN, KC_RGHT,   KC_ESCT, KC_TBAL, KC_LGUI,   LOWRS, KC_BSPC,\
  //`--------------------------------------------------------------------------------------------------------------------'  --------------------------------------------'
       KC_DEL \
  // ExtraKey: This key is an extra key. REV1 is a split back space. REV2 is to the right of the arrow-up key.
  ),

  [_LOWRS] = LAYOUT_rs( \
  // Treadstone48                                                                                                           Rhymestone
  //,--------------------------------------------------------------------------------------------------------------------.  --------------------------------------------.
      _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5, KC_MINS,  KC_EQL, KC_JYEN, KC_LBRC, KC_RBRC,           KC_DEL,     KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,\
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+-----------------|  --------+--------+--------+--------+--------|
      _______,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, XXXXXXX, XXXXXXX, KC_SCLN, KC_QUOT, KC_BSLS,          _______,     KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,\
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------+--------|  --------+--------+--------+--------+--------|
      _______,  KC_F11,  KC_F12,    BASE,   KANJI,  KC_ENT, XXXXXXX, KC_COMM,  KC_DOT, KC_SLSH,   KC_RO, KC_PGUP,            KC_11SF,  KC_F12,    BASE,   KANJI,  KC_ENT,\
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------+--------|  --------+--------+--------+--------+--------|
      _______, _______, _______, _______,           KC_DEL,          _______, _______, XXXXXXX, KC_HOME, KC_PGDN,  KC_END,   _______, _______, _______, _______,  KC_DEL,\
  //`--------------------------------------------------------------------------------------------------------------------'  --------------------------------------------'
      _______ \
  // ExtraKey: This key is an extra key. REV1 is a split back space. REV2 is to the right of the arrow-up key.
  ),

  [_RAISE] = LAYOUT_rs( \
  // Treadstone48                                                                                                           Rhymestone
  //,--------------------------------------------------------------------------------------------------------------------.  --------------------------------------------.
      _______,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,          XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+-----------------|  --------+--------+--------+--------+--------|
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_4,    KC_5,    KC_6, KC_QUOT,          _______,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------+--------|  --------+--------+--------+--------+--------|
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_1,    KC_2,    KC_3,   KC_RO, XXXXXXX,            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------+--------|  --------+--------+--------+--------+--------|
      _______, _______, _______, _______,          _______,          _______, _______,    KC_0,  KC_DOT, KC_COMM, KC_SLSH,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //`--------------------------------------------------------------------------------------------------------------------'  --------------------------------------------'
      _______ \
  // ExtraKey: This key is an extra key. REV1 is a split back space. REV2 is to the right of the arrow-up key.
  ),

  [_ADJUST] = LAYOUT_rs( \
  // Treadstone48                                                                                                           Rhymestone
  //,--------------------------------------------------------------------------------------------------------------------.  --------------------------------------------.
      XXXXXXX,   RESET,  RGBRST, AG_NORM, AG_SWAP, XXXXXXX, XXXXXXX, KC_WH_L, KC_WH_U, KC_HOME, KC_PGUP,          XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+-----------------|  --------+--------+--------+--------+--------|
      XXXXXXX, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX, KC_WH_R, KC_WH_D,  KC_END, KC_PGDN,          XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------+--------|  --------+--------+--------+--------+--------|
      _______, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX, XXXXXXX, KC_BTN1, KC_BTN2, XXXXXXX, KC_MS_U,            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------+--------|  --------+--------+--------+--------+--------|
      _______, _______, _______, _______,          XXXXXXX,          XXXXXXX, _______, XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //`--------------------------------------------------------------------------------------------------------------------'  --------------------------------------------'
      _______ \
  // ExtraKey: This key is an extra key. REV1 is a split back space. REV2 is to the right of the arrow-up key.
  )
};

#define L_BASE _BASE
#define L_BASES (1<<_BASES)
#define L_LOWER (1<<_LOWER)
#define L_LOWRS (1<<_LOWRS)
#define L_RAISE (1<<_RAISE)
#define L_ADJUST (1<<_ADJUST)
#define L_ADJUST_TRI (L_ADJUST|L_RAISE|L_LOWER)

#ifdef OLED_ENABLE
#include <stdio.h>
#include <string.h>

typedef struct {
  uint8_t state;
  char name[8];
}LAYER_DISPLAY_NAME;

#define LAYER_DISPLAY_MAX 7
const LAYER_DISPLAY_NAME layer_display_name[LAYER_DISPLAY_MAX] = {
  {L_BASE, "Base"},
  {L_BASE + 1, "Base"},
  {L_BASES, "BaseSpl"},
  {L_LOWER, "Lower"},
  {L_LOWRS, "LowrSpl"},
  {L_RAISE, "Raise"},
  {L_ADJUST_TRI, "Adjust"}
};

static inline const char* get_leyer_status(void) {

  for (uint8_t i = 0; i < LAYER_DISPLAY_MAX; ++i) {
    if (layer_state == 0 && layer_display_name[i].state == default_layer_state) {

      return layer_display_name[i].name;
    } else if (layer_state != 0 && layer_display_name[i].state == layer_state) {

      return layer_display_name[i].name;
    }
  }

  return "?";
}

static char layer_status_buf[24] = "Layer state ready.\n";
static inline void update_keymap_status(void) {

  snprintf(layer_status_buf, sizeof(layer_status_buf) - 1, "OS:%s Layer:%s\n",
    keymap_config.swap_lalt_lgui? "win" : "mac", get_leyer_status());
}

static inline void render_keymap_status(void) {

  oled_write(layer_status_buf, false);
}

#define UPDATE_KEYMAP_STATUS() update_keymap_status()

static inline void render_status(void) {

  UPDATE_LED_STATUS();
  RENDER_LED_STATUS();
  render_keymap_status();
  UPDATE_LOCK_STATUS();
  RENDER_LOCK_STATUS();
  RENDER_KEY_STATUS();
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {

//   if (is_keyboard_master())
//     return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

void oled_task_user(void) {

  if (is_keyboard_master()) {
    render_status();
  } else {
    render_logo();
  }
}

#else

#define UPDATE_KEYMAP_STATUS()

#endif

void update_change_layer(bool pressed, uint8_t layer1, uint8_t layer2, uint8_t layer3) {

  pressed ? layer_on(layer1) : layer_off(layer1);
  IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2) ? layer_on(layer3) : layer_off(layer3);
}

int RGB_current_mode;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  UPDATE_KEY_STATUS(keycode, record);

  bool result = false;
  switch (keycode) {
    case LOWER:
      update_change_layer(record->event.pressed, _LOWER, _RAISE, _ADJUST);
      break;
    case RAISE:
      update_change_layer(record->event.pressed, _RAISE, _LOWER, _ADJUST);
      break;
    case BASE:
      if (record->event.pressed) {
        default_layer_set(L_BASE);
      }
      break;
    case BASES:
      if (record->event.pressed) {
        default_layer_set(L_BASES);
      }
      break;
    case LOWRS:
      update_change_layer(record->event.pressed, _LOWRS, _RAISE, _ADJUST);
      break;
    case KANJI:
      if (record->event.pressed) {
        if (keymap_config.swap_lalt_lgui == false) {
          register_code(KC_LANG2);
        } else {
          SEND_STRING(SS_LALT("`"));
        }
      } else {
        unregister_code(KC_LANG2);
      }
      break;
    #ifdef RGBLIGHT_ENABLE
      case RGBRST:
          if (record->event.pressed) {
            eeconfig_update_rgblight_default();
            rgblight_enable();
          }
        break;
    #endif
    default:
      result = true;
      break;
  }

  UPDATE_KEYMAP_STATUS();
  return result;
}
