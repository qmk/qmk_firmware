// Copyright 2023 Sergey Vlasov (@sigprof)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "synchronization_util.h"

// Generate out-of-line copies for inline functions defined in synchronization_util.h.

#if !defined(PLATFORM_SUPPORTS_SYNCHRONIZATION)
#    if defined(SPLIT_KEYBOARD)
extern inline void split_shared_memory_lock(void);
extern inline void split_shared_memory_unlock(void);
#    endif
#endif

#if defined(SPLIT_KEYBOARD)
QMK_IMPLEMENT_AUTOUNLOCK_HELPERS(split_shared_memory)
#endif
