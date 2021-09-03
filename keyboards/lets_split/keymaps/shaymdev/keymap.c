#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _DVORAK 0
#define _QWERTY 1
#define _LOWER 2
#define _RAISE 3
#define _ADJUST 16

enum custom_keycodes {
  DVORAK = SAFE_RANGE,
  QWERTY
};

#define TO_DV TO(_DVORAK)
#define LOWER MO(_LOWER)
#define LWR LOWER
#define RAISE MO(_RAISE)
#define RAS RAISE

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_DVORAK] = LAYOUT( \
  KC_ESC,  KC_QUOT, KC_COMM, KC_DOT, KC_P,    KC_Y,        KC_F,    KC_G,   KC_C,  KC_R,   KC_L,    KC_SLSH, \
  KC_TAB,  KC_A,    KC_O,    KC_E,   KC_U,    KC_I,        KC_D,    KC_H,   KC_T,  KC_N,   KC_S,    KC_MINS, \
  KC_EQL,  KC_SCLN, KC_Q,    KC_J,   KC_K,    KC_X,        KC_B,    KC_M,   KC_W,  KC_V,   KC_Z,    KC_BSLS, \
  XXXXXXX, KC_ENT,  KC_LALT, TT(LWR), KC_LSFT, KC_LCTL,		 KC_BSPC, KC_SPC, TT(RAS), KC_DEL, KC_LGUI, XXXXXXX  \
),

[_QWERTY] = LAYOUT( \
  KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    	  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
  KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    	  KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    	  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_LGUI,\
  _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______
),

[_LOWER] = LAYOUT( \
  _______, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_AMPR,     _______, KC_P7,   KC_P8, KC_P9, KC_PMNS, _______, \
  _______, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_ASTR, 		_______, KC_P4,   KC_P5, KC_P6, KC_PPLS, _______, \
  _______, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_GRV,			_______, KC_P1,   KC_P2, KC_P3, KC_PENT, _______, \
  _______, _______, _______, _______, _______, _______,     _______, KC_KP_0, _______, _______, _______, _______ //This kp_0 is blocking the space key.... may want to do something about that.
),

[_RAISE] = LAYOUT( \
  _______, KC_PSCR, KC_HOME, KC_UP,   KC_END,  KC_PGUP,  		KC_VOLU, KC_F7,   KC_F8,   KC_F9,   KC_F10,  XXXXXXX,\
  KC_CAPS, KC_INS,  KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,  	 	KC_VOLD, KC_F4,   KC_F5,   KC_F6,   KC_F11,  XXXXXXX,\
  _______, KC_NLCK, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  	 	KC_MUTE, KC_F1,   KC_F2,   KC_F3,   KC_F12,  XXXXXXX,\
  _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______
),

[_ADJUST] =  LAYOUT( \
    TO_DV, RESET,   _______, _______, _______, _______, 		_______, _______, _______, _______, _______, KC_DEL,  \
  RGB_TOG, RGB_MOD, VLK_TOG, AU_ON,   AU_OFF,  AG_NORM, 		AG_SWAP,  QWERTY,  DVORAK, _______, _______, _______, \
  RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, 		_______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY,  \
  _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______
)

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case QWERTY:
    if (record->event.pressed) {
      set_single_persistent_default_layer(_QWERTY);
    }
    return false;
    break;
  case DVORAK:
    if (record->event.pressed) {
      set_single_persistent_default_layer(_DVORAK);
    }
    return false;
    break;
  }
  return true;
}


#ifdef RGBLIGHT_ENABLE

const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {4, 2, HSV_RED}       // Light 10 LEDs, starting with LED 0
);

const rgblight_segment_t PROGMEM my_qwerty_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 3, HSV_CHARTREUSE}       // Light 10 LEDs, starting with LED 0
);

const rgblight_segment_t PROGMEM my_lower_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {3, 2, HSV_BLUE}    // Light LEDs 0-4
);

const rgblight_segment_t PROGMEM my_raise_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {5, 2, HSV_ORANGE}    // Light LEDs 5-10
);

const rgblight_segment_t PROGMEM my_adjust_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {3, 4, HSV_GREEN}       // Light 10 LEDs, starting with LED 0
);


// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_capslock_layer,
    my_qwerty_layer,   // Overrides other layers
    my_lower_layer,    // Overrides other layers
    my_raise_layer,    // Overrides other layers
    my_adjust_layer    // Overrides other layers
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
    rgblight_disable_noeeprom(); // disables RGB, without saving settings
    //rgblight_sethsv_noeeprom(HSV_CYAN);
    //rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    // rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_SWIRL);
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(0, led_state.caps_lock);
    return true;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(1, layer_state_cmp(state, _QWERTY));
    return state;
}

#endif

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);

#ifdef RGBLIGHT_ENABLE
    rgblight_set_layer_state(2, layer_state_cmp(state, _LOWER));
    rgblight_set_layer_state(3, layer_state_cmp(state, _RAISE));
    rgblight_set_layer_state(4, layer_state_cmp(state, _ADJUST));
#endif

  return state;
}
