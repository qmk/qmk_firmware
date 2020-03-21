#include "split75.h"
#include "rgblight.h"

#include <avr/pgmspace.h>
#include <i2c_master.h>

#include "action_layer.h"

#define I2C_TIMEOUT     10

#define LED_INDICATORS

// Use the backlight as caps lock indicator?
// Best used if you only solder an LED under caps lock
#define BL_AS_CAPSLOCK 

extern inline void led_1_on(void);
extern inline void led_2_on(void);
extern inline void led_3_on(void);

extern inline void led_1_off(void);
extern inline void led_2_off(void);
extern inline void led_3_off(void);

void blink_all_leds(void);

uint8_t led0 = 0, led1 = 0, led2 = 0;

void indicator_init(void) {
    // D0, D1, and D6 are the indicators and D4 is the backlight
    DDRD |= 0x53;
    PORTD |= 0x53;
}

// for keyboard subdirectory level init functions
void matrix_init_kb(void) {
  // call user level keymaps, if any
  blink_all_leds();
  matrix_init_user();
}

void blink_all_leds(void) {
    led_1_on();
    _delay_ms(50);
    led_2_on();
    _delay_ms(50);
    led_3_on();
    _delay_ms(50);
    led_1_off();
    _delay_ms(50);
    led_2_off();
    _delay_ms(50);
    led_3_off();
}

__attribute__((weak)) // overridable
void matrix_init_user(void) {}

void matrix_scan_kb(void) {}

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  //debug_keyboard=true;
  //debug_mouse=true;
  led_set_user(0);
}

#if defined(LED_INDICATORS)
void led_set_user(uint8_t usb_led) {
  if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
    led_2_on();
  }
  else {
    led_2_off();
  }
}
#endif
