/* Copyright 2021 HellSingCoder
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

#define CB(name, action, ...) C_##name,
enum user_combos {
#include "combos.def"
    COMBO_LENGTH
};
#undef CB
uint16_t COMBO_LEN = COMBO_LENGTH;

#define CB(name, action, ...) const uint16_t PROGMEM name##_combo[] = {__VA_ARGS__, COMBO_END};
#include "combos.def"
#undef CB

combo_t key_combos[COMBO_LENGTH] = {
#define CB(name, action, ...) COMBO(name##_combo, action),
#include "combos.def"
#undef CB
};
