/* Copyright 2023 9R
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

#include "thumbstick.h"
#include <math.h>
#include "action.h"
#include "keycode.h"
#include "debug.h"

void init_wasd_state (void) {
    wasd_state.w = wasd_state.a = wasd_state.s = wasd_state.d = false;
    last_wasd_state = wasd_state;
    wasd_state.shift = false;
}

thumbstick_polar_position_t get_thumbstick_polar_position(int16_t x, int16_t y) {
    static thumbstick_polar_position_t position;

#ifdef THUMBSTICK_DEBUG
    dprintf("xN: %4d yN: %4d\n", x, y);
#endif

    //transform to carthesian coordinates to  polar coordinates
    //get distance from center as int in range [0-600]
    position.distance = (double)sqrt((double)x * (double)x + (double)y * (double)y);
    //get direction as int in range [0 to 359]
    position.angle = (double)atan2(y, x) * (180 /M_PI) + 180;

    //apply thumbstick rotation const to modify forward direction
    position.angle = (position.angle + _THUMBSTICK_ROTATION) % 360;

    return position;
}

bool update_keystate(uint16_t angle_from, uint16_t angle_to, uint16_t angle) {
    return (angle_from < angle && angle <= angle_to);
}

void update_keycode(uint16_t keycode, bool keystate, bool last_keystate) {
    if (keystate && keystate != last_keystate) {
        register_code16(keycode);
    } else if (!keystate) {
        unregister_code16(keycode);
    }
}

void thumbstick(controller_state_t controller_state) {
    xPos = joystick_state.axes[0];
    yPos = joystick_state.axes[1];

    thumbstick_polar_position = get_thumbstick_polar_position(xPos, yPos);

#ifdef THUMBSTICK_DEBUG
    dprintf("distance: %5d angle: %5d\n", thumbstick_polar_position.distance, thumbstick_polar_position.angle);
#endif

    // Update WASD state depending on thumbstick position
    // if thumbstick out of of deadzone
    if (thumbstick_polar_position.distance >= _DEADZONE) {
        wasd_state.w = update_keystate(  0,  90, thumbstick_polar_position.angle);
        // A angle:  45 - 180
        wasd_state.a = update_keystate( 45, 181, thumbstick_polar_position.angle);
        // S angle: 135 - 270
        wasd_state.s = update_keystate(135, 270, thumbstick_polar_position.angle);
        // D angle: 225 - 359
        wasd_state.d = update_keystate(225, 359, thumbstick_polar_position.angle);

        if (!wasd_state.w ) {
            wasd_state.w = update_keystate(315, 360, thumbstick_polar_position.angle);
        }
    } else {
        //reset WASD state when in _DEADZONE
        init_wasd_state();
    }

#ifdef THUMBSTICK_DEBUG
    dprintf("w: %2d a: %2d s: %2d d: %2d\n", wasd_state.w, wasd_state.a, wasd_state.s, wasd_state.d);
#endif

    update_keycode(KC_W, wasd_state.w, last_wasd_state.w);
    update_keycode(KC_A, wasd_state.a, last_wasd_state.a);
    update_keycode(KC_S, wasd_state.s, last_wasd_state.s);
    update_keycode(KC_D, wasd_state.d, last_wasd_state.d);

    last_wasd_state = wasd_state ;

    // handle WASD-Shift mode
    if (controller_state.wasdShiftMode) {
        bool Shifted = thumbstick_polar_position.distance > _SHIFTZONE;
        if (!wasd_state.shift && Shifted) {
            register_code(KC_LSFT);
            wasd_state.shift = true;
        } else if (wasd_state.shift && !Shifted) {
            unregister_code(KC_LSFT);
            wasd_state.shift = false;
        }
    }
}
