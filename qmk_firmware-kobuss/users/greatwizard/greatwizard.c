/* Copyright 2020 Guillaume Gérard
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
#include "greatwizard.h"

void eeconfig_init_user(void) {
    user_config_t user_config;
    user_config.raw              = 0;
#ifdef RGBLIGHT_ENABLE
    user_config.rgb_layer_change = true;
#endif
    eeconfig_update_user(user_config.raw);
    keyboard_init();
}

void keyboard_post_init_user(void) {
#ifdef RGBLIGHT_ENABLE
    keyboard_post_init_rgb();
#endif
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef RGBLIGHT_ENABLE
    process_record_rgb(keycode, record);
#endif
#ifdef LAYER_GAME
    process_record_game(keycode, record);
#endif
#ifdef LAYER_GIT
    process_record_git(keycode, record);
#endif
#ifdef LAYERS_PROGRAMMER
    process_record_pg(keycode, record);
#endif
    switch (keycode) {
        case QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
        case WORKMAN:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_WORKMAN);
            }
            return false;
        case COLEMAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAK);
            }
            return false;
        case DVORAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_DVORAK);
            }
            return false;
    }
    return true;
}

#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise) {
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
#ifdef LAYERS_PROGRAMMER
        case _PROGRAMMER_SHIFTED:
#endif
            if (clockwise) {
                tap_code(KC_AUDIO_VOL_UP);
            } else {
                tap_code(KC_AUDIO_VOL_DOWN);
            }
            break;
        default:
            if (clockwise) {
                tap_code(KC_MEDIA_NEXT_TRACK);
            } else {
                tap_code(KC_MEDIA_PREV_TRACK);
            }
            break;
    }
}
#endif

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _RAISE, _LOWER, _ADJUST);
#ifdef RGBLIGHT_ENABLE
    state = layer_state_set_rgb(state);
#endif
#ifdef LAYERS_ORTHO
    state = layer_state_set_ortho(state);
#endif
    return state;
}

bool led_update_user(led_t led_state) {
#ifdef RGBLIGHT_ENABLE
    led_update_rgb(led_state);
#endif
    return true;
}
