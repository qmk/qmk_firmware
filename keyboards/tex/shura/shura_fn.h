// Copyright 2026 Antonio SJ Musumeci (@trapexit)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include <stdbool.h>
#include <stdint.h>

enum { SHURA_FN_COUNT = 3, SHURA_FN1_LAYER = 1, SHURA_FN2_LAYER = 2, SHURA_FN3_LAYER = 3 };

// Dedicated counts and the middle contribution are independent owners.
typedef struct ShuraFnState {
    uint8_t dedicated[SHURA_FN_COUNT];
    bool    middle_down;
    bool    middle_used;
} ShuraFnState;

void shura_fn_dedicated(ShuraFnState *state_, uint8_t index_, bool pressed_);
// Returns true only for an unused middle release; the caller sends a balanced click.
bool    shura_fn_middle(ShuraFnState *state_, bool pressed_);
void    shura_fn_consume(ShuraFnState *state_);
uint8_t shura_fn_layers(const ShuraFnState *state_);
bool    shura_fn_scroll(const ShuraFnState *state_, bool dedicated_scroll_);
