// This is the canonical layout file for the Quantum project. If you want to add another keyboard,
// this is the style you want to emulate.

#include "M10A.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum layers {
  _LAYER0,
  _LAYER1
};

enum keycodes {
  BACKLIT
};

// // Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_LAYER0] = {{KC_P7,   KC_P8,   KC_P9  }, {KC_P4,   KC_P5,   KC_P6  }, {KC_P1,   KC_P2,   KC_P3  }, {XXXXXXX, XXXXXXX, LT(_LAYER1, KC_P0)}},
  [_LAYER1] = {{KC_NLCK, _______, BACKLIT}, {_______, _______, _______}, {_______, _______, RESET  }, {XXXXXXX, XXXXXXX, _______}}
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
      } else {
        unregister_code(KC_RSFT);
      }
      return false;
      break;
  }
  return true;
}

void matrix_init_user(void) {
    #ifdef AUDIO_ENABLE
        startup_user();
    #endif
}

