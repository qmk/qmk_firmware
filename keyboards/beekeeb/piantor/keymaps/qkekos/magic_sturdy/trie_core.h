
#pragma once
#include "../__init__.h"

extern uint8_t key_buffer[MAX_CONTEXT_LENGTH];
extern uint8_t key_buffer_size;

typedef uint16_t (*magic_provider)(uint8_t);
typedef void (*trie_fallback)(void);

typedef struct
{
    uint16_t       magic_key;
    int            data_size;
    const uint8_t  *data;
    trie_fallback  fallback;
    magic_provider next_magic_provider;
} trie_t;

typedef struct
{
    uint8_t depth;
    uint8_t num_backspaces;
    int     completion_offset;
} trie_search_result_t;

bool process_check(uint16_t*, keyrecord_t*, uint8_t*, uint8_t*);
void dequeue_keycodes(uint8_t);
void enqueue_keycode(uint8_t);
void dequeue_keycode(void);
void process_trie(trie_t);
void clear_buffer(void);

#define TDATA(L) pgm_read_byte(&trie->data[L])
#define queue(i) get_buffer_element(i)
