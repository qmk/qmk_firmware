// Copyright 2023 jpe230 (@jpe230)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "qp.h"
#include "qp_comms.h"
#include "qp_st77xx_opcodes.h"
#include "gfx/logo.qgf.h"

painter_device_t lcd;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Init board:
// - Draw logo

void keyboard_post_init_kb(void) {
    backlight_set(BACKLIGHT_DEFAULT_LEVEL);

    wait_ms(LCD_WAIT_TIME);

    // Initialise the LCD
    lcd = qp_st7735_make_spi_device(LCD_HEIGHT, LCD_WIDTH, LCD_CS_PIN, LCD_DC_PIN, LCD_RST_PIN, LCD_SPI_DIVISOR, 0);
    qp_init(lcd, LCD_ROTATION);

    // Invert Colour
    #ifdef LCD_INVERT_COLOUR
    qp_comms_start(lcd);
    qp_comms_command(lcd, ST77XX_CMD_INVERT_ON);
    qp_comms_stop(lcd);
    #endif

    // Apply Offset
    qp_set_viewport_offsets(lcd, LCD_OFFSET_X, LCD_OFFSET_Y);

    // Turn on the LCD and clear the display
    qp_power(lcd, true);
    qp_rect(lcd, 0, 0, LCD_WIDTH, LCD_HEIGHT, HSV_BLACK, true);

    // Show logo
    painter_image_handle_t logo_image = qp_load_image_mem(gfx_logo);
    qp_drawimage(lcd, 0, 0, logo_image);

    keyboard_post_init_user();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Lights handling:
//  - Turn off backlight (screen) after timeout or suspend
//  - Turn off rgblight after timeout or suspend

bool lights_off = false;

__attribute__((weak)) void lights_wakeup_user(void) {};
__attribute__((weak)) void lights_suspend_user(void) {};

void backlight_wakeup(void) {
    backlight_set(BACKLIGHT_DEFAULT_LEVEL);
}

void backlight_suspend(void) {
    backlight_set(0);
}

void lights_wakeup(void) {
    lights_off = false;
    rgblight_wakeup();
    backlight_wakeup();
    lights_wakeup_user();
}

void lights_suspend(void) {
    lights_off = true;
    lights_suspend_user();
    rgblight_suspend();
    backlight_suspend();
}

void housekeeping_task_kb(void) {
    if ( lights_off && last_input_activity_elapsed() <= LIGHTS_TIMEOUT)
    {
        lights_wakeup();
    }
    if (!lights_off && last_input_activity_elapsed() > LIGHTS_TIMEOUT) {
        lights_suspend();
    }
}

void suspend_power_down_kb(void) {
    lights_suspend();
    qp_power(lcd, false);
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    qp_power(lcd, true);
    lights_wakeup();
    suspend_wakeup_init_user();
}
