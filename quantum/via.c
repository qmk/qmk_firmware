/* Copyright 2019 Jason Williams (Wilba)
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

#ifndef RAW_ENABLE
#    error "RAW_ENABLE is not enabled"
#endif

#ifndef DYNAMIC_KEYMAP_ENABLE
#    error "DYNAMIC_KEYMAP_ENABLE is not enabled"
#endif

#include "quantum.h"

#include "via.h"
#include "raw_hid.h"
#include "dynamic_keymap.h"
#include "tmk_core/common/eeprom.h"
#include "version.h" // for QMK_BUILDDATE used in EEPROM magic

// Can be called in an overriding via_init_kb() to test if keyboard level code usage of
// EEPROM is invalid and use/save defaults.
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

// Sets VIA/keyboard level usage of EEPROM to valid/invalid
// Keyboard level code (eg. via_init_kb()) should not call this
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

// Flag QMK and VIA/keyboard level EEPROM as invalid.
// Used in bootmagic_lite() and VIA command handler.
// Keyboard level code should not need to call this.
void via_eeprom_reset(void)
{
    // Set the VIA specific EEPROM state as invalid.
    via_eeprom_set_valid(false);
    // Set the TMK/QMK EEPROM state as invalid.
    eeconfig_disable();
}

// Override bootmagic_lite() so it can flag EEPROM as invalid
// as well as jump to bootloader, thus performing a "factory reset"
// of dynamic keymaps and optionally backlight/other settings.
void bootmagic_lite(void)
{
    // The lite version of TMK's bootmagic based on Wilba.
    // 100% less potential for accidentally making the
    // keyboard do stupid things.

    // We need multiple scans because debouncing can't be turned off.
    matrix_scan();
#if defined(DEBOUNCE) && DEBOUNCE > 0
    wait_ms(DEBOUNCE * 2);
#else
    wait_ms(30);
#endif
    matrix_scan();

    // If the Esc and space bar are held down on power up,
    // reset the EEPROM valid state and jump to bootloader.
    // Assumes Esc is at [0,0].
    // This isn't very generalized, but we need something that doesn't
    // rely on user's keymaps in firmware or EEPROM.
    if (matrix_get_row(BOOTMAGIC_LITE_ROW) & (1 << BOOTMAGIC_LITE_COLUMN)) {
        // This is the only difference from the default implementation.
        via_eeprom_reset();
        // Jump to bootloader.
        bootloader_jump();
    }
}

// Override this at the keyboard code level to check
// VIA's EEPROM valid state and reset to defaults as needed.
// Used by keyboards that store their own state in EEPROM,
// for backlight, rotary encoders, etc.
// The override should not set via_eeprom_set_valid(true) as
// the caller also needs to check the valid state.
__attribute__((weak)) void via_init_kb(void) {
}

// Called by QMK core to initialize dynamic keymaps etc.
void via_init(void)
{
    // Let keyboard level test EEPROM valid state,
    // but not set it valid, it is done here.
    via_init_kb();

    // If the EEPROM has the magic, the data is good.
    // OK to load from EEPROM.
    if (via_eeprom_is_valid()) {
    } else	{
        // This resets the layout options
        via_set_layout_options(0);
        // This resets the keymaps in EEPROM to what is in flash.
        dynamic_keymap_reset();
        // This resets the macros in EEPROM to nothing.
        dynamic_keymap_macro_reset();
        // Save the magic number last, in case saving was interrupted
        via_eeprom_set_valid(true);
    }
}

// This is generalized so the layout options EEPROM usage can be
// variable, between 1 and 4 bytes.
uint32_t via_get_layout_options(void)
{
    uint32_t value = 0;
    // Start at the most significant byte
    void * source = (void *)(VIA_EEPROM_LAYOUT_OPTIONS_ADDR);
    for ( uint8_t i = 0; i < VIA_EEPROM_LAYOUT_OPTIONS_SIZE; i++ ) {
        value = value << 8;
        value |= eeprom_read_byte(source);
        source++;
    }
    return value;
}

void via_set_layout_options(uint32_t value)
{
    // Start at the least significant byte
    void * target = (void *)(VIA_EEPROM_LAYOUT_OPTIONS_ADDR+VIA_EEPROM_LAYOUT_OPTIONS_SIZE-1);
    for ( uint8_t i = 0; i < VIA_EEPROM_LAYOUT_OPTIONS_SIZE; i++ ) {
        eeprom_update_byte(target, value & 0xFF );
        value = value >> 8;
        target--;
    }
}

// Called by QMK core to process VIA-specific keycodes.
bool process_record_via(uint16_t keycode, keyrecord_t *record)
{
    // Handle macros
    if (record->event.pressed) {
        if ( keycode >= MACRO00 && keycode <= MACRO15 )
        {
            uint8_t id = keycode - MACRO00;
            dynamic_keymap_macro_send(id);
            return false;
        }
    }

    // TODO: ideally this would be generalized and refactored into
    // QMK core as advanced keycodes, until then, the simple case
    // can be available here to keyboards using VIA
    switch(keycode) {
        case FN_MO13:
            if (record->event.pressed) {
                layer_on(1);
                update_tri_layer(1, 2, 3);
            } else {
                layer_off(1);
                update_tri_layer(1, 2, 3);
            }
            return false;
            break;
        case FN_MO23:
            if (record->event.pressed) {
                layer_on(2);
                update_tri_layer(1, 2, 3);
            } else {
                layer_off(2);
                update_tri_layer(1, 2, 3);
            }
            return false;
            break;
    }
    return true;
}

// Keyboard level code can override this to handle custom messages from VIA.
// See raw_hid_receive() implementation.
// DO NOT call raw_hid_send() in the overide function.
__attribute__((weak)) void raw_hid_receive_kb(uint8_t *data, uint8_t length) {
    uint8_t *command_id = &(data[0]);
    *command_id = id_unhandled;
}

// VIA handles received HID messages first, and will route to
// raw_hid_receive_kb() for command IDs that are not handled here.
// This gives the keyboard code level the ability to handle the command
// specifically.
//
// raw_hid_send() is called at the end, with the same buffer, which was 
// possibly modified with returned values.
void raw_hid_receive( uint8_t *data, uint8_t length )
{
    uint8_t *command_id = &(data[0]);
    uint8_t *command_data = &(data[1]);
    switch ( *command_id )
    {
        case id_get_protocol_version:
        {
            command_data[0] = VIA_PROTOCOL_VERSION >> 8;
            command_data[1] = VIA_PROTOCOL_VERSION & 0xFF;
            break;
        }
        case id_get_keyboard_value:
        {
            switch ( command_data[0] )
            {
                case id_uptime:
                {
                    uint32_t value = timer_read32();
                    command_data[1] = (value >> 24 ) & 0xFF;
                    command_data[2] = (value >> 16 ) & 0xFF;
                    command_data[3] = (value >> 8 ) & 0xFF;
                    command_data[4] = value & 0xFF;
                    break;
                }
                case id_layout_options:
                {
                    uint32_t value = via_get_layout_options();
                    command_data[1] = (value >> 24 ) & 0xFF;
                    command_data[2] = (value >> 16 ) & 0xFF;
                    command_data[3] = (value >> 8 ) & 0xFF;
                    command_data[4] = value & 0xFF;
                    break;
                }
                case id_switch_matrix_state:
                {
#if ( (MATRIX_COLS/8+1)*MATRIX_ROWS <= 28 )
                    uint8_t i = 1;
                    for ( uint8_t row=0; row<MATRIX_ROWS; row++ ) {
                        matrix_row_t value = matrix_get_row(row);
#if (MATRIX_COLS > 24)
                        command_data[i++] = (value >> 24 ) & 0xFF;
#endif
#if (MATRIX_COLS > 16)
                        command_data[i++] = (value >> 16 ) & 0xFF;
#endif
#if (MATRIX_COLS > 8)
                        command_data[i++] = (value >> 8 ) & 0xFF;
#endif
                        command_data[i++] = value & 0xFF;
                    }
#endif
                    break;
                }
                default:
                {
                    raw_hid_receive_kb(data,length);
                    break;
                }
            }
            break;
        }
        case id_set_keyboard_value:
        {
            switch ( command_data[0] )
            {
                case id_layout_options:
                {
                    uint32_t value = ( (uint32_t)command_data[1] << 24 ) |
                                     ( (uint32_t)command_data[2] << 16 ) |
                                     ( (uint32_t)command_data[3] << 8 ) |
                                       (uint32_t)command_data[4];
                    via_set_layout_options(value);
                    break;
                }
                default:
                {
                    raw_hid_receive_kb(data,length);
                    break;
                }
            }
            break;
        }
        case id_dynamic_keymap_get_keycode:
        {
            uint16_t keycode = dynamic_keymap_get_keycode( command_data[0], command_data[1], command_data[2] );
            command_data[3] = keycode >> 8;
            command_data[4] = keycode & 0xFF;
            break;
        }
        case id_dynamic_keymap_set_keycode:
        {
            dynamic_keymap_set_keycode( command_data[0], command_data[1], command_data[2], ( command_data[3] << 8 ) | command_data[4] );
            break;
        }
        case id_dynamic_keymap_reset:
        {
            dynamic_keymap_reset();
            break;
        }
        case id_backlight_config_set_value:
        case id_backlight_config_get_value:
        case id_backlight_config_save:
        {
            raw_hid_receive_kb(data, length);
            break;
        }
        case id_dynamic_keymap_macro_get_count:
        {
            command_data[0] = dynamic_keymap_macro_get_count();
            break;
        }
        case id_dynamic_keymap_macro_get_buffer_size:
        {
            uint16_t size = dynamic_keymap_macro_get_buffer_size();
            command_data[0] = size >> 8;
            command_data[1] = size & 0xFF;
            break;
        }
        case id_dynamic_keymap_macro_get_buffer:
        {
            uint16_t offset = ( command_data[0] << 8 ) | command_data[1];
            uint16_t size = command_data[2]; // size <= 28
            dynamic_keymap_macro_get_buffer( offset, size, &command_data[3] );
            break;
        }
        case id_dynamic_keymap_macro_set_buffer:
        {
            uint16_t offset = ( command_data[0] << 8 ) | command_data[1];
            uint16_t size = command_data[2]; // size <= 28
            dynamic_keymap_macro_set_buffer( offset, size, &command_data[3] );
            break;
        }
        case id_dynamic_keymap_macro_reset:
        {
            dynamic_keymap_macro_reset();
            break;
        }
        case id_dynamic_keymap_get_layer_count:
        {
            command_data[0] = dynamic_keymap_get_layer_count();
            break;
        }
        case id_dynamic_keymap_get_buffer:
        {
            uint16_t offset = ( command_data[0] << 8 ) | command_data[1];
            uint16_t size = command_data[2]; // size <= 28
            dynamic_keymap_get_buffer( offset, size, &command_data[3] );
            break;
        }
        case id_dynamic_keymap_set_buffer:
        {
            uint16_t offset = ( command_data[0] << 8 ) | command_data[1];
            uint16_t size = command_data[2]; // size <= 28
            dynamic_keymap_set_buffer( offset, size, &command_data[3] );
            break;
        }
        case id_eeprom_reset:
        {
            via_eeprom_reset();
            break;
        }
        case id_bootloader_jump:
        {
            // Need to send data back before the jump
            // Informs host that the command is handled
            raw_hid_send( data, length );
            // Give host time to read it
            wait_ms(100);
            bootloader_jump();
            break;
        }
        default:
        {
            // The command ID is not known
            // Return the unhandled state
            *command_id = id_unhandled;
            break;
        }
    }

    // Return the same buffer, optionally with values changed
    // (i.e. returning state to the host, or the unhandled state).
    raw_hid_send( data, length );
}
