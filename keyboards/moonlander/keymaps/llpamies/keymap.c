#include QMK_KEYBOARD_H

#include "llpamies.h"

// Colors.
#define CL_BLK { RGB_BLACK }
#define CL_RED { RGB_RED }
#define CL_GRE { RGB_GREEN }
#define CL_BLU { RGB_BLUE }
#define CL_YEL { RGB_YELLOW }
#define CL_MAG { RGB_MAGENTA }
#define CL_CIA { RGB_CYAN }
#define CL_WHI { RGB_WHITE }

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_COLEMAK] = LAYOUT_moonlander(
   _______,   UNIQ(KC_1),  UNIQ(KC_2), UNIQ(KC_3),    UNIQ(KC_4), UNIQ(KC_5), _______,    KC_AUDIO_MUTE,     UNIQ(KC_6), UNIQ(KC_7), UNIQ(KC_8),     UNIQ(KC_9), UNIQ(KC_0), _______,
   KC_TAB,    KC_Q,        KC_W,       KC_F,          KC_P,       KC_B,       _______,    KC_AUDIO_VOL_UP,   KC_J,       KC_L,       KC_U,           KC_Y,       KC_SCOLON,  KC_BSLASH,
   KC_ESCAPE, MY_A,        MY_R,       MY_S,          KC_T,       KC_G,       LCTL(KC_A), KC_AUDIO_VOL_DOWN, KC_M,       KC_N,       MY_E,           MY_I,       MY_O,       KC_ENTER,
   KC_LSHIFT, KC_Z,        KC_X,       KC_C,          KC_D,       KC_V,                                      KC_K,       KC_H,       KC_COMMA,       KC_DOT,     KC_SLASH,   KC_QUOTE,
   KC_LCTRL,  KC_CAPSLOCK, KC_LALT,    UNIQ(KC_LEFT), SYMB_BSPC,  _______,                                   _______,    NAV_SPC,    UNIQ(KC_RIGHT), KC_COLN,    _______,    _______,
                                                      KC_DELETE,  _______,    _______,    _______,           _______,    KC_TAB
 ),

[_SYMBOL] = LAYOUT_moonlander(
  _______,  _______, _______, _______,     _______,    _______, _______, _______, _______,   _______, _______,  _______, _______,  _______,
  KC_TILD,  KC_EXLM, KC_AT,   KC_HASH,     KC_DLR,      KC_PERC, _______, _______, KC_CIRC,   KC_AMPR, KC_ASTR,  KC_LPRN, KC_RPRN,  KC_PIPE,
  KC_GRAVE, KC_1,    KC_2,    KC_3,        KC_4,        KC_5,    _______, _______, KC_6,      KC_7,    KC_8,     KC_9,    KC_0,     KC_BSLASH,
  _______,  KC_LCBR, KC_RCBR, KC_LBRACKET, KC_RBRACKET, KC_COLN,                   KC_SCOLON, KC_UNDS, KC_MINUS, KC_PLUS, KC_EQUAL, _______,
  _______,  _______, _______, _______,     _______,     _______,                   _______,   _______, _______,  _______, _______,  _______,
                                           _______,     _______, _______, _______, _______,   _______
),

[_NAVIGATION] = LAYOUT_moonlander(
  _______, _______,  _______,   _______, _______, _______, _______, _______, _______,    _______,    _______,    _______,    _______, _______,
  _______, VIM_QUIT, VIM_WRITE, _______, _______, _______, _______, _______, LCTL(KC_H), LCTL(KC_J), LCTL(KC_K), LCTL(KC_L), _______, _______,
  _______, _______,  _______,   _______, _______, _______, _______, _______, KC_LEFT,    KC_DOWN,    KC_UP,      KC_RIGHT,   _______, _______,
  _______, _______,  VIM_SAVE,  _______, _______, _______,                   KC_HOME,    KC_PGDOWN,  KC_PGUP,    KC_END,     _______, _______,
  _______, _______,  _______,   _______, _______, _______,                   _______,    _______,    _______,    _______,    _______, _______,
                                         _______, _______, _______, _______, _______,    _______
  ),

[_ADJUST] = LAYOUT_moonlander(
  _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RESET,
  _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______,     _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, _______,
  WEBUSB_PAIR, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______
  ),
};

void keyboard_post_init_user(void) { rgb_matrix_enable(); }

const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
[_COLEMAK] = {
  // Left side.
  CL_BLK, CL_GRE, CL_RED, CL_WHI, CL_WHI,
  CL_CIA, CL_GRE, CL_GRE, CL_GRE, CL_MAG,
  CL_CIA, CL_GRE, CL_GRE, CL_GRE, CL_WHI,
  CL_CIA, CL_GRE, CL_GRE, CL_GRE, CL_WHI,
  CL_CIA, CL_GRE, CL_GRE, CL_GRE, CL_RED,
  CL_CIA, CL_GRE, CL_GRE, CL_GRE,
  CL_BLK, CL_BLK, CL_MAG,
  CL_GRE, CL_BLK, CL_BLK, CL_BLK, // Thumb cluster.
  // Right side.
  CL_BLK, CL_GRE, CL_RED, CL_WHI, CL_BLK,
  CL_CIA, CL_GRE, CL_GRE, CL_GRE, CL_BLK,
  CL_CIA, CL_GRE, CL_GRE, CL_GRE, CL_GRE,
  CL_CIA, CL_GRE, CL_GRE, CL_GRE, CL_MAG,
  CL_CIA, CL_GRE, CL_GRE, CL_GRE, CL_RED,
  CL_CIA, CL_GRE, CL_GRE, CL_GRE,
  CL_WHI, CL_WHI, CL_WHI,
  CL_GRE, CL_BLK, CL_BLK, CL_BLK // Thumb cluster.
},

[_SYMBOL] = {
  // Left side.
  CL_BLK, CL_CIA, CL_CIA, CL_BLK, CL_BLK,
  CL_BLK, CL_CIA, CL_WHI, CL_RED, CL_BLK,
  CL_BLK, CL_CIA, CL_WHI, CL_RED, CL_BLK,
  CL_BLK, CL_CIA, CL_WHI, CL_GRE, CL_BLK,
  CL_BLK, CL_CIA, CL_WHI, CL_GRE, CL_BLK,
  CL_BLK, CL_CIA, CL_WHI, CL_MAG,
  CL_BLK, CL_BLK, CL_BLK,
  CL_BLK, CL_BLK, CL_BLK, CL_BLK,
  // Right side.
  CL_BLK, CL_CIA, CL_CIA, CL_BLK, CL_BLK,
  CL_BLK, CL_CIA, CL_WHI, CL_WHI, CL_BLK,
  CL_BLK, CL_CIA, CL_WHI, CL_WHI, CL_BLK,
  CL_BLK, CL_CIA, CL_WHI, CL_MAG, CL_BLK,
  CL_BLK, CL_CIA, CL_WHI, CL_MAG, CL_BLK,
  CL_BLK, CL_CIA, CL_WHI, CL_MAG,
  CL_BLK, CL_BLK, CL_BLK,
  CL_BLK, CL_BLK, CL_BLK, CL_BLK},

[_NAVIGATION] = {
  // Left side.
  CL_BLK, CL_BLK, CL_BLK, CL_BLK, CL_BLK,
  CL_BLK, CL_WHI, CL_BLK, CL_BLK, CL_BLK,
  CL_BLK, CL_WHI, CL_BLK, CL_WHI, CL_BLK,
  CL_BLK, CL_BLK, CL_BLK, CL_BLK, CL_BLK,
  CL_BLK, CL_BLK, CL_BLK, CL_BLK, CL_BLK,
  CL_BLK, CL_BLK, CL_BLK, CL_BLK,
  CL_BLK, CL_BLK, CL_BLK,
  CL_BLK, CL_BLK, CL_BLK, CL_BLK,
  // Right side.
  CL_BLK, CL_BLK, CL_BLK, CL_BLK, CL_BLK,
  CL_BLK, CL_BLK, CL_BLK, CL_BLK, CL_BLK,
  CL_BLK, CL_RED, CL_GRE, CL_MAG, CL_BLK,
  CL_BLK, CL_RED, CL_GRE, CL_MAG, CL_BLK,
  CL_BLK, CL_RED, CL_GRE, CL_MAG, CL_BLK,
  CL_BLK, CL_RED, CL_GRE, CL_MAG,
  CL_BLK, CL_BLK, CL_BLK,
  CL_BLK, CL_BLK, CL_BLK, CL_BLK},

[_ADJUST] = {
  // Left side.
  CL_BLK, CL_BLK, CL_BLK, CL_BLK, CL_MAG,
  CL_BLK, CL_BLK, CL_BLK, CL_BLK, CL_BLK,
  CL_BLK, CL_BLK, CL_BLK, CL_BLK, CL_BLK,
  CL_BLK, CL_BLK, CL_BLK, CL_BLK, CL_BLK,
  CL_BLK, CL_BLK, CL_BLK, CL_BLK, CL_BLK,
  CL_BLK, CL_BLK, CL_BLK, CL_BLK,
  CL_BLK, CL_BLK, CL_BLK,
  CL_BLK, CL_BLK, CL_BLK, CL_BLK,
  // Right side.
  CL_MAG, CL_BLK, CL_BLK, CL_BLK, CL_BLK,
  CL_BLK, CL_BLK, CL_BLK, CL_BLK, CL_BLK,
  CL_BLK, CL_BLK, CL_BLK, CL_BLK, CL_BLK,
  CL_BLK, CL_BLK, CL_BLK, CL_BLK, CL_BLK,
  CL_BLK, CL_BLK, CL_BLK, CL_BLK, CL_BLK,
  CL_BLK, CL_BLK, CL_BLK, CL_BLK,
  CL_BLK, CL_BLK, CL_BLK,
  CL_BLK, CL_BLK, CL_BLK, CL_BLK},
};

void set_layer_color(int layer) {
  for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
    uint8_t r = pgm_read_byte(&ledmap[layer][i][0]);
    uint8_t g = pgm_read_byte(&ledmap[layer][i][1]);
    uint8_t b = pgm_read_byte(&ledmap[layer][i][2]);
    rgb_matrix_set_color(i, r, g, b);
  }
}

void rgb_matrix_indicators_user(void) {
  if (g_suspend_state || keyboard_config.disable_layer_led) {
    return;
  }
  switch (biton32(layer_state)) {
    case 0:
      set_layer_color(0);
      break;
    case 1:
      set_layer_color(1);
      break;
    case 2:
      set_layer_color(2);
      break;
    case 3:
      set_layer_color(3);
      break;
    default:
      if (rgb_matrix_get_flags() == LED_FLAG_NONE) {
        rgb_matrix_set_color_all(0, 0, 0);
      }
      break;
  }
}
