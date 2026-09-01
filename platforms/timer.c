// Copyright 2023 Sergey Vlasov (@sigprof)
// SPDX-License-Identifier: GPL-2.0-or-later

// Use an angle-bracket include so the header is located via the include
// search path rather than source-relative lookup. timer.h uses
// #include_next to chain to the active platform's _timer.h, and that
// only has well-defined semantics when timer.h itself was found via -I.
#include <timer.h>

// Generate out-of-line copies for inline functions defined in timer.h.
extern inline fast_timer_t timer_read_fast(void);
extern inline fast_timer_t timer_elapsed_fast(fast_timer_t last);

uint16_t timer_elapsed(uint16_t last) {
    return TIMER_DIFF_16(timer_read(), last);
}

uint32_t timer_elapsed32(uint32_t last) {
    return TIMER_DIFF_32(timer_read32(), last);
}
