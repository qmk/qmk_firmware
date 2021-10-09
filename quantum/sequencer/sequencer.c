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

#include "sequencer.h"

#ifdef MIDI_ENABLE
#    include "process_midi.h"
#endif

#ifdef MIDI_MOCKED
#    include "tests/midi_mock.h"
#endif

sequencer_config_t sequencer_config = {
    false,     // enabled
    {false},   // steps
    {0},       // track notes
    60,        // tempo
    SQ_RES_4,  // resolution
};

sequencer_state_t sequencer_internal_state = {0, 0, 0, 0, SEQUENCER_PHASE_ATTACK};

bool is_sequencer_on(void) { return sequencer_config.enabled; }

void sequencer_on(void) {
    dprintln("sequencer on");
    sequencer_config.enabled               = true;
    sequencer_internal_state.current_track = 0;
    sequencer_internal_state.current_step  = 0;
    sequencer_internal_state.timer         = timer_read();
    sequencer_internal_state.phase         = SEQUENCER_PHASE_ATTACK;
}

void sequencer_off(void) {
    dprintln("sequencer off");
    sequencer_config.enabled              = false;
    sequencer_internal_state.current_step = 0;
}

void sequencer_toggle(void) {
    if (is_sequencer_on()) {
        sequencer_off();
    } else {
        sequencer_on();
    }
}

void sequencer_set_track_notes(const uint16_t track_notes[SEQUENCER_TRACKS]) {
    for (uint8_t i = 0; i < SEQUENCER_TRACKS; i++) {
        sequencer_config.track_notes[i] = track_notes[i];
    }
}

bool is_sequencer_track_active(uint8_t track) { return (sequencer_internal_state.active_tracks >> track) & true; }

void sequencer_set_track_activation(uint8_t track, bool value) {
    if (value) {
        sequencer_internal_state.active_tracks |= (1 << track);
    } else {
        sequencer_internal_state.active_tracks &= ~(1 << track);
    }
    dprintf("sequencer: track %d is %s\n", track, value ? "active" : "inactive");
}

void sequencer_toggle_track_activation(uint8_t track) { sequencer_set_track_activation(track, !is_sequencer_track_active(track)); }

void sequencer_toggle_single_active_track(uint8_t track) {
    if (is_sequencer_track_active(track)) {
        sequencer_internal_state.active_tracks = 0;
    } else {
        sequencer_internal_state.active_tracks = 1 << track;
    }
}

bool is_sequencer_step_on(uint8_t step) { return step < SEQUENCER_STEPS && (sequencer_config.steps[step] & sequencer_internal_state.active_tracks) > 0; }

bool is_sequencer_step_on_for_track(uint8_t step, uint8_t track) { return step < SEQUENCER_STEPS && (sequencer_config.steps[step] >> track) & true; }

void sequencer_set_step(uint8_t step, bool value) {
    if (step < SEQUENCER_STEPS) {
        if (value) {
            sequencer_config.steps[step] |= sequencer_internal_state.active_tracks;
        } else {
            sequencer_config.steps[step] &= ~sequencer_internal_state.active_tracks;
        }
        dprintf("sequencer: step %d is %s\n", step, value ? "on" : "off");
    } else {
        dprintf("sequencer: step %d is out of range\n", step);
    }
}

void sequencer_toggle_step(uint8_t step) {
    if (is_sequencer_step_on(step)) {
        sequencer_set_step_off(step);
    } else {
        sequencer_set_step_on(step);
    }
}

void sequencer_set_all_steps(bool value) {
    for (uint8_t step = 0; step < SEQUENCER_STEPS; step++) {
        if (value) {
            sequencer_config.steps[step] |= sequencer_internal_state.active_tracks;
        } else {
            sequencer_config.steps[step] &= ~sequencer_internal_state.active_tracks;
        }
    }
    dprintf("sequencer: all steps are %s\n", value ? "on" : "off");
}

uint8_t sequencer_get_tempo(void) { return sequencer_config.tempo; }

void sequencer_set_tempo(uint8_t tempo) {
    if (tempo > 0) {
        sequencer_config.tempo = tempo;
        dprintf("sequencer: tempo set to %d bpm\n", tempo);
    } else {
        dprintln("sequencer: cannot set tempo to 0");
    }
}

void sequencer_increase_tempo(void) {
    // Handling potential uint8_t overflow
    if (sequencer_config.tempo < UINT8_MAX) {
        sequencer_set_tempo(sequencer_config.tempo + 1);
    } else {
        dprintf("sequencer: cannot set tempo above %d\n", UINT8_MAX);
    }
}

void sequencer_decrease_tempo(void) { sequencer_set_tempo(sequencer_config.tempo - 1); }

sequencer_resolution_t sequencer_get_resolution(void) { return sequencer_config.resolution; }

void sequencer_set_resolution(sequencer_resolution_t resolution) {
    if (resolution >= 0 && resolution < SEQUENCER_RESOLUTIONS) {
        sequencer_config.resolution = resolution;
        dprintf("sequencer: resolution set to %d\n", resolution);
    } else {
        dprintf("sequencer: resolution %d is out of range\n", resolution);
    }
}

void sequencer_increase_resolution(void) { sequencer_set_resolution(sequencer_config.resolution + 1); }

void sequencer_decrease_resolution(void) { sequencer_set_resolution(sequencer_config.resolution - 1); }

uint8_t sequencer_get_current_step(void) { return sequencer_internal_state.current_step; }

void sequencer_phase_attack(void) {
    dprintf("sequencer: step %d\n", sequencer_internal_state.current_step);
    dprintf("sequencer: time %d\n", timer_read());

    if (sequencer_internal_state.current_track == 0) {
        sequencer_internal_state.timer = timer_read();
    }

    if (timer_elapsed(sequencer_internal_state.timer) < sequencer_internal_state.current_track * SEQUENCER_TRACK_THROTTLE) {
        return;
    }

#if defined(MIDI_ENABLE) || defined(MIDI_MOCKED)
    if (is_sequencer_step_on_for_track(sequencer_internal_state.current_step, sequencer_internal_state.current_track)) {
        process_midi_basic_noteon(midi_compute_note(sequencer_config.track_notes[sequencer_internal_state.current_track]));
    }
#endif

    if (sequencer_internal_state.current_track < SEQUENCER_TRACKS - 1) {
        sequencer_internal_state.current_track++;
    } else {
        sequencer_internal_state.phase = SEQUENCER_PHASE_RELEASE;
    }
}

void sequencer_phase_release(void) {
    if (timer_elapsed(sequencer_internal_state.timer) < SEQUENCER_PHASE_RELEASE_TIMEOUT + sequencer_internal_state.current_track * SEQUENCER_TRACK_THROTTLE) {
        return;
    }
#if defined(MIDI_ENABLE) || defined(MIDI_MOCKED)
    if (is_sequencer_step_on_for_track(sequencer_internal_state.current_step, sequencer_internal_state.current_track)) {
        process_midi_basic_noteoff(midi_compute_note(sequencer_config.track_notes[sequencer_internal_state.current_track]));
    }
#endif
    if (sequencer_internal_state.current_track > 0) {
        sequencer_internal_state.current_track--;
    } else {
        sequencer_internal_state.phase = SEQUENCER_PHASE_PAUSE;
    }
}

void sequencer_phase_pause(void) {
    if (timer_elapsed(sequencer_internal_state.timer) < sequencer_get_step_duration()) {
        return;
    }

    sequencer_internal_state.current_step = (sequencer_internal_state.current_step + 1) % SEQUENCER_STEPS;
    sequencer_internal_state.phase        = SEQUENCER_PHASE_ATTACK;
}

void sequencer_task(void) {
    if (!sequencer_config.enabled) {
        return;
    }

    if (sequencer_internal_state.phase == SEQUENCER_PHASE_PAUSE) {
        sequencer_phase_pause();
    }

    if (sequencer_internal_state.phase == SEQUENCER_PHASE_RELEASE) {
        sequencer_phase_release();
    }

    if (sequencer_internal_state.phase == SEQUENCER_PHASE_ATTACK) {
        sequencer_phase_attack();
    }
}

uint16_t sequencer_get_beat_duration(void) { return get_beat_duration(sequencer_config.tempo); }

uint16_t sequencer_get_step_duration(void) { return get_step_duration(sequencer_config.tempo, sequencer_config.resolution); }

uint16_t get_beat_duration(uint8_t tempo) {
    // Don’t crash in the unlikely case where the given tempo is 0
    if (tempo == 0) {
        return get_beat_duration(60);
    }

    /**
     * Given
     *  t = tempo and d = duration, both strictly greater than 0
     * When
     *  t beats / minute = 1 beat / d ms
     * Then
     *  t beats / 60000ms = 1 beat / d ms
     *  d ms = 60000ms / t
     */
    return 60000 / tempo;
}

uint16_t get_step_duration(uint8_t tempo, sequencer_resolution_t resolution) {
    /**
     * Resolution cheatsheet:
     * 1/2  => 2 steps per 4 beats
     * 1/2T => 3 steps per 4 beats
     * 1/4  => 4 steps per 4 beats
     * 1/4T => 6 steps per 4 beats
     * 1/8  => 8 steps per 4 beats
     * 1/8T => 12 steps per 4 beats
     * 1/16 => 16 steps per 4 beats
     * 1/16T => 24 steps per 4 beats
     * 1/32 => 32 steps per 4 beats
     *
     * The number of steps for binary resolutions follows the powers of 2.
     * The ternary variants are simply 1.5x faster.
     */
    bool     is_binary            = resolution % 2 == 0;
    uint8_t  binary_steps         = 2 << (resolution / 2);
    uint16_t binary_step_duration = get_beat_duration(tempo) * 4 / binary_steps;

    return is_binary ? binary_step_duration : 2 * binary_step_duration / 3;
}
