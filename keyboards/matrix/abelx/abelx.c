/**
 * abelx.c
 *
 * Copyright 2020 astro <yuleiz@gmail.com>
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

#include "abelx.h"
#include "tca6424.h"
#include "aw9523b.h"

void set_pin(uint16_t pin)
{
    uint8_t data = tca6424_read_port(GET_PORT(pin));
    data |= ( 1 << GET_PIN(pin));
    tca6424_write_port(GET_PORT(pin), data);
}

void clear_pin(uint16_t pin)
{
    uint8_t data = tca6424_read_port(GET_PORT(pin));
    data &= ~( 1 << GET_PIN(pin));
    tca6424_write_port(GET_PORT(pin), data);
}

uint8_t read_pin(uint16_t pin)
{
    uint8_t data = tca6424_read_port(GET_PORT(pin));
    return (data & (1<<GET_PIN(pin))) ? 1 : 0;
}

#ifdef RGBLIGHT_ENABLE
#include "rgblight.h"
#include "ws2812.h"
#include "i2c_master.h"

const aw9523b_led g_aw9523b_leds[AW9523B_RGB_NUM] = {
    {AW9523B_P12_PWM, AW9523B_P11_PWM, AW9523B_P10_PWM},
    {AW9523B_P01_PWM, AW9523B_P00_PWM, AW9523B_P13_PWM},
    {AW9523B_P04_PWM, AW9523B_P03_PWM, AW9523B_P02_PWM},
    {AW9523B_P07_PWM, AW9523B_P06_PWM, AW9523B_P05_PWM},
};

void init_custom(void) {
    aw9523b_init(AW9523B_ADDR);
    ws2812_init();
}

void set_color_custom(int index, uint8_t red, uint8_t green, uint8_t blue) {
    if (index < AW9523B_RGB_NUM) {
        aw9523b_set_color(index, red, green, blue);
    } else {
        ws2812_set_color(index - AW9523B_RGB_NUM, red, green, blue);
    }
}

void set_color_all_custom(uint8_t red, uint8_t green, uint8_t blue) {
    for (int i = 0; i < RGBLIGHT_LED_COUNT; i++) {
        set_color_custom(i, red, green, blue);
    }
}

void flush_custom(void) {
    aw9523b_update_pwm_buffers(AW9523B_ADDR);
    ws2812_flush();
}

const rgblight_driver_t rgblight_driver = {
    .init          = init_custom,
    .set_color     = set_color_custom,
    .set_color_all = set_color_all_custom,
    .flush         = flush_custom,
};

#endif

static uint16_t caps_lock_pin = DEF_PIN(TCA6424_PORT2, 3);
static uint16_t scroll_lock_pin = DEF_PIN(TCA6424_PORT0, 0);

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
        led_state.caps_lock ? set_pin(caps_lock_pin) : clear_pin(caps_lock_pin);
        led_state.scroll_lock ? set_pin(scroll_lock_pin) : clear_pin(scroll_lock_pin);
    }
    return res;
}

#define REBOOT_MAGIC 0x41544B42

void bootloader_jump(void) {
    *(uint32_t *)(&(RTCD1.rtc->BKP0R)) = REBOOT_MAGIC;
    NVIC_SystemReset();
}
