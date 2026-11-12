// Copyright 2026 Connor Gallopo (@connorgallopo)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define BOARD_NAME "Metakey Tenet 70"

#define HT32F52352

#define FLASH_SIZE (0x20000 - 0x4000)  // 128kB - 16kB bootloader

#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
void boardInit(void);
#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */
