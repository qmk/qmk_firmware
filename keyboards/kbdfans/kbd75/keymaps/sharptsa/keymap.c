#include QMK_KEYBOARD_H

/* ----------------------
-------RGB LIGHTNING-----
------------------------- */

const uint8_t RGBLED_RAINBOW_SWIRL_INTERVALS[] PROGMEM = {5, 5, 5};

// Light LEDs when caps lock is active.
const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
  {0, 4, 0, 255, 130}, // Left LEDs in dimmed red
  {8, 4, 0, 255, 130}
);

// Light LEDs when layer 1 is active.
const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
  {4, 4, 30, 255, 130},  // Right LEDs in dimmed golden rod
  {12, 4, 30, 255, 130}
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
  my_capslock_layer,
  my_layer1_layer
);

// All LEDs in dimmed blue
void set_default_keyboard_rgb(void) {
  rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
  rgblight_sethsv(170, 255, 130);
}

/* ----------------------
--------TAP DANCE--------
------------------------- */

uint16_t led_dance_timer;
bool led_dance_triggered = false;

void td_grv_php_arrow_finished(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count >= 2) {
    SEND_STRING("->");
  } else {
    register_code(KC_GRV);
  }
 
};

void td_grv_php_arrow_reset(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count < 2) {
    unregister_code(KC_GRV);
  } 
};

void td_reset_keyboard(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count >= 5) {
    reset_keyboard();
  }
};

void td_led_dance(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count >= 3) {
    rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL);
    led_dance_timer = timer_read();
    led_dance_triggered = true;
  }
};

// Reset default rgb lightning after 10sec
void td_led_dance_reset(void) {
  if (led_dance_triggered && (timer_elapsed(led_dance_timer) >= 10000) ) {
    set_default_keyboard_rgb();
    led_dance_triggered = false;
  }
}

// Tap Dance declarations
enum {
  TD_RESET,
  TD_GRV_PHPARROW,
  TD_LED_DANCE
};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  // Tap once for Escape, twice for Reset
  [TD_RESET] = ACTION_TAP_DANCE_FN(td_reset_keyboard),
  // Tap once for Grave, twice for PHP arrow
  [TD_GRV_PHPARROW] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_grv_php_arrow_finished, td_grv_php_arrow_reset),
  // Tap thrice for a led dance
  [TD_LED_DANCE] = ACTION_TAP_DANCE_FN(td_led_dance)
};

/* ----------------------
----------KEYMAP---------
------------------------- */

enum custom_keycodes {
    RGB_DEFAULT,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case RGB_DEFAULT:
        if (record->event.pressed) {
            // when keycode RGB_DEFAULT is pressed
            set_default_keyboard_rgb();
        } else {
            // when keycode RGB_DEFAULT is released
        }
        break;
    }
    return true;
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT(
    KC_ESC,                KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_PSCR,  KC_INS,   KC_HOME,
    TD(TD_GRV_PHPARROW),   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_NO,    KC_BSPC,  KC_PGUP,
    KC_TAB,                KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_PGDN,
    KC_CAPS,               KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,                      KC_ENT,   KC_DEL,
    KC_LSFT,               KC_NO,    KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,            KC_UP,    KC_END,
    KC_LCTL,               KC_LGUI,  KC_LALT,                      KC_SPC,   KC_SPC,   KC_SPC,                       KC_RALT,  KC_RGUI,  TT(1),    KC_LEFT,  KC_DOWN,  KC_RGHT
    ),

  [1] = LAYOUT(
    TD(TD_RESET),   _______,  _______,  _______,  _______,  _______,           KC_BRID,           KC_BRIU,  _______,  _______,      KC_MPRV,  KC_MPLY,  KC_MNXT,  _______,  _______,  KC_MUTE,
    _______,        _______,  _______,  _______,  _______,  _______,           _______,           _______,  _______,  _______,      _______,  _______,  _______,  _______,  _______,  KC_VOLU,
    _______,        RGB_TOG,  RGB_MOD,  RGB_HUI,  RGB_HUD,  RGB_SAI,           RGB_SAD,           RGB_VAI,  RGB_VAD,  RGB_DEFAULT,  _______,  _______,  _______,  _______,            KC_VOLD,
    _______,        _______,  _______,  _______,  _______,  _______,           _______,           _______,  _______,  _______,      _______,  _______,                      _______,  _______,
    _______,        _______,  _______,  _______,  _______,  _______,           _______,           _______,  _______,  _______,      _______,  _______,  _______,            _______,  _______,
    _______,        KC_MYCM,  _______,                      TD(TD_LED_DANCE),  TD(TD_LED_DANCE),  TD(TD_LED_DANCE),                 _______,  KC_MYCM,  _______,  _______,  _______,  _______
    ),
};

/* ----------------------
----------SETUP----------
------------------------- */

void keyboard_post_init_user(void) {
  // Enable the LED layers
  rgblight_layers = my_rgb_layers;
  set_default_keyboard_rgb();
}

layer_state_t layer_state_set_user(layer_state_t state) {
  rgblight_set_layer_state(1, layer_state_cmp(state, 1));
  return state;
}

bool led_update_user(led_t led_state) {
  rgblight_set_layer_state(0, led_state.caps_lock);
  return true;
}

void matrix_scan_user(void) {
  td_led_dance_reset();
}
