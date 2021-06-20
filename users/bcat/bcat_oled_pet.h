/* Copyright 2021 Jonathan Rascher
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

/* Common interface for an OLED pet (animated critter that reacts to typing).
 * Please link exactly one accompanying .c file to implement these functions.
 */

#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "led.h"

/* Opaque token identifying what animation state the pet is currently in. */
typedef uint8_t oled_pet_state_t;

/* The default animation state that every OLED pet must support. */
#define OLED_PET_IDLE 0

/* Returns the number of frames in the animation. Note that every state the pet
 * supports is expected to have the same number of frames.
 */
uint8_t oled_pet_num_frames(void);

/* Returns the number of bytes used to represent the animation frame (in
 * oled_write_raw_P format). Note that every state the pet supports is expected
 * to have the same frame size.
 */
uint16_t oled_pet_frame_bytes(void);

/* Returns the number of lines of the OLED occupied by the animation. Note that
 * every state the pet supports is expected to have the same frame size. The
 * returned value does not include the one line of padding that render_oled_pet
 * uses to account for "jumping".
 */
uint8_t oled_pet_frame_lines(void);

/* Returns whether or not the OLED pet should "jump" when the spacebar is
 * pressed. (The render_oled_pet implementation shifts the animation frame up
 * one line when this happens.)
 */
bool oled_pet_can_jump(void);

/* Returns the current state to be animated based on current keyboard state. */
oled_pet_state_t oled_pet_state(uint8_t mods, led_t leds, uint8_t wpm);

/* Returns the delay before the next animation frame should be displayed. */
uint16_t oled_pet_update_millis(uint8_t wpm);

/* Returns a PROGMEM pointer to the specified animation frame buffer for the
 * specified state. The animation frame has length given by
 * oled_pet_frame_bytes and is formatted as expected by oled_write_raw_P.
 */
const char *oled_pet_frame(oled_pet_state_t state, uint8_t frame);
