#pragma once

#include "magic_data.h"
#define MAGIC_KEY_TIMEOUT 1500

extern uint8_t key_buffer[MAX_CONTEXT_LENGTH];
extern uint8_t key_buffer_size;

extern int prev_key_timestamp;
extern int current_key_timestamp;

typedef void (*trie_fallback)(uint8_t);

typedef struct
{
    uint16_t      magic_key;
    uint8_t       data_size;
    const uint8_t *data;
    trie_fallback fallback;
} trie_t;

typedef struct
{
    uint8_t depth;
    uint8_t num_backspaces;
    int     completion_offset;
} trie_search_result_t;

bool process_check(uint16_t*, keyrecord_t*, uint8_t*, uint8_t*);
bool process_context_magic(uint16_t, keyrecord_t*);
uint16_t get_buffer_element(int index);
void process_magic_key(uint16_t);
void dequeue_keycodes(uint8_t);
void record_send_string(char*);
void enqueue_keycode(uint8_t);
void dequeue_keycode(void);
trie_t get_trie(uint16_t);
void process_trie(trie_t);
void clear_buffer(void);

void repeat_key_fallback(uint8_t tap_count);
void magic_key_fallback(uint8_t tap_count);

#define TDATA(L) pgm_read_byte(&trie->data[L])
#define queue(i) get_buffer_element(i)
