/* Copyright 2019 Rys Sommefeldt
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
#include QMK_KEYBOARD_H
#include "tmk_core/common/eeprom.h"
#include "led_control.h"

bool is_magic_valid(void) {
    return eeprom_read_byte((void*)THINK65_LED_EEPROM_BASE_ADDR) == THINK65_LED_EEPROM_MAGIC_BYTE;
}

void set_magic_value(void) {
    eeprom_update_byte((void*)THINK65_LED_EEPROM_BASE_ADDR, THINK65_LED_EEPROM_MAGIC_BYTE);
}

uint8_t read_magic_value(void) {
    return eeprom_read_byte((void*)THINK65_LED_EEPROM_BASE_ADDR);
}

void print_led_config(void) {
#ifdef CONSOLE_ENABLE
    uprintf("Magic     %d\n", read_magic_value());
    uprintf("LED state %d\n", user_config.current_led_state);
    uprintf("Escape    hsv(%d, %d, %d)\n", think65_led_config.esc_h,
                                           think65_led_config.esc_s,
                                           think65_led_config.esc_v);
    uprintf("Badge     hsv(%d, %d, %d)\n", think65_led_config.badge_h,
                                           think65_led_config.badge_s,
                                           think65_led_config.badge_v);
    uprintf("Underglow hsv(%d, %d, %d)\n", think65_led_config.underglow_h,
                                           think65_led_config.underglow_s,
                                           think65_led_config.underglow_v);
#endif
}

void clear_led_config(void) {
    // Clear to HSV_WHITE (0, 0, 255)
    think65_led_config.esc_h       = (uint8_t)0;
    think65_led_config.esc_s       = (uint8_t)0;
    think65_led_config.esc_v       = (uint8_t)255;
    think65_led_config.badge_h     = (uint8_t)0;
    think65_led_config.badge_s     = (uint8_t)0;
    think65_led_config.badge_v     = (uint8_t)255;
    think65_led_config.underglow_h = (uint8_t)0;
    think65_led_config.underglow_s = (uint8_t)0;
    think65_led_config.underglow_v = (uint8_t)255;
}

void read_led_config(void) {
    think65_led_config.esc_h =       (uint8_t)eeprom_read_byte(THINK65_LED_EEPROM_BASE_ADDR +
                                                               THINK65_LED_EEPROM_ESC_ADDR  +
                                                               THINK65_LED_EEPROM_H_BYTE);
    think65_led_config.esc_s =       (uint8_t)eeprom_read_byte(THINK65_LED_EEPROM_BASE_ADDR +
                                                               THINK65_LED_EEPROM_ESC_ADDR  +
                                                               THINK65_LED_EEPROM_S_BYTE);
    think65_led_config.esc_v =       (uint8_t)eeprom_read_byte(THINK65_LED_EEPROM_BASE_ADDR +
                                                               THINK65_LED_EEPROM_ESC_ADDR  +
                                                               THINK65_LED_EEPROM_V_BYTE);

    think65_led_config.badge_h =     (uint8_t)eeprom_read_byte(THINK65_LED_EEPROM_BASE_ADDR  +
                                                               THINK65_LED_EEPROM_BADGE_ADDR +
                                                               THINK65_LED_EEPROM_H_BYTE);
    think65_led_config.badge_s =     (uint8_t)eeprom_read_byte(THINK65_LED_EEPROM_BASE_ADDR  +
                                                               THINK65_LED_EEPROM_BADGE_ADDR +
                                                               THINK65_LED_EEPROM_S_BYTE);
    think65_led_config.badge_v =     (uint8_t)eeprom_read_byte(THINK65_LED_EEPROM_BASE_ADDR  +
                                                               THINK65_LED_EEPROM_BADGE_ADDR +
                                                               THINK65_LED_EEPROM_V_BYTE);

    think65_led_config.underglow_h = (uint8_t)eeprom_read_byte(THINK65_LED_EEPROM_BASE_ADDR      +
                                                               THINK65_LED_EEPROM_UNDERGLOW_ADDR +
                                                               THINK65_LED_EEPROM_H_BYTE);
    think65_led_config.underglow_s = (uint8_t)eeprom_read_byte(THINK65_LED_EEPROM_BASE_ADDR      +
                                                               THINK65_LED_EEPROM_UNDERGLOW_ADDR +
                                                               THINK65_LED_EEPROM_S_BYTE);
    think65_led_config.underglow_v = (uint8_t)eeprom_read_byte(THINK65_LED_EEPROM_BASE_ADDR      +
                                                               THINK65_LED_EEPROM_UNDERGLOW_ADDR +
                                                               THINK65_LED_EEPROM_V_BYTE);
}

void save_led_config(void) {
    eeprom_update_byte(THINK65_LED_EEPROM_BASE_ADDR +
                       THINK65_LED_EEPROM_ESC_ADDR +
                       THINK65_LED_EEPROM_H_BYTE, (uint8_t)think65_led_config.esc_h);
    eeprom_update_byte(THINK65_LED_EEPROM_BASE_ADDR +
                       THINK65_LED_EEPROM_ESC_ADDR +
                       THINK65_LED_EEPROM_S_BYTE, (uint8_t)think65_led_config.esc_s);
    eeprom_update_byte(THINK65_LED_EEPROM_BASE_ADDR +
                       THINK65_LED_EEPROM_ESC_ADDR +
                       THINK65_LED_EEPROM_V_BYTE, (uint8_t)think65_led_config.esc_v);

    eeprom_update_byte(THINK65_LED_EEPROM_BASE_ADDR +
                       THINK65_LED_EEPROM_BADGE_ADDR +
                       THINK65_LED_EEPROM_H_BYTE, (uint8_t)think65_led_config.badge_h);
    eeprom_update_byte(THINK65_LED_EEPROM_BASE_ADDR +
                       THINK65_LED_EEPROM_BADGE_ADDR +
                       THINK65_LED_EEPROM_S_BYTE, (uint8_t)think65_led_config.badge_s);
    eeprom_update_byte(THINK65_LED_EEPROM_BASE_ADDR +
                       THINK65_LED_EEPROM_BADGE_ADDR +
                       THINK65_LED_EEPROM_V_BYTE, (uint8_t)think65_led_config.badge_v);

    eeprom_update_byte(THINK65_LED_EEPROM_BASE_ADDR +
                       THINK65_LED_EEPROM_UNDERGLOW_ADDR +
                       THINK65_LED_EEPROM_H_BYTE, (uint8_t)think65_led_config.underglow_h);
    eeprom_update_byte(THINK65_LED_EEPROM_BASE_ADDR +
                       THINK65_LED_EEPROM_UNDERGLOW_ADDR +
                       THINK65_LED_EEPROM_S_BYTE, (uint8_t)think65_led_config.underglow_s);
    eeprom_update_byte(THINK65_LED_EEPROM_BASE_ADDR +
                       THINK65_LED_EEPROM_UNDERGLOW_ADDR +
                       THINK65_LED_EEPROM_V_BYTE, (uint8_t)think65_led_config.underglow_v);
}

// toggle one of the range flag bits
void toggle_led_state(unsigned int led_range) {
    if (led_range >= THINK65_LED_ESC_RANGE_BIT && led_range <= THINK65_LED_UNDERGLOW_RANGE_BIT) {
        user_config.current_led_state ^= 1 << led_range;
    }
}

// set one of the range flag bits
void set_led_state(unsigned int led_range) {
    if (led_range >= THINK65_LED_ESC_RANGE_BIT && led_range <= THINK65_LED_UNDERGLOW_RANGE_BIT) {
        user_config.current_led_state |= 1 << led_range;
    }
}

// clear one of the range flag bits
void clear_led_state(unsigned int led_range) {
    if (led_range >= THINK65_LED_ESC_RANGE_BIT && led_range <= THINK65_LED_UNDERGLOW_RANGE_BIT) {
        user_config.current_led_state &= ~(1 << led_range);
    }
}

// cycle LED states: Off -> Esc -> Badge -> Underglow -> Esc+Badge -> Esc+Underglow -> Badge+Underglow -> All
void cycle_led_state(void) {
    switch(user_config.current_led_state) {
        case THINK65_LED_STATE_OFF:
            user_config.current_led_state = THINK65_LED_STATE_ESC;
            break;
        case THINK65_LED_STATE_ESC:
            user_config.current_led_state = THINK65_LED_STATE_BADGE;
            break;
        case THINK65_LED_STATE_BADGE:
            user_config.current_led_state = THINK65_LED_STATE_UNDERGLOW;
            break;
        case THINK65_LED_STATE_UNDERGLOW:
            user_config.current_led_state = THINK65_LED_STATE_ESC_AND_BADGE;
            break;
        case THINK65_LED_STATE_ESC_AND_BADGE:
            user_config.current_led_state = THINK65_LED_STATE_ESC_AND_UNDERGLOW;
            break;
        case THINK65_LED_STATE_ESC_AND_UNDERGLOW:
            user_config.current_led_state = THINK65_LED_STATE_BADGE_AND_UNDERGLOW;
            break;
        case THINK65_LED_STATE_BADGE_AND_UNDERGLOW:
            user_config.current_led_state = THINK65_LED_STATE_ON;
            break;
        case THINK65_LED_STATE_ON:
            user_config.current_led_state = THINK65_LED_STATE_OFF;
            break;
        default:
            break;
    }
}

void apply_led_state(void) {
    uint8_t esc_h = think65_led_config.esc_h;
    uint8_t esc_s = think65_led_config.esc_s;
    uint8_t esc_v = think65_led_config.esc_v;
    uint8_t bdg_h = think65_led_config.badge_h;
    uint8_t bdg_s = think65_led_config.badge_s;
    uint8_t bdg_v = think65_led_config.badge_v;
    uint8_t ugl_h = think65_led_config.underglow_h;
    uint8_t ugl_s = think65_led_config.underglow_s;
    uint8_t ugl_v = think65_led_config.underglow_v;

    // Set the RGB ranges based on the current state
    switch(user_config.current_led_state) {
        case THINK65_LED_STATE_OFF:
            rgblight_sethsv_range(THINK65_LEDS_OFF,    THINK65_LED_RANGE_ALL);
            break;
        case THINK65_LED_STATE_ESC:
            rgblight_sethsv_range(esc_h, esc_s, esc_v, THINK65_LED_RANGE_ESC);
            rgblight_sethsv_range(THINK65_LEDS_OFF,    THINK65_LED_RANGE_BADGE);
            rgblight_sethsv_range(THINK65_LEDS_OFF,    THINK65_LED_RANGE_UNDERGLOW);
            break;
        case THINK65_LED_STATE_BADGE:
            rgblight_sethsv_range(THINK65_LEDS_OFF,    THINK65_LED_RANGE_ESC);
            rgblight_sethsv_range(bdg_h, bdg_s, bdg_v, THINK65_LED_RANGE_BADGE);
            rgblight_sethsv_range(THINK65_LEDS_OFF,    THINK65_LED_RANGE_UNDERGLOW);
            break;
        case THINK65_LED_STATE_UNDERGLOW:
            rgblight_sethsv_range(THINK65_LEDS_OFF,    THINK65_LED_RANGE_ESC);
            rgblight_sethsv_range(THINK65_LEDS_OFF,    THINK65_LED_RANGE_BADGE);
            rgblight_sethsv_range(ugl_h, ugl_s, ugl_v, THINK65_LED_RANGE_UNDERGLOW);
            break;
        case THINK65_LED_STATE_ESC_AND_BADGE:
            rgblight_sethsv_range(esc_h, esc_s, esc_v, THINK65_LED_RANGE_ESC);
            rgblight_sethsv_range(bdg_h, bdg_s, bdg_v, THINK65_LED_RANGE_BADGE);
            rgblight_sethsv_range(THINK65_LEDS_OFF,    THINK65_LED_RANGE_UNDERGLOW);
            break;
        case THINK65_LED_STATE_ESC_AND_UNDERGLOW:
            rgblight_sethsv_range(esc_h, esc_s, esc_v, THINK65_LED_RANGE_ESC);
            rgblight_sethsv_range(THINK65_LEDS_OFF,    THINK65_LED_RANGE_BADGE);
            rgblight_sethsv_range(ugl_h, ugl_s, ugl_v, THINK65_LED_RANGE_UNDERGLOW);
            break;
        case THINK65_LED_STATE_BADGE_AND_UNDERGLOW:
            rgblight_sethsv_range(THINK65_LEDS_OFF,    THINK65_LED_RANGE_ESC);
            rgblight_sethsv_range(bdg_h, bdg_s, bdg_v, THINK65_LED_RANGE_BADGE);
            rgblight_sethsv_range(ugl_h, ugl_s, ugl_v, THINK65_LED_RANGE_UNDERGLOW);
            break;
        case THINK65_LED_STATE_ON:
            rgblight_sethsv_range(esc_h, esc_s, esc_v, THINK65_LED_RANGE_ESC);
            rgblight_sethsv_range(bdg_h, bdg_s, bdg_v, THINK65_LED_RANGE_BADGE);
            rgblight_sethsv_range(ugl_h, ugl_s, ugl_v, THINK65_LED_RANGE_UNDERGLOW);
            break;
        default:
            break;
    }

    print_led_config();
}

void setup_led_range_control(void) {
    user_config.raw = eeconfig_read_user();

    if (user_config.current_led_state >= THINK65_LED_STATE_OFF && user_config.current_led_state <= THINK65_LED_STATE_ON) {
        // If we find a good LED range state in the user EEPROM

        if (is_magic_valid()) {
            // Try and get a valid colour configuration out of the EEPROM space we use
            read_led_config();
        } else {
            // It's invalid, so write a fresh one
            set_magic_value();
            clear_led_config();
            save_led_config();
        }

        // Apply it
        apply_led_state();
    } else {
        // Setup a new default state of all on
        user_config.current_led_state = THINK65_LED_STATE_ON;
        // Set the EEPROM magic value so we know we can safely read the values
        set_magic_value();
        // Then clear the colour set and save it
        clear_led_config();
        save_led_config();
        // Then apply that new default state and colour set
        apply_led_state();
        // Then save the state to user EEPROM
        eeconfig_update_user(user_config.raw);
    }
}

bool process_led_range_control_codes(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CYC_LED:
            if (record->event.pressed) {
                cycle_led_state();
                apply_led_state();
                eeconfig_update_user(user_config.raw);
            }
            break;
        case TOG_ESC:
            if (record->event.pressed) {
                toggle_led_state(THINK65_LED_ESC_RANGE_BIT);
                apply_led_state();
                eeconfig_update_user(user_config.raw);
            }
            break;
        case TOG_BDG:
            if (record->event.pressed) {
                toggle_led_state(THINK65_LED_BADGE_RANGE_BIT);
                apply_led_state();
                eeconfig_update_user(user_config.raw);
            }
            break;
        case TOG_UGL:
            if (record->event.pressed) {
                toggle_led_state(THINK65_LED_UNDERGLOW_RANGE_BIT);
                apply_led_state();
                eeconfig_update_user(user_config.raw);
            }
            break;
        case ESC_HUI:
            if (record->event.pressed) {
                think65_led_config.esc_h += RGBLIGHT_HUE_STEP / 2;
                apply_led_state();
                save_led_config();
            }
            break;
        case ESC_HUD:
            if (record->event.pressed) {
                think65_led_config.esc_h -= RGBLIGHT_HUE_STEP / 2;
                apply_led_state();
                save_led_config();
            }
            break;
        case ESC_SAI:
            if (record->event.pressed) {
                think65_led_config.esc_s += RGBLIGHT_SAT_STEP / 2;
                apply_led_state();
                save_led_config();
            }
            break;
        case ESC_SAD:
            if (record->event.pressed) {
                think65_led_config.esc_s -= RGBLIGHT_SAT_STEP / 2;
                apply_led_state();
                save_led_config();
            }
            break;
        case ESC_VAI:
            if (record->event.pressed) {
                think65_led_config.esc_v += RGBLIGHT_VAL_STEP / 2;
                apply_led_state();
                save_led_config();
            }
            break;
        case ESC_VAD:
            if (record->event.pressed) {
                think65_led_config.esc_v -= RGBLIGHT_VAL_STEP / 2;
                apply_led_state();
                save_led_config();
            }
            break;
        case BDG_HUI:
            if (record->event.pressed) {
                think65_led_config.badge_h += RGBLIGHT_HUE_STEP / 2;
                apply_led_state();
                save_led_config();
            }
            break;
        case BDG_HUD:
            if (record->event.pressed) {
                think65_led_config.badge_h -= RGBLIGHT_HUE_STEP / 2;
                apply_led_state();
                save_led_config();
            }
            break;
        case BDG_SAI:
            if (record->event.pressed) {
                think65_led_config.badge_s += RGBLIGHT_SAT_STEP / 2;
                apply_led_state();
                save_led_config();
            }
            break;
        case BDG_SAD:
            if (record->event.pressed) {
                think65_led_config.badge_s -= RGBLIGHT_SAT_STEP / 2;
                apply_led_state();
                save_led_config();
            }
            break;
        case BDG_VAI:
            if (record->event.pressed) {
                think65_led_config.badge_v += RGBLIGHT_VAL_STEP / 2;
                apply_led_state();
                save_led_config();
            }
            break;
        case BDG_VAD:
            if (record->event.pressed) {
                think65_led_config.badge_v -= RGBLIGHT_VAL_STEP / 2;
                apply_led_state();
                save_led_config();
            }
            break;
        case UGL_HUI:
            if (record->event.pressed) {
                think65_led_config.underglow_h += RGBLIGHT_HUE_STEP / 2;
                apply_led_state();
                save_led_config();
            }
            break;
        case UGL_HUD:
            if (record->event.pressed) {
                think65_led_config.underglow_h -= RGBLIGHT_HUE_STEP / 2;
                apply_led_state();
                save_led_config();
            }
            break;
        case UGL_SAI:
            if (record->event.pressed) {
                think65_led_config.underglow_s += RGBLIGHT_SAT_STEP / 2;
                apply_led_state();
                save_led_config();
            }
            break;
        case UGL_SAD:
            if (record->event.pressed) {
                think65_led_config.underglow_s -= RGBLIGHT_SAT_STEP / 2;
                apply_led_state();
                save_led_config();
            }
            break;
        case UGL_VAI:
            if (record->event.pressed) {
                think65_led_config.underglow_v += RGBLIGHT_VAL_STEP / 2;
                apply_led_state();
                save_led_config();
            }
            break;
        case UGL_VAD:
            if (record->event.pressed) {
                think65_led_config.underglow_v -= RGBLIGHT_VAL_STEP / 2;
                apply_led_state();
                save_led_config();
            }
            break;
        default:
            break;
    }
    return true;
}
