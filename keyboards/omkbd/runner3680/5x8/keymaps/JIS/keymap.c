#include QMK_KEYBOARD_H
#include "keymap_japanese.h"

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
rgblight_config_t RGB_current_config;
#endif

enum layer_number {
    _QWERTY = 0,
    _ADJUST
};

enum custom_keycodes {
  ADJUST = SAFE_RANGE,
  RGBRST
};

// Fillers to make layering more clear
#define EISU LALT(KC_GRV)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* QWERTY
     * ,-------------------------------------------------------.      ,--------------------------------------------------------.
     * |  F1  |  F2  | EISU |   1  |   2  |   3  |   4  |   5  |      |   6  |   7  |   8  |   9  |   0  |   -  |   ^  |   \  |
     * |------+------+------+------+------+------+------+------|      |------+------+------+------+------+------+------+------|
     * |  F3  |  F4  | Tab  |   Q  |   W  |   E  |   R  |   T  |      |   Y  |   U  |   I  |   O  |   P  |   @  |   [  | Bksp |
     * |------+------+------+------+------+------+------+------|      |------+------+------+------+------+------+------+------|
     * |  F5  |  F6  | Esc  |   A  |   S  |   D  |   F  |   G  |      |   H  |   J  |   K  |   L  |   :  |   ;  |   ]  | Enter|
     * |------+------+------+------+------+------+------+------|      |------+------+------+------+------+------+------+------|
     * |  F7  |  F8  | Shift|   Z  |   X  |   C  |   V  |   B  |      |   N  |   M  |   ,  |   .  |   /  |   \  |  Up  | Shift|
     * |------+------+------+------+------+------+------+------|      |------+------+------+------+------+------+------+------|
     * |  F9  |  F10 | Ctrl | GUI  | Alt  | MHEN |  Del | Space|      | Enter| Bksp | HENK |Adjust|  F10 | Left | Down | Right|
     * `-------------------------------------------------------'      `-------------------------------------------------------'
     */
  [_QWERTY] = LAYOUT(
      RGBRST , UG_TOGG, JP_ZKHK, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, JP_CIRC, JP_YEN,
      UG_NEXT, UG_SATU, KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    JP_AT,   JP_LBRC, KC_BSPC,
      UG_SATU, UG_SATD, KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,       KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, JP_COLN, JP_RBRC, KC_ENT,
      UG_VALU, UG_VALD, KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,       KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, JP_BSLS, KC_UP,   KC_RSFT,
      _______, _______, KC_LCTL, KC_LGUI, KC_LALT, JP_MHEN, KC_DEL,  KC_SPC,     KC_ENT,  KC_BSPC, JP_HENK, ADJUST,  KC_F10,  KC_LEFT, KC_DOWN, KC_RGHT
      ),

    /* Adjust
     * ,-------------------------------------------------------.      ,--------------------------------------------------------.
     * |      |      |      |   F1 |   F2 |   F3 |   F4 |   F5 |      |   F6 |   F7 |   F8 |   F9 |  F10 |  F11 |  F12 |      |
     * |------+------+------+------+------+------+------+------|      |------+------+------+------+------+------+------+------|
     * |      |      |      |RGBRST| QK_BOOT|      |      |      |      |      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------|      |------+------+------+------+------+------+------+------|
     * |      |      |      |  TOG |  HUI |  SAI |  VAI |      |      |      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------|      |------+------+------+------+------+------+------+------|
     * |      |      |      |  MOD |  HUD |  SAD |  VAD |      |      |      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------|      |------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
     * `-------------------------------------------------------'      `-------------------------------------------------------'
     */
  [_ADJUST] =  LAYOUT(
      _______, _______, _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,      KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,
      _______, _______, _______, RGBRST,  QK_BOOT, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, UG_TOGG, UG_HUEU, UG_SATU, UG_VALU, _______,    _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, UG_NEXT, UG_HUED, UG_SATD, UG_VALD, _______,    _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______, _______
      )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
      case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
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
