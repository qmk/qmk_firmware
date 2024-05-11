#include QMK_KEYBOARD_H

enum custom_keycodes {
  BL1 = SAFE_RANGE,
  BL2,
  BL3,
  BL4
};

const uint8_t LED_PINS[] = LED_ROW_PINS;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT_ortho_4x4(
    KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
    KC_P4,   KC_P5,   KC_P6,   KC_PMNS,
    KC_P1,   KC_P2,   KC_P3,   KC_PAST,
    MO(1),   KC_P0,   KC_PDOT, KC_ENT
  ),

  [1] = LAYOUT_ortho_4x4(
    KC_NUM,  BL1,     KC_TRNS, KC_PSLS,
    QK_BOOT,   BL2,     KC_TRNS, KC_TRNS,
    KC_TRNS, BL3,     KC_TRNS, KC_TRNS,
    KC_TRNS, BL4,     KC_TRNS, KC_TRNS
  ),

};

void set_led(int idx, bool enable) {
  uint8_t pin = LED_PINS[idx];
  if (enable) {
    _SFR_IO8((pin >> 4) + 2) |= _BV(pin & 0xF);
  } else {
    /* PORTx &= ~n */
    _SFR_IO8((pin >> 4) + 2) &= ~_BV(pin & 0xF);
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case BL1:
    gpio_write_pin(B4, record->event.pressed);
    return false;
  case BL2:
    gpio_write_pin(B5, record->event.pressed);
    return false;
  case BL3:
    gpio_write_pin(B6, record->event.pressed);
    return false;
  case BL4:
    gpio_write_pin(B7, record->event.pressed);
    return false;
  }
  return true;
}

void matrix_init_user(void) {
  /* set LED row pins to output and low */
  gpio_set_pin_output(B4);
  gpio_set_pin_output(B5);
  gpio_set_pin_output(B6);
  gpio_set_pin_output(B7);

  gpio_write_pin_low(B4);
  gpio_write_pin_low(B5);
  gpio_write_pin_low(B6);
  gpio_write_pin_low(B7);
}
