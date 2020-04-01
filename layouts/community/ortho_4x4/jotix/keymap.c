#include QMK_KEYBOARD_H

enum layers {
  _NUMPAD,
  _GAMEPAD,
  _FN
};

static bool is_p0_pressed;
static bool is_p7_pressed;
static bool is_pmns_pressed;

#define TGGAME TG(_GAMEPAD)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_NUMPAD] = LAYOUT_ortho_4x4 ( 
  KC_P7,  KC_P8,  KC_P9,  KC_PMNS,
  KC_P4,  KC_P5,  KC_P6,  KC_PPLS,
  KC_P1,  KC_P2,  KC_P3,  MO(_FN),
  KC_P0,  KC_PDOT,KC_PSLS,KC_PAST 
),

[_GAMEPAD] = LAYOUT_ortho_4x4 (
  KC_1,   KC_2,   KC_3,   KC_4,
  KC_5,   KC_6,   KC_7,   KC_8,
  KC_Q,   KC_W,   KC_E,   _______,
  KC_A,   KC_S,   KC_D,   KC_LSFT 
),

[_FN] = LAYOUT_ortho_4x4 (
  KC_9,   KC_0,   KC_MINS,KC_EQL,
  KC_NLCK,_______,_______,_______,
  _______,_______,_______,_______,
  TGGAME, _______,_______,_______
)
};

uint32_t layer_state_set_user(uint32_t state) {
  #ifdef JOTPAD16_LEDS
  if (biton32(state) == _FN) {
    writePinHigh(JOTPAD16_LED1);
  } else {
    writePinLow(JOTPAD16_LED1);
  }
  if (biton32(state) == _GAMEPAD) {
    writePinHigh(JOTPAD16_LED2);
  } else {
    writePinLow(JOTPAD16_LED2);
  }
  #endif
  return state;
}

bool led_update_user(led_t led_state) {
  // NumLock allways on
  if (!led_state.num_lock) {
    tap_code(KC_NUMLOCK);
  }
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_P0:
      is_p0_pressed = record->event.pressed;
      break;
    case KC_P7:
      is_p7_pressed = record->event.pressed;
      break;
    case KC_PMNS:
      is_pmns_pressed = record->event.pressed;
      break;
  };
  return true;
}

void matrix_scan_user(void) {
  if (is_p0_pressed && is_p7_pressed && is_pmns_pressed) {
    reset_keyboard();
  }
}