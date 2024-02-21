/* Copyright 2021 QMK
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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
#include "split_util.h"
#include "matrix.h"
#include "keyboard.h"
#include "timer.h"
#include "transport.h"
#include "wait.h"
#include "debug.h"
#include "usb_util.h"
#include "bootloader.h"

#ifdef EE_HANDS
#    include "eeconfig.h"
#endif

#if defined(RGBLIGHT_ENABLE) && defined(RGBLED_SPLIT)
#    include "rgblight.h"
#endif

#ifndef SPLIT_USB_TIMEOUT
#    define SPLIT_USB_TIMEOUT 2000
#endif

#ifndef SPLIT_USB_TIMEOUT_POLL
#    define SPLIT_USB_TIMEOUT_POLL 10
#endif

// Max number of consecutive failed communications (one per scan cycle) before the communication is seen as disconnected.
// Set to 0 to disable the disconnection check altogether.
#ifndef SPLIT_MAX_CONNECTION_ERRORS
#    define SPLIT_MAX_CONNECTION_ERRORS 10
#endif // SPLIT_MAX_CONNECTION_ERRORS

// How long (in milliseconds) to block all connection attempts after the communication has been flagged as disconnected.
// One communication attempt will be allowed everytime this amount of time has passed since the last attempt. If that attempt succeeds, the communication is seen as working again.
// Set to 0 to disable communication throttling while disconnected
#ifndef SPLIT_CONNECTION_CHECK_TIMEOUT
#    define SPLIT_CONNECTION_CHECK_TIMEOUT 500
#endif // SPLIT_CONNECTION_CHECK_TIMEOUT

static uint8_t connection_errors = 0;

volatile bool isLeftHand = true;

static struct {
    bool master;
    bool left;
} split_config;

#if defined(SPLIT_USB_DETECT)
_Static_assert((SPLIT_USB_TIMEOUT / SPLIT_USB_TIMEOUT_POLL) <= UINT16_MAX, "Please lower SPLIT_USB_TIMEOUT and/or increase SPLIT_USB_TIMEOUT_POLL.");
static bool usbIsActive(void) {
    for (uint16_t i = 0; i < (SPLIT_USB_TIMEOUT / SPLIT_USB_TIMEOUT_POLL); i++) {
        // This will return true if a USB connection has been established
        if (usb_connected_state()) {
            return true;
        }
        wait_ms(SPLIT_USB_TIMEOUT_POLL);
    }
    return false;
}
#else
static inline bool usbIsActive(void) {
    return usb_vbus_state();
}
#endif

#if defined(SPLIT_WATCHDOG_ENABLE)
#    if !defined(SPLIT_WATCHDOG_TIMEOUT)
#        if defined(SPLIT_USB_TIMEOUT)
#            define SPLIT_WATCHDOG_TIMEOUT (SPLIT_USB_TIMEOUT + 100)
#        else
#            define SPLIT_WATCHDOG_TIMEOUT 3000
#        endif
#    endif
#    if defined(SPLIT_USB_DETECT)
_Static_assert(SPLIT_USB_TIMEOUT < SPLIT_WATCHDOG_TIMEOUT, "SPLIT_WATCHDOG_TIMEOUT should not be below SPLIT_USB_TIMEOUT.");
#    endif
_Static_assert(SPLIT_MAX_CONNECTION_ERRORS > 0, "SPLIT_WATCHDOG_ENABLE requires SPLIT_MAX_CONNECTION_ERRORS be above 0 for a functioning disconnection check.");

static uint32_t split_watchdog_started = 0;
static bool     split_watchdog_done    = false;

void split_watchdog_init(void) {
    split_watchdog_started = timer_read32();
}

void split_watchdog_update(bool done) {
    split_watchdog_done = done;
}

bool split_watchdog_check(void) {
    if (!is_transport_connected()) {
        split_watchdog_done = false;
    }
    return split_watchdog_done;
}

void split_watchdog_task(void) {
    if (!split_watchdog_done && !is_keyboard_master()) {
        if (timer_elapsed32(split_watchdog_started) > SPLIT_WATCHDOG_TIMEOUT) {
            mcu_reset();
        }
    }
}
#endif // defined(SPLIT_WATCHDOG_ENABLE)

#ifdef SPLIT_HAND_MATRIX_GRID
void matrix_io_delay(void);

static uint8_t peek_matrix_intersection(pin_t out_pin, pin_t in_pin) {
    gpio_set_pin_input_high(in_pin);
    gpio_set_pin_output(out_pin);
    gpio_write_pin_low(out_pin);
    // It's almost unnecessary, but wait until it's down to low, just in case.
    wait_us(1);
    uint8_t pin_state = gpio_read_pin(in_pin);
    // Set out_pin to a setting that is less susceptible to noise.
    gpio_set_pin_input_high(out_pin);
    matrix_io_delay(); // Wait for the pull-up to go HIGH.
    return pin_state;
}
#endif

__attribute__((weak)) bool is_keyboard_left_impl(void) {
#if defined(SPLIT_HAND_PIN)
    gpio_set_pin_input(SPLIT_HAND_PIN);
    wait_us(100);
    // Test pin SPLIT_HAND_PIN for High/Low, if low it's right hand
#    ifdef SPLIT_HAND_PIN_LOW_IS_LEFT
    return !gpio_read_pin(SPLIT_HAND_PIN);
#    else
    return gpio_read_pin(SPLIT_HAND_PIN);
#    endif
#elif defined(SPLIT_HAND_MATRIX_GRID)
#    ifdef SPLIT_HAND_MATRIX_GRID_LOW_IS_LEFT
    return !peek_matrix_intersection(SPLIT_HAND_MATRIX_GRID);
#    else
    return peek_matrix_intersection(SPLIT_HAND_MATRIX_GRID);
#    endif
#elif defined(EE_HANDS)
    if (!eeconfig_is_enabled()) {
        eeconfig_init();
    }
    // TODO: Remove once ARM has a way to configure EECONFIG_HANDEDNESS within the emulated eeprom via dfu-util or another tool
#    if defined(INIT_EE_HANDS_LEFT) || defined(INIT_EE_HANDS_RIGHT)
#        if defined(INIT_EE_HANDS_LEFT)
#            pragma message "Faking EE_HANDS for left hand"
    const bool should_be_left = true;
#        else
#            pragma message "Faking EE_HANDS for right hand"
    const bool should_be_left = false;
#        endif
    bool       is_left        = eeconfig_read_handedness();
    if (is_left != should_be_left) {
        eeconfig_update_handedness(should_be_left);
    }
#    endif // defined(INIT_EE_HANDS_LEFT) || defined(INIT_EE_HANDS_RIGHT)
    return eeconfig_read_handedness();
#elif defined(MASTER_RIGHT)
    return !is_keyboard_master();
#else
    return is_keyboard_master();
#endif
}

__attribute__((weak)) bool is_keyboard_master_impl(void) {
    bool is_master = usbIsActive();

    // Avoid NO_USB_STARTUP_CHECK - Disable USB as the previous checks seem to enable it somehow
    if (!is_master) {
        usb_disconnect();
    }
    return is_master;
}

__attribute__((weak)) bool is_keyboard_left(void) {
    return split_config.left;
}

__attribute__((weak)) bool is_keyboard_master(void) {
    return split_config.master;
}

// this code runs before the keyboard is fully initialized
void split_pre_init(void) {
    split_config.master = is_keyboard_master_impl();
    split_config.left   = is_keyboard_left_impl();

    isLeftHand = is_keyboard_left(); // TODO: Remove isLeftHand

#if defined(RGBLIGHT_ENABLE) && defined(RGBLED_SPLIT)
    uint8_t num_rgb_leds_split[2] = RGBLED_SPLIT;
    if (is_keyboard_left()) {
        rgblight_set_clipping_range(0, num_rgb_leds_split[0]);
    } else {
        rgblight_set_clipping_range(num_rgb_leds_split[0], num_rgb_leds_split[1]);
    }
#endif

    if (is_keyboard_master()) {
        transport_master_init();
    }
}

// this code runs after the keyboard is fully initialized
//   - avoids race condition during matrix_init_quantum where slave can start
//     receiving before the init process has completed
void split_post_init(void) {
    if (!is_keyboard_master()) {
        transport_slave_init();
#if defined(SPLIT_WATCHDOG_ENABLE)
        split_watchdog_init();
#endif
    }
}

bool is_transport_connected(void) {
    return connection_errors < SPLIT_MAX_CONNECTION_ERRORS;
}

bool transport_master_if_connected(matrix_row_t master_matrix[], matrix_row_t slave_matrix[]) {
#if SPLIT_MAX_CONNECTION_ERRORS > 0 && SPLIT_CONNECTION_CHECK_TIMEOUT > 0
    // Throttle transaction attempts if target doesn't seem to be connected
    // Without this, a solo half becomes unusable due to constant read timeouts
    static uint16_t connection_check_timer = 0;
    const bool      is_disconnected        = !is_transport_connected();
    if (is_disconnected && timer_elapsed(connection_check_timer) < SPLIT_CONNECTION_CHECK_TIMEOUT) {
        return false;
    }
#endif // SPLIT_MAX_CONNECTION_ERRORS > 0 && SPLIT_CONNECTION_CHECK_TIMEOUT > 0

    __attribute__((unused)) bool okay = transport_master(master_matrix, slave_matrix);
#if SPLIT_MAX_CONNECTION_ERRORS > 0
    if (!okay) {
        if (connection_errors < UINT8_MAX) {
            connection_errors++;
        }
#    if SPLIT_CONNECTION_CHECK_TIMEOUT > 0
        bool connected = is_transport_connected();
        if (!connected) {
            connection_check_timer = timer_read();
            dprintln("Target disconnected, throttling connection attempts");
        }
        return connected;
    } else if (is_disconnected) {
        dprintln("Target connected");
#    endif // SPLIT_CONNECTION_CHECK_TIMEOUT > 0
    }

    connection_errors = 0;
#endif // SPLIT_MAX_CONNECTION_ERRORS > 0
    return true;
}
