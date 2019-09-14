/**
 * @file      msconf.h
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

#ifndef MSCONF_H
#define MSCONF_H

#define MSCONF_MAX_INPUT_LENGTH     (128)
#define MSCONF_MAX_INPUT_ARGS       ((MSCONF_MAX_INPUT_LENGTH / 2) + 1)

#if !defined(MSCONF_KEYMAP_SWAP_BS_DEL)
#define MSCONF_KEYMAP_SWAP_BS_DEL   (0)
#endif

#define MSCONF_KEYMAP_USE_CTRL      (1)
#define MSCONF_KEYMAP_USE_FUNCTION  (1)
#define MSCONF_KEYMAP_USE_ARROW     (1)
#define MSCONF_KEYMAP_USE_HOME_END  (1)
#define MSCONF_KEYMAP_USE_PAGE      (1)

#endif

