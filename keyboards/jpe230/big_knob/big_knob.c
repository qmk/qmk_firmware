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
    qp_comms_start(lcd);
    qp_comms_command(lcd, ST77XX_CMD_INVERT_ON);
    qp_comms_stop(lcd);

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

static uint16_t key_timer;
bool lights_off = false;

void backlight_wakeup(void) {
    backlight_enable();
    backlight_set(BACKLIGHT_DEFAULT_LEVEL);
}

void backlight_suspend(void) {
    backlight_set(0);
    backlight_disable();
}

void lights_wakeup(void) {
    key_timer = timer_read();
    if (!lights_off) {
        return;
    }
    lights_off = false;
    rgblight_wakeup();
    backlight_wakeup();
}

void lights_suspend(void) {
    lights_off = true;
    rgblight_suspend();
    backlight_suspend();
}

void post_process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed){
        lights_wakeup();
    }
    post_process_record_user(keycode, record);
}

bool encoder_update_kb(uint8_t index, bool clockwise) {
    lights_wakeup();
    if (!encoder_update_user(index, clockwise)) {
      return false;
    }

    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    return true;
}

void housekeeping_task_kb(void) {
    if (!lights_off && timer_elapsed(key_timer) > LIGHTS_TIMEOUT) {
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
