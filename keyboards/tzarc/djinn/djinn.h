// Copyright 2018-2023 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once
#include "quantum.h"
#include "qp.h"

//----------------------------------------------------------
// General stuff

extern painter_device_t lcd;

void matrix_wait_for_interrupt(void);

void        usbpd_update(void);
const char* usbpd_str(usbpd_allowance_t allowance);

//----------------------------------------------------------
// Runtime data sync -- keyboard

#pragma pack(push)
#pragma pack(1)
typedef struct kb_runtime_config {
    usbpd_allowance_t current_setting : 2;
} kb_runtime_config;
#pragma pack(pop)

extern kb_runtime_config kb_state;

void kb_state_update(void);
void kb_state_sync(void);
void kb_state_sync_slave(uint8_t m2s_size, const void* m2s_buffer, uint8_t s2m_size, void* s2m_buffer);
