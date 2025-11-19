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

#define USER_BATT_HIGH_POWER        (2555)
#define USER_BATT_LOW_POWER         (2065)
#define USER_BATT_STDOWN_POWER      (1865)

#define USER_BATT_POWER_SCAN_COUNT  (10)
#define USER_BATT_SCAN_COUNT        (10)

extern uint16_t User_Adc_Batt[USER_BATT_SCAN_COUNT];
extern uint16_t User_Scan_Batt[USER_BATT_SCAN_COUNT];
extern uint8_t User_Adc_Batt_Count;
extern uint8_t User_Batt_BaiFen;
extern uint8_t User_Batt_Old_BaiFen;
extern uint8_t User_Batt_10ms_Count;
extern uint16_t User_Batt_Time_15S_Count;
extern bool User_Batt_Power_Up;
extern bool User_Batt_Send_Spi;
extern uint16_t User_Batt_Power_Up_Delay_100ms_Count;
extern bool User_Batt_Power_Up_Delay;

extern bool User_Power_Low;
extern uint8_t User_Power_Low_Count;
extern uint8_t es_stdby_pin_state;

extern const md_adc_initial adc_initStruct;

extern void User_Adc_Init(void);
extern void User_Adc_Deinit(void);

extern void U16_Buff_Clear(uint16_t *Buff, uint8_t Len);
extern void Init_Batt_Infomation(void);
extern void User_Adc_Batt_Power_Up_Init(void);
extern void User_Adc_Batt_Number(void);