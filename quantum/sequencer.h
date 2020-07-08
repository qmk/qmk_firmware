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
#include "debug.h"

// Maximum number of steps: 256
#ifndef SEQUENCER_STEPS
#    define SEQUENCER_STEPS 16
#endif

typedef struct {
    bool enabled;
    bool steps[SEQUENCER_STEPS];
} sequencer_config_t;

extern sequencer_config_t sequencer_config;

bool is_sequencer_on(void);
void sequencer_toggle(void);
void sequencer_on(void);
void sequencer_off(void);

bool is_sequencer_step_on(uint8_t step);
void sequencer_set_step(uint8_t step, bool value);
void sequencer_toggle_step(uint8_t step);
void sequencer_set_all_steps(bool value);

#define sequencer_set_step_on(step) sequencer_set_step(step, true)
#define sequencer_set_step_off(step) sequencer_set_step(step, false)
#define sequencer_set_all_steps_on() sequencer_set_all_steps(true)
#define sequencer_set_all_steps_off() sequencer_set_all_steps(false)
