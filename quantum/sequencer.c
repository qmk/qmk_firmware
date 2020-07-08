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

sequencer_config_t sequencer_config = {false};

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
