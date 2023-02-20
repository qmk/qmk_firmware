#include QMK_KEYBOARD_H
#include "version.h"
#include "keymap_german.h"
#include "keymap_nordic.h"
#include "keymap_french.h"
#include "keymap_spanish.h"
#include "keymap_hungarian.h"
#include "keymap_swedish.h"
#include "keymap_br_abnt2.h"
#include "keymap_canadian_multilingual.h"
#include "keymap_german_ch.h"
#include "keymap_jp.h"
#include "keymap_korean.h"
#include "keymap_bepo.h"
#include "keymap_italian.h"
#include "keymap_slovenian.h"
#include "keymap_lithuanian_azerty.h"
#include "keymap_danish.h"
#include "keymap_norwegian.h"
#include "keymap_portuguese.h"
#include "keymap_contributions.h"
#include "keymap_czech.h"
#include "keymap_romanian.h"
#include "keymap_russian.h"
#include "keymap_uk.h"
#include "keymap_estonian.h"
#include "keymap_belgian.h"
#include "keymap_us_international.h"
#include "keymap_croatian.h"
#include "keymap_turkish_q.h"
#include "keymap_slovak.h"

#define KC_MAC_UNDO LGUI(KC_Z)
#define KC_MAC_CUT LGUI(KC_X)
#define KC_MAC_COPY LGUI(KC_C)
#define KC_MAC_PASTE LGUI(KC_V)
#define KC_PC_UNDO LCTL(KC_Z)
#define KC_PC_CUT LCTL(KC_X)
#define KC_PC_COPY LCTL(KC_C)
#define KC_PC_PASTE LCTL(KC_V)
#define ES_LESS_MAC KC_GRAVE
#define ES_GRTR_MAC LSFT(KC_GRAVE)
#define ES_BSLS_MAC ALGR(KC_6)
#define NO_PIPE_ALT KC_GRAVE
#define NO_BSLS_ALT KC_EQUAL
#define LSA_T(kc) MT(MOD_LSFT | MOD_LALT, kc)
#define BP_NDSH_MAC ALGR(KC_8)
#define SE_SECT_MAC ALGR(KC_6)
#define MOON_LED_LEVEL LED_LEVEL

enum custom_keycodes {
  RGB_SLD = ML_SAFE_RANGE,
  ST_MACRO_0,
  ST_MACRO_1,
  ST_MACRO_2,
  ST_MACRO_3,
  ST_MACRO_4,
  ST_MACRO_5,
};


enum tap_dance_codes {
  DANCE_0,
  DANCE_1,
  DANCE_2,
  DANCE_3,
  DANCE_4,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_moonlander(
    KC_ESCAPE,      KC_1,           KC_2,           KC_3,           KC_4,           KC_5,           KC_F5,                                          KC_GRAVE,       KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_MINUS,
    KC_TAB,         KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,           KC_F6,                                          KC_LBRACKET,    KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           KC_EQUAL,
    LCTL_T(KC_CAPSLOCK),LSFT_T(KC_A),LALT_T(KC_S),LCTL_T(KC_D),LSFT_T(KC_F),KC_G,           KC_F7,                                                                          KC_RBRACKET,    KC_H,           KC_J,           KC_K,           KC_L,           KC_SCOLON,      KC_QUOTE,
    KC_LSHIFT,      LGUI_T(KC_Z),KC_X,           KC_C,           KC_V,           KC_B,                                           KC_N,           KC_M,           KC_COMMA,       KC_DOT,         KC_SLASH,       KC_BSLASH,
    KC_LEFT,        KC_RIGHT,       KC_DOWN,        KC_UP,          LCTL_T(KC_TAB),TG(3),                                                                                                          TG(1),          LT(5,KC_SPACE), TD(DANCE_0),    DYN_MACRO_PLAY1,DYN_MACRO_PLAY2,_______,
    LT(4,KC_BSPACE),KC_DELETE,      _______,                 TG(6),          _______, LT(7,KC_ENTER)
  ),
  [1] = LAYOUT_moonlander(
    _______, _______, _______, _______, _______, _______, _______,                                 KC_TILD,        _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______,                                 KC_LBRACKET,    _______, _______, _______, _______, _______, _______,
    _______, LSFT_T(KC_A),KC_S,           KC_D,           KC_F,           _______, _______,                                                                 KC_RBRACKET,    _______, _______, _______, _______, _______, _______,
    _______, KC_Z,           _______, _______, _______, _______,                                 _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,                                                                                                 _______, _______, _______, _______, _______, _______,
    LT(2,KC_BSPACE),_______, _______,                 _______, _______, _______
  ),
  [2] = LAYOUT_moonlander(
    _______, _______, _______, _______, _______, _______, _______,                                 _______, _______, _______, _______, _______, _______, _______,
    _______, KC_NO,          KC_LPRN,        KC_EQUAL,       KC_RPRN,        _______, _______,                                 _______, _______, KC_7,           KC_8,           KC_9,           _______, _______,
    _______, KC_LCTRL,       KC_LBRACKET,    KC_MINUS,       KC_RBRACKET,    _______, _______,                                                                 _______, _______, KC_4,           KC_5,           KC_6,           KC_COLN,        KC_DQUO,
    _______, KC_LSHIFT,      KC_SLASH,       KC_EQUAL,       KC_BSLASH,      _______,                                 _______, KC_1,           KC_2,           KC_3,           _______, _______,
    _______, KC_MEH,         KC_HYPR,        _______, _______, _______,                                                                                                 _______, LT(5,KC_0),     _______, _______, _______, _______,
    _______, _______, _______,                 _______, _______, _______
  ),
  [3] = LAYOUT_moonlander(
    TO(0),          LCTL(KC_F1),    LGUI(LSFT(KC_RIGHT)),LGUI(KC_UP),    LGUI(KC_RIGHT), TD(DANCE_1),    LGUI(LSFT(KC_S)),                                KC_A,           KC_B,           _______, _______, _______, _______, _______,
    KC_TAB,         KC_MS_WH_UP,    KC_MS_BTN2,     KC_UP,          KC_MS_BTN1,     KC_PGUP,        KC_D,                                           KC_C,           KC_D,           KC_7,           KC_8,           KC_9,           _______, _______,
    KC_LCTRL,       KC_MS_WH_DOWN,  KC_LEFT,        KC_DOWN,        KC_RIGHT,       KC_PGDOWN,      TD(DANCE_2),                                                                    KC_E,           KC_F,           KC_4,           KC_5,           KC_6,           _______, _______,
    _______, LCTL(KC_Z),     LCTL(KC_X),     LCTL(KC_C),     LCTL(KC_V),     KC_MS_BTN3,                                     KC_MINUS,       KC_1,           KC_2,           KC_3,           _______, _______,
    _______, _______, _______, _______, _______, _______,                                                                                                 _______, _______, KC_COMMA,       KC_DOT,         _______, _______,
    KC_SPACE,       KC_ENTER,       _______,                 _______, _______, _______
  ),
  [4] = LAYOUT_moonlander(
    _______, KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          KC_F11,                                         KC_F12,         KC_F6,          KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_UNDS,
    _______, KC_B,           KC_C,           _______, KC_D,           TD(DANCE_3),    _______,                                 KC_LPRN,        KC_RPRN,        KC_7,           KC_8,           KC_9,           _______, KC_PLUS,
    _______, ST_MACRO_0,     ST_MACRO_1,     LCTL_T(KC_MINUS),ST_MACRO_2,     KC_DOT,         _______,                                                                 KC_LBRACKET,    KC_RBRACKET,    KC_4,           KC_5,           KC_6,           KC_COLN,        KC_DQUO,
    _______, TD(DANCE_4),    ST_MACRO_3,     KC_UNDS,        KC_EQUAL,       _______,                                 ST_MACRO_4,     KC_1,           KC_2,           KC_3,           _______, _______,
    _______, _______, _______, _______, _______, _______,                                                                                                 _______, LT(5,KC_0),     _______, _______, _______, _______,
    _______, _______, _______,                 _______, _______, _______
  ),
  [5] = LAYOUT_moonlander(
    TO(0),          LCTL(KC_F1),    KC_F2,          KC_F3,          LALT(KC_F4),    KC_F5,          KC_F6,                                          _______, _______, _______, _______, _______, _______, RESET,
    _______, _______, _______, _______, _______, _______, _______,                                 _______, _______, _______, _______, _______, _______, _______,
    _______, KC_LGUI,        KC_LALT,        KC_LCTRL,       KC_LSHIFT,      _______, _______,                                                                 _______, KC_INSERT,      KC_LEFT,        KC_DOWN,        KC_UP,          KC_RIGHT,       KC_ENTER,
    _______, KC_PC_UNDO,     KC_PC_CUT,      KC_PC_COPY,     KC_PC_PASTE,    LCTL(KC_B),                                     KC_APPLICATION, KC_HOME,        KC_PGDOWN,      KC_PGUP,        KC_END,         KC_BSPACE,
    _______, _______, _______, _______, _______, _______,                                                                                                 WEBUSB_PAIR,    _______, _______, DYN_REC_START1, DYN_REC_START2, _______,
    KC_BSPACE,      _______, _______,                 _______, _______, _______
  ),
  [6] = LAYOUT_moonlander(
    _______, _______, _______, _______, _______, _______, _______,                                 MU_TOG,         KC_B,           _______, TOGGLE_LAYER_COLOR,RGB_TOG,        RGB_MOD,        RGB_SLD,
    _______, KC_F12,         KC_F7,          KC_F8,          KC_F9,          _______, _______,                                 AU_TOG,         KC_C,           KC_7,           KC_8,           KC_9,           RGB_SPI,        RGB_SPD,
    _______, LGUI_T(KC_F11),LALT_T(KC_F4),LCTL_T(KC_F5),LSFT_T(KC_F6),KC_BSPACE,      _______,                                                                 MU_MOD,         KC_D,           LSFT_T(KC_4),LCTL_T(KC_5),LALT_T(KC_6),RGB_VAI,        RGB_VAD,
    _______, KC_F10,         KC_F1,          KC_F2,          KC_F3,          KC_DELETE,                                      KC_F,           KC_1,           KC_2,           KC_3,           RGB_SAI,        RGB_SAD,
    _______, _______, _______, _______, _______, _______,                                                                                                 _______, KC_0,           ST_MACRO_5,     KC_NO,          RGB_HUI,        RGB_HUD,
    _______, _______, _______,                 _______, _______, _______
  ),
  [7] = LAYOUT_moonlander(
    _______, LCTL(KC_F1),    _______, _______, LALT(KC_F4),    _______, _______,                                 _______, _______, _______, _______, _______, _______, _______,
    _______, _______, KC_MS_WH_DOWN,  KC_MS_UP,       KC_MS_WH_UP,    _______, _______,                                 _______, KC_NO,          KC_LSHIFT,      KC_LCTRL,       KC_LALT,        KC_LGUI,        _______,
    _______, _______, KC_MS_LEFT,     KC_MS_DOWN,     KC_MS_RIGHT,    _______, _______,                                                                 _______, KC_MS_BTN3,     KC_MS_ACCEL0,   KC_MS_BTN1,     KC_MS_BTN2,     KC_MS_ACCEL2,   _______,
    _______, LCTL(KC_Z),     LCTL(KC_X),     LCTL(KC_C),     LCTL(KC_V),     LCTL(KC_B),                                     KC_NO,          KC_LEFT,        KC_DOWN,        KC_UP,          KC_RIGHT,       _______,
    LCTL(LSFT(KC_E)),LALT(KC_S),     LALT(KC_TAB),   _______, _______, KC_MS_BTN3,                                                                                                     _______, _______, _______, _______, _______, _______,
    _______, _______, _______,                 _______, _______, _______
  ),
};

extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
}

const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
    [0] = { {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226}, {87,243,226} },

    [1] = { {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223}, {199,251,223} },

    [3] = { {0,0,0}, {0,0,0}, {0,0,0}, {74,255,255}, {74,255,255}, {0,0,0}, {131,255,255}, {131,255,255}, {152,255,255}, {74,255,255}, {0,0,0}, {41,255,255}, {0,245,245}, {152,255,255}, {74,255,255}, {152,255,255}, {0,245,245}, {0,245,245}, {152,255,255}, {0,0,0}, {0,0,0}, {41,255,255}, {0,245,245}, {152,255,255}, {0,0,0}, {0,0,0}, {131,255,255}, {131,255,255}, {41,255,255}, {0,0,0}, {0,0,0}, {219,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,255,255}, {0,255,255}, {0,255,255}, {0,0,0}, {0,0,0}, {0,255,255}, {0,255,255}, {0,255,255}, {0,0,0}, {0,0,0}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {72,244,245}, {72,244,245}, {72,244,245}, {0,0,0}, {72,244,245}, {72,244,245}, {72,244,245}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [4] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {31,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {31,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,255,255}, {0,255,255}, {0,255,255}, {0,0,0}, {0,0,0}, {0,255,255}, {0,255,255}, {0,255,255}, {0,0,0}, {0,0,0}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {31,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [5] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,255,255}, {0,0,0}, {81,253,252}, {0,0,0}, {0,0,0}, {0,255,255}, {0,0,0}, {81,253,252}, {0,0,0}, {0,0,0}, {0,255,255}, {0,0,0}, {81,253,252}, {0,0,0}, {0,0,0}, {0,255,255}, {0,0,0}, {81,253,252}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {81,253,252}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,255,255}, {81,253,252}, {0,0,0}, {0,0,0}, {0,0,0}, {0,255,255}, {81,253,252}, {0,0,0}, {0,0,0}, {0,0,0}, {0,255,255}, {81,253,252}, {0,0,0}, {0,0,0}, {0,0,0}, {0,255,255}, {81,253,252}, {0,0,0}, {0,0,0}, {0,0,0}, {81,253,252}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [6] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {146,224,255}, {146,224,255}, {146,224,255}, {0,0,0}, {0,0,0}, {169,120,255}, {169,120,255}, {169,120,255}, {0,0,0}, {0,0,0}, {169,120,255}, {169,120,255}, {169,120,255}, {0,0,0}, {0,0,0}, {169,120,255}, {169,120,255}, {169,120,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {85,203,158}, {85,203,158}, {85,203,158}, {85,203,158}, {85,203,158}, {10,225,255}, {10,225,255}, {10,225,255}, {10,225,255}, {10,225,255}, {134,255,213}, {169,120,255}, {169,120,255}, {169,120,255}, {0,0,0}, {134,255,213}, {169,120,255}, {169,120,255}, {169,120,255}, {0,0,0}, {0,0,0}, {169,120,255}, {169,120,255}, {169,120,255}, {169,120,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,0}, {0,0,255}, {0,0,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [7] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {81,253,252}, {0,0,0}, {0,0,0}, {0,255,255}, {172,255,255}, {81,253,252}, {0,0,0}, {0,0,0}, {172,255,255}, {172,255,255}, {81,253,252}, {0,0,0}, {0,0,0}, {0,255,255}, {172,255,255}, {81,253,252}, {0,0,0}, {0,0,0}, {81,253,252}, {128,255,252}, {81,253,252}, {0,0,0}, {81,253,252}, {128,255,252}, {0,0,0}, {0,0,0}, {0,0,0}, {128,255,252}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {81,253,252}, {0,0,0}, {0,255,255}, {0,0,0}, {0,0,0}, {81,253,252}, {172,255,255}, {0,255,255}, {0,0,0}, {0,0,0}, {81,253,252}, {172,255,255}, {0,255,255}, {0,0,0}, {0,0,0}, {81,253,252}, {172,255,255}, {0,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {172,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

};

void set_layer_color(int layer) {
  for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
    HSV hsv = {
      .h = pgm_read_byte(&ledmap[layer][i][0]),
      .s = pgm_read_byte(&ledmap[layer][i][1]),
      .v = pgm_read_byte(&ledmap[layer][i][2]),
    };
    if (!hsv.h && !hsv.s && !hsv.v) {
        rgb_matrix_set_color( i, 0, 0, 0 );
    } else {
        RGB rgb = hsv_to_rgb( hsv );
        float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
        rgb_matrix_set_color( i, f * rgb.r, f * rgb.g, f * rgb.b );
    }
  }
}

void rgb_matrix_indicators_user(void) {
  if (keyboard_config.disable_layer_led) { return; }
  switch (biton32(layer_state)) {
    case 0:
      set_layer_color(0);
      break;
    case 1:
      set_layer_color(1);
      break;
    case 3:
      set_layer_color(3);
      break;
    case 4:
      set_layer_color(4);
      break;
    case 5:
      set_layer_color(5);
      break;
    case 6:
      set_layer_color(6);
      break;
    case 7:
      set_layer_color(7);
      break;
   default:
    if (rgb_matrix_get_flags() == LED_FLAG_NONE)
      rgb_matrix_set_color_all(0, 0, 0);
    break;
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case ST_MACRO_0:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_LANG1) SS_DELAY(100) SS_TAP(X_A) SS_DELAY(100) SS_TAP(X_LANG1));

    }
    break;
    case ST_MACRO_1:
    if (record->event.pressed) {
      SEND_STRING(SS_LSFT(SS_TAP(X_9)) SS_DELAY(100) SS_LSFT(SS_TAP(X_0)) SS_DELAY(100) SS_TAP(X_LEFT));

    }
    break;
    case ST_MACRO_2:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_KP_COMMA) SS_DELAY(100) SS_TAP(X_SPACE));

    }
    break;
    case ST_MACRO_3:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_LBRACKET) SS_DELAY(100) SS_TAP(X_RBRACKET) SS_DELAY(100) SS_TAP(X_LEFT));

    }
    break;
    case ST_MACRO_4:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_BSLASH) SS_DELAY(100) SS_TAP(X_N));

    }
    break;
    case ST_MACRO_5:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_LEFT) SS_DELAY(100) SS_TAP(X_LEFT) SS_DELAY(100) SS_TAP(X_SLASH));

    }
    break;
    case RGB_SLD:
      if (record->event.pressed) {
        rgblight_mode(1);
      }
      return false;
  }
  return true;
}

typedef struct {
    bool is_press_action;
    uint8_t step;
} tap;

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP,
    MORE_TAPS
};

static tap dance_state[5];

uint8_t dance_step(qk_tap_dance_state_t *state);

uint8_t dance_step(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}


void on_dance_0(qk_tap_dance_state_t *state, void *user_data);
void dance_0_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_0_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_0(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_LANG1);
        tap_code16(KC_LANG1);
        tap_code16(KC_LANG1);
    }
    if(state->count > 3) {
        tap_code16(KC_LANG1);
    }
}

void dance_0_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state[0].step = dance_step(state);
    switch (dance_state[0].step) {
        case SINGLE_TAP: register_code16(KC_LANG1); break;
        case SINGLE_HOLD: register_code16(KC_LANG2); break;
        case DOUBLE_TAP: register_code16(KC_LANG1); register_code16(KC_LANG1); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_LANG1); register_code16(KC_LANG1);
    }
}

void dance_0_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[0].step) {
        case SINGLE_TAP: unregister_code16(KC_LANG1); break;
        case SINGLE_HOLD: unregister_code16(KC_LANG2); break;
        case DOUBLE_TAP: unregister_code16(KC_LANG1); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_LANG1); break;
    }
    dance_state[0].step = 0;
}
void on_dance_1(qk_tap_dance_state_t *state, void *user_data);
void dance_1_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_1_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_1(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_F5);
        tap_code16(KC_F5);
        tap_code16(KC_F5);
    }
    if(state->count > 3) {
        tap_code16(KC_F5);
    }
}

void dance_1_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state[1].step = dance_step(state);
    switch (dance_state[1].step) {
        case SINGLE_TAP: register_code16(KC_F5); break;
        case DOUBLE_TAP: register_code16(KC_F5); register_code16(KC_F5); break;
        case DOUBLE_HOLD: register_code16(LALT(KC_F4)); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_F5); register_code16(KC_F5);
    }
}

void dance_1_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[1].step) {
        case SINGLE_TAP: unregister_code16(KC_F5); break;
        case DOUBLE_TAP: unregister_code16(KC_F5); break;
        case DOUBLE_HOLD: unregister_code16(LALT(KC_F4)); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_F5); break;
    }
    dance_state[1].step = 0;
}
void on_dance_2(qk_tap_dance_state_t *state, void *user_data);
void dance_2_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_2_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_2(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_H);
        tap_code16(KC_H);
        tap_code16(KC_H);
    }
    if(state->count > 3) {
        tap_code16(KC_H);
    }
}

void dance_2_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state[2].step = dance_step(state);
    switch (dance_state[2].step) {
        case SINGLE_TAP: register_code16(KC_H); break;
        case SINGLE_HOLD: register_code16(KC_Z); break;
        case DOUBLE_TAP: register_code16(KC_H); register_code16(KC_H); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_H); register_code16(KC_H);
    }
}

void dance_2_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[2].step) {
        case SINGLE_TAP: unregister_code16(KC_H); break;
        case SINGLE_HOLD: unregister_code16(KC_Z); break;
        case DOUBLE_TAP: unregister_code16(KC_H); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_H); break;
    }
    dance_state[2].step = 0;
}
void on_dance_3(qk_tap_dance_state_t *state, void *user_data);
void dance_3_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_3_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_3(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_F);
        tap_code16(KC_F);
        tap_code16(KC_F);
    }
    if(state->count > 3) {
        tap_code16(KC_F);
    }
}

void dance_3_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state[3].step = dance_step(state);
    switch (dance_state[3].step) {
        case SINGLE_TAP: register_code16(KC_F); break;
        case SINGLE_HOLD: register_code16(KC_G); break;
        case DOUBLE_TAP: register_code16(KC_F); register_code16(KC_F); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_F); register_code16(KC_F);
    }
}

void dance_3_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[3].step) {
        case SINGLE_TAP: unregister_code16(KC_F); break;
        case SINGLE_HOLD: unregister_code16(KC_G); break;
        case DOUBLE_TAP: unregister_code16(KC_F); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_F); break;
    }
    dance_state[3].step = 0;
}
void on_dance_4(qk_tap_dance_state_t *state, void *user_data);
void dance_4_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_4_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_4(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(LCTL(KC_Z));
        tap_code16(LCTL(KC_Z));
        tap_code16(LCTL(KC_Z));
    }
    if(state->count > 3) {
        tap_code16(LCTL(KC_Z));
    }
}

void dance_4_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state[4].step = dance_step(state);
    switch (dance_state[4].step) {
        case SINGLE_TAP: register_code16(LCTL(KC_Z)); break;
        case SINGLE_HOLD: register_code16(KC_LGUI); break;
        case DOUBLE_TAP: register_code16(LCTL(KC_Z)); register_code16(LCTL(KC_Z)); break;
        case DOUBLE_SINGLE_TAP: tap_code16(LCTL(KC_Z)); register_code16(LCTL(KC_Z));
    }
}

void dance_4_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[4].step) {
        case SINGLE_TAP: unregister_code16(LCTL(KC_Z)); break;
        case SINGLE_HOLD: unregister_code16(KC_LGUI); break;
        case DOUBLE_TAP: unregister_code16(LCTL(KC_Z)); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(LCTL(KC_Z)); break;
    }
    dance_state[4].step = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
        [DANCE_0] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_0, dance_0_finished, dance_0_reset),
        [DANCE_1] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_1, dance_1_finished, dance_1_reset),
        [DANCE_2] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_2, dance_2_finished, dance_2_reset),
        [DANCE_3] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_3, dance_3_finished, dance_3_reset),
        [DANCE_4] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_4, dance_4_finished, dance_4_reset),
};

