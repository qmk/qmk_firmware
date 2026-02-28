// Copyright 2021 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdbool.h>
#include <stdlib.h>

#include "qp_internal.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Base comms APIs

bool     qp_comms_init(painter_device_t device);
bool     qp_comms_start(painter_device_t device);
void     qp_comms_stop(painter_device_t device);
uint32_t qp_comms_send(painter_device_t device, const void* data, uint32_t byte_count);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Comms APIs that use a D/C pin

bool     qp_comms_command(painter_device_t device, uint8_t cmd);
bool     qp_comms_command_databyte(painter_device_t device, uint8_t cmd, uint8_t data);
uint32_t qp_comms_command_databuf(painter_device_t device, uint8_t cmd, const void* data, uint32_t byte_count);
bool     qp_comms_bulk_command_sequence(painter_device_t device, const uint8_t* sequence, size_t sequence_len);
