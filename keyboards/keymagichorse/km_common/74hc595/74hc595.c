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
#include <stdint.h>
#include <stdbool.h>
#include "config.h"
#include "74hc595.h"
#include "gpio.h"
#include "atomic_util.h"

void shift595_pin_init(void)
{   
    gpio_set_pin_output(DS_PIN_74HC595);
    gpio_set_pin_output(SHCP_PIN_74HC595);
    gpio_set_pin_output(STCP_PIN_74HC595);
}
void shift595_pin_sleep(void)
{
    gpio_write_pin_low(DS_PIN_74HC595);
    gpio_write_pin_low(SHCP_PIN_74HC595);
    gpio_write_pin_low(STCP_PIN_74HC595);
}
// 用于短延时
#define small_delay() __asm__ __volatile__("nop;nop;nop;\n\t" ::: "memory")
#define compiler_barrier() __asm__ __volatile__("" ::: "memory")

void shift595_write_all(shift595_data_t data) {
    ATOMIC_BLOCK_FORCEON {
        // 从高位芯片开始输出（最后一个芯片先移入）
        for (int8_t chip = I_595_NUM - 1; chip >= 0; chip--) {
            uint8_t byteOut = (uint8_t)(data >> (chip * 8));

            for (uint8_t bit = 0; bit < 8; bit++) {
                compiler_barrier();

                if (byteOut & 0x80) {
                    gpio_write_pin_high(DS_PIN_74HC595);
                } else {
                    gpio_write_pin_low(DS_PIN_74HC595);
                }

                byteOut <<= 1;

                compiler_barrier();
                gpio_write_pin_high(SHCP_PIN_74HC595);
                small_delay();
                gpio_write_pin_low(SHCP_PIN_74HC595);
            }
        }

        compiler_barrier();
        gpio_write_pin_high(STCP_PIN_74HC595);  // 锁存输出
        small_delay();
        gpio_write_pin_low(STCP_PIN_74HC595);
        compiler_barrier();
    }
}

void shift595_write_pin_ex(uint8_t pin_index, uint8_t level, uint8_t other_level) {
    shift595_data_t data;

    // 先设置所有 IO 为 other_level
    data = other_level ? ~((shift595_data_t)0) : 0;

    // 设置目标 pin 为指定电平
    if (level) {
        data |= ((shift595_data_t)1 << pin_index);
    } else {
        data &= ~((shift595_data_t)1 << pin_index);
    }

    // 输出到 74HC595
    shift595_write_all(data);
}

void shift595_write_all_high(void)
{
#if I_595_NUM == 1
    shift595_write_all(0xff);
#elif I_595_NUM == 2
    shift595_write_all(0xfff);
#else

#endif
}

void shift595_write_all_low(void)
{
    shift595_write_all(0);
}