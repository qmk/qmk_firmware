/* Copyright 2018 Jason Williams (Wilba)
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

#include "quantum.h"

// Check that no backlight functions are called
#if RGB_BACKLIGHT_ENABLED
#include "keyboards/wilba_tech/wt_rgb_backlight.h"
#endif // RGB_BACKLIGHT_ENABLED
#if MONO_BACKLIGHT_ENABLED
#include "keyboards/wilba_tech/wt_mono_backlight.h"
#endif // MONO_BACKLIGHT_ENABLED

#include "via.h"

#ifndef VIA_ENABLE
#include "eeprom.h"
#include "version.h" // for QMK_BUILDDATE used in EEPROM magic
#endif

// Called from via_init() if VIA_ENABLE
// Called from matrix_init_kb() if not VIA_ENABLE
void wt_main_init(void)
{
    // This checks both an EEPROM reset (from bootmagic lite, keycodes)
    // and also firmware build date (from via_eeprom_is_valid())
    if (eeconfig_is_enabled()) {
#if RGB_BACKLIGHT_ENABLED || MONO_BACKLIGHT_ENABLED
        backlight_config_load();
#endif // RGB_BACKLIGHT_ENABLED || MONO_BACKLIGHT_ENABLED
    } else	{
#if RGB_BACKLIGHT_ENABLED || MONO_BACKLIGHT_ENABLED
        // If the EEPROM has not been saved before, or is out of date,
        // save the default values to the EEPROM. Default values
        // come from construction of the backlight_config instance.
        backlight_config_save();
#endif // RGB_BACKLIGHT_ENABLED || MONO_BACKLIGHT_ENABLED

        // DO NOT set EEPROM valid here, let caller do this
    }

#if RGB_BACKLIGHT_ENABLED || MONO_BACKLIGHT_ENABLED
    // Initialize LED drivers for backlight.
    backlight_init_drivers();

    backlight_timer_init();
    backlight_timer_enable();
#endif // RGB_BACKLIGHT_ENABLED || MONO_BACKLIGHT_ENABLED
}

void matrix_init_kb(void)
{
    // If VIA is disabled, we still need to load backlight settings.
    // Call via_init_kb() the same way as via_init_kb() does.
#ifndef VIA_ENABLE
    wt_main_init();
#endif // VIA_ENABLE

    matrix_init_user();
}

void matrix_scan_kb(void)
{
#if RGB_BACKLIGHT_ENABLED || MONO_BACKLIGHT_ENABLED
    // This only updates the LED driver buffers if something has changed.
    backlight_update_pwm_buffers();
#endif // RGB_BACKLIGHT_ENABLED || MONO_BACKLIGHT_ENABLED
    matrix_scan_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record)
{
#if RGB_BACKLIGHT_ENABLED || MONO_BACKLIGHT_ENABLED
    process_record_backlight(keycode, record);
#endif // RGB_BACKLIGHT_ENABLED || MONO_BACKLIGHT_ENABLED

    return process_record_user(keycode, record);
}

void suspend_power_down_kb(void)
{
#if RGB_BACKLIGHT_ENABLED || MONO_BACKLIGHT_ENABLED
    backlight_set_suspend_state(true);
#endif // RGB_BACKLIGHT_ENABLED || MONO_BACKLIGHT_ENABLED
}

void suspend_wakeup_init_kb(void)
{
#if RGB_BACKLIGHT_ENABLED || MONO_BACKLIGHT_ENABLED
    backlight_set_suspend_state(false);
#endif // RGB_BACKLIGHT_ENABLED || MONO_BACKLIGHT_ENABLED
}

// Moving this to the bottom of this source file is a workaround
// for an intermittent compiler error for Atmel compiler.
#ifdef VIA_ENABLE
void via_init_kb(void) {
    wt_main_init();
}

void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    uint8_t *command_id        = &(data[0]);
    uint8_t *channel_id        = &(data[1]);
    uint8_t *value_id_and_data = &(data[2]);

#if RGB_BACKLIGHT_ENABLED || MONO_BACKLIGHT_ENABLED
    if ( *channel_id == id_custom_channel ) {
        switch ( *command_id )
        {
            case id_custom_set_value:
            {
                backlight_config_set_value(value_id_and_data);
                break;
            }
            case id_custom_get_value:
            {
                backlight_config_get_value(value_id_and_data);
                break;
            }
            case id_custom_save:
            {
                backlight_config_save();
                break;
            }
            default:
            {
                // Unhandled message.
                *command_id = id_unhandled;
                break;
            }
        }
        return;
    }
#else
        *command_id = id_unhandled;
        *channel_id = *channel_id; // force use of variable
        *value_id_and_data = *value_id_and_data; // force use of variable
#endif // RGB_BACKLIGHT_ENABLED || MONO_BACKLIGHT_ENABLED

    // DO NOT call raw_hid_send(data,length) here, let caller do this
}

void via_set_device_indication(uint8_t value)
{
#if RGB_BACKLIGHT_ENABLED || MONO_BACKLIGHT_ENABLED
    backlight_device_indication(value);
#endif // RGB_BACKLIGHT_ENABLED || MONO_BACKLIGHT_ENABLED
}

#endif // VIA_ENABLE
