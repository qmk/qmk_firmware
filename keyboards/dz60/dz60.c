#include "dz60.h"
#include "led.h"

extern uint32_t layer_state;
extern struct cRGB led[16];

void matrix_init_kb(void)
{
  // Keyboard start-up code goes here
  // Runs once when the firmware starts up
  matrix_init_user();
  led_init_ports();
};

void matrix_scan_kb(void)
{
  // Looping keyboard code goes here
  // This runs every cycle (a lot)
  matrix_scan_user();

  uint8_t layer = biton32(layer_state);

  switch (layer)
  {
  case 1:
    rgblight_setrgb_at(191, 216, 0, 15);
    break;
  case 2:
    rgblight_setrgb_at(107, 91, 0, 15);
    break;
  case 3:
    rgblight_setrgb_at(233, 75, 0, 15);
    break;
  default:
    break;
  }
};

void led_init_ports(void)
{
  // Set caps lock LED pin as output
  DDRB |= (1 << 2);
  // Default to off
  PORTB |= (1 << 2);
}
