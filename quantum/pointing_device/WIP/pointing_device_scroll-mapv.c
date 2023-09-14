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

/* duplication of local inline function from pointing_device.c */
static inline int8_t pointing_device_hv_clamp(mouse_xy_report_t value) {
    if (value < INT8_MIN) {
        return INT8_MIN;
    } else if (value > INT8_MAX) {
        return INT8_MAX;
    } else {
        return value;
    }
}

static report_mouse_t process_scroll_mode(status_scroll_t scroll_status, report_mouse_t mouse_report);
static uint8_t get_scroll_direction(void);
static uint8_t get_scroll_divisor(void);

// set up context and functions if using two pointing devices
#    if defined(SPLIT_POINTING_ENABLE) && defined(POINTING_DEVICE_COMBINED)
/* set up local context for storing current values */
static context_scroll_t scroll_context = {.config.is_left = SCROLL_LEFT_SIDE_DEFAULT, .config.tg_mode = SCROLL_MODE_DEFAULT, .status.mode = SCROLL_MODE_DEFAULT};

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
void scroll_mode_switch_hands(void) {
    scroll_context.config.is_left ^= 1;
}
#    else
static context_scroll_t scroll_context = {.config.tg_mode = SCROLL_MODE_DEFAULT, .status.mode = SCROLL_MODE_DEFAULT};
#    endif

/**
 * @brief Reset scroll data
 *
 *  Clear scroll status and set to defaults
 */
static void scroll_reset(void) {
    memset(&scroll_context.status, 0, sizeof(status_scroll_t));
    scroll_context.status.mode = scroll_context.config.tg_mode;
}

/**
 * @brief set local stored scroll status
 *
 * NOTE: Will ensure non 0 divisor is set
 *
 * @param[in] scroll_status status_scroll_t
 */
void set_scroll_status(status_scroll_t scroll_status) {
    memcpy(&scroll_context.status, &scroll_status, sizeof(status_scroll_t));
}

/**
 * @brief local function to get direction based on h/v
 *
 * Determines direction based on axis with largest magnitude
 * 
 * NOTE: Defaults to SCROLL_DOWN
 *
 * @return direction uint8_t
 */
static uint8_t get_scroll_direction(void) {
    if (abs(scroll_context.status.h) > abs(scroll_context.status.v)) {
        if (scroll_context.status.h > 0) {
            return SCROLL_RIGHT;
        } else {
            return SCROLL_LEFT;
        }
    } else {
        if (scroll_context.status.v > 0) {
            return SCROLL_UP;
        } else {
            return SCROLL_DOWN;
        }
    }
}

/**
 * @brief local function to get scroll divisor
 *
 * Will handle default divisors and call weak kb and user functions
 * 
 * NOTE: Expects that scroll mode and direction has been updated
 *
 * @return divisor uint8_t
 */
static uint8_t get_scroll_divisor(void) {
    // check for keyboard and user overrides
    uint8_t divisor = get_scroll_divisor_kb(scroll_context.status.mode, scroll_context.status.direction);
    if (divisor) ][kreturn divisor;
    
    switch(scroll_context.status.mode) {
            
        case SM_CARET:
            divisor = scroll_context.status.direction < SCROLL_LEFT ? SCROLL_CARET_DIVISOR_V : SCROLL_CARET_DIVISOR_H;
            break;
    }
    
    if (!divisor) divisor = SCROLL_DEFAULT_DIVISOR;
    
    return divisor;
}

/**
 * @brief update dependent parameters of scroll_status
 * 
 * Will update the direction and divisor values based on scroll mode and h, and v axis values
 * 
 */
void update_scroll_status(void) {
    scroll_context.status.direction = get_scroll_direction();
    scroll_context.status.divisor   = get_scroll_divisor();
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
 * @params scroll_status[in] status_scroll_t
 * @params mouse_report[in]  report_mouse_t
 *
 * @return updated mouse_report report_mouse_t
 */
__attribute__((weak)) report_mouse_t scroll_conversion(status_scroll_t scroll_status, report_mouse_t mouse_report) {
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
 * @brief Tap keycodes based on scroll axis values
 *
 * Will translate scroll h & v input into keycode taps.
 * Uses input ordered {DOWN, UP, LEFT, RIGHT} and will output 1 keytap/divisor
 * and updating the h and v values.
 *
 * NOTE: favours staying on axis and weakly favours the horizontal over the vertical axis
 *
 * @param scroll_keycodes uint16_t array format {kc_down, kc_up, kc_left, kc_right}
 */
void scroll_tap_codes(uint16_t kc_left, uint16_t kc_down, uint16_t kc_up, uint16_t kc_right) {
    
    uint16_t scroll_keycode = 0;
    int16_t  count          = 0;
    
    switch(scroll_context.status.direction) {
    
        case SCROLL_DOWN:
            scroll_keycode = kc_down;
        case SCROLL_UP:
            if (!scroll_keycode) scroll_keycode = kc_up;
            count = scroll_context.status.v / scroll_context.status.divisor;
            if (count) {
                scroll_context.status.h = count * (int16_t)scroll_context.status.divisor;
                scroll_context.status.v = 0;
            } else {
                return;
            }
            break;
            
        case SCROLL_LEFT:
            scroll_keycode = kc_left;
        case SCROLL_RIGHT:
            if (!scroll_keycode) scroll_keycode = kc_right;
            count = scroll_context.status.h / scroll_context.status.divisor;
            if (count) {
                scroll_context.status.h = 0;
                scroll_context.status.v = count * (int16_t)scroll_context.status.divisor;
            } else {
                return;
            }
            break;
    }
    uint8_t taps = (uint8_t)abs(count);    
    for (uint8_t i = 0; i < taps; i++) {
        tap_code16_delay(scroll_keycode, SCROLL_TAP_DELAY);
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
    update_scroll_status();
    mouse_report = process_scroll_mode(scroll_context.status, mouse_report);

    return mouse_report;
}

/**
 * @brief Handle processing of scroll modes
 *
 * Takes in report_mouse_t and status_scroll_t allowing manipulation of mouse_report
 * and scroll_status via set_scroll_status
 */
static report_mouse_t process_scroll_mode(status_scroll_t scroll_status, report_mouse_t mouse_report) {
    switch (scroll_status.mode) {
        // Drag scroll mode (sets scroll axes to mouse_report h & v)
        case SM_DRAG:
            mouse_report.h = scroll_status.h / SCROLL_DRAG_DIVISOR_H;
            mouse_report.v = scroll_status.v / SCROLL_DRAG_DIVISOR_V;
            
            scroll_status.v -= mouse_report.v * SCROLL_DRAG_DIVISOR_H;
            scroll_status.h -= mouse_report.h * SCROLL_DRAG_DIVISOR_V;
            
            set_scroll_status(scroll_status);
            break;
            
        // Caret scroll mode (uses arrow keys to move cursor)
        case SM_CARET:
            scroll_tap_codes(KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT);
            break;
        
        default:
#    ifdef SCROLL_MODE_MAP_ENABLE
            scroll_tap_codes(SCROLL_MODE_MAP);
#    endif
            break;
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
            scroll_key_momentary((keycode - SCROLL_MO_START) & 0x1f, record);
            return true; // allow further processing
        // toggle
        case SCROLL_TG_START ... SCROLL_TG_END:
            scroll_key_toggle((keycode - SCROLL_TG_START) & 0x1f, record);
            return true; // allow further processing
        // end
        default:
            return true;
    }
}

/**
 * @brief Weak function for user level adding of scroll modes
 *
 * Takes status_scroll_t struct, and report_mouse_t sctruct and returns a
 * report_mouse_t allowing updating of both scroll_satus (using
 * set_scroll_status) and mouse_report
 *
 * @params scroll_status[in] status_scroll_t
 * @params mouse_report[in] report_mouse_t
 *
 * @return mouse_report report_mouse_t
 */
__attribute__((weak)) report_mouse_t process_scroll_mode_user(status_scroll_t scroll_status, report_mouse_t mouse_report) {
    return mouse_report;
}

/**
 * @brief Weak function for keyboard level adding of scroll modes
 *
 * Takes status_scroll_t struct, and report_mouse_t sctruct and returns a
 * report_mouse_t allowing updating of both scroll_satus (using
 * set_scroll_status) and mouse_report
 *
 * @params scroll_status[in] status_scroll_t
 * @params mouse_report[in] report_mouse_t
 *
 * @return mouse_report report_mouse_t
 */
__attribute__((weak)) report_mouse_t process_scroll_mode_kb(status_scroll_t scroll_status, report_mouse_t mouse_report) {
    return process_scroll_mode_user(scroll_status, mouse_report);
}

/**
 * @brief Weak function for user level adding of scroll_mode divisors
 *
 * Takes in scroll_mode and direction allowing for divisor values to be
 * determined based on these parameters
 *
 * @params scroll_mode[in] uint8_t
 * @params direction[in] uint8_t
 *
 * @return divisor uint8_t
 */
__attribute__((weak)) uint8_t get_scroll_divisor_user(uint8_t scroll_mode, uint8_t direction) {
    return 0; // continue processing
}

/**
 * @brief Weak function for user level adding of scroll_mode divisors
 *
 * Takes in scroll_mode and direction allowing for divisor values to be
 * determined based on these parameters
 *
 * @params scroll_mode[in] uint8_t
 * @params direction[in] uint8_t
 *
 * @return divisor uint8_t
 */
__attribute__((weak)) uint8_t get_scroll_divisor_kb(uint8_t scroll_mode, uint8_t direction) {
    return get_scroll_divisor_user(scroll_mode, direction);
}

#endif // POINTING_DEVICE_SCROLL_ENABLE
