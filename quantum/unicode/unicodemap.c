// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "unicodemap.h"
#include "unicode.h"
#include "keycodes.h"
#include "quantum_keycodes.h"
#include "modifiers.h"
#include "host.h"
#include "action_util.h"

uint8_t unicodemap_index(uint16_t keycode) {
    if (keycode >= QK_UNICODEMAP_PAIR) {
        // Keycode is a pair: extract index based on Shift / Caps Lock state
        uint16_t index;

        uint8_t mods = get_mods() | get_weak_mods();
#ifndef NO_ACTION_ONESHOT
        mods |= get_oneshot_mods();
#endif

        bool shift = mods & MOD_MASK_SHIFT;
        bool caps  = host_keyboard_led_state().caps_lock;
        if (shift ^ caps) {
            index = QK_UNICODEMAP_PAIR_GET_SHIFTED_INDEX(keycode);
        } else {
            index = QK_UNICODEMAP_PAIR_GET_UNSHIFTED_INDEX(keycode);
        }

        return index;
    } else {
        // Keycode is a regular index
        return QK_UNICODEMAP_GET_INDEX(keycode);
    }
}

uint32_t unicodemap_get_code_point(uint8_t index) {
    return pgm_read_dword(unicode_map + index);
}

void register_unicodemap(uint8_t index) {
    register_unicode(unicodemap_get_code_point(index));
}
