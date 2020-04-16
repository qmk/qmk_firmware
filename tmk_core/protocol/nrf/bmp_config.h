
#pragma once

#include "bmp_encoder.h"
#include "bmp_process_extended_keycode.h"
#include "keycode_str_converter.h"
#include "config_file_util.h"
#include "apidef.h"

uint32_t                    keymaps_len();
const bmp_encoder_config_t* get_bmp_encoder_config();
const char*                 get_keymap_string();
const char*                 get_config_string();
const char*                 get_encoder_string();

bmp_error_t webnus_write_callback(const uint8_t* dat, uint32_t len);

void update_config_files();

int load_eeprom_emulation_file();
int save_eeprom_emulation_file();

int load_tapping_term_file();
int save_tapping_term_file();

int load_ex_keycode_file();
int save_ex_keycode_file();

int load_encoder_config_file();

typedef enum {
    PARSER_CONFIG = 0,
    PARSER_KEYMAP,
    PARSER_QMK,
    PARSER_ENCODER,
    PARSER_NONE,
} parser_type_t;

typedef struct
{
  const char* key;
  char* string_dst;
  uint32_t dst_len;
  int (*parse)(void);
  void (*save)(void);
} file_string_parser_setting_t;

typedef struct
{
    const file_string_parser_setting_t * setting;
    uint16_t write_idx;
} file_string_parser_t;

void set_parser(parser_type_t parser_type);
file_string_parser_t * get_parser();

int stream_write_callback(const uint8_t* dat, uint32_t len);
bmp_error_t msc_write_callback(const uint8_t* dat, uint32_t len);
