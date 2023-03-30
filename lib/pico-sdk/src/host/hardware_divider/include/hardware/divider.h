/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_DIVIDER_H
#define _HARDWARE_DIVIDER_H

#include "pico/types.h"

typedef uint64_t divmod_result_t;

static inline int __sign_of(int32_t v) {
    return v > 0 ? 1 : (v < 0 ? -1 : 0);
}

// divides unsigned values a by b... (a/b) returned in low 32 bits, (a%b) in high 32 bits... results undefined for b==0
static inline uint64_t hw_divider_divmod_u32(uint32_t a, uint32_t b) {
    if (!b) return (((uint64_t)a)<<32u) | (uint32_t)(-1); // todo check this
    return (((uint64_t)(a%b))<<32u) | (a/b);
}

// divides signed values a by b... (a/b) returned in low 32 bits, (a%b) in high 32 bits... results undefined for b==0
static inline uint64_t hw_divider_divmod_s32(int32_t a, int32_t b) {
    if (!b) return (((uint64_t)a)<<32u) | (uint32_t)(-__sign_of(a));
    return (((uint64_t)(a%b))<<32u) | (uint32_t)(a/b);
}

extern __thread divmod_result_t hw_divider_result_threadlocal;

static inline void hw_divider_divmod_s32_start(int32_t a, int32_t b) {
    hw_divider_result_threadlocal = hw_divider_divmod_s32(a, b);
}

static inline void hw_divider_divmod_u32_start(uint32_t a, uint32_t b) {
    hw_divider_result_threadlocal = hw_divider_divmod_u32(a, b);
}

static inline divmod_result_t hw_divider_result_wait() {
    return hw_divider_result_threadlocal;
}

static inline uint64_t hw_divider_result_nowait() {
    return hw_divider_result_threadlocal;
}

inline static uint32_t to_quotient_u32(unsigned long long int r) {
    return (uint32_t) r;
}

inline static int32_t to_quotient_s32(unsigned long long int r) {
    return (int32_t)(uint32_t)r;
}

inline static uint32_t to_remainder_u32(unsigned long long int r) {
    return (uint32_t)(r >> 32u);
}

inline static int32_t to_remainder_s32(unsigned long long int r) {
    return (int32_t)(r >> 32u);
}

static inline uint32_t hw_divider_u32_quotient_wait() {
    return to_quotient_u32(hw_divider_result_wait());
}

static inline uint32_t hw_divider_u32_remainder_wait() {
    return to_remainder_u32(hw_divider_result_wait());
}

static inline int32_t hw_divider_s32_quotient_wait() {
    return to_quotient_s32(hw_divider_result_wait());
}

static inline int32_t hw_divider_s32_remainder_wait() {
    return to_remainder_s32(hw_divider_result_wait());
}

static inline uint32_t hw_divider_u32_quotient(uint32_t a, uint32_t b) {
    return b ? (a / b) : (uint32_t)(-1);
}

static inline uint32_t hw_divider_u32_remainder(uint32_t a, uint32_t b) {
    return b ? (a % b) : a;
}

static inline int32_t hw_divider_s32_quotient(int32_t a, int32_t b) {
    return b ? (a / b) : -__sign_of(a);
}

static inline int32_t hw_divider_s32_remainder(int32_t a, int32_t b) {
    return b ? (a % b) : a;
}

static inline uint32_t hw_divider_u32_quotient_inlined(uint32_t a, uint32_t b) {
    return hw_divider_u32_quotient(a,b);
}

static inline uint32_t hw_divider_u32_remainder_inlined(uint32_t a, uint32_t b) {
    return hw_divider_u32_remainder(a,b);
}

static inline int32_t hw_divider_s32_quotient_inlined(int32_t a, int32_t b) {
    return hw_divider_s32_quotient(a,b);
}

static inline int32_t hw_divider_s32_remainder_inlined(int32_t a, int32_t b) {
    return hw_divider_s32_remainder(a,b);
}

typedef uint64_t hw_divider_state_t;

static inline void hw_divider_save_state(hw_divider_state_t *dest) {
    *dest = hw_divider_result_threadlocal;
}

static inline void hw_divider_restore_state(hw_divider_state_t *src) {
    hw_divider_result_threadlocal = *src;
}

#endif // _HARDWARE_DIVIDER_H
