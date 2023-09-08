/* Copyright 2020 Rodolphe Belouin
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

#include "process_sequencer.h"

bool process_sequencer(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case QK_SEQUENCER_ON:
                sequencer_on();
                return false;
            case QK_SEQUENCER_OFF:
                sequencer_off();
                return false;
            case QK_SEQUENCER_TOGGLE:
                sequencer_toggle();
                return false;
            case QK_SEQUENCER_TEMPO_DOWN:
                sequencer_decrease_tempo();
                return false;
            case QK_SEQUENCER_TEMPO_UP:
                sequencer_increase_tempo();
                return false;
            case QK_SEQUENCER_RESOLUTION_DOWN:
                sequencer_decrease_resolution();
                return false;
            case QK_SEQUENCER_RESOLUTION_UP:
                sequencer_increase_resolution();
                return false;
            case QK_SEQUENCER_STEPS_ALL:
                sequencer_set_all_steps_on();
                return false;
            case QK_SEQUENCER_STEPS_CLEAR:
                sequencer_set_all_steps_off();
                return false;
            case SEQUENCER_STEP_MIN ... SEQUENCER_STEP_MAX:
                sequencer_toggle_step(keycode - SEQUENCER_STEP_MIN);
                return false;
            case SEQUENCER_RESOLUTION_MIN ... SEQUENCER_RESOLUTION_MAX:
                sequencer_set_resolution(keycode - SEQUENCER_RESOLUTION_MIN);
                return false;
            case SEQUENCER_TRACK_MIN ... SEQUENCER_TRACK_MAX:
                sequencer_toggle_single_active_track(keycode - SEQUENCER_TRACK_MIN);
                return false;
        }
    }

    return true;
}
