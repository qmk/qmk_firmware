/* Copyright 2021 Mikael Manukyan <arm.localhost@gmail.com>
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

// To add a new functionality define a new state here and then assign
// the handler to the `encoder_callback`
#include "quantum.h"

enum encoder_state {
    ENCODER_VOLUME = 0,
    ENCODER_RGB_HUE,
    ENCODER_RGB_SAT,
    ENCODER_RGB_VAL,
    ENCODER_RGB_EFFECT_SPEED,
    ENCODER_RGB_EFFECT,
};

typedef void (*encoder_callback)(void);

#define ENCODER_DEFAULT ENCODER_VOLUME

void volume_up(void);
void volume_down(void);
