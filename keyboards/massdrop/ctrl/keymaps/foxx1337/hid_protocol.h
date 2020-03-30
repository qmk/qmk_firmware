#pragma once

#include <raw_hid.h>

enum ctrl_hid_codes {
    CTRL_HID_EOM = 0x00,
    CTRL_HID_HELLO,
    CTRL_HID_LIGHTS_TOGGLE
};

extern uint8_t raw_hid_buffer[RAW_EPSIZE];

void raw_hid_perform_send(void);
