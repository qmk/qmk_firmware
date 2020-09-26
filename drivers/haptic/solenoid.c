/* Copyright 2018 mtdjr - modified by ishtob
 * Driver for solenoid written for QMK
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

#include <timer.h>
#include "solenoid.h"
#include "haptic.h"

bool     solenoid_on      = false;
bool     solenoid_buzzing = false;
uint16_t solenoid_start   = 0;
uint8_t  solenoid_dwell   = SOLENOID_DEFAULT_DWELL;

extern haptic_config_t haptic_config;

void solenoid_buzz_on(void) { haptic_set_buzz(1); }

void solenoid_buzz_off(void) { haptic_set_buzz(0); }

void solenoid_set_buzz(int buzz) { haptic_set_buzz(buzz); }

void solenoid_dwell_minus(uint8_t solenoid_dwell) {
    if (solenoid_dwell > 0) solenoid_dwell--;
}

void solenoid_dwell_plus(uint8_t solenoid_dwell) {
    if (solenoid_dwell < SOLENOID_MAX_DWELL) solenoid_dwell++;
}

void solenoid_set_dwell(uint8_t dwell) { solenoid_dwell = dwell; }

void solenoid_stop(void) {
    writePinLow(SOLENOID_PIN);
    solenoid_on      = false;
    solenoid_buzzing = false;
}

void solenoid_fire(void) {
    if (!haptic_config.buzz && solenoid_on) return;
    if (haptic_config.buzz && solenoid_buzzing) return;

    solenoid_on      = true;
    solenoid_buzzing = true;
    solenoid_start   = timer_read();
    writePinHigh(SOLENOID_PIN);
}

void solenoid_check(void) {
    uint16_t elapsed = 0;

    if (!solenoid_on) return;

    elapsed = timer_elapsed(solenoid_start);

    // Check if it's time to finish this solenoid click cycle
    if (elapsed > solenoid_dwell) {
        solenoid_stop();
        return;
    }

    // Check whether to buzz the solenoid on and off
    if (haptic_config.buzz) {
        if (elapsed / SOLENOID_MIN_DWELL % 2 == 0) {
            if (!solenoid_buzzing) {
                solenoid_buzzing = true;
                writePinHigh(SOLENOID_PIN);
            }
        } else {
            if (solenoid_buzzing) {
                solenoid_buzzing = false;
                writePinLow(SOLENOID_PIN);
            }
        }
    }
}

void solenoid_setup(void) {
    setPinOutput(SOLENOID_PIN);
    solenoid_fire();
}

void solenoid_shutdown(void) { writePinLow(SOLENOID_PIN); }
