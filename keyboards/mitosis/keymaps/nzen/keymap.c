

#include QMK_KEYBOARD_H

enum mitosis_layers
{
	_QWERTY,
	_WORKMAN,
	_NUMBERS,
	_PUNCT,
	_MOUSE,
	_LAYERS,
	_GAMING,
	_UNICODE,
	_NUMPAD
};


//Mousekeys
#define MOUSEKEY_DELAY 300
#define MOUSEKEY_INTERNAL 50
#define MOUSEKEY_MAX_SPEED 20
#define MOUSEKEY_TIME_TO_MAX 30
#define MOUSEKEY_WHEEL_MAX_SPEED 8
#define MOUSEKEY_WHEEL_TIME_TO_MAX 40

// Fillers to make layering more clear
#define XXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // https://github.com/nhou7/qmk_firmware_amj40/blob/master/doc/keycode.txt
  /* QWERTY
  ['Q', 'W', 'E', 'R', 'T',// 'Y', 'U', 'I', 'O', 'P' ],
  ['A', 'S', 'D', 'F', 'G',// 'H', 'J', 'K', 'L', '; :' ],
  ['Z', 'X', 'C', 'V', 'B',// 'N', 'M', ', <', '. >', '\' "' ],
  [  'back', 'del', 'ctrl', 'L_n',// 'L_p', 'ctrl', 'ent', 'back',  ],
  [  'alt', '0', 'shif', 'spac',// 'spac', 'shif', 'cap', 'alt',  ]
   */
  [_QWERTY] = LAYOUT(
    KC_Q,      KC_W,      KC_E,      KC_R,      KC_T,     KC_Y,      KC_U,        KC_I,        KC_O,   KC_P,
    KC_A,      KC_S,      KC_D,      KC_F,      KC_G,     KC_H,      KC_J,        KC_K,        KC_L,   KC_SCLN,
    KC_Z,      KC_X,      KC_C,      KC_V,      KC_B,     KC_N,      KC_M,        KC_COMM,     KC_DOT, KC_QUOTE,
               KC_BSPC,   KC_DELETE, KC_LCTL,   TG( 2 ),  TG( 3 ),   KC_RCTL,     KC_ENTER,    KC_BSPC,
               KC_LALT,   KC_0,      KC_LSFT,   KC_SPACE, KC_SPACE,  KC_RSFT,     KC_CAPS,     KC_RALT
  ),
  /*
  ['Q', 'D', 'R', 'W', 'B',/ ** / 'J', 'F', 'U', 'P', '; :' ],
  ['A', 'S', 'H', 'T', 'G',/ ** / 'Y', 'N', 'E', 'O', 'I' ],
  ['Z', 'X', 'M', 'C', 'V',/ ** / 'K', 'L', ', <', '. >', '\' "' ],
  [ '', '', '', '',/ ** / '', '', '', '',  ],
  [ '', '4', '', '',/ ** / '', '', '', '',  ]
   */
  [_WORKMAN] = LAYOUT(
    KC_Q, KC_D,    KC_R,    KC_W,    KC_B,    KC_J,    KC_F,    KC_U,     KC_P,    KC_SCLN,
    KC_A, KC_S,    KC_H,    KC_T,    KC_G,    KC_Y,    KC_N,    KC_E,     KC_O,    KC_I,
    KC_Z, KC_X,    KC_M,    KC_C,    KC_V,    KC_K,    KC_L,    KC_COMMA, KC_DOT,  KC_QUOTE,
          _______, _______, _______, _______, _______, _______, _______,  _______,
          _______, KC_1,    _______, _______, _______, _______, _______,  _______
  ),
  /*
  ['9', '8', '7', '6', '5',/ ** / 'F2', 'pDn', *up* /, '*tab* /, 'pUp' ],
  [' 4', ' 3', ' 2', ' 1', ' 0',/ ** / 'home', *lf* /, '*dn* /, *rt* /, 'end' ],
  ['undo', 'cut', 'copy', 'paste', 'os',/ ** / 'D', '_', ',', '-', '.' ],
  // --
  [ '', '', '', 'L_=6',/ ** / 'L_7', '', '', '',  ],
  [ '', '6', '', '',/ ** / '', '', '', '',  ]
   */
  [_NUMBERS] = LAYOUT(
    KC_9,       KC_8,       KC_7,       KC_6,       KC_5,    KC_F2,   KC_PGDN,       KC_UP,    KC_TAB,   KC_PGUP,
    KC_4,       KC_3,       KC_2,       KC_1,       KC_0,    KC_HOME, KC_LEFT,       KC_DOWN,  KC_RIGHT, KC_END,
    LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), KC_LGUI, KC_D,    KC_UNDERSCORE, KC_COMMA, KC_MINUS, KC_DOT,
                _______,    _______,    _______,    TG( 2 ), TG( 3 ), _______,       _______,  _______,
                _______,    KC_2,       _______,    _______, _______, _______,       _______,  _______
  ),
  /*
  [ '#', '@', '&', '.', ';',/ ** / '_', ',', '|', '^', '%' ],
  [ '*', '+', '{', '(', ':',/ ** / '"', ')', '}', '-', '=' ],
  [ '\\', '?', '<', '[', '$',/ ** / '~', ']', '>', '!', '/' ],
  // --
  ['', '', '', 'L_8',/ ** / 'L_=7', '', '', '',  ],
  ['', '7', '', '',/ ** / '', '', '', '',  ]
   */
  [_PUNCT] = LAYOUT(
    KC_HASH,     KC_AT,       KC_AMPERSAND, KC_DOT,      KC_SCLN,   KC_UNDERSCORE, KC_COMMA,    KC_PIPE, KC_CIRCUMFLEX, KC_PERCENT,
    KC_ASTERISK, KC_PLUS,     KC_LCBR,      KC_LPRN,     KC_COLON,  KC_DQUO,       KC_RPRN,     KC_RCBR, KC_MINUS,      KC_EQUAL,
    KC_BSLS,     KC_QUESTION, KC_LT,        KC_LBRC,     KC_DOLLAR, KC_TILDE,      KC_RBRC,     KC_GT,   KC_EXCLAIM,    KC_SLASH,
                 _______,     _______,      _______,     TG( 4 ),   TG( 3 ),       _______,     _______, _______,
                 _______,     KC_3,         _______,     _______,   _______,       _______,     _______, _______
  ),
  /*
  ['F6', 'F7', 'F8', 'F9', 'F10',/ ** / 'app', 'mb1', 'mmU', 'mb2', 'mwU' ],
  ['F1', 'F2', 'F3', 'F4', 'F5',/ ** / 'mnu', 'mmL', 'mmD', 'mmR', 'mwD' ],
  ['F11', 'F12', '`', 'mute', 'ESC',/ ** / 'prtSc', 'scrLk', 'mwL', 'mwR', 'mb3' ],
  // --
  [ '', '', '', 'L_=8',/ ** / 'L_9', '', '', '',  ],
  [ '', '8', '', '',/ ** / '', '', '', '',  ]
   */
  [_MOUSE] = LAYOUT(
    KC_F6,  KC_F7,   KC_F8,    KC_F9,    KC_F10,    KC_MENU,    KC_MS_BTN1, KC_MS_UP,      KC_MS_BTN2,     KC_MS_WH_UP,
    KC_F1,  KC_F2,   KC_F3,    KC_F4,    KC_F5,     KC_MENU,    KC_MS_LEFT, KC_MS_DOWN,    KC_MS_RIGHT,    KC_MS_WH_DOWN,
    KC_F11, KC_F12,  KC_GRAVE, KC_MUTE,  KC_ESCAPE, KC_PSCR,    KC_SCRL,    KC_MS_WH_LEFT, KC_MS_WH_RIGHT, KC_MS_BTN3,
            _______, _______,  _______,  TG( 4 ),   TG( 5 ),    _______,    _______,       _______,
            _______, KC_4,     _______,  _______,   _______,    _______,    _______,       _______
  ),
  /*
  ['L_ma1', '!', 'L_dv2', '!', 'L_cl3',/ ** / 'L_wk4', '!', 'L_ar5', '!', '!' ],
  ['!', '!', '!', '!', '!',/ ** / '!', '!', '!', '!', '!' ],
  ['L_gmA', '!', 'L_ucB', '!', 'L_npC',/ ** / '!', '!', '!', '!', '!' ],
  // --
  [ '', '', '', 'L_=9',/ ** / 'L_=9', '', '', '',  ],
  [ '', '9', '', '',/ ** / '', '', '', '',  ]
   */
  [_LAYERS] = LAYOUT(
    KC_EXCLAIM, KC_EXCLAIM, KC_EXCLAIM, KC_EXCLAIM, KC_EXCLAIM, TG( 1 ),    KC_EXCLAIM, KC_EXCLAIM, KC_EXCLAIM, KC_EXCLAIM,
    KC_EXCLAIM, KC_EXCLAIM, KC_EXCLAIM, KC_EXCLAIM, KC_EXCLAIM, KC_EXCLAIM, KC_EXCLAIM, KC_EXCLAIM, KC_EXCLAIM, KC_EXCLAIM,
    TG( 6 ),    KC_EXCLAIM, TG( 7 ),    KC_EXCLAIM, TG( 8 ),    KC_EXCLAIM, KC_EXCLAIM, KC_EXCLAIM, KC_EXCLAIM, KC_EXCLAIM,
                _______,    _______,    _______,    TG( 5 ),    TG( 5 ),    _______,    _______,    _______,
                _______,    KC_5,       _______,    _______,    _______,    _______,    _______,    _______
  ),
  /*
  ['Q', 'W', 'E', 'R', 'T',/ ** / 'P', 'Y', '\u2191'*up* /, 'K', '1' ],
  ['A', 'S', 'D', 'F', 'G',/ ** / 'H', '\u2190'*lf* /, '\u2193'*dn* /, '\u2192'*rt* /, '2' ],
  ['Z', 'X', 'C', 'V', 'B',/ ** / 'M', '*', '*', '*', '3' ],
  // --
  [ '', '', '', 'L_=A',/ ** / 'A', '', '', '',  ],
  [ '', 'A', '', '',/ ** / '', '', '', '',  ]
   */
  [_GAMING] = LAYOUT(
    KC_Q, KC_W,    KC_E,    KC_R,    KC_T,    KC_P,    KC_Y,        KC_UP,       KC_K,        KC_1,
    KC_A, KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_LEFT,     KC_DOWN,     KC_RIGHT,    KC_2,
    KC_Z, KC_X,    KC_C,    KC_V,    KC_B,    KC_M,    KC_ASTERISK, KC_ASTERISK, KC_ASTERISK, KC_3,
          _______, _______, _______, TG( 6 ), KC_6,    _______,     _______,     _______,
          _______, KC_6,    _______, _______, _______, _______,     _______,     _______
  ),
  /*
  ['\u00a2'cent* /, '\u00bc'1/4* /, '\u00bd'1/2* /, '\u03a3'sum* /, '\u00d8'Oslash* /,/ ** / '\u250f'box ul* /, '\u2533'box um* /, '\u2513'box ur* /, '\u03bb'lambda* /, '\u2018'sm'dn* / ],
  ['\u00F1'n~* /, '\u00a9'&copy* /, '\u00b0'degrees* /, '\u00b1'+-* /, '\u2b0f'arrow up* /,/ ** / '\u2523'box ml* /, '\u254B'box mm* /, '\u252B'box mr* /, '\u0394'delta* /, '\u2019'sm'up* / ],
  ['\u00a1'down !* /, '\u00bf'down ?* /, '\u00d7'mult x* /, '\u00f7'div/ * /, '\u03c0'pi* /,/ ** / '\u2517'box ll* /, '\u253b'bos lm* /, '\u251b'box lr* /, '\u201c'sm"dn* /, '\u201d'sm"up* / ],
  // --
  [ '', '', '', 'L_=B',/ ** / 'B', '', '', '',  ],
  [ '', 'B', '', '',/ ** / '', '', '', '',  ]
   */
  [_UNICODE] = LAYOUT(
    UC(0x00A2), UC(0x00BC), UC(0x00BD), UC(0x03A3), UC(0x00D8), UC(0x250F), UC(0x2533), UC(0x2513), UC(0x03BB), UC(0x2018),
    UC(0x00F1), UC(0x00A9), UC(0x00B0), UC(0x00B1), UC(0x2B0F), UC(0x2523), UC(0x254B), UC(0x252B), UC(0x0394), UC(0x2019),
    UC(0x00A1), UC(0x00BF), UC(0x00D7), UC(0x00F7), UC(0x03C0), UC(0x2517), UC(0x253B), UC(0x251B), UC(0x201C), UC(0x201D),
                _______,    _______,    _______,    TG( 7 ),    KC_7,       _______,    _______,    _______,
                _______,    KC_7,       _______,    _______,    _______,    _______,    _______,    _______
  ),
  /*
  ['n-.', 'n-7', 'n-8', 'n-9', 'n--',/ ** / 'n-=', 'volU', 'volD', 'volU', 'volD' ],
  ['n-0', 'n-4', 'n-5', 'n-6', 'n-+',/ ** / 'N-lck', 'BACK', 'MUTE', 'RGUI', 'paus' ],
  ['n -*', 'n-1', 'n-2', 'n-3', 'n-/',/ ** / 'n-ent', 'PLAY', 'PREV', 'NEXT', 'insr' ],
  // --
  [ '', '', '', 'L_=C',/ ** / 'C', '', '', '',  ],
  [ '', 'C', '', '',/ ** / '', '', '', '',  ]
   */
  [_NUMPAD] = LAYOUT(
    KC_KP_DOT,      KC_KP_7, KC_KP_8, KC_KP_9, KC_KP_MINUS, KC_KP_EQUAL, KC_AUDIO_VOL_UP,     KC_AUDIO_VOL_DOWN,   KC_VOLU,             KC_VOLD,
    KC_KP_0,        KC_KP_4, KC_KP_5, KC_KP_6, KC_KP_PLUS,  KC_NUM,      KC_WWW_BACK,         KC_AUDIO_MUTE,       KC_RGUI,             KC_PAUSE,
    KC_KP_ASTERISK, KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_SLASH, KC_KP_ENTER, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_PREV_TRACK, KC_MEDIA_NEXT_TRACK, KC_INSERT,
                    _______, _______, _______, TG( 8 ),     KC_8,        _______,             _______,             _______,
                    _______, KC_8,    _______, _______,     _______,     _______,             _______,             _______
  )// ,
  /*
   * /
  [_] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
             _______, _______, _______, _______, _______, _______, _______, _______,
             _______, _______, _______, _______, _______, _______, _______, _______
  )
   */
};

void matrix_scan_user(void) {
    uint8_t layer = get_highest_layer(layer_state);

    switch (layer) {
    	case _QWERTY:
    	case _WORKMAN:
    		set_led_off;
    		break;
        case _NUMBERS:
            set_led_blue;
            break;
        case _PUNCT:
            set_led_red;
            break;
        case _MOUSE:
            set_led_green;
            break;
        case _LAYERS:
            set_led_yellow;
            break;
        case _UNICODE:
            set_led_cyan;
            break;
        default:
            break;
   }
};

void matrix_init_user(void) {
	set_unicode_input_mode(UNICODE_MODE_LINUX); // or UNICODE_MODE_WINCOMPOSE
};
