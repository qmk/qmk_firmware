// Copyright 2026 Roman Kuzmitskii (@damex)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef bool (*uart_frame_starts_fn)(uint8_t byte);
typedef bool (*uart_frame_complete_fn)(const uint8_t *partial, uint16_t partial_length);
typedef bool (*uart_frame_verify_fn)(const uint8_t *frame, uint16_t length);
typedef bool (*uart_frame_is_ack_fn)(const uint8_t *frame, uint16_t length);
typedef void (*uart_frame_send_ack_fn)(void);
typedef void (*uart_frame_on_receive_fn)(const uint8_t *frame, uint16_t length);

typedef struct {
    uart_frame_starts_fn     starts;
    uart_frame_complete_fn   complete;
    uart_frame_verify_fn     verify;
    uart_frame_is_ack_fn     is_ack;
    uart_frame_send_ack_fn   send_ack;
    uart_frame_on_receive_fn on_receive;
    uint16_t                 ack_timeout_ms;
    uint8_t                  retry_max;
} uart_frame_config_t;

void uart_frame_init(const uart_frame_config_t *config);
int8_t uart_frame_send(const uint8_t *frame, uint16_t length);
void uart_frame_task(void);
bool uart_frame_is_busy(void);
