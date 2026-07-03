/* Copyright 2020 zvecr<git@zvecr.com>
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
#include "led.h"
#include "host.h"
#include "timer.h"
#include "debug.h"
#include "gpio.h"

#ifdef BACKLIGHT_CAPS_LOCK
#    ifdef BACKLIGHT_ENABLE
#        include "backlight.h"
extern backlight_config_t backlight_config;
#    else
#        pragma message "Cannot use BACKLIGHT_CAPS_LOCK without backlight being enabled"
#        undef BACKLIGHT_CAPS_LOCK
#    endif
#endif

#ifndef LED_PIN_ON_STATE
#    define LED_PIN_ON_STATE 1
#endif

#ifdef BACKLIGHT_CAPS_LOCK
/** \brief Caps Lock indicator using backlight (for keyboards without dedicated LED)
 */
static void handle_backlight_caps_lock(led_t led_state) {
    // Use backlight as Caps Lock indicator
    uint8_t bl_toggle_lvl = 0;

    if (led_state.caps_lock && !backlight_config.enable) {
        // Turning Caps Lock ON and backlight is disabled in config
        // Toggling backlight to the brightest level
        bl_toggle_lvl = BACKLIGHT_LEVELS;
    } else if (!led_state.caps_lock && backlight_config.enable) {
        // Turning Caps Lock OFF and backlight is enabled in config
        // Toggling backlight and restoring config level
        bl_toggle_lvl = backlight_config.level;
    }

    // Set level without modify backlight_config to keep ability to restore state
    backlight_set(bl_toggle_lvl);
}
#endif

static uint32_t last_led_modification_time = 0;

uint32_t last_led_activity_time(void) {
    return last_led_modification_time;
}

uint32_t last_led_activity_elapsed(void) {
    return timer_elapsed32(last_led_modification_time);
}

/** \brief Lock LED update callback - keymap/user level
 *
 * \return True if led_update_kb() should run its own code, false otherwise.
 */
__attribute__((weak)) bool led_update_user(led_t led_state) {
    return true;
}

/** \brief Lock LED update callback - keyboard level
 *
 * \return Ignored for now.
 */
__attribute__((weak)) bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
        led_update_ports(led_state);
    }
    return res;
}

/** \brief Write LED state to hardware
 */
__attribute__((weak)) void led_update_ports(led_t led_state) {
#if LED_PIN_ON_STATE == 0
    // invert the whole thing to avoid having to conditionally !led_state.x later
    led_state.raw = ~led_state.raw;
#endif

#ifdef LED_NUM_LOCK_PIN
    gpio_write_pin(LED_NUM_LOCK_PIN, led_state.num_lock);
#endif
#ifdef LED_CAPS_LOCK_PIN
    gpio_write_pin(LED_CAPS_LOCK_PIN, led_state.caps_lock);
#endif
#ifdef LED_SCROLL_LOCK_PIN
    gpio_write_pin(LED_SCROLL_LOCK_PIN, led_state.scroll_lock);
#endif
#ifdef LED_COMPOSE_PIN
    gpio_write_pin(LED_COMPOSE_PIN, led_state.compose);
#endif
#ifdef LED_KANA_PIN
    gpio_write_pin(LED_KANA_PIN, led_state.kana);
#endif
}

/** \brief Initialise any LED related hardware and/or state
 */
__attribute__((weak)) void led_init_ports(void) {
#ifdef LED_NUM_LOCK_PIN
    gpio_set_pin_output(LED_NUM_LOCK_PIN);
    gpio_write_pin(LED_NUM_LOCK_PIN, !LED_PIN_ON_STATE);
#endif
#ifdef LED_CAPS_LOCK_PIN
    gpio_set_pin_output(LED_CAPS_LOCK_PIN);
    gpio_write_pin(LED_CAPS_LOCK_PIN, !LED_PIN_ON_STATE);
#endif
#ifdef LED_SCROLL_LOCK_PIN
    gpio_set_pin_output(LED_SCROLL_LOCK_PIN);
    gpio_write_pin(LED_SCROLL_LOCK_PIN, !LED_PIN_ON_STATE);
#endif
#ifdef LED_COMPOSE_PIN
    gpio_set_pin_output(LED_COMPOSE_PIN);
    gpio_write_pin(LED_COMPOSE_PIN, !LED_PIN_ON_STATE);
#endif
#ifdef LED_KANA_PIN
    gpio_set_pin_output(LED_KANA_PIN);
    gpio_write_pin(LED_KANA_PIN, !LED_PIN_ON_STATE);
#endif
}

/** \brief Entrypoint for protocol to LED binding
 */
__attribute__((weak)) void led_set(uint8_t usb_led) {
#ifdef BACKLIGHT_CAPS_LOCK
    handle_backlight_caps_lock((led_t)usb_led);
#endif

    led_update_kb((led_t)usb_led);
}

/** \brief Trigger behaviour on transition to suspend
 */
void led_suspend(void) {
    led_t leds_off = {0};
#ifdef BACKLIGHT_CAPS_LOCK
    if (is_backlight_enabled()) {
        // Don't try to turn off Caps Lock indicator as it is backlight and backlight is already off
        leds_off.caps_lock = true;
    }
#endif
    led_set(leds_off.raw);
}

/** \brief Trigger behaviour on transition from suspend
 */
void led_wakeup(void) {
    led_set(host_keyboard_leds());
}

/** \brief set host led state
 *
 * Only sets state if change detected
 */
void led_task(void) {
    static uint8_t last_led_status = 0;

    // update LED
    uint8_t led_status = host_keyboard_leds();
    if (last_led_status != led_status) {
        last_led_status            = led_status;
        last_led_modification_time = timer_read32();

        if (debug_keyboard) {
            dprintf("led_task: %02X\n", led_status);
        }
        led_set(led_status);
    }
}
