#include QMK_KEYBOARD_H

enum layers {
  _QWERTY,
  _COLEMAK,
  _LOWER,
  _RAISE,
  _MEDIA,
  _ADJUST
};

enum keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Qwerty
    ┌─────┬─────┬─────┬─────┬─────┬─────┐      ┌─────┬─────┬─────┬─────┬─────┬─────┐
    | Tab |  Q  |  W  |  E  |  R  |  T  |      |  Y  |  U  |  I  |  O  |  P  |Bksp |
    ├─────┼─────┼─────┼─────┼─────┼─────┤      ├─────┼─────┼─────┼─────┼─────┼─────┤
    | Esc |  A  |  S  |  D  |  F  |  G  |      |  H  |  J  |  K  |  L  |  ;  |  '  |
    ├─────┼─────┼─────┼─────┼─────┼─────┤      ├─────┼─────┼─────┼─────┼─────┼─────┤
    |Shift|  Z  |  X  |  C  |  V  |  B  |      |Enter|  N  |  M  |  ,  |  .  |  /  |
    ├─────┼─────┼─────┼─────┼─────┼─────┤      ├─────┼─────┼─────┼─────┼─────┼─────┤
    |Ctrl | GUI |     | Alt |Lower|Space|      |WBksp|Raise|Media|     |Lead | End |
    └─────┴─────┘     └─────┴─────┴─────┘      └─────┴─────┴─────┘     └─────┴─────┘
    */
    [_QWERTY] = LAYOUT_40_alix(
        KC_TAB,    KC_Q,    KC_W,   KC_E,     KC_R,   KC_T,        KC_Y,            KC_U,   KC_I,    KC_O,      KC_P,    KC_BSPC, \
        KC_ESC,    KC_A,    KC_S,   KC_D,     KC_F,   KC_G,        KC_H,            KC_J,   KC_K,    KC_L,      KC_SCLN, KC_QUOT, \
        KC_LSFT,   KC_Z,    KC_X,   KC_C,     KC_V,   KC_B,        KC_ENT,          KC_N,   KC_M,    KC_COMM,   KC_DOT,  KC_SLSH, \
        KC_LCTL,   KC_LGUI,         KC_LALT,  LOWER,  KC_SPC,      LCTL(KC_BSPC),   RAISE,  MEDIA,              KC_LEAD, KC_END
    ),

    /* Colemak
    ┌─────┬─────┬─────┬─────┬─────┬─────┐      ┌─────┬─────┬─────┬─────┬─────┬─────┐
    | Tab |  Q  |  W  |  F  |  P  |  G  |      |  J  |  L  |  U  |  Y  |  ;  |Bksp |
    ├─────┼─────┼─────┼─────┼─────┼─────┤      ├─────┼─────┼─────┼─────┼─────┼─────┤
    | Esc |  A  |  R  |  S  |  T  |  D  |      |  H  |  N  |  E  |  I  |  O  |  '  |
    ├─────┼─────┼─────┼─────┼─────┼─────┤      ├─────┼─────┼─────┼─────┼─────┼─────┤
    |Shift|  Z  |  X  |  C  |  V  |  B  |      |Enter|  K  |  M  |  ,  |  .  |  /  |
    ├─────┼─────┼─────┼─────┼─────┼─────┤      ├─────┼─────┼─────┼─────┼─────┼─────┤
    |Ctrl | GUI |     | Alt |Lower|Space|      |WBksp|Raise|Media|     |Lead | End |
    └─────┴─────┘     └─────┴─────┴─────┘      └─────┴─────┴─────┘     └─────┴─────┘
    */
    [_COLEMAK] = LAYOUT_40_alix(
        KC_TAB,    KC_Q,    KC_W,   KC_F,     KC_P,   KC_G,        KC_J,            KC_L,   KC_U,    KC_Y,      KC_SCLN, KC_BSPC, \
        KC_ESC,    KC_A,    KC_R,   KC_S,     KC_T,   KC_D,        KC_H,            KC_N,   KC_E,    KC_I,      KC_O,    KC_QUOT, \
        KC_LSFT,   KC_Z,    KC_X,   KC_C,     KC_V,   KC_B,        KC_ENT,          KC_K,   KC_M,    KC_COMM,   KC_DOT,  KC_SLSH, \
        KC_LCTL,   KC_LGUI,         KC_LALT,  LOWER,  KC_SPC,      LCTL(KC_BSPC),   RAISE,  MEDIA,              KC_LEAD, KC_END
    ),

    /* Lower
    ┌─────┬─────┬─────┬─────┬─────┬─────┐      ┌─────┬─────┬─────┬─────┬─────┬─────┐
    |  ~  |  !  |  @  |  #  |  $  |  %  |      |  ^  |  &  |  *  |  (  |  )  | Del |
    ├─────┼─────┼─────┼─────┼─────┼─────┤      ├─────┼─────┼─────┼─────┼─────┼─────┤
    |  `  |  1  |  2  |  3  |  4  |  5  |      |  6  |  7  |  8  |  9  |  0  |  \  |
    ├─────┼─────┼─────┼─────┼─────┼─────┤      ├─────┼─────┼─────┼─────┼─────┼─────┤
    |     |  {  |  }  |  [  |  ]  |     |      |     |     |  -  |  _  |  =  |  +  |
    ├─────┼─────┼─────┼─────┼─────┼─────┤      ├─────┼─────┼─────┼─────┼─────┼─────┤
    |     |     |     |     |     |     |      | Del |Raise|     |     |     |     |
    └─────┴─────┘     └─────┴─────┴─────┘      └─────┴─────┴─────┘     └─────┴─────┘
        */
    [_LOWER]= LAYOUT_40_alix(
        KC_TILD,   KC_EXLM, KC_AT,    KC_HASH,  KC_DLR,    KC_PERC,       KC_CIRC,   KC_AMPR,  KC_ASTR,   KC_LPRN,  KC_RPRN,  KC_DEL,  \
        KC_GRV,    KC_1,    KC_2,     KC_3,     KC_4,      KC_5,          KC_6,      KC_7,     KC_8,      KC_9,     KC_0,     KC_BSLS, \
        _______,   KC_LCBR, KC_RCBR,  KC_LBRC,  KC_RBRC,   _______,       _______,   _______,  KC_MINS,   KC_UNDS,  KC_EQL,   KC_PLUS, \
        KC_RCTL,   _______,           _______,  _______,   _______,       KC_DEL,    RAISE,    _______,             _______,  KC_HOME
    ),

    /* Raise
    ┌─────┬─────┬─────┬─────┬─────┬─────┐      ┌─────┬─────┬─────┬─────┬─────┬─────┐
    |     |  F1 |  F2 |  F3 |  F4 |     |      |PGUP |     | Up  |     |     |     |
    ├─────┼─────┼─────┼─────┼─────┼─────┤      ├─────┼─────┼─────┼─────┼─────┼─────┤
    |Caps |  F5 |  F6 |  F7 |  F8 |     |      |PGDN |Left |Down |Right|     |  |  |
    ├─────┼─────┼─────┼─────┼─────┼─────┤      ├─────┼─────┼─────┼─────┼─────┼─────┤
    |     |  F9 | F10 | F11 | F12 |     |      |     |     |     |     |     |     |
    ├─────┼─────┼─────┼─────┼─────┼─────┤      ├─────┼─────┼─────┼─────┼─────┼─────┤
    |     |     |     |     |Lower|     |      |     |     |     |     |     |     |
    └─────┴─────┘     └─────┴─────┴─────┘      └─────┴─────┴─────┘     └─────┴─────┘
    */
    [_RAISE]= LAYOUT_40_alix(
        _______,   KC_F1,    KC_F2,   KC_F3,     KC_F4,     _______,       KC_PGUP,   _______,    KC_UP,     _______,   _______,   _______, \
		KC_CAPS,   KC_F5,    KC_F6,   KC_F7,     KC_F8,     _______,       KC_PGDN,   KC_LEFT,    KC_DOWN,   KC_RIGHT,  _______,   KC_PIPE, \
		_______,   KC_F9,    KC_F10,  KC_F11,    KC_F12,    _______,       _______,   _______,    _______,   _______,   _______,   _______, \
		_______,   _______,           _______,   LOWER,     _______,	   _______,   _______,    _______,              _______,   _______
    ),

    /* Media
    ┌─────┬─────┬─────┬─────┬─────┬─────┐      ┌─────┬─────┬─────┬─────┬─────┬─────┐
    |     |Vol+ |     |     |     |     |      | M00 | M01 | M02 | M03 | M04 |     |
    ├─────┼─────┼─────┼─────┼─────┼─────┤      ├─────┼─────┼─────┼─────┼─────┼─────┤
    |Mute |Vol- |Prev |Next |Play |     |      | M05 | M06 | M07 | M08 | M09 |     |
    ├─────┼─────┼─────┼─────┼─────┼─────┤      ├─────┼─────┼─────┼─────┼─────┼─────┤
    |     |     |     |     |     |     |      | M10 | M11 | M12 | M13 | M14 |     |
    ├─────┼─────┼─────┼─────┼─────┼─────┤      ├─────┼─────┼─────┼─────┼─────┼─────┤
    |     |     |     |     |     | M16 |      | M15 |     |     |     |     |     |
    └─────┴─────┘     └─────┴─────┴─────┘      └─────┴─────┴─────┘     └─────┴─────┘
    */
    [_MEDIA]= LAYOUT_40_alix(
        _______,  KC_VOLU,   _______,   _______,   _______,    _______,       MACRO00,   MACRO01,  MACRO02, MACRO03, MACRO04,   _______, \
		KC_MUTE,  KC_VOLD,   KC_MPRV,   KC_MNXT,   KC_MPLY,    _______,       MACRO05,   MACRO06,  MACRO07, MACRO08, MACRO09,   _______, \
		_______,  _______,   _______,   _______,   _______,    _______,       MACRO10,   MACRO11,  MACRO12, MACRO13, MACRO14,   _______, \
		_______,  _______,              _______,   _______,    MACRO16,	      MACRO15,   _______,  _______,          _______,   _______
    ),

    /* Adjust
    ┌─────┬─────┬─────┬─────┬─────┬─────┐      ┌─────┬─────┬─────┬─────┬─────┬─────┐
    |     |VLKTG|     |     |     |     |      |     |     |     |     |     |Reset|
    ├─────┼─────┼─────┼─────┼─────┼─────┤      ├─────┼─────┼─────┼─────┼─────┼─────┤
    |     |RGBTG|RGBM |RGBH |RGBS |RGBV |      |     |QWRTY|COLMK|     |     |     |
    ├─────┼─────┼─────┼─────┼─────┼─────┤      ├─────┼─────┼─────┼─────┼─────┼─────┤
    |     |     |     |     |CMOFF|CMON |      |     |BT A |BTUSB|BT BT|     |     |
    ├─────┼─────┼─────┼─────┼─────┼─────┤      ├─────┼─────┼─────┼─────┼─────┼─────┤
    |     |     |     |     |     |     |      |     |     |     |     |     |     |
    └─────┴─────┘     └─────┴─────┴─────┘      └─────┴─────┴─────┘     └─────┴─────┘
    */
    [_ADJUST]= LAYOUT_40_alix(
        _______,   VLK_TOG,   _______,   _______,   _______,    _______,        _______,   _______,    _______,   _______,   _______,   RESET,   \
		_______,   RGB_TOG,   RGB_MOD,   RGB_HUI,   RGB_SAI,    RGB_VAI,        _______,   QWERTY,     COLEMAK,   _______,   _______,   _______, \
		_______,   _______,   _______,   _______,   CMB_OFF,    CMB_ON,         _______,   OUT_AUTO,   OUT_USB,   OUT_BT,    _______,   _______, \
		_______,   _______,              _______,   _______,    _______,        _______,   _______,    _______,              _______,   _______
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QWERTY:
            if (record->event.pressed) {
                layer_move(_QWERTY);
            }
            return false;
            break;
        case COLEMAK:
            if (record->event.pressed) {
                layer_move(_COLEMAK);
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

const rgblight_segment_t PROGMEM layer_lower[] = RGBLIGHT_LAYER_SEGMENTS({9, 3, HSV_BLUE});
const rgblight_segment_t PROGMEM layer_raise[] = RGBLIGHT_LAYER_SEGMENTS({0, 3, HSV_RED});
const rgblight_segment_t PROGMEM layer_media[] = RGBLIGHT_LAYER_SEGMENTS({0, 3, HSV_GREEN});
const rgblight_segment_t PROGMEM layer_adjust[] = RGBLIGHT_LAYER_SEGMENTS({0, 3, HSV_PURPLE},{9, 3, HSV_PURPLE});

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
    rgblight_set_layer_state(0, layer_state_cmp(state, 2));
    rgblight_set_layer_state(1, layer_state_cmp(state, 3));
    rgblight_set_layer_state(2, layer_state_cmp(state, 4));
    rgblight_set_layer_state(3, layer_state_cmp(state, 5));

    return state;
};

LEADER_EXTERNS();

void matrix_scan_user(void) {
	LEADER_DICTIONARY(){
		leading = false;
		leader_end();

        SEQ_ONE_KEY(KC_T){
		      SEND_STRING("sudo /etc/init.d/tomcat7 restart");
	      }
        SEQ_TWO_KEYS(KC_T,KC_T){
		      SEND_STRING("sudo /etc/init.d/tomcat7 stop");
	      }
        SEQ_THREE_KEYS(KC_T,KC_T,KC_T){
		      SEND_STRING("sudo /etc/init.d/tomcat7 start");
	      }
        SEQ_ONE_KEY(KC_COMM){
          SEND_STRING("sudo service delegosrv-"SS_TAP(X_TAB)"restart");
        }
        SEQ_TWO_KEYS(KC_COMM,KC_COMM){
          SEND_STRING("sudo service delegosrv-"SS_TAP(X_TAB)"stop");
        }
        SEQ_THREE_KEYS(KC_COMM,KC_COMM,KC_COMM){
          SEND_STRING("sudo service delegosrv- start");
          SEND_STRING(SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT));
        }
        SEQ_ONE_KEY(KC_M){
          SEND_STRING("sudo service delegomt-"SS_TAP(X_TAB)"restart");
        }
        SEQ_TWO_KEYS(KC_M,KC_M){
          SEND_STRING("sudo service delegomt-"SS_TAP(X_TAB)"stop");
        }
        SEQ_THREE_KEYS(KC_M,KC_M,KC_M){
          SEND_STRING("sudo service delegomt- start");
          SEND_STRING(SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT));
        }
        SEQ_ONE_KEY(KC_DOT){
          SEND_STRING("sudo service delegosecure-"SS_TAP(X_TAB)"restart");
        }
        SEQ_TWO_KEYS(KC_DOT,KC_DOT){
          SEND_STRING("sudo service delegosecure-"SS_TAP(X_TAB)"stop");
        }
        SEQ_THREE_KEYS(KC_DOT,KC_DOT,KC_DOT){
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
        SEQ_TWO_KEYS(KC_D,KC_H){
          SEND_STRING("delego-home.sh");
        }
        SEQ_ONE_KEY(KC_P){
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
