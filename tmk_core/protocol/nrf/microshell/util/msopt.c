/**
 * @file      msopt.c
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

#include "msopt.h"

#define INITCODE            (0x97c0)
#define IS_WHITE_SPACE(C)   (((C) == ' ') || ((C) == '\t') || ((C) == '\r') || ((C) == '\n'))

static char *skip_white_space(char *text)
{
    char *p = text;
    while (IS_WHITE_SPACE(*p)) {
        if (*p == 0) {
            break;
        }
        p++;
    }
    return p;
}

static char *skip_text_string(char *text, int *length)
{
    char *p = text;
    int count = 0;
    while (!IS_WHITE_SPACE(*p)) {
        if (*p == 0) {
            break;
        }
        p++;
        count++;
    }
    *length = count;
    return p;
}

MSOPT_RESULT msopt_init(MSOPT *handle, char *text)
{
    char *src = text;
    char *des = handle->argv;
    while (*src) {
        *des++ = *src++;
    }
    *des = 0;
    handle->argc = 0;
    char *p = handle->argv;
    while (1) {
        if (handle->argc >= MSCONF_MAX_INPUT_ARGS) {
            return MSOPT_RESULT_ERROR_TOO_MUCH_ARGUMENTS;
        }
        p = skip_white_space(p);
        if (*p == 0) {
            break;
        }
        handle->info[handle->argc].head = p;
        p = skip_text_string(p, &(handle->info[handle->argc].length));
        handle->argc++;
    }
    handle->initcode = INITCODE;
    return MSOPT_RESULT_OK;
}

MSOPT_RESULT msopt_get_argc(MSOPT *handle, int *argc)
{
    if (handle->initcode != INITCODE) {
        *argc = 0;
        return MSOPT_RESULT_ERROR_ILLEGAL_OBJECT;
    }
    *argc = handle->argc;
    return MSOPT_RESULT_OK;
}

MSOPT_RESULT msopt_get_argv(MSOPT *handle, int index, char *bufptr, int bufsiz)
{
    *bufptr = 0;
    if (handle->argc <= index) {
        return MSOPT_RESULT_ERROR_ILLEGAL_INDEX_NUMBER;
    }
    char *src = handle->info[index].head;
    char *des = bufptr;
    int i;
    for (i = 0; i < handle->info[index].length; i++) {
        if (i >= bufsiz - 1) {
            *des = 0;
            return MSOPT_RESULT_ERROR_BUFFER_SIZE;
        }
        *des++ = *src++;
    }
    *des = 0;
    return MSOPT_RESULT_OK;
}

