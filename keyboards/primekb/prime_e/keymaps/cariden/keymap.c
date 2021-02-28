/* Copyright 2018 Holten Campbell
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

enum layers {
  _QWERTY,
  _COLEMAK,
  _COLEMAKDH,
  _GAMING,
  _LOWER,
  _RAISE,
  _MEDIA,
  _ADJUST
};

enum keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  COLEMAKDH,
  GAMING,
  MEDIA,
  LOWER,
  RAISE,
  MACRO00,
  MACRO01,
  MACRO02,
  MACRO03,
  MACRO04,
  MACRO05,
  MACRO06,
  MACRO07,
  MACRO08,
  MACRO09,
  MACRO10,
  MACRO11,
  MACRO12,
  MACRO13,
  MACRO14,
  MACRO15,
  MACRO16
};

enum {
    ALT_L2
};

qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Alt, twice for Layer 2
    [ALT_L2] = ACTION_TAP_DANCE_LAYER_TOGGLE(KC_LALT, _LOWER),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
		KC_TAB,          KC_Q,     KC_W,   KC_E,   KC_R,       KC_T,                 KC_Y,     KC_U,     KC_I, KC_O,    KC_P,     KC_BSLS,   KC_BSPC,
		CTL_T(KC_ESC),   KC_A,     KC_S,   KC_D,   KC_F,       KC_G,                 KC_H,     KC_J,     KC_K, KC_L,    KC_SCLN,  KC_QUOT,
		KC_LSFT,         KC_Z,     KC_X,   KC_C,   KC_V,       KC_B,                 KC_ENT,   KC_N,     KC_M, KC_COMM, KC_DOT,   KC_SLSH,   KC_LEAD,
		KC_LCTL,         KC_LGUI,                  KC_LALT,    LT(_LOWER,KC_SPC),	 LT(_RAISE,KC_BSPC),    MEDIA,                             KC_HOME,   KC_END
    ),

    [_COLEMAK] = LAYOUT(
		KC_TAB,          KC_Q,     KC_W,   KC_F,   KC_P,       KC_G,                 KC_J,     KC_L,    KC_U,   KC_Y,    KC_SCLN,  KC_BSLS,   KC_BSPC,
		CTL_T(KC_ESC),   KC_A,     KC_R,   KC_S,   KC_T,       KC_D,                 KC_H,     KC_N,    KC_E,   KC_I,    KC_O,     KC_QUOT,
		KC_LSFT,         KC_Z,     KC_X,   KC_C,   KC_V,       KC_B,                 KC_ENT,   KC_K,    KC_M,   KC_COMM, KC_DOT,   KC_SLSH,   KC_LEAD,
		KC_LCTL,         KC_LGUI,                  KC_LALT,    LT(_LOWER,KC_SPC),    LT(_RAISE,KC_BSPC),    MEDIA,                              KC_HOME,   KC_END
    ),

    [_COLEMAKDH] = LAYOUT(
		KC_TAB,   KC_Q,     KC_W,   KC_F,   KC_P,       KC_B,                KC_J,     KC_L,    KC_U,   KC_Y,    KC_SCLN,  KC_BSLS,   KC_BSPC,
		KC_GESC,  KC_A,     KC_R,   KC_S,   KC_T,       KC_G,                KC_M,     KC_N,    KC_E,   KC_I,    KC_O,     KC_QUOT,
		KC_LSFT,  KC_Z,     KC_X,   KC_C,   KC_D,       KC_V,                KC_ENT,   KC_K,    KC_H,   KC_COMM, KC_DOT,   KC_SLSH,   KC_LEAD,
		KC_LCTL,  KC_LGUI,                  KC_LALT,    LT(_LOWER,KC_SPC),   LT(_RAISE,KC_BSPC),    MEDIA,                              KC_HOME,   KC_END
    ),

    [_GAMING] = LAYOUT(
		KC_TAB,   KC_Q,     KC_W,   KC_E,   KC_R,       KC_T,            KC_Y,     KC_U,     KC_I, KC_O,    KC_P,     KC_BSLS,   KC_BSPC,
		KC_GESC,  KC_A,     KC_S,   KC_D,   KC_F,       KC_G,            KC_H,     KC_J,     KC_K, KC_L,    KC_SCLN,  KC_QUOT,
		KC_LSFT,  KC_Z,     KC_X,   KC_C,   KC_V,       KC_B,            KC_ENT,   KC_N,     KC_M, KC_COMM, KC_DOT,   KC_SLSH,   KC_LEAD,
		KC_LCTL,  KC_LGUI,                  KC_LALT,    KC_SPC,	         RAISE,    MEDIA,                             LOWER,   KC_END
    ),

    [_LOWER] = LAYOUT(
		KC_TILD,  KC_EXLM,   KC_AT,     KC_HASH,   KC_DLR,     KC_PERC,          KC_CIRC,   KC_AMPR,  KC_ASTR,   KC_LPRN,  KC_RPRN,   KC_PIPE,  KC_DEL,
		KC_GRV,   KC_1,      KC_2,      KC_3,      KC_4,       KC_5,             KC_6,      KC_7,     KC_8,      KC_9,     KC_0,      _______,
		_______,  KC_LCBR,   KC_RCBR,   KC_LBRC,   KC_RBRC,    _______,          KC_LEAD,   _______,  KC_MINS,   KC_UNDS,   KC_EQL,   KC_PLUS,  _______,
		_______,  _______,                         _______,    _______,	         RAISE,   _______,                                  KC_PGUP,  KC_PGDN
    ),

    [_RAISE] = LAYOUT(
		_______,   KC_F1,     KC_F2,     KC_F3,     KC_F4,      _______,        _______,   _______,    KC_UP,     _______,   _______,   KC_VOLD,   KC_VOLU,
		KC_CAPS,   KC_F5,     KC_F6,     KC_F7,     KC_F8,      _______,        _______,   KC_LEFT,    KC_DOWN,   KC_RIGHT,  _______,   KC_MUTE,
		_______,   KC_F9,     KC_F10,    KC_F11,    KC_F12,     _______,        _______,   _______,    _______,   _______,   _______,   _______,   _______,
		_______,   _______,                         _______,    LOWER,	        _______,   _______,                                     _______,   _______
    ),

    [_MEDIA] = LAYOUT(
		_______,  KC_VOLU,   _______,   _______,   _______,    _______,          MACRO00,   MACRO01,  MACRO02, MACRO03, MACRO04,   _______,  _______,
		KC_MUTE,  KC_VOLD,   KC_MPRV,   KC_MNXT,   KC_MPLY,    _______,          MACRO05,   MACRO06,  MACRO07, MACRO08, MACRO09,   _______,
		_______,  _______,   _______,   _______,   _______,    _______,          MACRO10,   MACRO11,  MACRO12, MACRO13, MACRO14,   _______,  _______,
		_______,  C(S(KC_F10)),                    _______,    MACRO16,	         MACRO15,   _______,                               _______,  _______
    ),

    [_ADJUST] = LAYOUT(
		_______,   _______,   _______,   _______,   _______,    _______,          _______,   _______,    _______,   _______,   _______,   _______,   RESET,
		_______,   RGB_TOG,   RGB_MOD,   RGB_HUI,   RGB_SAI,    RGB_VAI,          GAMING,    QWERTY,     COLEMAK,   COLEMAKDH,   _______,   _______,
		_______,   _______,   _______,   _______,   _______,    _______,          KC_CAPS,   _______,    _______,   _______,   _______,   _______,   _______,
		_______,   _______,                         _______,    _______,          _______,   _______,                                     _______,   _______
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QWERTY:
            if (record->event.pressed) {
                //set_single_persistent_default_layer(_QWERTY);
                layer_move(_QWERTY);
            }
            return false;
            break;
        case COLEMAK:
            if (record->event.pressed) {
                //set_single_persistent_default_layer(_COLEMAK);
                layer_move(_COLEMAK);
            }
            return false;
            break;
        case COLEMAKDH:
            if (record->event.pressed) {
                //set_single_persistent_default_layer(_COLEMAKDH);
                layer_move(_COLEMAKDH);
            }
            return false;
            break;
        case GAMING:
            if (record->event.pressed) {
                //set_single_persistent_default_layer(_GAMING);
                layer_move(_GAMING);
            }
            return false;
            break;
        case LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
            break;
        case RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
            break;
		case MEDIA:
            if (record->event.pressed) {
                layer_on(_MEDIA);
            } else {
                layer_off(_MEDIA);
            }
            return false;
            break;
        case MACRO00:
            if (record->event.pressed) {
                SEND_STRING("sudo /etc/init.d/tomcat7 stop");
            }
            else {}
            break;
        case MACRO01:
            if (record->event.pressed) {
                SEND_STRING("sudo /etc/init.d/tomcat7 start");
            }
            else {}
            break;
        case MACRO02:
            if (record->event.pressed) {
                SEND_STRING("sudo service delegosrv-"SS_TAP(X_TAB)"stop");
            }
            else {}
            break;
        case MACRO03:
            if (record->event.pressed) {
                SEND_STRING("sudo service delegosrv- start");
                SEND_STRING(SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT));
            }
            else {}
            break;
        case MACRO05:
            if (record->event.pressed) {
                SEND_STRING("sudo service delegomt-"SS_TAP(X_TAB)"stop");
            }
            else {}
            break;
        case MACRO06:
            if (record->event.pressed) {
                SEND_STRING("sudo service delegomt- start");
                SEND_STRING(SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT));
            }
            else {}
            break;
        case MACRO07:
            if (record->event.pressed) {
                SEND_STRING("sudo service delegosecure-"SS_TAP(X_TAB)"stop");
            }
            else {}
            break;
        case MACRO08:
            if (record->event.pressed) {
                SEND_STRING("sudo service delegosecure- start");
                SEND_STRING(SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT));
            }
            else {}
            break;
        case MACRO10:
            if (record->event.pressed) {
                SEND_STRING("sudo puppet agent --test");
            }
            else {}
            break;
        case MACRO11:
            if (record->event.pressed) {
               	SEND_STRING("sudo puppet agent --disable ");
                SEND_STRING(SS_LSFT("'"));
                SEND_STRING(SS_LSFT("'"));
                SEND_STRING(SS_TAP(X_LEFT));
            }
            else {}
            break;
        case MACRO12:
            if (record->event.pressed) {
               	SEND_STRING("sudo puppet agent --enable");
            }
            else {}
            break;
        case MACRO14:
            if (record->event.pressed) {
                SEND_STRING("export PYTHONWARNINGS=ignore;uname -r && test_ws_secure.py && test_ws_mt.py `test_ws_secure.py` && testCE.sh && grep ");
                SEND_STRING(SS_LSFT("'"));
                SEND_STRING("Connected with SAP");
                SEND_STRING(SS_LSFT("'"));
                SEND_STRING(" /var/log/delego/*/*/Delego*.log");
            }
            else {}
            break;
        case MACRO15:
            if (record->event.pressed) {
                SEND_STRING("delego-home.sh");
            }
            else {}
            break;
        case MACRO16:
            if (record->event.pressed) {
                SEND_STRING("./DelegoARRecur_reporting.sh");
            }
            else {}
            break;
        }
        return true;
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RSFT_T(KC_ENT):
            return TAPPING_TERM + 150;
        default:
            return TAPPING_TERM;
    }
};

void matrix_init_user(void) {
//   // set CapsLock LED to output and low
//   setPinOutput(B1);
//   writePinLow(B1);
//   // set NumLock LED to output and low
//   setPinOutput(B2);
//   writePinLow(B2);
//   // set ScrollLock LED to output and low
//   setPinOutput(B3);
//   writePinLow(B3);
};

LEADER_EXTERNS();

void matrix_scan_user(void) {
    LEADER_DICTIONARY() {
        leading = false;
        leader_end();

        SEQ_ONE_KEY(KC_TAB) {
        // Anything you can do in a macro.
            SEND_STRING(SS_LCTRL("`"));
        }
        SEQ_ONE_KEY(KC_Q){
            SEND_STRING(SS_LCTRL(SS_LSFT("p")));
        }
    }
};

const rgblight_segment_t PROGMEM layer_lower[] = RGBLIGHT_LAYER_SEGMENTS({2, 1, HSV_CYAN});
const rgblight_segment_t PROGMEM layer_raise[] = RGBLIGHT_LAYER_SEGMENTS({1, 1, HSV_PURPLE});
const rgblight_segment_t PROGMEM layer_media[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_CORAL});
const rgblight_segment_t PROGMEM layer_adjust[] = RGBLIGHT_LAYER_SEGMENTS({1, 2, HSV_SPRINGGREEN});

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    layer_lower,
    layer_raise,
    layer_media,
    layer_adjust
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
};

// function for layer indicator LED
layer_state_t layer_state_set_user(layer_state_t state)
{
    rgblight_set_layer_state(0, layer_state_cmp(state, 4));
    rgblight_set_layer_state(1, layer_state_cmp(state, 5));
    rgblight_set_layer_state(2, layer_state_cmp(state, 6));
    rgblight_set_layer_state(3, layer_state_cmp(state, 7));

    if (IS_LAYER_ON(_QWERTY)) {
        writePinLow(B2);
        writePinLow(B3);
        writePinHigh(B1);
    }
    else if (IS_LAYER_ON(_COLEMAK)) {
        writePinLow(B1);
        writePinLow(B3);
        writePinHigh(B2);
    }
    else if (IS_LAYER_ON(_GAMING)) {
        writePinLow(B1);
        writePinLow(B2);
        writePinHigh(B3);
    }

    return state;
};
