// Copyright 2025 Enoch Chau <enoch965@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef CONFIG_H
#define CONFIG_H

/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)

#endif
