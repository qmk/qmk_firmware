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

sequencer_config_t sequencer_config = {
    false,     // enabled
    {false},   // steps
    60,        // tempo
    SQ_RES_4,  // resolution
};

uint8_t  sequencer_active_tracks = 0;
uint8_t  sequencer_current_step  = 0;
uint16_t sequencer_timer         = 0;

/**
 * Because Digital Audio Workstations get overwhelmed when too many MIDI signals are sent concurrently,
 * We use a "phase" state machine to delay some of the events.
 */
enum sequencer_phase_t {
    SEQUENCER_PHASE_ATTACK,   // t=0ms, send the MIDI note on signal
    SEQUENCER_PHASE_RELEASE,  // t=SEQUENCER_PHASE_RELEASE_TIMEOUT ms, send the MIDI note off signal
    SEQUENCER_PHASE_PAUSE     // t=step duration ms, loop
};

uint8_t sequencer_phase = SEQUENCER_PHASE_ATTACK;

bool is_sequencer_on(void) { return sequencer_config.enabled; }

void sequencer_on(void) {
    dprintln("sequencer on");
    sequencer_config.enabled = true;
    sequencer_current_step   = 0;
    sequencer_timer          = timer_read();
    sequencer_phase          = SEQUENCER_PHASE_ATTACK;
}

void sequencer_off(void) {
    dprintln("sequencer off");
    sequencer_config.enabled = false;
    sequencer_current_step   = 0;
}

void sequencer_toggle(void) {
    if (is_sequencer_on()) {
        sequencer_off();
    } else {
        sequencer_on();
    }
}

bool is_sequencer_track_active(uint8_t track) { return (sequencer_active_tracks >> track) & true; }

void sequencer_set_track_activation(uint8_t track, bool value) {
    if (value) {
        sequencer_active_tracks |= (1 << track);
    } else {
        sequencer_active_tracks &= ~(1 << track);
    }
    dprintf("sequencer: track %d is %s\n", track, value ? "active" : "inactive");
}

void sequencer_toggle_track_activation(uint8_t track) { sequencer_set_track_activation(track, !is_sequencer_track_active(track)); }

bool is_sequencer_step_on(uint8_t step) { return step < SEQUENCER_STEPS && sequencer_config.steps[step]; }

void sequencer_set_step(uint8_t step, bool value) {
    if (step < SEQUENCER_STEPS) {
        sequencer_config.steps[step] = value;
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
        sequencer_config.steps[step] = value;
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

uint8_t sequencer_get_current_step(void) { return sequencer_current_step; }

void sequencer_phase_attack(void) {
    dprintf("sequencer: step %d\n", sequencer_current_step);
#ifdef MIDI_ENABLE
    if (is_sequencer_step_on(sequencer_current_step)) {
        // Drum kick
        process_midi_basic_noteon(36);
    }
#endif
    sequencer_timer = timer_read();
    sequencer_phase = SEQUENCER_PHASE_RELEASE;
}

void sequencer_phase_release(void) {
#ifdef MIDI_ENABLE
    if (is_sequencer_step_on(sequencer_current_step)) {
        // Drum kick
        process_midi_basic_noteoff(36);
    }
#endif
    sequencer_phase = SEQUENCER_PHASE_PAUSE;
}

void sequencer_phase_pause(void) {
    sequencer_current_step = (sequencer_current_step + 1) % SEQUENCER_STEPS;
    sequencer_phase        = SEQUENCER_PHASE_ATTACK;
}

void matrix_scan_sequencer(void) {
    if (!sequencer_config.enabled) {
        return;
    }

    if (sequencer_phase == SEQUENCER_PHASE_PAUSE && timer_elapsed(sequencer_timer) > sequencer_get_step_duration()) {
        sequencer_phase_pause();
    }

    if (sequencer_phase == SEQUENCER_PHASE_RELEASE && timer_elapsed(sequencer_timer) > SEQUENCER_PHASE_RELEASE_TIMEOUT) {
        sequencer_phase_release();
    }

    if (sequencer_phase == SEQUENCER_PHASE_ATTACK) {
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
