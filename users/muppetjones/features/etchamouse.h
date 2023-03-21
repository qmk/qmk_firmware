/* Copyright 2020 Stephen J. Bush
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

#if defined(POINTING_DEVICE_ENABLE) && defined(ENCODER_ENABLE)

/* max value on report descriptor */
#    ifndef MOUSEKEY_MOVE_MAX
#        define MOUSEKEY_MOVE_MAX 127
#    elif MOUSEKEY_MOVE_MAX > 127
#        error MOUSEKEY_MOVE_MAX needs to be smaller than 127
#    endif
#    ifndef MOUSEKEY_MOVE_DELTA
#        define MOUSEKEY_MOVE_DELTA 25
#    endif
#    ifndef MOUSEKEY_INITIAL_SPEED
#        define MOUSEKEY_INITIAL_SPEED 100
#    endif
#    ifndef MOUSEKEY_INTERVAL
#        define MOUSEKEY_INTERVAL 75
#    endif

/** Amount of time (ms) before zeroing out the count.
 *  A higher value will result in smoother curves but may lower accuracy
 */
#    ifndef TAPPING_TERM_PERSISTENCE
#        define TAPPING_TERM_PERSISTENCE 150
#    endif

/** Amount of time (ms) to register consecutive key presses
 *  A higher value will smooth out mouse movement and increase speed for
 *  consecutive presses.
 */
#    ifndef TAPPING_TERM_MOUSE_ENCODER
#        define TAPPING_TERM_MOUSE_ENCODER 50
#    endif

/** @brief Update mouse position based on encoder movement.
 *  @param index The encoder index. 0 controls x-axis; 1 controls y-axis.
 *  @param clockwise Indicates direction encoder was turned.
 *  @returns None.
 */
bool encoder_update_mouse(uint8_t index, bool clockwise);

#endif
