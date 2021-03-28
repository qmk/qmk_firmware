#pragma once

#include "quantum.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    char key_string[17];
    uint16_t keycode;
} lookup_table_t;

char* translate_keycode_to_string(uint16_t code);

extern lookup_table_t lookup_table[366];

#ifdef __cplusplus
}
#endif
