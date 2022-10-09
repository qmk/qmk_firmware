#include QMK_KEYBOARD_H
#include "losinggeneration-config.h"
#include "losinggeneration-keymap.h"

extern keymap_config_t keymap_config;

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
 * ,-----------------------------------------..-----------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |BL Off|| QK_BOOT| Game |Numpad|Mouse |      |Sleep |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * |      |  F5  |  F6  |  F7  |  F8  |BL Tg ||Aud on|Qwerty|Colmak|Workmn|Dvorak|      |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * | CAPS |  F9  |  F10 |  F11 |  F12 |BL On ||Audoff|      |      |      |  Up  |      |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * |      |      |      |      |      |      ||      |      | XXX  | Left | Down |Right |
 * `-----------------------------------------''-----------------------------------------'
 */
[_ADJUST] = CATMAP( \
  _______, KC_F1  ,  KC_F2 , KC_F3  , KC_F4  , BL_OFF , QK_BOOT, TO_GAME, TO_NUM , TO_MS  , _______, KC_SLEP, \
  _______, KC_F5  ,  KC_F6 , KC_F7  , KC_F8  , BL_TOGG, AU_ON  , QWERTY , COLEMAK, WORKMAN, DVORAK , _______, \
  KC_CAPS, KC_F9  ,  KC_F10, KC_F11 , KC_F12 , BL_ON  , AU_OFF , _______, _______, _______, KC_UP  , _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT  \
)

};

