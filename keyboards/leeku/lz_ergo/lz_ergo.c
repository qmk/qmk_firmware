/* Copyright 2021 MajorKoos <https://github.com/majorkoos>
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

#include "lz_ergo.h"
#include <avr/io.h>
#include <avr/wdt.h>
#include "../i2c.h"
#include "../tinycmdapi.h"

typedef enum
{
    LED_EFFECT_FADING          = 0,
    LED_EFFECT_FADING_PUSH_ON  = 1,
    LED_EFFECT_PUSHED_LEVEL    = 2,
    LED_EFFECT_PUSH_ON         = 3,
    LED_EFFECT_PUSH_OFF        = 4,
    LED_EFFECT_ALWAYS          = 5,
    LED_EFFECT_BASECAPS        = 6,
    LED_EFFECT_OFF             = 7,
    LED_EFFECT_NONE
}LED_MODE;

void keyboard_pre_init_kb(void)
{
    /*
    PA  [0:7]   col[0:7]
    PB  [0:7]   col[8:15]
    PC  [0]     SCL
        [1]     SDA
        [2:6]   row[0:6]
    PD  [0]     USB D+- level shifter(high 3.3v, low 5v)
        [1]     PS2 pull-up for CLK
        [2]     CLK[D+]
        [3]     DATA[D-]
        [4:7]   col[16:19]

        signal direction : row -> col
    */
    PORTA   = 0xFF; // pull up
    DDRA    = 0x00; // input
    PORTB   = 0xFF; // pull up
    DDRB    = 0x00; // input
    PORTC   = 0xFF; // pull up
    DDRC	= 0x00; // input
    PORTD   = 0xF1; // col(pull up) D-(pull up) D+(pull up) PS2PU(low) USBSHIFT(high)
    DDRD    = 0x03; // input
    i2c_init(I2C_BITRATE_KHZ);
    #ifdef WATCHDOG_ENABLE
    wdt_enable(WDTO_2S);
    #endif
    uint8_t ret = 0;
    uint16_t retry = 0;
    while(ret == 0 && (retry++ < 20))
    {
        // Make sure the MCU's responding
        _delay_ms(50);
        ret = tinycmd_ver(true);
        _delay_ms(50);
        if(ret)
        {
            // Turn off the backlight and RGB.
            // This is because of several reports (myself included) of a corrupted bootloader due to voltage issues using the original firmware.
            uint8_t led_preset[3][5] = {{LED_EFFECT_OFF, LED_EFFECT_OFF, LED_EFFECT_OFF, LED_EFFECT_OFF, LED_EFFECT_OFF},
                                {LED_EFFECT_OFF, LED_EFFECT_OFF, LED_EFFECT_OFF, LED_EFFECT_OFF, LED_EFFECT_OFF},
                                {LED_EFFECT_OFF, LED_EFFECT_OFF, LED_EFFECT_OFF, LED_EFFECT_OFF, LED_EFFECT_OFF}};
            tinycmd_led_config_preset((uint8_t *)led_preset, true); // turn off the backlight
            tinycmd_rgb_all(0, 0, 0, 0, false); // turn off the RGB
            break;
        }
    }
}

void matrix_scan_kb(void)
{
    #ifdef WATCHDOG_ENABLE
    wdt_reset();
    #endif
    matrix_scan_user();
}
