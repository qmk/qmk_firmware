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

#if defined(EEPROM_CUSTOM)
extern void eeprom_driver_init(void);
extern void eeprom_write_block_user(const void *buf, void *addr, size_t len);
extern void eeprom_read_block_user(void *buf, const void *addr, size_t len);
#endif

extern bool Save_Flash;
extern bool Reset_Save_Flash;
extern uint16_t Save_Flash_3S_Count;
extern bool Led_Flash_Busy;

extern void Save_Flash_Set(void);