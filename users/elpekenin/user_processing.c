// Copyright 2023 Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "elpekenin.h"

WEAK bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_keymap(keycode, record)) {
        return false;
    }

    // keyboard stats, more info at: <https://discord.com/channels/440868230475677696/648964704428883978/1042930029505548429>
#ifdef CONSOLE_ENABLE
    uprintf("0x%04X\t%u\t%u\t0x%X\t%u\t0x%02X\t0x%02X\t%u\n",
        keycode,
        record->event.key.row,
        record->event.key.col,
        layer_state|default_layer_state,
        record->event.pressed,
        get_mods(),
        get_oneshot_mods(),
        record->tap.count
    );
#endif

    uint8_t mods = get_mods();
    bool l_shift = mods & MOD_BIT(KC_LSFT);
    bool l_alt   = mods & MOD_BIT(KC_LALT);

    // helper variable for custom keycodes that get mapped
    // to different keycodes based on some condition
    uint16_t target_kc;

    switch (keycode) {
        // Remap ALT+KC4 to ALT+F4
        case KC_4:
            if (l_alt) {
                UN_REGISTER(KC_F4)
                return false;
            }
            break;

        case CKC_VOL:
            target_kc = l_shift ? KC_VOLD : KC_VOLU;
            UN_REGISTER(target_kc)
            return false;

        default:
            break;
    }

    return true;
}
