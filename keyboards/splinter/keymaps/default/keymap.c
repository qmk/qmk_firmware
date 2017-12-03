#include "splinter.h"
#include "action_layer.h"
#include "eeconfig.h"
#include "tap_dance.h"

extern keymap_config_t keymap_config;

enum custom_keycodes {
  CK_SAFE = SAFE_RANGE,
  RGUP,
  RGDWN
};

typedef enum {
  DEFAULT,
  ENABLED,
  DISABLED,
} rbw_led_status;

typedef struct {
  rbw_led_status status;
  uint8_t pos;
} rbw_key_led;

#define _______ KC_TRNS
#define KC_RGUP RGUP
#define KC_RGDWN RGDWN
#define TOTAL_MATRIX_POINTS (MATRIX_ROWS * MATRIX_COLS)

#define _BL 0  // The base layer.
#define _UL 1  // The up layer.
#define _VL 3  // This is for up layer but should be used by MO with the shift key pressed.
#define _DL 2  // The down layer.

#define _RBWC 2  // The count of rainbow leds.
#define _RBW_LCAPS 0
#define _RBW_RCAPS 1

uint8_t cur_lyr = 0;  // current selected layer.
uint8_t dim = 0;      // rgb dimming level.

static rbw_key_led rbw_leds[_RBWC] = {
  [_RBW_LCAPS] = { DEFAULT, 22 },
  [_RBW_RCAPS] = { DEFAULT, 47 }
};

const uint32_t _PC = 0xFF0000;  // LED Red, pressed LED.

const uint32_t _LC[5] = {
  [_BL] = 0x000000,  // LED off
  [_UL] = 0x0000FF,  // LED Blue
  [_VL] = 0xFFFF00,  // LED Yellow
  [_DL] = 0x00FF00   // LED Green
};

const uint8_t _LIGHTS[360] = {
    0,   0,   0,   0,   0,   1,   1,   2,
    2,   3,   4,   5,   6,   7,   8,  11,
   12,   9,  13,  15,  17,  18,  20,  22,
   24,  26,  28,  30,  32,  35,  37,  39,
   42,  44,  47,  49,  52,  55,  58,  60,
   63,  66,  69,  72,  75,  78,  81,  85,
   88,  91,  94,  97, 101, 104, 107, 111,
  114, 117, 121, 124, 127, 131, 134, 137,
  141, 144, 147, 150, 154, 157, 160, 163,
  167, 170, 173, 176, 179, 182, 185, 188,
  191, 194, 197, 200, 202, 205, 208, 210,
  213, 215, 217, 220, 222, 224, 226, 229,
  231, 232, 234, 236, 238, 239, 241, 242,
  244, 245, 246, 248, 249, 250, 251, 251,
  252, 253, 253, 254, 254, 255, 255, 255,
  255, 255, 255, 255, 254, 254, 253, 253,
  252, 251, 251, 250, 249, 248, 246, 245,
  244, 242, 241, 239, 238, 236, 234, 232,
  231, 229, 226, 224, 222, 220, 217, 215,
  213, 210, 208, 205, 202, 200, 197, 194,
  191, 188, 185, 182, 179, 176, 173, 170,
  167, 163, 160, 157, 154, 150, 147, 144,
  141, 137, 134, 131, 127, 124, 121, 117,
  114, 111, 107, 104, 101,  97,  94,  91,
   88,  85,  81,  78,  75,  72,  69,  66,
   63,  60,  58,  55,  52,  49,  47,  44,
   42,  39,  37,  35,  32,  30,  28,  26,
   24,  22,  20,  18,  17,  15,  13,  12,
   11,   9,   8,   7,   6,   5,   4,   3,
    2,   2,   1,   1,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0
};

#define _baseLayer KEYMAP( \
  KC_QUOTE,    KC_COMMA,    KC_DOT,          KC_P,            KC_Y,              KC_F,           KC_G,            KC_C,            KC_R,           KC_L,        \
  CTL_T(KC_A), SFT_T(KC_O), ALT_T(KC_E),     KC_U,            KC_I,              KC_D,           KC_H,            ALT_T(KC_T),     TD(CT_N_TILDE), CTL_T(KC_S), \
  KC_SCOLON,   KC_Q,        KC_J,            KC_K,            KC_X,              KC_B,           KC_M,            KC_W,            KC_V,           KC_Z,        \
  TO(_UL),     MO(_VL),     KC_TAB,          KC_BSPACE,       TD(CT_ESC_GRV),    KC_INS,         KC_HOME,         KC_PGUP,         MO(_VL),        TO(_UL),     \
  TO(_DL),     KC_LCTRL,    LSFT_T(KC_CAPS), TD(CT_LGUI_ALT), LGUI_T(KC_SPC),    RGUI_T(KC_ENT), TD(CT_RGUI_ALT), RSFT_T(KC_CAPS), KC_RCTRL,       TO(_DL))

#define _upLayer KEYMAP( \
  KC_4,          KC_5,          KC_6,          _______,  _______,     _______,  KC_RBRC,  _______,  KC_RGUP,   _______,  \
  LCTL_T(KC_1),  LSFT_T(KC_2),  LALT_T(KC_3),  _______,  _______,     KC_LBRC,  KC_BSLS,  _______,  KC_RGDWN,  _______,  \
  KC_7,          KC_8,          KC_9,          KC_0,     KC_GRV,      KC_SLSH,  _______,  _______,  _______,   _______,  \
  TO(_BL),       _______,       _______,       _______,  _______,     KC_DEL,   KC_END,   KC_PGDN,  _______,   TO(_BL),  \
  TO(_DL),       KC_MPLY,       KC_MPRV,       KC_MNXT,  KC_ENT,      KC_SPC,   _______,  _______,  _______,   TO(_DL))

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

#define SET_LED_RGB_HEX(v, p) setrgb( \
  ((v >> 16) & 0xFF) >> dim, \
  ((v >> 8) & 0xFF) >> dim,  \
  (v & 0xFF) >> dim,         \
  (LED_TYPE *)&led[p])

#define SET_LED_RGB(r, g, b, p) setrgb( \
  r >> dim, \
  g >> dim, \
  b >> dim, \
  (LED_TYPE *)&led[p])

void set_layer_led(uint32_t c) {
  for (uint8_t i = 0; i < TOTAL_MATRIX_POINTS; i++) {
    SET_LED_RGB_HEX(c, i);
  }
}

void layer_led(void) {
  static uint8_t pl = 0;

  if (pl != cur_lyr) {
    pl = cur_lyr;
    set_layer_led(_LC[cur_lyr]);
  }

  rgblight_set();
}

void set_key_led(keyrecord_t *record) {
  static const uint8_t base = 5;

  uint8_t r = record->event.key.row;
  uint8_t c = record->event.key.col;
  uint8_t pos = r % 2 == 0 ? r * base + c : r * base + (base - c + 1);

  if (record->event.pressed) {
    SET_LED_RGB_HEX(_PC, pos);
  } else {
    SET_LED_RGB_HEX(_LC[cur_lyr], pos);
  }

  rgblight_set();
}

void rainbow_loop(void) {
  static uint16_t last_timer = 0;
  static uint16_t i = 0;
  static uint8_t r, g, b;

  if (timer_elapsed(last_timer) < 8) {
    return;
  }

  if (i >= 260) {
    i = 0;
  }

  last_timer = timer_read();
  r = _LIGHTS[(i + 120) % 360];
  g = _LIGHTS[i];
  b = _LIGHTS[(i + 240) % 360];

  i++;

  for (uint8_t i = 0; i < _RBWC; i++) {
    switch(rbw_leds[i].status){
    case ENABLED:
      SET_LED_RGB(r, g, b, rbw_leds[i].pos);
      break;
    case DISABLED:
      SET_LED_RGB_HEX(_LC[cur_lyr], rbw_leds[i].pos);
      rbw_leds[i].status = DEFAULT;
      break;
    default:
      break;
    }
  }

  rgblight_set();
}

bool led_brightness(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case RGUP:
    if (record->event.pressed && dim > 0) {
      dim--;
    }

    return true;
    break;
  case RGDWN:
    if (record->event.pressed && dim < 8) {
      dim++;
    }

    return true;
    break;
  default:
    return false;
    break;
  }
}

void shifted_layer(void) {
  static bool is_shifted = false;

  if (cur_lyr == _VL) {
    register_code(KC_LSFT);
    is_shifted = true;
  } else {
    if (is_shifted) {
      unregister_code(KC_LSFT);
      is_shifted = false;
    }
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [CT_N_TILDE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, n_tilde_finished, n_tilde_reset),
  [CT_ESC_GRV] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, esc_grv_finished, esc_grv_reset),
  [CT_LGUI_ALT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lgui_alt_finished, lgui_alt_reset),
  [CT_RGUI_ALT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rgui_alt_finished, rgui_alt_reset)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  set_key_led(record);

  if (led_brightness(keycode, record)) {
    set_layer_led(_LC[cur_lyr]);
    return false;
  }

  return true;
}

void matrix_scan_user(void) {
  cur_lyr = biton32(layer_state);
  shifted_layer();
  layer_led();
  rainbow_loop();
}

void matrix_init_user(void) {
  init_tap_dance();
}

void led_set_kb(uint8_t usb_led) {
  if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
    rbw_leds[_RBW_LCAPS].status = ENABLED;
    rbw_leds[_RBW_RCAPS].status = ENABLED;
  } else {
    rbw_leds[_RBW_LCAPS].status = DISABLED;
    rbw_leds[_RBW_RCAPS].status = DISABLED;
  }
}
