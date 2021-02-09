/* Copyright 2015 LeeKu <https://github.com/leeku11>

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

#ifndef TINYCMD_H
#define TINYCMD_H

#define TINY_CMD_CMD_MASK               0x3F
#define TINY_CMD_RSP_MASK               0x80
#define TINY_CMD_KEY_MASK               0x40

// System Command
#define TINY_CMD_CONFIG_F               0
#define TINY_CMD_VER_F                  1
#define TINY_CMD_RESET_F                2
#define TINY_CMD_THREE_LOCK_F           3
#define TINY_CMD_DIRTY_F                4
#define TINY_CMD_SLEEP_F                5

// RGB Command
#define TINY_CMD_RGB_ALL_F              20
#define TINY_CMD_RGB_POS_F              21
#define TINY_CMD_RGB_RANGE_F            22
#define TINY_CMD_RGB_BUFFER_F           23
#define TINY_CMD_RGB_SET_EFFECT_F       24
#define TINY_CMD_RGB_SET_PRESET_F       25
#define TINY_CMD_RGB_EFFECT_SPEED_F     26
#define TINY_CMD_RGB_EFFECT_ON_F        27

// LED Command
#define TINY_CMD_LED_LEVEL_F            40
#define TINY_CMD_LED_SET_EFFECT_F       41
#define TINY_CMD_LED_SET_PRESET_F       42
#define TINY_CMD_LED_CONFIG_PRESET_F    43
#define TINY_CMD_LED_EFFECT_ON_F        44

#define TINY_CMD_MAX                    127



#endif // TINYCMD_H

