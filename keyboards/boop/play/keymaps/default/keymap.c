#include "quantum.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = {
    { KC_MPRV, KC_MNXT },
    { KC_MPLY, TO(1) },

  },
    [1] = {
    { MO(2) , RGB_MODE_FORWARD},
    { KC_MPLY, TO(3) },

  },

    [2] = {
    { RGB_MODE_REVERSE , RGB_MODE_FORWARD},
    { KC_MPLY, TO(0) },

  },
    [3] = {
    { MO(2) , RGB_MODE_FORWARD},
    { LCMD(KC_D), TO(0) },

  },
};


