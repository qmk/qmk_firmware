/* Copyright 2021 Batuhan Başerdem
 * <baserdem.batuhan@gmail.com> @bbaserdem
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


#include "bb-audio.h"
/* AUDIO
 * This contains some audio related stuff.
 * There is no need to wrap this up with preprocessor commands;
 * This is only called if audio is enabled
 */

float tone_game_intro[][2] = GAME_ON_SONG;
float tone_game_outro[][2] = GAME_OFF_SONG;

// Audio playing when layer changes
layer_state_t layer_state_set_audio(layer_state_t state) {
    // Get this layer
    static bool prev_game = false;

    // If entering the game layer; play the intro sound
    if (layer_state_cmp(state, _GAME) && (!prev_game)) {
        stop_all_notes();
        PLAY_SONG(tone_game_intro);
        prev_game = true;
    }
    // If exiting the game layer; play the outro sound
    if ((!layer_state_cmp(state, _GAME)) && prev_game) {
        stop_all_notes();
        PLAY_SONG(tone_game_outro);
        prev_game = false;
    }
    return state;
}

// Audio layer switch; add the music layer on top of this
bool process_record_audio(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MU_TOG:
            if (!record->event.pressed) {
                // On release, exit music mode if enabled
                if (layer_state_is(_MUSI)) {
                    layer_off(_MUSI);
                // If not enabled; turn off all layers and load music layer
                } else {
                    layer_clear();
                    layer_on(_MUSI);
                }
            }
            return true;
            break;
        case MU_ON:
            if (!record->event.pressed) {
                // On release, enter music mode
                layer_clear();
                layer_on(_MUSI);
            }
            return true;
            break;
        case MU_OFF:
            if (!record->event.pressed) {
                // On release, exit music mode
                layer_off(_MUSI);
            }
            return true;
            break;
    }
    return true;
}
