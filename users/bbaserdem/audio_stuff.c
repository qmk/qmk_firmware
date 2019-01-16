/*
Copyright 2019 Batuhan Başerdem <baserdem.batuhan@gmail.com> @bbaserdem
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "audio_stuff.h"
#include "audio.h"

float tone_game[][2]    = SONG(ZELDA_PUZZLE);
float tone_return[][2]  = SONG(ZELDA_TREASURE);

// Audio playing when layer changes
uint32_t layer_state_set_audio(uint32_t state) {

    uint8_t current_layer = biton32( state );

    if ( userspace_config.game_flag && ( current_layer != _GA ) ) {
        stop_all_notes();
        PLAY_SONG(tone_return);
        userspace_config.game_flag = false;
    } else if ( ( current_layer == _GA ) && ( !userspace_config.game_flag) ) {
        stop_all_notes();
        PLAY_SONG(tone_game);
        userspace_config.game_flag = true;
    }

    return state;
}

// Audio layer switch
bool process_record_audio(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {
        case MU_TOG:
            if (record->event.pressed) {
                // On press, turn off layer if active
                if ( biton32( layer_state ) == _SE ) {
                    layer_off(_SE);
                    layer_on(_MU);
                } else {
                    layer_off(_MU);
                }
            }
            return true;
            break;
    }
    return true;
}
