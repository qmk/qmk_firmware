/* Copyright 2024 Finalkey
 * Copyright 2024 LiWenLiu <https://github.com/LiuLiuQMK>
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

extern void es_mcu_reset(void);
extern void bootloader_jump(void);
extern void mcu_reset(void);

extern void User_Systime_Init(void);
extern void User_Systime_Deinit(void);

extern void User_Sleep(void);
extern void User_Wakeup(void);

extern void Init_Gpio_Infomation(void);
extern void Board_Wakeup_Init(void);
extern void es_chibios_user_idle_loop_hook(void);