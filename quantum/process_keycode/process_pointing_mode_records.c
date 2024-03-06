/* Copyright 2023 Alabastard (@Alabastard)
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

#ifdef POINTING_DEVICE_MODE_ENABLE

#    include "process_pointing_mode_records.h"

/**
 * @brief Handle pointing mode change keypress: Momentary
 *
 * Will set pointing mode id when key is pressed and reset on release
 *
 * NOTE: if pointing mode has changed since key down, reset is skipped
 *
 * @params mode_id[in] uint8_t
 * @params pressed[in] bool
 */
void pointing_mode_key_momentary(uint8_t mode_id, bool pressed) {
    if (pressed) {
        pointing_mode_set_mode(mode_id);
    } else if (pointing_mode_get_mode() == mode_id) {
        // reset mode only if the current mode matches (in case mode has changed before release)
        pointing_mode_reset();
    }
}

/**
 * @brief Handle pointing mode change keypress: Toggle
 *
 * Toggle pointing mode on key release of active device
 *
 * @params mode_id[in] uint8_t
 * @params pressed[in] bool
 */
void pointing_mode_key_toggle(uint8_t mode_id, bool pressed) {
    // only attempt to change mode on key release event (matches layer toggle behaviour)
    if (!pressed) pointing_mode_toggle_mode(mode_id);
}

/**
 * @brief Handle keypress to change active device
 *
 * Set active device id to device[in] on key release
 *
 * @params device[in]  uint8_t
 * @params pressed[in] bool
 */
void pointing_mode_key_set_device(uint8_t device, bool pressed) {
    if (!pressed) pointing_mode_set_active_device(device);
}

/**
 * @brief Handle keypress to change precision of active device
 *
 * @params precision[in]  uint8_t
 * @params pressed[in]    bool
 */
void pointing_mode_key_set_precision(uint8_t precision, bool pressed) {
    if (!pressed) pointing_mode_set_precision(precision);
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
        case QK_POINTING_MODE_MO ... QK_POINTING_MODE_MO_MAX:
            pointing_mode_key_momentary((keycode - QK_POINTING_MODE_MO) & (QK_POINTING_MODE_MO_MAX - QK_POINTING_MODE_MO), record->event.pressed);
            return true; // allow further processing
        // toggle
        case QK_POINTING_MODE_TG ... QK_POINTING_MODE_TG_MAX:
            pointing_mode_key_toggle((keycode - QK_POINTING_MODE_TG) & (QK_POINTING_MODE_TG_MAX - QK_POINTING_MODE_TG), record->event.pressed);
            return true; // allow further processing

        // Cycle through precision values
        case QK_PM_CYCLE_PRECISION:
            pointing_mode_key_set_precision(pointing_mode_get_precision() + POINTING_MODE_PRECISION_STEP, record->event.pressed);
            return true; // allow further processing
        case QK_PM_PRECISION_INCREASE:

#    if (POINTING_MODE_NUM_DEVICES > 1)
        // utils: Cycle devices
        case QK_PM_CYCLE_DEVICES:
            pointing_mode_key_set_device(pointing_mode_get_active_device() + 1, record->event.pressed);
            return true; // allow further processing
        // cut the below two functions
        // utils: DEVICE RIGHT
        case QK_PM_DEVICE_RIGHT:
            pointing_mode_key_set_device(PM_RIGHT_DEVICE, record->event.pressed);
            return true; // allow further processing
        // utils: DEVICE LEFT
        case QK_PM_DEVICE_LEFT:
            pointing_mode_key_set_device(PM_RIGHT_DEVICE, record->event.pressed);
            return true; // allow further processing
#    endif

        // end
        default:
            return true;
    }
}

#endif // POINTING_DEVICE_MODES_ENABLE
