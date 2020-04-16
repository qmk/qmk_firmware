#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef enum
{
  LOCALE_US,
  LOCALE_JP,
} KEYMAP_LOCALE;

typedef struct {
  uint16_t start_kc;
  uint16_t end_kc;
  const char* key_strings;
} key_string_map_t;

uint8_t quantum_keycode2str(uint16_t qk, char* str, uint32_t len);
uint8_t quantum_keycode2str_locale(uint16_t qk, char* str, uint32_t len,
  KEYMAP_LOCALE locale, bool use_ascii);
uint16_t get_kc_strlen(const char* str, uint16_t len);
uint16_t get_inner_element(const char** pp_str, uint16_t len);
uint16_t get_element_array(const char* str, uint16_t len,
    const char **pp_element, uint16_t* element_len, uint16_t buf_len);
uint16_t str2quantum_keycode(const char* str, uint32_t len);
uint16_t str2quantum_keycode_locale(const char* str, uint32_t len,
    KEYMAP_LOCALE locale);

uint8_t str2locale(const char *str);
void locale2str(KEYMAP_LOCALE locale, char *str, uint32_t len);
