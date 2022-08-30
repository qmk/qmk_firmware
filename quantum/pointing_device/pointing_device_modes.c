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

#ifdef POINTING_DEVICE_MODES_ENABLE

#    include "pointing_device_modes.h"

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

static report_mouse_t process_pointing_mode(pointing_mode_t pointing_mode, report_mouse_t mouse_report);
static uint8_t        get_pointing_device_direction(void);
static uint8_t        get_pointing_mode_divisor(void);

// set up context and functions if using two pointing devices
#    if defined(SPLIT_POINTING_ENABLE) && defined(POINTING_DEVICE_COMBINED)
/* set up local context for storing current values */
static context_pointing_mode_t pointing_mode_context = {.config.is_left = POINTING_MODES_LEFT_DEFAULT, .config.tg_mode_id = POINTING_MODE_DEFAULT, .mode.id = POINTING_MODE_DEFAULT, .mode.divisor = POINTING_DEFAULT_DIVISOR};

/**
 * @brief Check if left side is controlled by pointing mode framework
 *
 * @return is left side active [bool]
 */
bool is_pointing_mode_on_left(void) {
    return pointing_mode_context.config.is_left;
}

/**
 * @brief Allow changing of active side
 *
 * will change which side (left/right) is controlled by pointing mode framework
 */
void pointing_mode_switch_hands(void) {
    pointing_mode_context.config.is_left ^= 1;
}
#    else
static context_pointing_mode_t pointing_mode_context = {.config.tg_mode_id = POINTING_MODE_DEFAULT, .mode.id = POINTING_MODE_DEFAULT, .mode.divisor = POINTING_DEFAULT_DIVISOR};
#    endif

/**
 * @brief Reset pointing mode data
 *
 *  Clear poiting mode and set to defaults
 */
static void pointing_mode_reset(void) {
    memset(&pointing_mode_context.mode, 0, sizeof(pointing_mode_t));
    pointing_mode_context.mode.id      = pointing_mode_context.config.tg_mode_id;
    pointing_mode_context.mode.divisor = POINTING_DEFAULT_DIVISOR;
}

/**
 * @brief set current pointing mode data
 *
 * @param[in] pointing_mode pointing_mode_t
 */
void set_pointing_mode(pointing_mode_t pointing_mode) {
    // skip if same
    if (!memcmp(&pointing_mode_context.mode, &pointing_mode, sizeof(pointing_mode_t))) return;
    memcpy(&pointing_mode_context.mode, &pointing_mode, sizeof(pointing_mode_t));
    dprintf("PM status saved!");
    // Prevent zero divisor
    if (!pointing_mode_context.mode.divisor) {
        pointing_mode_context.mode.divisor = POINTING_DEFAULT_DIVISOR;
    }
}

/**
 * @brief access current pointing mode id
 *
 * @return uint8_t current pointing mode id
 */
uint8_t get_pointing_mode_id(void) {
    return pointing_mode_context.mode.id;
}

/**
 * @brief set pointing mode id
 *
 * @param[in] mode_id uint8_t
 */
void set_pointing_mode_id(uint8_t mode_id) {
    if (pointing_mode_context.mode.id != mode_id) {
        pointing_mode_reset();
        pointing_mode_context.mode.id = mode_id;
        dprintf("PMID Set: %d\n", mode_id);
    }
}

/**
 * @brief Toggle pointing mode id on/off
 *
 * Will change tg_mode_id setting to POINTING_MODE_DEFAULT when toggling "off"
 *
 * @param[in] mode_id uint8_t
 */
void toggle_pointing_mode_id(uint8_t mode_id) {
    if (pointing_mode_context.config.tg_mode_id == mode_id) {
        pointing_mode_context.config.tg_mode_id = POINTING_MODE_DEFAULT;
        dprintf("Toggled PMID: %d\n Off", mode_id);
    } else {
        pointing_mode_context.config.tg_mode_id = mode_id;
        dprintf("Toggled PMID: %d\n On", mode_id);
    }
    if (pointing_mode_context.mode.id != pointing_mode_context.config.tg_mode_id) pointing_mode_reset();
}

/**
 * @brief Access current toggled pointing mode
 *
 * @return uint8_t toggle pointing mode
 */
uint8_t get_toggled_pointing_mode_id(void) {
    return pointing_mode_context.config.tg_mode_id;
}

/**
 * @brief Weak function to convert x/y axes to h/v
 *
 * The default uses accumulation based on inversion defines and
 * halts cursor movement
 *
 * @params pointing_mode[in] pointing_mode_t
 * @params mouse_report[in]  report_mouse_t
 *
 * @return updated mouse_report report_mouse_t
 */
__attribute__((weak)) report_mouse_t pointing_modes_axes_conv(pointing_mode_t pointing_mode, report_mouse_t mouse_report) {
#    ifdef POINTING_DEVICE_INVERT_H
    pointing_mode.h -= mouse_report.x;
#    else
    pointing_mode.h += mouse_report.x;
#    endif
#    ifdef POINTING_DEVICE_INVERT_V
    pointing_mode.v -= mouse_report.y;
#    else
    pointing_mode.v += mouse_report.y;
#    endif
    set_pointing_mode(pointing_mode);
    mouse_report.x = 0;
    mouse_report.y = 0;
    return mouse_report;
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
static uint8_t get_pointing_device_direction(void) {
    if (abs(pointing_mode_context.mode.h) > abs(pointing_mode_context.mode.v)) {
        if (pointing_mode_context.mode.h > 0) {
            return PD_RIGHT;
        } else {
            return PD_LEFT;
        }
    } else {
        if (pointing_mode_context.mode.v > 0) {
            return PD_UP;
        } else {
            return PD_DOWN;
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
 * @return divisor uint8_t
 */
static uint8_t get_pointing_mode_divisor(void) {
    // allow for user and keyboard overrides
    uint8_t divisor;
    divisor = get_pointing_mode_divisor_user(pointing_mode_context.mode.id, pointing_mode_context.mode.direction);
    if (divisor) return divisor;
    divisor = get_pointing_mode_divisor_kb(pointing_mode_context.mode.id, pointing_mode_context.mode.direction);
    if (divisor) return divisor;

    // built in mode divisors
    switch (pointing_mode_context.mode.id) {
        case PM_HISTORY:
            divisor = POINTING_HISTORY_DIVISOR;
            break;
#    ifdef EXTRAKEY_ENABLE
        case PM_VOLUME:
            divisor = POINTING_VOLUME_DIVISOR;
            break;
#    endif
        case PM_CARET:
            divisor = pointing_mode_context.mode.direction < PD_LEFT ? POINTING_CARET_DIVISOR_V : POINTING_CARET_DIVISOR_H;
            break;

        case PM_PRECISION:
            divisor = POINTING_PRECISION_DIVISOR;
            break;

        case PM_DRAG:
            divisor = POINTING_DRAG_DIVISOR;
            break;
    }
    // Prevent 0 divisor
    if (!divisor) divisor = POINTING_DEFAULT_DIVISOR;

    return divisor;
}

/**
 * @brief update dependent parameters of pointing_mode
 *
 * Will update the direction and divisor values based on mode id and h, and v axis values
 *
 */
void pointing_mode_update(void) {
    pointing_mode_context.mode.direction = get_pointing_device_direction();
    pointing_mode_context.mode.divisor   = get_pointing_mode_divisor();
}

/**
 * @brief Tap keycodes based on mode axis values
 *
 * Will translate internal h & v axes into keycode taps.
 * Uses input ordered DOWN, UP, LEFT, RIGHT and will output 1 keytap/divisor
 * and will update the h and v values.
 *
 * NOTE: favours staying on axis and weakly favours the horizontal over the vertical axis
 *
 * @params kc_left[in]  uint16_t keycode for negative h
 * @params kc_down[in]  uint16_t keycode for negative v
 * @params kc_up[in]    uint16_t keycode for positive v
 * @params kc_right[in] uint16_t keycode for positive h
 */
void pointing_tap_codes(uint16_t kc_left, uint16_t kc_down, uint16_t kc_up, uint16_t kc_right) {
    uint16_t kc_direction = 0;
    int16_t  count        = 0;

    switch (pointing_mode_context.mode.direction) {
        case PD_DOWN:
            kc_direction = kc_down;
            break;

        case PD_UP:
            kc_direction = kc_up;
            break;

        case PD_LEFT:
            kc_direction = kc_left;
            break;

        case PD_RIGHT:
            kc_direction = kc_right;
            break;
    }

    switch (pointing_mode_context.mode.direction) {
        case PD_DOWN ... PD_UP:
            count = pointing_mode_context.mode.v / (int16_t)pointing_mode_context.mode.divisor;
            if (!count) return;
            pointing_mode_context.mode.v -= count * (int16_t)pointing_mode_context.mode.divisor;
            pointing_mode_context.mode.h = 0;
            break;
        case PD_LEFT ... PD_RIGHT:
            count = pointing_mode_context.mode.h / (int16_t)pointing_mode_context.mode.divisor;
            if (!count) return;
            pointing_mode_context.mode.h -= count * (int16_t)pointing_mode_context.mode.divisor;
            pointing_mode_context.mode.v = 0;
            break;
    }
    // skip if no key (but allow for axes update)
    if (kc_direction == KC_NO) return;
    uint8_t taps = abs(count);

    for (uint8_t i = 0; i < taps; i++) {
        tap_code16_delay(kc_direction, POINTING_TAP_DELAY);
    }
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
report_mouse_t pointing_device_modes_task(report_mouse_t mouse_report) {
    // skip all processing if pointing mode is PM_NONE
    if (pointing_mode_context.mode.id == PM_NONE) return mouse_report;

    mouse_report = pointing_modes_axes_conv(pointing_mode_context.mode, mouse_report);
    pointing_mode_update();
    mouse_report = process_pointing_mode(pointing_mode_context.mode, mouse_report);

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
    // allow overwrite of pointing modes by kb, user and map spaces user is given priority
    if (!(process_pointing_mode_user(pointing_mode, &mouse_report) && process_pointing_mode_kb(pointing_mode, &mouse_report))) {
        return mouse_report;
    }
#    if (POINTING_MODE_MAP_COUNT > 0)
    if (pointing_mode.id <= (POINTING_MODE_MAP_COUNT - 1)) {
        pointing_tap_codes(POINTING_MODE_MAP(pointing_mode.id));
        return mouse_report;
    }
#    endif
    switch (pointing_mode.id) {
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
        // caret mode (uses arrow keys to move cursor)
        case PM_CARET:
            pointing_tap_codes(KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT);
            break;

        // precision mode  (reduce x y sensitivity temporarily)
        case PM_PRECISION:
#    ifdef POINTING_DEVICE_INVERT_H
            mouse_report.x -= pointing_mode.h / (int16_t)pointing_mode.divisor;
            pointing_mode.h += mouse_report.x * (int16_t)pointing_mode.divisor;
#    else
            mouse_report.x += pointing_mode.h / (int16_t)pointing_mode.divisor;
            pointing_mode.h -= mouse_report.x * (int16_t)pointing_mode.divisor;
#    endif
#    ifdef POINTING_DEVICE_INVERT_V
            mouse_report.y -= pointing_mode.v / (int16_t)pointing_mode.divisor;
            pointing_mode.v += mouse_report.y * (int16_t)pointing_mode.divisor;
#    else
            mouse_report.y += pointing_mode.v / (int16_t)pointing_mode.divisor;
            pointing_mode.v -= mouse_report.y * (int16_t)pointing_mode.divisor;
#    endif
            set_pointing_mode(pointing_mode);
            break;

        // drag scroll mode (sets mouse axes to mouse_report h & v with divisor)
        case PM_DRAG:
            mouse_report.h = pointing_mode.h / (int16_t)pointing_mode.divisor;
            mouse_report.v = pointing_mode.v / (int16_t)pointing_mode.divisor;
            pointing_mode.h -= mouse_report.h * (int16_t)pointing_mode.divisor;
            pointing_mode.v -= mouse_report.v * (int16_t)pointing_mode.divisor;
            set_pointing_mode(pointing_mode);
            break;
    }
    return mouse_report;
}

/**
 * @brief Handle pointing mode change keypress: Momentary
 *
 * Will set pointing mode id when key is pressed and reset on release
 *
 * NOTE: if pointing mode has changed since key down, reset is skipped
 *
 * @params mode_id[in] uint8_t
 * @params record[in] keyrecord_t* pointer
 */
void pointing_mode_key_momentary(uint8_t mode_id, keyrecord_t* record) {
    if (record->event.pressed) {
        set_pointing_mode_id(mode_id);
    } else {
        // reset mode only if the current mode matches (in case mode has changed before release)
        if (pointing_mode_context.mode.id == mode_id) pointing_mode_reset();
    }
}
/**
 * @brief Handle pointing mode change keypress: Toggle
 *
 * Toggle pointing mode on key release
 *
 * @params mode_id[in] uint8_t
 * @params record[in] keyrecord_t* pointer
 */
void pointing_mode_key_toggle(uint8_t mode_id, keyrecord_t* record) {
    // only attempt to change mode on key release event (matches layer toggle behaviour)
    if (!record->event.pressed) toggle_pointing_mode_id(mode_id);
}

/**
 * @brief Core function to process pointing mode key records
 *
 * Only handles built in keyrecords and functions
 *
 * @params keycode[in] uint16_t
 * @params record[in] keyrecord_t pointer
 *
 * @return should keycode processing continue bool
 */
bool process_pointing_mode_records(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        // handle built in keycods for bottom 16 pointing modes (0-15)
        // momentary
        case POINTING_MODE_MO ... POINTING_MODE_MO_MAX:
            pointing_mode_key_momentary((keycode - POINTING_MODE_MO) & (POINTING_MODE_COUNT - 1), record);
            return true; // allow further processing
        // toggle
        case POINTING_MODE_TG ... POINTING_MODE_TG_MAX:
            pointing_mode_key_toggle((keycode - POINTING_MODE_TG) & (POINTING_MODE_COUNT - 1), record);
            return true; // allow further processing
        // end
        default:
            return true;
    }
}

/**
 * @brief Weak function for user level adding of pointing device modes
 *
 * Takes pointing_mode_t struct, and pointer to a report_mouse_t struct
 * and returns a bool to stop allowing updating of both pointing_mode (using
 * set_pointing_mode) and changing the mouse_report using the pointer
 *
 * NOTE: returning false will stop mode processing (for overwriting modes)
 *
 * @params pointing_mode[in] pointing_mode_t
 * @params mouse_report[in] pointer to report_mouse_t
 *
 * @return bool continue processing flag
 */
__attribute__((weak)) bool process_pointing_mode_user(pointing_mode_t pointing_mode, report_mouse_t* mouse_report) {
    return true; // continue processing
}

/**
 * @brief Weak function for keyboard level adding of pointing device modes
 *
 * Takes pointing_mode_t struct, and pointer to a report_mouse_t struct
 * and returns a bool to stop allowing updating of both pointing_mode (using
 * set_pointing_mode) and changing the mouse_report using the pointer
 *
 * NOTE: returning false will stop mode processing (for overwriting modes)
 *
 * @params pointing_mode[in] pointing_mode_t
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
 * @params pointing_mode[in] uint8_t
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
 * @params pointing_mode[in] uint8_t
 * @params direction[in] uint8_t
 *
 * @return divisor uint8_t
 */
__attribute__((weak)) uint8_t get_pointing_mode_divisor_kb(uint8_t mode_id, uint8_t direction) {
    return 0; // continue processing
}

#endif // POINTING_DEVICE_MODES_ENABLE
