#ifndef _API_H_
#define _API_H_

#include "lufa.h"

enum MESSAGE_TYPE {
    MT_GET_DATA =      0x10, // Get data from keyboard
    MT_GET_DATA_ACK =  0x11, // returned data to process (ACK)
    MT_SET_DATA =      0x20, // Set data on keyboard
    MT_SET_DATA_ACK =  0x21, // returned data to confirm (ACK)
    MT_SEND_DATA =     0x30, // Sending data/action from keyboard
    MT_SEND_DATA_ACK = 0x31, // returned data/action confirmation (ACK)
    MT_EXE_ACTION =    0x40, // executing actions on keyboard
    MT_EXE_ACTION_ACK =0x41, // return confirmation/value (ACK)
    MT_TYPE_ERROR =    0x80 // type not recofgnised (ACK)
};

enum DATA_TYPE {
    DT_NONE = 0x00,
    DT_HANDSHAKE,
    DT_DEFAULT_LAYER,
    DT_CURRENT_LAYER,
    DT_KEYMAP_OPTIONS,
    DT_BACKLIGHT,
    DT_RGBLIGHT,
    DT_UNICODE,
    DT_DEBUG,
    DT_AUDIO,
    DT_QUANTUM_ACTION,
    DT_KEYBOARD_ACTION,
    DT_USER_ACTION,
    DT_KEYMAP_SIZE,
    DT_KEYMAP
};

void dword_to_bytes(uint32_t dword, uint8_t * bytes);
uint32_t bytes_to_dword(uint8_t * bytes, uint8_t index);

#define MT_GET_DATA(data_type, data, length) SEND_BYTES(MT_GET_DATA, data_type, data, length)
#define MT_GET_DATA_ACK(data_type, data, length) SEND_BYTES(MT_GET_DATA_ACK, data_type, data, length)
#define MT_SET_DATA(data_type, data, length) SEND_BYTES(MT_SET_DATA, data_type, data, length)
#define MT_SET_DATA_ACK(data_type, data, length) SEND_BYTES(MT_SET_DATA_ACK, data_type, data, length)
#define MT_SEND_DATA(data_type, data, length) SEND_BYTES(MT_SEND_DATA, data_type, data, length)
#define MT_SEND_DATA_ACK(data_type, data, length) SEND_BYTES(MT_SEND_DATA_ACK, data_type, data, length)
#define MT_EXE_ACTION(data_type, data, length) SEND_BYTES(MT_EXE_ACTION, data_type, data, length)
#define MT_EXE_ACTION_ACK(data_type, data, length) SEND_BYTES(MT_EXE_ACTION_ACK, data_type, data, length)

void process_api(uint16_t length, uint8_t * data);

__attribute__ ((weak))
bool process_api_quantum(uint8_t length, uint8_t * data);

__attribute__ ((weak))
bool process_api_keyboard(uint8_t length, uint8_t * data);

__attribute__ ((weak))
bool process_api_user(uint8_t length, uint8_t * data);

#endif