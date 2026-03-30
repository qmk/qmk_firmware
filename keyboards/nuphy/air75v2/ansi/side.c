// Copyright 2023 Ryodeushii (@ryodeushii)
// SPDX-License-Identifier: GPL-2.0-or-later
#include <stdint.h>
#include "ansi.h"
#include "color.h"
#include "host.h"
#include "rgb_matrix.h"
#include "timer.h"
#include "user_kb.h"
#include "side.h"
#include "common/side_table.h"
#include "common/side_effects.h"
#include "common/rf_driver.h"

// clang-format off
const uint8_t side_speed_table[5][5] = {
    [SIDE_WAVE] = {10, 14, 20, 28, 38},
    [SIDE_MIX] = {10, 14, 20, 28, 38},
    [SIDE_BREATH] = {10, 14, 20, 28, 38},
    [SIDE_STATIC] = {50, 50, 50, 50, 50},
    [SIDE_OFF] = {50, 50, 50, 50, 50},
};

const uint8_t side_light_table[6] = {
    0, 16, 32, 64, 128, 255,
};

const uint8_t side_led_index_tab[SIDE_LINE] = {
    0, 1, 2, 3, 4, 5
};

// clang-format on
bool f_charging = 1;

uint8_t  side_play_point   = 0;
uint8_t  low_bat_blink_cnt = 6;
uint8_t  side_play_cnt     = 0;
uint32_t side_play_timer   = 0;

uint8_t                r_temp, g_temp, b_temp;
extern DEV_INFO_STRUCT dev_info;
extern bool            f_bat_hold;

extern uint8_t  right_side_play_point;
extern uint8_t  rf_blink_cnt;
extern uint16_t rf_link_show_time;
extern uint8_t  right_side_play_cnt;
extern uint32_t right_side_play_timer;

RGB  side_leds[SIDE_LED_NUM] = {0};
void side_ws2812_setleds(RGB *ledarray, uint16_t leds);
void rgb_matrix_update_pwm_buffers(void);
void right_side_led_loop(void);
void set_right_side_rgb(uint8_t r, uint8_t g, uint8_t b);

// Keyboard-specific RGB implementations
void side_rgb_set_color(int index, uint8_t red, uint8_t green, uint8_t blue) {
    side_leds[index].r = red;
    side_leds[index].g = green;
    side_leds[index].b = blue;
}

void side_rgb_refresh(void) {
    side_ws2812_setleds(side_leds, SIDE_LED_NUM);
}

/**
 * @brief Adjusting the brightness of side lights.
 * @param dir: 0 - decrease, 1 - increase.
 * @note save to eeprom.
 */
void side_brightness_control(uint8_t brighten) {
    if (brighten) {
        if (keyboard_config.lights.side_brightness == 5) {
            return;
        } else
            keyboard_config.lights.side_brightness++;

    } else {
        if (keyboard_config.lights.side_brightness == 0) {
            return;
        } else
            keyboard_config.lights.side_brightness--;
    }
    save_config_to_eeprom();
}

/**
 * @brief Adjusting the speed of side lights.
 * @param dir: 0 - decrease, 1 - increase.
 * @note save to eeprom.
 */
void side_speed_control(uint8_t fast) {
    if ((keyboard_config.lights.side_speed) > LIGHT_SPEED_MAX) (keyboard_config.lights.side_speed) = LIGHT_SPEED_MAX / 2;

    if (fast) {
        if (keyboard_config.lights.side_speed) keyboard_config.lights.side_speed--;
    } else {
        if (keyboard_config.lights.side_speed < LIGHT_SPEED_MAX) keyboard_config.lights.side_speed++;
    }
    save_config_to_eeprom();
}

/**
 * @brief Switch to the next color of side lights.
 * @param dir: 0 - prev, 1 - next.
 * @note save to eeprom.
 */
void side_color_control(uint8_t dir) {
    if (keyboard_config.lights.side_mode != SIDE_WAVE) {
        if (keyboard_config.lights.side_rgb) {
            keyboard_config.lights.side_rgb   = 0;
            keyboard_config.lights.side_color = 0;
        }
    }

    if (dir) {
        if (keyboard_config.lights.side_rgb) {
            keyboard_config.lights.side_rgb = 0;

            keyboard_config.lights.side_color = 0;

        } else {
            keyboard_config.lights.side_color++;
            if (keyboard_config.lights.side_color >= LIGHT_COLOR_MAX) {
                keyboard_config.lights.side_rgb   = 1;
                keyboard_config.lights.side_color = 0;
            }
        }
    } else {
        if (keyboard_config.lights.side_rgb) {
            keyboard_config.lights.side_rgb   = 0;
            keyboard_config.lights.side_color = LIGHT_COLOR_MAX - 1;

        } else {
            keyboard_config.lights.side_color--;
            if (keyboard_config.lights.side_color >= LIGHT_COLOR_MAX) {
                keyboard_config.lights.side_rgb   = 1;
                keyboard_config.lights.side_color = 0;
            }
        }
    }
    save_config_to_eeprom();
}

/**
 * @brief Change the color mode of side lights.
 * @param dir: 0 - prev, 1 - next.
 * @note save to eeprom.
 */
void side_mode_control(uint8_t dir) {
    if (dir) {
        keyboard_config.lights.side_mode++;
        if (keyboard_config.lights.side_mode > SIDE_OFF) {
            keyboard_config.lights.side_mode = 0;
        }
    } else {
        if (keyboard_config.lights.side_mode > 0) {
            keyboard_config.lights.side_mode--;
        } else {
            keyboard_config.lights.side_mode = SIDE_OFF;
        }
    }

    side_play_point = 0;
    save_config_to_eeprom();
}

/**
 * @brief set left side leds.
 * @param ...
 */
void set_side_rgb(uint8_t r, uint8_t g, uint8_t b) {
    for (int i = 0; i < SIDE_LINE; i++)
        side_rgb_set_color(i, r >> 2, g >> 2, b >> 2);
}

void set_indicator_on_side(uint8_t r, uint8_t g, uint8_t b) {
    set_side_rgb(r, g, b);
}

/**
 * @brief sleep_sw_led_show.
 */
void sleep_sw_led_show(void)

{
    static uint32_t sleep_show_timer     = 0;
    static bool     sleep_show_flag      = false;
    static bool     usb_sleep_show_flag  = false;
    static bool     deep_sleep_show_flag = false;

    if (f_sleep_show) {
        f_sleep_show = false;

        sleep_show_timer     = timer_read32();
        sleep_show_flag      = true;
        usb_sleep_show_flag  = false;
        deep_sleep_show_flag = false;
    } else if (f_usb_sleep_show) {
        f_usb_sleep_show     = false;
        sleep_show_timer     = timer_read32();
        usb_sleep_show_flag  = true;
        sleep_show_flag      = false;
        deep_sleep_show_flag = false;
    } else if (f_deep_sleep_show) {
        f_deep_sleep_show    = false;
        sleep_show_timer     = timer_read32();
        usb_sleep_show_flag  = false;
        sleep_show_flag      = false;
        deep_sleep_show_flag = true;
    }

    if (sleep_show_flag) {
        if (keyboard_config.common.sleep_toggle) {
            r_temp = 0x00;
            g_temp = 0x80;
            b_temp = 0x00;
        } else {
            r_temp = 0x80;
            g_temp = 0x00;
            b_temp = 0x00;
        }
        if ((timer_elapsed32(sleep_show_timer) / 500) % 2 == 0) {
            set_side_rgb(r_temp, g_temp, b_temp);
        } else {
            set_side_rgb(0x00, 0x00, 0x00);
        }
        if (timer_elapsed32(sleep_show_timer) >= (3000 - 50)) {
            sleep_show_flag = false;
        }
    } else if (usb_sleep_show_flag) {
        if (keyboard_config.common.usb_sleep_toggle) {
            r_temp = 0x00;
            g_temp = 0x80;
            b_temp = 0x00;
        } else {
            r_temp = 0x80;
            g_temp = 0x00;
            b_temp = 0x00;
        }
        if ((timer_elapsed32(sleep_show_timer) / 500) % 2 == 0) {
            set_side_rgb(r_temp, g_temp, b_temp);
        } else {
            set_side_rgb(0x00, 0x00, 0x00);
        }
        if (timer_elapsed32(sleep_show_timer) >= (3000 - 50)) {
            usb_sleep_show_flag = false;
        }
    } else if (deep_sleep_show_flag) {
        if (keyboard_config.common.deep_sleep_toggle) {
            r_temp = 0x00;
            g_temp = 0x80;
            b_temp = 0x00;
        } else {
            r_temp = 0x80;
            g_temp = 0x00;
            b_temp = 0x00;
        }
        if ((timer_elapsed32(sleep_show_timer) / 500) % 2 == 0) {
            set_side_rgb(r_temp, g_temp, b_temp);
        } else {
            set_side_rgb(0x00, 0x00, 0x00);
        }
        if (timer_elapsed32(sleep_show_timer) >= (3000 - 50)) {
            deep_sleep_show_flag = false;
        }
    }
}

/**
 * @brief sys_led_show.
 */
void sys_led_show(void) {
    // TODO: debug rf_led to know how to detect num_lock
    uint8_t caps_key_led_idx = get_led_index(3, 0);
    bool    showCapsLock     = false;
    if (dev_info.link_mode == LINK_USB) {
        showCapsLock = host_keyboard_led_state().caps_lock;
    } else {
        showCapsLock = dev_info.rf_led & 0x02;
    }

    if (showCapsLock) {
        switch (keyboard_config.common.caps_indicator_type) {
            case CAPS_INDICATOR_SIDE:
                set_side_rgb(0X00, 0x80, 0x80); // highlight top-left side led to indicate caps lock enabled state

                break;
            case CAPS_INDICATOR_UNDER_KEY:
                user_set_rgb_color(caps_key_led_idx, 0, 0x80, 0x80); // 63 is CAPS_LOCK position

                break;
            case CAPS_INDICATOR_BOTH:
                set_side_rgb(0X00, 0x80, 0x80);                      // highlight top-left side led to indicate caps lock enabled state
                user_set_rgb_color(caps_key_led_idx, 0, 0x80, 0x80); // 63 is CAPS_LOCK position

                break;
            case CAPS_INDICATOR_OFF:
            default:
                break;
        }
    }
}

void bat_charging_design(uint8_t init, uint8_t r, uint8_t g, uint8_t b) {
    static uint32_t interval_timer = 0;
    static uint16_t show_mask      = 0x00;
    static bool     f_move_trend   = 0;
    uint16_t        bit_mask       = 1;
    uint8_t         i;

    if (timer_elapsed32(interval_timer) > 100) {
        interval_timer = timer_read32();

        if (f_move_trend) {
            show_mask >>= 1;
            if (show_mask == 0x1f >> (SIDE_LINE - init)) f_move_trend = 0;
        } else {
            show_mask <<= 1;
            show_mask |= 1;
            if (show_mask == 0x7f) f_move_trend = 1;
        }
    }

    for (i = 0; i < SIDE_LINE; i++) {
        if (show_mask & bit_mask) {
            side_rgb_set_color(i, r, g, b);
        } else {
            side_rgb_set_color(i, 0x00, 0x00, 0x00);
        }
        bit_mask <<= 1;
    }
}

void rf_show_design(uint8_t r, uint8_t g, uint8_t b) {
    static uint32_t interval_timer = 0;
    static uint16_t show_mask      = 0x04;
    uint16_t        show_mask_temp = 0;
    uint16_t        show_priod;

    uint16_t bit_mask = 1;
    uint8_t  i;

    if (dev_info.rf_state == RF_PAIRING)
        show_priod = 100;
    else
        show_priod = 200;

    if (timer_elapsed32(interval_timer) > show_priod) {
        interval_timer = timer_read32();

        show_mask_temp = (show_mask << 1) | (show_mask >> 1);
        show_mask_temp |= 0x04;
        show_mask |= show_mask_temp;

        if (show_mask == 0x7f) show_mask = 0x0;
    }

    for (i = 0; i < SIDE_LINE; i++) {
        if (show_mask & bit_mask) {
            side_rgb_set_color(i, r >> 2, g >> 2, b >> 2);
        } else {
            side_rgb_set_color(i, 0x00, 0x00, 0x00);
        }
        bit_mask <<= 1;
    }
}

/**
 * @brief bat_led_show - keyboard-specific implementation.
 */
void bat_led_show(void) {
    static bool bat_show_flag = true;

    static uint32_t bat_show_time    = 0;
    static uint32_t bat_sts_debounce = 0;
    static uint32_t bat_per_debounce = 0;
    static uint8_t  charge_state     = 0;
    static uint8_t  bat_percent      = 0;
    static bool     f_init           = 1;

    if (dev_info.link_mode != LINK_USB) {
        extern uint16_t rf_link_show_time;
        if (rf_link_show_time < RF_LINK_SHOW_TIME) return;

        if (dev_info.rf_state != RF_CONNECT) return;
    }

    if (f_init) {
        f_init        = 0;
        bat_show_time = timer_read32();
        charge_state  = dev_info.rf_charge;
        bat_percent   = dev_info.rf_battery;
    }

    if (charge_state != dev_info.rf_charge) {
        if (timer_elapsed32(bat_sts_debounce) > 1000) {
            if (((charge_state & 0x01) == 0) && ((dev_info.rf_charge & 0x01) != 0)) {
                bat_show_flag = true;
                f_charging    = true;
                bat_show_time = timer_read32();
            }
            charge_state = dev_info.rf_charge;
        }

    } else {
        bat_sts_debounce = timer_read32();
        if (timer_elapsed32(bat_show_time) > 5000) {
            bat_show_flag = false;

            f_charging = false;
        }
        if (charge_state == 0x03) {
            f_charging = true;
        } else if (!(charge_state & 0x01)) {
            f_charging = 0;
        }
    }

    if (bat_percent != dev_info.rf_battery) {
        if (timer_elapsed32(bat_per_debounce) > 1000) {
            bat_percent = dev_info.rf_battery;
        }
    } else {
        bat_per_debounce = timer_read32();

        if ((bat_percent < 10) && (!(charge_state & 0x01))) {
            bat_show_flag = true;
            bat_show_time = timer_read32();

            if (rgb_matrix_config.hsv.v > RGB_MATRIX_VAL_STEP) {
                rgb_matrix_config.hsv.v = RGB_MATRIX_VAL_STEP;
            }

            if (keyboard_config.lights.side_brightness > 1) {
                keyboard_config.lights.side_brightness = 1;
            }

            if (keyboard_config.lights.right_side_brightness > 1) {
                keyboard_config.lights.right_side_brightness = 1;
            }
        }
    }

    if (f_bat_hold || bat_show_flag) {
        bat_percent_led(bat_percent);
    }
}

/**
 * @brief side_led_show_kb - keyboard-specific hook called by common side_led_show.
 */
void side_led_show_kb(void) {
    sys_led_show();
    sleep_sw_led_show();

    right_side_led_loop();
}

/**
 * @brief device_reset_show.
 */
void device_reset_show(void) {
    writePinHigh(DC_BOOST_PIN);
    setPinOutput(DRIVER_SIDE_CS_PIN);
    setPinOutput(DRIVER_MATRIX_CS_PIN);

    writePinLow(DRIVER_SIDE_CS_PIN);
    writePinLow(DRIVER_MATRIX_CS_PIN);

    for (int blink_cnt = 0; blink_cnt < 3; blink_cnt++) {
        rgb_matrix_set_color_all(0x10, 0x10, 0x10);
        for (int i = 0; i < SIDE_LED_NUM; i++) {
            side_rgb_set_color(i, 0x10, 0x10, 0x10);
        }
        rgb_matrix_update_pwm_buffers();

        side_rgb_refresh();
        wait_ms(200);

        rgb_matrix_set_color_all(0x00, 0x00, 0x00);
        for (int i = 0; i < SIDE_LED_NUM; i++) {
            side_rgb_set_color(i, 0x00, 0x00, 0x00);
        }
        rgb_matrix_update_pwm_buffers();
        side_rgb_refresh();
        wait_ms(200);
    }
}

/**
 * @brief device_reset_init.
 */
void device_reset_init(void) {
    side_play_point = 0;
    side_play_cnt   = 0;
    side_play_timer = timer_read32();

    right_side_play_point = 0;
    right_side_play_cnt   = 0;
    right_side_play_timer = timer_read32();

    f_bat_hold = false;

    kb_config_reset();
}

void rgb_test_show(void) {
    writePinHigh(DC_BOOST_PIN);
    setPinOutput(DRIVER_MATRIX_CS_PIN);
    writePinLow(DRIVER_MATRIX_CS_PIN);

    rgb_matrix_set_color_all(0xFF, 0x00, 0x00);
    for (int i = 0; i < SIDE_LED_NUM; i++)
        side_rgb_set_color(i, 0xFF, 0x00, 0x00);
    rgb_matrix_update_pwm_buffers();
    side_rgb_refresh();
    wait_ms(1000);
    rgb_matrix_set_color_all(0x00, 0xFF, 0x00);
    for (int i = 0; i < SIDE_LED_NUM; i++)
        side_rgb_set_color(i, 0x00, 0xFF, 0x00);

    rgb_matrix_update_pwm_buffers();
    side_rgb_refresh();
    wait_ms(1000);
    rgb_matrix_set_color_all(0x00, 0x00, 0xFF);
    for (int i = 0; i < SIDE_LED_NUM; i++)
        side_rgb_set_color(i, 0x00, 0x00, 0xFF);
    rgb_matrix_update_pwm_buffers();
    side_rgb_refresh();
    wait_ms(1000);
}