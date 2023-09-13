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

#if defined(IS31FL3731) || defined(IS31FL3733) || defined(IS31FL3736) || defined(IS31FL3737) || defined(IS31FL3741) || defined(IS31FLCOMMON) || defined(CKLED2001)
#    include "i2c_master.h"

// TODO: Remove this at some later date
#    if defined(DRIVER_ADDR_1) && defined(DRIVER_ADDR_2)
#        if DRIVER_ADDR_1 == DRIVER_ADDR_2
#            error "Setting DRIVER_ADDR_2 == DRIVER_ADDR_1 is obsolete. If you are only using one ISSI driver, set DRIVER_COUNT to 1 and remove DRIVER_ADDR_2"
#        endif
#    endif

static void init(void) {
    i2c_init();

#    if defined(IS31FL3731)
    is31fl3731_init(DRIVER_ADDR_1);
#        if defined(DRIVER_ADDR_2)
    is31fl3731_init(DRIVER_ADDR_2);
#            if defined(DRIVER_ADDR_3)
    is31fl3731_init(DRIVER_ADDR_3);
#                if defined(DRIVER_ADDR_4)
    is31fl3731_init(DRIVER_ADDR_4);
#                endif
#            endif
#        endif

#    elif defined(IS31FL3733)
#        if !defined(DRIVER_SYNC_1)
#            define DRIVER_SYNC_1 0
#        endif
    is31fl3733_init(DRIVER_ADDR_1, DRIVER_SYNC_1);
#        if defined(DRIVER_ADDR_2)
#            if !defined(DRIVER_SYNC_2)
#                define DRIVER_SYNC_2 0
#            endif
    is31fl3733_init(DRIVER_ADDR_2, DRIVER_SYNC_2);
#            if defined(DRIVER_ADDR_3)
#                if !defined(DRIVER_SYNC_3)
#                    define DRIVER_SYNC_3 0
#                endif
    is31fl3733_init(DRIVER_ADDR_3, DRIVER_SYNC_3);
#                if defined(DRIVER_ADDR_4)
#                    if !defined(DRIVER_SYNC_4)
#                        define DRIVER_SYNC_4 0
#                    endif
    is31fl3733_init(DRIVER_ADDR_4, DRIVER_SYNC_4);
#                endif
#            endif
#        endif

#    elif defined(IS31FL3736)
    is31fl3736_init(DRIVER_ADDR_1);
#        if defined(DRIVER_ADDR_2)
    is31fl3736_init(DRIVER_ADDR_2);
#            if defined(DRIVER_ADDR_3)
    is31fl3736_init(DRIVER_ADDR_3);
#                if defined(DRIVER_ADDR_4)
    is31fl3736_init(DRIVER_ADDR_4);
#                endif
#            endif
#        endif

#    elif defined(IS31FL3737)
    is31fl3737_init(DRIVER_ADDR_1);
#        if defined(DRIVER_ADDR_2)
    is31fl3737_init(DRIVER_ADDR_2);
#            if defined(DRIVER_ADDR_3)
    is31fl3737_init(DRIVER_ADDR_3);
#                if defined(DRIVER_ADDR_4)
    is31fl3737_init(DRIVER_ADDR_4);
#                endif
#            endif
#        endif

#    elif defined(IS31FL3741)
    is31fl3741_init(DRIVER_ADDR_1);
#        if defined(DRIVER_ADDR_2)
    is31fl3741_init(DRIVER_ADDR_2);
#            if defined(DRIVER_ADDR_3)
    is31fl3741_init(DRIVER_ADDR_3);
#                if defined(DRIVER_ADDR_4)
    is31fl3741_init(DRIVER_ADDR_4);
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

#    elif defined(CKLED2001)
    ckled2001_init(DRIVER_ADDR_1);
#        if defined(DRIVER_ADDR_2)
    ckled2001_init(DRIVER_ADDR_2);
#            if defined(DRIVER_ADDR_3)
    ckled2001_init(DRIVER_ADDR_3);
#                if defined(DRIVER_ADDR_4)
    ckled2001_init(DRIVER_ADDR_4);
#                endif
#            endif
#        endif
#    endif

    for (int index = 0; index < RGB_MATRIX_LED_COUNT; index++) {
        bool enabled = true;

        // This only caches it for later
#    if defined(IS31FL3731)
        is31fl3731_set_led_control_register(index, enabled, enabled, enabled);
#    elif defined(IS31FL3733)
        is31fl3733_set_led_control_register(index, enabled, enabled, enabled);
#    elif defined(IS31FL3736)
        is31fl3736_set_led_control_register(index, enabled, enabled, enabled);
#    elif defined(IS31FL3737)
        is31fl3737_set_led_control_register(index, enabled, enabled, enabled);
#    elif defined(IS31FL3741)
        is31fl3741_set_led_control_register(index, enabled, enabled, enabled);
#    elif defined(IS31FLCOMMON)
        IS31FL_RGB_set_scaling_buffer(index, enabled, enabled, enabled);
#    elif defined(CKLED2001)
        ckled2001_set_led_control_register(index, enabled, enabled, enabled);
#    endif
    }

    // This actually updates the LED drivers
#    if defined(IS31FL3731)
    is31fl3731_update_led_control_registers(DRIVER_ADDR_1, 0);
#        if defined(DRIVER_ADDR_2)
    is31fl3731_update_led_control_registers(DRIVER_ADDR_2, 1);
#            if defined(DRIVER_ADDR_3)
    is31fl3731_update_led_control_registers(DRIVER_ADDR_3, 2);
#                if defined(DRIVER_ADDR_4)
    is31fl3731_update_led_control_registers(DRIVER_ADDR_4, 3);
#                endif
#            endif
#        endif

#    elif defined(IS31FL3733)
    is31fl3733_update_led_control_registers(DRIVER_ADDR_1, 0);
#        if defined(DRIVER_ADDR_2)
    is31fl3733_update_led_control_registers(DRIVER_ADDR_2, 1);
#            if defined(DRIVER_ADDR_3)
    is31fl3733_update_led_control_registers(DRIVER_ADDR_3, 2);
#                if defined(DRIVER_ADDR_4)
    is31fl3733_update_led_control_registers(DRIVER_ADDR_4, 3);
#                endif
#            endif
#        endif

#    elif defined(IS31FL3736)
    is31fl3736_update_led_control_registers(DRIVER_ADDR_1, 0);
#        if defined(DRIVER_ADDR_2)
    is31fl3736_update_led_control_registers(DRIVER_ADDR_2, 1);
#            if defined(DRIVER_ADDR_3)
    is31fl3736_update_led_control_registers(DRIVER_ADDR_3, 2);
#                if defined(DRIVER_ADDR_4)
    is31fl3736_update_led_control_registers(DRIVER_ADDR_4, 3);
#                endif
#            endif
#        endif

#    elif defined(IS31FL3737)
    is31fl3737_update_led_control_registers(DRIVER_ADDR_1, 0);
#        if defined(DRIVER_ADDR_2)
    is31fl3737_update_led_control_registers(DRIVER_ADDR_2, 1);
#            if defined(DRIVER_ADDR_3)
    is31fl3737_update_led_control_registers(DRIVER_ADDR_3, 2);
#                if defined(DRIVER_ADDR_4)
    is31fl3737_update_led_control_registers(DRIVER_ADDR_4, 3);
#                endif
#            endif
#        endif

#    elif defined(IS31FL3741)
    is31fl3741_update_led_control_registers(DRIVER_ADDR_1, 0);
#        if defined(DRIVER_ADDR_2)
    is31fl3741_update_led_control_registers(DRIVER_ADDR_2, 1);
#            if defined(DRIVER_ADDR_3)
    is31fl3741_update_led_control_registers(DRIVER_ADDR_3, 2);
#                if defined(DRIVER_ADDR_4)
    is31fl3741_update_led_control_registers(DRIVER_ADDR_4, 3);
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

#    elif defined(CKLED2001)
    ckled2001_update_led_control_registers(DRIVER_ADDR_1, 0);
#        if defined(DRIVER_ADDR_2)
    ckled2001_update_led_control_registers(DRIVER_ADDR_2, 1);
#            if defined(DRIVER_ADDR_3)
    ckled2001_update_led_control_registers(DRIVER_ADDR_3, 2);
#                if defined(DRIVER_ADDR_4)
    ckled2001_update_led_control_registers(DRIVER_ADDR_4, 3);
#                endif
#            endif
#        endif
#    endif
}

#    if defined(IS31FL3731)
static void flush(void) {
    is31fl3731_update_pwm_buffers(DRIVER_ADDR_1, 0);
#        if defined(DRIVER_ADDR_2)
    is31fl3731_update_pwm_buffers(DRIVER_ADDR_2, 1);
#            if defined(DRIVER_ADDR_3)
    is31fl3731_update_pwm_buffers(DRIVER_ADDR_3, 2);
#                if defined(DRIVER_ADDR_4)
    is31fl3731_update_pwm_buffers(DRIVER_ADDR_4, 3);
#                endif
#            endif
#        endif
}

const rgb_matrix_driver_t rgb_matrix_driver = {
    .init          = init,
    .flush         = flush,
    .set_color     = is31fl3731_set_color,
    .set_color_all = is31fl3731_set_color_all,
};

#    elif defined(IS31FL3733)
static void flush(void) {
    is31fl3733_update_pwm_buffers(DRIVER_ADDR_1, 0);
#        if defined(DRIVER_ADDR_2)
    is31fl3733_update_pwm_buffers(DRIVER_ADDR_2, 1);
#            if defined(DRIVER_ADDR_3)
    is31fl3733_update_pwm_buffers(DRIVER_ADDR_3, 2);
#                if defined(DRIVER_ADDR_4)
    is31fl3733_update_pwm_buffers(DRIVER_ADDR_4, 3);
#                endif
#            endif
#        endif
}

const rgb_matrix_driver_t rgb_matrix_driver = {
    .init = init,
    .flush = flush,
    .set_color = is31fl3733_set_color,
    .set_color_all = is31fl3733_set_color_all,
};

#    elif defined(IS31FL3736)
static void flush(void) {
    is31fl3736_update_pwm_buffers(DRIVER_ADDR_1, 0);
#        if defined(DRIVER_ADDR_2)
    is31fl3736_update_pwm_buffers(DRIVER_ADDR_2, 1);
#            if defined(DRIVER_ADDR_3)
    is31fl3736_update_pwm_buffers(DRIVER_ADDR_3, 2);
#                if defined(DRIVER_ADDR_4)
    is31fl3736_update_pwm_buffers(DRIVER_ADDR_4, 3);
#                endif
#            endif
#        endif
}

const rgb_matrix_driver_t rgb_matrix_driver = {
    .init = init,
    .flush = flush,
    .set_color = is31fl3736_set_color,
    .set_color_all = is31fl3736_set_color_all,
};

#    elif defined(IS31FL3737)
static void flush(void) {
    is31fl3737_update_pwm_buffers(DRIVER_ADDR_1, 0);
#        if defined(DRIVER_ADDR_2)
    is31fl3737_update_pwm_buffers(DRIVER_ADDR_2, 1);
#            if defined(DRIVER_ADDR_3)
    is31fl3737_update_pwm_buffers(DRIVER_ADDR_3, 2);
#                if defined(DRIVER_ADDR_4)
    is31fl3737_update_pwm_buffers(DRIVER_ADDR_4, 3);
#                endif
#            endif
#        endif
}

const rgb_matrix_driver_t rgb_matrix_driver = {
    .init = init,
    .flush = flush,
    .set_color = is31fl3737_set_color,
    .set_color_all = is31fl3737_set_color_all,
};

#    elif defined(IS31FL3741)
static void flush(void) {
    is31fl3741_update_pwm_buffers(DRIVER_ADDR_1, 0);
#        if defined(DRIVER_ADDR_2)
    is31fl3741_update_pwm_buffers(DRIVER_ADDR_2, 1);
#            if defined(DRIVER_ADDR_3)
    is31fl3741_update_pwm_buffers(DRIVER_ADDR_3, 2);
#                if defined(DRIVER_ADDR_4)
    is31fl3741_update_pwm_buffers(DRIVER_ADDR_4, 3);
#                endif
#            endif
#        endif
}

const rgb_matrix_driver_t rgb_matrix_driver = {
    .init = init,
    .flush = flush,
    .set_color = is31fl3741_set_color,
    .set_color_all = is31fl3741_set_color_all,
};

#    elif defined(IS31FLCOMMON)
static void flush(void) {
    IS31FL_common_update_pwm_register(DRIVER_ADDR_1, 0);
#        if defined(DRIVER_ADDR_2)
    IS31FL_common_update_pwm_register(DRIVER_ADDR_2, 1);
#            if defined(DRIVER_ADDR_3)
    IS31FL_common_update_pwm_register(DRIVER_ADDR_3, 2);
#                if defined(DRIVER_ADDR_4)
    IS31FL_common_update_pwm_register(DRIVER_ADDR_4, 3);
#                endif
#            endif
#        endif
}

const rgb_matrix_driver_t rgb_matrix_driver = {
    .init = init,
    .flush = flush,
    .set_color = IS31FL_RGB_set_color,
    .set_color_all = IS31FL_RGB_set_color_all,
};

#    elif defined(CKLED2001)
static void flush(void) {
    ckled2001_update_pwm_buffers(DRIVER_ADDR_1, 0);
#        if defined(DRIVER_ADDR_2)
    ckled2001_update_pwm_buffers(DRIVER_ADDR_2, 1);
#            if defined(DRIVER_ADDR_3)
    ckled2001_update_pwm_buffers(DRIVER_ADDR_3, 2);
#                if defined(DRIVER_ADDR_4)
    ckled2001_update_pwm_buffers(DRIVER_ADDR_4, 3);
#                endif
#            endif
#        endif
}

const rgb_matrix_driver_t rgb_matrix_driver = {
    .init = init,
    .flush = flush,
    .set_color = ckled2001_set_color,
    .set_color_all = ckled2001_set_color_all,
};
#    endif

#elif defined(AW20216S)
#    include "spi_master.h"

static void init(void) {
    spi_init();

    aw20216s_init(AW20216S_DRIVER_1_CS, AW20216S_DRIVER_1_EN);
#    if defined(AW20216S_DRIVER_2_CS)
    aw20216s_init(AW20216S_DRIVER_2_CS, AW20216S_DRIVER_2_EN);
#    endif
}

static void flush(void) {
    aw20216s_update_pwm_buffers(AW20216S_DRIVER_1_CS, 0);
#    if defined(AW20216S_DRIVER_2_CS)
    aw20216s_update_pwm_buffers(AW20216S_DRIVER_2_CS, 1);
#    endif
}

const rgb_matrix_driver_t rgb_matrix_driver = {
    .init          = init,
    .flush         = flush,
    .set_color     = aw20216s_set_color,
    .set_color_all = aw20216s_set_color_all,
};

#elif defined(WS2812)
#    if defined(RGBLIGHT_ENABLE) && !defined(RGBLIGHT_CUSTOM_DRIVER)
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
