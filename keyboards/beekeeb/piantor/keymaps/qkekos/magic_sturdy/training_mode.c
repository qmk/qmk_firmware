
#include "../__init__.h"

bool is_magic_training_active = false;
bool is_hard_training_active = false;

void toggle_magic_training(void)  { is_magic_training_active = !is_magic_training_active; } 
void enable_magic_training(void)  { is_magic_training_active = true; } 
void disable_magic_training(void) { is_magic_training_active = false; } 
bool is_magic_training_on(void)   { return is_magic_training_active; }

void toggle_hard_training(void)  { is_hard_training_active = !is_hard_training_active; } 
void enable_hard_training(void)  { is_hard_training_active = true; } 
void disable_hard_training(void) { is_hard_training_active = false; } 
bool is_hard_training_on(void)   { return is_hard_training_active; } 

uint8_t key_buffer_copy[MAX_CONTEXT_LENGTH];
uint8_t buffer_len_copy;

char tmp_buffer[MAX_CONTEXT_LENGTH];

void wipe_result(potential_compl_result_t *result) {
    result->max_completion = NULL;
    result->max_completion_len = 0;
    result->match_context_level = 0;
    result->context_string[0] = '\0';
}

void record_potential_match(trie_visitor_t *v, int bspaces, const char *completion) {
    potential_compl_result_t *result = (potential_compl_result_t*)(v->cb_data);
    uint8_t completion_len = strlen(completion);

    if (completion_len < result->max_completion_len) return;

//    stack_dump(&v->stack, tmp_buffer);
//    if (!is_string_ascii(tmp_buffer) || v->stack.size == 0) return;
//    if (!is_string_ascii((char*)completion)) return;

    if (
        completion_len == result->max_completion_len &&
        v->stack.size < strlen(result->context_string)
    ) return;

    if (
        v->stack.size > strlen(result->context_string) &&
        key_buffer_size >= result->match_context_level
    ) wipe_result(result);

    for (int i = 0; i < completion_len; i += 1) {
        int index = buffer_len_copy - completion_len + i;
        if (index < 0 || index > buffer_len_copy) return;

        if (keycode_to_char(key_buffer_copy[index]) != completion[i])
            return;
    }

    for (int i = 0; i < v->stack.size; i += 1) {
        int index = buffer_len_copy - completion_len - i - 1;
        if (index < 0 || index > buffer_len_copy) return;

        if (key_buffer_copy[index] != char_to_keycode(v->stack.buffer[i]))
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
    return result->max_completion_len > 0;
}

void check_potential_matches(potential_match_found_cb callback) {
    if (!is_magic_training_active) return;

    potential_compl_result_t best_result;
    potential_compl_result_t current_result;

    uint16_t magic_key;

    for (int i = 0; tries[i].magic_key != KC_NO; i++) {
        wipe_result(&current_result);

        for (int j = 0; j < key_buffer_size; j += 1)
            key_buffer_copy[j] = key_buffer[j];

        if (
            check_potential_match(&tries[i], &current_result) &&
            current_result.max_completion_len > best_result.max_completion_len
        ) {
            magic_key = tries[i].magic_key;
            best_result = current_result;
        }
    }

    if (magic_key && get_last_keycode() != magic_key) {
        callback(magic_key, best_result.context_string, best_result.max_completion);
    }
}
