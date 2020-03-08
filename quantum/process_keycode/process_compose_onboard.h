#ifndef PROCESS_COMPOSE_ONBOARD_H
#define PROCESS_COMPOSE_ONBOARD_H

#include "quantum.h"

#ifndef COMPOSE_ONBOARD_ABORT
#define COMPOSE_ONBOARD_ABORT KC_SPC
#endif
#ifndef COMPOSE_ONBOARD_LEN
#define COMPOSE_ONBOARD_LEN 5
#endif

/// Compares the first `len` keycode (uint16_t) of the first two arguments
/// and returns the index at which they start to differ or `len` if they are equal.
size_t compose_onboard_memcmp_index(uint16_t* seq, uint16_t* input, size_t len);

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
    }
#define COMPOSE_ONBOARD_MAPPING(INPUT, ACTION) {\
    uint16_t input[] = INPUT; \
    uint16_t actions[] = ACTION; \
    _Static_assert(ARRAYLEN(input) <= COMPOSE_ONBOARD_LEN, "Number of keys in Compose Onboard input keystroke is too long. Consider increasing COMPOSE_ONBOARD_LEN"); \
    size_t test_len = min(ARRAYLEN(input), sequence_len); \
    size_t match_index = compose_onboard_memcmp_index(sequence, input, test_len); \
    if (match_index != 0) { \
        partial_match = true; \
    } \
    if (sequence_len == ARRAYLEN(input) && match_index == test_len) { \
        for (int i = 0; i < ARRAYLEN(actions); i++) { \
            register_code16(actions[i]); \
            unregister_code16(actions[i]); \
        } \
        return false; \
    } \
    return partial_match; \
}
#define COMPOSE_ONBOARD_INPUT(...) \
    {__VA_ARGS__}
#define COMPOSE_ONBOARD_ACTION(...) \
    {__VA_ARGS__}

#endif
