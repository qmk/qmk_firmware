#include QMK_KEYBOARD_H
#include "hid_protocol.h"

uint8_t raw_hid_buffer[RAW_EPSIZE];

void raw_hid_perform_send(void) {
    raw_hid_send(raw_hid_buffer, RAW_EPSIZE);
}
