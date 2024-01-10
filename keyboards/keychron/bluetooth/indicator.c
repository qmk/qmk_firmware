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
#include "rtc_timer.h"

#if defined(LED_MATRIX_ENABLE) || defined(RGB_MATRIX_ENABLE)
#    ifdef LED_MATRIX_ENABLE
#        include "led_matrix.h"
#    endif
#    ifdef RGB_MATRIX_ENABLE
#        include "rgb_matrix.h"
#    endif
#    include "i2c_master.h"
#    include "bat_level_animation.h"
#    include "eeprom.h"
#endif

#ifdef LED_MATRIX_ENABLE
#    define DECIDE_TIME(t, duration) (duration == 0 ? LED_MATRIX_TIMEOUT_INFINITE : ((t > duration) ? t : duration))
#endif
#ifdef RGB_MATRIX_ENABLE
#    define DECIDE_TIME(t, duration) (duration == 0 ? RGB_MATRIX_TIMEOUT_INFINITE : ((t > duration) ? t : duration))
#endif

#define LED_ON 0x80
#define INDICATOR_SET(s) memcpy(&indicator_config, &s##_config, sizeof(indicator_config_t));

enum {
    BACKLIGHT_OFF            = 0x00,
    BACKLIGHT_ON_CONNECTED   = 0x01,
    BACKLIGHT_ON_UNCONNECTED = 0x02,
};

static indicator_config_t pairing_config      = INDICATOR_CONFIG_PARING;
static indicator_config_t connected_config    = INDICATOR_CONFIG_CONNECTD;
static indicator_config_t reconnecting_config = INDICATOR_CONFIG_RECONNECTING;
static indicator_config_t disconnected_config = INDICATOR_CONFIG_DISCONNECTED;
indicator_config_t indicator_config;
static bluetooth_state_t indicator_state;
static uint16_t          next_period;
static indicator_type_t  type;
static uint32_t          indicator_timer_buffer = 0;

#if defined(BAT_LOW_LED_PIN) || defined(BAT_LOW_LED_PIN_STATE)
static uint32_t bat_low_pin_indicator  = 0;
static uint32_t bat_low_blink_duration = 0;
#    ifdef BAT_LOW_LED_PIN_STATE
bool bat_low_led_pin_state = false;
#    endif
#endif

#if defined(LOW_BAT_IND_INDEX)
static uint32_t bat_low_backlit_indicator = 0;
static uint8_t  bat_low_ind_state         = 0;
static uint32_t rtc_time                  = 0;
#endif

#if defined(LED_MATRIX_ENABLE) || defined(RGB_MATRIX_ENABLE)
backlight_state_t original_backlight_state;

static uint8_t host_led_matrix_list[HOST_DEVICES_COUNT] = HOST_LED_MATRIX_LIST;
#endif

#ifdef HOST_LED_PIN_LIST
static pin_t host_led_pin_list[HOST_DEVICES_COUNT] = HOST_LED_PIN_LIST;
#endif

#ifdef LED_MATRIX_ENABLE
#    define LED_DRIVER led_matrix_driver
#    define LED_INDICATORS_KB led_matrix_indicators_kb
#    define LED_INDICATORS_USER led_matrix_indicators_user
#    define LED_NONE_INDICATORS_KB led_matrix_none_indicators_kb
#    define SET_ALL_LED_OFF() led_matrix_set_value_all(0)
#    define SET_LED_OFF(idx) led_matrix_set_value(idx, 0)
#    define SET_LED_ON(idx) led_matrix_set_value(idx, 255)
#    define SET_LED_BT(idx) led_matrix_set_value(idx, 255)
#    define SET_LED_LOW_BAT(idx) led_matrix_set_value(idx, 255)
#    define LED_DRIVER_IS_ENABLED led_matrix_is_enabled
#    define LED_DRIVER_EECONFIG_RELOAD() \
        eeprom_read_block(&led_matrix_eeconfig, EECONFIG_LED_MATRIX, sizeof(led_matrix_eeconfig)); \
        if (!led_matrix_eeconfig.mode) { \
            eeconfig_update_led_matrix_default(); \
        }
#    define LED_DRIVER_ALLOW_SHUTDOWN led_matrix_driver_allow_shutdown
#    define LED_DRIVER_ENABLE_NOEEPROM led_matrix_enable_noeeprom
#    define LED_DRIVER_DISABLE_NOEEPROM led_matrix_disable_noeeprom
#    define LED_DRIVER_DISABLE_TIMEOUT_SET led_matrix_disable_timeout_set
#    define LED_DRIVER_DISABLE_TIME_RESET led_matrix_disable_time_reset
#endif

#ifdef RGB_MATRIX_ENABLE
#    define LED_DRIVER rgb_matrix_driver
#    define LED_INDICATORS_KB rgb_matrix_indicators_kb
#    define LED_INDICATORS_USER rgb_matrix_indicators_user
#    define LED_NONE_INDICATORS_KB rgb_matrix_none_indicators_kb
#    define SET_ALL_LED_OFF() rgb_matrix_set_color_all(0, 0, 0)
#    define SET_LED_OFF(idx) rgb_matrix_set_color(idx, 0, 0, 0)
#    define SET_LED_ON(idx) rgb_matrix_set_color(idx, 255, 255, 255)
#    define SET_LED_BT(idx) rgb_matrix_set_color(idx, 0, 0, 255)
#    define SET_LED_LOW_BAT(idx) rgb_matrix_set_color(idx, 255, 0, 0)
#    define LED_DRIVER_IS_ENABLED rgb_matrix_is_enabled
#    define LED_DRIVER_EECONFIG_RELOAD() \
        eeprom_read_block(&rgb_matrix_config, EECONFIG_RGB_MATRIX, sizeof(rgb_matrix_config)); \
        if (!rgb_matrix_config.mode) {  \
            eeconfig_update_rgb_matrix_default();  \
        }
#    define LED_DRIVER_ALLOW_SHUTDOWN rgb_matrix_driver_allow_shutdown
#    define LED_DRIVER_ENABLE_NOEEPROM rgb_matrix_enable_noeeprom
#    define LED_DRIVER_DISABLE_NOEEPROM rgb_matrix_disable_noeeprom
#    define LED_DRIVER_DISABLE_TIMEOUT_SET rgb_matrix_disable_timeout_set
#    define LED_DRIVER_DISABLE_TIME_RESET rgb_matrix_disable_time_reset
#endif
void indicator_init(void) {
    memset(&indicator_config, 0, sizeof(indicator_config));

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
    if (!LED_DRIVER_IS_ENABLED()) {
        LED_DRIVER_ENABLE_NOEEPROM();
    }
}

inline void indicator_disable(void) {
    LED_DRIVER_DISABLE_NOEEPROM();
}

void indicator_set_backlit_timeout(uint32_t time) {
    LED_DRIVER_DISABLE_TIMEOUT_SET(time);
}

static inline void indicator_reset_backlit_time(void) {
    LED_DRIVER_DISABLE_TIME_RESET();
}

bool indicator_is_enabled(void) {
    return LED_DRIVER_IS_ENABLED();
}

void indicator_eeconfig_reload(void) {
    LED_DRIVER_EECONFIG_RELOAD();
}

#endif

bool indicator_is_running(void) {
    return
#if defined(BAT_LOW_LED_PIN) || defined(BAT_LOW_LED_PIN_STATE)
        bat_low_blink_duration ||
#endif
#if defined(LOW_BAT_IND_INDEX)
        bat_low_ind_state ||
#endif
        !!indicator_config.value;
}

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
                } else {
                    time_up = true;
                }
            }
            break;
        default:
            time_up = true;

            next_period = 0;
            break;
    }

#ifdef HOST_LED_PIN_LIST
    if (indicator_config.value) {
        uint8_t idx = (indicator_config.value & 0x0F) - 1;

        if (idx < HOST_DEVICES_COUNT) {
            if ((indicator_config.value & 0x80) && !time_up) {
               writePin(host_led_pin_list[idx], HOST_LED_PIN_ON_STATE);
            } else {
               writePin(host_led_pin_list[idx], !HOST_LED_PIN_ON_STATE);
            }
        }
    }
#endif

    if (time_up) {
        /* Set indicator to off on timeup, avoid keeping light up until next update in raindrop effect */
        indicator_config.value = indicator_config.value & 0x0F;
#if defined(LED_MATRIX_ENABLE) || defined(RGB_MATRIX_ENABLE)
        LED_INDICATORS_KB();
#endif
        indicator_config.value = 0;
    }

    if (indicator_config.value == 0) {
        indicator_eeconfig_reload();
        if (!LED_DRIVER_IS_ENABLED()) indicator_disable();
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
#ifdef HOST_LED_PIN_LIST
            writePin(host_led_pin_list[host_index - 1], !HOST_LED_PIN_ON_STATE);
#endif
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
    indicator_eeconfig_reload();

    if (indicator_is_enabled()) {
        indicator_enable();
    } else {
        indicator_disable();
    }
}

#if defined(BAT_LOW_LED_PIN) || defined(BAT_LOW_LED_PIN_STATE)
void indicator_battery_low_enable(bool enable) {
    if (enable) {
        if (bat_low_blink_duration == 0) {
            bat_low_blink_duration = bat_low_pin_indicator = sync_timer_read32() | 1;
        } else
            bat_low_blink_duration = sync_timer_read32() | 1;
    } else {
#    if defined(BAT_LOW_LED_PIN)
        writePin(BAT_LOW_LED_PIN, !BAT_LOW_LED_PIN_ON_STATE);
#    else
        bat_low_led_pin_state = false;
#    endif
    }
}
#endif

#if defined(LOW_BAT_IND_INDEX)
void indicator_battery_low_backlit_enable(bool enable) {
    if (enable) {
        uint32_t t = rtc_timer_read_ms();
        /* Check overflow */
        if (rtc_time > t) {
            if (bat_low_ind_state == 0)
                rtc_time = t; // Update rtc_time if indicating is not running
            else {
                rtc_time += t;
            }
        }
        /* Indicating at first time or after the interval */
        if ((rtc_time == 0 || t - rtc_time > LOW_BAT_LED_TRIG_INTERVAL) && bat_low_ind_state == 0) {
            bat_low_backlit_indicator = enable ? (timer_read32() == 0 ? 1 : timer_read32()) : 0;
            rtc_time                  = rtc_timer_read_ms();
            bat_low_ind_state         = 1;

            indicator_enable();
        }
    } else {
        rtc_time          = 0;
        bat_low_ind_state = 0;

        indicator_eeconfig_reload();
        if (!LED_DRIVER_IS_ENABLED()) indicator_disable();
    }
}
#endif

void indicator_battery_low(void) {
#if defined(BAT_LOW_LED_PIN) || defined(BAT_LOW_LED_PIN_STATE)
    if (bat_low_pin_indicator && sync_timer_elapsed32(bat_low_pin_indicator) > (LOW_BAT_LED_BLINK_PERIOD)) {
#    if defined(BAT_LOW_LED_PIN)
        togglePin(BAT_LOW_LED_PIN);
#    else
        bat_low_led_pin_state = !bat_low_led_pin_state;
#    endif
        bat_low_pin_indicator = sync_timer_read32() | 1;
        // Turn off low battery indication if we reach the duration
#    if defined(BAT_LOW_LED_PIN)
        if (sync_timer_elapsed32(bat_low_blink_duration) > LOW_BAT_LED_BLINK_DURATION && palReadLine(BAT_LOW_LED_PIN) != BAT_LOW_LED_PIN_ON_STATE) {
#    elif defined(BAT_LOW_LED_PIN_STATE)
        if (sync_timer_elapsed32(bat_low_blink_duration) > LOW_BAT_LED_BLINK_DURATION) {
#    endif
            bat_low_blink_duration = bat_low_pin_indicator = 0;
        }
    }
#endif
#if defined(LOW_BAT_IND_INDEX)
    if (bat_low_ind_state) {
        if ((bat_low_ind_state & 0x0F) <= (LOW_BAT_LED_BLINK_TIMES) && sync_timer_elapsed32(bat_low_backlit_indicator) > (LOW_BAT_LED_BLINK_PERIOD)) {
            if (bat_low_ind_state & 0x80) {
                bat_low_ind_state &= 0x7F;
                bat_low_ind_state++;
            } else {
                bat_low_ind_state |= 0x80;
            }

            bat_low_backlit_indicator = sync_timer_read32() == 0 ? 1 : sync_timer_read32();

            /*  Restore backligth state */
            if ((bat_low_ind_state & 0x0F) > (LOW_BAT_LED_BLINK_TIMES)) {
#    if defined(NUM_LOCK_INDEX) || defined(CAPS_LOCK_INDEX) || defined(SCROLL_LOCK_INDEX) || defined(COMPOSE_LOCK_INDEX) || defined(KANA_LOCK_INDEX)
                if (LED_DRIVER_ALLOW_SHUTDOWN())
#    endif
                    indicator_disable();
            }
        } else if ((bat_low_ind_state & 0x0F) > (LOW_BAT_LED_BLINK_TIMES)) {
            bat_low_ind_state = 0;
        }
    }
#endif
}

void indicator_task(void) {
    bat_level_animiation_task();

    if (indicator_config.value && sync_timer_elapsed32(indicator_timer_buffer) >= next_period) {
        indicator_timer_cb((void *)&type);
        indicator_timer_buffer = sync_timer_read32();
    }

    indicator_battery_low();
}

#if defined(LED_MATRIX_ENABLE) || defined(RGB_MATRIX_ENABLE)
__attribute__((weak)) void os_state_indicate(void) {
#    if defined(NUM_LOCK_INDEX)
    if (host_keyboard_led_state().num_lock) {
        SET_LED_ON(NUM_LOCK_INDEX);
    }
#    endif
#    if defined(CAPS_LOCK_INDEX)
    if (host_keyboard_led_state().caps_lock) {
#        if defined(DIM_CAPS_LOCK)
        SET_LED_OFF(CAPS_LOCK_INDEX);
#        else
        SET_LED_ON(CAPS_LOCK_INDEX);
#        endif
    }
#    endif
#    if defined(SCROLL_LOCK_INDEX)
    if (host_keyboard_led_state().scroll_lock) {
        SET_LED_ON(SCROLL_LOCK_INDEX);
    }
#    endif
#    if defined(COMPOSE_LOCK_INDEX)
    if (host_keyboard_led_state().compose) {
        SET_LED_ON(COMPOSE_LOCK_INDEX);
    }
#    endif
#    if defined(KANA_LOCK_INDEX)
    if (host_keyboard_led_state().kana) {
        SET_LED_ON(KANA_LOCK_INDEX);
    }
#    endif
}

bool LED_INDICATORS_KB(void) {
    if (!LED_INDICATORS_USER()) {
        return false;
    }

    if (get_transport() == TRANSPORT_BLUETOOTH) {
        /* Prevent backlight flash caused by key activities */
        if (battery_is_critical_low()) {
            SET_ALL_LED_OFF();
             return false;
        }

#    if (defined(LED_MATRIX_ENABLE) || defined(RGB_MATRIX_ENABLE)) && defined(LOW_BAT_IND_INDEX)
        if (battery_is_empty()) SET_ALL_LED_OFF();
        if (bat_low_ind_state && (bat_low_ind_state & 0x0F) <= LOW_BAT_LED_BLINK_TIMES) {
            if (bat_low_ind_state & 0x80)
                SET_LED_LOW_BAT(LOW_BAT_IND_INDEX);
            else
                SET_LED_OFF(LOW_BAT_IND_INDEX);
        }
#    endif
        if (bat_level_animiation_actived()) {
            bat_level_animiation_indicate();
        }
        static uint8_t last_host_index = 0xFF;

        if (indicator_config.value) {
            uint8_t host_index = indicator_config.value & 0x0F;

            if (indicator_config.highlight) {
                SET_ALL_LED_OFF();
            } else if (last_host_index != host_index) {
                SET_LED_OFF(host_led_matrix_list[last_host_index - 1]);
                last_host_index = host_index;
            }

            if (indicator_config.value & 0x80) {
                SET_LED_BT(host_led_matrix_list[host_index - 1]);
            } else {
                SET_LED_OFF(host_led_matrix_list[host_index - 1]);
            }
        } else
            os_state_indicate();

    } else
        os_state_indicate();

   return false;
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
        led_update_ports(led_state);

        if (!LED_DRIVER_IS_ENABLED()) {
    #    if defined(LED_MATRIX_DRIVER_SHUTDOWN_ENABLE) || defined(RGB_MATRIX_DRIVER_SHUTDOWN_ENABLE)
            LED_DRIVER.exit_shutdown();
    #    endif
            SET_ALL_LED_OFF();
            os_state_indicate();
            LED_DRIVER.flush();
    #    if defined(LED_MATRIX_DRIVER_SHUTDOWN_ENABLE) || defined(RGB_MATRIX_DRIVER_SHUTDOWN_ENABLE)
            if (LED_DRIVER_ALLOW_SHUTDOWN()) LED_DRIVER.shutdown();
    #    endif
        }
    }

    return res;
}

void LED_NONE_INDICATORS_KB(void) {
    os_state_indicate();
}

#    if defined(LED_MATRIX_DRIVER_SHUTDOWN_ENABLE) || defined(RGB_MATRIX_DRIVER_SHUTDOWN_ENABLE)
bool LED_DRIVER_ALLOW_SHUTDOWN(void) {
#        if defined(NUM_LOCK_INDEX)
    if (host_keyboard_led_state().num_lock) return false;
#        endif
#        if defined(CAPS_LOCK_INDEX) && !defined(DIM_CAPS_LOCK)
    if (host_keyboard_led_state().caps_lock) return false;
#        endif
#        if defined(SCROLL_LOCK_INDEX)
    if (host_keyboard_led_state().scroll_lock) return false;
#        endif
#        if defined(COMPOSE_LOCK_INDEX)
    if (host_keyboard_led_state().compose) return false;
#        endif
#        if defined(KANA_LOCK_INDEX)
    if (host_keyboard_led_state().kana) return false;
#        endif
    return true;
}
#    endif

#endif
