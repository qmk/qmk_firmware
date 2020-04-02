#include "ext65rev2.h"

#ifdef OLED_DRIVER_ENABLE

void keyboard_pre_init_user(void) {
  // Call the keyboard pre init code.

  // Set our LED pins as output
  palSetPadMode(GPIOB, 8, PAL_MODE_ALTERNATE(1));
  palSetPadMode(GPIOB, 9, PAL_MODE_ALTERNATE(1));
}


void oled_task_user(void) {
  // Host Keyboard Layer Status
  oled_write_P(PSTR("Layer: "), false);
  switch (get_highest_layer(layer_state)) {
    case 0:
      oled_write_P(PSTR("Default\n"), false);
      break;
    case 1:
      oled_write_P(PSTR("Layer 1\n"), false);
      break;
    case 2:
      oled_write_P(PSTR("Layer 2\n"), false);
      break;
    default:
      // Or use the write_ln shortcut over adding '\n' to the end of your string
      oled_write_ln_P(PSTR("Undefined"), false);
  }

  // Host Keyboard LED Status
  uint8_t led_usb_state = host_keyboard_leds();
  oled_write_P(led_usb_state & (1<<USB_LED_NUM_LOCK) ? PSTR("NUMLCK ") : PSTR("       "), false);
  oled_write_P(led_usb_state & (1<<USB_LED_CAPS_LOCK) ? PSTR("CAPLCK ") : PSTR("       "), false);
  oled_write_P(led_usb_state & (1<<USB_LED_SCROLL_LOCK) ? PSTR("SCRLCK ") : PSTR("       "), false);
}
#else 

void keyboard_pre_init_user(void) {
  // Call the keyboard pre init code.

  // Set our LED pins as output
  setPinOutput(B4);
  setPinOutput(B3);
  setPinOutput(A15);
  setPinOutput(A14);
}

void led_set_user(uint8_t usb_led) {
    if (IS_LED_ON(usb_led, USB_LED_NUM_LOCK)) {
        writePinHigh(B4);
    } else {
        writePinLow(B4);
    }
    if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
        writePinHigh(B3);
    } else {
        writePinLow(B3);
    }
    if (IS_LED_ON(usb_led, USB_LED_SCROLL_LOCK)) {
        writePinHigh(A15);
    } else {
        writePinLow(A15);
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
      case 1:
        writePinHigh(A14);
        break;
      default: //  for any other layers, or the default layer
        writePinLow(A14);
        break;
      }
    return state;
}
#endif
