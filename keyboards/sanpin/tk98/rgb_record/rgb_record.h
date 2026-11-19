// Copyright 2025 lucky(@lucky-zang)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "color.h"
#include "eeprom.h"
#include "quantum.h"

#define KJ_GET_H(value) ((uint8_t)(value >> 8))
#define KJ_GET_S(value) ((uint8_t)(value & 0xFF))

/* HSV Color bit[15:8] H  bit[7:0] S */
#define KJ_AZURE        0x8466
#define KJ_BLACK        0x0000
#define KJ_BLUE         0xAAFF
#define KJ_CHARTREUSE   0x40FF
#define KJ_CORAL        0x0BB0
#define KJ_GOLD         0x24FF
#define KJ_GOLDENROD    0x1EDA
#define KJ_GREEN        0x55FF
#define KJ_MAGENTA      0xD5FF
#define KJ_ORANGE       0x15FF
#define KJ_PINK         0xEA80
#define KJ_PURPLE       0xBFFF
#define KJ_RED          0x00FF
#define KJ_CYAN         0x6AFF
#define KJ_TEAL         0x80FF
#define KJ_TURQUOISE    0x7B5A
#define KJ_WHITE        0x0101
#define KJ_YELLOW       0x2BFF

#define LASET_MOD_NO    0xFF
#define RGB_HSV_MAX     7
#define ________        KJ_BLACK

#ifndef RGB_RECORD_KJ_LISTS
#    define RGB_RECORD_KJ_LISTS \
        {KJ_BLACK, KJ_RED, KJ_GREEN, KJ_BLUE, KJ_YELLOW, KJ_PURPLE, KJ_CYAN, KJ_WHITE}
#endif

void rgbrec_read_current_channel(uint8_t channel);
void rgbrec_switch_channel(uint8_t channel);
uint16_t rgbrec_get_kj_data(uint8_t channel, uint8_t row, uint8_t column);
void rgbrec_set_kj_data(uint8_t channel, uint8_t row, uint8_t column, uint16_t kj);
void rgbrec_set_close_all(uint8_t h, uint8_t s, uint8_t v);
void rgbrec_set_kj_buffer(uint16_t offset, uint16_t size, uint8_t *data);
void rgbrec_play(uint8_t led_min, uint8_t led_max);
bool rgbrec_end(uint8_t channel, bool save_choose);
void rgbrec_get_kj_buffer(uint16_t offset, uint16_t size, uint8_t *data);
bool rgbrec_start(uint8_t channel);
bool rgbrec_show(uint8_t channel);
void rgbrec_init(uint8_t channel);
bool rgbrec_is_started(void);
void eeconfig_init_user_datablock(void);
bool rgbrec_register_record(uint16_t keycode, keyrecord_t *record);
void record_rgbmatrix_increase(uint8_t *last_mode);
uint8_t record_color_hsv(bool status);
uint8_t record_color_read_s_data(void);
uint8_t record_color_s(bool status);