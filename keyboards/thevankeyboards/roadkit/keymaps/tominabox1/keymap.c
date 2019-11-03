#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

enum layers {
    _BASE,
	  _NUMPAD,
    _ARROW
};

enum combo_events {
  NUM_TO_BASE,
  SPCL_RST,
  ARROW_TO_BASE,
  BASE_TO_NUM,
  NUM_BACKSPACE,
  BASE_TO_ARROW,
  NUMPAD_RET
};

const uint16_t PROGMEM num_to_base[] = {KC_PENT, KC_P0, COMBO_END};
const uint16_t PROGMEM spcl_rst[] = {KC_VOLU, KC_VOLD, COMBO_END};
const uint16_t PROGMEM arrow_to_base[] = {KC_LEFT, KC_DOWN, COMBO_END};
const uint16_t PROGMEM base_to_num[] = {KC_ENT, LGUI(KC_L), COMBO_END};
const uint16_t PROGMEM num_back[] = {KC_P9, KC_PAST, COMBO_END};
const uint16_t PROGMEM base_to_arrow[] = {KC_ENT, C(S(KC_ESC)), COMBO_END};
const uint16_t PROGMEM numpad_ret[] = {KC_PPLS, KC_PSLS, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [NUM_TO_BASE] = COMBO_ACTION(num_to_base),
  [SPCL_RST] = COMBO_ACTION(spcl_rst),
  [ARROW_TO_BASE] = COMBO_ACTION(arrow_to_base),
  [BASE_TO_NUM] = COMBO_ACTION(base_to_num),
  [NUM_BACKSPACE] = COMBO_ACTION(num_back),
  [BASE_TO_ARROW] = COMBO_ACTION(base_to_arrow),
  [NUMPAD_RET] = COMBO_ACTION(numpad_ret),
};

void process_combo_event(uint8_t combo_index, bool pressed) {
  switch(combo_index) {
    case NUM_TO_BASE:
    if (pressed) {
      layer_move(_BASE);
    }
    break;
    case SPCL_RST:
    if (pressed) {
      reset_keyboard();
    }
    break;
    case ARROW_TO_BASE:
    if (pressed) {
      layer_move(_BASE);
    }
    break;
    case BASE_TO_NUM:
    if (pressed) {
      layer_move(_NUMPAD);
    }
    break;
    case NUM_BACKSPACE:
    if (pressed) {
      tap_code16(KC_BSPC);
    }
    break;
    case BASE_TO_ARROW:
    if (pressed) {
      layer_move(_ARROW);
    }
    break;
    case NUMPAD_RET:
    if (pressed) {
      tap_code16(KC_PENT);
    }
    break;
  }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* | PREV | PAUSE | NEXT | VOLUP |
     |_ARROW|       |      | VOLDN |
     |CTLDEL|CTLSHC |CTLSHD| ENT   | EA Delete, Custom line, and Direct
     |_NUMP | LOCK  | TASK | RESET |  */

   [_BASE] = LAYOUT_ortho_4x4( /* Numpad */
    KC_MPRV, KC_MPLY,   KC_MNXT,   KC_VOLU,
    TG(_ARROW), KC_NO,   KC_NO,   KC_VOLD,
    C(KC_DEL), C(S(KC_C)),   C(S(KC_D)),   KC_NO,
    KC_ENT, LGUI(KC_L),   C(S(KC_ESC)), KC_NO
  ),
  /* | 7    | 8     | 9    | *     |
     | 4    | 5     | 6    | -     |
     | 1    | 2     | 3    | +     |
     |ENT   | 0     | .    | /     |  */

  [_NUMPAD] = LAYOUT_ortho_4x4( /* Numpad */
    KC_P7, KC_P8,   KC_P9,   KC_PAST,
    KC_P4, KC_P5,   KC_P6,   KC_PMNS,
    KC_P1, KC_P2,   KC_P3,   KC_PPLS,
    KC_PENT, KC_P0, KC_PDOT, KC_PSLS
  ),
  /* | F5   | F6    |      | S PUP |
     |      |       |      | S PDN |
     |HOME  |  UP   | END  | P UP  |
     | LEFT | DOWN  | RIGHT| P DN  |  */

  [_ARROW] = LAYOUT_ortho_4x4( /* Numpad */
    KC_F5, KC_F6,   KC_NO,   S(KC_PGUP),
    KC_NO, KC_UP,   KC_NO,   S(KC_PGDN),
    KC_HOME, KC_UP,   KC_END,   KC_PGUP,
    KC_LEFT, KC_DOWN, KC_RIGHT,  KC_PGDN
  ),
};
