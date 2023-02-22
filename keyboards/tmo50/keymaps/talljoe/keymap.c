#include "quantum.h"
#include "talljoe.h"

bool process_indicator_led_user(uint32_t state){
  return false;
}

#define LED_MASK (_BV(PB0) | _BV(PB1) | _BV(PB2) | _BV(PB3))
#define WHITE (_BV(PB0))
#define YELLOW (_BV(PB1))
#define MAGENTA (_BV(PB2))
#define RED (_BV(PB3))

void matrix_scan_keymap(void) {
  uint32_t lights = WHITE;

  switch(get_highest_layer(layer_state))
  {
    case _NAV:
      lights |= YELLOW;
      break;
    case _NUM:
      lights |= MAGENTA;
      break;
    case _ADJUST:
      lights |= RED;
      break;
    default: {
      uint8_t default_layer = get_highest_layer(default_layer_state);
      lights = 0; // no white LED by default.
      if(default_layer & 1)
        lights |= YELLOW;
      if(default_layer & 2)
        lights |= MAGENTA;
      if(default_layer & 4)
        lights |= RED;
    }
  }

  uint32_t port = PORTB;
  port |= LED_MASK;
  port &= ~lights;
  PORTB = port;
}
