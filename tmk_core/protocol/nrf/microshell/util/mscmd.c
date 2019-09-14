/**
 * @file      mscmd.c
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
#include "mscmd.h"
#include "ntlibc.h"

int mscmd_init(MSCMD *handle, const MSCMD_COMMAND_TABLE *command_table, int command_count, MSCMD_USER_OBJECT usrobj)
{
    handle->command_table = command_table;
    handle->command_count = command_count;
    handle->usrobj = usrobj;
    return 0;
}

int mscmd_execute(MSCMD *handle, char *text, MSCMD_USER_RESULT *result)
{
    MSOPT msopt;
    int argc = 0;
    char argv0[MSCONF_MAX_INPUT_LENGTH];

    msopt_init(&msopt, text);
    msopt_get_argc(&msopt, &argc);
    if (argc == 0) {
        return -1;
    }
    const MSCMD_COMMAND_TABLE *p = handle->command_table;
    int i;
    for (i = 0; i < handle->command_count; i++) {
        msopt_get_argv(&msopt, 0, argv0, sizeof(argv0));
        if (ntlibc_strcmp(argv0, p->argv0) == 0) {
            *result = p->func(&msopt, handle->usrobj);
            return 0;
        }
        p++;
    }
    return -2;
}

