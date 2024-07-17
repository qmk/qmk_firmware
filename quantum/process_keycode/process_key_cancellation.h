// Copyright 2024 Harrison Chan (@xelus22)

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "action.h"

#define NUM_INTERRUPT_KEYCODES 2

typedef struct key_cancellation_t {
    uint16_t press, unpress;
} key_cancellation_t;

bool process_key_cancellation(uint16_t keycode, keyrecord_t *record);
bool process_key_cancellation_user(uint16_t keycode, keyrecord_t *record);

bool key_cancellation_is_enabled(void);
void key_cancellation_enable(void);
void key_cancellation_disable(void);
void key_cancellation_toggle(void);
