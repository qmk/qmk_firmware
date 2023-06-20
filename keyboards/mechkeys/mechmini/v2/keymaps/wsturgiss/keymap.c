#include QMK_KEYBOARD_H

#define base 0
#define raise 1
#define lower 2

//Tap Dance Declarations
enum {
  TD_SEMI_QUOT = 0,
  TD_COMM_MINUS = 1,
  TD_DOT_EQUAL = 2,
  TD_SLASH_BACKSLASH = 3
};

//Tap Dance Definitions
tap_dance_action_t tap_dance_actions[] = {
  //Tap once for ;, twice for ' -not using this currently
  [TD_SEMI_QUOT]  = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_QUOT),
  //Tap once for , twice for -
  [TD_COMM_MINUS]  = ACTION_TAP_DANCE_DOUBLE(KC_COMM, KC_MINUS),
  //Tap once for . twice for =
  [TD_DOT_EQUAL]  = ACTION_TAP_DANCE_DOUBLE(KC_DOT, KC_EQUAL),
  //Tap once for / twice for '\'
  [TD_SLASH_BACKSLASH]  = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, KC_BSLS)
};

#define CTRL_ESC CTL_T(KC_ESC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[base] = LAYOUT_2u_space_ortho(
		KC_TAB,     KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSPC,
		CTRL_ESC,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_ENT,
		SC_LSPO,    KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     TD(1),    TD(2),    TD(3),    SC_RSPC,
		KC_LCTL,    QK_LEAD,  KC_LALT,  KC_LGUI,  MO(1),        KC_SPC,         MO(2),    KC_VOLD,  KC_MPLY,  KC_VOLU,  KC_GRV),

	[raise] = LAYOUT_2u_space_ortho(
		_______,    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_DEL,
		_______,    _______,  _______,  _______,  _______,  _______,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RIGHT, KC_QUOT,  _______,
		_______,    KC_HOME,  KC_END,   _______,  _______,  _______,  _______,  _______,  KC_LBRC,  KC_RBRC,  _______,  _______,
		_______,    _______,  _______,  _______,  _______,      _______,        _______,  KC_MPRV,  _______,  KC_MNXT,  EE_CLR),

	[lower] = LAYOUT_2u_space_ortho(
		_______,    KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     _______,
		_______,    RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_VAD,  _______,  _______,  KC_4,     KC_5,     KC_6,   KC_KP_PLUS, _______,
		_______,    RGB_SAI,  RGB_SAD,  RGB_HUI,  RGB_HUD,  _______,  _______,  KC_1,     KC_2,     KC_3,  KC_KP_MINUS, _______,
		_______,    _______,  _______,  _______,  _______,      _______,        _______,  KC_0,     _______,  _______,  _______)


};

//Leader maps
void leader_end_user(void) {
    if (leader_sequence_one_key(KC_F)) {
        // Anything you can do in a macro.
        SEND_STRING("QMK is awesome.");
    }
    //tableflip (LEADER - TF)
    if (leader_sequence_two_keys(KC_T, KC_F)) {
        set_unicode_input_mode(UNICODE_MODE_MACOS);
        send_unicode_string("(ノಠ痊ಠ)ノ彡┻━┻");
    }
    //screencap (LEADER - SC)
    if (leader_sequence_two_keys(KC_S, KC_C)) {
        SEND_STRING(SS_LGUI(SS_LSFT(SS_TAP(X_4))));
    }
    //screencap (LEADER - TM)
    if (leader_sequence_two_keys(KC_T, KC_M)) {
        set_unicode_input_mode(UNICODE_MODE_MACOS);
        register_unicode(0x2122); // ™
    }
    /*
    if (leader_sequence_three_keys(KC_D, KC_D, KC_S)) {
        SEND_STRING("https://start.duckduckgo.com"SS_TAP(X_ENTER));
    }
    */
}

//change colors and rgb modes on layer change
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case raise:
        rgblight_mode_noeeprom(1);
        rgblight_setrgb(0xc7, 0x00, 0xf4);
        break;
    case lower:
        rgblight_mode_noeeprom(1);
        rgblight_setrgb(0x00, 0xa3, 0x0d);
        break;
    default: // for any other layers, or the default layer
        rgblight_mode_noeeprom(5);
        rgblight_setrgb(0xFF, 0xB6, 0x00);
        break;
    }
  return state;
};
