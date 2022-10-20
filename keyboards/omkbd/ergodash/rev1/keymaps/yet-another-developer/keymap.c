#include QMK_KEYBOARD_H
#include "yet-another-developer.h"

#ifndef UNICODE_ENABLE
#    define UC(x) KC_NO
#endif

extern keymap_config_t keymap_config;

#define EISU LALT(KC_GRV)

#define LAYOUT_ergodash_pretty_wrapper(...)   LAYOUT_ergodash_pretty(__VA_ARGS__)

    /* Keymap: BASE layer
     *
     * ,----------------------------------------------------.           ,----------------------------------------------------.
     * | ESC    |   1    |   2  |   3  |   4  |   5  |   [  |           |  ]   |   6  |   7  |   8  |   9  |   0    | Pscree |
     * |--------+--------+------+------+------+-------------|           |------+------+------+------+------+--------+--------|
     * | `      |   K01  |  K02 |  K03 |  K04 |  K05 |   -  |           |  =   |  K06 |  K07 |  K08 |  K09 |  K0A   |   \    |
     * |--------+--------+------+------+------+------|------|           |------|------+------+------+------+--------+--------|
     * | Tab    |   K11  |  K12 |  K13 |  K14 |  K15 |   {  |           |  }   |  K16 |  K17 |  K18 |  K19 |  K1A   |   "    |
     * |--------+--------+------+------+------+------|------'           `------|------+------+------+------+--------+--------|
     * | LShift |   K21  |  K22 |  K23 |  K24 |  K25 |                         |  K26 |  K27 |  K28 |  K29 |  K2A   | RShift |
     * |--------+--------+------+------+------+------'                         `------+------+------+------+--------+--------|
     * | LCtrl  |   GUI  |  Alt |  Alt |                                                     | LEFT | DOWN |   UP   | RIGHT  |
     * `-------------------------------'                                                     `-------------------------------'
     *                                       ,--------------.           ,--------------.
     *                                       | Lower|       |           |      | Raise |
     *                               ,-------|   /  |  Del  |           | Bksp +   /   +-------.
     *                               |CMD/Spc| Space|       |           |      | Enter |CMD/Spc|
     *                               `----------------------'           `----------------------'
     */
#define LAYOUT_ergodash_pretty_base( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A  \
  ) \
  LAYOUT_ergodash_pretty_wrapper( \
      KC_ESC,  ________________NUMBER_LEFT________________, KC_LBRC,                  KC_RBRC, ________________NUMBER_RIGHT_______________, KC_PSCR, \
      KC_GRV,  K01,     K02,     K03,     K04,     K05,     KC_MINS,                  KC_EQL,  K06,    K07,    K08,    K09,    K0A,         KC_BSLS, \
      KC_TAB,  K11,     K12,     K13,     K14,     K15,     KC_LCBR,                  KC_RCBR, K16,    K17,    K18,    K19,    K1A,         KC_QUOT, \
      OS_LSFT, K21,     K22,     K23,     K24,     K25,                                        K26,    K27,    K28,    K29,    K2A,         OS_RSFT, \
      KC_LCTL, KC_LGUI, KC_LALT, KC_LALT,                                                                    KC_LEFT, KC_DOWN, KC_UP,       KC_RIGHT, \
                                              LT(_LOWER, KC_SPC),                         LT(_RAISE, KC_ENT),                                        \
                                      OS_LGUI,LT(_LOWER, KC_SPC),KC_DEL,         KC_BSPC, LT(_RAISE, KC_ENT),  OS_RGUI                               \
    )

#define LAYOUT_ergodash_pretty_base_wrapper(...)       LAYOUT_ergodash_pretty_base(__VA_ARGS__)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_ergodash_pretty_base_wrapper(
    _________________QWERTY_L1_________________, _________________QWERTY_R1_________________,
    _________________QWERTY_L2_________________, _________________QWERTY_R2_________________,
    _________________QWERTY_L3_________________, _________________QWERTY_R3_________________
  ),

/* Keymap: COLEMAK layer
 *
 * ,----------------------------------------------------.           ,----------------------------------------------------.
 * | ESC    |   1    |   2  |   3  |   4  |   5  |   [  |           |  ]   |   6  |   7  |   8  |   9  |   0    |   -    |
 * |--------+--------+------+------+------+-------------|           |------+------+------+------+------+--------+--------|
 * | `      |    Q   |   W  |   F  |   P  |   G  |   -  |           |  =   |   J  |   L  |   U  |   Y  |   ;    |   \    |
 * |--------+--------+------+------+------+------|------|           |------|------+------+------+------+--------+--------|
 * | Tab    |    A   |   R  |   S  |   T  |   D  |  Del |           | Bksp |   H  |   N  |   E  |   I  |   O    |   '    |
 * |--------+--------+------+------+------+------|------'           `------|------+------+------+------+--------+--------|
 * | LShift |    Z   |   X  |   C  |   V  |   B  |                         |   K  |   M  |  , < |  . > |   /    | RShift |
 * |--------+--------+------+------+------+------'                         `------+------+------+------+--------+--------|
 * | Ctrl   |   GUI  |  Alt | EISU |                                                     | LEFT | DOWN |   UP   | RIGHT  |
 * `-------------------------------'                                                     `-------------------------------'
 *                                       ,--------------.           ,--------------.
 *                                       | Lower|       |           |      | Raise |
 *                               ,-------|   /  |  Del  |           | Bksp +   /   +-------.
 *                               |CMD/Spc| Space|       |           |      | Enter |CMD/Spc|
 *                               `----------------------'           `----------------------'
 */


// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
  [_COLEMAK] = LAYOUT_ergodash_pretty_base_wrapper(
    _________________COLEMAK_L1________________, _________________COLEMAK_R1________________,
    _________________COLEMAK_L2________________, _________________COLEMAK_R2________________,
    _________________COLEMAK_L3________________, _________________COLEMAK_R3________________
  ),

  [_DVORAK] = LAYOUT_ergodash_pretty_base_wrapper(
    _________________DVORAK_L1_________________, _________________DVORAK_R1_________________,
    _________________DVORAK_L2_________________, _________________DVORAK_R2_________________,
    _________________DVORAK_L3_________________, _________________DVORAK_R3_________________
  ),

  [_WORKMAN] = LAYOUT_ergodash_pretty_base_wrapper(
    _________________WORKMAN_L1________________, _________________WORKMAN_R1________________,
    _________________WORKMAN_L2________________, _________________WORKMAN_R2________________,
    _________________WORKMAN_L3________________, _________________WORKMAN_R3________________
  ),

#ifdef UNICODEMAP_ENABLE
  [_UNICODE] = LAYOUT_ergodash_pretty_base_wrapper(
    _______________UNICODE_L1__________________, _______________UNICODE_R1__________________,
    _______________UNICODE_L2__________________, _______________UNICODE_R2__________________,
    _______________UNICODE_L3__________________, _______________UNICODE_R3__________________
  ),
#endif

  [_LOWER] = LAYOUT_ergodash_pretty_wrapper(
    KC_F11,  _________________FUNC_LEFT_________________, KC_RST ,         KC_RST , _________________FUNC_RIGHT________________, KC_F12,
    KC_TILD, _________________LOWER_L1__________________, _______,         _______, _________________LOWER_R1__________________, KC_PIPE,
    _______, _________________LOWER_L2__________________, _______,         _______, _________________LOWER_R2__________________, KC_DQUO,
    _______, _________________LOWER_L3__________________,                           _________________LOWER_R3__________________, KC_PSCR,
    _______, _______, _______, _______,                                                               _______, _______, _______, KC_PAUS,
                                                _______,                            _______,
                                        _______, _______, _______,         _______, _______, _______
    ),

  [_RAISE] = LAYOUT_ergodash_pretty_wrapper(
    KC_F12,  _________________FUNC_LEFT_________________, KC_RST,          KC_RST , _________________FUNC_RIGHT________________, KC_F11,
    KC_GRV,  _________________RAISE_L1__________________, _______,         _______, _________________RAISE_R1__________________, KC_BSLS,
    _______, _________________RAISE_L2__________________, _______,         _______, _________________RAISE_R2__________________, KC_QUOT,
    _______, _________________RAISE_L3__________________,                           _________________RAISE_R3__________________, KC_PSCR,
    _______, _______, _______, _______,                                                               KC_HOME, KC_PGDN, KC_PGUP, KC_END,
                                                 _______,                           _______,
                                        _______, _______, _______,         _______, _______, _______
    ),

  [_ADJUST] = LAYOUT_ergodash_pretty_wrapper(
    KC_MAKE, _______, _______, _______, _______, _______, _______,         KC_NUKE, _______, _______, _______, _______, _______, KC_RST,
    VRSN,    _________________ADJUST_L1_________________, _______,         _______, _________________ADJUST_R1_________________, EE_CLR,
    _______, _________________ADJUST_L2_________________, _______,         _______, _________________ADJUST_R2_________________, _______,
    _______, _________________ADJUST_L3_________________,                           _________________ADJUST_R3_________________, _______,
    _______, _______, _______, _______,                                                               _______, _______, _______, _______,
                                                 _______,                           _______,
                                        _______, _______, _______,         _______, _______, _______
    ),
};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    return true;
}
void matrix_init_keymap(void) {
#ifdef STARTUP_RESET_EEPROM
    eeconfig_init();
#endif
}

//
