// Copyright 2023 Hyojin Bak (@eerraa)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "tomak.h"
#include "quantum.h"
#include "eeprom.h"
#include "transactions.h"

tomak_config_t g_tomak_config;

#ifdef TOMAK_CONFIG_SYNC
void tomak_config_sync_handler(uint8_t initiator2target_buffer_size, const void* initiator2target_buffer, uint8_t target2initiator_buffer_size, void* target2initiator_buffer) {
    if (initiator2target_buffer_size == sizeof(g_tomak_config)) {
        memcpy(&g_tomak_config, initiator2target_buffer, sizeof(g_tomak_config));
    }
}

void keyboard_post_init_kb(void) {
    
    transaction_register_rpc(RPC_ID_KB_CONFIG_SYNC, tomak_config_sync_handler);
    keyboard_post_init_user();
}

void housekeeping_task_kb(void) {
    if (is_keyboard_master()) {
        // Keep track of the last state, so that we can tell if we need to propagate to slave.
        static tomak_config_t last_tomak_config = {0};
        static uint32_t           last_sync     = 0;
        bool                      needs_sync    = false;

        // Check if the state values are different.
        if (memcmp(&g_tomak_config, &last_tomak_config, sizeof(g_tomak_config))) {
            needs_sync = true;
            memcpy(&last_tomak_config, &g_tomak_config, sizeof(g_tomak_config));
        }
        // Send to slave every 500ms regardless of state change.
        if (timer_elapsed32(last_sync) > 500) {
            needs_sync = true;
        }

        // Perform the sync if requested.
        if (needs_sync) {
            if (transaction_rpc_send(RPC_ID_KB_CONFIG_SYNC, sizeof(g_tomak_config), &g_tomak_config)) {
                last_sync = timer_read32();
            }
        }
    }
    // No need to invoke the user-specific callback, as it's been called
    // already.
}
#endif

static void read_tomak_config_from_eeprom(tomak_config_t* config) {
    config->raw = eeconfig_read_kb() & 0xffffffff;
}

static void write_tomak_config_to_eeprom(tomak_config_t* config) {
    eeconfig_update_kb(config->raw);
}

uint8_t increment( uint8_t value, uint8_t step, uint8_t min, uint8_t max )
{
    int16_t new_value = value;
    new_value += step;
    return MIN( MAX( new_value, min ), max );
}

uint8_t decrement( uint8_t value, uint8_t step, uint8_t min, uint8_t max )
{
    int16_t new_value = value;
    new_value -= step;
    return MIN( MAX( new_value, min ), max );
}

void eeconfig_init_kb(void) {
    g_tomak_config.raw = 0;
    g_tomak_config.indicator_toggle = true;
    g_tomak_config.indicator_override = false;
    g_tomak_config.indicator_hsv.h = 0;
    g_tomak_config.indicator_hsv.s = 0;
    g_tomak_config.indicator_hsv.v = 255;
    write_tomak_config_to_eeprom(&g_tomak_config);
    eeconfig_init_user();
}

void matrix_init_kb(void) {
    read_tomak_config_from_eeprom(&g_tomak_config);
    matrix_init_user();
}

bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max)
{
    if (!rgb_matrix_indicators_advanced_user(led_min, led_max)) {
        return false;
    }
    if (g_tomak_config.indicator_toggle) {
        RGB rgb_caps = hsv_to_rgb( (HSV){ .h = g_tomak_config.indicator_hsv.h,
                                          .s = g_tomak_config.indicator_hsv.s,
                                          .v = g_tomak_config.indicator_hsv.v } );
        if (host_keyboard_led_state().caps_lock) {
            RGB_MATRIX_INDICATOR_SET_COLOR(96, rgb_caps.r, rgb_caps.g, rgb_caps.b);
            RGB_MATRIX_INDICATOR_SET_COLOR(97, rgb_caps.r, rgb_caps.g, rgb_caps.b);
            RGB_MATRIX_INDICATOR_SET_COLOR(98, rgb_caps.r, rgb_caps.g, rgb_caps.b);
        } else if (g_tomak_config.indicator_override) {
            RGB_MATRIX_INDICATOR_SET_COLOR(96, 0, 0, 0);
            RGB_MATRIX_INDICATOR_SET_COLOR(97, 0, 0, 0);
            RGB_MATRIX_INDICATOR_SET_COLOR(98, 0, 0, 0);
        }
    }

    return true;
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case IN_TOGG:
        {
            if (record->event.pressed) {
                g_tomak_config.indicator_toggle = g_tomak_config.indicator_toggle ? false : true;
                write_tomak_config_to_eeprom(&g_tomak_config);
            }
            return false;
        }
        case IN_OVER:
        {
            if (record->event.pressed) {
                g_tomak_config.indicator_override = g_tomak_config.indicator_override ? false : true;
                write_tomak_config_to_eeprom(&g_tomak_config);
            }
            return false;
        }
        case IN_BRI:
        {
            if (record->event.pressed) {
                g_tomak_config.indicator_hsv.v = increment( g_tomak_config.indicator_hsv.v, 8, 0, 255 );
                write_tomak_config_to_eeprom(&g_tomak_config);
            }
            return false;
        }
        case IN_BRD:
        {
            if (record->event.pressed) {
                g_tomak_config.indicator_hsv.v = decrement( g_tomak_config.indicator_hsv.v, 8, 0, 255 );
                write_tomak_config_to_eeprom(&g_tomak_config);
            }
            return false;
        }
        case IN_HUEI:
        {
            if (record->event.pressed) {
                g_tomak_config.indicator_hsv.h = increment( g_tomak_config.indicator_hsv.h, 8, 0, 255 );
                write_tomak_config_to_eeprom(&g_tomak_config);
            }
            return false;
        }
        case IN_HUED:
        {
            if (record->event.pressed) {
                g_tomak_config.indicator_hsv.h = decrement( g_tomak_config.indicator_hsv.h, 8, 0, 255 );
                write_tomak_config_to_eeprom(&g_tomak_config);
            }
            return false;
        }
        case IN_SATI:
        {
            if (record->event.pressed) {
                g_tomak_config.indicator_hsv.s = increment( g_tomak_config.indicator_hsv.s, 8, 0, 255 );
                write_tomak_config_to_eeprom(&g_tomak_config);
            }
            return false;
        }
        case IN_SATD:
        {
            if (record->event.pressed) {
                g_tomak_config.indicator_hsv.s = decrement( g_tomak_config.indicator_hsv.s, 8, 0, 255 );
                write_tomak_config_to_eeprom(&g_tomak_config);
            }
            return false;
        }
    }
    return process_record_user(keycode, record);
};