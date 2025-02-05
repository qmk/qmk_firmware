// Copyright 2024 Dasky (@daskygit)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "graphics/primeplus.qgf.h"

painter_image_handle_t primeplus;
painter_device_t       display;

void board_init(void) {
    AFIO->MAPR |= AFIO_MAPR_I2C1_REMAP;

    gpio_set_pin_output(A15);
    gpio_write_pin_high(A15); // Activate D+ pullup

    gpio_set_pin_output(OPTICAL_SW_PWR);
    gpio_write_pin_low(OPTICAL_SW_PWR); // Enable power for optical switches

    gpio_set_pin_output(OLED_PWR);
    gpio_write_pin_high(OLED_PWR); // Enable OLED power
}

void keyboard_post_init_kb(void) {
    wait_ms(1); // Wait for OLED

    gpio_set_pin_output(OLED_RESET);
    gpio_write_pin_low(OLED_RESET);
    wait_us(10); // Minimum wait 1us

    gpio_write_pin_high(OLED_RESET);
    wait_ms(1); // Minimum wait 1ms

    primeplus = qp_load_image_mem(gfx_primeplus);
    display   = qp_ld7032_make_i2c_device(96, 24, 0x37);

    qp_init(display, QP_ROTATION_180);
    qp_drawimage(display, 0, 0, primeplus);

    keyboard_post_init_user();
}
