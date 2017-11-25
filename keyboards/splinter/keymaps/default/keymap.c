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

uint32_t _BLC = 0x000000;
uint32_t _ULC = 0x0000FF;
uint32_t _VLC = 0xFFFF00;
uint32_t _DLC = 0x00FF00;
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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  set_key_led_status(record);
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
void layer_color(void) {
  uint8_t layer = biton32(layer_state);

  switch(layer){
  case _UL:
    /* SET_LED(_ULC); */
    for(uint8_t i = 0; i < 50; i++){
      SET_LED_RGB(_ULC, i);
    }
    break;
  case _DL:
    /* SET_LED(_DLC); */
    for(uint8_t i = 0; i < 50; i++){
      SET_LED_RGB(_DLC, i);
    }
    break;
  case _VL:
    /* SET_LED(_VLC); */
    for(uint8_t i = 0; i < 50; i++){
      SET_LED_RGB(_VLC, i);
    }
    break;
  default:
    /* SET_LED(_BLC); */
    for(uint8_t i = 0; i < 50; i++){
      SET_LED_RGB(_BLC, i);
    }
    break;
  }
}

void set_pressed_matrix(void) {
  for (uint8_t c = 0; c < MATRIX_COLS; c++) {
    for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
      if (matrix_is_on(r, c)) {
        row_pressed = r;
        col_pressed = c;
        break;
      }
    }
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [CT_N_TILDE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, n_tilde_finished, n_tilde_reset),
  [CT_ESC_GRV] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, esc_grv_finished, esc_grv_reset),
  [CT_LGUI_ALT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lgui_alt_finished, lgui_alt_reset),
  [CT_RGUI_ALT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rgui_alt_finished, rgui_alt_reset)
};



void matrix_scan_user(void) {
  shifted_layer();
  /* set_pressed_matrix(); */
  /* uint32_t mod_colors[4] = {0}; */
  /* mod_colors[0] = 0xFF0000; */
  /* mod_colors[1] = 0x00FF00; */
  /* mod_colors[2] = 0x0000FF; */
  /* mod_colors[3] = 0xFFFF00; */
  /* led[4].r = 100; */
  /* led[4].g = 0; */
  /* led[4].b = 0; */
  /* ws2812_setleds(led, 5); */
  /* sethsv(0, 100, 100,(LED_TYPE *)&led[2]); */
  /* SET_LED_RGB(mod_colors[1], 49); */
  layer_color();
  rgblight_set();
}

void matrix_init_user(void) {
  init_tap_dance();
}
