/*
Copyright 2011 Jun Wako <wakojun@gmail.com>

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
*/

#ifndef COMMAND_H
#define COMMAND

/* TODO: Refactoring */
typedef enum { ONESHOT, CONSOLE, MOUSEKEY } command_state_t;
extern command_state_t command_state;

/* This allows to extend commands. Return false when command is not processed. */
bool command_extra(uint8_t code);
bool command_console_extra(uint8_t code);

#ifdef COMMAND_ENABLE
bool command_proc(uint8_t code);
#else
#define command_proc(code)      false
#endif

#endif
