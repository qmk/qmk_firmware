// Copyright 2022 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "secure.h"
#include "timer.h"
#include "util.h"

#ifndef SECURE_UNLOCK_TIMEOUT
#    define SECURE_UNLOCK_TIMEOUT 5000
#endif

#ifndef SECURE_IDLE_TIMEOUT
#    define SECURE_IDLE_TIMEOUT 60000
#endif

#ifndef SECURE_UNLOCK_SEQUENCE
#    define SECURE_UNLOCK_SEQUENCE {{0, 0}}
#endif

static secure_status_t secure_status = SECURE_LOCKED;
static uint32_t        unlock_time   = 0;
static uint32_t        idle_time     = 0;

static void secure_hook(secure_status_t secure_status) {
    secure_hook_quantum(secure_status);
    secure_hook_kb(secure_status);
}

secure_status_t secure_get_status(void) {
    return secure_status;
}

void secure_lock(void) {
    secure_status = SECURE_LOCKED;
    secure_hook(secure_status);
}

void secure_unlock(void) {
    secure_status = SECURE_UNLOCKED;
    idle_time     = timer_read32();
    secure_hook(secure_status);
}

void secure_request_unlock(void) {
    if (secure_status == SECURE_LOCKED) {
        secure_status = SECURE_PENDING;
        unlock_time   = timer_read32();
    }
    secure_hook(secure_status);
}

void secure_activity_event(void) {
    if (secure_status == SECURE_UNLOCKED) {
        idle_time = timer_read32();
    }
}

void secure_keypress_event(uint8_t row, uint8_t col) {
    static const uint8_t sequence[][2] = SECURE_UNLOCK_SEQUENCE;
    static const uint8_t sequence_len  = ARRAY_SIZE(sequence);

    static uint8_t offset = 0;
    if ((sequence[offset][0] == row) && (sequence[offset][1] == col)) {
        offset++;
        if (offset == sequence_len) {
            offset = 0;
            secure_unlock();
        }
    } else {
        offset = 0;
        secure_lock();
    }
}

void secure_task(void) {
#if SECURE_UNLOCK_TIMEOUT != 0
    // handle unlock timeout
    if (secure_status == SECURE_PENDING) {
        if (timer_elapsed32(unlock_time) >= SECURE_UNLOCK_TIMEOUT) {
            secure_lock();
        }
    }
#endif

#if SECURE_IDLE_TIMEOUT != 0
    // handle idle timeout
    if (secure_status == SECURE_UNLOCKED) {
        if (timer_elapsed32(idle_time) >= SECURE_IDLE_TIMEOUT) {
            secure_lock();
        }
    }
#endif
}

__attribute__((weak)) bool secure_hook_user(secure_status_t secure_status) {
    return true;
}
__attribute__((weak)) bool secure_hook_kb(secure_status_t secure_status) {
    return secure_hook_user(secure_status);
}
