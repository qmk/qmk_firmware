#include "lets_split.h"

void force_num_lock(void)
{
  //Turns on num-lock if it was off.
  if (!(host_keyboard_leds() & (1 << USB_LED_NUM_LOCK))) {
    register_code(KC_NUMLOCK);
    unregister_code(KC_NUMLOCK);
  }
}

void matrix_init_kb(void) {

  force_num_lock();

	matrix_init_user();
};



