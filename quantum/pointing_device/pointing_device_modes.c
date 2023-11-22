/* Copyright 2023 Alabastard (@Alabastard-64)
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

#ifdef POINTING_DEVICE_MODES_ENABLE

#    include "pointing_device_modes.h"

// initialize local functions
static report_mouse_t process_pointing_mode(pointing_mode_t pointing_mode, report_mouse_t mouse_report);
static uint8_t        get_pointing_mode_direction(void);
static uint8_t        get_pointing_mode_divisor(void);
static uint8_t        divisor_postprocess(uint8_t divisor);

// local variables
#    if POINTING_MODES_DEVICE_CONTROL_COUNT > 1
static uint8_t current_device = POINTING_MODES_DEFAULT_DEVICE;
#    else
static const uint8_t current_device  = 0;
#        if defined(POINTING_MODES_SINGLE_CONTROL)
static uint8_t       selected_device = POINTING_MODES_DEFAULT_DEVICE;
#        endif
#    endif

static uint8_t         current_direction = 0;
static uint8_t         current_divisor   = POINTING_DEFAULT_DIVISOR;
static uint8_t         toggle_ids[]      = {[0 ... POINTING_MODES_DEVICE_CONTROL_COUNT - 1] = POINTING_MODE_DEFAULT};
static pointing_mode_t pointing_modes[]  = {[0 ... POINTING_MODES_DEVICE_CONTROL_COUNT - 1] = {.id = POINTING_MODE_DEFAULT}};

// set up clamping and divisor application functions
static inline int8_t clamp_int_16_to_8(int16_t value) {
    if (value < INT8_MIN) {
        return INT8_MIN;
    } else if (value > INT8_MAX) {
        return INT8_MAX;
    } else {
        return value;
    }
}

static inline int16_t clamp_int_32_to_16(int32_t value) {
    if (value < INT16_MIN) {
        return INT16_MIN;
    } else if (value > INT16_MAX) {
        return INT16_MAX;
    } else {
        return value;
    }
}

static inline uint16_t clamp_uint_16_to_8(uint16_t value) {
    if (value > UINT8_MAX) return UINT8_MAX;
    return value;
}

static int16_t divisor_multiply16(int16_t value) {
    return clamp_int_32_to_16(value * (int16_t)current_divisor);
}

static int8_t divisor_divide8(int16_t value) {
    return clamp_int_16_to_8(value / (int16_t)current_divisor);
}

static int16_t divisor_divide16(int16_t value) {
    return value / (int16_t)current_divisor;
}

/**
 * @brief divides value by current divisor return mouse x/y
 *
 * Intended for modifying pointing_mode x/y values
 *
 * @params value[in] value int16_t
 *
 * @return quotient clamped to mouse_xy_report_t range
 */
mouse_xy_report_t apply_divisor_xy(int16_t value) {
#    ifdef MOUSE_EXTENDED_REPORT
    return divisor_divide16(value);
#    else
    return divisor_divide8(value);
#    endif
}

/**
 * @brief divides value by current divisor return mouse h/v
 *
 * Intended for modifying pointing_mode x/y values
 *
 * @params value[in] value int16_t
 *
 * @return quotient clamped to int8_t range
 */
int8_t apply_divisor_hv(int16_t value) {
    return divisor_divide8(value);
}

/**
 * @brief multiplies mouse x/y value by current divisor
 *
 * Intended for collecting residuals by subtracting quotient * divisor from the dividend
 * as modulo can be large and slow on some chips
 *
 * @params value[in] value mouse_xy_report_t mouse x/y axis value to multiply
 *
 * @return product clamped to int16_t range
 */
int16_t multiply_divisor_xy(mouse_xy_report_t value) {
    return divisor_multiply16((int16_t)value);
}

/**
 * @brief multiplies mouse h/v value by current divisor
 *
 * Intended for collecting residuals by subtracting quotient * divisor from the dividend
 * as modulo can be large and slow on some chips
 *
 * @params value[in] value int8_t mouse h/v axis value to multiply
 *
 * @return modified and clamped value int16_t
 */
int16_t multiply_divisor_hv(int8_t value) {
    return divisor_multiply16((int16_t)value);
}

/**
 * @brief Return device id of current controlled device
 *
 * @return current device id [uint8_t]
 */
uint8_t get_pointing_mode_device(void) {
#    ifdef POINTING_MODES_SINGLE_CONTROL
    return selected_device;
#    else
    return current_device;
#    endif
}

/**
 * @brief Change current device
 *
 * Will change which device (PM_LEFT_DEVICE, PM_RIGHT_DEVICE, etc.) is currently being modified
 *
 * NOTE: If mode is set to out of range device number device is silently set to zero (this allows cycling)
 *
 * @params[in] new side uint8_t
 */
void set_pointing_mode_device(uint8_t device) {
#    if (POINTING_MODES_NUM_DEVICES > 1)
    if (device > (POINTING_MODES_NUM_DEVICES - 1)) device = 0;
#        ifdef POINTING_MODES_SINGLE_CONTROL
    selected_device = device;
#        else
    current_device = device;
#        endif
#    else
    ;
#    endif
}

/**
 * @brief Reset pointing mode data
 *
 *  Clear poiting mode and set to defaults
 */
void pointing_mode_reset(void) {
    memset(&pointing_modes[current_device], 0, sizeof(pointing_mode_t));
    pointing_modes[current_device].id = toggle_ids[current_device];
}

/**
 * @brief set current pointing mode data
 *
 * @param[in] pointing_mode pointing_mode_t
 */
void set_pointing_mode(pointing_mode_t pointing_mode) {
    // skip if same
    if (!memcmp(&pointing_modes[current_device], &pointing_mode, sizeof(pointing_mode_t))) return;
    memcpy(&pointing_modes[current_device], &pointing_mode, sizeof(pointing_mode_t));
}

/**
 * @brief access current pointing mode id
 *
 * @return uint8_t current pointing mode id
 */
uint8_t get_pointing_mode_id(void) {
    return pointing_modes[current_device].id;
}

/**
 * @brief set pointing mode id
 *
 * @param[in] mode_id uint8_t
 */
void set_pointing_mode_id(uint8_t mode_id) {
    if (get_pointing_mode_id() != mode_id) {
        pointing_mode_reset();
        pointing_modes[current_device].id = mode_id;
    }
}

/**
 * @brief Access current toggled pointing mode
 *
 * @return uint8_t toggle pointing mode
 */
uint8_t get_toggled_pointing_mode_id(void) {
    return toggle_ids[current_device];
}

/**
 * @brief Toggle pointing mode id on/off
 *
 * Will change tg_mode_id setting to POINTING_MODE_DEFAULT when toggling "off"
 *
 * @param[in] mode_id uint8_t
 */
void toggle_pointing_mode_id(uint8_t mode_id) {
    if (get_toggled_pointing_mode_id() == mode_id) {
        toggle_ids[current_device] = POINTING_MODE_DEFAULT;
    } else {
        toggle_ids[current_device] = mode_id;
    }
    if (get_pointing_mode_id() != get_toggled_pointing_mode_id()) pointing_mode_reset();
}

/**
 * @brief Weak function to convert x/y axes to h/v
 *
 * The default uses accumulation based on inversion defines and
 * halts cursor movement
 *
 * @params pointing_modes[in] pointing_mode_t
 * @params mouse_report[in]  report_mouse_t
 *
 * @return updated mouse_report report_mouse_t
 */
__attribute__((weak)) report_mouse_t pointing_modes_axes_conv(pointing_mode_t pointing_mode, report_mouse_t mouse_report) {
#    ifdef POINTING_DEVICE_MODES_INVERT_X
    pointing_mode.x -= mouse_report.x;
#    else
    pointing_mode.x += mouse_report.x;
#    endif
#    ifdef POINTING_DEVICE_MODES_INVERT_Y
    pointing_mode.y -= mouse_report.y;
#    else
    pointing_mode.y += mouse_report.y;
#    endif
    set_pointing_mode(pointing_mode);
    mouse_report.x = 0;
    mouse_report.y = 0;
    return mouse_report;
}

/**
 * @brief Modifies divisor after
 *
 * @params pointing_modes[in] uint8_t
 * @params direction[in] uint8_t
 *
 * @return divisor uint8_t
 */
static uint8_t divisor_postprocess(uint8_t divisor) {
    if (!(pointing_mode_divisor_postprocess_user(&divisor) && pointing_mode_divisor_postprocess_kb(&divisor))) {
        // never return without zero checking
        return divisor ? divisor : POINTING_DEFAULT_DIVISOR;
    }
    // Modify divisor if precision is toggled
    if (get_toggled_pointing_mode_id() == PM_PRECISION && !(get_pointing_mode_id() == PM_PRECISION)) {
        divisor = clamp_uint_16_to_8(divisor * POINTING_PRECISION_DIVISOR);
    }
    // never return without zero checking
    return divisor ? divisor : POINTING_DEFAULT_DIVISOR;
}

/**
 * @brief override current divisor value
 *
 * Will only take effect until next cycle update or next call of this process
 *
 * @param[in] divisor uint8_t
 */
void pointing_mode_divisor_override(uint8_t divisor) {
    current_divisor = divisor_postprocess(divisor);
}

/**
 * @brief local function to get pointing mode divisor
 *
 * Will handle default divisors and call weak kb and user functions
 *
 * NOTE: Expects that pointing mode and direction has been updated
 *
 * @return divisor uint8_t
 */
static uint8_t get_pointing_mode_divisor(void) {
    uint8_t divisor = 0;
    // allow for user and keyboard overrides
    divisor = get_pointing_mode_divisor_user(get_pointing_mode_id(), current_pointing_mode_direction());
    if (divisor) return divisor_postprocess(divisor);
    divisor = get_pointing_mode_divisor_kb(get_pointing_mode_id(), current_pointing_mode_direction());
    if (divisor) return divisor_postprocess(divisor);
    // built in divisors
    switch (get_pointing_mode_id()) {
        case PM_PRECISION:
            divisor = POINTING_PRECISION_DIVISOR;
            break;

        case PM_DRAG:
            divisor = POINTING_DRAG_DIVISOR;
            break;

        case PM_CARET:
            divisor = current_pointing_mode_direction() < PD_LEFT ? POINTING_CARET_DIVISOR_V : POINTING_CARET_DIVISOR_H;
            break;

        case PM_HISTORY:
            divisor = POINTING_HISTORY_DIVISOR;
            break;

#    ifdef EXTRAKEY_ENABLE
        case PM_VOLUME:
            divisor = POINTING_VOLUME_DIVISOR;
            break;
#    endif
    }
    return divisor_postprocess(divisor);
}

/**
 * @brief local function to get single direction based on h/v
 *
 * Determines direction based on axis with largest magnitude
 *
 * NOTE: Defaults to PD_DOWN
 *
 * @return direction uint8_t
 */
static uint8_t get_pointing_mode_direction(void) {
    if (abs(pointing_modes[current_device].x) > abs(pointing_modes[current_device].y)) {
        if (pointing_modes[current_device].x > 0) {
            return PD_RIGHT;
        } else {
            return PD_LEFT;
        }
    } else {
        if (pointing_modes[current_device].y > 0) {
            return PD_UP;
        } else {
            return PD_DOWN;
        }
    }
}

/**
 * @brief update dependent parameters of pointing_mode
 *
 * Will update the direction and divisor values based on mode id and h, and v axis values
 *
 */
void pointing_mode_update(void) {
    current_direction = get_pointing_mode_direction();
    current_divisor   = get_pointing_mode_divisor();
}

/**
 * @brief Access current pointing mode direction
 *
 * @return uint8_t direction
 */
uint8_t current_pointing_mode_direction(void) {
    return current_direction;
}

/**
 * @brief Access current pointing mode divisor
 *
 * @return uint8_t divisor
 */
uint8_t current_pointing_mode_divisor(void) {
    return current_divisor;
}

/**
 * @brief Tap keycodes based on mode axis values
 *
 * Will translate current mode x & y values into keycode taps based on divisor value.
 * Array should be ordered {DOWN, UP, LEFT, RIGHT} and will output 1 keytap/divisor
 * x and y values will be automatically updated
 *
 * NOTE: favours staying on axis and weakly favours the horizontal over the vertical axis
 *       and will clear the orthogonal axis
 *
 * @param[in] uint16_t* array pointer to set of four keycodes
 */
static void pointing_tap_keycodes_raw(uint16_t* pm_keycodes) {
    int16_t count = 0;
    uint8_t dir   = current_pointing_mode_direction();

    switch (dir) {
        case PD_DOWN ... PD_UP:
            count = divisor_divide16(pointing_modes[current_device].y);
            if (!count) return; // exit if accumulated y is too low
            pointing_modes[current_device].y -= divisor_multiply16(count);
            pointing_modes[current_device].x = 0;
            break;
        case PD_LEFT ... PD_RIGHT:
            count = divisor_divide16(pointing_modes[current_device].x);
            if (!count) return; // exit if accumulated x is too low
            pointing_modes[current_device].x -= divisor_multiply16(count);
            pointing_modes[current_device].y = 0;
            break;
    }
    // skip if KC_TRNS or KC_NO (but allow for axes update above)
    // if (pm_keycodes[dir] < 2) return;

    // tap codes
    uint8_t taps = clamp_uint_16_to_8((uint16_t)abs(count));
    do {
        tap_code16_delay(pm_keycodes[dir], POINTING_TAP_DELAY);
    } while (--taps);
}

/**
 * @brief external wrapper for pointing_tap_keycodes to allow easier input
 *
 * keycode order follow VIM convention (LEFT, DOWN, UP, RIGHT).s
 *
 * @params kc_left[in]  uint16_t keycode for negative x
 * @params kc_down[in]  uint16_t keycode for negative y
 * @params kc_up[in]    uint16_t keycode for positive y
 * @params kc_right[in] uint16_t keycode for positive x
 */
void pointing_tap_codes(uint16_t kc_left, uint16_t kc_down, uint16_t kc_up, uint16_t kc_right) {
    uint16_t pm_keycodes[4] = {kc_down, kc_up, kc_left, kc_right};
    pointing_tap_keycodes_raw(pm_keycodes);
}

/**
 * @brief Tap keycodes from pointing mode maps
 *
 * Will translate internal x & y axes into mode map keycode taps.
 * and will update the x and y values.-
 *
 * NOTE: favours staying on axis and favours the horizontal over the vertical axis
 *       and will clear the orthogonal axis
 *
 * @params map_id id of current map
 */
#    ifdef POINTING_MODE_MAP_ENABLE
static void pointing_exec_mapping(uint8_t map_id) {
    int16_t count = 0;
    uint8_t dir   = current_pointing_mode_direction();

    switch (dir) {
        case PD_DOWN ... PD_UP:
            count = divisor_divide16(pointing_modes[current_device].y);
            if (!count) return; // exit if accumulated y is too low
            pointing_modes[current_device].y -= divisor_multiply16(count);
            pointing_modes[current_device].x = 0;
            break;
        case PD_LEFT ... PD_RIGHT:
            count = divisor_divide16(pointing_modes[current_device].x);
            if (!count) return; // exit if accumulated x is too low
            pointing_modes[current_device].x -= divisor_multiply16(count);
            pointing_modes[current_device].y = 0;
            break;
    }

    // tap codes
    uint8_t taps = clamp_uint_16_to_8((uint16_t)abs(count));
    do {
        action_exec(MAKE_POINTING_MODE_EVENT(map_id, dir, true));
#        if POINTING_TAP_DELAY > 0
        wait_ms(POINTING_TAP_DELAY);
#        endif // POINTING_TAP_DELAY > 0
        action_exec(MAKE_POINTING_MODE_EVENT(map_id, dir, false));
    } while (--taps);
}
#    endif

/**
 * @brief Core function to handle pointing mode task
 *
 * Meant to be implemented in pointing_device_task
 *
 * @param[in] mouse_report report_mouse_t
 *
 * @return mouse_report report_mouse_t
 */
report_mouse_t pointing_device_modes_task(report_mouse_t mouse_report) {
    // skip all processing if pointing mode is PM_NONE
    if (get_pointing_mode_id() == PM_NONE) return mouse_report;

    mouse_report = pointing_modes_axes_conv(pointing_modes[current_device], mouse_report);
    pointing_mode_update();
    mouse_report = process_pointing_mode(pointing_modes[current_device], mouse_report);

    return mouse_report;
}

/**
 * @brief Handle processing of pointing modes
 *
 * Takes in report_mouse_t and pointing_mode_t allowing manipulation of mouse_report
 * and pointing_mode via set_pointing_mode
 *
 * @return mouse_report report_mouse_t
 */
static report_mouse_t process_pointing_mode(pointing_mode_t pointing_mode, report_mouse_t mouse_report) {
    // allow overwrite of pointing modes by user, and kb
    if (!(process_pointing_mode_user(pointing_mode, &mouse_report) && process_pointing_mode_kb(pointing_mode, &mouse_report))) {
        return mouse_report;
    }
    switch (pointing_mode.id) {
        // precision mode  (reduce x y sensitivity temporarily)
        case PM_PRECISION:
#    ifdef POINTING_DEVICE_MODES_INVERT_X
            mouse_report.x -= apply_divisor_xy(pointing_mode.x);
            pointing_mode.x += multiply_divisor_xy(mouse_report.x);
#    else
            mouse_report.x += apply_divisor_xy(pointing_mode.x);
            pointing_mode.x -= multiply_divisor_xy(mouse_report.x);
#    endif
#    ifdef POINTING_DEVICE_MODES_INVERT_Y
            mouse_report.y -= apply_divisor_xy(pointing_mode.y);
            pointing_mode.y += multiply_divisor_xy(mouse_report.y);
#    else
            mouse_report.y += apply_divisor_xy(pointing_mode.y);
            pointing_mode.y -= multiply_divisor_xy(mouse_report.y);
#    endif
            set_pointing_mode(pointing_mode);
            break;

        // drag scroll mode (sets mouse axes to mouse_report h & v with divisor)
        case PM_DRAG:
            mouse_report.h = apply_divisor_hv(pointing_mode.x);
            pointing_mode.x -= multiply_divisor_hv(mouse_report.h);
            mouse_report.v = apply_divisor_hv(pointing_mode.y);
            pointing_mode.y -= multiply_divisor_hv(mouse_report.v);
            set_pointing_mode(pointing_mode);
            break;

        // caret mode (uses arrow keys to move cursor)
        case PM_CARET:
            pointing_tap_codes(KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT);
            break;

        // history scroll mode (will scroll through undo/redo history)
        case PM_HISTORY:
            pointing_tap_codes(C(KC_Z), KC_NO, KC_NO, C(KC_Y));
            break;

#    ifdef EXTRAKEY_ENABLE
        // volume scroll mode (adjusts audio volume)
        case PM_VOLUME:
            pointing_tap_codes(KC_NO, KC_VOLD, KC_VOLU, KC_NO);
            break;
#    endif

#    ifdef POINTING_MODE_MAP_ENABLE
        default:
            if (pointing_mode.id > POINTING_MODE_MAP_START) {
                pointing_exec_mapping(pointing_mode.id - POINTING_MODE_MAP_START);
            }
#    endif
    }
    return mouse_report;
}

/**
 * @brief User level processing of pointing device modes
 *
 * Takes pointing_mode_t struct, and pointer to the report_mouse_t struct used in pointing mode process allowing
 * modification of mouse_report directly and pointing mode using set_pointing_mode(pointing_mode) and the returned
 * bool controls the continued processing of pointing modes.
 *
 * NOTE: returning false will stop mode processing (for overwriting modes)
 *
 * @params pointing_modes[in] pointing_mode_t
 * @params mouse_report[in] pointer to report_mouse_t
 *
 * @return bool continue processing flag
 */
__attribute__((weak)) bool process_pointing_mode_user(pointing_mode_t pointing_mode, report_mouse_t* mouse_report) {
    return true; // continue processing
}

/**
 * @brief Keyboard level processing of pointing device modes
 *
 * Takes pointing_mode_t struct, and pointer to the report_mouse_t struct used in pointing mode process allowing
 * modification of mouse_report directly and pointing mode using set_pointing_mode(pointing_mode) and the returned
 * bool controls the continued processing of pointing modes.
 *
 * NOTE: returning false will stop mode processing (for overwriting modes)
 *
 * @params pointing_modes[in] pointing_mode_t
 * @params mouse_report[in]  pointer to report_mouse_t
 *
 * @return bool continue processing flag
 */
__attribute__((weak)) bool process_pointing_mode_kb(pointing_mode_t pointing_mode, report_mouse_t* mouse_report) {
    return true; // continue processing
}

/**
 * @brief Weak function for user level adding of pointing mode divisors
 *
 * Takes in mode id and direction allowing for divisor values to be
 * determined based on these parameters
 *
 * @params pointing_modes[in] uint8_t
 * @params direction[in] uint8_t
 *
 * @return divisor uint8_t
 */
__attribute__((weak)) uint8_t get_pointing_mode_divisor_user(uint8_t mode_id, uint8_t direction) {
    return 0; // continue processing
}

/**
 * @brief Weak function for user level adding of pointing mode divisors
 *
 * Takes in mode id and direction allowing for divisor values to be
 * determined based on these parameters
 *
 * @params pointing_modes[in] uint8_t
 * @params direction[in] uint8_t
 *
 * @return divisor uint8_t
 */
__attribute__((weak)) uint8_t get_pointing_mode_divisor_kb(uint8_t mode_id, uint8_t direction) {
    return 0; // continue processing
}

/**
 * @brief Keyboard level modifying of divisors after being set and before use
 *
 * Allows modification the divisor after being set by get_pointing_mode_divisor stack before
 * handing off to default post processing
 *
 * @params[in] pointer to divisor uint8_t
 *
 * @return bool continue processing flag
 */
__attribute__((weak)) bool pointing_mode_divisor_postprocess_kb(uint8_t* divisor) {
    return true;
}

/**
 * @brief User level modifying of divisors after being set and before use
 *
 * Allows modification the divisor after being set by get_pointing_mode_divisor stack before
 * handing off to default post processing
 *
 * @params[in] pointer to divisor uint8_t
 *
 * @return bool continue processing flag
 */
__attribute__((weak)) bool pointing_mode_divisor_postprocess_user(uint8_t* divisor) {
    return true;
}

#endif // POINTING_DEVICE_MODES_ENABLE
