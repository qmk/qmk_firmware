#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "action.h"

typedef struct
{
    uint16_t magic_key;
    uint8_t  data_size;
    const uint8_t *data;
} trie_t;

typedef struct
{
    uint8_t depth;
    uint8_t num_backspaces;
    int     completion_offset;
} trie_search_result_t;

bool process_context_magic(uint16_t keycode, keyrecord_t *record);
void proces_magic_key(uint16_t keycode);
void enqueue_keycode(uint8_t keycode);
void dequeue_keycodes(uint8_t num);
trie_t get_trie(uint16_t keycode);
void process_trie(trie_t trie);
void dequeue_keycode(void);

#define TDATA(L) pgm_read_byte(&trie->data[L])
