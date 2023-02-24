#pragma once

#include <util/atomic.h>
#include <stdint.h>
#include <stdbool.h>

#ifndef RBUF_SIZE
#    define RBUF_SIZE 32
#endif

static uint8_t     rbuf[RBUF_SIZE];
static uint8_t     rbuf_head = 0;
static uint8_t     rbuf_tail = 0;
static inline bool rbuf_enqueue(uint8_t data) {
    bool ret = false;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        uint8_t next = (rbuf_head + 1) % RBUF_SIZE;
        if (next != rbuf_tail) {
            rbuf[rbuf_head] = data;
            rbuf_head       = next;
            ret             = true;
        }
    }
    return ret;
}
static inline uint8_t rbuf_dequeue(void) {
    uint8_t val = 0;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        if (rbuf_head != rbuf_tail) {
            val       = rbuf[rbuf_tail];
            rbuf_tail = (rbuf_tail + 1) % RBUF_SIZE;
        }
    }

    return val;
}
static inline bool rbuf_has_data(void) {
    bool has_data;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        has_data = (rbuf_head != rbuf_tail);
    }
    return has_data;
}
static inline void rbuf_clear(void) {
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        rbuf_head = rbuf_tail = 0;
    }
}
