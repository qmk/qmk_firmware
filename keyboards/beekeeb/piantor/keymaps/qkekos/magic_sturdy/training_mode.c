
#include "../__init__.h"

bool is_magic_training_active = false;

void toggle_magic_training(void)  { is_magic_training_active = !is_magic_training_active; } 
void enable_magic_training(void)  { is_magic_training_active = true; } 
void disable_magic_training(void) { is_magic_training_active = false; } 
bool is_magic_training_on(void)   { return is_magic_training_active; } 

uint8_t key_buffer_copy[MAX_CONTEXT_LENGTH];
uint8_t buffer_len_copy;

void record_potential_match(trie_visitor_t *v, int bspaces, const char *completion) {
    potential_compl_result_t *result = (potential_compl_result_t*)(v->cb_data);

    uint8_t completion_len = strlen(completion);
    if (completion_len < result->max_completion_len) return;

    if (
        completion_len == result->max_completion_len &&
        v->stack.size < strlen(result->context_string)
    ) return;

    if (
        v->stack.size > strlen(result->context_string) &&
        key_buffer_size >= result->match_context_level
    ) {
        result->max_completion = NULL;
        result->max_completion_len = 0;
        result->match_context_level = 0;
        result->context_string[0] = '\0';
    }

    if (completion_len > buffer_len_copy) return;

    for (int i = 0; i < completion_len; i += 1) {
        int index = buffer_len_copy - completion_len + i;

        if (index < 0 || index > buffer_len_copy) {
            uprintf("ALARM!!!!!\n");
            return;
        }

        if (keycode_to_char(key_buffer_copy[index]) != completion[i])
            return;
    }

    if (completion_len + v->stack.size > buffer_len_copy) return;

    for (int i = 0; i < v->stack.size; i += 1) {
        int index = buffer_len_copy - completion_len - i - 1;

        if (index < 0 || index > buffer_len_copy) {
            uprintf("ALARM 2!!!!!\n");
            return;
        }

        if (key_buffer_copy[buffer_len_copy - completion_len - i - 1] != char_to_keycode(v->stack.buffer[i]))
            return;
    }

    result->max_completion = (char*)completion;
    result->max_completion_len = completion_len;
    result->match_context_level = key_buffer_size;
    stack_dump(&v->stack, result->context_string);
}

bool check_potential_match(trie_t* trie, potential_compl_result_t* result) {
    trie_visitor_t record_visitor = { record_potential_match, result };

    buffer_len_copy = key_buffer_size;
    key_buffer_size -= 1;

    for (; key_buffer_size; key_buffer_size -= 1) {
        record_visitor.stack.size = 0;
        search_trie(trie->data, 0, &record_visitor);
    }

    key_buffer_size = buffer_len_copy;

    if (result->max_completion_len) {
        uprintf("yep - %d\n", result->max_completion_len);
    }

    return result->max_completion_len;
}

void check_potential_matches(potential_match_found_cb callback) {
    if (!is_magic_training_active) return;
    potential_compl_result_t result;

    for (int i = 0; tries[i].magic_key != KC_NO; i++) {
        for (int i = 0; i < key_buffer_size; i += 1)
            key_buffer_copy[i] = key_buffer[i];

        if (check_potential_match(&tries[i], &result)) {
            callback(tries[i].magic_key, result.context_string, result.max_completion);
            return;
        }
    }
}
