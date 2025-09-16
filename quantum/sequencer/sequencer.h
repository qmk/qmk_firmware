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

#pragma once

#include <stdbool.h>
#include <stdint.h>

// Maximum number of steps: 256
#ifndef SEQUENCER_STEPS
#    define SEQUENCER_STEPS 16
#endif

// Maximum number of tracks: 8
#ifndef SEQUENCER_TRACKS
#    define SEQUENCER_TRACKS 8
#endif

#ifndef SEQUENCER_TRACK_THROTTLE
#    define SEQUENCER_TRACK_THROTTLE 3
#endif

#ifndef SEQUENCER_PHASE_RELEASE_TIMEOUT
#    define SEQUENCER_PHASE_RELEASE_TIMEOUT 30
#endif

/**
 * Make sure that the items of this enumeration follow the powers of 2, separated by a ternary variant.
 * Check the implementation of `get_step_duration` for further explanation.
 */
typedef enum {
    SQ_RES_2, //
    SQ_RES_2T,
    SQ_RES_4,
    SQ_RES_4T,
    SQ_RES_8,
    SQ_RES_8T,
    SQ_RES_16,
    SQ_RES_16T,
    SQ_RES_32,
    SEQUENCER_RESOLUTIONS
} sequencer_resolution_t;

typedef struct {
    bool                   enabled;
    uint8_t                steps[SEQUENCER_STEPS];
    uint16_t               track_notes[SEQUENCER_TRACKS];
    uint8_t                tempo; // Is a maximum tempo of 255 reasonable?
    sequencer_resolution_t resolution;
} sequencer_config_t;

/**
 * Because Digital Audio Workstations get overwhelmed when too many MIDI signals are sent concurrently,
 * We use a "phase" state machine to delay some of the events.
 */
typedef enum sequencer_phase_t {
    SEQUENCER_PHASE_ATTACK,  // t=0ms, send the MIDI note on signal
    SEQUENCER_PHASE_RELEASE, // t=SEQUENCER_PHASE_RELEASE_TIMEOUT ms, send the MIDI note off signal
    SEQUENCER_PHASE_PAUSE    // t=step duration ms, loop
} sequencer_phase_t;

typedef struct {
    uint8_t           active_tracks;
    uint8_t           current_track;
    uint8_t           current_step;
    uint16_t          timer;
    sequencer_phase_t phase;
} sequencer_state_t;

extern sequencer_config_t sequencer_config;

// We expose the internal state to make the feature more "unit-testable"
extern sequencer_state_t sequencer_internal_state;

bool is_sequencer_on(void);
void sequencer_toggle(void);
void sequencer_on(void);
void sequencer_off(void);

void sequencer_set_track_notes(const uint16_t track_notes[SEQUENCER_TRACKS]);

bool is_sequencer_track_active(uint8_t track);
void sequencer_set_track_activation(uint8_t track, bool value);
void sequencer_toggle_track_activation(uint8_t track);
void sequencer_toggle_single_active_track(uint8_t track);

#define sequencer_activate_track(track) sequencer_set_track_activation(track, true)
#define sequencer_deactivate_track(track) sequencer_set_track_activation(track, false)

bool is_sequencer_step_on(uint8_t step);
bool is_sequencer_step_on_for_track(uint8_t step, uint8_t track);
void sequencer_set_step(uint8_t step, bool value);
void sequencer_toggle_step(uint8_t step);
void sequencer_set_all_steps(bool value);

#define sequencer_set_step_on(step) sequencer_set_step(step, true)
#define sequencer_set_step_off(step) sequencer_set_step(step, false)
#define sequencer_set_all_steps_on() sequencer_set_all_steps(true)
#define sequencer_set_all_steps_off() sequencer_set_all_steps(false)

uint8_t sequencer_get_tempo(void);
void    sequencer_set_tempo(uint8_t tempo);
void    sequencer_increase_tempo(void);
void    sequencer_decrease_tempo(void);

sequencer_resolution_t sequencer_get_resolution(void);
void                   sequencer_set_resolution(sequencer_resolution_t resolution);
void                   sequencer_increase_resolution(void);
void                   sequencer_decrease_resolution(void);

uint8_t sequencer_get_current_step(void);

uint16_t sequencer_get_beat_duration(void);
uint16_t sequencer_get_step_duration(void);

uint16_t get_beat_duration(uint8_t tempo);
uint16_t get_step_duration(uint8_t tempo, sequencer_resolution_t resolution);

void sequencer_task(void);
