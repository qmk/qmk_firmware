/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/divider.h"

// These functions save/restore divider state, so are safe to call from interrupts
int32_t div_s32s32(int32_t a, int32_t b) {
    return hw_divider_s32_quotient(a, b);
}

divmod_result_t divmod_s32s32(int32_t a, int32_t b) {
    return hw_divider_divmod_s32(a, b);
}

uint32_t div_u32u32(uint32_t a, uint32_t b) {
    return hw_divider_u32_quotient(a, b);
}

divmod_result_t divmod_u32u32(uint32_t a, uint32_t b) {
    return hw_divider_divmod_u32(a, b);
}

static inline int __sign_of_64(int32_t v) {
    return v > 0 ? 1 : (v < 0 ? -1 : 0);
}

typedef struct {
    uint64_t quotient;
    uint64_t remainder;
} qr_u64;

typedef struct {
    int64_t quotient;
    int64_t remainder;
} qr_s64;

// divides unsigned values a by b... (a/b) returned in low 32 bits, (a%b) in high 32 bits... results undefined for b==0
static inline qr_u64 udiv64(uint64_t a, uint64_t b) {
    qr_u64 rc;
    if (!b) {
        rc.quotient = (uint64_t)-1; // todo check this
        rc.remainder = a;
    } else {
        rc.quotient = a/b;
        rc.remainder = a%b;
    }
    return rc;
}

// divides signed values a by b... (a/b) returned in low 32 bits, (a%b) in high 32 bits... results undefined for b==0
static inline qr_s64 div64(int64_t a, int64_t b) {
    qr_s64 rc;
    if (!b) {
        rc.quotient = (uint64_t)(-__sign_of_64(a));
        rc.remainder = a;
    } else {
        rc.quotient = a/b;
        rc.remainder = a%b;
    }
    return rc;
}

int64_t div_s64s64(int64_t a, int64_t b) {
    qr_s64 qr = div64(a, b);
    return qr.quotient;
}

int64_t divmod_s64s64_rem(int64_t a, int64_t b, int64_t *rem) {
    qr_s64 qr = div64(a, b);
    *rem = qr.remainder;
    return qr.quotient;
}

int64_t divmod_s64s64(int64_t a, int64_t b) {
    qr_s64 qr = div64(a, b);
    return qr.quotient;
}

uint64_t div_u64u64(uint64_t a, uint64_t b) {
    qr_u64 qr = udiv64(a, b);
    return qr.quotient;
}

uint64_t divmod_u64u64_rem(uint64_t a, uint64_t b, uint64_t *rem) {
    qr_u64 qr = udiv64(a, b);
    *rem = qr.remainder;
    return qr.quotient;
}

uint64_t divmod_u64u64(uint64_t a, uint64_t b) {
    qr_u64 qr = udiv64(a, b);
    return qr.quotient;
}

// these functions are slightly faster, but unsafe the divider state, so are not generally safe to be called from interrupts

int32_t div_s32s32_unsafe(int32_t a, int32_t b) { return div_s32s32(a,b); }
int32_t divmod_s32s32_rem_unsafe(int32_t a, int32_t b, int32_t *rem) { return divmod_s32s32_rem(a, b, rem); }
int64_t divmod_s32s32_unsafe(int32_t a, int32_t b) { return divmod_s32s32(a, b); }

uint32_t div_u32u32_unsafe(uint32_t a, uint32_t b) { return div_u32u32(a, b); }
uint32_t divmod_u32u32_rem_unsafe(uint32_t a, uint32_t b, uint32_t *rem) { return divmod_u32u32_rem(a, b, rem); }
uint64_t divmod_u32u32_unsafe(uint32_t a, uint32_t b) { return divmod_u32u32(a, b); }

int64_t div_s64s64_unsafe(int64_t a, int64_t b) { return div_s64s64(a, b); }
int64_t divmod_s64s64_rem_unsafe(int64_t a, int64_t b, int64_t *rem) { return divmod_s64s64_rem(a, b, rem); }
int64_t divmod_s64s64_unsafe(int64_t a, int64_t b) { return divmod_s64s64(a, b); }

uint64_t div_u64u64_unsafe(uint64_t a, uint64_t b) { return div_u64u64(a, b); }
uint64_t divmod_u64u64_rem_unsafe(uint64_t a, uint64_t b, uint64_t *rem) { return divmod_u64u64_rem(a, b, rem); }
uint64_t divmod_u64u64_unsafe(uint64_t a, uint64_t b) { return divmod_u64u64(a, b); }
