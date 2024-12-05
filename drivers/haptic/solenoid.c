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

#include "timer.h"
#include "solenoid.h"
#include "haptic.h"
#include "gpio.h"
#include "usb_device_state.h"
#include "util.h"
#include <stdlib.h>

static pin_t solenoid_pads[] = SOLENOID_PINS;
#define NUMBER_OF_SOLENOIDS ARRAY_SIZE(solenoid_pads)
bool     solenoid_on[NUMBER_OF_SOLENOIDS]      = {false};
bool     solenoid_buzzing[NUMBER_OF_SOLENOIDS] = {false};
uint16_t solenoid_start[NUMBER_OF_SOLENOIDS]   = {0};
#ifdef SOLENOID_PIN_ACTIVE_LOW
#    define low true
#    define high false
#else
#    define low false
#    define high true
#endif
static bool solenoid_active_state[NUMBER_OF_SOLENOIDS];

extern haptic_config_t haptic_config;

void solenoid_buzz_on(void) {
    haptic_set_buzz(1);
}

void solenoid_buzz_off(void) {
    haptic_set_buzz(0);
}

void solenoid_set_buzz(uint8_t buzz) {
    haptic_set_buzz(buzz);
}

void solenoid_set_dwell(uint8_t dwell) {
    haptic_set_dwell(dwell);
}

/**
 * @brief Stops a specific solenoid
 *
 * @param index select which solenoid to check/stop
 */
void solenoid_stop(uint8_t index) {
    gpio_write_pin(solenoid_pads[index], !solenoid_active_state[index]);
    solenoid_on[index]      = false;
    solenoid_buzzing[index] = false;
}

/**
 * @brief Fires off a specific solenoid
 *
 * @param index Selects which solenoid to fire
 */
void solenoid_fire(uint8_t index) {
    if (!haptic_config.buzz && solenoid_on[index]) return;
    if (haptic_config.buzz && solenoid_buzzing[index]) return;

    solenoid_on[index]      = true;
    solenoid_buzzing[index] = true;
    solenoid_start[index]   = timer_read();
    gpio_write_pin(solenoid_pads[index], solenoid_active_state[index]);
}

/**
 * @brief Handles selecting a non-active solenoid, and firing it.
 *
 */
void solenoid_fire_handler(void) {
#ifndef SOLENOID_RANDOM_FIRE
    if (NUMBER_OF_SOLENOIDS > 1) {
        uint8_t i = rand() % NUMBER_OF_SOLENOIDS;
        if (!solenoid_on[i]) {
            solenoid_fire(i);
        }
    } else {
        solenoid_fire(0);
    }
#else
    for (uint8_t i = 0; i < NUMBER_OF_SOLENOIDS; i++) {
        if (!solenoid_on[i]) {
            solenoid_fire(i);
            break;
        }
    }
#endif
}

/**
 * @brief Checks active solenoid to stop them, and to handle buzz mode
 *
 */
void solenoid_check(void) {
    uint16_t elapsed[NUMBER_OF_SOLENOIDS] = {0};

    for (uint8_t i = 0; i < NUMBER_OF_SOLENOIDS; i++) {
        if (!solenoid_on[i]) continue;

        elapsed[i] = timer_elapsed(solenoid_start[i]);

        // Check if it's time to finish this solenoid click cycle
        if (elapsed[i] > haptic_config.dwell) {
            solenoid_stop(i);
            continue;
        }

        // Check whether to buzz the solenoid on and off
        if (haptic_config.buzz) {
            if ((elapsed[i] % (SOLENOID_BUZZ_ACTUATED + SOLENOID_BUZZ_NONACTUATED)) < SOLENOID_BUZZ_ACTUATED) {
                if (!solenoid_buzzing[i]) {
                    solenoid_buzzing[i] = true;
                    gpio_write_pin(solenoid_pads[i], solenoid_active_state[i]);
                }
            } else {
                if (solenoid_buzzing[i]) {
                    solenoid_buzzing[i] = false;
                    gpio_write_pin(solenoid_pads[i], !solenoid_active_state[i]);
                }
            }
        }
    }
}

/**
 * @brief Initial configuration for solenoids
 *
 */
void solenoid_setup(void) {
#ifdef SOLENOID_PINS_ACTIVE_STATE
    bool    state_temp[] = SOLENOID_PINS_ACTIVE_STATE;
    uint8_t bound_check  = ARRAY_SIZE(state_temp);
#endif

    for (uint8_t i = 0; i < NUMBER_OF_SOLENOIDS; i++) {
#ifdef SOLENOID_PINS_ACTIVE_STATE
        solenoid_active_state[i] = (bound_check - i) ? state_temp[i] : high;
#else
        solenoid_active_state[i] = high;
#endif
        gpio_write_pin(solenoid_pads[i], !solenoid_active_state[i]);
        gpio_set_pin_output(solenoid_pads[i]);
        if ((!HAPTIC_OFF_IN_LOW_POWER) || (usb_device_state_get_configure_state() == USB_DEVICE_STATE_CONFIGURED)) {
            solenoid_fire(i);
        }
    }
}

/**
 * @brief stops solenoids prior to device reboot, to prevent them from being locked on
 *
 */
void solenoid_shutdown(void) {
    for (uint8_t i = 0; i < NUMBER_OF_SOLENOIDS; i++) {
        gpio_write_pin(solenoid_pads[i], !solenoid_active_state[i]);
    }
}
