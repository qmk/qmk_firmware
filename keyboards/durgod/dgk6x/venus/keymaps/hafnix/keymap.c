#include QMK_KEYBOARD_H

#define ______ KC_TRNS


// needed for ALT_OSL1
typedef struct {
  bool is_press_action;
  int state;
} tap;

// needed for ALT_OSL1
enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  TRIPLE_TAP = 5,
  TRIPLE_HOLD = 6
};

// needed for ALT_OSL1
int cur_dance (qk_tap_dance_state_t *state);
void alt_finished (qk_tap_dance_state_t *state, void *user_data);
void alt_reset (qk_tap_dance_state_t *state, void *user_data);

// Tap Dance declarations
enum {
	TD_ESC,
	TD_CLN,
	TD_QUO,
	TD_HOM,
	TD_END,
	ALT_OSL1
};

// ALT_OSL1:
// ALT hold = ALT
// ALT tap = OneShot Layer 1 (ALT tap 4 = F4)
// ALT tap + hold = OSL1 with ALT (ALT tap + hold = ALT-F4)

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
	[TD_ESC] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS),
	[TD_CLN] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_COLN),
	[TD_QUO] = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, KC_DQUO),
	[TD_HOM] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_HOME),
	[TD_END] = ACTION_TAP_DANCE_DOUBLE(KC_RBRC, KC_END),
	[ALT_OSL1] = ACTION_TAP_DANCE_FN_ADVANCED(NULL,alt_finished, alt_reset)
};


// Layout
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_60_ansi(KC_GESC,       KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,       KC_MINS,    KC_EQL,        KC_BSPC,
                       LGUI_T(KC_TAB), KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,       TD(TD_HOM), TD(TD_END),   RGUI_T(KC_BSLS),
                       LT(1,KC_ESC),    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    TD(TD_CLN), TD(TD_QUO),              KC_ENT,
                       KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                            RSFT_T(KC_UP),
                       KC_LCTL, KC_LGUI, TD(ALT_OSL1), KC_SPC,                                                  RALT_T(KC_DEL), LT(1,KC_LEFT), LT(2,KC_DOWN), RCTL_T(KC_RIGHT)),

	[1] = LAYOUT_60_ansi(KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
                       _______, _______, KC_UP,   _______, _______, _______, _______, _______, _______, KC_PSCR, KC_INS,  KC_HOME, KC_END,  KC_DEL,
                       KC_CAPS, KC_LEFT, KC_DOWN, KC_RIGHT,_______, _______, _______, _______, _______, _______, KC_PGUP, KC_PGDN,          _______,
                       _______,          _______, _______, KC_CALC, _______, _______, _______, _______, TG(1),   TG(2),   TG(3),            _______,
                       _______, KC_TGUI, TD(ALT_OSL1),                       _______,                            _______, _______, MO(3),   _______),

	[2] = LAYOUT_60_ansi(TD(TD_ESC), KC_MPLY, KC_MSTP, KC_MPRV, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______, _______, RGB_TOG, RGB_MOD, RGB_RMOD,
                       _______, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                       _______, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, _______, _______, _______, _______, _______, _______, _______,          _______,
                       _______,          _______, _______, KC_CALC, _______, _______, _______, _______, TG(1),   TG(2),   TG(3),            _______,
                       _______, _______, _______,                            _______,                            _______, MO(3),   _______, _______),

	[3] = LAYOUT_60_ansi(_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
                       _______,          _______, _______, _______, _______, _______, _______, _______, TG(1),   TG(2),   TG(3),            _______,
                       _______, _______, _______,                            _______,                            _______, _______, _______, _______),

	[4] = LAYOUT_60_ansi(_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
                       _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
                       _______, _______, _______,                            _______,                            _______, _______, _______, _______),

	[5] = LAYOUT_60_ansi(_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
                       _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
                       _______, _______, _______,                            _______,                            _______, _______, _______, _______),

  [6] = LAYOUT_60_ansi(_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
                       _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
                       _______, _______, _______,                            _______,                            _______, _______, _______, _______),

  [7] = LAYOUT_60_ansi(_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
                       _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
                       _______, _______, _______,                            _______,                            _______, _______, _______, _______),

  [8] = LAYOUT_60_ansi(_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
                       _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
                       _______, _______, _______,                            _______,                            _______, _______, _______, _______),

  [9] = LAYOUT_60_ansi(_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
                       _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
                       _______, _______, _______,                            _______,                            _______, _______, _______, _______),

  [10] = LAYOUT_60_ansi(_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
                        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
                        _______, _______, _______,                            _______,                            _______, _______, _______, _______),

  [11] = LAYOUT_60_ansi(_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
                        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
                        _______, _______, _______,                            _______,                            _______, _______, _______, _______),

  [12] = LAYOUT_60_ansi(_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
                        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
                        _______, _______, _______,                            _______,                            _______, _______, _______, _______),

  [13] = LAYOUT_60_ansi(_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
                        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
                        _______, _______, _______,                            _______,                            _______, _______, _______, _______),

  [14] = LAYOUT_60_ansi(_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
                        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
                        _______, _______, _______,                            _______,                            _______, _______, _______, _______),

	[15] = LAYOUT_60_ansi(_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
                        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
                        _______, _______, _______,                            _______,                            _______, _______, _______, _______)
};


// Indicator LEDs per Layer
//
void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {

	switch (get_highest_layer(layer_state)) {

	case 1:
		/* for (uint8_t i = led_min; i <= led_max; i++) { */
		/* 	RGB_MATRIX_INDICATOR_SET_COLOR(i, 0, 0, 0); // switch all LEDs off */
		/* } */
		RGB_MATRIX_INDICATOR_SET_COLOR(16, 255,   0,   0); // W
		RGB_MATRIX_INDICATOR_SET_COLOR(29, 255,   0,   0); // A
		RGB_MATRIX_INDICATOR_SET_COLOR(30, 255,   0,   5); // S
		RGB_MATRIX_INDICATOR_SET_COLOR(31, 255,   0,   0); // D
		RGB_MATRIX_INDICATOR_SET_COLOR(49, 255,   0,   0); // .> P1
		RGB_MATRIX_INDICATOR_SET_COLOR(50,   0, 255,   0); // .> P2
		RGB_MATRIX_INDICATOR_SET_COLOR(51,   0, 255,   0); // .> P3
		RGB_MATRIX_INDICATOR_SET_COLOR(58, 255,   0,   0); // Fn1
		break;

	case 2:
		/* for (uint8_t i = led_min; i <= led_max; i++) { */
		/* 	RGB_MATRIX_INDICATOR_SET_COLOR(i, 0, 0, 0); // switch all LEDs off */
		/* } */
		RGB_MATRIX_INDICATOR_SET_COLOR(15, 255, 255, 255); // Q
		RGB_MATRIX_INDICATOR_SET_COLOR(16, 255, 255, 255); // W
		RGB_MATRIX_INDICATOR_SET_COLOR(17,   0, 255,   0); // E
		RGB_MATRIX_INDICATOR_SET_COLOR(18, 255, 255, 255); // R
		RGB_MATRIX_INDICATOR_SET_COLOR(29, 255, 255, 255); // A
		RGB_MATRIX_INDICATOR_SET_COLOR(30, 255, 255, 255); // S
		RGB_MATRIX_INDICATOR_SET_COLOR(31,   0, 255,   0); // D
		RGB_MATRIX_INDICATOR_SET_COLOR(32, 255, 255, 255); // F
		RGB_MATRIX_INDICATOR_SET_COLOR(49,   0, 255,   0); // .> P1
		RGB_MATRIX_INDICATOR_SET_COLOR(50, 255,   0,   0); // .> P2
		RGB_MATRIX_INDICATOR_SET_COLOR(51,   0, 255,   0); // .> P3
		RGB_MATRIX_INDICATOR_SET_COLOR(59, 255,   0,   0); // Fn2
		break;

	case 3:
		for (uint8_t i = led_min; i <= led_max; i++) {
			RGB_MATRIX_INDICATOR_SET_COLOR(i, 0, 0, 0); // switch all LEDs off
		}
		RGB_MATRIX_INDICATOR_SET_COLOR(49,   0, 255,   0); // .> P1
		RGB_MATRIX_INDICATOR_SET_COLOR(50,   0, 255,   0); // .> P2
		RGB_MATRIX_INDICATOR_SET_COLOR(51, 255,   0,   0); // .> P3
		RGB_MATRIX_INDICATOR_SET_COLOR(58, 255,   0,   0); // Fn1
		RGB_MATRIX_INDICATOR_SET_COLOR(59, 255,   0,   0); // Fn2
		break;

	default:
		break;
	}
}


// needed for ALT_OSL1
int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->pressed) return SINGLE_HOLD;
    else return SINGLE_TAP;
  }
  else if (state->count == 2) {
    if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  else if (state->count == 3) {
    if (state->interrupted || !state->pressed)  return TRIPLE_TAP;
    else return TRIPLE_HOLD;
  }
  else return 8;
}

// needed for ALT_OSL1
static tap alttap_state = {
  .is_press_action = true,
  .state = 0
};

// needed for ALT_OSL1
void alt_finished (qk_tap_dance_state_t *state, void *user_data) {
  alttap_state.state = cur_dance(state);
  switch (alttap_state.state) {
    case SINGLE_TAP: set_oneshot_layer(1, ONESHOT_START); clear_oneshot_layer_state(ONESHOT_PRESSED); break;
    case SINGLE_HOLD: register_code(KC_LALT); break;
    case DOUBLE_TAP: set_oneshot_layer(1, ONESHOT_START); set_oneshot_layer(1, ONESHOT_PRESSED); break;
    case DOUBLE_HOLD: register_code(KC_LALT); layer_on(1); break;
  }
}

// needed for ALT_OSL1
void alt_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (alttap_state.state) {
    case SINGLE_TAP: break;
    case SINGLE_HOLD: unregister_code(KC_LALT); break;
    case DOUBLE_TAP: break;
    case DOUBLE_HOLD: layer_off(1); unregister_code(KC_LALT); break;
  }
  alttap_state.state = 0;
}

// needed for ALT_OSL1
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_TRNS:
    case KC_NO:
      /* Always cancel one-shot layer when another key gets pressed */
      if (record->event.pressed && is_oneshot_layer_active())
      clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
      return true;
    case RESET:
      /* Don't allow reset from oneshot layer state */
      if (record->event.pressed && is_oneshot_layer_active()){
        clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
        return false;
      }
      return true;
    default:
      return true;
  }
  return true;
}
