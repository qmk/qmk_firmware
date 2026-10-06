// Copyright 2026 doombadroid (@doombadroid)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* NUC1261SG4AE (PDID 0x01205212) is register-compatible with the NUC126SG4AE. */
#define NUC126SG4AE
#define BOARD_NAME "Ducky One 3 RGB (NUC1261SG4AE)"

#if !defined(_FROM_ASM_)
void boardInit(void);
#endif
