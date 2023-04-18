// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "qp.h"
#include "color.h"

extern painter_device_t display;

// Helper macro to avoid duplication, will also come handy if the signature of the function changes
#define QP_ARGS \
    SCREEN_WIDTH, SCREEN_HEIGHT, CS_PIN, DC_PIN, RST_PIN, SPI_DIV, SPI_MODE
