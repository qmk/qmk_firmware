#ifdef ENCODER_ENABLE

#define BOOL_SIZE 2

static const uint16_t PROGMEM encoder_table[NUM_ENCODERS][BOOL_SIZE][BOOL_SIZE] = {
  [0] = { // left
    { KC_VOLD,  KC_VOLU  }, // un-shifted
    { KC_MNXT,  KC_MPRV  }  // shifted
  },
  [1] ={ // right
    { KC_UP,    KC_DOWN  }, // un-shifted
    { KC_LEFT,  KC_RIGHT }  // shifted
  }
};

bool encoder_update_user(uint8_t index, bool clockwise) {
  if (index >= 0 && index < NUM_ENCODERS) {
    tap_code(encoder_table[index][get_shift_held()][clockwise]);
  }
  return true;
}

#endif
