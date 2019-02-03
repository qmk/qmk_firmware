//#include "jj40.h"
//#include "action_layer.h"
#include QMK_KEYBOARD_H

//layers
#define _QWERTY 0
#define _SYMBL  1
#define _NUMBS  2

//mod tap keys
#define SHFZ MT(MOD_LSFT, KC_Z)
#define SHFS MT(MOD_RSFT, KC_SLSH)

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  SYMBL,
  NUMBS,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] =
{
    /* Qwerty
    * ,-----------------------------------------------------------------------------------.
    * |   Q  |   W  |   E  |   R  |   T  |  [   |   ]  |   Y  |   U  |   I  |   O  |   P  |
    * |------+------+------+------+------+-------------+------+------+------+------+------|
    * |   A  |   S  |   D  |   F  |   G  |  (   |   )  |   H  |   J  |   K  |   L  |   ;  |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |   Z  |   X  |   C  |   V  |   B  |  {   |   }  |   N  |   M  |   ,  |   .  |   /  |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Ctrl |  OS  | alt  |numbs |Back  |Enter | Tab  |Space |symbl |vol_dn|vol_up| Esc  |
    * `----------------------------------------------------------------------------------'
    */
    [_QWERTY] = LAYOUT_ortho_4x12( \
    KC_Q      , KC_W   , KC_E  , KC_R       , KC_T   , KC_LBRC, KC_RBRC, KC_Y  , KC_U      , KC_I   , KC_O   , KC_P   , \
    KC_A      , KC_S   , KC_D  , KC_F       , KC_G   , KC_LPRN, KC_RPRN, KC_H  , KC_J      , KC_K   , KC_L   , KC_SCLN, \
    SHFZ      , KC_X   , KC_C  , KC_V       , KC_B   , KC_LCBR, KC_RCBR, KC_N  , KC_M      , KC_COMM, KC_DOT , SHFS   , \
    KC_LCTL   , KC_LGUI, KC_LALT, MO(_NUMBS), KC_BSPC, KC_ENT , KC_TAB , KC_SPC, MO(_SYMBL), KC_VOLD, KC_VOLU, KC_ESC   \
    ),

    /* Symbols
    * ,-----------------------------------------------------------------------------------.
    * |  ~   |   @  |   #  |   *  |      |      |      |      |      |      |      |      |
    * |------+------+------+------+------+-------------+------+------+------+------+------|
    * |  !   |   %  |   -  |   =  |   +  |   ^  |   $  |   |  |   &  |   `  |  '   |   "  |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |  \   |      |      |   _  |      |      |      |      |      |      |      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |      |      |      |      |      |      |      |
    * `-----------------------------------------------------------------------------------'
    */
    [_SYMBL] = LAYOUT_ortho_4x12( \
    KC_TILD, KC_AT  , KC_HASH, KC_ASTR, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
    KC_EXLM, KC_PERC, KC_MINS, KC_EQL , KC_PLUS, KC_CIRC, KC_DLR , KC_PIPE, KC_AMPR, KC_GRV , KC_QUOT, KC_DQUO, \
    KC_BSLS, KC_TRNS, KC_TRNS, KC_UNDS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS  \
    ),

    /* Numbers
    * ,-----------------------------------------------------------------------------------.
    * |  1   |  2   |  3   |  4   |  5   |      |      |  6   |  7   |  8   |  9   |  0   |
    * |------+------+------+------+------+-------------+------+------+------+------+------|
    * |      |      |      |      |      |      |      | left | down |  up  |right |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |shift |      |      |      |      |      |      |      |      |      |      |shift |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |RESET |      |      |      |      |      |      |      |      |      |      |      |
    * `-----------------------------------------------------------------------------------'
    */
    [_NUMBS] = LAYOUT_ortho_4x12( \
    KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_TRNS, KC_TRNS, KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , \
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_TRNS, \
    KC_LSFT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_RSFT, \
    RESET  , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS  \
    ),
};

// Loop
void matrix_scan_user(void) {
  // Empty
};
