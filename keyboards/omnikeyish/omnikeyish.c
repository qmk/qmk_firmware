#include "matrix.h"
#include "quantum.h"
#include "config.h"

#include "dynamic_macro.h"

void keyboard_pre_init_user(void) {
  /* Column 1 to 8 uses PORTF, disable JTAG function on it.
     JTAG disable for PORT F. write JTD bit twice within four cycles. */
  MCUCR |= (1 << JTD);
  MCUCR |= (1 << JTD);

  // Configure LED driving pins as output pins
  setPinOutput(NUMLOCKLEDPIN);
  setPinOutput(CAPSLOCKLEDPIN);
  setPinOutput(SCROLLLOCKLEDPIN);

  dynamic_macro_init();
}

void keyboard_post_init_user(void) {
  /* Customise these values to desired behaviour */
  debug_enable = true;
  /* debug_matrix=true;
     debug_keyboard=true;
     debug_mouse=true; */

#if DYNAMIC_MACRO_EEPROM_STORAGE
  /* Restore macros from eeprom */
  dynamic_macro_load_eeprom_all();
#endif

  /* Send numlock keycode to attempt to force numlock back on. */
  register_code(KC_NUMLOCK);
  unregister_code(KC_NUMLOCK);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (!process_record_dynamic_macro(keycode, record)) {
    return false;
  }

  return true;
}

void led_set_user(uint8_t usb_led) {
  if (IS_LED_ON(usb_led, USB_LED_NUM_LOCK)) {
    writePinHigh(NUMLOCKLEDPIN);
  } else {
    writePinLow(NUMLOCKLEDPIN);
  }

  if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
    writePinHigh(CAPSLOCKLEDPIN);
  } else {
    writePinLow(CAPSLOCKLEDPIN);
  }

  if (IS_LED_ON(usb_led, USB_LED_SCROLL_LOCK)) {
    writePinHigh(SCROLLLOCKLEDPIN);
  } else {
    writePinLow(SCROLLLOCKLEDPIN);
  }
}