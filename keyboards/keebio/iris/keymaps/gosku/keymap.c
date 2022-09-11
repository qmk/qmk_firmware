#include QMK_KEYBOARD_H


#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3

#define SFT_CAPS MT(MOD_LSFT,KC_CAPS) // code for a mod_tap: hold for shift, tap for caps locks
#define C_LBRC C(KC_LBRC) // ctrl + open braces
#define C_RBRC C(KC_RBRC) // ctrl + close braces
#define A_DASH A(KC_MINS)
#define A_PLUS A(KC_EQL)
#define C_LEFT C(KC_LEFT)
#define C_RGHT C(KC_RGHT)
#define S_HOME S(KC_HOME)
#define S_END S(KC_END)
#define CS_LEFT C(S(KC_LEFT))
#define CS_RGHT C(S(KC_RGHT))
#define W_S_TAB LGUI(S(KC_TAB))

// Hue colors
#define VIOLET 193
#define ORANGE 10
#define RED 1
#define PINK 245
#define TURKEISE 104
#define YELLOW 23
#define GREEN 85
#define BLUE 130
#define NONE 0 // This is actually a color, but it is being used here as a flag to turn a led off

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                                 KC_H,    KC_J,   KC_K,    KC_L,   KC_SCLN, KC_QUOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     SFT_CAPS , KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                              KC_N,    KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_PSCR, KC_LGUI, KC_LALT, KC_LCTL, LOWER,   KC_SPC,  _______,          KC_MPLY,  KC_SPC,  RAISE,   KC_ENT, KC_MPLY,  KC_VOLD, KC_VOLU,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, C(KC_PGUP), C(KC_PGDN)
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_LOWER] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                            KC_CIRC,  KC_P7,   KC_P8,   KC_P9,  _______, KC_TRNS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      KC_GRV, KC_AMPR, KC_PAST, KC_PMNS, KC_UNDS, KC_GRV,                             _______, KC_P4,   KC_P5,   KC_P6,   KC_PLUS,  KC_PMNS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_LT,   KC_GT,   KC_PLUS, KC_EQL,  KC_DQUO,                             KC_RBRC,  KC_P1,   KC_P2,  KC_P3,  KC_PAST, KC_SLSH,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_PDOT, KC_TRNS,  KC_P0,   KC_TRNS, KC_MPRV, KC_MNXT,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,  KC_TRNS, KC_TRNS
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_RAISE] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_TRNS, C_LBRC,   C_RBRC,  A_DASH,  A_PLUS, KC_LBRC,                            KC_RBRC, KC_PGUP,  KC_UP,   KC_PGDN, _______, KC_DEL,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TRNS, KC_HOME,  C_LEFT,  C_RGHT,  KC_END, KC_LPRN,                            KC_RPRN, KC_LEFT, KC_DOWN, KC_RGHT, KC_PIPE,  KC_BSLS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT, S_HOME,  CS_LEFT, CS_RGHT,  S_END,  KC_LCBR,                            KC_RCBR,  _______, _______, _______, _______, KC_RSFT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          C(KC_P0), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BRID, KC_BRIU,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_ADJUST] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______,  KC_F1,   KC_F2,   KC_F3,   KC_F4,  _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______,  KC_F5,   KC_F6,   KC_F7,   KC_F8,  _______,                            _______, RGB_TOG, _______, _______, _______,  RESET,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______,  KC_F9,   KC_F10,  KC_F11, KC_F12,  _______,                            _______, RGB_MOD, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______, KC_TRNS,          KC_TRNS, _______, _______, _______, _______, _______, EEP_RST,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  )
};


extern bool g_suspend_state;
extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;

    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;

    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;

    default:
      return true; // Process all other keycodes normally
  }
  return true;
}

int ledmap[][DRIVER_LED_TOTAL] = {
    [_QWERTY] = {
        PINK, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW,   YELLOW, YELLOW, YELLOW, YELLOW, YELLOW,   PINK,  // R1
      YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW,   YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW,  // R2
      YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW,   YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW,  // R3
      YELLOW, YELLOW,   BLUE,    RED,   PINK, YELLOW,   YELLOW,   PINK,    RED, YELLOW, YELLOW, YELLOW,  // R4
                      ORANGE, ORANGE, ORANGE, ORANGE,   ORANGE, ORANGE, ORANGE, ORANGE,                  // Thumb Cluster
      ORANGE, ORANGE, ORANGE, ORANGE, ORANGE, ORANGE,   ORANGE, ORANGE, ORANGE, ORANGE, ORANGE, ORANGE,  // Underglow
    },

    [_LOWER] = {
       GREEN,  GREEN,  GREEN,  GREEN,  GREEN,  GREEN,    GREEN, YELLOW, YELLOW, YELLOW,   NONE,   NONE,  // R1
       GREEN,  GREEN,  GREEN, VIOLET, VIOLET,  GREEN,     NONE, YELLOW, YELLOW, YELLOW, VIOLET, VIOLET,  // R2
        NONE,  GREEN,  GREEN, VIOLET, VIOLET,  GREEN,     NONE, YELLOW, YELLOW, YELLOW, VIOLET, VIOLET,  // R3
        NONE,   NONE,   BLUE,    RED,   PINK, YELLOW,   YELLOW,   PINK, YELLOW,  GREEN,  GREEN,  GREEN,  // R4
                      ORANGE, ORANGE, ORANGE, ORANGE,   ORANGE, ORANGE, ORANGE, ORANGE,                  // Thumb Cluster
      ORANGE, ORANGE, ORANGE, ORANGE, ORANGE, ORANGE,   ORANGE, ORANGE, ORANGE, ORANGE, ORANGE, ORANGE,  // Underglow
    },

    [_RAISE] = {
        PINK, YELLOW, YELLOW, YELLOW, YELLOW, VIOLET,   VIOLET,  GREEN, YELLOW,  GREEN,   NONE,   BLUE,  // R1
        NONE, YELLOW, YELLOW, YELLOW, YELLOW, VIOLET,   VIOLET, YELLOW, YELLOW, YELLOW,   PINK,   PINK,  // R2
        NONE, YELLOW, YELLOW, YELLOW, YELLOW, VIOLET,   VIOLET,   NONE,   NONE,   NONE,   NONE,   NONE,  // R3
        NONE,   NONE,   BLUE,    RED,   PINK, YELLOW,   YELLOW,   PINK,   NONE,   NONE,   NONE,   NONE,  // R4
                      ORANGE, ORANGE, ORANGE, ORANGE,   ORANGE, ORANGE, ORANGE, ORANGE,                  // Thumb Cluster
      ORANGE, ORANGE, ORANGE, ORANGE, ORANGE, ORANGE,   ORANGE, ORANGE, ORANGE, ORANGE, ORANGE, ORANGE,  // Underglow
    },

    [_ADJUST] = {
        NONE, VIOLET, VIOLET, VIOLET, VIOLET,   NONE,     NONE,   NONE,   NONE,   NONE,   NONE,   NONE,  // R1
        NONE, VIOLET, VIOLET, VIOLET, VIOLET,   NONE,     NONE,    RED,   NONE,   NONE,   NONE,  GREEN,  // R2
        NONE, VIOLET, VIOLET, VIOLET, VIOLET,   NONE,     NONE,   BLUE,   NONE,   NONE,   NONE,   NONE,  // R3
        NONE,   NONE,   NONE,   NONE,   PINK,   NONE,     NONE,   PINK,   NONE,   NONE,   NONE,   BLUE,  // R4
                        NONE,   NONE,   NONE,   NONE,     NONE,   NONE,   NONE,   NONE,                  // Thumb Cluster
      ORANGE, ORANGE, ORANGE, ORANGE, ORANGE, ORANGE,   ORANGE, ORANGE, ORANGE, ORANGE, ORANGE, ORANGE,  // Underglow
    },

};



// This constant is used to map the led order in the board to key position in the board, allowing
// us to define the color of each led in the same order as the keys are placed in the board
// This constant is similar to the g_led_config, but including the underglow leds as well
const uint8_t ledmap_to_index[DRIVER_LED_TOTAL] = {
      0,  1,   2,  3,  4,  5,                    39, 38, 37, 36, 35, 34, // R1
      11, 10,  9,  8,  7,  6,                    40, 41, 42, 43, 44, 45, // R2
      12, 13, 14, 15, 16, 17,                    51, 50, 49, 48, 47, 46, // R3
      23, 22, 21, 20, 19, 18,                    52, 53, 54, 55, 56, 57, // R4
                      24, 25, 26, 27,    58, 59, 60, 61, //                 Thumb Cluster
      28, 29, 30, 31, 32, 33,                    62, 63, 64, 65, 66, 67, // Underglow
};


void set_led_color(int led_index, int hue){
  // get the position of the led that correspond with the key in ledmap
  int position = ledmap_to_index[led_index];
  if (hue == NONE) {
    rgb_matrix_set_color(position, 0, 0, 0);
  } else {
    HSV hsv = {
      .h = hue,
      .s = 255,
      .v = 170,
    };
    RGB rgb = hsv_to_rgb( hsv );
    rgb_matrix_set_color(position, rgb.r, rgb.g, rgb.b );
  }

}

void set_layer_color(int layer) {

  for (int i = 0; i < DRIVER_LED_TOTAL; i++){
    set_led_color(i, ledmap[layer][i]);
  }
}



void rgb_matrix_indicators_user(void) {
  switch (biton32(layer_state)) {
    case 0:
      set_layer_color(_QWERTY);
      if (host_keyboard_led_state().caps_lock){
        set_led_color(24, PINK); // assuming caps lock is at led with index #24
      }
      break;
    case 1:
      set_layer_color(_LOWER);
      break;
    case 2:
      set_layer_color(_RAISE);
      break;
    case 3:
      set_layer_color(_ADJUST);
      break;
   default:
    if (rgb_matrix_get_flags() == LED_FLAG_NONE)
      rgb_matrix_set_color_all(0, 0, 0);
    break;
  }

}


#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_QWERTY] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_LOWER] = { ENCODER_CCW_CW(W_S_TAB, W_S_TAB), ENCODER_CCW_CW(W_S_TAB, W_S_TAB) },
    [_RAISE] = { ENCODER_CCW_CW(C(KC_PMNS), C(KC_PLUS)), ENCODER_CCW_CW(C(KC_PMNS), C(KC_PLUS)) },
    [_ADJUST] = { ENCODER_CCW_CW(C(KC_PMNS), C(KC_PLUS)), ENCODER_CCW_CW(C(KC_PMNS), C(KC_PLUS)) },
// #   endif
};
#endif