/*
Copyright 2022 Roberto Lupi <Roberto.Lupi@gmail.com> @robertolupi

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "deferred_exec.h"

#include "robertolupi.h"

#define KEYMAP_FUNC(function, ...) KEYMAP_FUNC_(function##_keymap, __VA_ARGS__)
#define KEYMAP_FUNC_(function, ...) \
    __attribute__((weak)) bool function(__VA_ARGS__) { return true; }

// These functions can be overridden in keymaps (e.g. process_record_keymap)

KEYMAP_FUNC(process_record, uint16_t keycode, keyrecord_t* record)
KEYMAP_FUNC(dip_switch_update, uint8_t index, bool active)
KEYMAP_FUNC(matrix_scan, void)
KEYMAP_FUNC(music_mask, uint16_t keycode)

static uint32_t _temporary_mod_cb(uint32_t trigger_time, void* cb_arg) {
    struct temporary_mod_t* mod = cb_arg;
    unregister_code(mod->keycode);
    mod->token = INVALID_DEFERRED_TOKEN;
    return 0;
}

bool send_temporary_mod(struct temporary_mod_t* mod, uint32_t duration) {
    if (mod->token != INVALID_DEFERRED_TOKEN) {
        extend_deferred_exec(mod->token, duration);
        return true;
    }
    if ((get_mods() & MOD_BIT(mod->keycode)) != MOD_BIT(mod->keycode)) {
        register_code(mod->keycode);
        mod->token = defer_exec(duration, _temporary_mod_cb, mod);
        return true;
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    static struct temporary_mod_t tmCMD = {.keycode = KC_LCMD, .token = INVALID_DEFERRED_TOKEN};

    if (!process_record_keymap(keycode, record)) {
        return false;
    }
    switch (keycode) {
        case KC_MISSION_CONTROL:
            if (record->event.pressed) {
                host_consumer_send(0x29F);
            } else {
                host_consumer_send(0);
            }
            return false;
        case KC_LAUNCHPAD:
            if (record->event.pressed) {
                host_consumer_send(0x2A0);
            } else {
                host_consumer_send(0);
            }
            return false;
        case KC_NEXT_APP:
            if (record->event.pressed) {
                send_temporary_mod(&tmCMD, 1000);
                tap_code16(KC_TAB);
            }
            return false;
        case KC_PREVIOUS_APP:
            if (record->event.pressed) {
                send_temporary_mod(&tmCMD, 1000);
                tap_code16(S(KC_TAB));
            }
            return false;
    }
    return true;
}

bool dip_switch_update_user(uint8_t index, bool active) {
    return dip_switch_update_keymap(index, active);
}
void matrix_scan_user(void) {
    if (matrix_scan_keymap()) return;
}
bool music_mask_user(uint16_t keycode) {
    return music_mask_keymap(keycode);
}
