#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
    KC_NO,
    KC_MPRV, KC_MPLY, KC_MNXT,
    KC_BRID, KC_MUTE, KC_BRIU
  ),
};

// Volume up/down on the encoder
bool encoder_update_user(uint8_t index, bool clockwise) {
  if (clockwise) {
    tap_code_delay(KC_VOLU, 10);
  }
  else {
    tap_code_delay(KC_VOLD, 10);
  }

  return true;
}

#ifdef RGBLIGHT_ENABLE
// called post init on every "boot"
// will set the initial lightings
void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();  // enables Rgb, without saving settings
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    rgblight_sethsv_noeeprom(HSV_WHITE);
}
#endif
