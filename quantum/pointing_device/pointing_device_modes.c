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
static uint8_t pm_mode_ids[]                = {[0 ... POINTING_MODE_DEVICE_CONTROL_COUNT - 1] = {POINTING_MODE_DEFAULT_MODE}};
static uint8_t pm_base_modes[]              = {[0 ... POINTING_MODE_DEVICE_CONTROL_COUNT - 1] = {POINTING_MODE_DEFAULT_MODE}};
static uint8_t pm_precisions[]              = {[0 ... POINTING_MODE_DEVICE_CONTROL_COUNT - 1] = {1}};
static pointing_mode_residuals_t pm_res[]   = {[0 ... POINTING_MODE_DEVICE_CONTROL_COUNT - 1] = {0}};
static pointing_mode_held_keys_t pm_held[]  = {[0 ... POINTING_MODE_DEVICE_CONTROL_COUNT - 1] = {PMK_NONE}};
#    if POINTING_MODE_DEVICE_CONTROL_COUNT > 1
static uint8_t active_device_id = POINTING_MODE_DEFAULT_DEVICE;
#    else
static const uint8_t active_device_id = 0;
#    endif

// set up clamping functions (move to standard utils perhaps?)
static inline mouse_xy_report_t pointing_device_xy_clamp(clamp_range_t value) {
    if (value < XY_REPORT_MIN) {
        return XY_REPORT_MIN;
    } else if (value > XY_REPORT_MAX) {
        return XY_REPORT_MAX;
    } else {
        return value;
    }
}

static inline int8_t pointing_device_hv_clamp(int16_t value) {
    if (value < INT8_MIN) {
        return INT8_MIN;
    } else if (value > INT8_MAX) {
        return INT8_MAX;
    } else {
        return value;
    }
}
// This function is to help avoid wrap around behaviour of unsigned integers and instead clamp to UINT8_MAX
static inline uint16_t clamp_uint_16_to_8(uint16_t value) {
    if (value > UINT8_MAX) return UINT8_MAX;
    return value;
}

/**
 * @brief apply divisor to device axis and update residuals
 *
 * Will apply the divisor to the specified axis (FALSE:x, TRUE:y) and will update device axis with residuals
 *
 * @params value[in] axis bool
 *
 * @return quotient
 */
mouse_xy_report_t pointing_mode_apply_divisor(bool axis) {
    if (axis) {
        mouse_xy_report_t result = pm_res[active_device_id].y / (mouse_xy_report_t)current_divisor;
        pm_res[active_device_id].y -= pointing_device_xy_clamp(result * (mouse_xy_report_t)current_divisor);
    } else {
        mouse_xy_report_t result = pm_res[active_device_id].x / (mouse_xy_report_t)current_divisor;
        pm_res[active_device_id].x -= pointing_device_xy_clamp(result * (mouse_xy_report_t)current_divisor);
    }
    return result;
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
 * @brief Release held keys of active device
 *
 *  releases held keys and sets them to the default value of 8
 */
static void pointing_mode_release_held_keys(void) {
    if(pm_mode_ids[active_device_id] < POINTING_MODE_MAP_START) return;
    map_id = pm_mode_ids[active_device_id] - POINTING_MODE_MAP_START;
    if (pm_held[active_device_id].v ^ PMK_NONE) {
        action_exec(MAKE_POINTING_MODE_EVENT(map_id, pm_held[active_device_id].v, false));
        pm_held[active_device_id].v = PMK_NONE;
    }
    if (pm_held[active_device_id].h ^ PMK_NONE) {
        action_exec(MAKE_POINTING_MODE_EVENT(map_id, pm_held[active_device_id].h, false));
        pm_held[active_device_id].h = PMK_NONE;
    }
}

/**
 * @brief Reset active device mode and mode data
 *
 *  Clear poiting device status, and set mode id to toggle mode id
 */
void pointing_mode_reset(void) {
    pointing_mode_release_held_keys();
    pm_mode_ids[active_device_id] = pm_base_modes[active_device_id];
    memcpy(&pm_res[active_device_id], 0, sizeof(pm_res[active_device_id]));
}

/**
 * @brief get precision of active device
 *
 * @return uint8_t active device precision divisor
 */
uint8_t pointing_mode_get_precision(void) {
    return pm_precisions[active_device_id];
}

/**
 * @brief set precision of active device
 *
 * @param[in] uint8_t precision
 */
void pointing_mode_set_precision(uint8_t precision) {
    if (precision > POINTING_MODE_PRECISION_MAX || !precision) {
        pm_precisions[active_device_id] = 1;
    } else {
        pm_precisions[active_device_id] = precision;
    }
}
//
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
    return pm_mode_ids[active_device_id];
}

/**
 * @brief set pointing mode id
 *
 * @param[in] mode_id uint8_t
 */
void pointing_mode_set_mode(uint8_t mode_id) {
    if (pointing_mode_get_mode() != mode_id) {
        pointing_mode_reset();
        pm_mode_ids[active_device_id] = mode_id;
    }
}

/**
 * @brief Access current toggled pointing mode
 *
 * @return uint8_t toggle pointing mode
 */
uint8_t pointing_mode_get_toggled_mode(void) {
    return pm_base_modes[active_device_id];
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
        pm_base_modes[active_device_id] = POINTING_MODE_DEFAULT;
    } else {
        pm_base_modes[active_device_id] = mode_id;
    }
    if (pointing_mode_get_mode() != pm_base_modes[active_device_id]) pointing_mode_reset();
}

/**
 * @brief Weak function to convert x/y axes to h/v
 *
 * The default uses accumulation based on inversion defines and
 * halts cursor movement
 *s
 * @params mouse_report[in]  report_mouse_t
 *
 * @return updated mouse_report report_mouse_t
 */
static void pointing_mode_axes_conv(report_mouse_t* mouse_report) {
    // !! fix this as these are signed ints so bit shifting needs to respect sign
    // set X axis of pointing mode for device
    if(mouse_report->x) {
#    ifdef POINTING_DEVICE_MODES_INVERT_X
        pm_res[active_device_id].x -= mouse_report->x;
        mouse_report->x = 0;
#    else
        pm_res[active_device_id].x += mouse_report->x;
        mouse_report->x = 0;
#    endif
    }
// set Y axis of pointing mode for device
    if(mouse_report->y) {
#    ifdef POINTING_DEVICE_MODES_INVERT_Y
        pm_res[active_device_id].y -= mouse_report->y;
        mouse_report->y = 0;
#    else
        pm_res[active_device_id].y += mouse_report->y;
        mouse_report->y = 0;
#    endif
    }
    return;
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
    divisor = get_pointing_mode_divisor_kb(pm_mode_ids[active_device_id], current_direction);
    divisor = get_pointing_mode_divisor_user(pm_mode_ids[active_device_id], current_direction);
    // built in divisors
    switch (mode_id) {
        case PM_NONE:
            divisor = 1;
            break;
        case PM_DRAG:
            divisor = POINTING_MODE_DRAG_DIVISOR;
            break;
    }
    divisor = divisor ? divisor : POINTING_MODE_DEFAULT_DIVISOR;
    divisor = clamp_uint16_to_8((uint16_t)divisor * (uint16_t)pm_precisions[active_device_id]);
    return divisor;
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
    if((abs(pm_res[active_device_id].x) + abs(pm_res[active_device_id].y)) < POINTING_MODE_THRESHOLD) {
        return PMD_NONE
    }
#    endif
    switch (pointing_mode_get_type(pointing_mode_get_mode()) & PMT_MODES) {
        case PMT_4WAY:
            if (abs(pm_res[active_device_id].x) > abs(pm_res[active_device_id].y)) {
                if (pm_res[active_device_id].x > 0) {
                    return PMD_RIGHT;
                } else {
                    return PMD_LEFT;
                }
            } else {
                if (pm_res[active_device_id].y > 0) {
                    return PMD_DOWN;
                } else {
                    return PMD_UP;
                }
            }
            break;
        case PMT_DPAD:
            uint8_t dir_out = PMD_NONE;
            if ((abs(pm_res[active_device_id].x) << 1) > abs(pm_res[active_device_id].y) {
                if (pm_res[active_device_id].x > 0) {
                    dir_out &= PMD_RIGHT;
                } else {
                    dir_out &= PMD_LEFT;
                }
            }
            if ((abs(pm_res[active_device_id].y) << 1) > abs(pm_res[active_device_id].x) {
                if (pm_res[active_device_id].y > 0) {
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
    mouse_xy_report_t count[]   = {0, 0};
    uint8_t key[]               = {0, 0};
    uint8_t mode_type = pointing_mode_get_type(pointing_mode_get_mode());
    switch (mode_type & PMT_MODES) {
        case PMT_4WAY:
            switch (current_pointing_mode_direction()) {
                case PMD_DOWN ... PMD_UP:
                    count[0] = pointing_mode_apply_divisor(1);
                    if (!count[0]) return; // exit if accumulated y is too low
                    key[0] = count[0] > 0? PMK_DOWN:PMK_UP;
                    pm_res[active_device_id].x = 0;
                    break;
                case PMD_LEFT ... PMD_RIGHT:
                    count[0] = pointing_mode_apply_divisor(0);
                    if (!count[0]) return; // exit if accumulated x is too low
                    key[0] = count[0] > 0? PMK_RIGHT:PMK_LEFT;
                    pm_res[active_device_id].y = 0;
                    break;
            }
            break;
        case PMT_DPAD:
            uint8_t dir = current_pointing_mode_direction();
            if(dir & PMD_HORI) {
                count[0] = pointing_mode_apply_divisor(0);
                pm_res[active_device_id].x = 0;
                key[0] = count[0] > 0? PMK_RIGHT:PMK_LEFT;
            }
            if(dir & PMD_VERT) {
                count[1] = pointing_mode_apply_divisor(1);
                pm_res[active_device_id].y = 0;
                key[1] = count[1] > 0? PMK_DOWN:PMK_UP;
            }
    }
    switch(mode_type & PMT_OPTS){
        case PMT_TAP:
            // Tap Horizontal/4-Way
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
            // Tap Vertical
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
            // Hold Horizontal/4-Way
            if(count[0]) {
                if(!(pm_held[active_device_id].v ^ PMK_NONE)) {
                    action_exec(MAKE_POINTING_MODE_EVENT(map_id, pm_held[active_device_id].v, false));
                }
                if(pm_held[active_device_id].v != key[0]) {
                    action_exec(MAKE_POINTING_MODE_EVENT(map_id, key[0], true));
                    pm_held[active_device_id].v = key[0];
                } else {
                    pm_held[active_device_id].v = PMK_NONE;
                }
            }
            // Hold Vertical
            if(count[1]) {
                if(pm_held[active_device_id].h ^ PMK_NONE) {
                    action_exec(MAKE_POINTING_MODE_EVENT(map_id, pm_held[active_device_id].h, false));
                }
                if(pm_held[active_device_id].h != key[0]) {
                    action_exec(MAKE_POINTING_MODE_EVENT(map_id, key[0], true));
                    pm_held[active_device_id].h = key[0];
                } else {
                    pm_held[active_device_id].h = PMK_NONE;
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
    pointing_mode_axes_conv(&mouse_report);
    pointing_mode_update();
    process_pointing_mode(&mouse_report);

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
static void process_pointing_mode(report_mouse_t* mouse_report) {
    // allow overwrite of pointing modes by user, and kb
    if (
        !(
            process_pointing_mode_user(&pm_res[active_device_id], &mouse_report) &&
            process_pointing_mode_kb(&pm_res[active_device_id], &mouse_report)
        )
    ) {
        return;
    }
    switch (pm_mode_ids[active_device_id]) {
        // if no pointing mode selected set back to mouse_report and clear
        case PM_NONE:
#    ifdef POINTING_DEVICE_MODES_INVERT_X
            mouse_report->x -= pointing_mode_apply_divisor(0);
#    else
            mouse_report->x += pointing_mode_apply_divisor(0);
#    endif
#    ifdef POINTING_DEVICE_MODES_INVERT_Y
            mouse_report->y -= pointing_mode_apply_divisor(1);
#    else
            mouse_report->y += pointing_mode_apply_divisor(1);
#    endif
            return;
        // drag scroll mode (sets mouse axes to mouse_report h & v with divisor)
        case PM_DRAG:
            mouse_report->h = pointing_device_hv_clamp(pointing_mode_apply_divisor(0));
            mouse_report->v = pointing_device_hv_clamp(pointing_mode_apply_divisor(1));
            return;

#    ifdef POINTING_MODE_MAP_ENABLE
        default:
            pointing_exec_mapping(pm_mode_ids[active_device_id] - POINTING_MODE_MAP_START);
#    endif
    }
    return;
}

/**
 * @brief User level processing of pointing device modes
 *
 * Used in pointing mode process allowing modification of mouse_report and pointing mode residuals
 * directly and returned bool controls the continued processing of pointing modes.
 *
 * NOTE: returning false will stop mode processing (for overwriting modes)
 *
 * @params pm_res[in] pointer to pointing_mode_residuals_t
 * @params mouse_report[in] pointer to report_mouse_t
 *
 * @return bool continue processing flag
 */
__attribute__((weak)) bool process_pointing_mode_user(pointing_mode_residuals_t* residuals, report_mouse_t* mouse_report) {
    return true; // continue processing
}

/**
 * @brief Keyboard level processing of pointing device modes
 *
 * Used in pointing mode process allowing modification of mouse_report and pointing mode residuals
 * directly and returned bool controls the continued processing of pointing modes.
 *
 * NOTE: returning false will stop mode processing (for overwriting modes)
 *
 * @params pm_res[in] pointer to pointing_mode_residuals_t
 * @params mouse_report[in]  pointer to report_mouse_t
 *
 * @return bool continue processing flag
 */
__attribute__((weak)) bool process_pointing_mode_kb(pointing_mode_residuals_t* residuals, report_mouse_t* mouse_report) {
    return true; // continue processing
}

/**
 * @brief Weakly defined function adding of pointing mode divisors at user level
 *
 * Takes in mode id and direction allowing for divisor values to be
 * determined based on these parameters
 *
 * @params mode_id[in]   uint8_t
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
 * @params mode_id[in]   uint8_t
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
