/* Copyright 2021 @nstickney
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "nstickney.h"

// Tap Dancing
void dance_layer(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            tap_code(KC_APP);
            break;
        case 2:
            layer_invert(NUMP);
            break;
        case 3:
            layer_invert(SYMB);
            break;
        default:
            break;
    }
};

void dance_lock_finished(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            register_code(KC_LGUI);
            break;
        case 2:
            register_code(KC_NLCK);
            break;
        case 3:
            register_code(KC_CAPS);
            break;
        case 4:
            register_code(KC_SLCK);
            break;
        default:
            break;
    }
};

void dance_lock_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            unregister_code(KC_LGUI);
            break;
        case 2:
            register_code(KC_NLCK);
            break;
        case 3:
            register_code(KC_CAPS);
            break;
        case 4:
            register_code(KC_SLCK);
            break;
        default:
            break;
    }
};

qk_tap_dance_action_t tap_dance_actions[] = {
	[LOCKS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_lock_finished, dance_lock_reset),
	[LAYERS] = ACTION_TAP_DANCE_FN(dance_layer)
};

// RGB underglow per-layer hue values
const uint16_t LAYER_HUE[] = {6, 197, 133, 69};

// Initialize RGB underglow (colorful)
void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    for (uint16_t i = 0; i < 256; ++i) {
        rgblight_sethsv_noeeprom((i + LAYER_HUE[BASE]) % 256, 255, 136);
        wait_ms(8);
    }
};

// Turn on RGB underglow according to active layer
layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t user_val = rgblight_get_val();
    rgblight_sethsv_noeeprom(LAYER_HUE[get_highest_layer(state)], 255, user_val);
    return state;
};
