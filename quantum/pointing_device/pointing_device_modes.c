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

#ifdef POINTING_DEVICE_POINTING_MODES_ENABLE

#    include "pointing_device_modes.h"

// initialize local functions
static report_mouse_t process_pointing_mode(pointing_mode_device_t pointing_mode, report_mouse_t mouse_report);
static uint8_t        pointing_mode_update_direction(void);
static uint8_t        pointing_mode_update_divisor(void);
static uint8_t        divisor_postprocess(uint8_t divisor);

// local variables
static uint8_t current_direction = 0;
static uint8_t current_divisor   = POINTING_MODE_DEFAULT_DIVISOR;

// set up devices and active device
static pointing_mode_device_t pointing_mode_devices[]  = {[0 ... POINTING_MODE_DEVICE_CONTROL_COUNT - 1] = {.toggle_id = POINTING_MODE_DEFAULT_MODE, .mode_id = POINTING_MODE_DEFAULT_MODE}};
#    if POINTING_MODE_DEVICE_CONTROL_COUNT > 1
static uint8_t active_device_id = POINTING_MODE_DEFAULT_DEVICE;
#    else
static const uint8_t active_device_id = 0;
#    endif

// set up clamping and divisor application functions (move to standard utils perhaps?)
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
 * @brief Return device struct by device id
 *
 */
pointing_mode_device_t pointing_mode_get_device_settings(uint8_t device_id) {
    return pointing_mode_devices[device_id];
}

/**
 * @brief Return device id of current controlled device
 *
 * @return current device id [uint8_t]
 */
uint8_t pointing_mode_active_device_id(void) {
    return active_device_id;
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
void pointing_mode_set_active_device_id(uint8_t device_id) {
#    if (POINTING_MODE_NUM_DEVICES > 1)
    if (device_id > (POINTING_MODE_NUM_DEVICES - 1)) device_id = 0;
    active_device_id = device_id;
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
    memset(&pointing_mode_devices[active_device_id], 0, sizeof(pointing_mode_device_t));
    pointing_mode_devices[active_device_id].mode_id = pointing_mode_devices[active_device_id].toggle_id;
}

/**
 * @brief set pointing mode data of active device
 *
 * @param[in] pointing_mode_device pointing_mode_device_t
 */
void pointing_mode_set_device_settings(pointing_mode_device_t device) {
    // skip if same
    if (!memcmp(&pointing_mode_devices[active_device_id], &device, sizeof(pointing_mode_device_t))) return;
    memcpy(&pointing_mode_devices[active_device_id], &device, sizeof(pointing_mode_device_t));
}

/**
 * @brief get precision of active device
 *
 * @return uint8_t active device precision divisor
 */
uint8_t pointing_mode_get_precision(void) {
    return pointing_mode_devices[active_device_id].precision;
}

/**
 * @brief set precision of active device
 *
 * @param[in] uint8_t precision
 */
void pointing_mode_set_precision(uint8_t precision) {
    if (precision > POINTING_MODE_PRECISION_MAX || !precision) {
        pointing_mode_devices[active_device_id].precision = 1;
    } else {
        pointing_mode_devices[active_device_id].precision = precision;
    }
}

static uint8_t pointing_mode_get_type(uint8_t mode_id) {
    uint8_t mode_type = PMT_NONE;

    mode_type = pointing_mode_get_type_kb(mode_id);
    if (mode_type) return mode_type;

    mode_type = pointing_mode_get_type_user(mode_id);
    if (mode_type) return mode_type;

    return PMT_4WAY;
}

/**
 * @brief access current pointing mode id
 *
 * @return uint8_t current pointing mode id
 */
uint8_t pointing_mode_get_mode(void) {
    return pointing_mode_devices[active_device_id].mode_id;
}

/**
 * @brief set pointing mode id
 *
 * @param[in] mode_id uint8_t
 */
void pointing_mode_set_mode(uint8_t mode_id) {
    if (pointing_mode_get_mode() != mode_id) {
        pointing_mode_reset();
        pointing_mode_devices[active_device_id].mode_id = mode_id;
    }
}

/**
 * @brief Access current toggled pointing mode
 *
 * @return uint8_t toggle pointing mode
 */
uint8_t pointing_mode_get_toggled_mode(void) {
    return pointing_mode_devices[active_device_id].toggle_id;
}

/**
 * @brief Toggle pointing mode id on/off
 *
 * Will change tg_mode_id setting to POINTING_MODE_DEFAULT_MODE when toggling "off"
 *
 * @param[in] mode_id uint8_t
 */
void pointing_mode_device_toggle_mode(uint8_t mode_id) {
    if (pointing_mode_get_toggled_mode() == mode_id) {
        pointing_mode_devices[active_device_id].toggle_id = POINTING_MODE_DEFAULT;
    } else {
        pointing_mode_devices[active_device_id].toggle_id = mode_id;
    }
    if (pointing_mode_get_mode() != pointing_mode_get_toggled_mode()) pointing_mode_reset();
}

/**
 * @brief Weak function to convert x/y axes to h/v
 *
 * The default uses accumulation based on inversion defines and
 * halts cursor movement
 *
 * @params pointing_mode_devices[in] pointing_mode_device_t
 * @params mouse_report[in]  report_mouse_t
 *
 * @return updated mouse_report report_mouse_t
 */
static report_mouse_t pointing_mode_axes_conv(pointing_mode_device_t device, report_mouse_t mouse_report) {
    // !! fix this as these are signed ints so bit shifting needs to respect sign
    // set X axis of pointing mode for device
#    ifdef POINTING_DEVICE_MODES_INVERT_X
    pointing_mode_device.x -= (mouse_report.x / device.precision);
#    else
    pointing_mode_device.x += (mouse_report.x / device.precision);
#    endif
// set Y axis of pointing mode for device
#    ifdef POINTING_DEVICE_MODES_INVERT_Y
    pointing_mode_device.y -= (mouse_report.y / device.precision);
#    else
    pointing_mode_device.y += (mouse_report.y / device.precision);
#    endif
    pointing_mode_set_device_settings(device);
    mouse_report.x = 0;
    mouse_report.y = 0;
    return mouse_report;
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
static uint8_t pointing_mode_update_divisor(void) {
    uint8_t divisor = 0;
    // allow for user and keyboard overrides
    divisor = get_pointing_mode_divisor_user(pointing_mode_get_mode(), current_pointing_mode_direction());
    if (divisor) return divisor;
    divisor = get_pointing_mode_divisor_kb(pointing_mode_get_mode(), current_pointing_mode_direction());
    if (divisor) return divisor;
    // built in divisors
    switch (pointing_mode_get_mode()) {
        case PM_DRAG:
            divisor = POINTING_MODE_DRAG_DIVISOR;
            break;
    }
    return divisor ? divisor : POINTING_MODE_DEFAULT_DIVISOR;
}

/**
 * @brief local function to get single direction based on h/v
 *
 * Determines direction based on axis with largest magnitude
 *
 * NOTE: Defaults to PMD_DOWN
 *
 * @return direction uint8_t
 */
static uint8_t pointing_mode_update_direction(void) {
#    if POINTING_MODE_THRESHOLD > 0
    if(abs(pointing_mode_devices[active_device_id].x) + abs(pointing_mode_devices[active_device_id].y) > POINTING_MODE_THRESHOLD) {
        return PMD_NONE
    }
#    endif
    switch (pointing_mode_get_type(pointing_mode_get_mode() & PMT_MODES) {
        case PMT_4WAY:
            if (abs(pointing_mode_devices[active_device_id].x) > abs(pointing_mode_devices[active_device_id].y)) {
                if (pointing_mode_devices[active_device_id].x > 0) {
                    return PMD_RIGHT;
                } else {
                    return PMD_LEFT;
                }
            } else {
                if (pointing_mode_devices[active_device_id].y > 0) {
                    return PMD_DOWN;
                } else {
                    return PMD_UP;
                }
            }
            break;
        case PMT_DPAD:
            uint8_t dir_out = PMD_NONE;
            if ((abs(pointing_mode_devices[active_device_id].x) << 1) > abs(pointing_mode_devices[active_device_id].y) {
                if (pointing_mode_devices[active_device_id].x > 0) {
                    dir_out &= PMD_RIGHT;
                } else {
                    dir_out &= PMD_LEFT;
                }
            }
            if ((abs(pointing_mode_devices[active_device_id].y) << 1) > abs(pointing_mode_devices[active_device_id].x) {
                if (pointing_mode_devices[active_device_id].y > 0) {
                    dir_out &= PMD_DOWN;
                } else {
                    dir_out &= PMD_UP;
                }
            }
            return dir_out;
    }
}

/**
 * @brief update dependent parameters of pointing_mode
 *
 * Will update the direction and divisor values based on mode id and h, and v axis values
 *
 */
void pointing_mode_update(void) {
    current_direction = pointing_mode_update_direction();
    current_divisor   = pointing_mode_update_divisor();
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
    uint8_t key   = 0;

    switch (current_pointing_mode_direction()) {
        case PMD_DOWN ... PMD_UP:
            count = divisor_divide16(pointing_mode_devices[active_device_id].y);
            if (!count) return; // exit if accumulated y is too low
            key = count > 0? PMK_DOWN:PMK_UP;
            pointing_mode_devices[active_device_id].y -= divisor_multiply16(count);
            pointing_mode_devices[active_device_id].x = 0;
            break;
        case PMD_LEFT ... PMD_RIGHT:
            count = divisor_divide16(pointing_mode_devices[active_device_id].x);
            if (!count) return; // exit if accumulated x is too low
            key = count > 0? PMK_RIGHT:PMK_LEFT;
            pointing_mode_devices[active_device_id].x -= divisor_multiply16(count);
            pointing_mode_devices[active_device_id].y = 0;
            break;
    }
    // skip if KC_TRNS or KC_NO (but allow for axes update above)
    // if (pm_keycodes[dir] < 2) return;

    // tap codes
    uint8_t taps = clamp_uint_16_to_8((uint16_t)abs(count));
    do {
        tap_code16_delay(pm_keycodes[key], POINTING_MODE_TAP_DELAY);
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
    static uint16_t prev_key[] = {0, 0};

    int16_t count[]   = {0, 0};
    uint8_t key[]     = {0, 0};
    uint8_t mode_type = pointing_mode_get_type(pointing_mode_get_mode());
    switch (mode_type & PMT_MODES) {
        case PMT_4WAY:
            switch (current_pointing_mode_direction()) {
                case PMD_DOWN ... PMD_UP:
                    count[0] = divisor_divide16(pointing_mode_devices[active_device_id].y);
                    if (!count[0]) return; // exit if accumulated y is too low
                    key[0] = count[0] > 0? PMK_DOWN:PMK_UP;
                    pointing_mode_devices[active_device_id].y = 0;
                    pointing_mode_devices[active_device_id].x = 0;
                    break;
                case PMD_LEFT ... PMD_RIGHT:
                    count[0] = divisor_divide16(pointing_mode_devices[active_device_id].x);
                    if (!count[0]) return; // exit if accumulated x is too low
                    key[0] = count[0] > 0? PMK_RIGHT:PMK_LEFT;
                    pointing_mode_devices[active_device_id].x = 0;
                    pointing_mode_devices[active_device_id].y = 0;
                    break;
            }
            break;
        case PMT_DPAD:
            uint8_t dir = current_pointing_mode_direction();
            if(dir & PMD_VERT) {
                count[0] = divisor_divide16(pointing_mode_devices[active_device_id].y);
                pointing_mode_devices[active_device_id].y = 0;
                key[0] = count[0] > 0? PMK_DOWN:PMK_UP;
            }
            if(dir & PMD_HORI) {
                count[1] = divisor_divide16(pointing_mode_devices[active_device_id].x);
                pointing_mode_devices[active_device_id].x = 0;
                key[1] = count[1] > 0? PMK_RIGHT:PMK_LEFT;
            }
    }
    switch(mode_type & PMT_OPTS){
        case PMT_TAP:
            if(count[0]) {
                uint8_t taps = clamp_uint_16_to_8((uint16_t)abs(count[0]));
                do {
                    action_exec(MAKE_POINTING_MODE_EVENT(map_id, key[0], true));
#        if POINTING_MODE_TAP_DELAY > 0
                    wait_ms(POINTING_MODE_TAP_DELAY);
#        endif // POINTING_MODE_TAP_DELAY > 0
                    action_exec(MAKE_POINTING_MODE_EVENT(map_id, key[0], false));
                } while (--taps);
            }
            if(count[1]) {
                uint8_t taps = clamp_uint_16_to_8((uint16_t)abs(count[1]));
                do {
                    action_exec(MAKE_POINTING_MODE_EVENT(map_id, key[1], true));
#        if POINTING_MODE_TAP_DELAY > 0
                    wait_ms(POINTING_MODE_TAP_DELAY);
#        endif // POINTING_MODE_TAP_DELAY > 0
                    action_exec(MAKE_POINTING_MODE_EVENT(map_id, key[1], false));
                } while (--taps);
            }
            break;
        case PMT_HOLD:
            if(count[0]) {
                action_exec(MAKE_POINTING_MODE_EVENT(map_id, prev_key[0], false));
                if(prev_key[0] != key[0]) {
                    action_exec(MAKE_POINTING_MODE_EVENT(map_id, key[0], true));
                    prev_key[0] = key[0];
                } else {
                    prev_key[0] = 0;
                }
            }
            if(count[1]) {
                action_exec(MAKE_POINTING_MODE_EVENT(map_id, prev_key[1], false));
                if(prev_key[1] != key[1]) {
                    action_exec(MAKE_POINTING_MODE_EVENT(map_id, key[1], true));
                    prev_key[1] = key[1];
                } else {
                    prev_key[1] = 0;
                }
            }
    }
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
    mouse_report = pointing_mode_axes_conv(pointing_mode_devices[active_device_id], mouse_report);
    pointing_mode_update();
    mouse_report = process_pointing_mode(pointing_mode_devices[active_device_id], mouse_report);

    return mouse_report;
}

/**
 * @brief Handle processing of pointing modes
 *
 * Takes in report_mouse_t and pointing_mode_device_t allowing manipulation of mouse_report
 * and pointing_mode via pointing_mode_set_device_settings
 *
 * @return mouse_report report_mouse_t
 */
static report_mouse_t process_pointing_mode(pointing_mode_device_t pointing_mode_device, report_mouse_t mouse_report) {
    // allow overwrite of pointing modes by user, and kb
    if (!(process_pointing_mode_user(pointing_mode, &mouse_report) && process_pointing_mode_kb(pointing_mode, &mouse_report))) {
        return mouse_report;
    }
    switch (pointing_mode.mode_id) {
        // if no pointing mode selected set back to mouse_report and clear
        case PM_NONE:
#    ifdef POINTING_DEVICE_MODES_INVERT_X
            mouse_report.x -= pointing_mode_device.x;
#    else
            mouse_report.x += pointing_mode_device.x;
#    endif
#    ifdef POINTING_DEVICE_MODES_INVERT_Y
            mouse_report.y -= pointing_mode_device.y;
#    else
            mouse_report.y += pointing_mode_device.y;
#    endif
            pointing_mode_device.x = 0;
            pointing_mode_device.y = 0;
        // drag scroll mode (sets mouse axes to mouse_report h & v with divisor)
        case PM_DRAG:
            mouse_report.h = apply_divisor_hv(pointing_mode_device.x);
            pointing_mode_device.x -= multiply_divisor_hv(mouse_report.h);
            mouse_report.v = apply_divisor_hv(pointing_mode_device.y);
            pointing_mode_device.y -= multiply_divisor_hv(mouse_report.v);
            pointing_mode_set_device_settings(pointing_mode);
            break;

#    ifdef POINTING_MODE_MAP_ENABLE
        default:
            if (pointing_mode_device.mode_id > POINTING_MODE_MAP_START) {
                pointing_exec_mapping(pointing_mode_device.mode_id - POINTING_MODE_MAP_START);
            }
#    endif
    }
    return mouse_report;
}

/**
 * @brief User level processing of pointing device modes
 *
 * Takes pointing_mode_device_t struct, and pointer to the report_mouse_t struct used in pointing mode process allowing
 * modification of mouse_report directly and pointing mode using pointing_mode_set_device_settings(pointing_mode) and the returned
 * bool controls the continued processing of pointing modes.
 *
 * NOTE: returning false will stop mode processing (for overwriting modes)
 *
 * @params pointing_mode_devices[in] pointing_mode_device_t
 * @params mouse_report[in] pointer to report_mouse_t
 *
 * @return bool continue processing flag
 */
__attribute__((weak)) bool process_pointing_mode_user(pointing_mode_device_t pointing_mode, report_mouse_t* mouse_report) {
    return true; // continue processing
}

/**
 * @brief Keyboard level processing of pointing device modes
 *
 * Takes pointing_mode_device_t struct, and pointer to the report_mouse_t struct used in pointing mode process allowing
 * modification of mouse_report directly and pointing mode using pointing_mode_set_device_settings(pointing_mode) and the returned
 * bool controls the continued processing of pointing modes.
 *
 * NOTE: returning false will stop mode processing (for overwriting modes)
 *
 * @params pointing_mode_devices[in] pointing_mode_device_t
 * @params mouse_report[in]  pointer to report_mouse_t
 *
 * @return bool continue processing flag
 */
__attribute__((weak)) bool process_pointing_mode_kb(pointing_mode_device_t pointing_mode, report_mouse_t* mouse_report) {
    return true; // continue processing
}

/**
 * @brief Weakly defined function adding of pointing mode divisors at user level
 *
 * Takes in mode id and direction allowing for divisor values to be
 * determined based on these parameters
 *
 * @params pointing_mode_devices[in] uint8_t
 * @params direction[in] uint8_t
 *
 * @return divisor uint8_t
 */
__attribute__((weak)) uint8_t get_pointing_mode_divisor_user(uint8_t mode_id, uint8_t direction) {
    return 0; // continue processing
}

/**
 * @brief Weakly defined function adding of pointing mode divisors at keyboard level
 *
 * Takes in mode id and direction allowing for divisor values to be
 * determined based on these parameters
 *
 * @params pointing_mode_devices[in] uint8_t
 * @params direction[in] uint8_t
 *
 * @return divisor uint8_t
 */
__attribute__((weak)) uint8_t get_pointing_mode_divisor_kb(uint8_t mode_id, uint8_t direction) {
    return 0; // continue processing
}

/**
 * @brief Weakly defined function for setting pointing mode type at the user level
 *
 * Takes in mode id and returns current pointing mode type (PMT_4WAY, PMT_DPAD).
 * Also mode options may be added to the mode type (PMT_HOLD)
 *
 * @params mode_id uint8_t
 *
 * @return pointing_mode_type uint8_t
 */
__attribute__((weak)) uint8_t get_pointing_mode_type_user(uint8_t mode_id) {
    return PMT_NONE; // continue processing
}

/**
 * @brief Weakly defined function for setting pointing mode type at the user level
 *
 * Takes in mode id and returns current pointing mode type (PMT_4WAY, PMT_DPAD).
 * Also mode options may be added to the mode type (PMT_HOLD)
 *
 * @params mode_id uint8_t
 *
 * @return pointing_mode_type uint8_t
 */
__attribute__((weak)) uint8_t get_pointing_mode_type_kb(uint8_t mode_id, uint8_t direction) {
    return PMT_NONE; // continue processing
}

#endif // POINTING_DEVICE_POINTING_MODES_ENABLE
