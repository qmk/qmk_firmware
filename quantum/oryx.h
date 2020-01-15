#pragma once

#include "quantum.h"
#include "webusb.h"

#ifndef WEBUSB_ENABLE
#    error "WebUSB needs to be enabled, please enable it!"
#endif

#ifndef DYNAMIC_KEYMAP_ENABLE
#    error "Dynamic Keymaps are not enabled. It must be aenbled "
#endif


enum Oryx_Command_Code {
    ORYX_GET_LAYER = WEBUSB_CMD_SAFE_RANGE,

};

enum Oryx_Event_Code {
    ORYX_EVT_KEYDOWN = WEBUSB_EVT_SAFE_RANGE,
    ORYX_EVT_KEYUP,
    ORYX_EVT_LAYER,
};



extern bool webusb_state_live_training_enabled;

bool webusb_receive_oryx(uint8_t *data, uint8_t length);
void oryx_layer_event(void);


void keyboard_pre_init_oryx(void);
