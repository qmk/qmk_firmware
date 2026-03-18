// Copyright 2025 ZSA Technology Labs, Inc <@zsa>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdint.h>
#include <stdbool.h>

#ifndef AUTOMOUSE_LAYER
#    error "AUTOMOUSE_LAYER must be defined when using the automouse module"
#endif

#ifndef AUTOMOUSE_TIMEOUT
#    define AUTOMOUSE_TIMEOUT 650
#endif

#ifndef AUTOMOUSE_THRESHOLD
#    define AUTOMOUSE_THRESHOLD 10
#endif

#ifndef AUTOMOUSE_SCROLL_THRESHOLD
#    define AUTOMOUSE_SCROLL_THRESHOLD AUTOMOUSE_THRESHOLD
#endif

#ifndef AUTOMOUSE_DEBOUNCE
#    define AUTOMOUSE_DEBOUNCE 25
#endif

#ifndef AUTOMOUSE_DELAY
#    define AUTOMOUSE_DELAY GET_TAPPING_TERM(QK_MOUSE_BUTTON_1, &(keyrecord_t){})
#endif

void automouse_enable(void);
void automouse_disable(void);
void automouse_toggle(void);
bool automouse_is_enabled(void);
bool automouse_is_active(void);
