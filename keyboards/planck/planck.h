#pragma once

#include "quantum.h"

#define encoder_update(clockwise) encoder_update_user(uint8_t index, clockwise)

#if defined(KEYBOARD_planck_ez)
#    include "ez.h"
#endif  // Planck revisions
