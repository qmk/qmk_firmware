#include "../../crawlpad.h"

enum custom_keycodes {
  BL1 = SAFE_RANGE,
  BL2,
  BL3,
  BL4
};

const uint8_t LED_PINS[] = LED_ROW_PINS;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

KEYMAP(
    KC_P7, KC_P8, KC_P9, KC_PPLS,
    KC_P4, KC_P5, KC_P6, KC_PMNS,
    KC_P1, KC_P2, KC_P3, KC_PAST,
    MO(1), KC_P0, KC_PDOT, KC_ENT),

KEYMAP(
    KC_NLCK, BL1, KC_TRNS, KC_PSLS,
    RESET, BL2, KC_TRNS, KC_TRNS,
    KC_TRNS, BL3, KC_TRNS, KC_TRNS,
    KC_TRNS, BL4, KC_TRNS, KC_TRNS),

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

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  return MACRO_NONE ;
}

void matrix_init_user(void) {
  /* set LED row pins to output and low */
  DDRB |= (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7);
  PORTB &= ~(1 << 4) & ~(1 << 5) & ~(1 << 6) & ~(1 << 7);
}

void matrix_scan_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case BL1:
    if (record->event.pressed) {
      PORTB |= (1 << 4);
    } else {
      PORTB &= ~(1 << 4);
    }
    return false;
  case BL2:
    if (record->event.pressed) {
      PORTB |= (1 << 5);
    } else {
      PORTB &= ~(1 << 5);
    }
    return false;
  case BL3:
    if (record->event.pressed) {
      PORTB |= (1 << 6);
    } else {
      PORTB &= ~(1 << 6);
    }
    return false;
  case BL4:
    if (record->event.pressed) {
      PORTB |= (1 << 7);
    } else {
      PORTB &= ~(1 << 7);
    }
    return false;
  }
  return true;
}

void led_set_user(uint8_t usb_led) {

  if (usb_led & (1 << USB_LED_NUM_LOCK)) {

  } else {

  }

  if (usb_led & (1 << USB_LED_CAPS_LOCK)) {

  } else {

  }

  if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {

  } else {

  }

  if (usb_led & (1 << USB_LED_COMPOSE)) {

  } else {

  }

  if (usb_led & (1 << USB_LED_KANA)) {

  } else {

  }

}
