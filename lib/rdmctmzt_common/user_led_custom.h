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
extern uint8_t Led_Colour_Tab[9][3];
extern uint8_t Led_Wave_Pwm_Tab[128];

extern void rgb_matrix_driver_init(void);
extern void User_Pwm_Deinit(void);
extern void rgb_matrix_driver_flush_pwm_dma_start(void);
extern void rgb_matrix_driver_flush(void);
extern void rgb_matrix_driver_set_color(int index, uint8_t r, uint8_t g, uint8_t b);
extern void rgb_matrix_driver_set_color_all(uint8_t r, uint8_t g, uint8_t b);
extern const rgb_matrix_driver_t rgb_matrix_driver;
