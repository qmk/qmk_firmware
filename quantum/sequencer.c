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
    false,   // enabled
    {false}  // steps
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
