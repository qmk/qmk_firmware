
#pragma once
#include "../__init__.h"

enum pr_response lang_independant_pr(uint16_t, keyrecord_t*);
void tap_lang_independant_key(uint16_t);
void send_lang_independant_string(const char *str);
void lang_independant_init(void);
