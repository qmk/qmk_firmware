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
#include "haptic.h"
#include "eeconfig.h"
#include "debug.h"
#include "usb_device_state.h"
#include "gpio.h"
#ifdef DRV2605L
#    include "DRV2605L.h"
#endif
#ifdef SOLENOID_ENABLE
#    include "solenoid.h"
#endif
#if defined(SPLIT_KEYBOARD) && defined(SPLIT_HAPTIC_ENABLE)
extern uint8_t split_haptic_play;
#endif

haptic_config_t haptic_config;

static void update_haptic_enable_gpios(void) {
    if (haptic_config.enable && ((!HAPTIC_OFF_IN_LOW_POWER) || (usb_device_state == USB_DEVICE_STATE_CONFIGURED))) {
#if defined(HAPTIC_ENABLE_PIN)
        HAPTIC_ENABLE_PIN_WRITE_ACTIVE();
#endif
#if defined(HAPTIC_ENABLE_STATUS_LED)
        HAPTIC_ENABLE_STATUS_LED_WRITE_ACTIVE();
#endif
    } else {
#if defined(HAPTIC_ENABLE_PIN)
        HAPTIC_ENABLE_PIN_WRITE_INACTIVE();
#endif
#if defined(HAPTIC_ENABLE_STATUS_LED)
        HAPTIC_ENABLE_STATUS_LED_WRITE_INACTIVE();
#endif
    }
}

static void set_haptic_config_enable(bool enabled) {
    haptic_config.enable = enabled;
    update_haptic_enable_gpios();
}

void haptic_init(void) {
    if (!eeconfig_is_enabled()) {
        eeconfig_init();
    }
    haptic_config.raw = eeconfig_read_haptic();
#ifdef SOLENOID_ENABLE
    solenoid_set_dwell(haptic_config.dwell);
#endif
    if ((haptic_config.raw == 0)
#ifdef SOLENOID_ENABLE
        || (haptic_config.dwell == 0)
#endif
    ) {
        // this will be called, if the eeprom is not corrupt,
        // but the previous firmware didn't have haptic enabled,
        // or the previous firmware didn't have solenoid enabled,
        // and the current one has solenoid enabled.
        haptic_reset();
    } else {
        // Haptic configuration has been loaded through the "raw" union item.
        // This is to execute any side effects of the configuration.
        set_haptic_config_enable(haptic_config.enable);
    }
#ifdef SOLENOID_ENABLE
    solenoid_setup();
    dprintf("Solenoid driver initialized\n");
#endif
#ifdef DRV2605L
    DRV_init();
    dprintf("DRV2605 driver initialized\n");
#endif
    eeconfig_debug_haptic();
#ifdef HAPTIC_ENABLE_PIN
    setPinOutput(HAPTIC_ENABLE_PIN);
#endif
#ifdef HAPTIC_ENABLE_STATUS_LED
    setPinOutput(HAPTIC_ENABLE_STATUS_LED);
#endif
}

void haptic_task(void) {
#ifdef SOLENOID_ENABLE
    solenoid_check();
#endif
}

void eeconfig_debug_haptic(void) {
    dprintf("haptic_config eeprom\n");
    dprintf("haptic_config.enable = %d\n", haptic_config.enable);
    dprintf("haptic_config.mode = %d\n", haptic_config.mode);
}

void haptic_enable(void) {
    set_haptic_config_enable(true);
    xprintf("haptic_config.enable = %u\n", haptic_config.enable);
    eeconfig_update_haptic(haptic_config.raw);
}

void haptic_disable(void) {
    set_haptic_config_enable(false);
    xprintf("haptic_config.enable = %u\n", haptic_config.enable);
    eeconfig_update_haptic(haptic_config.raw);
}

void haptic_toggle(void) {
    if (haptic_config.enable) {
        haptic_disable();
    } else {
        haptic_enable();
    }
    eeconfig_update_haptic(haptic_config.raw);
}

void haptic_feedback_toggle(void) {
    haptic_config.feedback++;
    if (haptic_config.feedback >= HAPTIC_FEEDBACK_MAX) haptic_config.feedback = KEY_PRESS;
    xprintf("haptic_config.feedback = %u\n", !haptic_config.feedback);
    eeconfig_update_haptic(haptic_config.raw);
}

void haptic_buzz_toggle(void) {
    bool buzz_stat     = !haptic_config.buzz;
    haptic_config.buzz = buzz_stat;
    haptic_set_buzz(buzz_stat);
}

void haptic_mode_increase(void) {
    uint8_t mode = haptic_config.mode + 1;
#ifdef DRV2605L
    if (haptic_config.mode >= drv_effect_max) {
        mode = 1;
    }
#endif
    haptic_set_mode(mode);
}

void haptic_mode_decrease(void) {
    uint8_t mode = haptic_config.mode - 1;
#ifdef DRV2605L
    if (haptic_config.mode < 1) {
        mode = (drv_effect_max - 1);
    }
#endif
    haptic_set_mode(mode);
}

void haptic_dwell_increase(void) {
#ifdef SOLENOID_ENABLE
    int16_t next_dwell = ((int16_t)haptic_config.dwell) + SOLENOID_DWELL_STEP_SIZE;
    if (haptic_config.dwell >= SOLENOID_MAX_DWELL) {
        // if it's already at max, we wrap back to min
        next_dwell = SOLENOID_MIN_DWELL;
    } else if (next_dwell > SOLENOID_MAX_DWELL) {
        // if we overshoot the max, then cap at max
        next_dwell = SOLENOID_MAX_DWELL;
    }
    solenoid_set_dwell(next_dwell);
#else
    int16_t next_dwell = ((int16_t)haptic_config.dwell) + 1;
#endif
    haptic_set_dwell(next_dwell);
}

void haptic_dwell_decrease(void) {
#ifdef SOLENOID_ENABLE
    int16_t next_dwell = ((int16_t)haptic_config.dwell) - SOLENOID_DWELL_STEP_SIZE;
    if (haptic_config.dwell <= SOLENOID_MIN_DWELL) {
        // if it's already at min, we wrap to max
        next_dwell = SOLENOID_MAX_DWELL;
    } else if (next_dwell < SOLENOID_MIN_DWELL) {
        // if we go below min, then we cap to min
        next_dwell = SOLENOID_MIN_DWELL;
    }
    solenoid_set_dwell(next_dwell);
#else
    int16_t next_dwell = ((int16_t)haptic_config.dwell) - 1;
#endif
    haptic_set_dwell(next_dwell);
}

void haptic_reset(void) {
    set_haptic_config_enable(true);
    uint8_t feedback       = HAPTIC_FEEDBACK_DEFAULT;
    haptic_config.feedback = feedback;
#ifdef DRV2605L
    uint8_t mode       = HAPTIC_MODE_DEFAULT;
    haptic_config.mode = mode;
#endif
#ifdef SOLENOID_ENABLE
    uint8_t dwell       = SOLENOID_DEFAULT_DWELL;
    haptic_config.dwell = dwell;
    haptic_config.buzz  = SOLENOID_DEFAULT_BUZZ;
    solenoid_set_dwell(dwell);
#else
    // This is to trigger haptic_reset again, if solenoid is enabled in the future.
    haptic_config.dwell = 0;
    haptic_config.buzz  = 0;
#endif
    eeconfig_update_haptic(haptic_config.raw);
    xprintf("haptic_config.feedback = %u\n", haptic_config.feedback);
    xprintf("haptic_config.mode = %u\n", haptic_config.mode);
}

void haptic_set_feedback(uint8_t feedback) {
    haptic_config.feedback = feedback;
    eeconfig_update_haptic(haptic_config.raw);
    xprintf("haptic_config.feedback = %u\n", haptic_config.feedback);
}

void haptic_set_mode(uint8_t mode) {
    haptic_config.mode = mode;
    eeconfig_update_haptic(haptic_config.raw);
    xprintf("haptic_config.mode = %u\n", haptic_config.mode);
}

void haptic_set_amplitude(uint8_t amp) {
    haptic_config.amplitude = amp;
    eeconfig_update_haptic(haptic_config.raw);
    xprintf("haptic_config.amplitude = %u\n", haptic_config.amplitude);
#ifdef DRV2605L
    DRV_amplitude(amp);
#endif
}

void haptic_set_buzz(uint8_t buzz) {
    haptic_config.buzz = buzz;
    eeconfig_update_haptic(haptic_config.raw);
    xprintf("haptic_config.buzz = %u\n", haptic_config.buzz);
}

void haptic_set_dwell(uint8_t dwell) {
    haptic_config.dwell = dwell;
    eeconfig_update_haptic(haptic_config.raw);
    xprintf("haptic_config.dwell = %u\n", haptic_config.dwell);
}

uint8_t haptic_get_enable(void) {
    return haptic_config.enable;
}

uint8_t haptic_get_mode(void) {
    if (!haptic_config.enable) {
        return false;
    }
    return haptic_config.mode;
}

uint8_t haptic_get_feedback(void) {
    if (!haptic_config.enable) {
        return false;
    }
    return haptic_config.feedback;
}

uint8_t haptic_get_dwell(void) {
    if (!haptic_config.enable) {
        return false;
    }
    return haptic_config.dwell;
}

void haptic_enable_continuous(void) {
    haptic_config.cont = 1;
    xprintf("haptic_config.cont = %u\n", haptic_config.cont);
    eeconfig_update_haptic(haptic_config.raw);
#ifdef DRV2605L
    DRV_rtp_init();
#endif
}

void haptic_disable_continuous(void) {
    haptic_config.cont = 0;
    xprintf("haptic_config.cont = %u\n", haptic_config.cont);
    eeconfig_update_haptic(haptic_config.raw);
#ifdef DRV2605L
    DRV_write(DRV_MODE, 0x00);
#endif
}

void haptic_toggle_continuous(void) {
    if (haptic_config.cont) {
        haptic_disable_continuous();
    } else {
        haptic_enable_continuous();
    }
}

void haptic_cont_increase(void) {
    uint8_t amp = haptic_config.amplitude + 10;
    if (haptic_config.amplitude >= 120) {
        amp = 120;
    }
    haptic_set_amplitude(amp);
}

void haptic_cont_decrease(void) {
    uint8_t amp = haptic_config.amplitude - 10;
    if (haptic_config.amplitude < 20) {
        amp = 20;
    }
    haptic_set_amplitude(amp);
}

void haptic_play(void) {
#ifdef DRV2605L
    uint8_t play_eff = 0;
    play_eff         = haptic_config.mode;
    DRV_pulse(play_eff);
#    if defined(SPLIT_KEYBOARD) && defined(SPLIT_HAPTIC_ENABLE)
    split_haptic_play = haptic_config.mode;
#    endif
#endif
#ifdef SOLENOID_ENABLE
    solenoid_fire_handler();
#    if defined(SPLIT_KEYBOARD) && defined(SPLIT_HAPTIC_ENABLE)
    split_haptic_play = 1;
#    endif
#endif
}

void haptic_shutdown(void) {
#ifdef SOLENOID_ENABLE
    solenoid_shutdown();
#endif
}

void haptic_notify_usb_device_state_change(void) {
    update_haptic_enable_gpios();
#if defined(HAPTIC_ENABLE_PIN)
    setPinOutput(HAPTIC_ENABLE_PIN);
#endif
#if defined(HAPTIC_ENABLE_STATUS_LED)
    setPinOutput(HAPTIC_ENABLE_STATUS_LED);
#endif
}
