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
#include "util.h"

/* Each driver needs to define the struct
 *    const rgb_matrix_driver_t rgb_matrix_driver;
 * All members must be provided.
 * Keyboard custom drivers can define this in their own files, it should only
 * be here if shared between boards.
 */

#if defined(RGB_MATRIX_IS31FL3218) || defined(RGB_MATRIX_IS31FL3731) || defined(RGB_MATRIX_IS31FL3733) || defined(RGB_MATRIX_IS31FL3736) || defined(RGB_MATRIX_IS31FL3737) || defined(RGB_MATRIX_IS31FL3741) || defined(IS31FLCOMMON) || defined(RGB_MATRIX_SNLED27351)
#    include "i2c_master.h"

static void init(void) {
    i2c_init();

#    if defined(RGB_MATRIX_IS31FL3218)
    is31fl3218_init();

#    elif defined(RGB_MATRIX_IS31FL3731)
    is31fl3731_init(IS31FL3731_I2C_ADDRESS_1);
#        if defined(IS31FL3731_I2C_ADDRESS_2)
    is31fl3731_init(IS31FL3731_I2C_ADDRESS_2);
#            if defined(IS31FL3731_I2C_ADDRESS_3)
    is31fl3731_init(IS31FL3731_I2C_ADDRESS_3);
#                if defined(IS31FL3731_I2C_ADDRESS_4)
    is31fl3731_init(IS31FL3731_I2C_ADDRESS_4);
#                endif
#            endif
#        endif

#    elif defined(RGB_MATRIX_IS31FL3733)
#        if !defined(IS31FL3733_SYNC_1)
#            define IS31FL3733_SYNC_1 0
#        endif
    is31fl3733_init(IS31FL3733_I2C_ADDRESS_1, IS31FL3733_SYNC_1);
#        if defined(IS31FL3733_I2C_ADDRESS_2)
#            if !defined(IS31FL3733_SYNC_2)
#                define IS31FL3733_SYNC_2 0
#            endif
    is31fl3733_init(IS31FL3733_I2C_ADDRESS_2, IS31FL3733_SYNC_2);
#            if defined(IS31FL3733_I2C_ADDRESS_3)
#                if !defined(IS31FL3733_SYNC_3)
#                    define IS31FL3733_SYNC_3 0
#                endif
    is31fl3733_init(IS31FL3733_I2C_ADDRESS_3, IS31FL3733_SYNC_3);
#                if defined(IS31FL3733_I2C_ADDRESS_4)
#                    if !defined(IS31FL3733_SYNC_4)
#                        define IS31FL3733_SYNC_4 0
#                    endif
    is31fl3733_init(IS31FL3733_I2C_ADDRESS_4, IS31FL3733_SYNC_4);
#                endif
#            endif
#        endif

#    elif defined(RGB_MATRIX_IS31FL3736)
    is31fl3736_init(IS31FL3736_I2C_ADDRESS_1);
#        if defined(IS31FL3736_I2C_ADDRESS_2)
    is31fl3736_init(IS31FL3736_I2C_ADDRESS_2);
#            if defined(IS31FL3736_I2C_ADDRESS_3)
    is31fl3736_init(IS31FL3736_I2C_ADDRESS_3);
#                if defined(IS31FL3736_I2C_ADDRESS_4)
    is31fl3736_init(IS31FL3736_I2C_ADDRESS_4);
#                endif
#            endif
#        endif

#    elif defined(RGB_MATRIX_IS31FL3737)
    is31fl3737_init(IS31FL3737_I2C_ADDRESS_1);
#        if defined(IS31FL3737_I2C_ADDRESS_2)
    is31fl3737_init(IS31FL3737_I2C_ADDRESS_2);
#            if defined(IS31FL3737_I2C_ADDRESS_3)
    is31fl3737_init(IS31FL3737_I2C_ADDRESS_3);
#                if defined(IS31FL3737_I2C_ADDRESS_4)
    is31fl3737_init(IS31FL3737_I2C_ADDRESS_4);
#                endif
#            endif
#        endif

#    elif defined(RGB_MATRIX_IS31FL3741)
    is31fl3741_init(IS31FL3741_I2C_ADDRESS_1);
#        if defined(IS31FL3741_I2C_ADDRESS_2)
    is31fl3741_init(IS31FL3741_I2C_ADDRESS_2);
#            if defined(IS31FL3741_I2C_ADDRESS_3)
    is31fl3741_init(IS31FL3741_I2C_ADDRESS_3);
#                if defined(IS31FL3741_I2C_ADDRESS_4)
    is31fl3741_init(IS31FL3741_I2C_ADDRESS_4);
#                endif
#            endif
#        endif

#    elif defined(IS31FLCOMMON)
    IS31FL_common_init(DRIVER_ADDR_1, ISSI_SSR_1);
#        if defined(DRIVER_ADDR_2)
    IS31FL_common_init(DRIVER_ADDR_2, ISSI_SSR_2);
#            if defined(DRIVER_ADDR_3)
    IS31FL_common_init(DRIVER_ADDR_3, ISSI_SSR_3);
#                if defined(DRIVER_ADDR_4)
    IS31FL_common_init(DRIVER_ADDR_4, ISSI_SSR_4);
#                endif
#            endif
#        endif

#    elif defined(RGB_MATRIX_SNLED27351)
    snled27351_init(SNLED27351_I2C_ADDRESS_1);
#        if defined(SNLED27351_I2C_ADDRESS_2)
    snled27351_init(SNLED27351_I2C_ADDRESS_2);
#            if defined(SNLED27351_I2C_ADDRESS_3)
    snled27351_init(SNLED27351_I2C_ADDRESS_3);
#                if defined(SNLED27351_I2C_ADDRESS_4)
    snled27351_init(SNLED27351_I2C_ADDRESS_4);
#                endif
#            endif
#        endif
#    endif

    for (int index = 0; index < RGB_MATRIX_LED_COUNT; index++) {
        bool enabled = true;

        // This only caches it for later
#    if defined(RGB_MATRIX_IS31FL3218)
        is31fl3218_set_led_control_register(index, enabled, enabled, enabled);
#    elif defined(RGB_MATRIX_IS31FL3731)
        is31fl3731_set_led_control_register(index, enabled, enabled, enabled);
#    elif defined(RGB_MATRIX_IS31FL3733)
        is31fl3733_set_led_control_register(index, enabled, enabled, enabled);
#    elif defined(RGB_MATRIX_IS31FL3736)
        is31fl3736_set_led_control_register(index, enabled, enabled, enabled);
#    elif defined(RGB_MATRIX_IS31FL3737)
        is31fl3737_set_led_control_register(index, enabled, enabled, enabled);
#    elif defined(RGB_MATRIX_IS31FL3741)
        is31fl3741_set_led_control_register(index, enabled, enabled, enabled);
#    elif defined(IS31FLCOMMON)
        IS31FL_RGB_set_scaling_buffer(index, enabled, enabled, enabled);
#    elif defined(RGB_MATRIX_SNLED27351)
        snled27351_set_led_control_register(index, enabled, enabled, enabled);
#    endif
    }

    // This actually updates the LED drivers
#    if defined(RGB_MATRIX_IS31FL3218)
    is31fl3218_update_led_control_registers();

#    elif defined(RGB_MATRIX_IS31FL3731)
    is31fl3731_update_led_control_registers(IS31FL3731_I2C_ADDRESS_1, 0);
#        if defined(IS31FL3731_I2C_ADDRESS_2)
    is31fl3731_update_led_control_registers(IS31FL3731_I2C_ADDRESS_2, 1);
#            if defined(IS31FL3731_I2C_ADDRESS_3)
    is31fl3731_update_led_control_registers(IS31FL3731_I2C_ADDRESS_3, 2);
#                if defined(IS31FL3731_I2C_ADDRESS_4)
    is31fl3731_update_led_control_registers(IS31FL3731_I2C_ADDRESS_4, 3);
#                endif
#            endif
#        endif

#    elif defined(RGB_MATRIX_IS31FL3733)
    is31fl3733_update_led_control_registers(IS31FL3733_I2C_ADDRESS_1, 0);
#        if defined(IS31FL3733_I2C_ADDRESS_2)
    is31fl3733_update_led_control_registers(IS31FL3733_I2C_ADDRESS_2, 1);
#            if defined(IS31FL3733_I2C_ADDRESS_3)
    is31fl3733_update_led_control_registers(IS31FL3733_I2C_ADDRESS_3, 2);
#                if defined(IS31FL3733_I2C_ADDRESS_4)
    is31fl3733_update_led_control_registers(IS31FL3733_I2C_ADDRESS_4, 3);
#                endif
#            endif
#        endif

#    elif defined(RGB_MATRIX_IS31FL3736)
    is31fl3736_update_led_control_registers(IS31FL3736_I2C_ADDRESS_1, 0);
#        if defined(IS31FL3736_I2C_ADDRESS_2)
    is31fl3736_update_led_control_registers(IS31FL3736_I2C_ADDRESS_2, 1);
#            if defined(IS31FL3736_I2C_ADDRESS_3)
    is31fl3736_update_led_control_registers(IS31FL3736_I2C_ADDRESS_3, 2);
#                if defined(IS31FL3736_I2C_ADDRESS_4)
    is31fl3736_update_led_control_registers(IS31FL3736_I2C_ADDRESS_4, 3);
#                endif
#            endif
#        endif

#    elif defined(RGB_MATRIX_IS31FL3737)
    is31fl3737_update_led_control_registers(IS31FL3737_I2C_ADDRESS_1, 0);
#        if defined(IS31FL3737_I2C_ADDRESS_2)
    is31fl3737_update_led_control_registers(IS31FL3737_I2C_ADDRESS_2, 1);
#            if defined(IS31FL3737_I2C_ADDRESS_3)
    is31fl3737_update_led_control_registers(IS31FL3737_I2C_ADDRESS_3, 2);
#                if defined(IS31FL3737_I2C_ADDRESS_4)
    is31fl3737_update_led_control_registers(IS31FL3737_I2C_ADDRESS_4, 3);
#                endif
#            endif
#        endif

#    elif defined(RGB_MATRIX_IS31FL3741)
    is31fl3741_update_led_control_registers(IS31FL3741_I2C_ADDRESS_1, 0);
#        if defined(IS31FL3741_I2C_ADDRESS_2)
    is31fl3741_update_led_control_registers(IS31FL3741_I2C_ADDRESS_2, 1);
#            if defined(IS31FL3741_I2C_ADDRESS_3)
    is31fl3741_update_led_control_registers(IS31FL3741_I2C_ADDRESS_3, 2);
#                if defined(IS31FL3741_I2C_ADDRESS_4)
    is31fl3741_update_led_control_registers(IS31FL3741_I2C_ADDRESS_4, 3);
#                endif
#            endif
#        endif

#    elif defined(IS31FLCOMMON)
#        ifdef ISSI_MANUAL_SCALING
    IS31FL_set_manual_scaling_buffer();
#        endif
    IS31FL_common_update_scaling_register(DRIVER_ADDR_1, 0);
#        if defined(DRIVER_ADDR_2)
    IS31FL_common_update_scaling_register(DRIVER_ADDR_2, 1);
#            if defined(DRIVER_ADDR_3)
    IS31FL_common_update_scaling_register(DRIVER_ADDR_3, 2);
#                if defined(DRIVER_ADDR_4)
    IS31FL_common_update_scaling_register(DRIVER_ADDR_4, 3);
#                endif
#            endif
#        endif

#    elif defined(RGB_MATRIX_SNLED27351)
    snled27351_update_led_control_registers(SNLED27351_I2C_ADDRESS_1, 0);
#        if defined(SNLED27351_I2C_ADDRESS_2)
    snled27351_update_led_control_registers(SNLED27351_I2C_ADDRESS_2, 1);
#            if defined(SNLED27351_I2C_ADDRESS_3)
    snled27351_update_led_control_registers(SNLED27351_I2C_ADDRESS_3, 2);
#                if defined(SNLED27351_I2C_ADDRESS_4)
    snled27351_update_led_control_registers(SNLED27351_I2C_ADDRESS_4, 3);
#                endif
#            endif
#        endif
#    endif
}

#    if defined(RGB_MATRIX_IS31FL3218)
const rgb_matrix_driver_t rgb_matrix_driver = {
    .init          = init,
    .flush         = is31fl3218_update_pwm_buffers,
    .set_color     = is31fl3218_set_color,
    .set_color_all = is31fl3218_set_color_all,
};

#    elif defined(RGB_MATRIX_IS31FL3731)
const rgb_matrix_driver_t rgb_matrix_driver = {
    .init = init,
    .flush = is31fl3731_flush,
    .set_color = is31fl3731_set_color,
    .set_color_all = is31fl3731_set_color_all,
};

#    elif defined(RGB_MATRIX_IS31FL3733)
const rgb_matrix_driver_t rgb_matrix_driver = {
    .init = init,
    .flush = is31fl3733_flush,
    .set_color = is31fl3733_set_color,
    .set_color_all = is31fl3733_set_color_all,
};

#    elif defined(RGB_MATRIX_IS31FL3736)
const rgb_matrix_driver_t rgb_matrix_driver = {
    .init = init,
    .flush = is31fl3736_flush,
    .set_color = is31fl3736_set_color,
    .set_color_all = is31fl3736_set_color_all,
};

#    elif defined(RGB_MATRIX_IS31FL3737)
const rgb_matrix_driver_t rgb_matrix_driver = {
    .init = init,
    .flush = is31fl3737_flush,
    .set_color = is31fl3737_set_color,
    .set_color_all = is31fl3737_set_color_all,
};

#    elif defined(RGB_MATRIX_IS31FL3741)
const rgb_matrix_driver_t rgb_matrix_driver = {
    .init = init,
    .flush = is31fl3741_flush,
    .set_color = is31fl3741_set_color,
    .set_color_all = is31fl3741_set_color_all,
};

#    elif defined(IS31FLCOMMON)
const rgb_matrix_driver_t rgb_matrix_driver = {
    .init = init,
    .flush = IS31FL_common_flush,
    .set_color = IS31FL_RGB_set_color,
    .set_color_all = IS31FL_RGB_set_color_all,
};

#    elif defined(RGB_MATRIX_SNLED27351)
const rgb_matrix_driver_t rgb_matrix_driver = {
    .init = init,
    .flush = snled27351_flush,
    .set_color = snled27351_set_color,
    .set_color_all = snled27351_set_color_all,
};
#    endif

#elif defined(RGB_MATRIX_AW20216S)
#    include "spi_master.h"

static void init(void) {
    spi_init();

    aw20216s_init(AW20216S_CS_PIN_1, AW20216S_EN_PIN_1);
#    if defined(AW20216S_CS_PIN_2)
    aw20216s_init(AW20216S_CS_PIN_2, AW20216S_EN_PIN_2);
#    endif
}

const rgb_matrix_driver_t rgb_matrix_driver = {
    .init          = init,
    .flush         = aw20216s_flush,
    .set_color     = aw20216s_set_color,
    .set_color_all = aw20216s_set_color_all,
};

#elif defined(RGB_MATRIX_WS2812)
#    if defined(RGBLIGHT_WS2812)
#        pragma message "Cannot use RGBLIGHT and RGB Matrix using WS2812 at the same time."
#        pragma message "You need to use a custom driver, or re-implement the WS2812 driver to use a different configuration."
#    endif

// LED color buffer
rgb_led_t rgb_matrix_ws2812_array[RGB_MATRIX_LED_COUNT];
bool      ws2812_dirty = false;

static void init(void) {
    ws2812_dirty = false;
}

static void flush(void) {
    if (ws2812_dirty) {
        ws2812_setleds(rgb_matrix_ws2812_array, RGB_MATRIX_LED_COUNT);
        ws2812_dirty = false;
    }
}

// Set an led in the buffer to a color
static inline void setled(int i, uint8_t r, uint8_t g, uint8_t b) {
#    if defined(RGB_MATRIX_ENABLE) && defined(RGB_MATRIX_SPLIT)
    const uint8_t k_rgb_matrix_split[2] = RGB_MATRIX_SPLIT;
    if (!is_keyboard_left()) {
        if (i >= k_rgb_matrix_split[0]) {
            i -= k_rgb_matrix_split[0];
        } else {
            return;
        }
    } else if (i >= k_rgb_matrix_split[0]) {
        return;
    }
#    endif

    if (rgb_matrix_ws2812_array[i].r == r && rgb_matrix_ws2812_array[i].g == g && rgb_matrix_ws2812_array[i].b == b) {
        return;
    }

    ws2812_dirty                 = true;
    rgb_matrix_ws2812_array[i].r = r;
    rgb_matrix_ws2812_array[i].g = g;
    rgb_matrix_ws2812_array[i].b = b;
#    ifdef RGBW
    convert_rgb_to_rgbw(&rgb_matrix_ws2812_array[i]);
#    endif
}

static void setled_all(uint8_t r, uint8_t g, uint8_t b) {
    for (int i = 0; i < ARRAY_SIZE(rgb_matrix_ws2812_array); i++) {
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
