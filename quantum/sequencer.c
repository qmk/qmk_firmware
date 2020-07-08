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

sequencer_config_t sequencer_config = {
    false,     // enabled
    {false},   // steps
    60,        // tempo
    SQ_RES_4,  // resolution
};

bool is_sequencer_on(void) { return sequencer_config.enabled; }

void sequencer_on(void) {
    dprintln("sequencer on");
    sequencer_config.enabled = true;
}

void sequencer_off(void) {
    dprintln("sequencer off");
    sequencer_config.enabled = false;
}

void sequencer_toggle(void) {
    if (is_sequencer_on()) {
        sequencer_off();
    } else {
        sequencer_on();
    }
}

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
