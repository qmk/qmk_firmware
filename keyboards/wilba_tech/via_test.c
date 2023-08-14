// Copyright 2022 Jason Williams (@wilba)
// SPDX-License-Identifier: GPL-2.0-or-later

// This is a test harness for VIA custom UI.
//
// It handles channel IDs 0-7, value IDs 0-7.
//
// It's useful for testing custom UI on a PCB without compiling in
// features, especially features that will cause firmware to freeze
// if the PCB doesn't have support.
// 
// To use:
// - add `SRC = keyboards/wilba_tech/via_test.c` to rules.mk
// - add `#define VIA_EEPROM_CUSTOM_CONFIG_SIZE 128` to config.h
//   (or change to match CHANNELS*VALUES*2)

#include "quantum.h"
#include "via.h"

#ifdef VIA_ENABLE

#define CHANNELS 8
#define VALUES 8
uint8_t g_value[CHANNELS][VALUES][2];

void values_init(void)
{
    for ( uint8_t channel_id = 0; channel_id < CHANNELS; channel_id++ ) {
        for ( uint8_t value_id = 0; value_id < VALUES; value_id++ ) {
            g_value[channel_id][value_id][0] = 0x00;
            g_value[channel_id][value_id][1] = 0x00;
        }
    }
}

void values_load(void)
{
    eeprom_read_block( g_value, ((void*)VIA_EEPROM_CUSTOM_CONFIG_ADDR), VIA_EEPROM_CUSTOM_CONFIG_SIZE );
}

void values_save(void)
{
    eeprom_update_block( g_value, ((void*)VIA_EEPROM_CUSTOM_CONFIG_ADDR), VIA_EEPROM_CUSTOM_CONFIG_SIZE );
}

// We do this to test if VIA is sending save commands per channel
// Not relevant for real situations
void values_save_on_channel(uint8_t channel_id)
{
    uint16_t offset = channel_id * VALUES * 2;
    eeprom_update_block( ((void*)g_value) + offset,
        ((void*)VIA_EEPROM_CUSTOM_CONFIG_ADDR) + offset,
        VALUES * 2 );
}

void via_init_kb(void)
{
    values_init();

    // If the EEPROM has the magic, the data is good.
    // OK to load from EEPROM
    if (via_eeprom_is_valid()) {
        values_load();
    } else	{
        values_save();
        // DO NOT set EEPROM valid here, let caller do this
    }
}

void set_value( uint8_t channel_id, uint8_t *data )
{
    // data = [ value_id, value_data ]
    uint8_t *value_id = &(data[0]);
    uint8_t *value_data = &(data[1]);
    if ( *value_id >= 0 && *value_id < VALUES ) {
        g_value[channel_id][*value_id][0] = value_data[0];
        g_value[channel_id][*value_id][1] = value_data[1];
    }
}

void get_value( uint8_t channel_id, uint8_t *data )
{
    // data = [ value_id, value_data ]
    uint8_t *value_id = &(data[0]);
    uint8_t *value_data = &(data[1]);
    if ( *value_id >= 0 && *value_id < VALUES ) {
        value_data[0] = g_value[channel_id][*value_id][0];
        value_data[1] = g_value[channel_id][*value_id][1];
    }
}

void via_custom_value_command(uint8_t *data, uint8_t length) {
    // data = [ command_id, channel_id, value_id, value_data ]
    uint8_t *command_id        = &(data[0]);
    uint8_t *channel_id        = &(data[1]);
    uint8_t *value_id_and_data = &(data[2]);

    if ( *channel_id >= 0 && *channel_id < CHANNELS ) {
        switch ( *command_id )
        {
            case id_custom_set_value:
            {
                set_value(*channel_id,value_id_and_data);
                break;
            }
            case id_custom_get_value:
            {
                get_value(*channel_id,value_id_and_data);
                break;
            }
            case id_custom_save:
            {
                //for ( uint8_t i=0; i<CHANNELS; i++) {
                    values_save_on_channel(*channel_id);
                //}
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
    else {
        *command_id = id_unhandled;
    }

    // DO NOT call raw_hid_send(data,length) here, let caller do this
}
#endif // VIA_ENABLE