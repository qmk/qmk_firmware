// Copyright 2026 Antonio SJ Musumeci (@trapexit)
// SPDX-License-Identifier: GPL-2.0-or-later
//
// Fn layer ownership: the middle button and each dedicated Fn key hold layers
// independently. A middle release clicks only if nothing used it while held.
#include "shura_fn.h"

void shura_fn_dedicated(ShuraFnState *state_, uint8_t index_, bool pressed_) {
    if (index_ >= SHURA_FN_COUNT) {
        return;
    }
    if (pressed_) {
        shura_fn_consume(state_);
        if (state_->dedicated[index_] != UINT8_MAX) {
            state_->dedicated[index_]++;
        }
    } else if (state_->dedicated[index_] != 0) {
        state_->dedicated[index_]--;
    }
}

bool shura_fn_middle(ShuraFnState *state_, bool pressed_) {
    bool click = false;

    if (pressed_) {
        if (!state_->middle_down) {
            state_->middle_used = false;
        }
        state_->middle_down = true;
    } else {
        click               = (state_->middle_down && !state_->middle_used);
        state_->middle_down = false;
        state_->middle_used = false;
    }

    return click;
}

void shura_fn_consume(ShuraFnState *state_) {
    if (state_->middle_down) {
        state_->middle_used = true;
    }
}

uint8_t shura_fn_layers(const ShuraFnState *state_) {
    uint8_t layers = 0;
    uint8_t index;

    for (index = 0; index < SHURA_FN_COUNT; index++) {
        if (state_->dedicated[index] != 0) {
            layers |= (uint8_t)(1U << (index + SHURA_FN1_LAYER));
        }
    }

    if (state_->middle_down) {
        layers |= (uint8_t)(1U << SHURA_FN1_LAYER);
    }
    return layers;
}

bool shura_fn_scroll(const ShuraFnState *state_, bool dedicated_scroll_) {
    return (state_->middle_down || (dedicated_scroll_ && (state_->dedicated[0] != 0)));
}
