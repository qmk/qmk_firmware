/* Protokeeb Copyright 2024 A-Tech Officials (@atechofficials)
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program. 
 * If not, see <https://www.gnu.org/licenses/gpl-3.0.html>.
 */

/* Protokeeb v1.0
 * Keymap: Default ortho 4x4
 */

#include QMK_KEYBOARD_H
#include "os_detection.h"
#include "quantum.h"

enum protokeeb_keymap_layers {
    LAYER_BASE = 0,
    LAYER_LOWER = 1,
		LAYER_RAISE = 2,
		LAYER_ADJUST = 3,
};

#define LOWER LT(LAYER_LOWER, KC_KP_0)
#define RAISE LT(LAYER_RAISE, KC_KP_ENTER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[LAYER_BASE] = LAYOUT_ortho_4x4( /* Base */ 
			KC_KP_7, KC_KP_8, KC_KP_9, KC_KP_SLASH,
			KC_KP_4, KC_KP_5, KC_KP_6, KC_KP_ASTERISK,
			KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_MINUS,
			LOWER, KC_KP_DOT, RAISE, KC_KP_PLUS
	),

	[LAYER_LOWER] = LAYOUT_ortho_4x4( /* RGB Control */
			RGB_MODE_PLAIN, RGB_MODE_FORWARD, RGB_MODE_REVERSE, RGB_TOG,
			RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD,
			RGB_VAI, RGB_VAD, RGB_SPI, RGB_SPD,
			KC_TRNS, RGB_MODE_SWIRL, KC_TRNS, QK_BOOT
	),

	[LAYER_RAISE] = LAYOUT_ortho_4x4( /* Raise */
  		KC_F1, KC_F2, KC_F3, KC_F4,
  		KC_F5, KC_F6, KC_F7, KC_F8,
  		KC_F9, KC_F10, KC_F11, KC_F12,
  		QK_REBOOT, QK_DEBUG_TOGGLE, KC_TRNS, QK_AUDIO_TOGGLE
  ),
    
  [LAYER_ADJUST] = LAYOUT_ortho_4x4( /* Adjust */
  		KC_MEDIA_PLAY_PAUSE, KC_MEDIA_PREV_TRACK, KC_MEDIA_NEXT_TRACK, KC_MEDIA_STOP,
  		KC_CALCULATOR, KC_MY_COMPUTER, KC_CONTROL_PANEL, KC_SYSTEM_POWER,
  		KC_NO, KC_NO, KC_NO, KC_NO,
  		KC_TRNS, KC_NO, KC_TRNS, KC_NO
  ),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [LAYER_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [LAYER_LOWER] = { ENCODER_CCW_CW(RGB_HUD, RGB_HUI) },
		[LAYER_RAISE] = { ENCODER_CCW_CW(KC_BRIGHTNESS_DOWN, KC_BRIGHTNESS_UP) },
    [LAYER_ADJUST] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
};
#endif

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, LAYER_LOWER, LAYER_RAISE, LAYER_ADJUST);
}
