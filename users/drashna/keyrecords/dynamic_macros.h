// Copyright 2016 Jack Humbert
// Copyright 2019 Wojciech Siewierski < wojciech dot siewierski at onet dot pl >
// Copyright 2023 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "action.h"
#include "action_layer.h"

#ifndef DYNAMIC_MACRO_COUNT
#    define DYNAMIC_MACRO_COUNT 8
#endif

#ifndef DYNAMIC_MACRO_SIZE
#    define DYNAMIC_MACRO_SIZE 64
#endif

enum dynamic_macro_recording_state {
    STATE_NOT_RECORDING,
    STATE_RECORD_KEY_PRESSED,
    STATE_CURRENTLY_RECORDING,
};

typedef struct {
    keyrecord_t events[DYNAMIC_MACRO_SIZE];
    uint8_t     length;
    uint16_t    checksum;
} dynamic_macro_t;

void dynamic_macro_init(void);
bool dynamic_macro_record_start(uint8_t macro_id);
void dynamic_macro_play(uint8_t macro_id);
void dynamic_macro_record_key(uint8_t macro_id, keyrecord_t* record);
void dynamic_macro_record_end(uint8_t macro_id);
bool process_record_dynamic_macro(uint16_t keycode, keyrecord_t* record);

void dynamic_macro_record_start_user(void);
void dynamic_macro_play_user(uint8_t macro_id);
void dynamic_macro_record_key_user(uint8_t macro_id, keyrecord_t* record);
void dynamic_macro_record_end_user(uint8_t macro_id);

#define DYNAMIC_MACRO_CRC_LENGTH (sizeof(dynamic_macro_t) - sizeof(uint16_t))
#define IS_DYN_KEYCODE(keycode) (keycode >= DYN_MACRO_KEY00 && keycode <= DYN_MACRO_KEY15)

uint16_t dynamic_macro_calc_crc(dynamic_macro_t* macro);
void     dynamic_macro_load_eeprom_all(void);
void     dynamic_macro_load_eeprom(uint8_t macro_id);
void     dynamic_macro_save_eeprom(uint8_t macro_id);
bool     dynamic_macro_header_correct(void);
