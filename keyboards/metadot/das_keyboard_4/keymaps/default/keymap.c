// Copyright 2026 Giuseppe Iannello
// SPDX-License-Identifier: GPL-2.0-or-later

const uint16_t PROGMEM bootloader[] = {KC_ESC, KC_1, KC_A, COMBO_END};
combo_t key_combos[] = {
    COMBO(bootloader, QK_BOOT),
};
