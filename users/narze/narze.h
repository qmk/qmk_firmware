#pragma once

#include "quantum.h"

#ifdef COMBO_ENABLE
#   include "superduper.h"
#endif

void perform_mod_tap_with_mod(keyrecord_t *record, uint8_t holdMod, uint8_t tapMod, uint8_t keycode);
