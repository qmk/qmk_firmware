
#pragma once
#include "../__init__.h"

bool lang_independant_pr(uint16_t, keyrecord_t*, bool*);
void tap_lang_independant_key(uint16_t);
void send_lang_independant_string(const char *str);
void lang_independant_init(void);
