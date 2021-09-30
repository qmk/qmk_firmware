#include "rev6.h"

// Indicator color definitions
#ifndef HSV_CAPS
    #define HSV_CAPS  96, 255, 120 // Define caps lock color (H, S, V)
#endif

#ifndef HSV_NLCK
    #define HSV_NLCK  160, 255, 120 // Define num lock color (H, S, V)
#endif

#ifndef HSV_LYR
    #define HSV_LYR  0, 255, 120 // Define layer color (H, S, V)
#endif

#ifndef HSV_BLACK
    #define HSV_BLACK  0, 0, 0  // Define 'black' color, more like 'LED off' (H, S, V)
#endif

void eeconfig_init_kb(void) {  // EEPROM is getting reset!
  rgblight_enable(); // Enable RGB by default
  rgblight_sethsv(0, 255, 128);  // Set default HSV - red hue, full saturation, medium brightness
  rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL + 2); // set to RGB_RAINBOW_SWIRL by default

  eeconfig_update_kb(0);
  eeconfig_init_user();
}

#ifdef RGBLIGHT_ENABLE

__attribute__ ((weak))
void led_set_user(uint8_t usb_led) {
    if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
        sethsv_raw(HSV_CAPS, (LED_TYPE *)&led[1]);
    } else {
        sethsv(HSV_BLACK, (LED_TYPE *)&led[1]);
    }
    if (IS_LED_ON(usb_led, USB_LED_NUM_LOCK)) {
        sethsv_raw(HSV_NLCK, (LED_TYPE *)&led[2]);
    } else {
        sethsv(HSV_BLACK, (LED_TYPE *)&led[2]);
    }
    rgblight_set();
}

__attribute__ ((weak))
void keyboard_post_init_user(void) {
    rgblight_set_effect_range(3, RGBLED_NUM-3);
    led_set_user(1 <<(USB_LED_CAPS_LOCK)|1 <<(USB_LED_NUM_LOCK));
    wait_ms(300);
    led_set_user(0);
}

__attribute__ ((weak))
void cypher_sethsv_range(uint8_t hue, uint8_t sat, uint8_t val, uint8_t start, uint8_t end) {
  LED_TYPE tmp_led;
  sethsv_raw(hue, sat, val, &tmp_led);
  for (uint8_t i = start; i < end; i++) {
      led[i] = tmp_led;
  }
  rgblight_set();
}

__attribute__((weak)) layer_state_t layer_state_set_user(layer_state_t state) {
    if (state & (1UL << 1)) {
        sethsv_raw(HSV_LYR, (LED_TYPE *)&led[0]);
    } else {
        sethsv(HSV_BLACK, (LED_TYPE *)&led[0]);
    }
  return state;
}

#endif
