#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "action.h"

bool process_context_magic(uint16_t keycode, keyrecord_t *record);
