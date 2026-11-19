// Copyright 2025 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once
#include_next <errno.h>

// Picolibc does not define `struct _reent`, which is used by ChibiOS.
#ifdef __PICOLIBC__
struct _reent;
#endif

// Newer versions of picolibc don't seem to provide `__errno_r(r)` in the header file, but is used by ChibiOS.
#ifndef __errno_r
#    ifdef __REENT_ERRNO
#        define __errno_r(r) _REENT_ERRNO(r)
#    else
#        define __errno_r(r) (errno)
#    endif
#endif
