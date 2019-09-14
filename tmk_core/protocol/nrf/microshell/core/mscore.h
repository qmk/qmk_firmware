/**
 * @file      mscore.h
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

#ifndef MSCORE_H
#define MSCORE_H

#define MSCORE_BUFFER_SIZE     (8)
#define MSCORE_INITIALIZER()   { .keycnt = 0, .keybuf = {0} }

typedef enum {
    MSCORE_ACTION_IGNORE,
    MSCORE_ACTION_DISPLAYABLE,
    MSCORE_ACTION_BS,
    MSCORE_ACTION_DEL,
    MSCORE_ACTION_TAB,
    MSCORE_ACTION_INSERT,
    MSCORE_ACTION_ENTER,
    MSCORE_ACTION_CTRL_A,
    MSCORE_ACTION_CTRL_B,
    MSCORE_ACTION_CTRL_C,
    MSCORE_ACTION_CTRL_D,
    MSCORE_ACTION_CTRL_E,
    MSCORE_ACTION_CTRL_F,
    MSCORE_ACTION_CTRL_G,
    MSCORE_ACTION_CTRL_H,
    MSCORE_ACTION_CTRL_I,
    MSCORE_ACTION_CTRL_J,
    MSCORE_ACTION_CTRL_K,
    MSCORE_ACTION_CTRL_L,
    MSCORE_ACTION_CTRL_M,
    MSCORE_ACTION_CTRL_N,
    MSCORE_ACTION_CTRL_O,
    MSCORE_ACTION_CTRL_P,
    MSCORE_ACTION_CTRL_Q,
    MSCORE_ACTION_CTRL_R,
    MSCORE_ACTION_CTRL_S,
    MSCORE_ACTION_CTRL_T,
    MSCORE_ACTION_CTRL_U,
    MSCORE_ACTION_CTRL_V,
    MSCORE_ACTION_CTRL_W,
    MSCORE_ACTION_CTRL_X,
    MSCORE_ACTION_CTRL_Y,
    MSCORE_ACTION_CTRL_Z,
    MSCORE_ACTION_F1,
    MSCORE_ACTION_F2,
    MSCORE_ACTION_F3,
    MSCORE_ACTION_F4,
    MSCORE_ACTION_F5,
    MSCORE_ACTION_F6,
    MSCORE_ACTION_F7,
    MSCORE_ACTION_F8,
    MSCORE_ACTION_F9,
    MSCORE_ACTION_F10,
    MSCORE_ACTION_F11,
    MSCORE_ACTION_F12,
    MSCORE_ACTION_ARROW_UP,
    MSCORE_ACTION_ARROW_DOWN,
    MSCORE_ACTION_ARROW_LEFT,
    MSCORE_ACTION_ARROW_RIGHT,
    MSCORE_ACTION_HOME,
    MSCORE_ACTION_END,
    MSCORE_ACTION_PAGE_UP,
    MSCORE_ACTION_PAGE_DOWN,
} MSCORE_ACTION;

typedef struct {
    int keycnt;
    char keybuf[MSCORE_BUFFER_SIZE];
} MSCORE;

#ifdef __cplusplus
extern "C" {
#endif

void mscore_init(MSCORE *handle);
MSCORE_ACTION mscore_push(MSCORE *handle, char c);

#ifdef __cplusplus
}
#endif

#endif

