/*
Header file for process_record_user

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert
Copyright 2020 Ben Roesner (keycapsss.com)
Copyright 2022 Vii33 (https://github.com/vii33/mecha-keyboard-lily58l)

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


#ifndef PROCESS_RECORD_USER_H
#define PROCESS_RECORD_USER_H

#include QMK_KEYBOARD_H

bool process_record_user(uint16_t keycode, keyrecord_t *record);

extern bool lunaIsSneaking;
extern bool lunaIsJumping;
extern bool lunaIsBarking;
extern bool lunaShowedJump;

extern void add_keylog(uint16_t keycode);

#endif