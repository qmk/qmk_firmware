
#pragma once

#include <stdint.h>
#include "bmp_extended_keycode.h"
#include "keycode_str_converter.h"

uint8_t str2bmp_ex_keycode_locale(bmp_ex_keycode_t* ek_res, const char* str, uint32_t len, KEYMAP_LOCALE locale);

uint8_t bmp_ex_keycode2str_locale(bmp_ex_keycode_t const* const ek, char* str, uint16_t len, KEYMAP_LOCALE locale, bool use_ascii);
