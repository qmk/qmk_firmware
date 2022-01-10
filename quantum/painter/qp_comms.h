// Copyright 2021 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdbool.h>
#include <stdlib.h>

#include <qp_internal.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Base comms APIs

bool     qp_comms_init(painter_device_t device);
bool     qp_comms_start(painter_device_t device);
void     qp_comms_stop(painter_device_t device);
uint32_t qp_comms_send(painter_device_t device, const void QP_RESIDENT_FLASH_OR_RAM* data, uint32_t byte_count);
