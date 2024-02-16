
#include "../__init__.h"

bool is_magic_training_active = false;

void toggle_magic_training(void)  { is_magic_training_active = !is_magic_training_active; } 
void enable_magic_training(void)  { is_magic_training_active = true; } 
void disable_magic_training(void) { is_magic_training_active = false; } 
bool is_magic_training_on(void)   { return is_magic_training_active; } 

uint8_t temple_key_buffer[MAX_CONTEXT_LENGTH];
uint8_t temple_len;

void record_potential_match(trie_visitor_t *v, int bspaces, const char *completion) {
    potential_compl_result_t *result = (potential_compl_result_t*)(v->cb_data);

    uint8_t completion_len = strlen(completion);
    if (completion_len < result->max_completion_len) return;

    for (int i = 0; i < completion_len; i += 1)
        if (keycode_to_char(temple_key_buffer[temple_len - completion_len + i]) != completion[i])
            return;

    for (int i = 0; i < v->stack.size; i += 1)
        if (temple_key_buffer[temple_len - completion_len - i - 1] != char_to_keycode(v->stack.buffer[i]))
            return;

    result->max_completion = (char*)completion;
    result->max_completion_len = completion_len;
    stack_dump(&v->stack, result->context_string);
}

bool check_potential_match(trie_t* trie, potential_compl_result_t* result) {
    trie_visitor_t record_visitor = { record_potential_match, result };

    temple_len = key_buffer_size;
    key_buffer_size -= 1;

    for (; key_buffer_size; key_buffer_size -= 1) {
        record_visitor.stack.size = 0;
        search_trie(trie->data, 0, &record_visitor);
    }

    key_buffer_size = temple_len;
    return result->max_completion_len;
}

void check_potential_matches(potential_match_found_cb callback) {
    if (!is_magic_training_active) return;
    potential_compl_result_t result;

    for (int i = 0; tries[i].magic_key != KC_NO; i++) {
        for (int i = 0; i < key_buffer_size; i += 1)
            temple_key_buffer[i] = key_buffer[i];

        if (check_potential_match(&tries[i], &result)) {
            callback(tries[i].magic_key, result.context_string, result.max_completion);
            return;
        }
    }
}
