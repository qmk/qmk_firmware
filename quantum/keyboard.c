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
#include "quantum.h"
#include "keyboard.h"
#include "matrix.h"
#include "keymap.h"
#include "magic.h"
#include "host.h"
#include "led.h"
#include "keycode.h"
#include "timer.h"
#include "sync_timer.h"
#include "print.h"
#include "debug.h"
#include "command.h"
#include "util.h"
#include "sendchar.h"
#include "eeconfig.h"
#include "action_layer.h"
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
#ifdef STENO_ENABLE
#    include "process_steno.h"
#endif
#ifdef POINTING_DEVICE_ENABLE
#    include "pointing_device.h"
#endif
#ifdef MIDI_ENABLE
#    include "process_midi.h"
#endif
#ifdef JOYSTICK_ENABLE
#    include "process_joystick.h"
#endif
#ifdef PROGRAMMABLE_BUTTON_ENABLE
#    include "programmable_button.h"
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
#ifdef VELOCIKEY_ENABLE
#    include "velocikey.h"
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
#ifdef DIGITIZER_ENABLE
#    include "digitizer.h"
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
#ifdef BLUETOOTH_ENABLE
#    include "outputselect.h"
#endif

static uint32_t last_input_modification_time = 0;
uint32_t        last_input_activity_time(void) {
    return last_input_modification_time;
}
uint32_t last_input_activity_elapsed(void) {
    return timer_elapsed32(last_input_modification_time);
}

static uint32_t last_matrix_modification_time = 0;
uint32_t        last_matrix_activity_time(void) {
    return last_matrix_modification_time;
}
uint32_t last_matrix_activity_elapsed(void) {
    return timer_elapsed32(last_matrix_modification_time);
}
void last_matrix_activity_trigger(void) {
    last_matrix_modification_time = last_input_modification_time = timer_read32();
}

static uint32_t last_encoder_modification_time = 0;
uint32_t        last_encoder_activity_time(void) {
    return last_encoder_modification_time;
}
uint32_t last_encoder_activity_elapsed(void) {
    return timer_elapsed32(last_encoder_modification_time);
}
void last_encoder_activity_trigger(void) {
    last_encoder_modification_time = last_input_modification_time = timer_read32();
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
extern const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS];
static matrix_row_t   get_real_keys(uint8_t row, matrix_row_t rowdata) {
    matrix_row_t out = 0;
    for (uint8_t col = 0; col < MATRIX_COLS; col++) {
        // read each key in the row data and check if the keymap defines it as a real key
        if (pgm_read_byte(&keymaps[0][row][col]) && (rowdata & (1 << col))) {
            // this creates new row data, if a key is defined in the keymap, it will be set here
            out |= 1 << col;
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

#endif

void disable_jtag(void) {
// To use PF4-7 (PC2-5 on ATmega32A), disable JTAG by writing JTD bit twice within four cycles.
#if (defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB647__) || defined(__AVR_AT90USB1286__) || defined(__AVR_AT90USB1287__) || defined(__AVR_ATmega16U4__) || defined(__AVR_ATmega32U4__))
    MCUCR |= _BV(JTD);
    MCUCR |= _BV(JTD);
#elif defined(__AVR_ATmega32A__)
    MCUCSR |= _BV(JTD);
    MCUCSR |= _BV(JTD);
#endif
}

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

/** \brief keyboard_post_init_user
 *
 * FIXME: needs doc
 */

__attribute__((weak)) void keyboard_post_init_user() {}

/** \brief keyboard_post_init_kb
 *
 * FIXME: needs doc
 */

__attribute__((weak)) void keyboard_post_init_kb(void) {
    keyboard_post_init_user();
}

/** \brief keyboard_setup
 *
 * FIXME: needs doc
 */
void keyboard_setup(void) {
#ifndef NO_JTAG_DISABLE
    disable_jtag();
#endif
    print_set_sendchar(sendchar);
#ifdef EEPROM_DRIVER
    eeprom_driver_init();
#endif
    matrix_setup();
    keyboard_pre_init_kb();
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
    housekeeping_task_kb();
    housekeeping_task_user();
}

/** \brief Init tasks previously located in matrix_init_quantum
 *
 * TODO: rationalise against keyboard_init and current split role
 */
void quantum_init(void) {
    magic();
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
#ifdef HAPTIC_ENABLE
    haptic_init();
#endif
#if defined(BLUETOOTH_ENABLE) && defined(OUTPUT_AUTO_ENABLE)
    set_output(OUTPUT_AUTO);
#endif
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
    matrix_init();
    quantum_init();
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
#ifdef ENCODER_ENABLE
    encoder_init();
#endif
#ifdef STENO_ENABLE
    steno_init();
#endif
#ifdef POINTING_DEVICE_ENABLE
    pointing_device_init();
#endif
#if defined(NKRO_ENABLE) && defined(FORCE_NKRO)
    keymap_config.nkro = 1;
    eeconfig_update_keymap(keymap_config.raw);
#endif
#ifdef DIP_SWITCH_ENABLE
    dip_switch_init();
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

#if defined(DEBUG_MATRIX_SCAN_RATE) && defined(CONSOLE_ENABLE)
    debug_enable = true;
#endif

    keyboard_post_init_kb(); /* Always keep this last */
}

/** \brief key_event_task
 *
 * This function is responsible for calling into other systems when they need to respond to electrical switch press events.
 * This is differnet than keycode events as no layer processing, or filtering occurs.
 */
void switch_events(uint8_t row, uint8_t col, bool pressed) {
#if defined(LED_MATRIX_ENABLE)
    process_led_matrix(row, col, pressed);
#endif
#if defined(RGB_MATRIX_ENABLE)
    process_rgb_matrix(row, col, pressed);
#endif
}

/** \brief Perform scan of keyboard matrix
 *
 * Any detected changes in state are sent out as part of the processing
 */
bool matrix_scan_task(void) {
    static matrix_row_t matrix_prev[MATRIX_ROWS];
    matrix_row_t        matrix_row    = 0;
    matrix_row_t        matrix_change = 0;
#ifdef QMK_KEYS_PER_SCAN
    uint8_t keys_processed = 0;
#endif

    uint8_t matrix_changed = matrix_scan();
    if (matrix_changed) last_matrix_activity_trigger();

    for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
        matrix_row    = matrix_get_row(r);
        matrix_change = matrix_row ^ matrix_prev[r];
        if (matrix_change) {
#ifdef MATRIX_HAS_GHOST
            if (has_ghost_in_row(r, matrix_row)) {
                continue;
            }
#endif
            if (debug_matrix) matrix_print();
            matrix_row_t col_mask = 1;
            for (uint8_t c = 0; c < MATRIX_COLS; c++, col_mask <<= 1) {
                if (matrix_change & col_mask) {
                    if (should_process_keypress()) {
                        action_exec((keyevent_t){
                            .key = (keypos_t){.row = r, .col = c}, .pressed = (matrix_row & col_mask), .time = (timer_read() | 1) /* time should not be 0 */
                        });
                    }
                    // record a processed key
                    matrix_prev[r] ^= col_mask;

                    switch_events(r, c, (matrix_row & col_mask));

#ifdef QMK_KEYS_PER_SCAN
                    // only jump out if we have processed "enough" keys.
                    if (++keys_processed >= QMK_KEYS_PER_SCAN)
#endif
                        // process a key per task call
                        goto MATRIX_LOOP_END;
                }
            }
        }
    }
    // call with pseudo tick event when no real key event.
#ifdef QMK_KEYS_PER_SCAN
    // we can get here with some keys processed now.
    if (!keys_processed)
#endif
        action_exec(TICK);

MATRIX_LOOP_END:

    matrix_scan_perf_task();
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

#if defined(AUDIO_ENABLE) && defined(AUDIO_INIT_DELAY)
    // There are some tasks that need to be run a little bit
    // after keyboard startup, or else they will not work correctly
    // because of interaction with the USB device state, which
    // may still be in flux...
    //
    // At the moment the only feature that needs this is the
    // startup song.
    static bool     delayed_tasks_run  = false;
    static uint16_t delayed_task_timer = 0;
    if (!delayed_tasks_run) {
        if (!delayed_task_timer) {
            delayed_task_timer = timer_read();
        } else if (timer_elapsed(delayed_task_timer) > 300) {
            audio_startup();
            delayed_tasks_run = true;
        }
    }
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

#ifdef WPM_ENABLE
    decay_wpm();
#endif

#ifdef HAPTIC_ENABLE
    haptic_task();
#endif

#ifdef DIP_SWITCH_ENABLE
    dip_switch_read(false);
#endif

#ifdef AUTO_SHIFT_ENABLE
    autoshift_matrix_scan();
#endif
}

/** \brief Keyboard task: Do keyboard routine jobs
 *
 * Do routine keyboard jobs:
 *
 * * scan matrix
 * * handle mouse movements
 * * handle midi commands
 * * light LEDs
 *
 * This is repeatedly called as fast as possible.
 */
void keyboard_task(void) {
    bool matrix_changed = matrix_scan_task();
    (void)matrix_changed;

    quantum_task();

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
    bool encoders_changed = encoder_read();
    if (encoders_changed) last_encoder_activity_trigger();
#endif

#ifdef OLED_ENABLE
    oled_task();
#    if OLED_TIMEOUT > 0
    // Wake up oled if user is using those fabulous keys or spinning those encoders!
#        ifdef ENCODER_ENABLE
    if (matrix_changed || encoders_changed) oled_on();
#        else
    if (matrix_changed) oled_on();
#        endif
#    endif
#endif

#ifdef ST7565_ENABLE
    st7565_task();
#    if ST7565_TIMEOUT > 0
    // Wake up display if user is using those fabulous keys or spinning those encoders!
#        ifdef ENCODER_ENABLE
    if (matrix_changed || encoders_changed) st7565_on();
#        else
    if (matrix_changed) st7565_on();
#        endif
#    endif
#endif

#ifdef MOUSEKEY_ENABLE
    // mousekey repeat & acceleration
    mousekey_task();
#endif

#ifdef PS2_MOUSE_ENABLE
    ps2_mouse_task();
#endif

#ifdef POINTING_DEVICE_ENABLE
    pointing_device_task();
#endif

#ifdef MIDI_ENABLE
    midi_task();
#endif

#ifdef VELOCIKEY_ENABLE
    if (velocikey_enabled()) {
        velocikey_decelerate();
    }
#endif

#ifdef JOYSTICK_ENABLE
    joystick_task();
#endif

#ifdef DIGITIZER_ENABLE
    digitizer_task();
#endif

#ifdef PROGRAMMABLE_BUTTON_ENABLE
    programmable_button_send();
#endif

    led_task();
}
