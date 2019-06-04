#include QMK_KEYBOARD_H
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
rgblight_config_t RGB_current_config;
#endif

extern uint8_t is_master;

enum layer_number {
    _QWERTY = 0,
    _ADJUST
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  ADJUST,
  RGBRST
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define EISU LALT(KC_GRV)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* QWERTY
     * ,------------------------------------------------.      ,------------------------------------------------.
     * |  F4  | Tab  |   Q  |   W  |   E  |   R  |   T  |      |   Y  |   U  |   I  |   O  |   P  |   [  |   ]  |
     * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
     * |  F6  | Esc  |   A  |   S  |   D  |   F  |   G  |      |   H  |   J  |   K  |   L  |   ;  |   "  | Enter|
     * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
     * |  F8  | Shift|   Z  |   X  |   C  |   V  |   B  |      |   N  |   M  |   ,  |   .  |   /  |   \  |  Up  |
     * `------------------------------------------------'      `------------------------------------------------'
     */
  [_QWERTY] = LAYOUT( \
      KC_F4,   KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, \
      KC_F6,   KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,       KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  \
      KC_F8,   KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,       KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_BSLS, KC_UP    \
      ),

    /* Adjust
     * ,------------------------------------------------.      ,------------------------------------------------.
     * |      |      |RGBRST| RESET|      |      |      |      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
     * |      |      |  TOG |  HUI |  SAI |  VAI |      |      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
     * |      |      |  MOD |  HUD |  SAD |  VAD |      |      |      |      |      |      |      |      |      |
     * `------------------------------------------------'      `------------------------------------------------'
     */
  [_ADJUST] =  LAYOUT( \
      _______, _______, RGBRST,  RESET,   _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______, \
      _______, _______, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, _______,    _______, _______, _______, _______, _______, _______, _______, \
      _______, _______, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, _______,    _______, _______, _______, _______, _______, _______, _______  \
      )
};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
      case QWERTY:
        if (record->event.pressed) {
           print("mode just switched to qwerty and this is a huge string\n");
          set_single_persistent_default_layer(_QWERTY);
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

      case RGBRST:
        #ifdef RGBLIGHT_ENABLE
          if (record->event.pressed) {
            eeconfig_update_rgblight_default();
            rgblight_enable();
            RGB_current_config = rgblight_config;
          }
        #endif
        break;
  }
  return true;
}
