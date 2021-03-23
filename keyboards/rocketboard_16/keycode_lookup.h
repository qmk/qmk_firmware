#pragma once

#include "quantum.h"

#ifdef __cplusplus
extern "C" {
#endif

char* translate_keycode_to_string(uint8_t code);

extern char keycode_to_string_array [] [24];

#ifdef __cplusplus
}
#endif
