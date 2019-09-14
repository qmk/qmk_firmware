/**
 * @file      mscmd.h
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

#ifndef MSCMD_H
#define MSCMD_H

#include "msopt.h"

typedef int MSCMD_USER_RESULT;
typedef void * MSCMD_USER_OBJECT;

typedef MSCMD_USER_RESULT (*MSCMD_FUNC)(MSOPT *msopt, MSCMD_USER_OBJECT usrobj);

typedef struct {
    char *argv0;
    MSCMD_FUNC func;
    char *desc;
} MSCMD_COMMAND_TABLE;

typedef struct {
    const MSCMD_COMMAND_TABLE *command_table;
    int command_count;
    MSCMD_USER_OBJECT usrobj;
} MSCMD;

#ifdef __cplusplus
extern "C" {
#endif

int mscmd_init(MSCMD *handle, const MSCMD_COMMAND_TABLE *command_table, int command_count, MSCMD_USER_OBJECT usrobj);
int mscmd_execute(MSCMD *handle, char *text, MSCMD_USER_RESULT *result);

#ifdef __cplusplus
}
#endif

#endif

