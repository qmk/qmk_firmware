
#pragma once
#include "../__init__.h"

extern uint8_t key_buffer[MAX_CONTEXT_LENGTH];
extern uint8_t key_buffer_size;

typedef uint16_t (*magic_provider)(uint8_t);
typedef void (*trie_fallback)(void);

typedef struct trie_visitor trie_visitor_t;
typedef void (*trie_visitor_cb_t)(trie_visitor_t*, int, const char*);

typedef struct
{
    uint16_t       magic_key;
    int            data_size;
    const uint8_t  *data;
    trie_fallback  fallback;
    magic_provider next_magic_provider;
} trie_t;

typedef struct {
	char buffer[MAGIC_MAX_LENGTH];
	int size;
} stack_t;

struct trie_visitor {
	trie_visitor_cb_t cb_func;
	void	          *cb_data;
	stack_t	          stack;
};

typedef struct {
    char    *completion;
    uint8_t max_condext_len;
    uint8_t bspace_count;  
} search_result_t;

void search_trie(const uint8_t *trie, int offset, trie_visitor_t *v);
bool process_check(uint16_t*, keyrecord_t*, uint8_t*, uint8_t*);
void stack_dump(stack_t *stack, char *str);
void dequeue_keycodes(uint8_t);
void enqueue_keycode(uint8_t);
void dequeue_keycode(void);
void process_trie(trie_t*);
void clear_buffer(void);
void print_buffer(void);

#define TDATA(L) pgm_read_byte(&trie->data[L])
#define queue(i) get_buffer_element(i)
