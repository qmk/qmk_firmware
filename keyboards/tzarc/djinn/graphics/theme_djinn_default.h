// Copyright 2018-2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

//----------------------------------------------------------
// Sync

#pragma pack(push)
#pragma pack(1)
typedef struct theme_runtime_config {
    uint32_t scan_rate;
} theme_runtime_config;
#pragma pack(pop)

extern theme_runtime_config theme_state;

void theme_init(void);
void theme_state_update(void);
void theme_state_sync(void);
