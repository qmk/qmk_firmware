
#pragma once
#include "../__init__.h"

#define MAGIC_KEY_TIMEOUT 1500

extern uint8_t magic_tap_count;

extern int prev_key_timestamp;
extern int current_key_timestamp;

bool process_context_magic(uint16_t, keyrecord_t*);
uint16_t get_buffer_element(int index);
void process_magic_key(uint16_t);
trie_t get_trie(uint16_t);

uint16_t db_arep_provider(uint8_t);
void repeat_key_fallback(void);
void magic_key_fallback(void);
