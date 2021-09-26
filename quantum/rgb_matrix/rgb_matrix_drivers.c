/* Copyright 2018 James Laird-Wah
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

#include "rgb_matrix.h"

/* Each driver needs to define the struct
 *    const rgb_matrix_driver_t rgb_matrix_driver;
 * All members must be provided.
 * Keyboard custom drivers can define this in their own files, it should only
 * be here if shared between boards.
 */

#if defined(IS31FL3731) || defined(IS31FL3733) || defined(IS31FL3737) || defined(IS31FL3741)

#    include "i2c_master.h"

static void init(void) {
    i2c_init();
#    ifdef IS31FL3731
    IS31FL3731_init(DRIVER_ADDR_1);
#        ifdef DRIVER_ADDR_2
    IS31FL3731_init(DRIVER_ADDR_2);
#        endif
#        ifdef DRIVER_ADDR_3
    IS31FL3731_init(DRIVER_ADDR_3);
#        endif
#        ifdef DRIVER_ADDR_4
    IS31FL3731_init(DRIVER_ADDR_4);
#        endif
#    elif defined(IS31FL3733)
#        ifndef DRIVER_SYNC_1
#            define DRIVER_SYNC_1 0
#        endif
    IS31FL3733_init(DRIVER_ADDR_1, DRIVER_SYNC_1);
#        if defined DRIVER_ADDR_2 && (DRIVER_ADDR_1 != DRIVER_ADDR_2)
#            ifndef DRIVER_SYNC_2
#                define DRIVER_SYNC_2 0
#            endif
    IS31FL3733_init(DRIVER_ADDR_2, DRIVER_SYNC_2);
#        endif
#        ifdef DRIVER_ADDR_3
#            ifndef DRIVER_SYNC_3
#                define DRIVER_SYNC_3 0
#            endif
    IS31FL3733_init(DRIVER_ADDR_3, DRIVER_SYNC_3);
#        endif
#        ifdef DRIVER_ADDR_4
#            ifndef DRIVER_SYNC_4
#                define DRIVER_SYNC_4 0
#            endif
    IS31FL3733_init(DRIVER_ADDR_4, DRIVER_SYNC_4);
#        endif
#    elif defined(IS31FL3737)
    IS31FL3737_init(DRIVER_ADDR_1);
#        if defined(DRIVER_ADDR_2) && (DRIVER_ADDR_2 != DRIVER_ADDR_1)  // provides backward compatibility
    IS31FL3737_init(DRIVER_ADDR_2);
#        endif
#    else
    IS31FL3741_init(DRIVER_ADDR_1);
#    endif
    for (int index = 0; index < DRIVER_LED_TOTAL; index++) {
        bool enabled = true;
        // This only caches it for later
#    ifdef IS31FL3731
        IS31FL3731_set_led_control_register(index, enabled, enabled, enabled);
#    elif defined(IS31FL3733)
        IS31FL3733_set_led_control_register(index, enabled, enabled, enabled);
#    elif defined(IS31FL3737)
        IS31FL3737_set_led_control_register(index, enabled, enabled, enabled);
#    else
        IS31FL3741_set_led_control_register(index, enabled, enabled, enabled);
#    endif
    }
    // This actually updates the LED drivers
#    ifdef IS31FL3731
    IS31FL3731_update_led_control_registers(DRIVER_ADDR_1, 0);
#        ifdef DRIVER_ADDR_2
    IS31FL3731_update_led_control_registers(DRIVER_ADDR_2, 1);
#        endif
#        ifdef DRIVER_ADDR_3
    IS31FL3731_update_led_control_registers(DRIVER_ADDR_3, 2);
#        endif
#        ifdef DRIVER_ADDR_4
    IS31FL3731_update_led_control_registers(DRIVER_ADDR_4, 3);
#        endif
#    elif defined(IS31FL3733)
    IS31FL3733_update_led_control_registers(DRIVER_ADDR_1, 0);
#        ifdef DRIVER_ADDR_2
    IS31FL3733_update_led_control_registers(DRIVER_ADDR_2, 1);
#        endif
#        ifdef DRIVER_ADDR_3
    IS31FL3733_update_led_control_registers(DRIVER_ADDR_3, 2);
#        endif
#        ifdef DRIVER_ADDR_4
    IS31FL3733_update_led_control_registers(DRIVER_ADDR_4, 3);
#        endif
#    elif defined(IS31FL3737)
    IS31FL3737_update_led_control_registers(DRIVER_ADDR_1, 0);
#        if defined(DRIVER_ADDR_2) && (DRIVER_ADDR_2 != DRIVER_ADDR_1)  // provides backward compatibility
    IS31FL3737_update_led_control_registers(DRIVER_ADDR_2, 1);
#        endif
#    else
    IS31FL3741_update_led_control_registers(DRIVER_ADDR_1, 0);
#    endif
}

#    ifdef IS31FL3731
static void flush(void) {
    IS31FL3731_update_pwm_buffers(DRIVER_ADDR_1, 0);
#        ifdef DRIVER_ADDR_2
    IS31FL3731_update_pwm_buffers(DRIVER_ADDR_2, 1);
#        endif
#        ifdef DRIVER_ADDR_3
    IS31FL3731_update_pwm_buffers(DRIVER_ADDR_3, 2);
#        endif
#        ifdef DRIVER_ADDR_4
    IS31FL3731_update_pwm_buffers(DRIVER_ADDR_4, 3);
#        endif
}

const rgb_matrix_driver_t rgb_matrix_driver = {
    .init          = init,
    .flush         = flush,
    .set_color     = IS31FL3731_set_color,
    .set_color_all = IS31FL3731_set_color_all,
};
#    elif defined(IS31FL3733)
static void flush(void) {
    IS31FL3733_update_pwm_buffers(DRIVER_ADDR_1, 0);
#        ifdef DRIVER_ADDR_2
    IS31FL3733_update_pwm_buffers(DRIVER_ADDR_2, 1);
#        endif
#        ifdef DRIVER_ADDR_3
    IS31FL3733_update_pwm_buffers(DRIVER_ADDR_3, 2);
#        endif
#        ifdef DRIVER_ADDR_4
    IS31FL3733_update_pwm_buffers(DRIVER_ADDR_4, 3);
#        endif
}

const rgb_matrix_driver_t rgb_matrix_driver = {
    .init = init,
    .flush = flush,
    .set_color = IS31FL3733_set_color,
    .set_color_all = IS31FL3733_set_color_all,
};
#    elif defined(IS31FL3737)
static void flush(void) {
    IS31FL3737_update_pwm_buffers(DRIVER_ADDR_1, 0);
#        if defined(DRIVER_ADDR_2) && (DRIVER_ADDR_2 != DRIVER_ADDR_1)  // provides backward compatibility
    IS31FL3737_update_pwm_buffers(DRIVER_ADDR_2, 1);
#        endif
}

const rgb_matrix_driver_t rgb_matrix_driver = {
    .init = init,
    .flush = flush,
    .set_color = IS31FL3737_set_color,
    .set_color_all = IS31FL3737_set_color_all,
};
#    else
static void flush(void) {
    IS31FL3741_update_pwm_buffers(DRIVER_ADDR_1, 0);
#        if defined(DRIVER_ADDR_2) && (DRIVER_ADDR_2 != DRIVER_ADDR_1)  // provides backward compatibility
    IS31FL3741_update_pwm_buffers(DRIVER_ADDR_2, 1);
#        endif
}

const rgb_matrix_driver_t rgb_matrix_driver = {
    .init = init,
    .flush = flush,
    .set_color = IS31FL3741_set_color,
    .set_color_all = IS31FL3741_set_color_all,
};
#    endif

#elif defined(AW20216)
#    include "spi_master.h"
static void init(void) {
    spi_init();
    AW20216_init(DRIVER_1_CS, DRIVER_1_EN);
#    ifdef DRIVER_2_CS
    AW20216_init(DRIVER_2_CS, DRIVER_2_EN);
#    endif
}

static void flush(void) {
    AW20216_update_pwm_buffers(DRIVER_1_CS, 0);
#    ifdef DRIVER_2_CS
    AW20216_update_pwm_buffers(DRIVER_2_CS, 1);
#    endif
}

const rgb_matrix_driver_t rgb_matrix_driver = {
    .init          = init,
    .flush         = flush,
    .set_color     = AW20216_set_color,
    .set_color_all = AW20216_set_color_all,
};

#elif defined(WS2812)
#    if defined(RGBLIGHT_ENABLE) && !defined(RGBLIGHT_CUSTOM_DRIVER)
#        pragma message "Cannot use RGBLIGHT and RGB Matrix using WS2812 at the same time."
#        pragma message "You need to use a custom driver, or re-implement the WS2812 driver to use a different configuration."
#    endif

// LED color buffer
LED_TYPE rgb_matrix_ws2812_array[DRIVER_LED_TOTAL];

static void init(void) {}

static void flush(void) {
    // Assumes use of RGB_DI_PIN
    ws2812_setleds(rgb_matrix_ws2812_array, DRIVER_LED_TOTAL);
}

// Set an led in the buffer to a color
static inline void setled(int i, uint8_t r, uint8_t g, uint8_t b) {
    rgb_matrix_ws2812_array[i].r = r;
    rgb_matrix_ws2812_array[i].g = g;
    rgb_matrix_ws2812_array[i].b = b;
#    ifdef RGBW
    convert_rgb_to_rgbw(&rgb_matrix_ws2812_array[i]);
#    endif
}

static void setled_all(uint8_t r, uint8_t g, uint8_t b) {
    for (int i = 0; i < sizeof(rgb_matrix_ws2812_array) / sizeof(rgb_matrix_ws2812_array[0]); i++) {
        setled(i, r, g, b);
    }
}

const rgb_matrix_driver_t rgb_matrix_driver = {
    .init          = init,
    .flush         = flush,
    .set_color     = setled,
    .set_color_all = setled_all,
};
#endif
