#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_planck_mit(
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
    KC_ESC, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_ENT,
    KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_UP,
    KC_LCTL, KC_LGUI, KC_LALT, KC_LBRC, KC_MINS, LT(1, KC_SPC), KC_EQL, KC_RBRC, KC_LEFT, KC_DOWN, KC_RGHT,
    KC_VOLD, KC_VOLU, KC_PGDN, KC_PGUP),
  [1] = LAYOUT_planck_mit(
    KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BSPC, KC_TRNS, KC_DEL, KC_TRNS, KC_TRNS, KC_BSLS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
};

extern rgblight_config_t rgblight_config;
int RGB_LAYER0_mode = 6;
static uint8_t current_layer = 0;
static bool has_layer_changed = true;
uint16_t i = 0;
uint16_t j = 0;
static uint16_t RGB_encoder_timer;
static uint16_t RGB_encoder_timer2;
static uint8_t RGB_encoder_dir = 0;

const uint8_t RGBLED_RAINBOW_MOOD_INTERVALS[] PROGMEM = {
  30,
  5,
  -5
};

void matrix_init_user(void) {
  RGB_encoder_timer = timer_read();
  RGB_encoder_timer2 = timer_read();
}

void matrix_scan_user(void) {
  uint8_t layer = biton32(layer_state);

  if (RGB_encoder_dir != 0) {
    if (timer_elapsed(RGB_encoder_timer) > 1400) {
      RGB_encoder_dir = 0;
      rgblight_mode(RGB_LAYER0_mode);
    } else {
      if (timer_elapsed(RGB_encoder_timer2) > 700) {
        rgblight_setrgb(0, 0, 0);
        RGB_encoder_timer2 = timer_read();
      }
      if (timer_elapsed(RGB_encoder_timer2) > 80) {
        if (RGB_encoder_dir == 1) {
          rgblight_setrgb_at(128, 128, 0, 19);
        } else {
          rgblight_setrgb_at(128, 128, 0, 16);
        }
      }
      if (timer_elapsed(RGB_encoder_timer2) > 180) {
        if (RGB_encoder_dir == 1) {
          rgblight_setrgb_at(160, 160, 0, 8);
        } else {
          rgblight_setrgb_at(160, 160, 0, 3);
        }
      }
      if (timer_elapsed(RGB_encoder_timer2) > 280) {
        if (RGB_encoder_dir == 1) {
          rgblight_setrgb_at(192, 192, 0, 9);
        } else {
          rgblight_setrgb_at(192, 192, 0, 2);
        }
      }
      if (timer_elapsed(RGB_encoder_timer2) > 400) {
        if (RGB_encoder_dir == 1) {
            rgblight_setrgb_at(224, 224, 0, 10);
          } else {
            rgblight_setrgb_at(224, 224, 0, 1);
          }
      }
    }
  }

  /* layer rgb */
  if (layer != current_layer) {
    has_layer_changed = true;
    current_layer = layer;
  }
  if (has_layer_changed) {
    if (layer == 0) {
      rgblight_mode(RGB_LAYER0_mode);
    } else {
      rgblight_mode(1);
      for (i = 0; i < 48; i++) {
        (i > 41) ? (j = i - 1) : (j = i);
        uint16_t kc = keymap_key_to_keycode(layer, (keypos_t) {.row = 0, .col = i
        });
        if (kc == KC_TRNS) {
          setrgb(5, 5, 5, (LED_TYPE * ) & led[j]); /* TRNS color 0-255*/
        } else if (kc == KC_NO) {
          setrgb(0, 0, 0, (LED_TYPE * ) & led[j]); /* NO color 0-255*/
        } else {
          if (layer == 1) {
            setrgb(128, 64, 0, (LED_TYPE * ) & led[j]); /* 1 layer 0-255*/
          } else if (layer == 2) {
            setrgb(0, 64, 128, (LED_TYPE * ) & led[j]); /* 2*/
          } else if (layer == 3) {
            setrgb(64, 128, 0, (LED_TYPE * ) & led[j]); /* 3*/
          } else if (layer == 4) {
            setrgb(0, 128, 64, (LED_TYPE * ) & led[j]); /* 4*/
          } else if (layer == 5) {
            setrgb(128, 0, 128, (LED_TYPE * ) & led[j]); /* 5*/
          } else if (layer == 6) {
            setrgb(128, 0, 128, (LED_TYPE * ) & led[j]); /* 6*/
          } else if (layer == 7) {
            setrgb(128, 128, 0, (LED_TYPE * ) & led[j]); /* 7*/
          } else if (layer == 8) {
            setrgb(0, 128, 128, (LED_TYPE * ) & led[j]); /* 8*/
          } else if (layer == 9) {
            setrgb(128, 192, 64, (LED_TYPE * ) & led[j]); /* 9*/
          } else if (layer == 10) {
            setrgb(64, 192, 128, (LED_TYPE * ) & led[j]); /* 10*/
          } else if (layer == 11) {
            setrgb(128, 64, 192, (LED_TYPE * ) & led[j]); /* 11*/
          } else if (layer == 12) {
            setrgb(64, 128, 192, (LED_TYPE * ) & led[j]); /* 12*/
          } else if (layer == 13) {
            setrgb(128, 192, 0, (LED_TYPE * ) & led[j]); /* 13*/
          } else if (layer == 14) {
            setrgb(192, 0, 128, (LED_TYPE * ) & led[j]); /* 14*/
          } else if (layer == 15) {
            setrgb(0, 192, 128, (LED_TYPE * ) & led[j]); /* 15*/
          }
        }
      }
      rgblight_set();
    }
    has_layer_changed = false;
  }
  /* end of layer rgb */
}

bool process_record_user(uint16_t keycode, keyrecord_t * record) {
  switch (keycode) {
  case RGB_MOD:
    RGB_LAYER0_mode = rgblight_config.mode;
    break;
  default:
    return (true);
  }
  return (true);
}

void encoder_update_user(uint8_t index, bool clockwise) {
  RGB_encoder_timer = timer_read();
  RGB_encoder_timer2 = timer_read();
  uint8_t layer = biton32(layer_state);
  if (clockwise) {
    RGB_encoder_dir = 1;
  } else {
    RGB_encoder_dir = -1;
  }
  if (index == 0) /* Right encoder */ {
    if (clockwise) {
      register_code(keymap_key_to_keycode(layer, (keypos_t) {.row = 4, .col = 11
      }));
      unregister_code(keymap_key_to_keycode(layer, (keypos_t) {.row = 4, .col = 11
      }));
    } else {
      register_code(keymap_key_to_keycode(layer, (keypos_t) {.row = 4, .col = 10
      }));
      unregister_code(keymap_key_to_keycode(layer, (keypos_t) {.row = 4, .col = 10
      }));
    }
  } else if (index == 1) /* Left encoder */ {
    if (clockwise) {
      register_code(keymap_key_to_keycode(layer, (keypos_t) {.row = 4, .col = 1
      }));
      unregister_code(keymap_key_to_keycode(layer, (keypos_t) {.row = 4, .col = 1
      }));
    } else {
      register_code(keymap_key_to_keycode(layer, (keypos_t) {.row = 4, .col = 0
      }));
      unregister_code(keymap_key_to_keycode(layer, (keypos_t) {.row = 4, .col = 0
      }));
    }
  }
}
