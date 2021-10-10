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
  MEDIA,
  LOWER,
  RAISE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Qwerty
    ┌─────┬─────┬─────┬─────┬─────┬─────┐      ┌─────┬─────┬─────┬─────┬─────┬─────┐
    | Tab |  Q  |  W  |  E  |  R  |  T  |      |  Y  |  U  |  I  |  O  |  P  |Bksp |
    ├─────┼─────┼─────┼─────┼─────┼─────┤      ├─────┼─────┼─────┼─────┼─────┼─────┤
    | Esc |  A  |  S  |  D  |  F  |  G  |      |  H  |  J  |  K  |  L  |  ;  |  '  |
    ├─────┼─────┼─────┼─────┼─────┼─────┤      ├─────┼─────┼─────┼─────┼─────┼─────┤
    |Shift|  Z  |  X  |  C  |  V  |  B  |      |ENTER|  N  |  M  |  ,  |  .  |  /  |
    ├─────┼─────┼─────┼─────┼─────┼─────┤      ├─────┼─────┼─────┼─────┼─────┼─────┤
    |Ctrl | GUI |     | Alt |Lower|Space|      |Media|Raise|WBksp|     |Lead | End |
    └─────┴─────┘     └─────┴─────┴─────┘      └─────┴─────┴─────┘     └─────┴─────┘
    */
    [_QWERTY] = LAYOUT_40_alix(
        KC_TAB,    KC_Q,    KC_W,   KC_E,     KC_R,   KC_T,        KC_Y,    KC_U,   KC_I,   KC_O,      KC_P,    KC_BSPC, \
        KC_ESC,    KC_A,    KC_S,   KC_D,     KC_F,   KC_G,        KC_H,    KC_J,   KC_K,   KC_L,      KC_SCLN, KC_QUOT, \
        KC_LSFT,   KC_Z,    KC_X,   KC_C,     KC_V,   KC_B,        KC_ENT,  KC_N,   KC_M,   KC_COMM,   KC_DOT,  KC_SLSH, \
        KC_LCTL,   KC_LGUI,         KC_LALT,  LOWER,  KC_SPC,      MEDIA,   RAISE,  LCTL(KC_BSPC),      KC_LEAD, KC_END
    ),

    /* Colemak
    ┌─────┬─────┬─────┬─────┬─────┬─────┐      ┌─────┬─────┬─────┬─────┬─────┬─────┐
    | Tab |  Q  |  W  |  F  |  P  |  G  |      |  J  |  L  |  U  |  Y  |  ;  |Bksp |
    ├─────┼─────┼─────┼─────┼─────┼─────┤      ├─────┼─────┼─────┼─────┼─────┼─────┤
    | Esc |  A  |  R  |  S  |  T  |  D  |      |  H  |  N  |  E  |  I  |  O  |  '  |
    ├─────┼─────┼─────┼─────┼─────┼─────┤      ├─────┼─────┼─────┼─────┼─────┼─────┤
    |Shift|  Z  |  X  |  C  |  V  |  B  |      |ENTER|  K  |  M  |  ,  |  .  |  /  |
    ├─────┼─────┼─────┼─────┼─────┼─────┤      ├─────┼─────┼─────┼─────┼─────┼─────┤
    |Ctrl | GUI |     | Alt |Lower|Space|      |Media|Raise|WBksp|     |Lead | End |
    └─────┴─────┘     └─────┴─────┴─────┘      └─────┴─────┴─────┘     └─────┴─────┘
    */
    [_COLEMAK] = LAYOUT_40_alix(
        KC_TAB,    KC_Q,    KC_W,   KC_F,     KC_P,   KC_G,        KC_J,    KC_L,   KC_U,   KC_Y,      KC_SCLN, KC_BSPC, \
        KC_ESC,    KC_A,    KC_R,   KC_S,     KC_T,   KC_D,        KC_H,    KC_N,   KC_E,   KC_I,      KC_O,    KC_QUOT, \
        KC_LSFT,   KC_Z,    KC_X,   KC_C,     KC_V,   KC_B,        KC_ENT,  KC_K,   KC_M,   KC_COMM,   KC_DOT,  KC_SLSH, \
        KC_LCTL,   KC_LGUI,         KC_LALT,  LOWER,  KC_SPC,      MEDIA,   RAISE,  LCTL(KC_BSPC),      KC_LEAD, KC_END
    ),

    /* Lower
    ┌─────┬─────┬─────┬─────┬─────┬─────┐      ┌─────┬─────┬─────┬─────┬─────┬─────┐
    |  ~  |  !  |  @  |  #  |  $  |  %  |      |  ^  |  &  |  *  |  (  |  )  | Del |
    ├─────┼─────┼─────┼─────┼─────┼─────┤      ├─────┼─────┼─────┼─────┼─────┼─────┤
    |  `  |  1  |  2  |  3  |  4  |  5  |      |  6  |  7  |  8  |  9  |  0  |  \  |
    ├─────┼─────┼─────┼─────┼─────┼─────┤      ├─────┼─────┼─────┼─────┼─────┼─────┤
    |     |  {  |  }  |  [  |  ]  |Snip |      |     |     |  -  |  _  |  =  |  +  |
    ├─────┼─────┼─────┼─────┼─────┼─────┤      ├─────┼─────┼─────┼─────┼─────┼─────┤
    |RCtrl|     |     |     |     |     |      |WDel |Raise|     |     |     |Home |
    └─────┴─────┘     └─────┴─────┴─────┘      └─────┴─────┴─────┘     └─────┴─────┘
        */
    [_LOWER]= LAYOUT_40_alix(
        KC_TILD,     KC_EXLM, KC_AT,    KC_HASH,  KC_DLR,    KC_PERC,       KC_CIRC,       KC_AMPR,  KC_ASTR,   KC_LPRN,  KC_RPRN,  KC_DEL,  \
        KC_GRV,      KC_1,    KC_2,     KC_3,     KC_4,      KC_5,          KC_6,          KC_7,     KC_8,      KC_9,     KC_0,     KC_BSLS, \
        _______,     KC_LCBR, KC_RCBR,  KC_LBRC,  KC_RBRC,   SGUI(KC_S),    _______,       _______,  KC_MINS,   KC_UNDS,  KC_EQL,   KC_PLUS, \
        KC_RCTL,     _______,           _______,  _______,   _______,       _______,       RAISE,    LCTL(KC_DEL),        _______,  KC_HOME
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
    |DMStp|Rec 1|Rec 2|     |     |     |      |     |Play |Vol+ |Mute |     |Media|
    ├─────┼─────┼─────┼─────┼─────┼─────┤      ├─────┼─────┼─────┼─────┼─────┼─────┤
    |     |Play1|Play2|     |     |     |      |     |Prev |Vol- |Next |     |     |
    ├─────┼─────┼─────┼─────┼─────┼─────┤      ├─────┼─────┼─────┼─────┼─────┼─────┤
    |     |     |     |     |     |     |      |     |     |     |     |     |     |
    ├─────┼─────┼─────┼─────┼─────┼─────┤      ├─────┼─────┼─────┼─────┼─────┼─────┤
    |     |     |     |     |     |     |      |     |     |     |     |     |     |
    └─────┴─────┘     └─────┴─────┴─────┘      └─────┴─────┴─────┘     └─────┴─────┘
    */
    [_MEDIA]= LAYOUT_40_alix(
        DM_RSTP,  DM_REC1,   DM_REC2,   _______,   _______,    _______,       _______,   KC_MPLY,  KC_VOLU, KC_MUTE, _______,   KC_MSEL, \
		_______,  DM_PLY1,   DM_PLY2,   _______,   _______,    _______,       _______,   KC_MPRV,  KC_VOLD, KC_MNXT, _______,   _______, \
		_______,  _______,   _______,   _______,   _______,    _______,       _______,   _______,  _______, _______, _______,   _______, \
		_______,  _______,              _______,   _______,    _______,	      _______,   _______,  _______,          _______,   _______
    ),

    /* Adjust
    ┌─────┬─────┬─────┬─────┬─────┬─────┐      ┌─────┬─────┬─────┬─────┬─────┬─────┐
    |     |     |     |     |     |     |      |     |     |     |     |     |Reset|
    ├─────┼─────┼─────┼─────┼─────┼─────┤      ├─────┼─────┼─────┼─────┼─────┼─────┤
    |     |RGBTG|RGBM |RGBH |RGBS |RGBV |      |     |QWRTY|COLMK|     |     |     |
    ├─────┼─────┼─────┼─────┼─────┼─────┤      ├─────┼─────┼─────┼─────┼─────┼─────┤
    |     |     |     |     |     |     |      |     |BT A |BTUSB|BT BT|     |     |
    ├─────┼─────┼─────┼─────┼─────┼─────┤      ├─────┼─────┼─────┼─────┼─────┼─────┤
    |     |     |     |     |     |     |      |     |     |     |     |     |     |
    └─────┴─────┘     └─────┴─────┴─────┘      └─────┴─────┴─────┘     └─────┴─────┘
    */
    [_ADJUST]= LAYOUT_40_alix(
        _______,   _______,   _______,   _______,   _______,    _______,        _______,   _______,    _______,   _______,   _______,   RESET,   \
		_______,   RGB_TOG,   RGB_MOD,   RGB_HUI,   RGB_SAI,    RGB_VAI,        _______,   QWERTY,     COLEMAK,   _______,   _______,   _______, \
		_______,   _______,   _______,   _______,   _______,    _______,        _______,   OUT_AUTO,   OUT_USB,   OUT_BT,    _______,   _______, \
		_______,   _______,              _______,   _______,    _______,        _______,   _______,    _______,              _______,   _______
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
            break;
        case COLEMAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAK);
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
const rgblight_segment_t PROGMEM caps_lock[] = RGBLIGHT_LAYER_SEGMENTS({9, 1, HSV_YELLOW});

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

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(4, led_state.caps_lock);
    return true;
};

layer_state_t layer_state_set_user(layer_state_t state)
{
    rgblight_set_layer_state(0, layer_state_cmp(state, _LOWER));
    rgblight_set_layer_state(1, layer_state_cmp(state, _RAISE));
    rgblight_set_layer_state(2, layer_state_cmp(state, _MEDIA));
    rgblight_set_layer_state(3, layer_state_cmp(state, _ADJUST));

    return state;
};

LEADER_EXTERNS();

void matrix_scan_user(void) {
	LEADER_DICTIONARY(){
		leading = false;
		leader_end();

        SEQ_ONE_KEY(KC_BSPC){
            SEND_STRING(SS_LCTRL("`"));
        }
        SEQ_ONE_KEY(KC_QUOT){
            SEND_STRING(SS_LCTRL(SS_LSFT("p")));
        }
	}
};
