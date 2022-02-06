/* Copyright 2019 ishtob
 * Driver for haptic feedback written for QMK
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
#include <stdint.h>
#include <stdbool.h>

#ifndef HAPTIC_FEEDBACK_DEFAULT
#    define HAPTIC_FEEDBACK_DEFAULT 0
#endif
#ifndef HAPTIC_MODE_DEFAULT
#    define HAPTIC_MODE_DEFAULT DRV_MODE_DEFAULT
#endif

/* EEPROM config settings */
typedef union {
    uint32_t raw;
    struct {
        bool    enable : 1;
        uint8_t feedback : 2;
        uint8_t mode : 7;
        bool    buzz : 1;
        uint8_t dwell : 7;
        bool    cont : 1;
        uint8_t amplitude : 8;
        uint8_t reserved : 5;
    };
} haptic_config_t;

typedef enum HAPTIC_FEEDBACK {
    KEY_PRESS,
    KEY_PRESS_RELEASE,
    KEY_RELEASE,
    HAPTIC_FEEDBACK_MAX,
} HAPTIC_FEEDBACK;

void    haptic_init(void);
void    haptic_task(void);
void    eeconfig_debug_haptic(void);
void    haptic_enable(void);
void    haptic_disable(void);
void    haptic_toggle(void);
void    haptic_feedback_toggle(void);
void    haptic_mode_increase(void);
void    haptic_mode_decrease(void);
void    haptic_mode(uint8_t mode);
void    haptic_reset(void);
void    haptic_set_feedback(uint8_t feedback);
void    haptic_set_mode(uint8_t mode);
void    haptic_set_dwell(uint8_t dwell);
void    haptic_set_buzz(uint8_t buzz);
void    haptic_buzz_toggle(void);
uint8_t haptic_get_enable(void);
uint8_t haptic_get_mode(void);
uint8_t haptic_get_feedback(void);
void    haptic_dwell_increase(void);
void    haptic_dwell_decrease(void);
void    haptic_toggle_continuous(void);
void    haptic_cont_increase(void);
void    haptic_cont_decrease(void);

void haptic_play(void);
void haptic_shutdown(void);
void haptic_notify_usb_device_state_change(void);

#ifdef HAPTIC_ENABLE_PIN_ACTIVE_LOW
#    ifndef HAPTIC_ENABLE_PIN
#        error HAPTIC_ENABLE_PIN not defined
#    endif
#    define HAPTIC_ENABLE_PIN_WRITE_ACTIVE() writePinLow(HAPTIC_ENABLE_PIN)
#    define HAPTIC_ENABLE_PIN_WRITE_INACTIVE() writePinHigh(HAPTIC_ENABLE_PIN)
#else
#    define HAPTIC_ENABLE_PIN_WRITE_ACTIVE() writePinHigh(HAPTIC_ENABLE_PIN)
#    define HAPTIC_ENABLE_PIN_WRITE_INACTIVE() writePinLow(HAPTIC_ENABLE_PIN)
#endif

#ifdef HAPTIC_ENABLE_STATUS_LED_ACTIVE_LOW
#    ifndef HAPTIC_ENABLE_STATUS_LED
#        error HAPTIC_ENABLE_STATUS_LED not defined
#    endif
#    define HAPTIC_ENABLE_STATUS_LED_WRITE_ACTIVE() writePinLow(HAPTIC_ENABLE_STATUS_LED)
#    define HAPTIC_ENABLE_STATUS_LED_WRITE_INACTIVE() writePinHigh(HAPTIC_ENABLE_STATUS_LED)
#else
#    define HAPTIC_ENABLE_STATUS_LED_WRITE_ACTIVE() writePinHigh(HAPTIC_ENABLE_STATUS_LED)
#    define HAPTIC_ENABLE_STATUS_LED_WRITE_INACTIVE() writePinLow(HAPTIC_ENABLE_STATUS_LED)
#endif

#ifndef HAPTIC_OFF_IN_LOW_POWER
#    define HAPTIC_OFF_IN_LOW_POWER 0
#endif
