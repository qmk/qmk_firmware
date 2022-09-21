#include QMK_KEYBOARD_H
#include "losinggeneration-config.h"
#include "losinggeneration-keymap.h"

extern keymap_config_t keymap_config;

#define MT_CAPS LSFT_T(KC_CAPS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY]  = CATMAP( QWERTY_LAYER  ),
[_COLEMAK] = CATMAP( COLEMAK_LAYER ),
[_WORKMAN] = CATMAP( WORKMAN_LAYER ),
[_DVORAK]  = CATMAP( DVORAK_LAYER  ),
[_GAME]    = CATMAP( GAME_LAYER    ),
[_NUMPAD]  = CATMAP( NUMPAD_LAYER  ),
[_MOUSE]   = CATMAP( MOUSE_LAYER   ),
[_LOWER]   = CATMAP( LOWER_LAYER   ),
[_RAISE]   = CATMAP( RAISE_LAYER   ),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |      | QK_BOOT| Game |Numpad|Mouse |      |Sleep |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F5  |  F6  |  F7  |  F8  |      |      |Qwerty|Colmak|Workmn|Dvorak|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | CAPS |  F9  |  F10 |  F11 |  F12 |      |      |      |      |      |  Up  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | XXX  | Left | Down |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = CATMAP( \
  _______, KC_F1  ,  KC_F2 , KC_F3  , KC_F4  , _______, QK_BOOT, TO_GAME, TO_NUM , TO_MS  , _______, KC_SLEP, \
  _______, KC_F5  ,  KC_F6 , KC_F7  , KC_F8  , _______, _______, QWERTY , COLEMAK, WORKMAN, DVORAK , _______, \
  MT_CAPS, KC_F9  ,  KC_F10, KC_F11 , KC_F12 , _______, _______, _______, _______, _______, KC_UP  , _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT  \
)

};

