/* Copyright 2020 Purdea Andrei
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

struct key_def
{
    unsigned int row;
    unsigned int col;
    double x;
    double y;
    double w;
    double h;
};

struct lay_def
{
    const char *lay_name;
    int n_keys;
    const struct key_def *keys;
};

struct kbd_def
{
    const char *kbd_name;
    int n_layouts;
    const struct lay_def *layouts;
    unsigned int cols;
    unsigned int rows;
    unsigned int extra_direct_rows;
};

extern struct kbd_def keyboards[];
extern int n_keyboards;
