#include "quantum.h"

#ifdef BACKLIGHT_ENABLE
#    include "backlight.h"
extern backlight_config_t backlight_config;
#endif

#ifndef LED_PIN_ON_STATE
#    define LED_PIN_ON_STATE 0
#endif

/** \brief Lock LED set callback - keymap/user level
 *
 * \deprecated Use led_update_user() instead.
 */
__attribute__((weak)) void led_set_user(uint8_t usb_led) {}

/** \brief Lock LED set callback - keyboard level
 *
 * \deprecated Use led_update_kb() instead.
 */
__attribute__((weak)) void led_set_kb(uint8_t usb_led) { led_set_user(usb_led); }

/** \brief Lock LED update callback - keymap/user level
 *
 * \return True if led_update_kb() should run its own code, false otherwise.
 */
__attribute__((weak)) bool led_update_user(led_t led_state) { return true; }

/** \brief Lock LED update callback - keyboard level
 *
 * \return Ignored for now.
 */
__attribute__((weak)) bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
#if defined(LED_NUM_LOCK_PIN) || defined(LED_CAPS_LOCK_PIN) || defined(LED_SCROLL_LOCK_PIN) || defined(LED_COMPOSE_PIN) || defined(LED_KANA_PIN)
        // TODO: refactor to call led_init_ports in core && remove init from keyboards
        static bool s_init = false;
        if (!s_init) {
            led_init_ports();
            s_init = true;
        }

#    if LED_PIN_ON_STATE == 0
        // invert the whole thing to avoid having to conditionally !led_state.x later
        led_state.raw = ~led_state.raw;
#    endif

#    ifdef LED_NUM_LOCK_PIN
        writePin(LED_NUM_LOCK_PIN, led_state.num_lock);
#    endif
#    ifdef LED_CAPS_LOCK_PIN
        writePin(LED_CAPS_LOCK_PIN, led_state.caps_lock);
#    endif
#    ifdef LED_SCROLL_LOCK_PIN
        writePin(LED_SCROLL_LOCK_PIN, led_state.scroll_lock);
#    endif
#    ifdef LED_COMPOSE_PIN
        writePin(LED_COMPOSE_PIN, led_state.compose);
#    endif
#    ifdef LED_KANA_PIN
        writePin(LED_KANA_PIN, led_state.kana);
#    endif
#endif
    }
    return res;
}

__attribute__((weak)) void led_init_ports(void) {
#ifdef LED_NUM_LOCK_PIN
    setPinOutput(LED_NUM_LOCK_PIN);
#endif
#ifdef LED_CAPS_LOCK_PIN
    setPinOutput(LED_CAPS_LOCK_PIN);
#endif
#ifdef LED_SCROLL_LOCK_PIN
    setPinOutput(LED_SCROLL_LOCK_PIN);
#endif
#ifdef LED_COMPOSE_PIN
    setPinOutput(LED_COMPOSE_PIN);
#endif
#ifdef LED_KANA_PIN
    setPinOutput(LED_KANA_PIN);
#endif
}

__attribute__((weak)) void led_set(uint8_t usb_led) {
#if defined(BACKLIGHT_CAPS_LOCK) && defined(BACKLIGHT_ENABLE)
    // Use backlight as Caps Lock indicator
    uint8_t bl_toggle_lvl = 0;

    if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK) && !backlight_config.enable) {
        // Turning Caps Lock ON and backlight is disabled in config
        // Toggling backlight to the brightest level
        bl_toggle_lvl = BACKLIGHT_LEVELS;
    } else if (IS_LED_OFF(usb_led, USB_LED_CAPS_LOCK) && backlight_config.enable) {
        // Turning Caps Lock OFF and backlight is enabled in config
        // Toggling backlight and restoring config level
        bl_toggle_lvl = backlight_config.level;
    }

    // Set level without modify backlight_config to keep ability to restore state
    backlight_set(bl_toggle_lvl);
#endif

    led_set_kb(usb_led);
    led_update_kb((led_t)usb_led);
}