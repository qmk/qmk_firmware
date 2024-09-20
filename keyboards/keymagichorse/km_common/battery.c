/* Copyright 2024 keymagichorse
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

#include "battery.h"
#include "gpio.h"
#include "analog.h"

#include "km_printf.h"

#include "bhq.h"

uint32_t battery_timer_buffer = 0;
void battery_init(void)
{
    battery_timer_buffer = 0;
}


void battery_stop(void)
{
    // adcStop(&ADCD1);
    // battery_timer_buffer = 0;
}

uint16_t battery_adc_read(void)
{
    analogReadPin(BATTER_ADC_PIN);  // Discard the first value
    return analogReadPin(BATTER_ADC_PIN);
}

// 定义数据点（电压为毫伏）
int voltages[] = {
    4150, 4140, 4120, 4100, 4080, 4050, 4030, 3970, 3930, 3900,
    3870, 3840, 3810, 3790, 3770, 3760, 3740, 3730, 3720, 3710,
    3690, 3660, 3650, 3640, 3630, 3610, 3590, 3500
};

uint8_t capacities[] = {
    100, 97, 95, 92, 90, 87, 85, 80, 75, 70,
    65, 60, 55, 50, 45, 42, 40, 35, 30, 25,
    20, 15, 12, 10, 8, 5, 3, 0
};

#define NUM_POINTS (sizeof(voltages) / sizeof(voltages[0]))

// 分段线性插值函数
uint8_t battery_percent_read(uint16_t voltage_mV) {
    for (int i = 0; i < NUM_POINTS - 1; i++) {
        if (voltage_mV >= voltages[i + 1] && voltage_mV <= voltages[i]) {
            // 如果电压正好等于某个电压点，直接返回对应的容量
            if (voltage_mV == voltages[i]) {
                return capacities[i];
            }
            // 对于在两个点之间的电压，返回靠近的容量
            int voltage_diff = voltages[i] - voltages[i + 1];
            int capacity_diff = capacities[i] - capacities[i + 1];
            int voltage_offset = voltage_mV - voltages[i + 1];
            return capacities[i + 1] + (capacity_diff * voltage_offset) / voltage_diff;
        }
    }

    // 超出范围时的处理
    if (voltage_mV > voltages[0]) {
        return 100; // 超过最大电压，返回100%
    } else if (voltage_mV < voltages[NUM_POINTS - 1]) {
        return 0; // 低于最小电压，返回0%
    }

    return 0;
}
void battery_task(void)
{

    // if(battery_timer_buffer == 0)
    // {
    //     battery_timer_buffer = sync_timer_read32();
    // }

    // if (sync_timer_elapsed32(battery_timer_buffer) > VOLTAGE_MEASURE_INTERVAL) 
    // {
    //     battery_timer_buffer = 0;
    //     uint16_t adc = battery_adc_read();
    //     adc = battery_adc_read();
    //     uint16_t voltage_mV_Fenya = (adc * 3300) / 1023;
    //     uint16_t voltage_mV_actual = voltage_mV_Fenya  * (1 + (R_UPPER / R_LOWER));
    //     uint8_t percent = battery_percent_read(voltage_mV_actual);
    //     km_printf("1111111 newnewnew !!!666hello rtt log adc:%d   fymv:%d  sjmv:%d  bfb:%d\r\n",adc,voltage_mV_Fenya,voltage_mV_actual,percent);

    //     bhq_update_battery_percent(percent);
    // }
 
}