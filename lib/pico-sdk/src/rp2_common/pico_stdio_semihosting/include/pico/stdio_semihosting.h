/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PICO_STDIO_SEMIHOSTING_H
#define _PICO_STDIO_SEMIHOSTING_H

#include "pico/stdio.h"

/** \brief Experimental support for stdout using RAM semihosting
 *  \defgroup pico_stdio_semihosting pico_stdio_semihosting
 *  \ingroup pico_stdio
 *
 *  Linking this library or calling `pico_enable_stdio_semihosting(TARGET ENABLED)` in the CMake (which
 *  achieves the same thing) will add semihosting to the drivers used for standard output
 */

// PICO_CONFIG: PICO_STDIO_SEMIHOSTING_DEFAULT_CRLF, Default state of CR/LF translation for semihosting output, type=bool, default=PICO_STDIO_DEFAULT_CRLF, group=pico_stdio_semihosting
#ifndef PICO_STDIO_SEMIHOSTING_DEFAULT_CRLF
#define PICO_STDIO_SEMIHOSTING_DEFAULT_CRLF PICO_STDIO_DEFAULT_CRLF
#endif

#ifdef __cplusplus
extern "C" {
#endif

extern stdio_driver_t stdio_semihosting;

/*! \brief Explicitly initialize stdout over semihosting and add it to the current set of stdout targets
 *  \ingroup pico_stdio_semihosting
 *
 * \note this method is automatically called by \ref stdio_init_all() if `pico_stdio_semihosting` is included in the build
 */
void stdio_semihosting_init(void);

#ifdef __cplusplus
}
#endif

#endif
