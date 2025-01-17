// Created/amended by OleVoip 2024.
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config.h"

typedef char labelmap_t[DRIVE_LINES][SENSE_LINES][4];
extern const labelmap_t key_position_labels;
extern void init_bus(void);

// .