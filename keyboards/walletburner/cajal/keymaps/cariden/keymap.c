/* Copyright 2020 Worldspawn <mcmancuso@gmail.com>
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

enum cajal_layers {
    _QWERTY,
    _COLEMAK,
    _LOWER,
    _RAISE,
    _MEDIA,
    _ADJUST
};

enum cajal_keycodes {
    QWERTY = SAFE_RANGE,
    COLEMAK,
    MEDIA,
    LOWER,
    RAISE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Qwerty
    * .------------------------------------------------------------------------------------------.   .------.
    * | Tab  |   Q  |   W  |   E  |   R  |   T  | Del  |   Y  |   U  |   I  |   O  |  P   | Bksp |   | RGBT |
    * |------+------+------+------+------+------+------+------+------+------+------+------+------|   '------'
    * | Esc  |   A  |   S  |   D  |   F  |   G  |      |   H  |   J  |   K  |   L  |  ;   |  '   |
    * |------+------+------+------+------+------+------+------+------+------+------+------+------'
    * | Shift|   Z  |   X  |   C  |   V  |   B  | Enter|   N  |   M  |   ,  |   .  |  /   |   .------.
    * |------+------+------+------+------+------+------+------+------+------+------+------'   |  Up  |
    * | Ctrl | GUI  |Media | Alt  |Lower |Space |Leader|WBksp |Raise | Home |  End |   .------+------+------.
    * '----------------------------------------------------------------------------'   | Left | Down | Right|
                                                                                       '--------------------'
    */
    [_QWERTY] = LAYOUT_ortho(
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,  KC_T,   KC_DEL,   KC_Y,          KC_U,  KC_I,    KC_O,    KC_P,    KC_BSPC,        RGB_TOG,
        KC_ESC, KC_A,    KC_S,    KC_D,    KC_F,  KC_G,   KC_NO,    KC_H,          KC_J,  KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,  KC_B,   KC_ENTER, KC_N,          KC_M,  KC_COMM, KC_DOT,  KC_SLSH,                 KC_UP,
        KC_LCTL, KC_LGUI, MEDIA,   KC_LALT, LOWER, KC_SPC, KC_LEAD,    LCTL(KC_BSPC), RAISE, KC_HOME, KC_END,                  KC_LEFT, KC_DOWN, KC_RGHT
    ),

    /* Colemak
    * .------------------------------------------------------------------------------------------.   .------.
    * | Tab  |   Q  |   W  |   F  |   P  |   G  | Del  |   J  |   L  |   U  |   Y  |  ;   | Bksp |   | RGBT |
    * |------+------+------+------+------+------+------+------+------+------+------+------+------|   '------'
    * | Esc  |   A  |   R  |   S  |   T  |   D  |      |   H  |   N  |   E  |   I  |  O   |  '   |
    * |------+------+------+------+------+------+------+------+------+------+------+------+------'
    * | Shift|   Z  |   X  |   C  |   V  |   B  | Enter|   K  |   M  |   ,  |   .  |  /   |   .------.
    * |------+------+------+------+------+------+------+------+------+------+------+------'   |  Up  |
    * | Ctrl | GUI  |Media | Alt  |Lower |Space |Leader|WBksp |Raise | Home |  End |   .------+------+------.
    * '----------------------------------------------------------------------------'   | Left | Down | Right|
                                                                                       '--------------------'
    */
    [_COLEMAK] = LAYOUT_ortho(
        KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,  KC_G,   KC_DEL,    KC_J,           KC_L,    KC_U,    KC_Y,    KC_SCLN,  KC_BSPC,            RGB_TOG,
        KC_ESC, KC_A,    KC_R,    KC_S,    KC_T,  KC_D,   KC_NO,     KC_H,           KC_N,    KC_E,    KC_I,    KC_O,     KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,  KC_B,   KC_ENTER,  KC_K,           KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                      KC_UP,
        KC_LCTL, KC_LGUI, MEDIA,   KC_LALT, LOWER, KC_SPC, KC_LEAD,     LCTL(KC_BSPC),  RAISE,   KC_HOME,  KC_END,             KC_LEFT, KC_DOWN, KC_RGHT
    ),

    /* Lower
    * .------------------------------------------------------------------------------------------.   .------.
    * |      |  !   |  @   |  #   |  $   |  %   |      |  ^   |  &   |  *   |  (   |  )   | Del  |   | RGBT |
    * |------+------+------+------+------+------+------+------+------+------+------+------+------|   '------'
    * |      |  1   |  2   |  3   |  4   |  5   |      |  6   |  7   |  8   |  9   |  0   |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------+------'
    * |      |  {   |  }   |  [   |  ]   |      |      |      |  -   |  _   |  =   |   +  |   .------.
    * |------+------+------+------+------+------+------+------+------+------+------+------'   |  Up  |
    * |      |      |      |      |      |      |      |      |      |      |      |   .------+------+------.
    * '----------------------------------------------------------------------------'   | Left | Down | Right|
                                                                                       '--------------------'
    */
    [_LOWER] = LAYOUT_ortho(
        KC_TILD,    KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,  _______,
        KC_GRV,     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS,
        SGUI(KC_S), KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, _______, _______, _______, KC_MINS, KC_UNDS, KC_EQL,  KC_PLUS, _______,
        KC_RCTL,    _______, _______, _______, _______, _______, _______, KC_DEL,  RAISE, _______, _______, _______,   _______, _______
    ),

    /* Raise
    * .------------------------------------------------------------------------------------------.   .------.
    * |      |  F1  |  F2  |  F3  |  F4  |      |      | PgUp |      |  Up  |      |      |Numlck|   | RGBT |
    * |------+------+------+------+------+------+------+------+------+------+------+------+------|   '------'
    * | Caps |  F5  |  F6  |  F7  |  F8  |      |      | PgDn | Left | Down | Right|      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------+------'
    * |      |  F9  |  F10 |  F11 |  F12 |      |      |      |      |      |      |      |   .------.
    * |------+------+------+------+------+------+------+------+------+------+------+------'   |  Up  |
    * |      |      |      |      |      |      |      |      |      |      |      |   .------+------+------.
    * '----------------------------------------------------------------------------'   | Left | Down | Right|
                                                                                       '--------------------'
    */
    [_RAISE] = LAYOUT_ortho(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______, _______, KC_PGUP,   _______, KC_UP,   _______,   _______, KC_NUMLOCK, _______,
        KC_CAPS, KC_F5,   KC_F6,   KC_F7,   KC_F8,   _______, _______, KC_PGDN,   KC_LEFT, KC_DOWN, KC_RIGHT,  _______, KC_PIPE,
        _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______,   _______, _______, _______,   _______, _______,
        _______, _______, _______, _______, LOWER, _______, _______, _______,   _______, _______, _______,   _______, _______, _______
    ),

    /* Media
    * .------------------------------------------------------------------------------------------.   .------.
    * |      |Volup |      |      |      |      |      |      |      |      |      |      |      |   | RGBT |
    * |------+------+------+------+------+------+------+------+------+------+------+------+------|   '------'
    * | Mute |Voldn | Prev | Next | Play |      |      |      |      |      |      |      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------+------'
    * |      |      |      |      |      |      |      |      |      |      |      |      |   .------.
    * |------+------+------+------+------+------+------+------+------+------+------+------'   |  Up  |
    * |      |      |      |      |      |      |      |      |      |      |      |   .------+------+------.
    * '----------------------------------------------------------------------------'   | Left | Down | Right|
                                                                                       '--------------------'
    */
    [_MEDIA] = LAYOUT_ortho(
        _______, KC_VOLU, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        KC_MUTE, KC_VOLD, KC_MPRV, KC_MNXT, KC_MPLY, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    /* Adjust
    * .------------------------------------------------------------------------------------------.   .------.
    * |      |      |      |      |      |      |      |      |      |      |      |      |Reset |   | RGBT |
    * |------+------+------+------+------+------+------+------+------+------+------+------+------|   '------'
    * |      |RGBMde|RGBHue|RGBSat|RGBVal|      |      |QWERTY|COLEMK|      |      |      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------+------'
    * |      |      |      |      |      |      |      |      |      |      |      |      |   .------.
    * |------+------+------+------+------+------+------+------+------+------+------+------'   |  Up  |
    * |      |      |      |      |      |      |      |      |      |      |      |   .------+------+------.
    * '----------------------------------------------------------------------------'   | Left | Down | Right|
                                                                                       '--------------------'
    */
    [_ADJUST] = LAYOUT_ortho(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RESET,  _______,
        _______, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, _______, _______, _______, QWERTY,  COLEMAK, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
        case QWERTY:
          if (record->event.pressed) {
              set_single_persistent_default_layer (_QWERTY);
          }
          return false;
          break;
        case COLEMAK:
          if (record->event.pressed) {
            set_single_persistent_default_layer (_COLEMAK);
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
        }
    return true;
};

void matrix_init_user(void) {
  // set  LED 1 to output and low
  setPinOutput(B5);
  writePinLow(B5);
  // set LED 2 to output and low
  setPinOutput(B6);
  writePinLow(B6);
  // set LED 3 to output and low
  setPinOutput(B7);
  writePinLow(B7);
}

const rgblight_segment_t PROGMEM layer_lower[] = RGBLIGHT_LAYER_SEGMENTS({10, 4, HSV_BLUE});
const rgblight_segment_t PROGMEM layer_raise[] = RGBLIGHT_LAYER_SEGMENTS({14, 4, HSV_RED});
const rgblight_segment_t PROGMEM layer_media[] = RGBLIGHT_LAYER_SEGMENTS({10, 4, HSV_GREEN});
const rgblight_segment_t PROGMEM layer_adjust[] = RGBLIGHT_LAYER_SEGMENTS({10, 8, HSV_PURPLE});
const rgblight_segment_t PROGMEM caps_lock[] = RGBLIGHT_LAYER_SEGMENTS({10, 1, HSV_YELLOW});

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    layer_lower,
    layer_raise,
    layer_media,
    layer_adjust,
    caps_lock
);

void keyboard_post_init_user(void) {
    rgblight_layers = my_rgb_layers;
};

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _LOWER));
    rgblight_set_layer_state(1, layer_state_cmp(state, _RAISE));
    rgblight_set_layer_state(2, layer_state_cmp(state, _MEDIA));
    rgblight_set_layer_state(3, layer_state_cmp(state, _ADJUST));

    return state;
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(4, led_state.caps_lock);
    return false;
}

void encoder_update_user(uint8_t index, bool clockwise) {
    if(IS_LAYER_ON(_RAISE)) {
        if (clockwise){
                tap_code(KC_WH_U);
            } else{
                tap_code(KC_WH_D);
            }
    } else if(IS_LAYER_ON(_LOWER)) {
            if (clockwise){
                tap_code(KC_PGUP);
            } else{
                tap_code(KC_PGDN);
            }
    }
    else{
        if (clockwise){
            tap_code(KC_VOLD);
        } else{
            tap_code(KC_VOLU);
        }
    }
}

LEADER_EXTERNS();

void matrix_scan_user(void) {
	LEADER_DICTIONARY(){
		leading = false;
		leader_end();

        SEQ_ONE_KEY(KC_T){
		    SEND_STRING("sudo /etc/init.d/tomcat7 ");
	    }
        SEQ_ONE_KEY(KC_COMM){
            SEND_STRING("sudo service delegosrv-"SS_TAP(X_TAB));
        }
        SEQ_TWO_KEYS(KC_COMM,KC_COMM){
            SEND_STRING("sudo service delegosrv- start");
            SEND_STRING(SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT));
        }
        SEQ_ONE_KEY(KC_M){
            SEND_STRING("sudo service delegomt-"SS_TAP(X_TAB));
        }
        SEQ_TWO_KEYS(KC_M,KC_M){
            SEND_STRING("sudo service delegomt- start");
            SEND_STRING(SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT));
        }
        SEQ_ONE_KEY(KC_DOT){
            SEND_STRING("sudo service delegosecure-"SS_TAP(X_TAB));
        }
        SEQ_TWO_KEYS(KC_DOT,KC_DOT){
            SEND_STRING("sudo service delegosecure- start");
            SEND_STRING(SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT));
        }
	    SEQ_ONE_KEY(KC_SLSH){
		    SEND_STRING("sudo puppet agent --test");
	    }
        SEQ_TWO_KEYS(KC_SLSH,KC_SLSH){
		    SEND_STRING("sudo puppet agent --disable ");
            SEND_STRING(SS_LSFT("'"));
            SEND_STRING(SS_LSFT("'"));
            SEND_STRING(SS_TAP(X_LEFT));
	    }
        SEQ_THREE_KEYS(KC_SLSH,KC_SLSH,KC_SLSH){
		    SEND_STRING("sudo puppet agent --enable");
	    }
        SEQ_ONE_KEY(KC_D){
            SEND_STRING("delego-home.sh");
        }
        SEQ_ONE_KEY(KC_QUOT){
            SEND_STRING(SS_LCTRL(SS_LSFT("p")));
        }
        SEQ_ONE_KEY(KC_BSPC){
            SEND_STRING(SS_LCTRL("`"));
        }
        SEQ_ONE_KEY(KC_F){
            SEND_STRING(SS_LCTRL("k0"));
        }
        SEQ_TWO_KEYS(KC_F,KC_F){
            SEND_STRING(SS_LCTRL("kj"));
        }
        SEQ_TWO_KEYS(KC_T,KC_S){
            SEND_STRING("export PYTHONWARNINGS=ignore;uname -r && test_ws_secure.py && test_ws_mt.py `test_ws_secure.py` && testCE.sh && grep ");
            SEND_STRING(SS_LSFT("'"));
            SEND_STRING("Connected with SAP");
            SEND_STRING(SS_LSFT("'"));
            SEND_STRING(" /var/log/delego/*/*/Delego*.log");
        }
	}
}
