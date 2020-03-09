#ifndef PROCESS_COMPOSE_ONBOARD_H
#define PROCESS_COMPOSE_ONBOARD_H

#include "quantum.h"

#ifndef COMPOSE_ONBOARD_ABORT
#define COMPOSE_ONBOARD_ABORT KC_COMPOSE_ONBOARD
#endif
#ifndef COMPOSE_ONBOARD_LEN
#define COMPOSE_ONBOARD_LEN 5
#endif

bool process_compose_onboard(uint16_t keycode, keyrecord_t* record);
bool compose_onboard_mapping(uint16_t* sequence, uint8_t len);
void compose_onboard_start(void);
void compose_onboard_end(void);

/// Compares the first `len` keycode (uint16_t) of the first two arguments
/// and returns the index at which they start to differ or `len` if they are equal.
size_t compose_onboard_memcmp_index(uint16_t* seq, uint16_t* input, size_t len);
/// Compares the compose mapping input to the sequence so far.
/// Returns -1 on a full match, 0 on no match, and 1 on a partial match.
/// This is done to reduce the binary size compared to inlining it everywhere
int compose_onboard_compare_input(uint16_t* input, uint8_t input_len, uint16_t* seq, uint8_t seq_len);

#define ARGLEN(...) (sizeof((uint16_t[]){__VA_ARGS__})/sizeof(uint16_t))
#define ARRAYLEN(arr) (sizeof(arr)/sizeof(arr[0]))
#define min(a,b) ({ \
    __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a < _b ? _a : _b; \
})

#define COMPOSE_ONBOARD_DICTIONARY(...) \
    bool compose_onboard_mapping(uint16_t* sequence, uint8_t sequence_len) { \
        bool partial_match = false; \
        __VA_ARGS__ \
    return partial_match; \
    }
#define COMPOSE_ONBOARD_MAPPING(INPUT, ACTION) {\
    uint16_t input[] = INPUT; \
    _Static_assert(ARRAYLEN(input) <= COMPOSE_ONBOARD_LEN, "Number of keys in Compose Onboard input keystroke is too long. Consider increasing COMPOSE_ONBOARD_LEN"); \
    uint8_t input_len = ARRAYLEN(input); \
    int res = compose_onboard_compare_input(input, input_len, sequence, sequence_len); \
    if (res == -1) { \
        ACTION \
        return false; \
    } \
    partial_match |= res; \
}
#define COMPOSE_ONBOARD_INPUT(...) \
    {__VA_ARGS__}
#define COMPOSE_ONBOARD_ACTION(...) \
    uint16_t actions[] = {__VA_ARGS__}; \
    for (int i = 0; i < ARRAYLEN(actions); i++) { \
        register_code16(actions[i]); \
        unregister_code16(actions[i]); \
    }
#endif
