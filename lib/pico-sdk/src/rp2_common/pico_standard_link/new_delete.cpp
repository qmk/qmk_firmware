/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#if !PICO_CXX_ENABLE_EXCEPTIONS 
// Override the standard allocators to use regular malloc/free

#if !PICO_CXX_DISABLE_ALLOCATION_OVERRIDES // Let user override
#include <cstdlib>

void *operator new(std::size_t n) {
    return std::malloc(n);
}

void *operator new[](std::size_t n) {
    return std::malloc(n);
}

void operator delete(void *p) { std::free(p); }

void operator delete[](void *p) noexcept { std::free(p); }

#if __cpp_sized_deallocation

void operator delete(void *p, __unused std::size_t n) noexcept { std::free(p); }

void operator delete[](void *p, __unused std::size_t n) noexcept { std::free(p); }

#endif

#endif

#endif
