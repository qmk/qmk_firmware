/* Copyright 2021 Giorgi Chavchanidze
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

#define UNICODE_SELECTED_MODES UNICODE_MODE_WINCOMPOSE

/* Selected Unicode input method relies on WinCompose
 * https://docs.qmk.fm/#/feature_unicode?id=input-modes
 * Linux users are better served by xkb configuration
 * https://gitlab.com/lykt/geotype/-/blob/master/xkb/dsae
 */
