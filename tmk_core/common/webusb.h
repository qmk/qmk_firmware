#pragma once

#include <stdint.h>
#include <stdbool.h>

void webusb_receive(uint8_t *data, uint8_t length);
void webusb_send(uint8_t *data, uint8_t length);
void webusb_error(uint8_t);
void webusb_set_pairing_state(void);

typedef struct{
    bool paired;
    bool pairing;
} webusb_state_t;

extern webusb_state_t webusb_state;

enum Webusb_Status_Code {
    WEBUSB_STATUS_NOT_PAIRED = -1,
    WEBUSB_STATUS_OK,
    WEBUSB_STATUS_UNKNOWN_COMMAND,
};


