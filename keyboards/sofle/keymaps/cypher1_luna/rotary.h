#ifdef ENCODER_ENABLE

#define BOOL_SIZE 2
#define NUM_ENCODERS 2

const uint16_t encoder_table[NUM_ENCODERS][BOOL_SIZE][BOOL_SIZE] = {
  /*left*/ [0] = {
    /*unshifted*/{ /* counter-clockwise */  KC_VOLD, /* clockwise */ KC_VOLU  },
    /*  shifted*/{ /* counter-clockwise */ KC_MNXT,  /* clockwise */ KC_MPRV  }
  },
  /*right*/[1] ={
    /*unshifted*/{ /* counter-clockwise */ KC_UP,    /* clockwise */ KC_DOWN  },
    /*  shifted*/{ /* counter-clockwise */ KC_LEFT,  /* clockwise */ KC_RIGHT }
  }
};

bool encoder_update_user(uint8_t index, bool clockwise) {
  if (index < NUM_ENCODERS) {
    tap_code(encoder_table[index][shift_held][clockwise]);
  }
  return true;
}

#endif
