/**
 * @file      msopt.h
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

#ifndef MSOPT_H
#define MSOPT_H

#include "msconf.h"

typedef struct {
    char *head;
    int length;
} MSOPT_ARGINFO;

typedef struct {
    unsigned int initcode;
    int argc;
    char argv[MSCONF_MAX_INPUT_LENGTH];
    MSOPT_ARGINFO info[MSCONF_MAX_INPUT_ARGS];
} MSOPT;

typedef enum {
    MSOPT_RESULT_OK = 0,
    MSOPT_RESULT_ERROR_ILLEGAL_OBJECT,
    MSOPT_RESULT_ERROR_ILLEGAL_INDEX_NUMBER,
    MSOPT_RESULT_ERROR_TOO_MUCH_ARGUMENTS,
    MSOPT_RESULT_ERROR_BUFFER_SIZE,
} MSOPT_RESULT;

#ifdef __cplusplus
extern "C" {
#endif

MSOPT_RESULT msopt_init(MSOPT *handle, char *text);
MSOPT_RESULT msopt_get_argc(MSOPT *handle, int *argc);
MSOPT_RESULT msopt_get_argv(MSOPT *handle, int index, char *bufptr, int bufsiz);

#ifdef __cplusplus
}
#endif

#endif

