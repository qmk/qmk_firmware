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

#include "quantum.h"
#include "backlight.h"
#include "eeconfig.h"
#include "debug.h"

backlight_config_t backlight_config;

#ifdef BACKLIGHT_BREATHING
// TODO: migrate to backlight_config_t
static uint8_t breathing_period = BREATHING_PERIOD;
#endif

#ifndef BACKLIGHT_CUSTOM_DRIVER
#    if defined(BACKLIGHT_PINS)
static const pin_t backlight_pins[] = BACKLIGHT_PINS;
#        ifndef BACKLIGHT_LED_COUNT
#            define BACKLIGHT_LED_COUNT (sizeof(backlight_pins) / sizeof(pin_t))
#        endif

#        define FOR_EACH_LED(x)                                 \
            for (uint8_t i = 0; i < BACKLIGHT_LED_COUNT; i++) { \
                pin_t backlight_pin = backlight_pins[i];        \
                { x }                                           \
            }
#    else
// we support only one backlight pin
static const pin_t backlight_pin = BACKLIGHT_PIN;
#        define FOR_EACH_LED(x) x
#    endif

static inline void backlight_on(pin_t backlight_pin) {
#    if BACKLIGHT_ON_STATE == 0
    writePinLow(backlight_pin);
#    else
    writePinHigh(backlight_pin);
#    endif
}

static inline void backlight_off(pin_t backlight_pin) {
#    if BACKLIGHT_ON_STATE == 0
    writePinHigh(backlight_pin);
#    else
    writePinLow(backlight_pin);
#    endif
}

void backlight_init_pins(void) {
    // Setup backlight pin as output and output to off state.
    FOR_EACH_LED(setPinOutput(backlight_pin); backlight_off(backlight_pin);)
}

void backlight_pins_on(void) { FOR_EACH_LED(backlight_on(backlight_pin);) }

void backlight_pins_off(void) { FOR_EACH_LED(backlight_off(backlight_pin);) }

#endif

/** \brief Backlight initialization
 *
 * FIXME: needs doc
 */
void backlight_init(void) {
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
void backlight_increase(void) {
    if (backlight_config.level < BACKLIGHT_LEVELS) {
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
void backlight_decrease(void) {
    if (backlight_config.level > 0) {
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
void backlight_toggle(void) {
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
void backlight_enable(void) {
    if (backlight_config.enable) return;  // do nothing if backlight is already on

    backlight_config.enable = true;
    if (backlight_config.raw == 1)  // enabled but level == 0
        backlight_config.level = 1;
    eeconfig_update_backlight(backlight_config.raw);
    dprintf("backlight enable\n");
    backlight_set(backlight_config.level);
}

/** \brief Disable backlight
 *
 * FIXME: needs doc
 */
void backlight_disable(void) {
    if (!backlight_config.enable) return;  // do nothing if backlight is already off

    backlight_config.enable = false;
    eeconfig_update_backlight(backlight_config.raw);
    dprintf("backlight disable\n");
    backlight_set(0);
}

/** /brief Get the backlight status
 *
 * FIXME: needs doc
 */
bool is_backlight_enabled(void) { return backlight_config.enable; }

/** \brief Backlight step through levels
 *
 * FIXME: needs doc
 */
void backlight_step(void) {
    backlight_config.level++;
    if (backlight_config.level > BACKLIGHT_LEVELS) {
        backlight_config.level = 0;
    }
    backlight_config.enable = !!backlight_config.level;
    eeconfig_update_backlight(backlight_config.raw);
    dprintf("backlight step: %u\n", backlight_config.level);
    backlight_set(backlight_config.level);
}

/** \brief Backlight set level without EEPROM update
 *
 */
void backlight_level_noeeprom(uint8_t level) {
    if (level > BACKLIGHT_LEVELS) level = BACKLIGHT_LEVELS;
    backlight_config.level  = level;
    backlight_config.enable = !!backlight_config.level;
    backlight_set(backlight_config.level);
}

/** \brief Backlight set level
 *
 * FIXME: needs doc
 */
void backlight_level(uint8_t level) {
    backlight_level_noeeprom(level);
    eeconfig_update_backlight(backlight_config.raw);
}

/** \brief Update current backlight state to EEPROM
 *
 */
void eeconfig_update_backlight_current(void) { eeconfig_update_backlight(backlight_config.raw); }

/** \brief Get backlight level
 *
 * FIXME: needs doc
 */
uint8_t get_backlight_level(void) { return backlight_config.level; }

#ifdef BACKLIGHT_BREATHING
/** \brief Backlight breathing toggle
 *
 * FIXME: needs doc
 */
void backlight_toggle_breathing(void) {
    bool breathing = backlight_config.breathing;
    dprintf("backlight breathing toggle: %u\n", breathing);
    if (breathing)
        backlight_disable_breathing();
    else
        backlight_enable_breathing();
}

/** \brief Enable backlight breathing
 *
 * FIXME: needs doc
 */
void backlight_enable_breathing(void) {
    if (backlight_config.breathing) return;  // do nothing if breathing is already on

    backlight_config.breathing = true;
    eeconfig_update_backlight(backlight_config.raw);
    dprintf("backlight breathing enable\n");
    breathing_enable();
}

/** \brief Disable backlight breathing
 *
 * FIXME: needs doc
 */
void backlight_disable_breathing(void) {
    if (!backlight_config.breathing) return;  // do nothing if breathing is already off

    backlight_config.breathing = false;
    eeconfig_update_backlight(backlight_config.raw);
    dprintf("backlight breathing disable\n");
    breathing_disable();
}

/** \brief Get the backlight breathing status
 *
 * FIXME: needs doc
 */
bool is_backlight_breathing(void) { return backlight_config.breathing; }

// following are marked as weak purely for backwards compatibility
__attribute__((weak)) void breathing_period_set(uint8_t value) { breathing_period = value ? value : 1; }

__attribute__((weak)) uint8_t get_breathing_period(void) { return breathing_period; }

__attribute__((weak)) void breathing_period_default(void) { breathing_period_set(BREATHING_PERIOD); }

__attribute__((weak)) void breathing_period_inc(void) { breathing_period_set(breathing_period + 1); }

__attribute__((weak)) void breathing_period_dec(void) { breathing_period_set(breathing_period - 1); }

__attribute__((weak)) void breathing_toggle(void) {
    if (is_breathing())
        breathing_disable();
    else
        breathing_enable();
}

#endif

// defaults for backlight api
__attribute__((weak)) void backlight_init_ports(void) {}

__attribute__((weak)) void backlight_set(uint8_t level) {}

__attribute__((weak)) void backlight_task(void) {}
