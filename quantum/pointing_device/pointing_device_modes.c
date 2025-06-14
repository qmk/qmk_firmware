/* Copyright 2025 Alabastard (@Alabastard-64)
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
static void pointing_modes_task(report_mouse_t* mouse_report);
static void pointing_modes_axes_conv(report_mouse_t* mouse_report);
static void pointing_modes_update_direction(void);
static void pointing_modes_update_divisor(void);
static void pointing_modes_update_type(void);
static void pointing_modes_release_held_keys(void);
static void pointing_modes_hold_decay(void);
static void pointing_modes_exec_mapping(uint8_t map_id);

// local variables
static uint8_t           current_direction = PMD_NONE;
static mouse_xy_report_t current_divisor   = POINTING_MODES_DEFAULT_DIVISOR;
static uint8_t           current_type      = PMT_4WAY | PMO_TAP;

// set up devices and active device
static uint8_t                    pm_mode_ids[]   = {[0 ... POINTING_MODES_DEVICE_CONTROL_COUNT - 1] = POINTING_MODES_DEFAULT_MODE};
static uint8_t                    pm_base_modes[] = {[0 ... POINTING_MODES_DEVICE_CONTROL_COUNT - 1] = POINTING_MODES_DEFAULT_MODE};
static mouse_xy_report_t          pm_precisions[] = {[0 ... POINTING_MODES_DEVICE_CONTROL_COUNT - 1] = POINTING_MODES_PRECISION_MIN};
static pointing_modes_residuals_t pm_res[]        = {[0 ... POINTING_MODES_DEVICE_CONTROL_COUNT - 1] = {.x = 0, .y = 0}};
static pointing_modes_held_keys_t pm_held[]       = {[0 ... POINTING_MODES_DEVICE_CONTROL_COUNT - 1] = {.h = PMK_NONE, .v = PMK_NONE}};
#    if POINTING_MODES_DEVICE_CONTROL_COUNT > 1
static uint8_t active_device_id = POINTING_MODES_DEFAULT_DEVICE;
#    else
static const uint8_t active_device_id = 0;
#    endif

// set up inline clamping functions ----------------------------------------------------------------------------
static inline mouse_xy_report_t pointing_device_xy_clamp(xy_clamp_range_t value) {
    if (value < MOUSE_REPORT_XY_MIN) {
        return MOUSE_REPORT_XY_MIN;
    } else if (value > MOUSE_REPORT_XY_MAX) {
        return MOUSE_REPORT_XY_MAX;
    } else {
        return value;
    }
}

static inline mouse_hv_report_t pointing_device_hv_clamp(hv_clamp_range_t value) {
    if (value < MOUSE_REPORT_HV_MIN) {
        return MOUSE_REPORT_HV_MIN;
    } else if (value > MOUSE_REPORT_HV_MAX) {
        return MOUSE_REPORT_HV_MAX;
    } else {
        return value;
    }
}

// Internal functions ------------------------------------------------------------------------------------------

/**
 * @brief Handle processing of pointing modes
 *
 * Takes in report_mouse_t and pointing_modes_device_t allowing manipulation of mouse_report
 * and pointing_mode via pointing_modes_set_device_settings
 *
 * @return mouse_report report_mouse_t
 */
static void pointing_modes_task(report_mouse_t* mouse_report) {
    // allow overwrite of pointing modes by user, and kb
    if (!(pointing_modes_task_user(mouse_report, &pm_res[active_device_id]) && pointing_modes_task_kb(mouse_report, &pm_res[active_device_id]))) {
        return;
    }
    switch (pm_mode_ids[active_device_id]) {
        // if no pointing mode selected set back to mouse_report and clear
        case PM_NONE:
            mouse_report->x += pointing_modes_apply_divisor(PM_X_AXIS);
            mouse_report->y += pointing_modes_apply_divisor(PM_Y_AXIS);
            return;
        // drag scroll mode (sets mouse axes to mouse_report h & v with divisor)
        case PM_DRAG:
            mouse_report->h += (mouse_hv_report_t)pointing_modes_apply_divisor(PM_H_AXIS);
            mouse_report->v += (mouse_hv_report_t)pointing_modes_apply_divisor(PM_V_AXIS);
            return;

        default:
            // check that the mode id is a valid map
            if (pointing_modes_get_mode() < POINTING_MODES_MAP_START) {
                pointing_modes_set_mode(PM_NONE);
                return;
            }
            pointing_modes_exec_mapping(pm_mode_ids[active_device_id] - POINTING_MODES_MAP_START);
    }
}

/**
 * @brief Converts mouse_report x/y to residuals
 *
 * The default uses accumulation based on inversion defines and
 * halts cursor movement
 *
 * @params mouse_report[in]  report_mouse_t
 *
 * @return updated mouse_report report_mouse_t
 */
static void pointing_modes_axes_conv(report_mouse_t* mouse_report) {
    uint8_t mode_type = pointing_modes_get_type();
    if (mouse_report->x && !(mode_type == PMT_VERT)) {
        if (mode_type & PMO_XINV) {
            pm_res[active_device_id].x -= mouse_report->x;
        } else {
            pm_res[active_device_id].x += mouse_report->x;
        }
    }
    mouse_report->x = 0;
    // set Y axis of pointing mode for device
    if (mouse_report->y && !(mode_type == PMT_HORI)) {
        if (mode_type & PMO_YINV) {
            pm_res[active_device_id].y -= mouse_report->y;
        } else {
            pm_res[active_device_id].y += mouse_report->y;
        }
    }
    mouse_report->y = 0;
}

/**
 * @brief local function to get single direction based on h/v
 *
 * Determines direction based on axis with largest magnitude
 *
 * NOTE: Defaults to PMD_DOWN
 *
 */
static void pointing_modes_update_direction(void) {
    current_direction = PMD_NONE;
    if ((abs(pm_res[active_device_id].x) + abs(pm_res[active_device_id].y)) <= POINTING_MODES_THRESHOLD) {
        return;
    }
    // This will detect all 8 directions: 2|Axis| >= |Other_Axis| allows for diagonal detection
    if ((abs(pm_res[active_device_id].x) << 1) >= abs(pm_res[active_device_id].y)) {
        if (pm_res[active_device_id].x > 0) {
            current_direction |= PMD_RIGHT;
        } else {
            current_direction |= PMD_LEFT;
        }
    }
    if ((abs(pm_res[active_device_id].y) << 1) >= abs(pm_res[active_device_id].x)) {
        if (pm_res[active_device_id].y > 0) {
            current_direction |= PMD_DOWN;
        } else {
            current_direction |= PMD_UP;
        }
    }
    if (pointing_modes_get_type() == PMT_4WAY) {
        // remove diagonal directions
        if ((current_direction & PMD_HORI) && (current_direction & PMD_VERT)) {
            if (abs(pm_res[active_device_id].x) > abs(pm_res[active_device_id].y)) {
                current_direction &= PMD_HORI;
            } else {
                current_direction &= PMD_VERT;
            }
        }
    }
}

/**
 * @brief local function to get pointing mode divisor
 *
 * Will handle default divisors and call weak kb and user functions
 *
 * NOTE: Expects that pointing mode and direction has been updated
 *
 */
static void pointing_modes_update_divisor(void) {
    uint8_t mode_id = pointing_modes_get_mode();
    // allow for user and keyboard overrides
    current_divisor = pointing_modes_get_divisor_user(mode_id, current_direction);
    if (!current_divisor) {
        current_divisor = pointing_modes_get_divisor_kb(mode_id, current_direction);
        if (!current_divisor) {
            // built in divisors
            switch (pointing_modes_get_mode()) {
                case PM_NONE:
                    current_divisor = 1;
                    break;
                case PM_DRAG:
                    current_divisor = POINTING_MODES_DRAG_DIVISOR;
                    break;
            }
        }
    }
    // check for zero divisor and apply precision
    current_divisor = current_divisor ? current_divisor : POINTING_MODES_DEFAULT_DIVISOR;
    current_divisor = abs(pointing_device_xy_clamp(current_divisor * pointing_modes_get_precision()));
}

/**
 * @brief update mode type based on current status
 *

 */
static void pointing_modes_update_type(void) {
    uint8_t mode_id = pointing_modes_get_mode();
    current_type    = 0x00;
    // allow for keyboard and user overrides
    current_type = pointing_modes_get_type_user(mode_id);
    if (current_type) {
        return;
    }
    current_type = pointing_modes_get_type_kb(mode_id);
    if (current_type) {
        return;
    }
    current_type = PMT_4WAY | PMO_TAP; // same as 0x00
}

/**
 * @brief Release held keys of active device
 *
 *  releases held keys and sets them to the default value of 8
 */
static void pointing_modes_release_held_keys(void) {
    if (pm_mode_ids[active_device_id] < POINTING_MODES_MAP_START) {
        return;
    }
    uint8_t map_id = pm_mode_ids[active_device_id] - POINTING_MODES_MAP_START;
    if (pm_held[active_device_id].v ^ PMK_NONE) {
        action_exec(MAKE_POINTING_MODES_EVENT(map_id, pm_held[active_device_id].v, false));
        pm_held[active_device_id].v = PMK_NONE;
    }
    if (pm_held[active_device_id].h ^ PMK_NONE) {
        action_exec(MAKE_POINTING_MODES_EVENT(map_id, pm_held[active_device_id].h, false));
        pm_held[active_device_id].h = PMK_NONE;
    }
}

/**
 * @brief Decrease residuals by the decay rate
 *
 * Decays residuals towards zero 0 by decay rate of active device
 *
 */
static void pointing_modes_hold_decay(void) {
    // Decay X
    if (pm_res[active_device_id].x > 0) {
        pm_res[active_device_id].x -= MIN((mouse_xy_report_t)POINTING_MODES_HOLD_DECAY_RATE, pm_res[active_device_id].x);
    }
    if (pm_res[active_device_id].x < 0) {
        pm_res[active_device_id].x += MIN((mouse_xy_report_t)POINTING_MODES_HOLD_DECAY_RATE, abs(pm_res[active_device_id].x));
    }
    // Decay Y
    if (pm_res[active_device_id].y > 0) {
        pm_res[active_device_id].y -= MIN((mouse_xy_report_t)POINTING_MODES_HOLD_DECAY_RATE, pm_res[active_device_id].y);
    }
    if (pm_res[active_device_id].y < 0) {
        pm_res[active_device_id].y += MIN((mouse_xy_report_t)POINTING_MODES_HOLD_DECAY_RATE, abs(pm_res[active_device_id].y));
    }
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
static void pointing_modes_exec_mapping(uint8_t map_id) {
    int8_t  count[] = {0, 0};
    uint8_t key[]   = {PMK_NONE, PMK_NONE};
    switch (current_type & PMT_MODES) {
        case PMT_4WAY ... PMT_8WAY:
            switch (current_direction) {
                case PMD_NONE:
                    break;
                case PMD_DOWN:
                    key[0] = PMK_DOWN;
                case PMD_UP:
                    if (key[0] == PMK_NONE) {
                        key[0] = PMK_UP;
                    }
                    count[0] = pointing_modes_apply_divisor(PM_Y_KEY);
                    if (!count[0]) {
                        break;
                    } // exit if accumulated y is too low
                    pm_res[active_device_id].x = 0;
                    break;
                case PMD_LEFT:
                    key[0] = PMK_LEFT;
                case PMD_RIGHT:
                    if (key[0] == PMK_NONE) {
                        key[0] = PMK_RIGHT;
                    }
                    count[0] = pointing_modes_apply_divisor(PM_X_KEY);
                    if (!count[0]) {
                        break;
                    } // exit if accumulated x is too low
                    pm_res[active_device_id].y = 0;
#    ifdef POINTING_MODES_8WAY_MAP_ENABLE
                    break;
                case PMD_DNLT:
                    key[0] = PMK_DOWNLEFT;
                case PMD_UPLT:
                    if (key[0] == PMK_NONE) {
                        key[0] = PMK_UPLEFT;
                    }
                case PMD_DNRT:
                    if (key[0] == PMK_NONE) {
                        key[0] = PMK_DOWNRIGHT;
                    }
                case PMD_UPRT:
                    if (key[0] == PMK_NONE) {
                        key[0] = PMK_UPRIGHT;
                    }
                    count[0] = pointing_modes_apply_divisor(PM_XY_KEY);
#    endif // POINTING_MODES_8WAY_MAP_ENABLE
            }
            break;
        case PMT_DPAD:
            if (current_direction & PMD_HORI) {
                count[PM_X_AXIS] = pointing_modes_apply_divisor(PM_X_KEY);
                key[PM_X_AXIS]   = (current_direction & PMD_RIGHT) ? PMK_RIGHT : PMK_LEFT;
            }
            if (current_direction & PMD_VERT) {
                count[PM_Y_AXIS] = pointing_modes_apply_divisor(PM_Y_KEY);
                key[PM_Y_AXIS]   = (current_direction & PMD_DOWN) ? PMK_DOWN : PMK_UP;
            }
    }
    switch (current_type & PMO_OPTS) {
        case PMO_TAP:
            // Tap Horizontal/4-Way/8-Way
            if (count[PM_X_AXIS]) {
                action_exec(MAKE_POINTING_MODES_EVENT(map_id, key[PM_X_AXIS], true));
#    if POINTING_MODES_TAP_DELAY > 0
                wait_ms(POINTING_MODES_TAP_DELAY);
#    endif // POINTING_MODES_TAP_DELAY > 0
                action_exec(MAKE_POINTING_MODES_EVENT(map_id, key[PM_X_AXIS], false));
            }
            // Tap Vertical
            if (count[PM_Y_AXIS]) {
                action_exec(MAKE_POINTING_MODES_EVENT(map_id, key[PM_Y_AXIS], true));
#    if POINTING_MODES_TAP_DELAY > 0
                wait_ms(POINTING_MODES_TAP_DELAY);
#    endif // POINTING_MODES_TAP_DELAY > 0
                action_exec(MAKE_POINTING_MODES_EVENT(map_id, key[PM_Y_AXIS], false));
            }
            break;

        case PMO_HOLD:
            // Hold: DPAD_HORI/2-Way/4-Way/8-Way
            if (count[PM_X_AXIS]) {
                if (pm_held[active_device_id].h != key[PM_X_AXIS]) {
                    if (pm_held[active_device_id].h != PMK_NONE) {
                        action_exec(MAKE_POINTING_MODES_EVENT(map_id, pm_held[active_device_id].h, false));
                    }
                    action_exec(MAKE_POINTING_MODES_EVENT(map_id, key[PM_X_AXIS], true));
                    pm_held[active_device_id].h = key[PM_X_AXIS];
                }
            }
            // Hold: DPAD_VERT
            if (count[PM_Y_AXIS]) {
                if (pm_held[active_device_id].v != key[PM_Y_AXIS]) {
                    if (pm_held[active_device_id].v != PMK_NONE) {
                        action_exec(MAKE_POINTING_MODES_EVENT(map_id, pm_held[active_device_id].v, false));
                    }
                    action_exec(MAKE_POINTING_MODES_EVENT(map_id, key[PM_Y_AXIS], true));
                    pm_held[active_device_id].v = key[PM_Y_AXIS];
                }
            }
            // Decay hold
            pointing_modes_hold_decay();
            // Hold: release on no movement
            if (current_direction == PMD_NONE) {
                pointing_modes_release_held_keys();
            }
    }
}

// External functions ------------------------------------------------------------------------------------------

/**
 * @brief apply divisor to specified device axis and update residuals
 *
 * Will apply the divisor to the specified axis (PM_X_AXIS, PM_Y_AXIS, PM_H_AXIS, PM_V_AXIS)
 * will use appropriate clamping in returned result and update residuals
 *
 * @params value[in] axis uint8_t
 *
 * @return quotient
 */
mouse_xy_report_t pointing_modes_apply_divisor(uint8_t axis) {
    mouse_xy_report_t result    = 0;
    uint8_t           mode_opts = pointing_modes_get_type() & PMO_OPTS;
    switch (axis) {
        case PM_X_AXIS:
            result = pm_res[active_device_id].x / current_divisor;
            pm_res[active_device_id].x -= pointing_device_xy_clamp(result * current_divisor);
            break;
        case PM_Y_AXIS:
            result = pm_res[active_device_id].y / current_divisor;
            pm_res[active_device_id].y -= pointing_device_xy_clamp(result * current_divisor);
            break;
        case PM_H_AXIS:
            result = pointing_device_hv_clamp(pm_res[active_device_id].x / current_divisor);
            pm_res[active_device_id].x -= pointing_device_xy_clamp(result * current_divisor);
            break;
        case PM_V_AXIS:
            result = pointing_device_hv_clamp(pm_res[active_device_id].y / current_divisor);
            pm_res[active_device_id].y -= pointing_device_xy_clamp(result * current_divisor);
            break;
        case PM_X_KEY:
            if (abs(pm_res[active_device_id].x) >= current_divisor) {
                if (pm_res[active_device_id].x > 0) {
                    result = 1;
                    if (mode_opts ^ PMO_HOLD) {
                        pm_res[active_device_id].x -= current_divisor;
                    }
                } else {
                    result = -1;
                    if (mode_opts ^ PMO_HOLD) {
                        pm_res[active_device_id].x += current_divisor;
                    }
                }
            }
            break;
        case PM_Y_KEY:
            if (abs(pm_res[active_device_id].y) >= current_divisor) {
                if (pm_res[active_device_id].y > 0) {
                    result = 1;
                    if (mode_opts ^ PMO_HOLD) {
                        pm_res[active_device_id].y -= current_divisor;
                    }
                } else {
                    result = -1;
                    if (mode_opts ^ PMO_HOLD) {
                        pm_res[active_device_id].y += current_divisor;
                    }
                }
            }
            break;
        case PM_XY_KEY:
            result = pointing_modes_apply_divisor(PM_X_KEY);
            result += abs(pointing_modes_apply_divisor(PM_Y_KEY));
            break;
    }
    return result;
}

/**
 * @brief Return device id of current controlled device
 *
 * @return current device id [uint8_t]
 */
uint8_t pointing_modes_get_active_device(void) {
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
void pointing_modes_set_active_device(uint8_t device_id) {
#    if (POINTING_MODES_NUM_DEVICES > 1)
    if (device_id > (POINTING_MODES_NUM_DEVICES - 1)) device_id = 0;
    active_device_id = device_id;
#    else
    ;
#    endif
}

/**
 * @brief Reset active device mode and mode data
 *
 *  Clear poiting device status, and set mode id to toggle mode id
 */
void pointing_modes_reset(void) {
    pointing_modes_release_held_keys();
    // must set these directly rather than calling pointing_modes_set_mode to avoid loops
    pm_mode_ids[active_device_id] = pm_base_modes[active_device_id];
    pm_res[active_device_id].x    = 0;
    pm_res[active_device_id].y    = 0;
}

/**
 * @brief get precision of active device
 *
 * @return mouse_xy_report_t active device precision divisor
 */
mouse_xy_report_t pointing_modes_get_precision(void) {
    return pm_precisions[active_device_id];
}

/**
 * @brief set precision of active device
 *
 * @param[in] mouse_xy_report_t precision
 */
void pointing_modes_set_precision(mouse_xy_report_t precision) {
    if (precision > POINTING_MODES_PRECISION_MAX || precision < POINTING_MODES_PRECISION_MIN) {
        pm_precisions[active_device_id] = POINTING_MODES_PRECISION_MIN;
    } else {
        pm_precisions[active_device_id] = precision;
    }
}

/**
 * @brief access current pointing mode id
 *
 * @return uint8_t current pointing mode id
 */
uint8_t pointing_modes_get_mode(void) {
    return pm_mode_ids[active_device_id];
}

/**
 * @brief set pointing mode id
 *
 * @param[in] mode_id uint8_t
 */
void pointing_modes_set_mode(uint8_t mode_id) {
    if (pointing_modes_get_mode() != mode_id) {
        pointing_modes_reset();
        pm_mode_ids[active_device_id] = mode_id;
    }
}

/**
 * @brief Access current toggled pointing mode
 *
 * @return uint8_t toggle pointing mode
 */
uint8_t pointing_modes_get_toggled_mode(void) {
    return pm_base_modes[active_device_id];
}

/**
 * @brief Toggle pointing mode id on/off
 *
 * Will change tg_mode_id setting to POINTING_MODES_DEFAULT_MODE when toggling "off"
 *
 * @param[in] mode_id uint8_t
 */
void pointing_modes_toggle_mode(uint8_t mode_id) {
    if (pointing_modes_get_toggled_mode() == mode_id) {
        pm_base_modes[active_device_id] = POINTING_MODES_DEFAULT_MODE;
    } else {
        pm_base_modes[active_device_id] = mode_id;
    }
    if (pointing_modes_get_mode() != pm_base_modes[active_device_id]) pointing_modes_reset();
}

/**
 * @brief update dependent parameters of pointing_mode
 *
 * Will update the direction and divisor values based on mode id and h, and v axis values
 *
 */
void pointing_modes_update(void) {
    pointing_modes_update_type();
    pointing_modes_update_direction();
    pointing_modes_update_divisor();
}

/**
 * @brief Access current pointing mode direction
 *
 * @return uint8_t direction
 */
uint8_t pointing_modes_get_direction(void) {
    return current_direction;
}

/**
 * @brief Access current pointing mode divisor
 *
 * @return mouse_xy_report_t divisor
 */
mouse_xy_report_t pointing_modes_get_divisor(void) {
    return current_divisor;
}

/**
 * @brief get current mode type
 *
 * @return uint8_t mode_type
 */
uint8_t pointing_modes_get_type(void) {
    return current_type;
}
/**
 * @brief Access active device residuals
 *
 * @return pointing_modes_residuals_t
 */
pointing_modes_residuals_t pointing_modes_get_residuals(void) {
    return pm_res[active_device_id];
}

/**
 * @brief Modify active device residuals
 *
 * @param[in] residuals pointing_modes_residuals_t
 */
void pointing_modes_set_residuals(pointing_modes_residuals_t residuals) {
    pm_res[active_device_id] = residuals;
    return;
}

/**
 * @brief Core function to handle pointing mode task
 *
 * Meant to be implemented in pointing_device_task
 *
 * @param[in] mouse_report report_mouse_t
 *
 * @return mouse_report report_mouse_t
 */
report_mouse_t pointing_modes_device_task(report_mouse_t mouse_report) {
    pointing_modes_update_type();
    pointing_modes_axes_conv(&mouse_report);
    pointing_modes_update_direction();
    pointing_modes_update_divisor();
    pointing_modes_task(&mouse_report);
    return mouse_report;
}

// Callback functions ------------------------------------------------------------------------------------------

/**
 * @brief User level processing of pointing device modes
 *
 * Used in pointing mode process allowing modification of mouse_report
 * directly and returned bool controls the continued processing of pointing modes.
 *
 * NOTE: returning false will stop mode processing (for overwriting modes)
 *
 * @params mouse_report[in] pointer to report_mouse_t
 *
 * @return bool continue processing flag
 */
__attribute__((weak)) bool pointing_modes_task_user(report_mouse_t* mouse_report, pointing_modes_residuals_t* residuals) {
    return true; // continue processing
}

/**
 * @brief Keyboard level processing of pointing device modes
 *
 * Used in pointing mode process allowing modification of mouse_report
 * directly and returned bool controls the continued processing of pointing modes.
 *
 * NOTE: returning false will stop mode processing (for overwriting modes)
 *
 * @params mouse_report[in]  pointer to report_mouse_t
 * @params residuals[in]     pointer to pointing_modes_residuals_t
 *
 * @return bool continue processing flag
 */
__attribute__((weak)) bool pointing_modes_task_kb(report_mouse_t* mouse_report, pointing_modes_residuals_t* residuals) {
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
 * @return divisor mouse_xy_report_t
 */
__attribute__((weak)) mouse_xy_report_t pointing_modes_get_divisor_user(uint8_t mode_id, uint8_t direction) {
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
 * @return divisor mouse_xy_report_t
 */
__attribute__((weak)) mouse_xy_report_t pointing_modes_get_divisor_kb(uint8_t mode_id, uint8_t direction) {
    return 0; // continue processing
}

/**
 * @brief Weakly defined function for setting pointing mode type at the user level
 *
 * Takes in mode id and returns current pointing mode type (PMT_4WAY, PMT_DPAD, PMT_8WAY, PMT_HORI, PMT_VERT).
 * Also mode options may be added to the mode type (PMO_HOLD, PMO_XINV, PMO_YINV)
 *
 * @params mode_id uint8_t
 *
 * @return pointing_modes_type uint8_t
 */
__attribute__((weak)) uint8_t pointing_modes_get_type_user(uint8_t mode_id) {
    return PMT_4WAY; // continue processing
}

/**
 * @brief Weakly defined function for setting pointing mode type and options at the user level
 *
 * Takes in mode id and returns current pointing mode type (PMT_4WAY, PMT_DPAD, PMT_8WAY, PMT_HORI, PMT_VERT).
 * Also mode options may be added to the mode type (PMO_HOLD, PMO_XINV, PMO_YINV)
 *
 * @params mode_id uint8_t
 *
 * @return pointing_modes_type uint8_t
 */
__attribute__((weak)) uint8_t pointing_modes_get_type_kb(uint8_t mode_id) {
    return PMT_4WAY; // continue processing
}

#endif // POINTING_DEVICE_MODES_ENABLE
