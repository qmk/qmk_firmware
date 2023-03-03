// Copyright 2023 Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "keymap_spanish.h"

enum userspace_keycodes {
    CKC_VOL = QK_USER,

    // First value that can be used on a keymap, keep last
    QK_KEYMAP
};

#define _______ KC_TRNS

#if defined(TAP_DANCE_ENABLE)
enum userspace_tapdances {
    _TD_NTIL,
    _TD_Z,
    _TD_GRV,
    _TD_SPC,
};
#    define TD_NTIL TD(_TD_NTIL)
#    define TD_Z    TD(_TD_Z)
#    define TD_GRV  TD(_TD_GRV)
#    define TD_SPC  TD(_TD_SPC)
#else
#    define TD_NTIL ES_NTIL
#    define TD_Z    KC_Z
#    define TD_GRV  ES_GRV
#    define TD_SPC  KC_SPC
#endif // TAP_DANCE_ENABLE

// helper macro to register/unregister a keycode on press/release
#define UN_REGISTER(kc)        \
    if (record->event.pressed) \
        register_code16(kc);   \
    else                       \
        unregister_code16(kc);

#if !defined(WEAK)
#    define WEAK __attribute__((weak))
#endif
