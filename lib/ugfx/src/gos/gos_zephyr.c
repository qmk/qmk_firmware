/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#include "../../gfx.h"

#if GFX_USE_OS_ZEPHYR

gTicks gfxSystemTicks(void)
{
	s32_t ms = k_uptime_get_32();
	return CONFIG_SYS_CLOCK_TICKS_PER_SEC*ms/1000;
}

#endif // GFX_USE_OS_ZEPHYR
