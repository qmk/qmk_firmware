/* Copyright 2023 @ Mike Killewald (https://github.com/mkillewald)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "mkillewald.h"

enum layers{
    MAC_BASE,
    MAC_FN,
    WIN_BASE,
    WIN_FN
};

#define MAC_FN1     MAC_FN
#define WIN_FN1     WIN_FN
#define MAC_WIN_FN2 255  // not used, keymap does not have fn2 key

/* Factory test keys */
#define FN_KEY1             MO(MAC_FN)  // Fn Mac Base
#define FN_KEY2             MO(WIN_FN)  // Fn Win Base

#define RESET_KEY1          KC_J
#define RESET_KEY2          KC_Z
#define RESET_KEY2_ALT      KC_LTTOG

#define BL_TEST_KEY1        KC_RIGHT
#define BL_TEST_KEY2        KC_HOME