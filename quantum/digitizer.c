/* Copyright 2025 George Norton (@george-norton)
 * Copyright 2021
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
#include "digitizer.h"
#include "digitizer_mouse_fallback.h"
#include "debug.h"
#include "host.h"
#include "timer.h"
#include "gpio.h"
#include "keyboard.h"
#include "action.h"

#ifdef DIGITIZER_MOTION_PIN
#    undef DIGITIZER_TASK_THROTTLE_MS
#endif

#if defined(DIGITIZER_LEFT) || defined(DIGITIZER_RIGHT)
#    ifndef SPLIT_DIGITIZER_ENABLE
#        error "Using DIGITIZER_LEFT or DIGITIZER_RIGHT, then SPLIT_DIGITIZER_ENABLE is required but has not been defined"
#    endif
#endif

typedef struct {
    void (*init)(void);
    digitizer_t (*get_report)(digitizer_t digitizer_report);
} digitizer_driver_t;

const digitizer_driver_t digitizer_driver = {};

static digitizer_t digitizer_state = {};
static bool        dirty           = false;

#if defined(SPLIT_DIGITIZER_ENABLE)

#    if defined(DIGITIZER_LEFT)
#        define DIGITIZER_THIS_SIDE is_keyboard_left()
#    elif defined(DIGITIZER_RIGHT)
#        define DIGITIZER_THIS_SIDE !is_keyboard_left()
#    endif

digitizer_t shared_digitizer_report = {};

/**
 * @brief Sets the shared digitizer report used by digitizer device task
 *
 * NOTE : Only available when using SPLIT_DIGITIZER_ENABLE
 *
 * @param[in] report digitizer_t
 */
void digitizer_set_shared_report(digitizer_t report) {
    shared_digitizer_report = report;
}
#endif // defined(SPLIT_DIGITIZER_ENABLE)

/**
 * @brief Utility for checking if the digitizer state has changed between two structs.
 *
 * @return digitizer_t
 */
static bool has_digitizer_state_changed(digitizer_t *tmp_state, digitizer_t *old_state) {
    const int cmp = memcmp(tmp_state, old_state, sizeof(digitizer_t));
    return cmp != 0;
}

/**
 * @brief Gets the current digitizer state used by the digitizer task
 *
 * @return digitizer_t
 */
digitizer_t digitizer_get_state(void) {
    return digitizer_state;
}

/**
 * @brief Sets the digitizer state, the new state will be sent when the digitizer task next runs.
 *
 * @param[in] new_digitizer_state
 */
void digitizer_set_state(digitizer_t new_digitizer_state) {
    dirty |= has_digitizer_state_changed(&digitizer_state, &new_digitizer_state);
    if (dirty) memcpy(&digitizer_state, &new_digitizer_state, sizeof(digitizer_t));
}

/**
 * @brief Keyboard level digitizer initialisation function
 *
 */
__attribute__((weak)) void digitizer_init_kb(void) {}

/**
 * @brief User level digitizer initialisation function
 *
 */
__attribute__((weak)) void digitizer_init_user(void) {}

/**
 * @brief Weak function allowing for user level digitizer state modification
 *
 * Takes digitizer_t struct allowing modification at user level then returns digitizer_t.
 *
 * @param[in] digitizer_state digitizer_t
 * @return digitizer_t
 */
__attribute__((weak)) digitizer_t digitizer_task_user(digitizer_t digitizer_state) {
    return digitizer_state;
}

/**
 * @brief Weak function allowing for keyboard level digitizer state modification
 *
 * Takes digitizer_t struct allowing modification at keyboard level then returns digitizer_t.
 *
 * @param[in] digitizer_state digitizer_t
 * @return digitizer_t
 */
__attribute__((weak)) digitizer_t digitizer_task_kb(digitizer_t digitizer_state) {
    return digitizer_task_user(digitizer_state);
}

/**
 * \brief Initializes the digitizer feature.
 */
void digitizer_init(void) {
#if defined(SPLIT_DIGITIZER_ENABLE)
    if (!(DIGITIZER_THIS_SIDE)) return;
#endif
    if (digitizer_driver.init) {
        digitizer_driver.init();
    }
#ifdef DIGITIZER_MOTION_PIN
#    ifdef DIGITIZER_MOTION_PIN_ACTIVE_LOW
    setPinInputHigh(DIGITIZER_MOTION_PIN);
#    else
    setPinInput(DIGITIZER_MOTION_PIN);
#    endif
#endif

    digitizer_init_kb();
    digitizer_init_user();
}

#ifdef DIGITIZER_MOTION_PIN
/**
 * \brief Checks if the motion pin is active.
 */
__attribute__((weak)) bool digitizer_motion_detected(void) {
#    ifdef DIGITIZER_MOTION_PIN_ACTIVE_LOW
    return !readPin(DIGITIZER_MOTION_PIN);
#    else
    return readPin(DIGITIZER_MOTION_PIN);
#    endif
}
#endif

/**
 * \brief Task processing routine for the digitizer feature. This function polls the digitizer hardware
 * and sends events to the host as required.
 *
 * \return true if a new event was sent
 */
bool digitizer_task(void) {
    report_digitizer_t report = {.fingers = {}, .contact_count = 0, .scan_time = 0, .button1 = digitizer_state.button1, .button2 = digitizer_state.button2, .button3 = digitizer_state.button3};
#if defined(DIGITIZER_HAS_STYLUS)
    report_digitizer_stylus_t stylus_report  = {};
    bool                      updated_stylus = false;
#endif
    int  contacts             = 0;
    bool gesture_changed      = false;
    bool button_state_changed = false;

#if DIGITIZER_TASK_THROTTLE_MS
    static uint32_t last_exec = 0;
    if (timer_elapsed32(last_exec) < DIGITIZER_TASK_THROTTLE_MS) {
        return false;
    }
    last_exec = timer_read32();
#endif
#if defined(POINTING_DEVICE_DRIVER_digitizer)
    gesture_changed                          = digitizer_update_gesture_state();
    static report_digitizer_t last_report    = {0};
    bool                      report_changed = false;
#endif

#if defined(DIGITIZER_MOTION_PIN)
    if (digitizer_motion_detected())
#endif
    {
#if defined(SPLIT_DIGITIZER_ENABLE)
#    if defined(DIGITIZER_LEFT) || defined(DIGITIZER_RIGHT)
        digitizer_t driver_state = DIGITIZER_THIS_SIDE ? (digitizer_driver.get_report ? digitizer_driver.get_report(digitizer_state) : digitizer_state) : shared_digitizer_report;
#    else
#        error "You need to define the side(s) the digitizer is on. DIGITIZER_LEFT / DIGITIZER_RIGHT"
#    endif
#else
        digitizer_t driver_state = digitizer_driver.get_report ? digitizer_driver.get_report(digitizer_state) : digitizer_state;
#endif
        // Handle user modification of stylus state. We explicity do not store the user modified
        // state so we do not pass them back state that they have previously transformed.
        digitizer_t tmp_state = digitizer_task_kb(driver_state);

        if (digitizer_state.buttons != tmp_state.buttons) {
            button_state_changed = true;
            report.button1 |= tmp_state.button1;
            report.button2 |= tmp_state.button2;
            report.button3 |= tmp_state.button3;
        }

        int skip_count = 0;
        for (int i = 0; i < DIGITIZER_CONTACT_COUNT; i++) {
            // If this is a finger which is down, or it was on the last scan (but now it is up)..
            if (i < DIGITIZER_FINGER_COUNT) {
                const bool    finger_contact = (tmp_state.contacts[i].type == FINGER && tmp_state.contacts[i].tip) || (digitizer_state.contacts[i].type == FINGER && digitizer_state.contacts[i].tip);
                const uint8_t finger_index   = finger_contact ? report.contact_count : DIGITIZER_FINGER_COUNT - skip_count - 1;

                if (tmp_state.contacts[i].type != UNKNOWN) {
                    // 'contacts' is the number of current contacts wheras 'report->contact_count' also counts fingers which have
                    // been removed from the sensor since the last report.
                    contacts++;
                }
                if (finger_contact) {
                    report.fingers[finger_index].tip = tmp_state.contacts[i].tip;
                    report.contact_count++;
                } else {
                    skip_count++;
                    report.fingers[finger_index].tip = false;
                }
                report.fingers[finger_index].contact_id = i;
                report.fingers[finger_index].x          = tmp_state.contacts[i].x;
                report.fingers[finger_index].y          = tmp_state.contacts[i].y;
                report.fingers[finger_index].confidence = tmp_state.contacts[i].confidence;
            }
#ifdef DIGITIZER_HAS_STYLUS
            if (tmp_state.contacts[i].type == STYLUS) {
                updated_stylus         = true;
                stylus_report.x        = tmp_state.contacts[i].x;
                stylus_report.y        = tmp_state.contacts[i].y;
                stylus_report.tip      = tmp_state.contacts[i].tip;
                stylus_report.in_range = tmp_state.contacts[i].in_range;
            } else if (digitizer_state.contacts[i].type == STYLUS) {
                // Drop the tip, then drop out of range next scan
                updated_stylus         = true;
                stylus_report.x        = digitizer_state.contacts[i].x;
                stylus_report.y        = digitizer_state.contacts[i].y;
                stylus_report.in_range = false;
                stylus_report.tip      = false;
            }
#endif
        }
        digitizer_state = driver_state;

#if defined(POINTING_DEVICE_DRIVER_digitizer)
        report_changed = true;
#endif
    }
#ifdef DIGITIZER_HAS_STYLUS
    if (updated_stylus) {
        host_digitizer_stylus_send(&stylus_report);
    }
#endif
    if (report.contact_count || button_state_changed || gesture_changed) {
#if defined(POINTING_DEVICE_DRIVER_digitizer)
        // We may get here because we read a new digitizer report, or because
        // a timeout on a gesture occured. If a timeout occured use the last known
        // digitizer state. Otherwise send the new state for processing.
        if (report_changed) {
            last_report = report;
            digitizer_update_mouse_report(&report);
        } else {
            digitizer_update_mouse_report(&last_report);
        }
        if (!digitizer_send_mouse_reports) {
#endif
            if (report.contact_count || button_state_changed) {
#if DIGITIZER_FINGER_COUNT > 0
                static uint32_t scan_time     = 0;
                static int      last_contacts = 0;

                // Reset the scan_time after a period of inactivity (1000ms with no contacts)
                static uint32_t inactivity_timer = 0;
                if (last_contacts == 0 && contacts && timer_elapsed32(inactivity_timer) > 1000) {
                    scan_time = timer_read32();
                }
                inactivity_timer = timer_read32();
                last_contacts    = contacts;

                // Microsoft require we report in 100us ticks.
                uint32_t scan    = timer_elapsed32(scan_time);
                report.scan_time = scan * 10;
#endif
                host_digitizer_send(&report);
            }
#if defined(POINTING_DEVICE_DRIVER_digitizer)
        }
#endif
    }

#ifdef DIGITIZER_HAS_STYLUS
    return report.contact_count > 0 || button_state_changed || updated_stylus;
#else
    return report.contact_count > 0 || button_state_changed;
#endif
}
