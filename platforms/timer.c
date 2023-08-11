// Copyright 2023 Sergey Vlasov (@sigprof)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "timer.h"

// Generate out-of-line copies for inline functions defined in timer.h.
extern inline fast_timer_t timer_read_fast(void);
extern inline fast_timer_t timer_elapsed_fast(fast_timer_t last);
