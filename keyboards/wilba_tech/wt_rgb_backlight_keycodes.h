/* Copyright 2017 Jason Williams (Wilba)
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

enum wt_rgb_backlight_keycodes {
    BR_INC = QK_KB_0, // brightness increase
    BR_DEC,             // brightness decrease
    EF_INC,             // effect increase
    EF_DEC,             // effect decrease
    ES_INC,             // effect speed increase
    ES_DEC,             // effect speed decrease
    H1_INC,             // color 1 hue increase
    H1_DEC,             // color 1 hue decrease
    S1_INC,             // color 1 saturation increase
    S1_DEC,             // color 1 saturation decrease
    H2_INC,             // color 2 hue increase
    H2_DEC,             // color 2 hue decrease
    S2_INC,             // color 2 saturation increase
    S2_DEC              // color 2 saturation decrease
};
