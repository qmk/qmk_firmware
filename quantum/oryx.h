#pragma once
/*
The Oryx Webhid protocol

Each HID packet is a series of bytes.  The first byte is the packet type is the command. The rest of the bytes are the params.

Before sending a packet, the host needs to be paired or should request a pairing code.

The pairing code is a sequence of key positions derived from Oryx's firmware version code stored in the FIRMWARE_VERSION define.

Once the host has paired, it can freely use the commands define in the Oryx_Command_Code enum for which the board will always respond with a Oryx_Event_Code or a Oryx_Error_Code.
*/

#include "quantum.h"
#include "raw_hid.h"

#ifndef RAW_ENABLE
#    error "Raw hid needs to be enabled, please enable it!"
#endif
#ifndef RAW_EPSIZE
#    define RAW_EPSIZE 32
#endif

#define ORYX_PROTOCOL_VERSION = 0x02
#define ORYX_STOP_BIT -2

enum Oryx_Command_Code {
    ORYX_CMD_GET_FW_VERSION,
    ORYX_CMD_PAIRING_INIT,
    ORYX_CMD_PAIRING_VALIDATE,
    ORYX_CMD_DISCONNECT,
    ORYX_SET_LAYER,
    ORYX_RGB_CONTROL,
    ORYX_SET_RGB_LED,
    ORYX_SET_STATUS_LED,
    ORYX_UPDATE_BRIGHTNESS,
    ORYX_GET_PROTOCOL_VERSION = 0xFE,
};

enum Oryx_Event_Code {
    ORYX_EVT_GET_FW_VERSION,
    ORYX_EVT_PAIRING_INPUT,
    ORYX_EVT_PAIRING_KEY_INPUT,
    ORYX_EVT_PAIRING_FAILED,
    ORYX_EVT_PAIRING_SUCCESS,
    ORYX_EVT_LAYER,
    ORYX_EVT_KEYDOWN,
    ORYX_EVT_KEYUP,
    ORYX_EVT_RGB_CONTROL,
    ORYX_EVT_GET_PROTOCOL_VERSION = 0XFE,
    ORYX_EVT_ERROR                = 0xFF,
};

enum Oryx_Error_Code {
    ORYX_ERR_PAIRING_INIT_FAILED,
    ORYX_ERR_PAIRING_INPUT_FAILED,
    ORYX_ERR_PAIRING_KEY_INPUT_FAILED,
    ORYX_ERR_PAIRING_FAILED,
    ORYX_ERR_RGB_MATRIX_NOT_ENABLED,
    ORYX_ERR_STATUS_LED_OUT_OF_RANGE,
    ORYX_ERR_UNKNOWN_COMMAND = 0xFF,
};

extern bool oryx_state_live_training_enabled;

typedef struct {
    bool paired;
    bool rgb_control;
} rawhid_state_t;

extern rawhid_state_t rawhid_state;

void oryx_error(uint8_t code);
void pairing_failed_event(void);
void pairing_succesful_event(void);

void oryx_layer_event(void);
bool process_record_oryx(uint16_t keycode, keyrecord_t* record);
void layer_state_set_oryx(layer_state_t state);

#if defined(RGB_MATRIX_ENABLE) && !defined(KEYBOARD_ergodox_ez_glow)
RGB webhid_leds[RGB_MATRIX_LED_COUNT];
#endif
