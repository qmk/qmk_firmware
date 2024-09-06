// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "leader.h"
#include "timer.h"
#include "util.h"

#include <string.h>

#ifndef LEADER_TIMEOUT
#    define LEADER_TIMEOUT 300
#endif

// Leader key stuff
bool     leading              = false;
uint16_t leader_time          = 0;
uint16_t leader_sequence[5]   = {0, 0, 0, 0, 0};
uint8_t  leader_sequence_size = 0;

__attribute__((weak)) void leader_start_user(void) {}

__attribute__((weak)) void leader_end_user(void) {}

__attribute__((weak)) bool leader_add_user(uint16_t keycode) {
    return false;
}

void leader_start(void) {
    if (leading) {
        return;
    }
    leader_start_user();
    leading              = true;
    leader_time          = timer_read();
    leader_sequence_size = 0;
    memset(leader_sequence, 0, sizeof(leader_sequence));
}

void leader_end(void) {
    leading = false;
    leader_end_user();
}

void leader_task(void) {
    if (leader_sequence_active() && leader_sequence_timed_out()) {
        leader_end();
    }
}

bool leader_sequence_active(void) {
    return leading;
}

bool leader_sequence_add(uint16_t keycode) {
    if (leader_sequence_size >= ARRAY_SIZE(leader_sequence)) {
        return false;
    }

#if defined(LEADER_NO_TIMEOUT)
    if (leader_sequence_size == 0) {
        leader_reset_timer();
    }
#endif

    leader_sequence[leader_sequence_size] = keycode;
    leader_sequence_size++;

    if (leader_add_user(keycode)) {
        leader_end();
    }
    return true;
}

bool leader_sequence_timed_out(void) {
#if defined(LEADER_NO_TIMEOUT)
    return leader_sequence_size > 0 && timer_elapsed(leader_time) > LEADER_TIMEOUT;
#else
    return timer_elapsed(leader_time) > LEADER_TIMEOUT;
#endif
}

void leader_reset_timer(void) {
    leader_time = timer_read();
}

bool leader_sequence_is(uint16_t kc1, uint16_t kc2, uint16_t kc3, uint16_t kc4, uint16_t kc5) {
    return leader_sequence[0] == kc1 && leader_sequence[1] == kc2 && leader_sequence[2] == kc3 && leader_sequence[3] == kc4 && leader_sequence[4] == kc5;
}

bool leader_sequence_one_key(uint16_t kc) {
    return leader_sequence_is(kc, 0, 0, 0, 0);
}

bool leader_sequence_two_keys(uint16_t kc1, uint16_t kc2) {
    return leader_sequence_is(kc1, kc2, 0, 0, 0);
}

bool leader_sequence_three_keys(uint16_t kc1, uint16_t kc2, uint16_t kc3) {
    return leader_sequence_is(kc1, kc2, kc3, 0, 0);
}

bool leader_sequence_four_keys(uint16_t kc1, uint16_t kc2, uint16_t kc3, uint16_t kc4) {
    return leader_sequence_is(kc1, kc2, kc3, kc4, 0);
}

bool leader_sequence_five_keys(uint16_t kc1, uint16_t kc2, uint16_t kc3, uint16_t kc4, uint16_t kc5) {
    return leader_sequence_is(kc1, kc2, kc3, kc4, kc5);
}
