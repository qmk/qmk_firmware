/* Copyright 2020 Christopher Ko <chriskopher@gmail.com>
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

enum keyboard_layer {
    // Base layers
    _CKO,
    _QWERTY,
    // Intermediate layers
    _SUPERDUPER,
    _DEV,
    // Adjust layer at the end
    _ADJUST
};

enum tap_dance_key_event {
    // Extended space cadet shift tap dance
    ESPC_L,
    ESPC_R,
    // Semicolon-Colon tap dance
    SCLN_CLN
};
