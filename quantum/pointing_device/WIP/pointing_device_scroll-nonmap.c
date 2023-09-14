/* Copyright 2022 Alabastard
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

#ifdef POINTING_DEVICE_SCROLL_ENABLE

#    include "pointing_device_scroll.h"

/* initialize static functions */

/* duplication of inline function from pointing_device.c */
static inline int8_t pointing_device_hv_clamp(mouse_xy_report_t value) {
    if (value < INT8_MIN) {
        return INT8_MIN;
    } else if (value > INT8_MAX) {
        return INT8_MAX;
    } else {
        return value;
    }
}

static report_mouse_t process_scroll_mode(scroll_status_t scroll_status, report_mouse_t mouse_report);

// set up context and functions if using two pointing devices
#    if defined(SPLIT_POINTING_ENABLE) && defined(POINTING_DEVICE_COMBINED)
/* set up local context for storing current values */
static scroll_context_t scroll_context = {config.is_left = SCROLL_LEFT_SIDE_DEFAULT, .config.tg_mode = SCROLL_MODE_DEFAULT, .status.mode = SCROLL_MODE_DEFAULT};

/**
 * @brief Check if left side is controlled by scroll mode
 *
 * @return is left side active [bool]
 */
bool is_scroll_mode_left(void) {
    return scroll_context.config.is_left;
}

/**
 * @brief Allow changing of active side
 *
 * will change which side (left/right) is controlled by scroll mode
 */
void scroll_mode_switch_hands() {
    scroll_context.config.is_left ^= 1;
}
#    else
static scroll_context_t scroll_context = {.config.tg_mode = SCROLL_MODE_DEFAULT, .status.mode = SCROLL_MODE_DEFAULT};
#    endif

/**
 * @brief Reset scroll data
 *
 *  Clear scroll status and set to defaults
 */
static void scroll_reset(void) {
    memset(&scroll_context.status, 0, sizeof(scroll_status_t));
    scroll_context.status.mode = scroll_context.config.tg_mode;
}

/**
 * @brief set local stored scroll status
 *
 * NOTE: Will ensure non 0 divisor is set
 *
 * @param[in] scroll_status scroll_status_t
 */
void set_scroll_status(scroll_status_t scroll_status) {
    memcpy(&scroll_context.status, &scroll_status, sizeof(scroll_status_t));
}

/**
 * @brief access active scroll record
 *
 * @return uint8_t active scroll record
 */
uint8_t get_scroll_mode(void) {
    return scroll_context.status.mode;
}

/**
 * @brief set scroll record scroll mode
 *
 * @param[in] scroll_mode uint8_t
 */
void set_scroll_mode(uint8_t scroll_mode) {
    if (scroll_context.status.mode != scroll_mode) {
        scroll_reset();
        scroll_context.status.mode = scroll_mode;
        dprintf("Scroll Mode Set: %d\n", scroll_mode);
    }
}

/**
 * @brief Toggle scroll_mode
 *
 * Will change tg_mode setting to SCROLL_MODE_DEFAULT if on and
 *
 * @param[in] scroll_mode uint8_t
 */
void scroll_mode_toggle(uint8_t scroll_mode) {
    if (scroll_context.config.tg_mode == scroll_mode) {
        scroll_context.config.tg_mode = SCROLL_MODE_DEFAULT;
    } else {
        scroll_context.config.tg_mode = scroll_mode;
    }
    if (get_scroll_mode() != scroll_context.config.tg_mode) scroll_reset();
}

/**
 * @brief access current toggled scroll mode
 *
 * @return uint8_t toggle scroll mode
 */
uint8_t get_scroll_mode_toggle(void) {
    return scroll_context.config.tg_mode;
}

/**
 * @brief Weak function to convert x/y axes to h/v
 *
 * The default uses accumulation based on inversion defines and
 * halts cursor movement
 *
 * @params scroll_status[in] scroll_status_t
 * @params mouse_report[in]  report_mouse_t
 *
 * @return updated mouse_report report_mouse_t
 */
__attribute__((weak)) report_mouse_t scroll_conversion(scroll_status_t scroll_status, report_mouse_t mouse_report) {
#    ifdef POINTING_DEVICE_INVERT_H
    scroll_status.h -= mouse_report.x;
#    else
    scroll_status.h += mouse_report.x;
#    endif
#    ifdef POINTING_DEVICE_INVERT_V
    scroll_status.v -= mouse_report.y;
#    else
    scroll_status.v += mouse_report.y;
#    endif
    set_scroll_status(scroll_status);
    mouse_report.x = 0;
    mouse_report.y = 0;
    return mouse_report;
}

/**
 * @brief Tap keycodes based on scroll input
 *
 * Will translate scroll h & v input into keycode taps.
 * Uses vim arrow ordered input (LEFT, DOWN, UP, RIGHT) and will output 1 keytap/divisor
 *
 * NOTE: favours staying on axis and weakly favours the horizontal over the vertical axis
 *
 * @params kc_h_neg[in] uint16_t negative h keycode (LEFT)
 * @params kc_v_neg[in] uint16_t negative v keycode (DOWN)
 * @params kc_v_pos[in] uint16_t positive v keycode (UP)
 * @params kc_h_pos[in] uint16_t positive h keycode (RIGHT)
 * @params scroll_status[in]  scroll_status_t current scroll status
 */
void scroll_tap_codes(uint16_t st_kc_left, uint16_t st_kc_down, uint16_t st_kc_up, uint16_t st_kc_right, uint8_t divisor) {
    // avoid div by 0
    if (!divisor) divisor = 1;
    // Ensure larger than divisor before commiting key presses
    if (abs(scroll_context.status.h) > abs(scroll_context.status.v)) {
        // Horizontal handling (RIGHT/LEFT)
        if (scroll_context.status.h > divisor) {
            uint16_t taps = (uint16_t)abs(scroll_context.status.h) / divisor;
            // RIGHT
            for (uint16_t i = 0; i < taps; i++) {
                tap_code16_delay(st_kc_right, SCROLL_TAP_DELAY);
                scroll_context.status.h -= divisor;
            }
            scroll_context.status.v = 0;
        } else {
            uint16_t taps = (uint16_t)abs(scroll_context.status.h) / divisor;
            // LEFT
            for (uint16_t i = 0; i < taps; i++) {
                tap_code16_delay(st_kc_left, SCROLL_TAP_DELAY);
                scroll_context.status.h += divisor;
            }
            scroll_context.status.v = 0;
        }
    } else {
        // Vertical handling (UP/DOWN)
        if (scroll_context.status.v > divisor) {
            uint16_t taps = (uint16_t)abs(scroll_context.status.v) / divisor;
            // UP
            for (uint16_t i = 0; i < taps; i++) {
                tap_code16_delay(st_kc_up, SCROLL_TAP_DELAY);
                scroll_context.status.v -= divisor;
            }
            scroll_context.status.h = 0;
        } else {
            uint16_t taps = (uint16_t)abs(scroll_context.status.v) / divisor;
            // DOWN
            for (uint16_t i = 0; i < taps; i++) {
                tap_code16_delay(st_kc_down, SCROLL_TAP_DELAY);
                scroll_context.status.v += divisor;
            }
            scroll_context.status.h = 0;
        }
    }
}

/**
 * @brief Core function to initiate scroll mode process
 *
 * Meant to be implemented in pointing_device_task
 *
 * @param[in] mouse_report report_mouse_t
 *
 * @return mouse_report report_mouse_t
 */
report_mouse_t pointing_device_task_scroll(report_mouse_t mouse_report) {
    // skip all processing if scroll_mode is SM_NONE
    if (get_scroll_mode() == SM_NONE) return mouse_report;

    mouse_report = scroll_conversion(scroll_context.status, mouse_report);
    mouse_report = process_scroll_mode(scroll_context.status, mouse_report);

    return mouse_report;
}

/**
 * @brief Handle processing of scroll modes
 *
 * Takes in report_mouse_t and scroll_status_t allowing manipulation of mouse_report
 * and scroll_status via set_scroll_status
 */
static report_mouse_t process_scroll_mode(scroll_status_t scroll_status, report_mouse_t mouse_report) {
    switch (scroll_status.mode) {
        // Drag scroll mode (sets scroll axes to mouse_report h & v)
        case SM_DRAG:
            mouse_report.h = scroll_status.h / SCROLL_DRAG_DIVISOR;
            mouse_report.v = scroll_status.v / SCROLL_DRAG_DIVISOR;
            scroll_status.v -= (int16_t)mouse_report.v * SCROLL_DRAG_DIVISOR;
            scroll_status.h -= (int16_t)mouse_report.h * SCROLL_DRAG_DIVISOR;
            set_scroll_status(scroll_status);
            break;
        // Caret scroll mode (uses arrow keys to move cursor)
        case SM_CARET:
            scroll_tap_codes(KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, SCROLL_CARET_DIVISOR);
            break;
/*
#    ifdef EXTRAKEY_ENABLE
        // Volume scroll mode (adjusts audio volume)
        case SM_VOLUME:
            scroll_tap_codes(KC_NO, KC_VOLD, KC_VOLU, KC_NO, SCROLL_VOL_DIVISOR);
            break;
#    endif
*/
    }
    return process_scroll_mode_kb(scroll_status, mouse_report);
}

/**
 * @brief Handle scroll_mode keypress: Momentary
 *
 * Will set scroll mode when key is pressed and reset scroll mode
 * on release
 *
 * NOTE: if scroll mode has changed since key down reset is skipped
 *
 * @params scroll_mode[in] uint8_t
 * @params record[in] keyrecord_t* pointer
 */
void scroll_key_momentary(uint8_t scroll_mode, keyrecord_t* record) {
    if (record->event.pressed) {
        // blindly set mode
        set_scroll_mode(scroll_mode);
    } else {
        // reset scroll mode only if the active mode matches (in case mode has switched before release)
        if (get_scroll_mode() == scroll_mode) scroll_reset();
    }
}
/**
 * @brief Handle scroll_mode keypress: Toggle
 *
 * Toggle scroll mode on key release
 *
 * @params scroll_mode[in] uint8_t
 * @params record[in] keyrecord_t* pointer
 */
void scroll_key_toggle(uint8_t scroll_mode, keyrecord_t* record) {
    if (!record->event.pressed) scroll_mode_toggle(scroll_mode);
}

/**
 * @brief Core function to process scroll mode key records
 *
 * Only handles built in keyrecords and functions
 *
 * @params keycode[in] uint16_t
 * @params record[in] keyrecord_t pointer
 *
 * @return should keycode processing continue bool
 */
bool process_record_scroll(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        // handle built in keycods for bottom 16 scroll modes
        // momentary
        case SCROLL_MO_START ... SCROLL_MO_END:
            scroll_key_momentary((keycode - SCROLL_MO_START) & 0x0f, record);
            return true; // allow further processing
        // toggle
        case SCROLL_TG_START ... SCROLL_TG_END:
            scroll_key_toggle((keycode - SCROLL_TG_START) & 0x0f, record);
            return true; // allow further processing

        default:
            return true;
    }
}

/**
 * @brief Weak function for user level adding of scroll modes
 *
 * Takes scroll_status_t struct, and report_mouse_t sctruct and returns a
 * report_mouse_t allowing updating of both scroll_satus (using
 * set_scroll_status) and mouse_report
 *
 * @params scroll_status[in] scroll_status_t
 * @params mouse_report[in] report_mouse_t
 *
 * @return mouse_report report_mouse_t
 */
__attribute__((weak)) report_mouse_t process_scroll_mode_user(scroll_status_t scroll_status, report_mouse_t mouse_report) {
    return mouse_report;
}

/**
 * @brief Weak function for keyboard level adding of scroll modes
 *
 * Takes scroll_status_t struct, and report_mouse_t sctruct and returns a
 * report_mouse_t allowing updating of both scroll_satus (using
 * set_scroll_status) and mouse_report
 *
 * @params scroll_status[in] scroll_status_t
 * @params mouse_report[in] report_mouse_t
 *
 * @return mouse_report report_mouse_t
 */
__attribute__((weak)) report_mouse_t process_scroll_mode_kb(scroll_status_t scroll_status, report_mouse_t mouse_report) {
    return process_scroll_mode_user(scroll_status, mouse_report);
}

#endif // POINTING_DEVICE_SCROLL_ENABLE
