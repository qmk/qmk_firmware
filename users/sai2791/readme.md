Copyright 2019 Steven Inglis sai2791@googlemail.com @sai2791

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

# Overview

This is my personal userspace.

# Shared Keys
- System wide Mac lock screen Keys (KC_LOCKSCR)

# Shared Keyboards
- ergodox_ez  Doesnt use the sai2791.c
- radox_w     Doesnt use the sai2791.c
- ymdk_np21   Doesnt use the sai2791.c

# Notes to myself
30/1/2019
- New kemaps added desk_l and desk_r, should add these to my keymaps
- maybe move the window moving, and screen moving stuff to a layer

28/1/2019
- If i add the compile time flags flto gives an error about the redefinition
of fn_action
quantum/keymap_common.c:190:24: error: type of 'fn_actions' does not match original declaration [-Werror]
|  const uint16_t PROGMEM fn_actions[] = {
|                         ^
| keyboards/ergodox_ez/keymaps/sai2791/keymap.c:226:24: note: previously declared here
|  const uint16_t PROGMEM fn_actions[] = {

  Fixed this by commenting it out in the keymaps.c in the keyboard/keymaps directory, it seems to compile ok,
  needs testing.
