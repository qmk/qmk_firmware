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

#include "quantum.h"
#include "indicator.h"
#include "transport.h"
#include "battery.h"
#include "eeconfig.h"
#include "wireless_config.h"
#include "config.h"
#include "rtc_timer.h"
#include "lemokey_common.h"
#include "usb_main.h"
#ifdef FACTORY_TEST_ENABLE
#    include "factory_test.h"
#endif
#include "lpm.h"
#include "lemokey_task.h"
#if defined(LED_MATRIX_ENABLE) || defined(RGB_MATRIX_ENABLE)
#    ifdef LED_MATRIX_ENABLE
#        include "led_matrix.h"
#    endif
#    ifdef RGB_MATRIX_ENABLE
#        include "rgb_matrix.h"
#    endif
#endif
#include "bat_level_animation.h"

#define INDEX_MASK 0x0F
#define P24G_IND_MASK 0x10
#define USB_IND_MASK 0x20
#define LED_ON 0x80

#define IND_VAL_MASK (USB_IND_MASK | P24G_IND_MASK | INDEX_MASK)

#ifdef LED_MATRIX_ENABLE
#    define DECIDE_TIME(t, duration) (duration == 0 ? LED_MATRIX_TIMEOUT_INFINITE : ((t > duration) ? t : duration))
#endif
#ifdef RGB_MATRIX_ENABLE
#    define DECIDE_TIME(t, duration) (duration == 0 ? RGB_MATRIX_TIMEOUT_INFINITE : ((t > duration) ? t : duration))
#endif

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
indicator_config_t        indicator_config;
static wt_state_t         indicator_state;
static uint16_t           next_period;
static indicator_type_t   type;
static uint32_t           indicator_timer_buffer = 0;

#if defined(BAT_LOW_LED_PIN) || defined(SPACE_KEY_LOW_BAT_IND)
static uint32_t bat_low_backlit_indicator = 0;
static uint8_t  bat_low_ind_state         = 0;
static uint32_t rtc_time                  = 0;
#endif

#if defined(LED_MATRIX_ENABLE) || defined(RGB_MATRIX_ENABLE)
backlight_state_t original_backlight_state;

#    ifdef BT_INDICATION_LED_LIST
static uint8_t bt_host_led_matrix_list[BT_HOST_DEVICES_COUNT] = BT_INDICATION_LED_LIST;
#    endif
#endif

#ifdef BT_INDICATION_LED_PIN_LIST
static pin_t bt_led_pin_list[BT_HOST_DEVICES_COUNT] = BT_INDICATION_LED_PIN_LIST;
#endif

#ifdef LED_MATRIX_ENABLE
#    define LED_DRIVER led_matrix_driver
#    define LED_INDICATORS_KB led_matrix_indicators_bt
#    define LED_INDICATORS_USER led_matrix_indicators_user
#    define LED_NONE_INDICATORS_KB led_matrix_none_indicators_kb
#    define SET_ALL_LED_OFF() led_matrix_set_value_all(0)
#    define SET_LED_OFF(idx) led_matrix_set_value(idx, 0)
#    define SET_LED_ON(idx) led_matrix_set_value(idx, 255)
#    define SET_LED_BT SET_LED_ON
#    define SET_LED_P24G SET_LED_ON
#    define SET_LED_LOW_BAT SET_LED_ON
#    define LED_DRIVER_IS_ENABLED led_matrix_is_enabled
#    define LED_DRIVER_EECONFIG_RELOAD()                                                           \
        eeprom_read_block(&led_matrix_eeconfig, EECONFIG_LED_MATRIX, sizeof(led_matrix_eeconfig)); \
        if (!led_matrix_eeconfig.mode) {                                                           \
            eeconfig_update_led_matrix_default();                                                  \
        }
#    define LED_DRIVER_ALLOW_SHUTDOWN led_matrix_driver_allow_shutdown
#    define LED_DRIVER_SHUTDOWN led_matrix_driver_shutdown
#    define LED_DRIVER_EXIT_SHUTDOWN led_matrix_driver_exit_shutdown
#    define LED_DRIVER_ENABLE_NOEEPROM led_matrix_enable_noeeprom
#    define LED_DRIVER_DISABLE_NOEEPROM led_matrix_disable_noeeprom
#    define LED_DRIVER_DISABLE_TIMEOUT_SET led_matrix_disable_timeout_set
#    define LED_DRIVER_DISABLE_TIME_RESET led_matrix_disable_time_reset
#    define LED_DRIVER_TIMEOUTED led_matrix_timeouted
#endif

#ifdef RGB_MATRIX_ENABLE
#    define LED_DRIVER rgb_matrix_driver
#    define LED_INDICATORS_KB rgb_matrix_indicators_bt
#    define LED_INDICATORS_USER rgb_matrix_indicators_user
#    define LED_NONE_INDICATORS_KB rgb_matrix_none_indicators_kb
#    define SET_ALL_LED_OFF() rgb_matrix_set_color_all(0, 0, 0)
#    define SET_LED_OFF(idx) rgb_matrix_set_color(idx, 0, 0, 0)
#    define SET_LED_ON(idx) rgb_matrix_set_color(idx, 255, 255, 255)
#    define SET_LED_BT(idx) rgb_matrix_set_color(idx, 0, 0, 255)
#    define SET_LED_P24G(idx) rgb_matrix_set_color(idx, 0, 255, 0)
#    define SET_LED_LOW_BAT(idx) rgb_matrix_set_color(idx, 255, 0, 0)
#    define LED_DRIVER_IS_ENABLED rgb_matrix_is_enabled
#    define LED_DRIVER_EECONFIG_RELOAD()                                                       \
        eeprom_read_block(&rgb_matrix_config, EECONFIG_RGB_MATRIX, sizeof(rgb_matrix_config)); \
        if (!rgb_matrix_config.mode) {                                                         \
            eeconfig_update_rgb_matrix_default();                                              \
        }
#    define LED_DRIVER_ALLOW_SHUTDOWN rgb_matrix_driver_allow_shutdown
#    define LED_DRIVER_SHUTDOWN rgb_matrix_driver_shutdown
#    define LED_DRIVER_EXIT_SHUTDOWN rgb_matrix_driver_exit_shutdown
#    define LED_DRIVER_ENABLE_NOEEPROM rgb_matrix_enable_noeeprom
#    define LED_DRIVER_DISABLE_NOEEPROM rgb_matrix_disable_noeeprom
#    define LED_DRIVER_DISABLE_TIMEOUT_SET rgb_matrix_disable_timeout_set
#    define LED_DRIVER_DISABLE_TIME_RESET rgb_matrix_disable_time_reset
#    define LED_DRIVER_TIMEOUTED rgb_matrix_timeouted
#endif

#ifdef WINLOCK_LED_LIST
#    define SET_LED_WINLOCK(idx) rgb_matrix_set_color(idx, 255, 0, 0)
#endif

bool LED_INDICATORS_KB(void);

void indicator_init(void) {
    memset(&indicator_config, 0, sizeof(indicator_config));

#ifdef BT_INDICATION_LED_PIN_LIST
    for (uint8_t i = 0; i < BT_HOST_DEVICES_COUNT; i++) {
        setPinOutput(bt_led_pin_list[i]);
        writePin(bt_led_pin_list[i], !BT_INDICATION_LED_ON_STATE);
    }
#endif

#ifdef COMMON_BT_LED_PIN
    setPinOutput(COMMON_BT_LED_PIN);
    writePin(COMMON_BT_LED_PIN, !COMMON_BT_LED_PIN_ON_STATE);
#endif

#ifdef P24G_INDICATION_LED_PIN
    setPinOutput(P24G_INDICATION_LED_PIN);
    writePin(P24G_INDICATION_LED_PIN, !BT_INDICATION_LED_ON_STATE);
#endif

#ifdef BAT_LOW_LED_PIN
    setPinOutput(BAT_LOW_LED_PIN);
    writePin(BAT_LOW_LED_PIN, !BAT_LOW_LED_PIN_ON_STATE);
#endif

#ifdef WIN_LOCK_LED_PIN
    setPinOutput(WIN_LOCK_LED_PIN);
    writePin(WIN_LOCK_LED_PIN, keymap_config.no_gui);
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
#if defined(BAT_LOW_LED_PIN) || defined(SPACE_KEY_LOW_BAT_IND)
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
                    indicator_config.value = indicator_config.value & IND_VAL_MASK;
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
                    indicator_config.value = indicator_config.value & IND_VAL_MASK;
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

#if defined(BT_INDICATION_LED_PIN_LIST) || defined(P24G_INDICATION_LED_PIN) || defined(COMMON_BT_LED_PIN)
    if (indicator_config.value) {
#    if defined(P24G_INDICATION_LED_PIN)
        if (indicator_config.value & P24G_IND_MASK) {
            if ((indicator_config.value & LED_ON) && !time_up) {
                writePin(P24G_INDICATION_LED_PIN, BT_INDICATION_LED_ON_STATE);
            } else {
                writePin(P24G_INDICATION_LED_PIN, !BT_INDICATION_LED_ON_STATE);
            }
        } else
#    endif
        {
            uint8_t idx = (indicator_config.value & INDEX_MASK) - 1;
#ifdef BT_INDICATION_LED_PIN_LIST
            for (uint8_t i = 0; i < BT_HOST_DEVICES_COUNT; i++) {
                if (i != idx) writePin(bt_led_pin_list[idx], !BT_INDICATION_LED_ON_STATE);
            }
#endif
            if ((indicator_config.value & LED_ON) && !time_up) {
#ifdef BT_INDICATION_LED_PIN_LIST
                writePin(bt_led_pin_list[idx], BT_INDICATION_LED_ON_STATE);
#endif
#ifdef COMMON_BT_LED_PIN
                writePin(COMMON_BT_LED_PIN, COMMON_BT_LED_PIN_ON_STATE);
#endif
            } else {
#ifdef BT_INDICATION_LED_PIN_LIST
                writePin(bt_led_pin_list[idx], !BT_INDICATION_LED_ON_STATE);
#endif
#ifdef COMMON_BT_LED_PIN
                writePin(COMMON_BT_LED_PIN, !COMMON_BT_LED_PIN_ON_STATE);
#endif
            }
        }
    }
#endif

    if (time_up) {
        /* Set indicator to off on timeup, avoid keeping light up until next update in raindrop effect */
        indicator_config.value = indicator_config.value & IND_VAL_MASK;
#if defined(LED_MATRIX_ENABLE) || defined(RGB_MATRIX_ENABLE)
        LED_INDICATORS_KB();
#endif

        indicator_config.value = 0;
        lpm_timer_reset();
    }

    if (indicator_config.value == 0) {
#if defined(LED_MATRIX_ENABLE) || defined(RGB_MATRIX_ENABLE)
        indicator_eeconfig_reload();
        if (!LED_DRIVER_IS_ENABLED()) indicator_disable();
#endif
    }
}

void indicator_set(wt_state_t state, uint8_t host_index) {
    if (get_transport() == TRANSPORT_USB) return;

#if defined(LED_MATRIX_ENABLE) || defined(RGB_MATRIX_ENABLE)
    static uint8_t pre_state = 0;
#endif
    static uint8_t current_state      = 0;
    static uint8_t current_host       = 0;
    bool           host_index_changed = false;

    if (host_index == P24G_HOST_INDEX)
        host_index = P24G_IND_MASK | 0x01;

    else if (host_index == USB_HOST_INDEX)
        host_index = USB_IND_MASK | 0x01;

    if (current_host != host_index && state != WT_DISCONNECTED) {
        host_index_changed = true;
        current_host       = host_index;
    }

    if (current_state != state || host_index_changed || state == WT_RECONNECTING) {
        // Some BT chips need to reset to enter sleep mode, ignore it.
        if (current_state == WT_SUSPEND && state == WT_DISCONNECTED) return;
#if defined(LED_MATRIX_ENABLE) || defined(RGB_MATRIX_ENABLE)
        pre_state = current_state;
#endif
        current_state = state;
    } else {
        return;
    }

    indicator_timer_buffer = timer_read32();

#if defined(LED_MATRIX_ENABLE) || defined(RGB_MATRIX_ENABLE)
    /* Turn on backlight mode for indicator */
    indicator_enable();
    indicator_reset_backlit_time();
#endif
#if defined(BT_INDICATION_LED_PIN_LIST)
    for (uint8_t i = 0; i < BT_HOST_DEVICES_COUNT; i++)
        writePin(bt_led_pin_list[i], !BT_INDICATION_LED_ON_STATE);
#endif

#if defined(P24G_INDICATION_LED_PIN)
    writePin(P24G_INDICATION_LED_PIN, !BT_INDICATION_LED_ON_STATE);
#endif
#ifdef COMMON_BT_LED_PIN
    writePin(COMMON_BT_LED_PIN, !COMMON_BT_LED_PIN_ON_STATE);
#endif
    switch (state) {
        case WT_DISCONNECTED:

#if defined(BT_INDICATION_LED_PIN_LIST)
            if ((host_index & P24G_IND_MASK) != P24G_IND_MASK) writePin(bt_led_pin_list[(host_index & INDEX_MASK) - 1], !BT_INDICATION_LED_ON_STATE);
#endif
#if defined(P24G_INDICATION_LED_PIN)
            writePin(P24G_INDICATION_LED_PIN, !BT_INDICATION_LED_ON_STATE);
#endif

            INDICATOR_SET(disconnected);
            indicator_config.value = (indicator_config.type == INDICATOR_NONE) ? 0 : host_index;
            indicator_timer_cb((void *)&indicator_config.type);
#if defined(LED_MATRIX_ENABLE) || defined(RGB_MATRIX_ENABLE)
            if (battery_is_critical_low()) {
                indicator_set_backlit_timeout(1000);

            } else {
#if defined(LED_MATRIX_ENABLE) || defined(RGB_MATRIX_ENABLE)
                if (pre_state == WT_CONNECTED)
                    indicator_set_backlit_timeout(1000);
                else
#endif
                /* Set timer so that user has chance to turn on the backlight when is off */
                indicator_set_backlit_timeout(DECIDE_TIME(DISCONNECTED_BACKLIGHT_DISABLE_TIMEOUT * 1000, indicator_config.duration));
            }
#endif
            break;

        case WT_CONNECTED:
            if (indicator_state != WT_CONNECTED) {
                INDICATOR_SET(connected);
                indicator_config.value = (indicator_config.type == INDICATOR_NONE) ? 0 : host_index;
                indicator_timer_cb((void *)&indicator_config.type);
            }
#if defined(LED_MATRIX_ENABLE) || defined(RGB_MATRIX_ENABLE)
            indicator_set_backlit_timeout(DECIDE_TIME(CONNECTED_BACKLIGHT_DISABLE_TIMEOUT * 1000, indicator_config.duration));
#endif
            break;

        case WT_PARING:
            INDICATOR_SET(pairing);
            indicator_config.value = (indicator_config.type == INDICATOR_NONE) ? 0 : LED_ON | host_index;
            indicator_timer_cb((void *)&indicator_config.type);
#if defined(LED_MATRIX_ENABLE) || defined(RGB_MATRIX_ENABLE)
            indicator_set_backlit_timeout(DECIDE_TIME(DISCONNECTED_BACKLIGHT_DISABLE_TIMEOUT * 1000, indicator_config.duration));
#endif
            break;

        case WT_RECONNECTING:
            INDICATOR_SET(reconnecting);
            indicator_config.value = (indicator_config.type == INDICATOR_NONE) ? 0 : LED_ON | host_index;
            indicator_timer_cb((void *)&indicator_config.type);
#if defined(LED_MATRIX_ENABLE) || defined(RGB_MATRIX_ENABLE)
            indicator_set_backlit_timeout(DECIDE_TIME(DISCONNECTED_BACKLIGHT_DISABLE_TIMEOUT * 1000, indicator_config.duration));
#endif
            break;

        case WT_SUSPEND:
            INDICATOR_SET(disconnected);
            indicator_config.value = (indicator_config.type == INDICATOR_NONE) ? 0 : host_index;
            indicator_timer_cb((void *)&indicator_config.type);
#if defined(LED_MATRIX_ENABLE) || defined(RGB_MATRIX_ENABLE)
#    ifdef FACTORY_TEST_ENABLE
            if (factory_reset_indicating())
                indicator_set_backlit_timeout(3000);
            else
#    endif
            {
                indicator_set_backlit_timeout(1000);
            }
#endif

#if defined(BT_INDICATION_LED_PIN_LIST)
            for (uint8_t i = 0; i < BT_HOST_DEVICES_COUNT; i++)
                writePin(bt_led_pin_list[i], !BT_INDICATION_LED_ON_STATE);
#endif
#if defined(P24G_INDICATION_LED_PIN)
            writePin(P24G_INDICATION_LED_PIN, !BT_INDICATION_LED_ON_STATE);
#endif
#ifdef COMMON_BT_LED_PIN
            writePin(COMMON_BT_LED_PIN, !COMMON_BT_LED_PIN_ON_STATE);
#endif
#    if defined(BAT_LOW_LED_PIN)
            writePin(BAT_LOW_LED_PIN, !BAT_LOW_LED_PIN_ON_STATE);
#    endif
            break;

        default:
            break;
    }

    indicator_state = state;
}

void indicator_stop(void) {
    indicator_config.value = 0;
#if defined(LED_MATRIX_ENABLE) || defined(RGB_MATRIX_ENABLE)
    indicator_eeconfig_reload();

    if (indicator_is_enabled()) {
        indicator_enable();
    } else {
        indicator_disable();
    }
#endif
}

void indicator_battery_low_enable(bool enable) {
#if defined(BAT_LOW_LED_PIN) || defined(SPACE_KEY_LOW_BAT_IND)
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
            bat_low_backlit_indicator = enable ? timer_read32() : 0;
            rtc_time                  = rtc_timer_read_ms();
            bat_low_ind_state         = 1;
#    if defined(SPACE_KEY_LOW_BAT_IND)
            indicator_enable();
#    endif
        }
    } else {
        rtc_time          = 0;
        bat_low_ind_state = 0;
#    if defined(SPACE_KEY_LOW_BAT_IND)
        indicator_eeconfig_reload();
        if (!LED_DRIVER_IS_ENABLED()) indicator_disable();
#    endif
    }
#endif
}

void indicator_battery_low(void) {
#if defined(BAT_LOW_LED_PIN) || defined(SPACE_KEY_LOW_BAT_IND)
    if (bat_low_ind_state) {
        if ((bat_low_ind_state & 0x0F) <= (LOW_BAT_LED_BLINK_TIMES) && timer_elapsed32(bat_low_backlit_indicator) > (LOW_BAT_LED_BLINK_PERIOD)) {
            if (bat_low_ind_state & 0x80) {
                bat_low_ind_state &= 0x7F;
                bat_low_ind_state++;
#    if defined(BAT_LOW_LED_PIN)
                writePin(BAT_LOW_LED_PIN, !BAT_LOW_LED_PIN_ON_STATE);
#    endif
            } else {
                bat_low_ind_state |= 0x80;
#    if defined(BAT_LOW_LED_PIN)
                writePin(BAT_LOW_LED_PIN, BAT_LOW_LED_PIN_ON_STATE);
#    endif
            }

            bat_low_backlit_indicator = timer_read32();

            /*  Restore backligth state */
            if ((bat_low_ind_state & 0x0F) > (LOW_BAT_LED_BLINK_TIMES)) {
#    if defined(BAT_LOW_LED_PIN)
                writePin(BAT_LOW_LED_PIN, !BAT_LOW_LED_PIN_ON_STATE);
#    endif
#    if defined(SPACE_KEY_LOW_BAT_IND)
#        if defined(NUM_LOCK_INDEX) || defined(CAPS_LOCK_INDEX) || defined(SCROLL_LOCK_INDEX) || defined(COMPOSE_LOCK_INDEX) || defined(KANA_LOCK_INDEX)
                if (LED_DRIVER_ALLOW_SHUTDOWN())
#        endif
                    indicator_disable();
#    endif
            }
        } else if ((bat_low_ind_state & 0x0F) > (LOW_BAT_LED_BLINK_TIMES)) {
#    if defined(BAT_LOW_LED_PIN)
            writePin(BAT_LOW_LED_PIN, !BAT_LOW_LED_PIN_ON_STATE);
#    endif
            bat_low_ind_state = 0;
            lpm_timer_reset();
        }
    }
#endif
}

void indicator_task(void) {
    bat_level_animiation_task();
    if (indicator_config.value && timer_elapsed32(indicator_timer_buffer) >= next_period) {
        indicator_timer_cb((void *)&type);
        indicator_timer_buffer = timer_read32();
    }

    indicator_battery_low();
}

#if defined(LED_MATRIX_ENABLE) || defined(RGB_MATRIX_ENABLE)
__attribute__((weak)) void os_state_indicate(void) {
#    if defined(RGB_DISABLE_WHEN_USB_SUSPENDED) || defined(LED_DISABLE_WHEN_USB_SUSPENDED)
    if (get_transport() == TRANSPORT_USB && USB_DRIVER.state == USB_SUSPENDED) return;
#    endif

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

#    if defined(WIN_LOCK_LED_PIN) || defined(WINLOCK_LED_LIST)
    /* TODO: move to common.c */
    if (keymap_config.no_gui && (((get_transport() & TRANSPORT_WIRELESS) && wireless_get_state() == WT_CONNECTED) || (get_transport() == TRANSPORT_USB && USBD1.state == USB_ACTIVE))) {
#        ifdef WINLOCK_LED_LIST
        if (keymap_config.no_gui) {
            uint8_t led_list[] = WINLOCK_LED_LIST;
            uint8_t led_cnt    = ARRAY_SIZE(led_list);
            for (uint8_t i = 0; i < led_cnt; i++) {
#            if defined(DIM_WIN_LOCK)
                SET_LED_OFF(led_list[i]);
#            else
                SET_LED_WINLOCK(led_list[i]);
#            endif
            }
        }
#        endif
#        ifdef WIN_LOCK_LED_PIN
        writePin(WIN_LOCK_LED_PIN, WIN_LOCK_LED_ON_LEVEL);
#        endif
    } else {
#        ifdef WIN_LOCK_LED_PIN
        writePin(WIN_LOCK_LED_PIN, !WIN_LOCK_LED_ON_LEVEL);
#        endif
    }
#    endif
}

bool LED_INDICATORS_KB(void) {
    if (get_transport() & TRANSPORT_WIRELESS) {
        /* Prevent backlight flash caused by key activities */
        if (battery_is_critical_low()) {
            SET_ALL_LED_OFF();
            return true;
        }

        if (battery_is_empty()) SET_ALL_LED_OFF();
#    if defined(LOW_BAT_IND_INDEX)
        if (bat_low_ind_state && (bat_low_ind_state & 0x0F) <= LOW_BAT_LED_BLINK_TIMES) {
            uint8_t idx_list[] = LOW_BAT_IND_INDEX;
            for (uint8_t i = 0; i < sizeof(idx_list); i++) {
                if (bat_low_ind_state & LED_ON) {
                    SET_LED_LOW_BAT(idx_list[i]);
                } else {
                    SET_LED_OFF(idx_list[i]);
                }
            }
        }
#    endif

#    if (defined(LED_MATRIX_ENABLE) || defined(RGB_MATRIX_ENABLE)) && defined(BAT_LEVEL_LED_LIST)
        if (bat_level_animiation_actived()) {
            bat_level_animiation_indicate();
        }
#    endif
        static uint8_t last_host_index = 0xFF;

        if (indicator_config.value) {
            uint8_t host_index = indicator_config.value & INDEX_MASK;

            if (indicator_config.highlight) {
                SET_ALL_LED_OFF();
            } else if (last_host_index != host_index) {
#    ifdef P24G_INDICATION_LED_INDEX
                if (indicator_config.value & P24G_IND_MASK)
                    SET_LED_OFF(P24G_INDICATION_LED_INDEX);
                else
#    endif
                    SET_LED_OFF(bt_host_led_matrix_list[host_index - 1]);
                last_host_index = host_index;
            }

            if (indicator_config.value & LED_ON) {
#    ifdef P24G_INDICATION_LED_INDEX
                if (indicator_config.value & P24G_IND_MASK)
                    SET_LED_P24G(P24G_INDICATION_LED_INDEX);
                else
#    endif
                    SET_LED_BT(bt_host_led_matrix_list[host_index - 1]);

            } else {
#    ifdef P24G_INDICATION_LED_INDEX
                if (indicator_config.value & P24G_IND_MASK)
                    SET_LED_OFF(P24G_INDICATION_LED_INDEX);
                else
#    endif
                    SET_LED_OFF(bt_host_led_matrix_list[host_index - 1]);
            }
        } else
            os_state_indicate();
    }
    if (get_transport() == TRANSPORT_USB) os_state_indicate();

    if (!LED_INDICATORS_USER()) return true;

    return true;
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
        led_update_ports(led_state);

        if (!LED_DRIVER_IS_ENABLED() || (LED_DRIVER_IS_ENABLED() && LED_DRIVER_TIMEOUTED())) {
#    if defined(LED_MATRIX_DRIVER_SHUTDOWN_ENABLE) || defined(RGB_MATRIX_DRIVER_SHUTDOWN_ENABLE)
            LED_DRIVER_EXIT_SHUTDOWN();
#    endif
            SET_ALL_LED_OFF();
            os_state_indicate();
            LED_DRIVER.flush();
#    if defined(LED_MATRIX_DRIVER_SHUTDOWN_ENABLE) || defined(RGB_MATRIX_DRIVER_SHUTDOWN_ENABLE)
            if (LED_DRIVER_ALLOW_SHUTDOWN()) LED_DRIVER_SHUTDOWN();
#    endif
        }
    }

    return res;
}

void LED_NONE_INDICATORS_KB(void) {
#    if defined(RGB_DISABLE_WHEN_USB_SUSPENDED) || defined(LED_DISABLE_WHEN_USB_SUSPENDED)
    if (get_transport() == TRANSPORT_USB && USB_DRIVER.state == USB_SUSPENDED) return;
#    endif

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
#        if defined(WINLOCK_LED_LIST) && !defined(WIN_LOCK_LED_PIN)
    if (keymap_config.no_gui && (wireless_get_state() == WT_CONNECTED || get_transport()==TRANSPORT_USB)) return false;
#        endif

    return true;
}
#    endif
#endif
