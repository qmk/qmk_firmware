/*
Copyright 2016 Ralf Schmitt <ralf@bunkertor.net>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef LEDL3_H
#define LEDL3_H

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

enum backlight_level {
    BACKLIGHT_PCB      = 0b0000001,
    BACKLIGHT_SWITCH   = 0b0000010
};

void led_off(void);
void led_on(void);
void rgb_on(void);
void rgb_off(void);
void led_speed(void);
void led_rgb_preset(void);
void led_change_mode(void);
void rgb_change_mode(void);

#endif // LEDL3_H
