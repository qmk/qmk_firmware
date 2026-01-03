/*
Copyright 2011, 2012, 2013 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdint.h>
#include "keyboard.h"
#include "keycode_config.h"
#include "matrix.h"
#include "keymap_introspection.h"
#include "host.h"
#include "led.h"
#include "keycode.h"
#include "timer.h"
#include "sync_timer.h"
#include "print.h"
#include "debug.h"
#include "command.h"
#include "util.h"
#include "host.h"
#include "sendchar.h"
#include "eeconfig.h"
#include "action_layer.h"
#include "suspend.h"
#ifdef BOOTMAGIC_ENABLE
#    include "bootmagic.h"
#endif
#ifdef AUDIO_ENABLE
#    include "audio.h"
#endif
#if defined(AUDIO_ENABLE) || (defined(MIDI_ENABLE) && defined(MIDI_BASIC))
#    include "process_music.h"
#endif
#ifdef BACKLIGHT_ENABLE
#    include "backlight.h"
#endif
#ifdef MOUSEKEY_ENABLE
#    include "mousekey.h"
#endif
#ifdef PS2_MOUSE_ENABLE
#    include "ps2_mouse.h"
#endif
#ifdef RGBLIGHT_ENABLE
#    include "rgblight.h"
#endif
#ifdef LED_MATRIX_ENABLE
#    include "led_matrix.h"
#endif
#ifdef RGB_MATRIX_ENABLE
#    include "rgb_matrix.h"
#endif
#ifdef ENCODER_ENABLE
#    include "encoder.h"
#endif
#ifdef HAPTIC_ENABLE
#    include "haptic.h"
#endif
#ifdef AUTO_SHIFT_ENABLE
#    include "process_auto_shift.h"
#endif
#ifdef COMBO_ENABLE
#    include "process_combo.h"
#endif
#ifdef TAP_DANCE_ENABLE
#    include "process_tap_dance.h"
#endif
#ifdef STENO_ENABLE
#    include "process_steno.h"
#endif
#ifdef KEY_OVERRIDE_ENABLE
#    include "process_key_override.h"
#endif
#ifdef SECURE_ENABLE
#    include "secure.h"
#endif
#ifdef POINTING_DEVICE_ENABLE
#    include "pointing_device.h"
#endif
#ifdef MIDI_ENABLE
#    include "process_midi.h"
#endif
#ifdef JOYSTICK_ENABLE
#    include "joystick.h"
#endif
#ifdef HD44780_ENABLE
#    include "hd44780.h"
#endif
#ifdef OLED_ENABLE
#    include "oled_driver.h"
#endif
#ifdef ST7565_ENABLE
#    include "st7565.h"
#endif
#ifdef VIA_ENABLE
#    include "via.h"
#endif
#ifdef DIP_SWITCH_ENABLE
#    include "dip_switch.h"
#endif
#ifdef EEPROM_DRIVER
#    include "eeprom_driver.h"
#endif
#if defined(CRC_ENABLE)
#    include "crc.h"
#endif
#ifdef VIRTSER_ENABLE
#    include "virtser.h"
#endif
#ifdef SLEEP_LED_ENABLE
#    include "sleep_led.h"
#endif
#ifdef SPLIT_KEYBOARD
#    include "split_util.h"
#endif
#ifdef BATTERY_ENABLE
#    include "battery.h"
#endif
#ifdef BLUETOOTH_ENABLE
#    include "bluetooth.h"
#endif
#ifdef CAPS_WORD_ENABLE
#    include "caps_word.h"
#endif
#ifdef LEADER_ENABLE
#    include "leader.h"
#endif
#ifdef UNICODE_COMMON_ENABLE
#    include "unicode.h"
#endif
#ifdef WPM_ENABLE
#    include "wpm.h"
#endif
#ifdef OS_DETECTION_ENABLE
#    include "os_detection.h"
#endif
#ifdef LAYER_LOCK_ENABLE
#    include "layer_lock.h"
#endif
#ifdef CONNECTION_ENABLE
#    include "connection.h"
#endif

static uint32_t last_input_modification_time = 0;
uint32_t        last_input_activity_time(void) {
    return last_input_modification_time;
}
uint32_t last_input_activity_elapsed(void) {
    return sync_timer_elapsed32(last_input_modification_time);
}

static uint32_t last_matrix_modification_time = 0;
uint32_t        last_matrix_activity_time(void) {
    return last_matrix_modification_time;
}
uint32_t last_matrix_activity_elapsed(void) {
    return sync_timer_elapsed32(last_matrix_modification_time);
}
void last_matrix_activity_trigger(void) {
    last_matrix_modification_time = last_input_modification_time = sync_timer_read32();
}

static uint32_t last_encoder_modification_time = 0;
uint32_t        last_encoder_activity_time(void) {
    return last_encoder_modification_time;
}
uint32_t last_encoder_activity_elapsed(void) {
    return sync_timer_elapsed32(last_encoder_modification_time);
}
void last_encoder_activity_trigger(void) {
    last_encoder_modification_time = last_input_modification_time = sync_timer_read32();
}

static uint32_t last_pointing_device_modification_time = 0;
uint32_t        last_pointing_device_activity_time(void) {
    return last_pointing_device_modification_time;
}
uint32_t last_pointing_device_activity_elapsed(void) {
    return sync_timer_elapsed32(last_pointing_device_modification_time);
}
void last_pointing_device_activity_trigger(void) {
    last_pointing_device_modification_time = last_input_modification_time = sync_timer_read32();
}

void set_activity_timestamps(uint32_t matrix_timestamp, uint32_t encoder_timestamp, uint32_t pointing_device_timestamp) {
    last_matrix_modification_time          = matrix_timestamp;
    last_encoder_modification_time         = encoder_timestamp;
    last_pointing_device_modification_time = pointing_device_timestamp;
    last_input_modification_time           = MAX(matrix_timestamp, MAX(encoder_timestamp, pointing_device_timestamp));
}

// Only enable this if console is enabled to print to
#if defined(DEBUG_MATRIX_SCAN_RATE)
static uint32_t matrix_timer           = 0;
static uint32_t matrix_scan_count      = 0;
static uint32_t last_matrix_scan_count = 0;

void matrix_scan_perf_task(void) {
    matrix_scan_count++;

    uint32_t timer_now = timer_read32();
    if (TIMER_DIFF_32(timer_now, matrix_timer) >= 1000) {
#    if defined(CONSOLE_ENABLE)
        dprintf("matrix scan frequency: %lu\n", matrix_scan_count);
#    endif
        last_matrix_scan_count = matrix_scan_count;
        matrix_timer           = timer_now;
        matrix_scan_count      = 0;
    }
}

uint32_t get_matrix_scan_rate(void) {
    return last_matrix_scan_count;
}
#else
#    define matrix_scan_perf_task()
#endif

#ifdef MATRIX_HAS_GHOST
static matrix_row_t get_real_keys(uint8_t row, matrix_row_t rowdata) {
    matrix_row_t out = 0;
    for (uint8_t col = 0; col < MATRIX_COLS; col++) {
        // read each key in the row data and check if the keymap defines it as a real key
        if (keycode_at_keymap_location(0, row, col) && (rowdata & (((matrix_row_t)1) << col))) {
            // this creates new row data, if a key is defined in the keymap, it will be set here
            out |= ((matrix_row_t)1) << col;
        }
    }
    return out;
}

static inline bool popcount_more_than_one(matrix_row_t rowdata) {
    rowdata &= rowdata - 1; // if there are less than two bits (keys) set, rowdata will become zero
    return rowdata;
}

static inline bool has_ghost_in_row(uint8_t row, matrix_row_t rowdata) {
    /* No ghost exists when less than 2 keys are down on the row.
    If there are "active" blanks in the matrix, the key can't be pressed by the user,
    there is no doubt as to which keys are really being pressed.
    The ghosts will be ignored, they are KC_NO.   */
    rowdata = get_real_keys(row, rowdata);
    if ((popcount_more_than_one(rowdata)) == 0) {
        return false;
    }
    /* Ghost occurs when the row shares a column line with other row,
    and two columns are read on each row. Blanks in the matrix don't matter,
    so they are filtered out.
    If there are two or more real keys pressed and they match columns with
    at least two of another row's real keys, the row will be ignored. Keep in mind,
    we are checking one row at a time, not all of them at once.
    */
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        if (i != row && popcount_more_than_one(get_real_keys(i, matrix_get_row(i)) & rowdata)) {
            return true;
        }
    }
    return false;
}

#else

static inline bool has_ghost_in_row(uint8_t row, matrix_row_t rowdata) {
    return false;
}

#endif

/** \brief matrix_setup
 *
 * FIXME: needs doc
 */
__attribute__((weak)) void matrix_setup(void) {}

/** \brief keyboard_pre_init_user
 *
 * FIXME: needs doc
 */
__attribute__((weak)) void keyboard_pre_init_user(void) {}

/** \brief keyboard_pre_init_kb
 *
 * FIXME: needs doc
 */
__attribute__((weak)) void keyboard_pre_init_kb(void) {
    keyboard_pre_init_user();
}

/** \brief keyboard_pre_init_modules
 *
 * FIXME: needs doc
 */
__attribute__((weak)) void keyboard_pre_init_modules(void) {}

/** \brief keyboard_pre_init_quantum
 *
 * FIXME: needs doc
 */
void keyboard_pre_init_quantum(void) {
    keyboard_pre_init_modules();
    keyboard_pre_init_kb();
}

/** \brief keyboard_post_init_user
 *
 * FIXME: needs doc
 */

__attribute__((weak)) void keyboard_post_init_user(void) {}

/** \brief keyboard_post_init_kb
 *
 * FIXME: needs doc
 */

__attribute__((weak)) void keyboard_post_init_kb(void) {
    keyboard_post_init_user();
}

/** \brief keyboard_post_init_modules
 *
 * FIXME: needs doc
 */

__attribute__((weak)) void keyboard_post_init_modules(void) {}

/** \brief keyboard_post_init_quantum
 *
 * FIXME: needs doc
 */

void keyboard_post_init_quantum(void) {
    keyboard_post_init_modules();
    keyboard_post_init_kb();
}

/** \brief matrix_can_read
 *
 * Allows overriding when matrix scanning operations should be executed.
 */
__attribute__((weak)) bool matrix_can_read(void) {
    return true;
}

/** \brief keyboard_setup
 *
 * FIXME: needs doc
 */
void keyboard_setup(void) {
    print_set_sendchar(sendchar);
#ifdef EEPROM_DRIVER
    eeprom_driver_init();
#endif
    matrix_setup();
    keyboard_pre_init_quantum();
}

#ifndef SPLIT_KEYBOARD

/** \brief is_keyboard_master
 *
 * FIXME: needs doc
 */
__attribute__((weak)) bool is_keyboard_master(void) {
    return true;
}

/** \brief is_keyboard_left
 *
 * FIXME: needs doc
 */
__attribute__((weak)) bool is_keyboard_left(void) {
    return true;
}

#endif

/** \brief should_process_keypress
 *
 * Override this function if you have a condition where keypresses processing should change:
 *   - splits where the slave side needs to process for rgb/oled functionality
 */
__attribute__((weak)) bool should_process_keypress(void) {
    return is_keyboard_master();
}

/** \brief housekeeping_task_modules
 *
 * Codegen will override this if community modules are enabled.
 * This is specific to keyboard-level functionality.
 */
__attribute__((weak)) void housekeeping_task_modules(void) {}

/** \brief housekeeping_task_kb
 *
 * Override this function if you have a need to execute code for every keyboard main loop iteration.
 * This is specific to keyboard-level functionality.
 */
__attribute__((weak)) void housekeeping_task_kb(void) {}

/** \brief housekeeping_task_user
 *
 * Override this function if you have a need to execute code for every keyboard main loop iteration.
 * This is specific to user/keymap-level functionality.
 */
__attribute__((weak)) void housekeeping_task_user(void) {}

/** \brief housekeeping_task
 *
 * Invokes hooks for executing code after QMK is done after each loop iteration.
 */
void housekeeping_task(void) {
    housekeeping_task_modules();
    housekeeping_task_kb();
    housekeeping_task_user();
}

/** \brief quantum_init
 *
 * Init global state
 */
void quantum_init(void) {
    /* check signature */
    if (!eeconfig_is_enabled()) {
        eeconfig_init();
    }

    /* init globals */
    eeconfig_read_debug(&debug_config);
    eeconfig_read_keymap(&keymap_config);

#ifdef BOOTMAGIC_ENABLE
    bootmagic();
#endif

    /* read here just incase bootmagic process changed its value */
    layer_state_t default_layer = (layer_state_t)eeconfig_read_default_layer();
    default_layer_set(default_layer);

    /* Also initialize layer state to trigger callback functions for layer_state */
    layer_state_set_kb((layer_state_t)layer_state);
}

/** \brief keyboard_init
 *
 * FIXME: needs doc
 */
void keyboard_init(void) {
    timer_init();
    sync_timer_init();
#ifdef VIA_ENABLE
    via_init();
#endif
#ifdef SPLIT_KEYBOARD
    split_pre_init();
#endif
#ifdef ENCODER_ENABLE
    encoder_init();
#endif
    matrix_init();
    quantum_init();
#ifdef CONNECTION_ENABLE
    connection_init();
#endif
    host_init();
    led_init_ports();
#ifdef BACKLIGHT_ENABLE
    backlight_init_ports();
#endif
#ifdef AUDIO_ENABLE
    audio_init();
#endif
#ifdef LED_MATRIX_ENABLE
    led_matrix_init();
#endif
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_init();
#endif
#if defined(UNICODE_COMMON_ENABLE)
    unicode_input_mode_init();
#endif
#if defined(CRC_ENABLE)
    crc_init();
#endif
#ifdef OLED_ENABLE
    oled_init(OLED_ROTATION_0);
#endif
#ifdef ST7565_ENABLE
    st7565_init(DISPLAY_ROTATION_0);
#endif
#ifdef PS2_MOUSE_ENABLE
    ps2_mouse_init();
#endif
#ifdef BACKLIGHT_ENABLE
    backlight_init();
#endif
#ifdef RGBLIGHT_ENABLE
    rgblight_init();
#endif
#ifdef STENO_ENABLE_ALL
    steno_init();
#endif
#if defined(NKRO_ENABLE) && defined(FORCE_NKRO)
#    pragma message "FORCE_NKRO option is now deprecated - Please migrate to NKRO_DEFAULT_ON instead."
    keymap_config.nkro = 1;
    eeconfig_update_keymap(&keymap_config);
#endif
#ifdef DIP_SWITCH_ENABLE
    dip_switch_init();
#endif
#ifdef JOYSTICK_ENABLE
    joystick_init();
#endif
#ifdef SLEEP_LED_ENABLE
    sleep_led_init();
#endif
#ifdef VIRTSER_ENABLE
    virtser_init();
#endif
#ifdef SPLIT_KEYBOARD
    split_post_init();
#endif
#ifdef POINTING_DEVICE_ENABLE
    // init after split init
    pointing_device_init();
#endif
#ifdef BATTERY_ENABLE
    battery_init();
#endif
#ifdef BLUETOOTH_ENABLE
    bluetooth_init();
#endif
#ifdef HAPTIC_ENABLE
    haptic_init();
#endif

#if defined(DEBUG_MATRIX_SCAN_RATE) && defined(CONSOLE_ENABLE)
    debug_enable = true;
#endif

    keyboard_post_init_quantum(); /* Always keep this last */
}

/** \brief key_event_task
 *
 * This function is responsible for calling into other systems when they need to respond to electrical switch press events.
 * This is differnet than keycode events as no layer processing, or filtering occurs.
 */
void switch_events(uint8_t row, uint8_t col, bool pressed) {
#if defined(LED_MATRIX_ENABLE)
    led_matrix_handle_key_event(row, col, pressed);
#endif
#if defined(RGB_MATRIX_ENABLE)
    rgb_matrix_handle_key_event(row, col, pressed);
#endif
    wakeup_matrix_handle_key_event(row, col, pressed);
}

/**
 * @brief Generates a tick event at a maximum rate of 1KHz that drives the
 * internal QMK state machine.
 */
static inline void generate_tick_event(void) {
    static uint16_t last_tick = 0;
    const uint16_t  now       = timer_read();
    if (TIMER_DIFF_16(now, last_tick) != 0) {
        action_exec(MAKE_TICK_EVENT);
        last_tick = now;
    }
}

matrix_row_t matrix_previous[MATRIX_ROWS];

/**
 * @brief This task scans the keyboards matrix and processes any key presses
 * that occur.
 *
 * @return true Matrix did change
 * @return false Matrix didn't change
 */
static bool matrix_task(void) {
    if (!matrix_can_read()) {
        generate_tick_event();
        return false;
    }

    matrix_scan();
    bool matrix_changed = false;
    for (uint8_t row = 0; row < MATRIX_ROWS && !matrix_changed; row++) {
        matrix_changed |= matrix_previous[row] ^ matrix_get_row(row);
    }

    matrix_scan_perf_task();

    // Short-circuit the complete matrix processing if it is not necessary
    if (!matrix_changed) {
        generate_tick_event();
        return matrix_changed;
    }

    if (debug_config.matrix) {
        matrix_print();
    }

    const bool process_keypress = should_process_keypress();

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        const matrix_row_t current_row = matrix_get_row(row);
        const matrix_row_t row_changes = current_row ^ matrix_previous[row];

        if (!row_changes || has_ghost_in_row(row, current_row)) {
            continue;
        }

        matrix_row_t col_mask = 1;
        for (uint8_t col = 0; col < MATRIX_COLS; col++, col_mask <<= 1) {
            if (row_changes & col_mask) {
                const bool key_pressed = current_row & col_mask;

                if (process_keypress && !keypress_is_wakeup_key(row, col)) {
                    action_exec(MAKE_KEYEVENT(row, col, key_pressed));
                }

                switch_events(row, col, key_pressed);
            }
        }

        matrix_previous[row] = current_row;
    }

    return matrix_changed;
}

/** \brief Tasks previously located in matrix_scan_quantum
 *
 * TODO: rationalise against keyboard_task and current split role
 */
void quantum_task(void) {
#ifdef SPLIT_KEYBOARD
    // some tasks should only run on master
    if (!is_keyboard_master()) return;
#endif

#ifdef AUDIO_ENABLE
    audio_task();
#endif

#if defined(AUDIO_ENABLE) && !defined(NO_MUSIC_MODE)
    music_task();
#endif

#ifdef KEY_OVERRIDE_ENABLE
    key_override_task();
#endif

#ifdef SEQUENCER_ENABLE
    sequencer_task();
#endif

#ifdef TAP_DANCE_ENABLE
    tap_dance_task();
#endif

#ifdef COMBO_ENABLE
    combo_task();
#endif

#ifdef LEADER_ENABLE
    leader_task();
#endif

#ifdef WPM_ENABLE
    decay_wpm();
#endif

#ifdef DIP_SWITCH_ENABLE
    dip_switch_task();
#endif

#ifdef AUTO_SHIFT_ENABLE
    autoshift_matrix_scan();
#endif

#ifdef CAPS_WORD_ENABLE
    caps_word_task();
#endif

#ifdef SECURE_ENABLE
    secure_task();
#endif

#ifdef LAYER_LOCK_ENABLE
    layer_lock_task();
#endif

    host_task();
}

/** \brief Main task that is repeatedly called as fast as possible. */
void keyboard_task(void) {
    __attribute__((unused)) bool activity_has_occurred = false;
    if (matrix_task()) {
        last_matrix_activity_trigger();
        activity_has_occurred = true;
    }

    quantum_task();

#if defined(SPLIT_WATCHDOG_ENABLE)
    split_watchdog_task();
#endif

#if defined(RGBLIGHT_ENABLE)
    rgblight_task();
#endif

#ifdef LED_MATRIX_ENABLE
    led_matrix_task();
#endif
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_task();
#endif

#if defined(BACKLIGHT_ENABLE)
#    if defined(BACKLIGHT_PIN) || defined(BACKLIGHT_PINS)
    backlight_task();
#    endif
#endif

#ifdef ENCODER_ENABLE
    if (encoder_task()) {
        last_encoder_activity_trigger();
        activity_has_occurred = true;
    }
#endif

#ifdef POINTING_DEVICE_ENABLE
    if (pointing_device_task()) {
        last_pointing_device_activity_trigger();
        activity_has_occurred = true;
    }
#endif

#ifdef OLED_ENABLE
    oled_task();
#    if OLED_TIMEOUT > 0
    // Wake up oled if user is using those fabulous keys or spinning those encoders!
    if (activity_has_occurred) oled_on();
#    endif
#endif

#ifdef ST7565_ENABLE
    st7565_task();
#    if ST7565_TIMEOUT > 0
    // Wake up display if user is using those fabulous keys or spinning those encoders!
    if (activity_has_occurred) st7565_on();
#    endif
#endif

#ifdef MOUSEKEY_ENABLE
    // mousekey repeat & acceleration
    mousekey_task();
#endif

#ifdef PS2_MOUSE_ENABLE
    ps2_mouse_task();
#endif

#ifdef MIDI_ENABLE
    midi_task();
#endif

#ifdef JOYSTICK_ENABLE
    joystick_task();
#endif

#ifdef BATTERY_ENABLE
    battery_task();
#endif

#ifdef BLUETOOTH_ENABLE
    bluetooth_task();
#endif

#ifdef HAPTIC_ENABLE
    haptic_task();
#endif

    led_task();

#ifdef OS_DETECTION_ENABLE
    os_detection_task();
#endif
}
