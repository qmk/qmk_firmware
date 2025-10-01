/*
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

#include "blackberry_trackball.h"
#include "ch.h"
#include "hal.h"
#include "gpio.h"
#include "print.h"

volatile int8_t x = 0;
volatile int8_t y = 0;
char debug = '\0';

const pointing_device_driver_t blackberry_trackball_pointing_device_driver = {
    .init       = blackberry_trackball_init,
    .get_report = blackberry_trackball_get_report,
    .set_cpi    = NULL,
    .get_cpi    = NULL,
};


void trackball_movement_cb(void *arg) {

    switch ((intptr_t)arg) {

        case M_UP:
            y -= BLACKBERRY_TRACKBALL_STEP;
            debug = 'U';
            break;
        case M_DOWN:
            y += BLACKBERRY_TRACKBALL_STEP;
            debug = 'D';
            break;
        case M_RIGHT:
            x += BLACKBERRY_TRACKBALL_STEP;
            debug = 'R';
            break;
        case M_LEFT:
            x -= BLACKBERRY_TRACKBALL_STEP;
            debug = 'L';
            break;
    }
}



void blackberry_trackball_init(void) {

    palSetLineMode(BLACKBERRY_TRACKBALL_UP_PIN, PAL_MODE_INPUT);
    palEnableLineEvent(BLACKBERRY_TRACKBALL_UP_PIN, PAL_EVENT_MODE_RISING_EDGE );
    palSetLineCallback(BLACKBERRY_TRACKBALL_UP_PIN, trackball_movement_cb, (void *)M_UP); 

    palSetLineMode(BLACKBERRY_TRACKBALL_DOWN_PIN, PAL_MODE_INPUT);
    palEnableLineEvent(BLACKBERRY_TRACKBALL_DOWN_PIN, PAL_EVENT_MODE_RISING_EDGE );
    palSetLineCallback(BLACKBERRY_TRACKBALL_DOWN_PIN, trackball_movement_cb, (void *)M_DOWN); 

    palSetLineMode(BLACKBERRY_TRACKBALL_LEFT_PIN, PAL_MODE_INPUT);
    palEnableLineEvent(BLACKBERRY_TRACKBALL_LEFT_PIN, PAL_EVENT_MODE_RISING_EDGE );
    palSetLineCallback(BLACKBERRY_TRACKBALL_LEFT_PIN, trackball_movement_cb, (void *)M_LEFT); 

    palSetLineMode(BLACKBERRY_TRACKBALL_RIGHT_PIN, PAL_MODE_INPUT);
    palEnableLineEvent(BLACKBERRY_TRACKBALL_RIGHT_PIN, PAL_EVENT_MODE_RISING_EDGE );
    palSetLineCallback(BLACKBERRY_TRACKBALL_RIGHT_PIN, trackball_movement_cb, (void *)M_RIGHT); 
}


report_mouse_t blackberry_trackball_get_report(report_mouse_t mouse_report) {

    mouse_report.x = x;
    mouse_report.y = y;
    x = 0;
    y = 0;   

    #ifdef BLACKBERRY_TRACKBALL_DEBUG
        if (debug != '\0') {
            uprintf("%c\n", debug);
        }
        debug = '\0';
    #endif

    return mouse_report;
}
