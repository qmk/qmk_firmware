/* Copyright 2021 Joshua T.
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

// NOTE: In some implementations of the "secrets" functionality, the
// secrets.h file is the file that actually contains secret text.
//
// This is not the case in my implementation. That file is called
// "secret_definitions.h", and it's in a local .gitignore file so it
// does not get committed.
//
// The inclusion of this file is not an error, and there is no sensitive
// text here.

bool process_record_secrets(uint16_t keycode, const keyrecord_t *record);
