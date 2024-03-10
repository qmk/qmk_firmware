#include "quantum.h"
#include "keymap_estonian.h"
#include "sendstring_estonian.h"
#include QMK_KEYBOARD_H

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

enum my_keycodes {
    MY_BKTK = SAFE_RANGE,
    MY_CARN,
    MY_TILD,
};


#define ALT_ENT  MT(MOD_LALT, KC_ENT)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT_preonic_2x2u(
  KC_ESC  ,   KC_1  ,  KC_2   ,  KC_3   ,   KC_4  ,  KC_5   ,   KC_6  ,  KC_7   ,   KC_8  ,   KC_9  ,   KC_0  , KC_BSPC ,
  KC_TAB  ,   KC_Q  ,  KC_W   ,  KC_E   ,   KC_R  ,  KC_T   ,   KC_Y  ,  KC_U   ,   KC_I  ,   KC_O  ,   KC_P  , KC_DEL  ,
  KC_F13  ,   KC_A  ,  KC_S   ,  KC_D   ,   KC_F  ,  KC_G   ,   KC_H  ,  KC_J   ,   KC_K  ,   KC_L  , EE_ODIA , EE_ADIA ,
  KC_LSFT ,   KC_Z  ,  KC_X   ,  KC_C   ,   KC_V  ,  KC_B   ,   KC_N  ,  KC_M   , KC_COMM , KC_DOT  , EE_MINS , KC_LSFT ,
  KC_LCTL , KC_LGUI , KC_LALT , ALT_ENT , LT(_LOWER,KC_SPC) , LT(_RAISE,KC_SPC) , KC_LEFT , KC_DOWN , KC_UP   , KC_RGHT
),

[_GAMING] = LAYOUT_preonic_2x2u(
  KC_ESC  ,   KC_1  ,  KC_2   ,       KC_3        , KC_4 , KC_5 ,    KC_6  ,  KC_7   , KC_8    ,  KC_9   , KC_0    , KC_BSPC ,
  KC_TAB  ,   KC_Q  ,  KC_W   ,       KC_E        , KC_R , KC_T ,    KC_Y  ,  KC_U   , KC_I    ,  KC_O   , KC_P    , KC_DEL  ,
  KC_F13  ,   KC_A  ,  KC_S   ,       KC_D        , KC_F , KC_G ,    KC_H  ,  KC_J   , KC_K    ,  KC_L   , EE_ODIA , KC_QUOT ,
  KC_LSFT ,   KC_Z  ,  KC_X   ,       KC_C        , KC_V , KC_B ,    KC_N  ,  KC_M   , KC_COMM , KC_DOT  , EE_MINS , KC_LSFT ,
  KC_LCTL , KC_LGUI , KC_LALT , LT(_LOWER,KC_ENT) ,    KC_SPC   ,  LT(_RAISE,KC_SPC) , _______ , _______ , _______ , _______
),

[_LOWER] = LAYOUT_preonic_2x2u(
  KC_GRV  ,  KC_F1  ,  KC_F2  ,   KC_F3  ,   KC_F4  , KC_F5,   KC_F6   ,   KC_F7 ,   KC_F8 ,   KC_F9 ,  KC_F10 , _______ ,
  _______ , _______ , _______ , _______  , _______  , _______, KC_PGUP , KC_HOME , _______ ,  KC_END , _______ , _______ ,
  KC_CAPS , KC_LGUI , KC_LALT , KC_LCTL  , KC_LSFT  , _______, KC_LEFT , KC_DOWN ,  KC_UP  , KC_RGHT , EE_OTIL , _______ ,
  _______ , _______ , _______ , _______  , _______  , _______, KC_PGDN , KC_INS  , _______ , _______ , EE_UDIA , _______ ,
  _______ , _______ , _______ , _______  ,       _______     ,       _______     , _______ , _______ , _______ , KC_PSCR
),

[_RAISE] = LAYOUT_preonic_2x2u(
  TO(_QWERTY), TO(_GAMING) , _______ , _______ , _______ , _______ , _______  , _______  , _______  , _______  , _______  , _______ ,
  _______    ,   EE_PERC   , MY_BKTK , EE_LBRC , EE_LABK , EE_SLSH , EE_BSLS  , EE_RABK  , EE_RBRC  , EE_AMPR  , EE_EURO  , _______ ,
  _______    ,   EE_PIPE   , EE_DQUO , EE_ASTR , EE_LPRN , EE_LCBR , EE_RCBR  , EE_RPRN  , EE_EQL   , EE_QUOT  , EE_DLR   , EE_PLUS ,
  _______    ,   MY_CARN   , EE_CIRC , MY_TILD , EE_EXLM , EE_AT   , EE_HASH  , EE_QUES  , EE_SCLN  , EE_COLN  , EE_UNDS  , _______ ,
  _______    ,   _______   , _______ , _______ ,      _______      ,       _______       , _______  , _______  , _______  , KC_PSCR
)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MY_BKTK:
            if (record->event.pressed) {
                send_string("`");
                return false;
            }
        case MY_CARN:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_GRV)SS_TAP(X_GRV));
                return false;
            }
        case MY_TILD:
            if (record->event.pressed) {
                SEND_STRING(SS_LSFT(SS_TAP(X_GRV)SS_TAP(X_GRV)));
                return false;
            }
        default:
            return true;
    }
}
