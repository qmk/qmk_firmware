#include <stdint.h>
#include <stdbool.h>
#include "quantum.h"
#include QMK_KEYBOARD_H
#include "i2c_master.h"


void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  //debug_matrix=true;
  debug_keyboard=true;
  //debug_mouse=true;
}

