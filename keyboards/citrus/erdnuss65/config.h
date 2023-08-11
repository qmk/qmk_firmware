/* Copyright 2023 Citrus Lab
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

// The pin connected to the data pin of the LEDs
#define RGBLIGHT_LAYERS//允许您定义可打开或关闭的照明层。非常适合显示当前键盘层或大写锁定状态。
#define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF//如果已定义，则即使 RGB 光源处于关闭状态，也会显示照明图层。

#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE//尝试使开关状态与键盘指示灯状态保持一致