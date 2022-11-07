#include "zer09.h"
#include "lights.h"
#include "tap_dance.h"

__attribute__((weak)) void matrix_init_keymap(void) {}

__attribute__((weak)) void matrix_scan_keymap(void) {}

__attribute__((weak)) bool process_record_keymap(uint16_t keycode,
                                                 keyrecord_t *record) {
  return true;
}

__attribute__((weak)) void led_set_keymap(uint8_t usb_led) {}

static uint8_t c_lyr = 0; // current layer.

bool shifted_layer(void) {
  static bool is_shifted = false;

  if (c_lyr == _VL) {
    if (!is_shifted) {
      register_code(KC_LSFT);
      is_shifted = true;
      return true;
    }
  } else {
    if (is_shifted) {
      unregister_code(KC_LSFT);
      is_shifted = false;
      return true;
    }
  }

  return false;
}

void matrix_init_user(void) {
  eeprom_read_led_dim_lvl();

  matrix_init_keymap();
}

void matrix_scan_user(void) {
  static uint8_t is_leds_changes = 1;
  c_lyr = get_highest_layer(layer_state);

  is_leds_changes = is_leds_changes << set_layer_led(c_lyr);
  is_leds_changes = is_leds_changes << shifted_layer();
  is_leds_changes = is_leds_changes << rainbow_loop(c_lyr);

  if (is_leds_changes > 1) {
    rgblight_set();
    is_leds_changes = 1;
  }

  matrix_scan_keymap();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  set_key_led(record, c_lyr);

  if (led_brightness(keycode, record)) {
    rgblight_set();
    return false;
  }

  rgblight_set();
  return process_record_keymap(keycode, record);
}

void led_set_user(uint8_t usb_led) {
  if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
    rbw_led_keys[RBW_LCAP].status = ENABLED;
    rbw_led_keys[RBW_RCAP].status = ENABLED;
  } else {
    rbw_led_keys[RBW_LCAP].status = DISABLED;
    rbw_led_keys[RBW_RCAP].status = DISABLED;
  }

  if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {
    rbw_led_keys[RBW_SCRL].status = ENABLED;
  } else {
    rbw_led_keys[RBW_SCRL].status = DISABLED;
  }

  led_set_keymap(usb_led);
}
