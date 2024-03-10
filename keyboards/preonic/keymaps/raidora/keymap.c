#include "QMK_KEYBOARD_H"

enum preonic_layers {
  _QWERTY,
  _GAMING,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum preonic_keycodes {
  QWERTY,
  LOWER,
  RAISE,
  BACKLIT
};

#define ALT_ENT  MT(MOD_LALT, KC_ENT)

//Special characters for estonian input method
#define EE_Ö KC_SCLN
#define EE_Ä KC_QUOT
#define EE_Õ KC_RBRC
#define EE_Ü KC_LBRC
#define EE_DASH KC_SLSH
#define EE_LEFT_ANGLE_BRACKET KC_NUBS
#define EE_RIGHT_ANGLE_BRACKET S(KC_NUBS)
#define EE_LEFT_BRACKET S(KC_8)
#define EE_RIGHT_BRACKET S(KC_9)
#define EE_LEFT_CURLY_BRACKET RALT(KC_7)
#define EE_RIGHT_CURLY_BRACKET RALT(KC_0)
#define EE_LEFT_SQUARE_BRACKET RALT(KC_8)
#define EE_RIGHT_SQUARE_BRACKET RALT(KC_9)

#define EE_DOLLAR RALT(KC_4)
#define EE_EURO RALT(KC_5)
#define EE_AMPERSAND S(KC_6de)
#define EE_EQUALS S(KC_0)
#define EE_UNDERSCORE S(KC_SLSH)
#define EE_DOUBLE_QUOTE S(KC_2)
#define EE_SINGLE_QUOTE KC_BSLS
#define EE_PIPE RALT(KC_NUBS)
#define EE_MINUS KC_SLSH
#define EE_PLUS KC_MINS
#define EE_ROOF RALT(KC_QUOT)
#define EE_BACKTICK S(KC_EQL)
#define EE_HASHTAG S(KC_3)
#define EE_QUESTION_MARK S(KC_MINS)
#define EE_SEMI_COLON S(KC_COMM)
#define EE_COLON S(KC_DOT)
#define EE_EXCLAMATION_MARK S(KC_1)
#define EE_ASTERISK S(KC_BSLS)
#define EE_BACKSLASH RALT(KC_MINS)
#define EE_FORWARDSLASH S(KC_7)
#define EE_COMMERCIAL_AT RALT(KC_2)
#define EE_PERCENT S(KC_5)
#define EE_TILDE S(KC_GRAVE)
#define EE_CARON KC_GRAVE


//Shorthands
#define EE_LABR EE_LEFT_ANGLE_BRACKET
#define EE_RABR EE_RIGHT_ANGLE_BRACKET
#define EE_LCBR EE_LEFT_CURLY_BRACKET
#define EE_RCBR EE_RIGHT_CURLY_BRACKET
#define EE_LSBR EE_LEFT_SQUARE_BRACKET
#define EE_RSBR EE_RIGHT_SQUARE_BRACKET
#define EE_LBRC EE_LEFT_BRACKET
#define EE_RBRC EE_RIGHT_BRACKET

#define EE_SCLN EE_SEMI_COLON
#define EE_COLN EE_COLON
#define EE_USCR EE_UNDERSCORE
#define EE_QSTN EE_QUESTION_MARK
#define EE_BKTK EE_BACKTICK
#define EE_HSTG EE_HASHTAG
#define EE_EQLS EE_EQUALS
#define EE_AMPR EE_AMPERSAND
#define EE_MINS EE_MINUS
#define EE_DOLR EE_DOLLAR
#define EE_EXCL EE_EXCLAMATION_MARK
#define EE_ASTR EE_ASTERISK
#define EE_BSLS EE_BACKSLASH
#define EE_SLSH EE_FORWARDSLASH
#define EE_DBQT EE_DOUBLE_QUOTE
#define EE_SIQT EE_SINGLE_QUOTE
#define EE_ATSI EE_COMMERCIAL_AT
#define EE_PRCT EE_PERCENT
#define EE_TLDE EE_TILDE
#define EE_CARO EE_CARON


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT_preonic_2x2u(
  KC_ESC  ,   KC_1  ,  KC_2   ,  KC_3   ,   KC_4  ,  KC_5   ,   KC_6  ,  KC_7   ,   KC_8  ,   KC_9  ,   KC_0  , KC_BSPC ,
  KC_TAB  ,   KC_Q  ,  KC_W   ,  KC_E   ,   KC_R  ,  KC_T   ,   KC_Y  ,  KC_U   ,   KC_I  ,   KC_O  ,   KC_P  , KC_DEL  ,
  KC_F13  ,   KC_A  ,  KC_S   ,  KC_D   ,   KC_F  ,  KC_G   ,   KC_H  ,  KC_J   ,   KC_K  ,   KC_L  ,   EE_Ö  ,  EE_Ä   ,
  KC_LSFT ,   KC_Z  ,  KC_X   ,  KC_C   ,   KC_V  ,  KC_B   ,   KC_N  ,  KC_M   , KC_COMM , KC_DOT  , EE_DASH , KC_LSFT ,
  KC_LCTL , KC_LGUI , KC_LALT , ALT_ENT , LT(_LOWER,KC_SPC) , LT(_RAISE,KC_SPC) , KC_LEFT , KC_DOWN , KC_UP   , KC_RGHT
),

[_GAMING] = LAYOUT_preonic_2x2u(
  KC_ESC  ,   KC_1  ,  KC_2   ,       KC_3        , KC_4 , KC_5 ,    KC_6  ,  KC_7   , KC_8    ,  KC_9   , KC_0    , KC_BSPC ,
  KC_TAB  ,   KC_Q  ,  KC_W   ,       KC_E        , KC_R , KC_T ,    KC_Y  ,  KC_U   , KC_I    ,  KC_O   , KC_P    , KC_DEL  ,
  KC_F13  ,   KC_A  ,  KC_S   ,       KC_D        , KC_F , KC_G ,    KC_H  ,  KC_J   , KC_K    ,  KC_L   , EE_Ö    , KC_QUOT ,
  KC_LSFT ,   KC_Z  ,  KC_X   ,       KC_C        , KC_V , KC_B ,    KC_N  ,  KC_M   , KC_COMM , KC_DOT  , EE_DASH , KC_LSFT ,
  KC_LCTL , KC_LGUI , KC_LALT , LT(_LOWER,KC_ENT) ,    KC_SPC   ,  LT(_RAISE,KC_SPC) , _______ , _______ , _______ , _______
),

[_LOWER] = LAYOUT_preonic_2x2u(
  KC_GRV  ,  KC_F1  ,  KC_F2  ,   KC_F3  ,    KC_F4  , KC_F5,   KC_F6   ,   KC_F7 ,   KC_F8 ,   KC_F9 ,  KC_F10 , _______ ,
  _______ , _______ , _______ , _______  ,  _______  , _______, KC_PGUP , KC_HOME , _______ ,  KC_END , _______ , _______ ,
  KC_CAPS , KC_LGUI , KC_LALT , KC_LCTRL , KC_LSHIFT , _______, KC_LEFT , KC_DOWN ,  KC_UP  , KC_RGHT , EE_Õ    , _______ ,
  _______ , _______ , _______ , _______  ,  _______  , _______, KC_PGDN , KC_INS  , _______ , _______ , EE_Ü    , _______ ,
  _______ , _______ , _______ , _______  ,        _______     ,       _______     , _______ , _______ , _______ , KC_PSCR
),

[_RAISE] = LAYOUT_preonic_2x2u(
  TO(_QWERTY), TO(_GAMING) , _______ , _______ , _______ , _______ , _______  , _______  , _______  , _______  , _______  , _______ ,
  _______    ,   EE_PRCT   , EE_BKTK , EE_LSBR , EE_LABR , EE_SLSH , EE_BSLS  , EE_RABR  , EE_RSBR  , EE_AMPR  , EE_EURO  , _______ ,
  _______    ,   EE_PIPE   , EE_DBQT , EE_USCR , EE_LBRC , EE_LCBR , EE_RCBR  , EE_RBRC  , EE_EQLS  , EE_SIQT  , EE_DOLR  , EE_PLUS ,
  _______    ,   EE_CARO   , EE_ROOF , EE_TLDE , EE_EXCL , EE_ATSI , EE_HSTG  , EE_QSTN  , EE_SCLN  , EE_COLN  , EE_USCR  , _______ ,
  _______    ,   _______   , _______ , _______ ,      _______      ,       _______       , _______  , _______  , _______  , KC_PSCR
)
};

