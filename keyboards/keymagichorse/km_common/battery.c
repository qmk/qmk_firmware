/* Copyright 2025 keymagichorse
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
#include "analog.h"
#include "bhq.h"
#include "wireless.h"
#include "transport.h"
#include "timer.h"

uint32_t battery_timer = 0;
// 电池电压转百分比
uint8_t calculate_battery_percentage(uint16_t current_mv) {
    if (current_mv >= BATTER_MAX_MV) {
        return 100;
    } else if (current_mv <= BATTER_MIN_MV) {
        return 0;
    } else {
        uint16_t percentage = ((current_mv - BATTER_MIN_MV) * 100) / (BATTER_MAX_MV - BATTER_MIN_MV);
        // 如果百分比超过100，确保其被限制在100以内
        if (percentage > 100) {
            percentage = 100;
        }
        return (uint8_t)percentage;
    }
}

// 读取并更新数据
void battery_read_and_update_data(void)
{
    uint16_t adc = analogReadPin(BATTER_ADC_PIN);
    adc = analogReadPin(BATTER_ADC_PIN);

    uint16_t voltage_mV_Fenya = (adc * 3300) / 1023;
    uint16_t voltage_mV_actual = voltage_mV_Fenya  * (1 + (BAT_R_UPPER / BAT_R_LOWER));

    // voltage_mV_actual = voltage_mV_actual;  // 
    // km_printf("adc:%d   fymv:%d  sjmv:%d  bfb:%d  \r\n",
    // adc,voltage_mV_Fenya,voltage_mV_actual,calculate_battery_percentage(voltage_mV_actual));
    // km_printf("adcState:%d\r\n",ADCD1.state);
    // 上报电池百分比到模块中
    bhq_update_battery_percent(calculate_battery_percentage(voltage_mV_actual),voltage_mV_actual);
    battery_timer = 0;
}
void battery_percent_read_task(void)
{ 
    if(battery_timer == 0)
    {
        battery_timer = timer_read32();
    }

    if (timer_elapsed32(battery_timer) > 60000 && IS_WIRELESS_TRANSPORT(transport_get()) == true && wireless_get() == WT_STATE_CONNECTED)     // 1分钟
    {
        battery_timer = timer_read32();
        battery_read_and_update_data();
    }
}
void battery_reset_timer(void)
{
    battery_timer = 0;
}



