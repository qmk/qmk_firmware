/*
Copyright 2013 Mathias Andersson <wraul@dbox.se>

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

#include "backlight.h"
#include "eeconfig.h"
#include "debug.h"

backlight_config_t backlight_config;

void backlight_init(void)
{
    /* check signature */
    if (!eeconfig_is_enabled()) {
        eeconfig_init();
    }
    backlight_config.raw = eeconfig_read_backlight();
    backlight_set(backlight_config.enable ? backlight_config.level : 0);
}

void backlight_increase(void)
{
    if(backlight_config.level < BACKLIGHT_LEVELS)
    {
        backlight_config.level++;
        backlight_config.enable = 1;
        eeconfig_write_backlight(backlight_config.raw);
    }
    dprintf("backlight increase: %u\n", backlight_config.level);
    backlight_set(backlight_config.level);
}

void backlight_decrease(void)
{
    if(backlight_config.level > 0)
    {
        backlight_config.level--;
        backlight_config.enable = !!backlight_config.level;
        eeconfig_write_backlight(backlight_config.raw);
    }
    dprintf("backlight decrease: %u\n", backlight_config.level);
    backlight_set(backlight_config.level);
}

void backlight_toggle(void)
{
    backlight_config.enable ^= 1;
    eeconfig_write_backlight(backlight_config.raw);
    dprintf("backlight toggle: %u\n", backlight_config.enable);
    backlight_set(backlight_config.enable ? backlight_config.level : 0);
}

void backlight_step(void)
{
    backlight_config.level++;
    if(backlight_config.level > BACKLIGHT_LEVELS)
    {
        backlight_config.level = 0;
    }
    backlight_config.enable = !!backlight_config.level;
    eeconfig_write_backlight(backlight_config.raw);
    dprintf("backlight step: %u\n", backlight_config.level);
    backlight_set(backlight_config.level);
}

void backlight_level(uint8_t level)
{
    backlight_config.level ^= level;
    backlight_config.enable = !!backlight_config.level;
    eeconfig_write_backlight(backlight_config.raw);
    backlight_set(backlight_config.level);
}
