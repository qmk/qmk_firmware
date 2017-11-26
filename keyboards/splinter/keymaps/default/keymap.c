#include "splinter.h"
#include "action_layer.h"
#include "eeconfig.h"
#include "tap_dance.h"

extern keymap_config_t keymap_config;

#define _______ KC_TRNS
/* extern struct cRGB led[5]; */

#define _BL 0 // The base layer.
#define _UL 1 // The up layer.
#define _VL 3 // This is for up layer but should be used by MO with the shift key pressed.
#define _DL 2 // The down layer.

#define TOTAL_MATRIX_POINTS (MATRIX_ROWS * MATRIX_COLS)

const uint32_t _PC = 0xFF0000;
const uint32_t _LC[5] = { \
  // LED off
  [_BL] = 0x000000, \
  // LED Blue
  [_UL] = 0x0000FF, \
  // LED Yellow
  [_VL] = 0xFFFF00, \
  // LED Green
  [_DL] = 0x00FF00  \
};

uint8_t current_layer = 0;
uint32_t _pressedC = 0xFF0000;
uint8_t rgb_dimming = 7;
bool _key_pressed[50];

#define _baseLayer KEYMAP( \
  KC_QUOTE,    KC_COMMA,    KC_DOT,          KC_P,            KC_Y,              KC_F,           KC_G,            KC_C,            KC_R,           KC_L,        \
  CTL_T(KC_A), SFT_T(KC_O), ALT_T(KC_E),     KC_U,            KC_I,              KC_D,           KC_H,            ALT_T(KC_T),     TD(CT_N_TILDE), CTL_T(KC_S), \
  KC_SCOLON,   KC_Q,        KC_J,            KC_K,            KC_X,              KC_B,           KC_M,            KC_W,            KC_V,           KC_Z,        \
  TO(_UL),     MO(_VL),     KC_TAB,          KC_BSPACE,       TD(CT_ESC_GRV),    KC_INS,         KC_HOME,         KC_PGUP,         MO(_VL),        TO(_UL),     \
  TO(_DL),     KC_LCTRL,    LSFT_T(KC_CAPS), TD(CT_LGUI_ALT), LGUI_T(KC_SPC),    RGUI_T(KC_ENT), TD(CT_RGUI_ALT), RSFT_T(KC_CAPS), KC_RCTRL,       TO(_DL))

#define _upLayer KEYMAP( \
  KC_4,          KC_5,          KC_6,          _______,  _______,     _______,  KC_RBRC,  _______,  _______,  _______,  \
  LCTL_T(KC_1),  LSFT_T(KC_2),  LALT_T(KC_3),  _______,  _______,     KC_LBRC,  KC_BSLS,  _______,  _______,  _______,  \
  KC_7,          KC_8,          KC_9,          KC_0,     KC_GRV,      KC_SLSH,  _______,  _______,  _______,  _______,  \
  TO(_BL),       _______,       _______,       _______,  _______,     KC_DEL,   KC_END,   KC_PGDN,  _______,  TO(_BL),  \
  TO(_DL),       KC_MPLY,       KC_MPRV,       KC_MNXT,  KC_ENT,      KC_SPC,   _______,  _______,  _______,  TO(_DL))

#define _downLayer KEYMAP( \
  KC_F4,          KC_F5,          KC_F6,          KC_F12,   _______,     _______,   KC_RPRN,   _______,   KC_UP,    KC_RIGHT,  \
  LCTL_T(KC_F1),  LSFT_T(KC_F2),  LALT_T(KC_F3),  KC_F11,   _______,     KC_LPRN,   KC_EQUAL,  KC_LEFT,   KC_DOWN,  _______,   \
  KC_F7,          KC_F8,          KC_F9,          KC_F10,   _______,     KC_MINUS,  _______,   _______,   _______,  _______,   \
  TO(_UL),        _______,        _______,        _______,  _______,     KC_PSCR,   KC_SLCK,   KC_PAUSE,  _______,  TO(_UL),   \
  TO(_BL),        KC_MUTE,        KC_VOLD,        KC_VOLU,  _______,     _______,   _______,   _______,   _______,  TO(_BL))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BL] = _baseLayer,
  [_UL] = _upLayer,
  [_DL] = _downLayer,
  [_VL] = _upLayer
};

#define SET_LED_RGB(val, led_num) setrgb(((val >> 16) & 0xFF) >> rgb_dimming, ((val >> 8) & 0xFF) >> rgb_dimming, (val & 0xFF) >> rgb_dimming, (LED_TYPE *)&led[led_num])

void set_key_led_status(keyrecord_t *record) {
  uint8_t base = 5;
  uint8_t r = record->event.key.row;
  uint8_t c = record->event.key.col;
  bool pressed = record->event.pressed;

  if (record->event.key.row % 2 == 0) {
    _key_pressed[r * base + c] = pressed;
  } else {
    _key_pressed[r * base + (base - (c + 1))] = pressed;
  }
  /* for (uint8_t r = 0; r < MATRIX_ROWS; r++) { */
  /*   if (r % 2 == 0) { */
  /*     for (uint8_t c = 0; c < MATRIX_COLS; c++) { */
  /*       _key_pressed[r * base + c] = */
  /*     } */
  /*   } */
  /* } */
}

uint8_t base = 5;


void process_led(keyrecord_t *record) {
  uint8_t pos = 0;
  uint8_t r = record->event.key.row;
  uint8_t c = record->event.key.col;
  /* uint8_t ls = biton32(layer_state); */

  /* if (current_layer != ls) { */
  /*   current_layer = ls; */
  /*   switch (current_layer) { */
  /*   case _UL: */
  /*     set_layer_led(_ULC); */
  /*     break; */
  /*   case _DL: */
  /*     set_layer_led(_DLC); */
  /*     break; */
  /*   case _VL: */
  /*     set_layer_led(_VLC); */
  /*     break; */
  /*   default: */
  /*     set_layer_led(_BLC); */
  /*     break; */
  /*   } */
  /* } */

  if (r % 2 == 0) {
    pos = r * base + c;
    SET_LED_RGB(_pressedC, pos);
  } else {
    pos = r * base + (base - (c + 1));
    SET_LED_RGB(_pressedC, pos);
  }

}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  /* set_key_led_status(record); */
  /* uint8_t base = 5; */
  /* uint8_t r = record->event.key.row; */
  /* uint8_t c = record->event.key.col; */

  /* if (record->event.key.row % 2 == 0) { */
  /*   xprintf("Pressed: %d \n", record->event.key.row * base + record->event.key.col); */
  /* } else { */
  /*   xprintf("Pressed: %d \n", record->event.key.row * base + (base - (record->event.key.col + 1))); */
  /* } */

  process_led(record);

  /* rgblight_set(); */
  return true;
}


void shifted_layer(void) {
  uint8_t layer = biton32(layer_state);
  static uint8_t current_layer = 0;
  static bool has_layer_changed = false;
  static bool is_shifted = false;

  if(layer != current_layer) {
    has_layer_changed = true;
    current_layer = layer;
  }

  if(has_layer_changed) {
    if(layer == _VL) {
      register_code(KC_LSFT);
      is_shifted = true;
    } else {
      if(is_shifted) {
        unregister_code(KC_LSFT);
        is_shifted = false;
      }

      has_layer_changed = false;
    }
  }
}

void SET_LED(uint32_t color) {
  uint8_t base = 5;
  uint8_t pos = 0;
  for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
    if (r % 2 == 0) {
      for (uint8_t c = 0; c < MATRIX_COLS; c++) {
        pos = r * base + c;
        if (_key_pressed[pos]) {
          SET_LED_RGB(_pressedC, pos);
        } else {
          SET_LED_RGB(color, pos);
        }
      }
    } else {
      for (uint8_t c = 4; c >= 0; c--) {
        pos = r * base + c;
        if (_key_pressed[pos]) {
          SET_LED_RGB(_pressedC, pos);
        } else {
          SET_LED_RGB(color, pos);
        }
      }
    }
  }
}

void set_layer_led(uint32_t c) {
  for (uint8_t i = 0; i < TOTAL_MATRIX_POINTS; i++) {
    SET_LED_RGB(c, i);
  }
}

void layer_led(void) {
  uint8_t ls = biton32(layer_state);

  if (current_layer != ls) {
    current_layer = ls;
    set_layer_led(_LC[current_layer]);
  };
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [CT_N_TILDE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, n_tilde_finished, n_tilde_reset),
  [CT_ESC_GRV] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, esc_grv_finished, esc_grv_reset),
  [CT_LGUI_ALT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lgui_alt_finished, lgui_alt_reset),
  [CT_RGUI_ALT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rgui_alt_finished, rgui_alt_reset)
};



void matrix_scan_user(void) {
  shifted_layer();
  layer_led();
  rgblight_set();
}

void matrix_init_user(void) {
  init_tap_dance();
}
