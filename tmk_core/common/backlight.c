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

/** \brief Backlight initialization
 *
 * FIXME: needs doc
 */
void backlight_init(void)
{
    /* check signature */
    if (!eeconfig_is_enabled()) {
        eeconfig_init();
    }
    backlight_config.raw = eeconfig_read_backlight();
    if (backlight_config.level > BACKLIGHT_LEVELS) {
       backlight_config.level = BACKLIGHT_LEVELS;
    }
    backlight_set(backlight_config.enable ? backlight_config.level : 0);
}

/** \brief Backlight increase
 *
 * FIXME: needs doc
 */
void backlight_increase(void)
{
    if(backlight_config.level < BACKLIGHT_LEVELS)
    {
        backlight_config.level++;
    }
    backlight_config.enable = 1;
    eeconfig_update_backlight(backlight_config.raw);
    dprintf("backlight increase: %u\n", backlight_config.level);
    backlight_set(backlight_config.level);
}

/** \brief Backlight decrease
 *
 * FIXME: needs doc
 */
void backlight_decrease(void)
{
    if(backlight_config.level > 0)
    {
        backlight_config.level--;
        backlight_config.enable = !!backlight_config.level;
        eeconfig_update_backlight(backlight_config.raw);
    }
    dprintf("backlight decrease: %u\n", backlight_config.level);
    backlight_set(backlight_config.level);
}

/** \brief Backlight toggle
 *
 * FIXME: needs doc
 */
void backlight_toggle(void)
{
	bool enabled = backlight_config.enable;
	dprintf("backlight toggle: %u\n", enabled);
	if (enabled) 
		backlight_disable();
	else
		backlight_enable();
}

/** \brief Enable backlight
 *
 * FIXME: needs doc
 */
void backlight_enable(void)
{
	if (backlight_config.enable) return; // do nothing if backlight is already on

	backlight_config.enable = true;
	if (backlight_config.raw == 1) // enabled but level == 0
		backlight_config.level = 1;
	eeconfig_update_backlight(backlight_config.raw);
	dprintf("backlight enable\n");
	backlight_set(backlight_config.level);
}

/** /brief Disable backlight
 *
 * FIXME: needs doc
 */
void backlight_disable(void)
{
	if (!backlight_config.enable) return; // do nothing if backlight is already off

	backlight_config.enable = false;
	eeconfig_update_backlight(backlight_config.raw);
	dprintf("backlight disable\n");
	backlight_set(0);
}

/** /brief Get the backlight status
 *
 * FIXME: needs doc
 */
bool is_backlight_enabled(void)
{
	return backlight_config.enable;
}

/** \brief Backlight step through levels
 *
 * FIXME: needs doc
 */
void backlight_step(void)
{
    backlight_config.level++;
    if(backlight_config.level > BACKLIGHT_LEVELS)
    {
        backlight_config.level = 0;
    }
    backlight_config.enable = !!backlight_config.level;
    eeconfig_update_backlight(backlight_config.raw);
    dprintf("backlight step: %u\n", backlight_config.level);
    backlight_set(backlight_config.level);
}

/** \brief Backlight set level
 *
 * FIXME: needs doc
 */
void backlight_level(uint8_t level)
{
    if (level > BACKLIGHT_LEVELS)
        level = BACKLIGHT_LEVELS;
    backlight_config.level = level;
    backlight_config.enable = !!backlight_config.level;
    eeconfig_update_backlight(backlight_config.raw);
    backlight_set(backlight_config.level);
}

/** \brief Get backlight level
 *
 * FIXME: needs doc
 */
uint8_t get_backlight_level(void)
{
    return backlight_config.level;
}
