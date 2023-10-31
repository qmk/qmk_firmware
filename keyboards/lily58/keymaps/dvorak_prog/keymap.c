#include QMK_KEYBOARD_H

enum layer_number {
  _DVORAK = 0,
  _LOWER,
  _RAISE,
  _NUMBERS,
  _EFS,
  _ADJUST,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*================================================================================================================
 * PROGRAMMER DVORAK
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   7  |   5  |   3  |   1  |  9   |                    |   0  |   2  |   4  |   6  |   8  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   :  |   <  |   >  |   P  |   Y  |                    |   F  |   G  |   C  |   R  |   L  |  ?   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |   A  |   O  |   E  |   U  |   I  |-------.    ,-------|   D  |   H  |   T  |   N  |   S  |  -   |
 * |------+------+------+------+------+------|DELETE |    |EFS    |------+------+------+------+------+------|
 * |LShift|   "  |   Q  |   J  |   K  |   X  |-------|    |-------|   B  |   M  |   W  |   V  |   Z  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt |NUMBERS LOWER| /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
 [_DVORAK] = LAYOUT(
  KC_ESC,   KC_7,           KC_5,       KC_3,       KC_1,    KC_9,                              KC_0,    KC_2,    KC_4,     KC_6,   KC_8,   KC_GRAVE,
  KC_TAB,   KC_SEMICOLON,   KC_COMMA,   KC_DOT,     KC_P,    KC_Y,                              KC_F,    KC_G,    KC_C,     KC_R,   KC_L,   KC_SLASH,
  KC_LCTL,  KC_A,           KC_O,       KC_E,       KC_U,    KC_I,                              KC_D,    KC_H,    KC_T,     KC_N,   KC_S,   KC_MINS,
  KC_LSFT,  KC_QUOTE,       KC_Q,       KC_J,       KC_K,    KC_X,   KC_DELETE,       TG(_EFS), KC_B,    KC_M,    KC_W,     KC_V,   KC_Z,   KC_RSFT,
                            KC_LALT,    TG(_NUMBERS),    MO(_LOWER), KC_SPC,          KC_ENT,   MO(_RAISE),     KC_BSPC, KC_RGUI
),

/*================================================================================================================
 * LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |   *  |   )  |   +  |   ]  |   !  |  #   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |   ć  |      |   ł  |  @   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |      |   ń  |   ś  |   _  |
 * |------+------+------+------+------+------|DELETE |    |RGUI   |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------| left | down |  up  | right|   ż  |   |  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt |NUMBERS 	  | /Space  /       \Enter \  |RAISE |BackSP| EFS  |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_LOWER] = LAYOUT(
  _______,  _______,   _______, _______, _______, _______,                    KC_ASTERISK,KC_RIGHT_PAREN, KC_PLUS,    KC_RIGHT_BRACKET, KC_EXCLAIM, KC_HASH,
  _______,  _______,   _______, _______, _______, _______,                    _______,    _______,        RALT(KC_C), _______,          RALT(KC_L),    KC_AT,
  _______,  _______,   _______, _______, _______, _______,                    _______,    _______,        _______,    RALT(KC_N),       RALT(KC_S),    KC_UNDERSCORE,
  _______,  _______,   _______, _______, _______, _______,  _______, _______, KC_LEFT,    KC_DOWN,        KC_UP,      KC_RIGHT,         RALT(KC_Z),    KC_PIPE,
                                _______, _______, XXXXXXX, _______,   _______, _______,  _______, _______
),

/*================================================================================================================
 * RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |   &  |  [   |   {  |   }  |   (  |   =  |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |CpsLck|   ą  |  ó   |   ę  |      |      |-------.    ,-------|      |      |      |      |	     |      |
 * |------+------+------+------+------+------|DELETE |    |RGUI   |------+------+------+------+------+------|
 * |      |   ^  |  $   |  @   |   %  |  \   |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt |NUMBERS LOWER| /Space  /       \Enter \  |      |BackSP| EFS  |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_RAISE] = LAYOUT(
  KC_AMPERSAND, KC_LEFT_BRACKET, KC_LEFT_CURLY_BRACE, KC_RIGHT_CURLY_BRACE, KC_LEFT_PAREN, KC_EQUAL,        		       _______, _______, _______, _______,  _______, _______,
  _______,  	_______, 	     _______,             _______,              _______,       _______,                        _______, _______, _______, _______,  _______, _______,
  KC_CAPS,  	RALT(KC_A),      RALT(KC_O),   	      RALT(KC_E),           _______,   	   _______,                        _______, _______, _______, _______,  _______, _______,
  _______,   	KC_CIRCUMFLEX,   KC_DOLLAR,   	      KC_AT,  		        KC_PERCENT,    KC_BACKSLASH, _______, _______, _______, _______, _______, _______,  _______, _______,
                               	 	                                    _______, _______, _______,   _______,          _______,  XXXXXXX, _______, _______
),

/*================================================================================================================
 * NUMBERS
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |   7  |   8  |  9   |                    |      |  +   |   -  |  =   |   \  |   ^  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |   4  |   5  |  6   |-------.    ,-------|      | [    |  ]   |   *  |	  %  |      |
 * |------+------+------+------+------+------|DELETE |    |RGUI   |------+------+------+------+------+------|
 * |      |      |   0  |   1  |   2  |  3   |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt |DEFAULT LOWER| /Space  /       \Enter \  |      |BackSP|      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_NUMBERS] = LAYOUT(
  _______, _______, _______, _______, _______, _______,        		          _______, _______, _______,   _______,     _______, _______,
  _______, _______, _______, KC_7,    KC_8,    KC_9,                          _______, KC_PLUS, KC_MINUS,  KC_EQL,      KC_NUBS, KC_CIRCUMFLEX,
  _______, _______, _______, KC_4,    KC_5,    KC_6,                          _______, KC_LBRC, KC_RBRC,   KC_ASTERISK, KC_PERCENT, _______,
  _______, _______, KC_0,    KC_1,    KC_2,    KC_3,    _______,   _______,   _______, _______, _______,   _______,     _______, _______,
                       _______, _______,		_______,   _______,    _______,  XXXXXXX, _______, _______
),

/*================================================================================================================
 *  EFS
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |  F1  |  F2  |  F3  |  F4  |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |  F5  |  F6  |  F7  |  F8  |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|DELETE |    |RGUI   |------+------+------+------+------+------|
 * |      |      |  F9  |  F10 |  F11 |  F12 |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt |      | 	  | /Space  /       \Enter \  |RAISE |BackSP|      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_EFS] = LAYOUT(
  _______,  _______,  _______, _______,  _______,  _______,                   _______,  _______, _______,  _______,  _______,  _______,
  _______,  _______,  KC_F1,   KC_F2,    KC_F3,    KC_F4,                     _______,  _______, _______,  _______,  _______,  _______,
  _______,  _______,  KC_F5,   KC_F6,    KC_F7,    KC_F8,                     _______,  _______, _______,  _______,  _______,  _______,
  _______,  _______,  KC_F9,   KC_F10,   KC_F11,   KC_F12, _______, _______,  _______,  _______, _______,  _______,  _______,  _______,
                        _______,    _______,    XXXXXXX, _______,    _______,  _______, _______, _______
),

/*================================================================================================================
 * ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |RGB ON| HUE+ | SAT+ | VAL+ |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      | MODE | HUE- | SAT- | VAL- |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [_ADJUST] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                             _______, _______, _______, _______, _______,  _______, _______, _______
  )
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

/* SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk */
#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (is_keyboard_master())
    return OLED_ROTATION_270;  // flips the display 180 degrees if offhand
  return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// void set_timelog(void);
// const char *read_timelog(void);

void render_default_layer_state(void) {
    oled_write_P(PSTR("Layer"), false);
    oled_write_P(PSTR(" "), false);
    switch (get_highest_layer(layer_state)) {
        case _DVORAK:
            oled_write_P(PSTR("DVRK"), false);
            break;
        case _LOWER:
            oled_write_ln_P(PSTR("LOW"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("HIGH"), false);
            break;
        case _ADJUST:
            oled_write_ln_P(PSTR("ADJ"), false);
            break;
        case _NUMBERS:
            oled_write_ln_P(PSTR("NUM"), false);
            break;
        case _EFS:
            oled_write_ln_P(PSTR("EFS"), false);
            break;

        default:
            oled_write_ln_P(PSTR("Undefined"), false);
    }
}

char wpm_str[3];
bool oled_task_user(void) {
  if (is_keyboard_master()) {
    oled_write_P(PSTR("-----"), false);
    oled_write_ln(read_keylogs(), false);
    oled_write_P(PSTR("-----"), false);
    oled_write_P(PSTR("WPM: "), false);
    oled_write_ln(get_u8_str(get_current_wpm(), ' '), false);
    oled_write_P(PSTR("-----"), false);
    render_default_layer_state();
    oled_write_P(PSTR("-----"), false);
  } else {
    oled_write(read_logo(), false);
  }
    return false;
}
#endif // OLED_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_ENABLE
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }
  return true;
}
