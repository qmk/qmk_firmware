// Copyright 2026 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "steno.h"
#include "eeconfig.h"
#include "util.h"

#ifndef STENO_DEFAULT_MODE
#    if defined(STENO_ENABLE_GEMINI)
#        define STENO_DEFAULT_MODE STENO_MODE_GEMINI
#    elif defined(STENO_ENABLE_BOLT)
#        define STENO_DEFAULT_MODE STENO_MODE_BOLT
#    endif
#endif

static steno_mode_t mode = STENO_DEFAULT_MODE;

uint8_t chord[MAX_STROKE_SIZE] = {0};

void steno_clear_chord(void) {
    memset(chord, 0, sizeof(chord));
}

steno_mode_t steno_get_mode(void) {
    return mode;
}

#if NUM_STENO_PROTOCOLS > 1

static const steno_mode_t mode_candidates[] = {
#    if defined(STENO_ENABLE_GEMINI)
    STENO_MODE_GEMINI,
#    endif
#    if defined(STENO_ENABLE_BOLT)
    STENO_MODE_BOLT,
#    endif
};

#    define MODE_CANDIDATES_COUNT ARRAY_SIZE(mode_candidates)

static inline bool is_valid_mode(steno_mode_t mode) {
    for (uint8_t i = 0; i < MODE_CANDIDATES_COUNT; i++) {
        if (mode == mode_candidates[i]) {
            return true;
        }
    }
    return false;
}

void steno_set_mode_noeeprom(steno_mode_t new_mode) {
    if (!is_valid_mode(new_mode)) {
        return;
    }

    steno_clear_chord();

    mode = new_mode;
}

void steno_set_mode(steno_mode_t new_mode) {
    steno_set_mode_noeeprom(new_mode);

    eeconfig_update_steno_mode(mode);
}

void steno_mode_next_noeeprom(void) {
    uint8_t next = 0;
    for (uint8_t i = 0; i < MODE_CANDIDATES_COUNT; i++) {
        if (mode_candidates[i] == mode) {
            next = (i == MODE_CANDIDATES_COUNT - 1) ? 0 : (i + 1);
            break;
        }
    }

    steno_set_mode_noeeprom(mode_candidates[next]);
}

void steno_mode_next(void) {
    steno_mode_next_noeeprom();

    eeconfig_update_steno_mode(mode);
}

void steno_mode_previous_noeeprom(void) {
    uint8_t next = 0;
    for (uint8_t i = 0; i < MODE_CANDIDATES_COUNT; i++) {
        if (mode_candidates[i] == mode) {
            next = (i == 0) ? (MODE_CANDIDATES_COUNT - 1) : (i - 1);
            break;
        }
    }

    steno_set_mode_noeeprom(mode_candidates[next]);
}

void steno_mode_previous(void) {
    steno_mode_previous_noeeprom();

    eeconfig_update_steno_mode(mode);
}

#endif

void eeconfig_update_steno_default(void) {
    eeconfig_update_steno_mode(STENO_DEFAULT_MODE);
}

void steno_init(void) {
#if NUM_STENO_PROTOCOLS > 1
    steno_mode_t loaded = eeconfig_read_steno_mode();
    if (is_valid_mode(loaded)) {
        mode = loaded;
    }
#endif
}
