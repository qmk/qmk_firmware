/**
 * @file      microshell.h
 * @author    Shinichiro Nakamura (CuBeatSystems)
 * ===============================================================
 * MicroShell (Version 0.0.2)
 * Copyright (c) 2016, 2017 Shinichiro Nakamura (CuBeatSystems)
 * ===============================================================
 * The MIT License : https://opensource.org/licenses/MIT
 *
 * Copyright (c) 2016, 2017 Shinichiro Nakamura (CuBeatSystems)
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef MICROSHELL_H
#define MICROSHELL_H

#include "mscore.h"

typedef void (*MICROSHELL_UART_PUTC)(char c);
typedef int (*MICROSHELL_UART_AVAILABLE)(void);
typedef char (*MICROSHELL_UART_GETC)(void);
typedef void (*MICROSHELL_ACTION_HOOK)(MSCORE_ACTION action);

typedef struct {
    MSCORE mscore;
    MICROSHELL_UART_PUTC uart_putc;
    MICROSHELL_UART_AVAILABLE uart_available;
    MICROSHELL_UART_GETC uart_getc;
    MICROSHELL_ACTION_HOOK action_hook;
} MICROSHELL;

#ifdef __cplusplus
extern "C" {
#endif

void microshell_init(MICROSHELL *handle, MICROSHELL_UART_PUTC uart_putc, MICROSHELL_UART_AVAILABLE uart_available, MICROSHELL_UART_GETC uart_getc, MICROSHELL_ACTION_HOOK action_hook);
char *microshell_getline(MICROSHELL *handle, char *buf, char *cur, int siz);

#ifdef __cplusplus
}
#endif

#endif

