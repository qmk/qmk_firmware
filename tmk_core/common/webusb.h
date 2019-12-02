#pragma once

#include <stdint.h>
#include <stdbool.h>

#ifndef FIRMWARE_VERSION
#define FIRMWARE_VERSION u8"default"
#endif
#define WEBUSB_STOP_BIT -2
#define WEBUSB_BLINK_STEPS 512
#define WEBUSB_BLINK_END WEBUSB_BLINK_STEPS * 60

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

enum Webusb_Command_Code {
    WEBUSB_CMD_PAIR,
    WEBUSB_GET_FW_VERSION
};

enum Webusb_Event_Code {
    WEBUSB_EVT_PAIRED,
    WEBUSB_EVT_KEYDOWN,
    WEBUSB_EVT_KEYUP,
    WEBUSB_EVT_LAYER,
    WEBUSB_EVT_LANDING_PAGE
};
