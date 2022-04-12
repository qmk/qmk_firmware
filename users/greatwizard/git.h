/* Copyright 2020 Guillaume Gérard
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

#include QMK_KEYBOARD_H
#include "greatwizard.h"

bool process_record_git(uint16_t keycode, keyrecord_t *record);

#define GIT_BRC GIT_BRANCH
#define GIT_CKT GIT_CHECKOUT
#define GIT_CPK GIT_CHERRYPICK
#define GIT_CMT GIT_COMMIT
#define GIT_DIF GIT_DIFF
#define GIT_FTC GIT_FETCH
#define GIT_GRP GIT_GREP
#define GIT_INI GIT_INIT
#define GIT_MRG GIT_MERGE
#define GIT_PUS GIT_PUSH
#define GIT_PUL GIT_PULL
#define GIT_RBS GIT_REBASE
#define GIT_RMT GIT_REMOTE
#define GIT_RST GIT_RESET
#define GIT_SHW GIT_SHOW
#define GIT_STS GIT_STASH
#define GIT_STT GIT_STATUS
