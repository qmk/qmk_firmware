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
#define CHANNEL OCR1B

void backlight_init_ports()
{

  // Setup PB6 as output and output low.
  DDRB |= (1<<6);
  PORTB &= ~(1<<6);

  // Use full 16-bit resolution. 
  ICR1 = 0xFFFF;

  // I could write a wall of text here to explain... but TL;DW
  // Go read the ATmega32u4 datasheet.
  // And this: http://blog.saikoled.com/post/43165849837/secret-konami-cheat-code-to-high-resolution-pwm-on

  // Pin PB7 = OCR1C (Timer 1, Channel C)
  // Compare Output Mode = Clear on compare match, Channel C = COM1B1=1 COM1C0=0
  // (i.e. start high, go low when counter matches.)
  // WGM Mode 14 (Fast PWM) = WGM13=1 WGM12=1 WGM11=1 WGM10=0
  // Clock Select = clk/1 (no prescaling) = CS12=0 CS11=0 CS10=1

  TCCR1A = _BV(COM1B1) | _BV(WGM11); // = 0b00001010;
  TCCR1B = _BV(WGM13) | _BV(WGM12) | _BV(CS10); // = 0b00011001;

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
  else if ( level == BACKLIGHT_LEVELS)
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
