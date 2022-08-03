/* Copyright 2021 @ lokher (https://www.keychron.com)
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

#include "quantum.h"
#include "indicator.h"
#include "transport.h"
#include "battery.h"
#include "eeconfig.h"
#include "bluetooth_config.h"
#include "config.h"
#if defined(LED_MATRIX_ENABLE) || defined(RGB_MATRIX_ENABLE)
#    ifdef LED_MATRIX_ENABLE
#        include "led_matrix.h"
#    endif
#    ifdef RGB_MATRIX_ENABLE
#        include "rgb_matrix.h"
#    endif
#    include "i2c_master.h"
#    include "bat_level_animation.h"
#endif

#ifdef LED_MATRIX_ENABLE
#    define DECIDE_TIME(t, duration) (duration == 0 ? LED_DISABLE_TIME_INFINITE : ((t > duration) ? t : duration))
#endif
#ifdef RGB_MATRIX_ENABLE
#    define DECIDE_TIME(t, duration) (duration == 0 ? RGB_DISABLE_TIME_INFINITE : ((t > duration) ? t : duration))
#endif

#define LED_ON 0x80

#define INDICATOR_SET(s)                               \
    indicator_config.type      = s##_config.type;      \
    indicator_config.on_time   = s##_config.on_time;   \
    indicator_config.off_time  = s##_config.off_time;  \
    indicator_config.duration  = s##_config.duration;  \
    indicator_config.highlight = s##_config.highlight; \
    indicator_config.elapsed   = 0;

indicator_config_t pairing_config      = INDICATOR_CONFIG_PARING;
indicator_config_t connected_config    = INDICATOR_CONFIG_CONNECTD;
indicator_config_t reconnecting_config = INDICATOR_CONFIG_RECONNECTING;
indicator_config_t disconnected_config = INDICATOR_CONFIG_DISCONNECTED;

enum {
    BACKLIGHT_OFF            = 0x00,
    BACKLIGHT_ON_CONNECTED   = 0x01,
    BACKLIGHT_ON_UNCONNECTED = 0x02,
};

indicator_config_t indicator_config;

static bluetooth_state_t indicator_state;
static uint16_t          next_period;
static indicator_type_t  type;
static uint32_t          indicator_timer_buffer;
static uint32_t          battery_low_indicator = 0;

#if defined(LED_MATRIX_ENABLE) || defined(RGB_MATRIX_ENABLE)
backlight_state_t original_backlight_state;

static uint8_t host_led_matrix_list[HOST_DEVICES_COUNT] = HOST_LED_MATRIX_LIST;
#endif

#ifdef HOST_LED_PIN_LIST
static pin_t host_led_pin_list[HOST_DEVICES_COUNT] = HOST_LED_PIN_LIST;
#endif

void indicator_init(void) {
#ifdef HOST_LED_PIN_LIST
    for (uint8_t i = 0; i < HOST_DEVICES_COUNT; i++) {
        setPinOutput(host_led_pin_list[i]);
        writePin(host_led_pin_list[i], !HOST_LED_PIN_ON_STATE);
    }
#endif

#ifdef BAT_LOW_LED_PIN
    setPinOutput(BAT_LOW_LED_PIN);
    writePin(BAT_LOW_LED_PIN, !BAT_LOW_LED_PIN_ON_STATE);
#endif
}

#if defined(LED_MATRIX_ENABLE) || defined(RGB_MATRIX_ENABLE)
void indicator_enable(void) {
#    ifdef LED_MATRIX_ENABLE
    if (!led_matrix_is_enabled()) {
        led_matrix_enable_noeeprom();
    }
#    endif
#    ifdef RGB_MATRIX_ENABLE
    if (!rgb_matrix_is_enabled()) {
        rgb_matrix_enable_noeeprom();
    }
#    endif
}

void indicator_disable(void) {
#    ifdef LED_MATRIX_ENABLE
    led_matrix_disable_noeeprom();
#    endif
#    ifdef RGB_MATRIX_ENABLE
    rgb_matrix_disable_noeeprom();
#    endif
}

void indicator_set_backlit_timeout(uint32_t time) {
#    ifdef LED_MATRIX_ENABLE
    led_matrix_disable_timeout_set(time);
#    endif
#    ifdef RGB_MATRIX_ENABLE
    rgb_matrix_disable_timeout_set(time);
#    endif
}

static inline void indicator_reset_backlit_time(void) {
#    ifdef LED_MATRIX_ENABLE
    led_matrix_disable_time_reset();
#    endif
#    ifdef RGB_MATRIX_ENABLE
    rgb_matrix_disable_time_reset();
#    endif
}

bool indicator_is_enabled(void) {
#    ifdef LED_MATRIX_ENABLE
    return led_matrix_is_enabled();
#    endif
#    ifdef RGB_MATRIX_ENABLE
    return rgb_matrix_is_enabled();
#    endif
}

bool indicator_is_backlit_enabled_eeprom(void) {
#    ifdef LED_MATRIX_ENABLE
    return led_matrix_is_enabled_eeprom();
#    endif
#    ifdef RGB_MATRIX_ENABLE
    return rgb_matrix_is_enabled_eeprom();
#    endif
    return false;
}

#endif

bool indicator_is_running(void) { return !!indicator_config.value; }

static void indicator_timer_cb(void *arg) {
    if (*(indicator_type_t *)arg != INDICATOR_LAST) type = *(indicator_type_t *)arg;

    bool time_up = false;
    switch (type) {
        case INDICATOR_NONE:
            break;
        case INDICATOR_OFF:
            next_period = 0;
            time_up     = true;
            break;

        case INDICATOR_ON:
            if (indicator_config.value) {
                if (indicator_config.elapsed == 0) {
                    indicator_config.value |= LED_ON;

                    if (indicator_config.duration) {
                        indicator_config.elapsed += indicator_config.duration;
                    }
                } else
                    time_up = true;
            }
            break;

        case INDICATOR_ON_OFF:
            if (indicator_config.value) {
                if (indicator_config.elapsed == 0) {
                    indicator_config.value |= LED_ON;
                    next_period = indicator_config.on_time;
                } else {
                    indicator_config.value = indicator_config.value & 0x0F;
                    next_period            = indicator_config.duration - indicator_config.on_time;
                }

                if ((indicator_config.duration == 0 || indicator_config.elapsed <= indicator_config.duration) && next_period != 0) {
                    indicator_config.elapsed += next_period;
                } else {
                    time_up = true;
                }
            }
            break;

        case INDICATOR_BLINK:
            if (indicator_config.value) {
                if (indicator_config.value & LED_ON) {
                    indicator_config.value = indicator_config.value & 0x0F;
                    next_period            = indicator_config.off_time;
                } else {
                    indicator_config.value |= LED_ON;
                    next_period = indicator_config.on_time;
                }

                if ((indicator_config.duration == 0 || indicator_config.elapsed <= indicator_config.duration) && next_period != 0) {
                    indicator_config.elapsed += next_period;
                } else
                    time_up = true;
            }
            break;
        default:
            time_up = true;

            next_period = 0;
            break;
    }

    if (time_up) {
        /* Set indicator to off on timeup, avoid keeping light up until next update in raindrop effect */
        indicator_config.value = indicator_config.value & 0x0F;
#ifdef LED_MATRIX_ENABLE
        led_matrix_indicators_kb();
#endif
#ifdef RGB_MATRIX_ENABLE
        rgb_matrix_indicators_kb();
#endif
        indicator_config.value = 0;
    }

#ifdef HOST_LED_PIN_LIST
    if (indicator_config.value && (indicator_config.value & 0x80)) {
        writePin(host_led_pin_list[indicator_config.value & 0x0F], HOST_LED_PIN_ON_STATE);
    } else {
        writePin(host_led_pin_list[indicator_config.value & 0x0F], !HOST_LED_PIN_ON_STATE);
    }
#endif

    if (indicator_config.value == 0 && !indicator_is_backlit_enabled_eeprom()) {
        indicator_disable();
    }
}

void indicator_set(bluetooth_state_t state, uint8_t host_index) {
    if (get_transport() != TRANSPORT_BLUETOOTH) return;
    dprintf("indicator set: %d, %d\n", state, host_index);

    static uint8_t current_state = 0;
    static uint8_t current_host  = 0;

    bool host_index_changed = false;
    if (current_host != host_index && state != BLUETOOTH_DISCONNECTED) {
        host_index_changed = true;
        current_host       = host_index;
    }

    if (current_state != state || host_index_changed) {
        current_state = state;
    } else {
        return;
    }

    indicator_timer_buffer = sync_timer_read32();

    /* Turn on backlight mode for indicator */
    indicator_enable();
    indicator_reset_backlit_time();

    switch (state) {
        case BLUETOOTH_DISCONNECTED:
            INDICATOR_SET(disconnected);
            indicator_config.value = (indicator_config.type == INDICATOR_NONE) ? 0 : host_index;
            indicator_timer_cb((void *)&indicator_config.type);

            if (battery_is_critical_low()) {
                indicator_set_backlit_timeout(1000);
            } else {
                /* Set timer so that user has chance to turn on the backlight when is off */
                indicator_set_backlit_timeout(DECIDE_TIME(DISCONNECTED_BACKLIGHT_DISABLE_TIMEOUT * 1000, indicator_config.duration));
            }
            break;

        case BLUETOOTH_CONNECTED:
            if (indicator_state != BLUETOOTH_CONNECTED) {
                INDICATOR_SET(connected);
                indicator_config.value = (indicator_config.type == INDICATOR_NONE) ? 0 : host_index;
                indicator_timer_cb((void *)&indicator_config.type);
            }
            indicator_set_backlit_timeout(DECIDE_TIME(CONNECTED_BACKLIGHT_DISABLE_TIMEOUT * 1000, indicator_config.duration));
            break;

        case BLUETOOTH_PARING:
            INDICATOR_SET(pairing);
            indicator_config.value = (indicator_config.type == INDICATOR_NONE) ? 0 : LED_ON | host_index;
            indicator_timer_cb((void *)&indicator_config.type);
            indicator_set_backlit_timeout(DECIDE_TIME(DISCONNECTED_BACKLIGHT_DISABLE_TIMEOUT * 1000, indicator_config.duration));
            break;

        case BLUETOOTH_RECONNECTING:
            INDICATOR_SET(reconnecting);
            indicator_config.value = (indicator_config.type == INDICATOR_NONE) ? 0 : LED_ON | host_index;
            indicator_timer_cb((void *)&indicator_config.type);
            indicator_set_backlit_timeout(DECIDE_TIME(DISCONNECTED_BACKLIGHT_DISABLE_TIMEOUT * 1000, indicator_config.duration));
            break;

        case BLUETOOTH_SUSPEND:
            INDICATOR_SET(disconnected);
            indicator_config.value = (indicator_config.type == INDICATOR_NONE) ? 0 : host_index;
            indicator_timer_cb((void *)&indicator_config.type);
            indicator_set_backlit_timeout(100);
            break;

        default:
            break;
    }

    indicator_state = state;
}

void indicator_stop(void) {
    indicator_config.value = 0;

    if (indicator_is_backlit_enabled_eeprom()) {
        indicator_enable();
    } else {
        indicator_disable();
    }
}

void indicator_battery_low_enable(bool enable) {
    battery_low_indicator = enable ? (sync_timer_read32() | 1) : 0;
#ifdef BAT_LOW_LED_PIN
    if (!enable) writePin(BAT_LOW_LED_PIN, !BAT_LOW_LED_PIN_ON_STATE);
#endif
}

void indicator_task(void) {
    bat_level_animiation_task();

    if (indicator_config.value && sync_timer_elapsed32(indicator_timer_buffer) >= next_period) {
        indicator_timer_cb((void *)&type);
        indicator_timer_buffer = sync_timer_read32();
    }

    if (battery_low_indicator && sync_timer_elapsed32(battery_low_indicator) > LOW_BAT_ON_OFF_DURATION) {
#ifdef BAT_LOW_LED_PIN
        togglePin(BAT_LOW_LED_PIN);
#endif
        battery_low_indicator = sync_timer_read32() | 1;
    }
}

#ifdef LED_MATRIX_ENABLE
void led_matrix_indicators_kb(void) {
    if (get_transport() == TRANSPORT_BLUETOOTH) {
        if (battery_is_critical_low()) {
            /* Prevent backlight flash caused by key activities */
            led_matrix_set_value_all(0);
            return;
        }

        if (bat_level_animiation_actived()) {
            bat_level_animiation_indicate();
        }

        static uint8_t last_host_index = 0xFF;
        if (indicator_config.value) {
            uint8_t host_index = indicator_config.value & 0x0F;

            if (indicator_config.highlight) {
                led_matrix_set_value_all(0);
            } else if (last_host_index != host_index) {
                led_matrix_set_value(host_led_matrix_list[last_host_index - 1], 0);
                last_host_index = host_index;
            }

            if (indicator_config.value & 0x80)
                led_matrix_set_value(host_led_matrix_list[host_index - 1], 255);
            else
                led_matrix_set_value(host_led_matrix_list[host_index - 1], 0);
        }
#    if defined(DIM_CAPS_LOCK) && defined(CAPS_LOCK_INDEX)
        else if (host_keyboard_led_state().caps_lock) {
            led_matrix_set_value(CAPS_LOCK_INDEX, 0);
        }
#    endif
    }
}
#endif

#ifdef RGB_MATRIX_ENABLE
void rgb_matrix_indicators_kb(void) {
    {
        if (battery_is_critical_low()) {
            /* Prevent backlight flash caused by key activities */
            rgb_matrix_set_color_all(0, 0, 0);
            return;
        }

        if (bat_level_animiation_actived()) {
            bat_level_animiation_indicate();
        }
        static uint8_t last_host_index = 0xFF;

        if (indicator_config.value) {
            uint8_t host_index = indicator_config.value & 0x0F;

            if (indicator_config.highlight) {
                rgb_matrix_set_color_all(0, 0, 0);
            } else if (last_host_index != host_index) {
                rgb_matrix_set_color(host_led_matrix_list[last_host_index - 1], 0, 0, 0);
                last_host_index = host_index;
            }

            if (indicator_config.value & 0x80) {
                rgb_matrix_set_color(host_led_matrix_list[host_index - 1], 0, 0, 255);
            } else {
                rgb_matrix_set_color(host_led_matrix_list[host_index - 1], 0, 0, 0);
            }
        }
#    if defined(DIM_CAPS_LOCK) && defined(CAPS_LOCK_INDEX)
        else if (host_keyboard_led_state().caps_lock) {
            rgb_matrix_set_color(CAPS_LOCK_INDEX, 0, 0, 0);
        }
#    endif
    }
}
#endif
