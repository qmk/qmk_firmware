/*
Copyright 2019 Batuhan Başerdem <baserdem.batuhan@gmail.com> @bbaserdem
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
#pragma once
#include "bbaserdem.h"
// Contain the main oled writer here 
void oled_task_user(void);
bool oled_task_keymap(void);
// This is only neccessary for oled; hence here
#ifdef ENCODER_ENABLE
void encoder_state_string5(uint8_t index, uint8_t layer, char* buffer);
void encoder_state_string8(uint8_t index, uint8_t layer, char* buffer);
#endif
