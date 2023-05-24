// Copyright 2022 Stefan Kerkmann
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#if defined(PLATFORM_SUPPORTS_SYNCHRONIZATION)
#    if defined(SPLIT_KEYBOARD)
void split_shared_memory_lock(void);
void split_shared_memory_unlock(void);
#    endif
#else
inline void split_shared_memory_lock(void){};
inline void split_shared_memory_unlock(void){};
#endif
