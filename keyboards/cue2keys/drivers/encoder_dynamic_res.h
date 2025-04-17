// Copyright 2018 Jack Humbert <jack.humb@gmail.com>
// Copyright 2018-2023 Nick Brassel (@tzarc)
// Copyright 2025 @esplo
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <stdint.h>
#include <stdbool.h>

#define ENCODER_CLOCKWISE true
#define ENCODER_COUNTER_CLOCKWISE false

extern uint8_t encoder_quadrature_read_pin(uint8_t index, bool pad_b);
void           dynamic_res_encoder_quadrature_handle_read(uint8_t index, uint8_t pin_a_state, uint8_t pin_b_state);
void           dynamic_res_encoder_update_res(uint8_t index, uint8_t res);
