// Copyright 2024 Stefan Kerkmann
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef __ASSEMBLER__

#define __not_in_flash(group) __attribute__((section(".ramtext." group)))

#else 

#define RAM_SECTION_NAME(x) .ramtext.##x

#endif
