// Copyright 2022 Kyle McCreery (@kylemccreery)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "bbs.h"

#ifdef DIP_SWITCH_ENABLE
bool dip_switch_update_kb(uint8_t index, bool active) { 
    if (!dip_switch_update_user(index, active)) { return false; }
    switch (index) {
        case 0:
            if(active) { tap_code(KC_CLCK); }
            break;
        break;
    }
    return true;
}
#endif

void eeconfig_init_kb() {
    steno_set_mode(STENO_MODE_GEMINI); // or STENO_MODE_BOLT
}