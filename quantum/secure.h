// Copyright 2022 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    SECURE_LOCKED,
    SECURE_PENDING,
    SECURE_UNLOCKED,
} secure_status_t;

secure_status_t secure_get_status(void);

bool secure_is_unlocking(void);

void secure_lock(void);

void secure_unlock(void);

void secure_request_unlock(void);

void secure_activity_event(void);

void secure_keypress_event(uint8_t row, uint8_t col);

void secure_task(void);
