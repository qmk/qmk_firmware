#pragma once
#include "analogkeys.h"
#include "stdint.h"

typedef enum {
    SEND_KEYBOARD_DATA,
    RECIEVE_RGB_SETTINGS,
    RECIEVE_KEY_CONFIG,
    RECIEVE_KEY_REBIND,
    BOOTLOADER_JUMP,
    EEPROM_RESET,
    SEND_RGB_SETTINGS,
    SEND_KEY_CONFIG,
    SEND_KEY_REBIND,
    SWITCH_RGB_MODE,
    SEND_DEBUG_KEY_STATE
} report_id_t;

void raw_hid_send_rgb_settings(void);
void raw_hid_send_key_rebinds(void);
void raw_hid_send_key_config(uint8_t, uint16_t, key_config_t*);
void raw_hid_send_all_key_configs(void);
void raw_hid_send_debug_key_state(uint8_t row, uint8_t col, uint16_t raw, uint16_t value, bool state);

void raw_hid_receive(uint8_t *, uint8_t);
