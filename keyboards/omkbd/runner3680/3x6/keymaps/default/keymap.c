#include QMK_KEYBOARD_H


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
     * ,-----------------------------------------.      ,-----------------------------------------.
     * | Tab  |   Q  |   W  |   E  |   R  |   T  |      |   Y  |   U  |   I  |   O  |   P  |   [  |
     * |------+------+------+------+------+------|      |------+------+------+------+------+------|
     * | Esc  |   A  |   S  |   D  |   F  |   G  |      |   H  |   J  |   K  |   L  |   ;  |   "  |
     * |------+------+------+------+------+------|      |------+------+------+------+------+------|
     * | Shift|   Z  |   X  |   C  |   V  |   B  |      |   N  |   M  |   ,  |   .  |   /  |   \  |
     * `-----------------------------------------'      `-----------------------------------------'
     */
  [_QWERTY] = LAYOUT(
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
      KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,       KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,       KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_BSLS
      ),

    /* Adjust
     * ,-----------------------------------------.      ,-----------------------------------------.
     * |      |RGBRST| QK_BOOT|      |      |      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------|      |------+------+------+------+------+------|
     * |      |  TOG |  HUI |  SAI |  VAI |      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------|      |------+------+------+------+------+------|
     * |      |  MOD |  HUD |  SAD |  VAD |      |      |      |      |      |      |      |      |
     * `-----------------------------------------'      `-----------------------------------------'
     */
  [_ADJUST] =  LAYOUT(
      _______, RGBRST,  QK_BOOT, _______, _______, _______,    _______, _______, _______, _______, _______, _______,
      _______, UG_TOGG, UG_HUEU, UG_SATU, UG_VALU, _______,    _______, _______, _______, _______, _______, _______,
      _______, UG_NEXT, UG_HUED, UG_SATD, UG_VALD, _______,    _______, _______, _______, _______, _______, _______
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
