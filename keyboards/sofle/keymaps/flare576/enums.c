/* Copyright 2021 Flare576 <flare576@gmail.com>
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
enum _layers {
    /* _M_XYZ = Mac Os, _W_XYZ = Win/Linux */
    _BASE,
    _MOUS,
    _SYMS,
    _META,
    _MDIA,
    _FF14,
    _ESDF,
};

enum custom_keycodes {
    _COMP1  = SAFE_RANGE,
    _COMP2,
    M_1,
    M_2,
    M_3,
    M_4,
    M_5,
    V_FS,
    T_FS,
    T_N,
    T_L,
    T_S,
    T_E,
    T_R,
    T_NAME,
};

enum custom_tapdance {
    TD_PLAY,
    TD_HOME,
};
