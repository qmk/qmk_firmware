/*
Copyright 2019 Sekigon

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "apidef.h"
#include "keycode_str_converter.h"
#include "bmp_extended_keycode_converter.h"
#include "bmp_custom_keycode.h"

#define LAYOUT_NAME_MAXLEN 32
typedef struct {
    uint16_t*     keymap;
    uint32_t      keymap_idx;
    uint32_t      keymap_len;
    KEYMAP_LOCALE locale;
    char          tail[16];

    bmp_ex_keycode_t* bmp_ek;
    uint16_t          ek_num;

    char layout_name[LAYOUT_NAME_MAXLEN];
} json_keymap_convert_inst_t;

typedef struct {
    const uint16_t* keymap;
    uint32_t        keymap_idx;
    uint32_t        keymap_len;
    KEYMAP_LOCALE   locale;
    uint8_t         use_ascii;

    bmp_ex_keycode_t* bmp_ek;

    const char* layout_name;
} keymap_json_convert_inst_t;

typedef struct {
    bmp_api_config_t* config;
    char              tail[16];
} json_config_convert_inst_t;

void    keymap_to_json_init(keymap_json_convert_inst_t* const inst, const uint16_t* keymap, uint32_t keymap_len);
void    keymap_to_json_conv(keymap_json_convert_inst_t* const inst, char* json, uint32_t len, uint32_t key_num);
void    keymap_to_json_conv_layout(keymap_json_convert_inst_t* const inst, char* json, uint32_t len, uint8_t const* const layout);
int32_t config_to_json_conv(bmp_api_config_t const* const config, char* str, uint32_t len);

int32_t is_json_closed(const char* json, uint32_t len);
void    json_to_keymap_init(json_keymap_convert_inst_t* const inst, uint16_t* keymap, uint32_t keymap_len);
int32_t json_to_keymap_conv(json_keymap_convert_inst_t* const inst, const char* json);
void    json_to_config_conv_inst_init(json_config_convert_inst_t* const inst, bmp_api_config_t* const config);

int32_t json_to_config_conv(json_config_convert_inst_t* const inst, const char* json);

int32_t get_config_from_stream(json_config_convert_inst_t* const inst, const char* str, const char last_char, uint32_t len, bool exit_flag);

int32_t get_keymap_from_stream(json_keymap_convert_inst_t* const inst, const char* str, const char last_char, uint32_t len, bool exit_flag);

uint32_t json_to_tapping_term_config_conv(const char* json, bmp_qmk_config_t* conf, KEYMAP_LOCALE locale);
void     tapping_term_config_to_json_conv(bmp_qmk_config_t const* const conf, char* json, uint32_t json_len, KEYMAP_LOCALE locale, bool use_ascii);
