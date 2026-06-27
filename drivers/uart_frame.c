// Copyright 2026 Roman Kuzmitskii (@damex)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "uart_frame.h"

#include <assert.h>
#include "quantum.h"
#include "uart.h"

#ifndef UART_FRAME_QUEUE_CAPACITY
#    define UART_FRAME_QUEUE_CAPACITY 8
#endif

#ifndef UART_FRAME_PAYLOAD_MAX
#    define UART_FRAME_PAYLOAD_MAX 36
#endif

#define UART_FRAME_QUEUE_BUFFER_SIZE (UART_FRAME_QUEUE_CAPACITY * UART_FRAME_PAYLOAD_MAX)

typedef enum {
    QUEUE_STATE_FREE = 0,
    QUEUE_STATE_BUSY,
    QUEUE_STATE_RETRY,
    QUEUE_STATE_REPLIED,
} queue_state_t;

typedef struct {
    uint16_t buffer_offset;
    uint16_t length;
} queue_entry_t;

typedef struct {
    queue_state_t state;
    queue_entry_t entries[UART_FRAME_QUEUE_CAPACITY];
    uint16_t      read_entry_index;
    uint16_t      write_entry_index;
    uint16_t      write_buffer_offset;
    uint16_t      buffer_used_bytes;
} queue_t;

static uint8_t                    queue_buffer[UART_FRAME_QUEUE_BUFFER_SIZE];
static queue_t                    queue_instance;
static const uart_frame_config_t *active_config;
static uint8_t                    scratch_payload[UART_FRAME_PAYLOAD_MAX];
static uint8_t                    receive_payload[UART_FRAME_PAYLOAD_MAX];

static void queue_init(void) {
    queue_instance.read_entry_index    = 0;
    queue_instance.write_entry_index   = 0;
    queue_instance.write_buffer_offset = 0;
    queue_instance.buffer_used_bytes   = 0;
    queue_instance.state               = QUEUE_STATE_FREE;
}

static bool queue_push(const uint8_t *data, uint16_t size) {
    if (size > UART_FRAME_PAYLOAD_MAX) {
        return false;
    }

    uint16_t next_write_entry_index = (queue_instance.write_entry_index + 1) % UART_FRAME_QUEUE_CAPACITY;
    if (next_write_entry_index == queue_instance.read_entry_index) {
        return false;
    }

    if (UART_FRAME_QUEUE_BUFFER_SIZE - queue_instance.buffer_used_bytes < size) {
        return false;
    }

    uint16_t start_offset = queue_instance.write_buffer_offset;
    for (uint16_t byte_index = 0; byte_index < size; byte_index++) {
        queue_buffer[(start_offset + byte_index) % UART_FRAME_QUEUE_BUFFER_SIZE] = data[byte_index];
    }

    queue_instance.entries[queue_instance.write_entry_index].buffer_offset = start_offset;
    queue_instance.entries[queue_instance.write_entry_index].length        = size;
    queue_instance.write_entry_index                                       = next_write_entry_index;
    queue_instance.write_buffer_offset                                     = (start_offset + size) % UART_FRAME_QUEUE_BUFFER_SIZE;
    queue_instance.buffer_used_bytes += size;

    return true;
}

static uint16_t queue_peek(uint8_t *data, uint16_t length) {
    if (queue_instance.read_entry_index == queue_instance.write_entry_index) {
        return 0;
    }

    queue_entry_t *entry = &queue_instance.entries[queue_instance.read_entry_index];
    if (entry->length > length) {
        return 0;
    }

    for (uint16_t byte_index = 0; byte_index < entry->length; byte_index++) {
        data[byte_index] = queue_buffer[(entry->buffer_offset + byte_index) % UART_FRAME_QUEUE_BUFFER_SIZE];
    }

    return entry->length;
}

static void queue_pop(void) {
    if (queue_instance.read_entry_index == queue_instance.write_entry_index) {
        return;
    }

    queue_entry_t *entry = &queue_instance.entries[queue_instance.read_entry_index];
    queue_instance.buffer_used_bytes -= entry->length;
    queue_instance.read_entry_index = (queue_instance.read_entry_index + 1) % UART_FRAME_QUEUE_CAPACITY;
}

static void receive_task(void) {
    static uint16_t buffered = 0;

    while (uart_available()) {
        uint8_t data = uart_read();

        if (buffered == 0 && !active_config->starts(data)) {
            continue;
        }

        if (buffered >= UART_FRAME_PAYLOAD_MAX) {
            buffered = 0;
            continue;
        }

        receive_payload[buffered++] = data;

        if (!active_config->complete(receive_payload, buffered)) {
            continue;
        }

        if (active_config->is_ack(receive_payload, buffered)) {
            if (queue_instance.state == QUEUE_STATE_BUSY) {
                queue_instance.state = QUEUE_STATE_REPLIED;
            }
        } else if (active_config->verify(receive_payload, buffered)) {
            active_config->send_ack();
            active_config->on_receive(receive_payload, buffered);
        }

        buffered = 0;
    }
}

static void send_task(void) {
    static uint32_t send_timer  = 0;
    static uint8_t  retry_count = 0;

    switch (queue_instance.state) {
        case QUEUE_STATE_BUSY: {
            if (sync_timer_elapsed32(send_timer) > active_config->ack_timeout_ms) {
                queue_instance.state = QUEUE_STATE_RETRY;
            }
            break;
        }
        case QUEUE_STATE_RETRY: {
            if (++retry_count > active_config->retry_max) {
                retry_count = 0;
                queue_pop();
            }
            queue_instance.state = QUEUE_STATE_FREE;
            break;
        }
        case QUEUE_STATE_REPLIED: {
            retry_count = 0;
            queue_pop();
            queue_instance.state = QUEUE_STATE_FREE;
        }
            /* fallthrough */
        case QUEUE_STATE_FREE: {
            uint16_t size = queue_peek(scratch_payload, sizeof(scratch_payload));
            if (size > 0) {
                uart_transmit(scratch_payload, size);
                send_timer           = sync_timer_read32();
                queue_instance.state = QUEUE_STATE_BUSY;
            }
            break;
        }
        default: {
            assert(false);
            break;
        }
    }
}

void uart_frame_init(const uart_frame_config_t *config) {
    assert(config != NULL);
    assert(config->starts != NULL);
    assert(config->complete != NULL);
    assert(config->verify != NULL);
    assert(config->is_ack != NULL);
    assert(config->send_ack != NULL);
    assert(config->on_receive != NULL);

    active_config = config;
    queue_init();
}

int8_t uart_frame_send(const uint8_t *frame, uint16_t length) {
    assert(frame != NULL);
    return queue_push(frame, length) ? 0 : -1;
}

void uart_frame_task(void) {
    send_task();
    receive_task();
}

bool uart_frame_is_busy(void) {
    return queue_instance.read_entry_index != queue_instance.write_entry_index;
}
