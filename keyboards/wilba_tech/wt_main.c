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
#include "tmk_core/common/eeprom.h"
#include "version.h" // for QMK_BUILDDATE used in EEPROM magic
#endif

// Called from via_init() if VIA_ENABLE
// Called from matrix_init_kb() if not VIA_ENABLE
void via_init_kb(void)
{
    // If the EEPROM has the magic, the data is good.
    // OK to load from EEPROM
    if (via_eeprom_is_valid()) {
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
    // Call via_init_kb() the same way as via_init(), with setting
    // EEPROM valid afterwards.
#ifndef VIA_ENABLE
    via_init_kb();
    via_eeprom_set_valid(true);
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

void led_set_kb(uint8_t usb_led)
{
#if RGB_BACKLIGHT_ENABLED || MONO_BACKLIGHT_ENABLED
    backlight_set_indicator_state(usb_led);
#endif // RGB_BACKLIGHT_ENABLED || MONO_BACKLIGHT_ENABLED
    led_set_user(usb_led);
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
void raw_hid_receive_kb(uint8_t *data, uint8_t length) {
    uint8_t *command_id = &(data[0]);
    uint8_t *command_data = &(data[1]);
    switch ( *command_id )
    {
#if RGB_BACKLIGHT_ENABLED || MONO_BACKLIGHT_ENABLED
        case id_lighting_set_value:
        {
            backlight_config_set_value(command_data);
            break;
        }
        case id_lighting_get_value:
        {
            backlight_config_get_value(command_data);
            break;
        }
        case id_lighting_save:
        {
            backlight_config_save();
            break;
        }
#endif // RGB_BACKLIGHT_ENABLED || MONO_BACKLIGHT_ENABLED
        default:
        {
            // Unhandled message.
            *command_id = id_unhandled;
            *command_data = *command_data; // force use of variable
            break;
        }
    }
    // DO NOT call raw_hid_send(data,length) here, let caller do this
}
#endif // VIA_ENABLE

//
// In the case of VIA being disabled, we still need to check if
// keyboard level EEPROM memory is valid before loading.
// Thus these are copies of the same functions in VIA, since
// the backlight settings reuse VIA's EEPROM magic/version,
// and the ones in via.c won't be compiled in.
//
// Yes, this is sub-optimal, and is only here for completeness
// (i.e. catering to the 1% of people that want wilba.tech LED bling
// AND want persistent settings BUT DON'T want to use dynamic keymaps/VIA).
//
#ifndef VIA_ENABLE

bool via_eeprom_is_valid(void)
{
    char *p = QMK_BUILDDATE; // e.g. "2019-11-05-11:29:54"
    uint8_t magic0 = ( ( p[2] & 0x0F ) << 4 ) | ( p[3]  & 0x0F );
    uint8_t magic1 = ( ( p[5] & 0x0F ) << 4 ) | ( p[6]  & 0x0F );
    uint8_t magic2 = ( ( p[8] & 0x0F ) << 4 ) | ( p[9]  & 0x0F );

    return (eeprom_read_byte( (void*)VIA_EEPROM_MAGIC_ADDR+0 ) == magic0 &&
            eeprom_read_byte( (void*)VIA_EEPROM_MAGIC_ADDR+1 ) == magic1 &&
            eeprom_read_byte( (void*)VIA_EEPROM_MAGIC_ADDR+2 ) == magic2 );
}

void via_eeprom_set_valid(bool valid)
{
    char *p = QMK_BUILDDATE; // e.g. "2019-11-05-11:29:54"
    uint8_t magic0 = ( ( p[2] & 0x0F ) << 4 ) | ( p[3]  & 0x0F );
    uint8_t magic1 = ( ( p[5] & 0x0F ) << 4 ) | ( p[6]  & 0x0F );
    uint8_t magic2 = ( ( p[8] & 0x0F ) << 4 ) | ( p[9]  & 0x0F );

    eeprom_update_byte( (void*)VIA_EEPROM_MAGIC_ADDR+0, valid ? magic0 : 0xFF);
    eeprom_update_byte( (void*)VIA_EEPROM_MAGIC_ADDR+1, valid ? magic1 : 0xFF);
    eeprom_update_byte( (void*)VIA_EEPROM_MAGIC_ADDR+2, valid ? magic2 : 0xFF);
}

void via_eeprom_reset(void)
{
    // Set the VIA specific EEPROM state as invalid.
    via_eeprom_set_valid(false);
    // Set the TMK/QMK EEPROM state as invalid.
    eeconfig_disable();
}

#endif // VIA_ENABLE
