#include "kc60.h"

__attribute__ ((weak))
  void matrix_init_user(void) {
    // leave this function blank - it can be defined in a keymap file
  };

__attribute__ ((weak))
  void matrix_scan_user(void) {
    // leave this function blank - it can be defined in a keymap file
  }

__attribute__ ((weak))
  bool process_action_user(keyrecord_t *record) {
    // leave this function blank - it can be defined in a keymap file
    return true;
  }

__attribute__ ((weak))
  void led_set_user(uint8_t usb_led) {
    // leave this function blank - it can be defined in a keymap file
  }

void matrix_init_kb(void) {
  // put your keyboard start-up code here
  // runs once when the firmware starts up

#ifdef BACKLIGHT_ENABLE
  backlight_init_ports();
#endif

  matrix_init_user();
}

void matrix_scan_kb(void) {
  // put your looping keyboard code here
  // runs every cycle (a lot)

  matrix_scan_user();
}

bool process_action_kb(keyrecord_t *record) {
  // put your per-action keyboard code here
  // runs for every action, just before processing by the firmware

  return process_action_user(record);
}

void led_set_kb(uint8_t usb_led) {
  // put your keyboard LED indicator (ex: Caps Lock LED) toggling code here

  led_set_user(usb_led);
}

#ifdef BACKLIGHT_ENABLE

#define output_low(port,pin) port &= ~(1<<pin)
#define output_high(port,pin) port |= (1<<pin)
#define PIN 6

void backlight_init_ports()
{
  DDRB |= (1<<PIN);  // Make port B6 an output port.
  output_low(PORTB, PIN);

  backlight_init();
}

void backlight_set(uint8_t level)
{
  println("Setting backlight with function ---------------");
  if(level == 0) {
    println("Backlight off! -------------");
    output_low(PORTB, PIN);
  } else {
    output_high(PORTB, PIN);
  }
}

#endif
