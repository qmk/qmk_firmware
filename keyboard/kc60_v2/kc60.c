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

#define CHANNEL OCR1B

void backlight_init_ports()
{
  DDRB |= (1<<6);  // Make port B6 an output port.
  PORTB &= ~(1<<6); // Make port B6 set to output low

  // Use full 16-bit resolution. 
  ICR1 = 0xFFFF;

  // I could write a wall of text here to explain... but TL;DW
  // Go read the ATmega32u4 datasheet.
  // And this: http://blog.saikoled.com/post/43165849837/secret-konami-cheat-code-to-high-resolution-pwm-on

  TCCR1A = 0b00001010;
  TCCR1B = 0b00011001;

  CHANNEL = 0x0000;

  backlight_init();
}

void backlight_set(uint8_t level)
{
  // Prevent backlight blink on lowest level
  PORTB &= ~(_BV(PORTB6));

  if ( level == 0 )
  {
    // Turn off PWM control on PB6, revert to output low.
    TCCR1A &= ~(_BV(COM1B1));
    CHANNEL = 0x0;
  }
  else if ( level == BACKLIGHT_LEVELS )
  {
    // Turn on PWM control of PB6
    TCCR1A |= _BV(COM1B1);
    // Set the brightness
    CHANNEL = 0xFFFF;
  }
  else        
  {
    // Turn on PWM control of PB6
    TCCR1A |= _BV(COM1B1);
    // Set the brightness
    CHANNEL = 0xFFFF >> ((BACKLIGHT_LEVELS - level) * ((BACKLIGHT_LEVELS + 1) / 2));
  }
}

#endif
