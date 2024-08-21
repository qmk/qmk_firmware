/* Copyright 2022~2024 @ lokher (https://www.keychron.com)
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

#include "config.h"
#include "wireless.h"

#define P24G_HOST_INDEX 24
#define USB_HOST_INDEX 34

/* Indication of pairing */
#ifndef INDICATOR_CONFIG_PARING
#    define INDICATOR_CONFIG_PARING {INDICATOR_BLINK, 1000, 1000, 0, true, 0};
#endif

/* Indication on Connected */
#ifndef INDICATOR_CONFIG_CONNECTD
#    define INDICATOR_CONFIG_CONNECTD {INDICATOR_ON_OFF, 2000, 250, 2000, true, 0};
#endif

/* Reconnecting indication */
#ifndef INDICATOR_CONFIG_RECONNECTING
#    define INDICATOR_CONFIG_RECONNECTING {INDICATOR_BLINK, 100, 100, 600, true, 0};
#endif

/* Disconnected indication */
#ifndef INDICATOR_CONFIG_DISCONNECTED
#    define INDICATOR_CONFIG_DISCONNECTED {INDICATOR_NONE, 100, 100, 600, false, 0};
#endif

/* Uint: Second */
#ifndef DISCONNECTED_BACKLIGHT_DISABLE_TIMEOUT
#    define DISCONNECTED_BACKLIGHT_DISABLE_TIMEOUT 40
#endif

/* Uint: Second, the timer restarts on key activities. */
#ifndef CONNECTED_BACKLIGHT_DISABLE_TIMEOUT
#    define CONNECTED_BACKLIGHT_DISABLE_TIMEOUT 600
#endif

/* Uint: ms */
#ifndef LOW_BAT_LED_BLINK_PERIOD
#    define LOW_BAT_LED_BLINK_PERIOD 1000
#endif

#ifndef LOW_BAT_LED_BLINK_TIMES
#    define LOW_BAT_LED_BLINK_TIMES 5
#endif

#ifndef LOW_BAT_LED_TRIG_INTERVAL
#    define LOW_BAT_LED_TRIG_INTERVAL 30000
#endif

#if ((defined(LED_MATRIX_ENABLE) || defined(RGB_MATRIX_ENABLE)) && defined(LOW_BAT_IND_INDEX))
#    define SPACE_KEY_LOW_BAT_IND
#endif

#if BT_HOST_MAX_COUNT > 6
#    pragma error("HOST_COUNT max value is 6")
#endif

typedef enum {
    INDICATOR_NONE,
    INDICATOR_OFF,
    INDICATOR_ON,
    INDICATOR_ON_OFF,
    INDICATOR_BLINK,
    INDICATOR_LAST,
} indicator_type_t;

typedef struct PACKED {
    indicator_type_t type;
    uint32_t         on_time;
    uint32_t         off_time;
    uint32_t         duration;
    bool             highlight;
    uint8_t          value;
    uint32_t         elapsed;
} indicator_config_t;

typedef struct PACKED {
    uint8_t value;
    bool    saved;
} backlight_state_t;

void indicator_init(void);
void indicator_set(wt_state_t state, uint8_t host_index);
void indicator_set_backlit_timeout(uint32_t time);
void indicator_backlight_timer_reset(bool enable);
bool indicator_hook_key(uint16_t keycode);
void indicator_enable(void);
void indicator_disable(void);
void indicator_stop(void);
void indicator_eeconfig_reload(void);
bool indicator_is_enabled(void);
bool indicator_is_running(void);
void indicator_battery_low_enable(bool enable);

void indicator_task(void);
