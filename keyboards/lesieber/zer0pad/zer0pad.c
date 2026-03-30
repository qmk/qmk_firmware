// Copyright 2024 Leon Sieber (@lesieber)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "raw_hid.h"
#include <string.h>

// Layer names stored in EEPROM (16 chars each)
static char layer_names[4][16] = {
    "Base",
    "Numbers", 
    "Functions",
    "Media"
};

// HID command IDs
#define CMD_GET_LAYER       0x01
#define CMD_LAYER_CHANGED   0x02
#define CMD_GET_LAYER_NAME  0x03
#define CMD_SET_LAYER_NAME  0x04
#define CMD_GET_ALL_NAMES   0x05

// Current layer tracking
static uint8_t current_layer = 0;

void eeconfig_init_user(void) {
    // Initialize default layer names in EEPROM
    const char* defaults[] = {"Base", "Numbers", "Functions", "Media"};
    for (int i = 0; i < 4; i++) {
        strncpy(layer_names[i], defaults[i], 15);
        layer_names[i][15] = '\0';
    }
    eeconfig_update_user_datablock(layer_names);
}

void keyboard_post_init_user(void) {
    // Load layer names from EEPROM
    eeconfig_read_user_datablock(layer_names);
}

// Send layer change notification to companion app
void notify_layer_change(uint8_t layer) {
    uint8_t data[32] = {0};
    data[0] = CMD_LAYER_CHANGED;
    data[1] = layer;
    // Include layer name in notification
    strncpy((char*)&data[2], layer_names[layer], 15);
    raw_hid_send(data, 32);
}

// Called when layer state changes
layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t new_layer = get_highest_layer(state);
    if (new_layer != current_layer) {
        current_layer = new_layer;
        notify_layer_change(current_layer);
    }
    return state;
}

// Handle raw HID commands from companion app / web configurator
void raw_hid_receive(uint8_t *data, uint8_t length) {
    uint8_t response[32] = {0};
    
    switch (data[0]) {
        case CMD_GET_LAYER:
            // Return current layer
            response[0] = CMD_GET_LAYER;
            response[1] = current_layer;
            strncpy((char*)&response[2], layer_names[current_layer], 15);
            raw_hid_send(response, 32);
            break;
            
        case CMD_GET_LAYER_NAME:
            // Return name for requested layer
            response[0] = CMD_GET_LAYER_NAME;
            response[1] = data[1]; // layer index
            if (data[1] < 4) {
                strncpy((char*)&response[2], layer_names[data[1]], 15);
            }
            raw_hid_send(response, 32);
            break;
            
        case CMD_SET_LAYER_NAME:
            // Set name for layer
            if (data[1] < 4) {
                strncpy(layer_names[data[1]], (char*)&data[2], 15);
                layer_names[data[1]][15] = '\0';
                eeconfig_update_user_datablock(layer_names);
            }
            response[0] = CMD_SET_LAYER_NAME;
            response[1] = 0x01; // success
            raw_hid_send(response, 32);
            break;
            
        case CMD_GET_ALL_NAMES:
            // Return all layer names (multiple packets)
            for (int i = 0; i < 4; i++) {
                response[0] = CMD_GET_ALL_NAMES;
                response[1] = i;
                response[2] = (i == 3) ? 1 : 0; // last packet flag
                strncpy((char*)&response[3], layer_names[i], 15);
                raw_hid_send(response, 32);
            }
            break;
    }
}
