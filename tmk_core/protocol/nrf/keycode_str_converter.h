#pragma once

#include <stdint.h>

typedef enum
{
  LOCALE_US,
  LOCALE_JP,
} KEYMAP_LOCALE;

uint8_t quantum_keycode2str(uint16_t qk, char* str, uint8_t len);
uint8_t quantum_keycode2str_locale(uint16_t qk, char* str, uint8_t len,
  KEYMAP_LOCALE locale, bool use_ascii);
uint16_t str2quantum_keycode(const char* str, uint32_t len);
uint16_t str2quantum_keycode_locale(const char* str, uint32_t len,
    KEYMAP_LOCALE locale);

uint8_t str2locale(const char *str);
void locale2str(KEYMAP_LOCALE locale, char *str, uint32_t len);
