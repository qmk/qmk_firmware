#include QMK_KEYBOARD_H
#include "keymap_bepo.h"

enum layers {
    _BEPO,
    _LOWER,
    _RAISE,
    _ADJUST,
};

#define TABLO LT(_LOWER, KC_TAB)
#define ENTRA LT(_RAISE, KC_ENTER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* BEPO
 *
 * ,----------------------------------.           ,----------------------------------.
 * |  B   |  W   |  P   |  O   |  ’   |           |  ^   |  V   |  D   |  L   |  J   |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  A   |  U   |  I   |  E   |  ,   |           |  C   |  T   |  S   |  R   |  N   |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * | Z/GUI| Y/Alt| X/Ctl| ./Sft|  K   |           |  M   | Q/Sft| G/Ctl| H/Alt| F/GUI|
 * `----------------------------------'           `----------------------------------'
 *                  ,------.------.------.    ,------,------.------.
 *                  | Del  |  Tab |      |    |      |Enter |Escape|
 *                  |      | LOWER| Space|    |BckSpc|RAISE |      |
 *                  `------'------|      |    |      |------'------'
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_BEPO] = LAYOUT(
          BP_B,        BP_W,        BP_P,          BP_O,  BP_APOS,         BP_DCRC, BP_V ,       BP_D,        BP_L,        BP_J,
          BP_A,        BP_U,        BP_I,          BP_E, BP_COMMA,         BP_C,    BP_T,        BP_S,        BP_R,        BP_N,
  LGUI_T(BP_Z), ALT_T(BP_Y), CTL_T(BP_X), SFT_T(BP_DOT),     BP_K,         BP_M,    SFT_T(BP_Q), CTL_T(BP_G), ALT_T(BP_H), LGUI_T(BP_F),
                                  KC_DEL,         TABLO,   KC_SPC,         KC_BSPC, ENTRA      , KC_ESC
),

/* Lower.
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   |  |   É  |   &  |   œ  |   È  |           | PgUp | Home |  Up  |  End |ScrlUp|
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   æ  |   Ù  |   ¨  |   €  |   $  |           | PgDn | Left | Down | Right|ScrlDn|
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   À  |  Alt |  Ctl | Shift|   Ç  |           |      | Shift|  Ctl |  Alt |      |
 * `----------------------------------'           `----------------------------------'
 *                  ,------,------,------.    ,------,------,------.
 *                  |      |      |      |    |      |      |      |
 *                  `------'------|      |    |      |------'------'
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_LOWER] = LAYOUT(
  ALGR(BP_B), BP_E_ACUTE, ALGR(BP_P), ALGR(BP_O), BP_E_GRAVE,        KC_PGUP,   KC_HOME, KC_UP,   KC_END,   KC_MS_WH_UP,
  ALGR(BP_A), ALGR(BP_U), ALGR(BP_I), ALGR(BP_E),  BP_DOLLAR,        KC_PGDOWN, KC_LEFT, KC_DOWN, KC_RIGHT, KC_MS_WH_DOWN,
     BP_AGRV,    KC_LALT,    KC_LCTL,    KC_LSFT,    BP_CCED,        _______,   KC_LSFT, KC_LCTL, KC_LALT,  _______,
                             _______,    _______,    _______,        _______,   _______, _______
),

/* Raise
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   "  |   <  |   >  |   (  |   )  |           |   @  |   +  |   -  |   /  |   *  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   `  |   {  |   }  |   [  |   ]  |           |   ~  |   =  |   %  |   \  |   #  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   |  |  Alt |  Ctl | Shift|   '  |           |      | Shift|  Ctl |  Alt |   &  |
 * `----------------------------------'           `----------------------------------'
 *                  ,------,------,------.    ,------,------,------.
 *                  |      |      |      |    |      |      |      |
 *                  `------'------|  _   |    |      |------'------'
 *                                |      |    |      |
 *                                `------'     `------'
 */
[_RAISE] = LAYOUT(
        BP_DQOT, ALGR(BP_LGIL), ALGR(BP_RGIL),       BP_LPRN,       BP_RPRN,        BP_AT,      BP_PLUS,    BP_MINUS,    BP_SLASH,         BP_ASTR,
  S(BP_PERCENT),    ALGR(BP_Y),    ALGR(BP_X), ALGR(BP_LPRN), ALGR(BP_RPRN),        ALGR(BP_K), BP_EQUAL,   BP_PERCENT,  ALGR(BP_A_GRAVE), S(BP_DOLLAR),
     ALGR(BP_B),       KC_LALT,       KC_LCTL,       KC_LSFT, ALGR(BP_COMM),        _______,    KC_LSFT,    KC_LCTL,     KC_LALT,          ALGR(BP_P),
                                      _______,       _______,  ALGR(KC_SPC),        _______,    _______,    _______
),

/* Adjust (Lower + Raise)
 * (GUI, ALT, Ctrl, Shft ONLY on left-hand home row)
 *
 * ,----------------------------------.           ,----------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |           |  F6  |  F7  |  F8  |  F9  |  F10 |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   1  |   2  |   3  |   4  |   5  |           |   6  |   7  |   8  |   9  |  0   |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  F11 |  Alt |  Ctl | Shift|      |           |      | Shift|  Ctl |  Alt |  F12 |
 * `----------------------------------'           `----------------------------------'
 *                  ,------,------,------.    ,------,------,------.
 *                  |      |      |      |    |      |      |      |
 *                  `------'------|      |    |      |------'------'
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_ADJUST] = LAYOUT(
  KC_F1,           KC_F2,      KC_F3,      KC_F4,      KC_F5,        KC_F6,    KC_F7,      KC_F8,       KC_F9,       KC_F10,
  S(BP_DQOT), S(BP_LGIL), S(BP_RGIL), S(BP_LPRN), S(BP_RPRN),        S(BP_AT), S(BP_PLUS), S(BP_MINUS), S(BP_SLASH), S(BP_ASTR),
  KC_F11,        KC_LALT,    KC_LCTL,    KC_LSFT,    _______,        _______,  KC_LSFT,    KC_LCTL,     KC_LALT,     KC_F12 ,
                             _______,    _______,    _______,        _______,  _______,    _______
)
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
