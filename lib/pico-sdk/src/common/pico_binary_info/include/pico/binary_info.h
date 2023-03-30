/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PICO_BINARY_INFO_H
#define _PICO_BINARY_INFO_H

/** \file binary_info.h
 *  \defgroup pico_binary_info pico_binary_info
 *
 * Binary info is intended for embedding machine readable information with the binary in FLASH.
 *
 * Example uses include:
 *
 * - Program identification / information
 * - Pin layouts
 * - Included features
 * - Identifying flash regions used as block devices/storage
 */

#include "pico/binary_info/defs.h"
#include "pico/binary_info/structure.h"
#if !PICO_ON_DEVICE && !defined(PICO_NO_BINARY_INFO)
#define PICO_NO_BINARY_INFO 1
#endif
#include "pico/binary_info/code.h"
#endif
