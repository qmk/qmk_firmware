
#include "../__init__.h"

void record_potential_match(trie_visitor_t *v, int bspaces, const char *completion) {
    potential_compl_result_t *result = (potential_compl_result_t*)(v->cb_data);

    uint8_t completion_len = strlen(completion);
    if (completion_len < result->max_completion_len) return;

    char whatever[50];
    stack_dump(&v->stack, whatever);

    print_buffer();
    uprintf("%s -> %s\n", whatever, completion);
    uprintf("------------------\n");

    for (int i = 0; i < completion_len; i += 1) {
        char buffer_char = keycode_to_char(key_buffer[key_buffer_size - completion_len + i]);
        char c_char = completion[i];

        uprintf("%c == %c, %d\n", buffer_char, c_char, key_buffer_size);

        if (buffer_char != c_char)
            return;
    }

    uprintf("hello world 2\n");

    for (int i = 0; i < v->stack.size; i += 1)
        if (key_buffer[key_buffer_size - completion_len - i - 1] != char_to_keycode(v->stack.buffer[i]))
            return;

    result->max_completion = (char*)completion;
    result->max_completion_len = completion_len;
    stack_dump(&v->stack, result->context_string);
}

bool check_potential_match(trie_t trie, potential_compl_result_t* result) {
    trie_visitor_t record_visitor = { record_potential_match, &result };
    uint8_t original_buffer_size = key_buffer_size;

    for (; key_buffer_size; key_buffer_size -= 1) {
        record_visitor.stack.size = 0;
        search_trie(trie.data, 0, &record_visitor);
    }

    key_buffer_size = original_buffer_size;
    return result->max_completion_len;
}

void check_potential_matches(potential_match_found_cb callback) {
    for (int i = 0; tries[i].magic_key != KC_NO; i++) {
        potential_compl_result_t result;

        if (check_potential_match(tries[i], &result))
            callback(tries[i].magic_key, result.context_string, result.max_completion);

        break;
    }
}
