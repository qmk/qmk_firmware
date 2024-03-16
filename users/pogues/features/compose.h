#pragma once

/* shamelessly copied from oberien https://github.com/qmk/qmk_firmware/pull/8359/files# */

#include "quantum.h"

#ifndef COMPOSE_LEN
#define COMPOSE_LEN 3
#endif

enum compose_return_state {
    COMPOSE_OK = 0,
    COMPOSE_PARTIAL,
    COMPOSE_CANCELLED,
    COMPOSE_ERROR,
};

bool process_compose(uint16_t keycode, keyrecord_t* record, uint16_t compose_keycode);
uint8_t compose_mapping(uint16_t* sequence, uint8_t len);
void compose_start(void);
void compose_end(uint8_t state);

/// Compares the first `len` keycode (uint16_t) of the first two arguments
/// and returns the index at which they start to differ or `len` if they are equal.
size_t compose_memcmp_index(uint16_t* seq, uint16_t* input, size_t len);
/// Compares the compose mapping input to the sequence so far.
/// Returns -1 on a full match, 0 on no match, and 1 on a partial match.
/// This is done to reduce the binary size compared to inlining it everywhere
int compose_compare_input(uint16_t* input, uint8_t input_len, uint16_t* seq, uint8_t seq_len);

#define ARGLEN(...) (sizeof((uint16_t[]){__VA_ARGS__})/sizeof(uint16_t))
#define ARRAYLEN(arr) (sizeof(arr)/sizeof(arr[0]))

#define COMPOSE_MAPPING(INPUT, ACTION) { \
    uint16_t input[] = INPUT; \
    _Static_assert(ARRAYLEN(input) <= COMPOSE_LEN, "Number of keys in Compose input keystroke is too long. Consider increasing COMPOSE_LEN"); \
    uint8_t input_len = ARRAYLEN(input); \
    int res = compose_compare_input(input, input_len, sequence, sequence_len); \
    if (res == -1) { \
        ACTION \
        return COMPOSE_OK; \
    } else if (res == 1) { \
        return COMPOSE_PARTIAL; \
    } \
}

#define COMPOSE_INPUT(...) \
    {__VA_ARGS__}

#define COMPOSE_ACTION(...) \
    uint16_t actions[] = {__VA_ARGS__}; \
    for (int i = 0; i < ARRAYLEN(actions); i++) { \
        register_code16(actions[i]); \
        unregister_code16(actions[i]); \
    }


// there is a common case of key+key to alt-k or ctl-k
#define COMPOSE_MAPPING_ALT(KEY1, KEY2, ACTION_KEY) \
    COMPOSE_MAPPING( \
        COMPOSE_INPUT(KEY1, KEY2), \
        { SEND_STRING(SS_LALT(ACTION_KEY)); } \
    )
#define COMPOSE_MAPPING_CTL(KEY1, KEY2, ACTION_KEY) \
    COMPOSE_MAPPING( \
        COMPOSE_INPUT(KEY1, KEY2), \
        { SEND_STRING(SS_LCTL(ACTION_KEY)); } \
    )
#define COMPOSE_MAPPING_CTL_SFT(KEY1, KEY2, ACTION_KEY) \
    COMPOSE_MAPPING( \
        COMPOSE_INPUT(KEY1, KEY2), \
        { SEND_STRING(SS_LCTL(SS_LSFT(ACTION_KEY))); } \
    )




