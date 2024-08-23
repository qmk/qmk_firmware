#pragma once
#include "stdint.h"

typedef enum {
    SEND_KEYBOARD_DATA,
    RECIEVE_KEY_CONFIG,
    RECIEVE_KEY_REBIND,
    BOOTLOADER_JUMP,
    EEPROM_RESET,

} report_id_t;

void raw_hid_receive(uint8_t *, uint8_t);
