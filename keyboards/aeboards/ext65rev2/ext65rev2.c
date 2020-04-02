#include "ext65rev2.h"

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_90;  // flips the display 90 degrees
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
