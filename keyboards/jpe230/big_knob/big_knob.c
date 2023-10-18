// Copyright 2023 jpe230 (@jpe230)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "qp.h"
#include "qp_comms.h"
#include "qp_st7735.h"
#include "qp_st77xx_opcodes.h"
#include "qp_st7735_opcodes.h"
#include "gfx/logo.qgf.h"

painter_device_t lcd;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter Init
// Using custom init to invert the colors of the display

static inline void st7735_automatic_viewport_offsets(painter_device_t device, painter_rotation_t rotation) {
    painter_driver_t *driver = (painter_driver_t *)device;

    // clang-format off
    const struct {
        uint16_t offset_x;
        uint16_t offset_y;
    } rotation_offsets_80x160[] = {
        [QP_ROTATION_0]   = { .offset_x = 26, .offset_y = 26 },
        [QP_ROTATION_90]  = { .offset_x =  1, .offset_y =  1 },
        [QP_ROTATION_180] = { .offset_x = 26, .offset_y =  1 },
        [QP_ROTATION_270] = { .offset_x =  1, .offset_y = 26 },
    };
    // clang-format on

    if (driver->panel_width == 80 && driver->panel_height == 160) {
        driver->offset_x = rotation_offsets_80x160[rotation].offset_x;
        driver->offset_y = rotation_offsets_80x160[rotation].offset_y;
    }
}

bool qp_st7735_init(painter_device_t device, painter_rotation_t rotation) {
    // clang-format off
    const uint8_t st7735_init_sequence[] = {
        // Command,                 Delay, N, Data[N]
        ST77XX_CMD_RESET,            120,  0,
        ST77XX_CMD_SLEEP_OFF,          5,  0,
        ST77XX_SET_PIX_FMT,            0,  1, 0x55,
        ST77XX_CMD_INVERT_ON,          0,  0,
        ST77XX_CMD_NORMAL_ON,          0,  0,
        ST77XX_CMD_DISPLAY_ON,        20,  0
    };
    // clang-format on
    qp_comms_bulk_command_sequence(device, st7735_init_sequence, sizeof(st7735_init_sequence));

    // Configure the rotation (i.e. the ordering and direction of memory writes in GRAM)
    const uint8_t madctl[] = {
        [QP_ROTATION_0]   = ST77XX_MADCTL_BGR,
        [QP_ROTATION_90]  = ST77XX_MADCTL_BGR | ST77XX_MADCTL_MX | ST77XX_MADCTL_MV,
        [QP_ROTATION_180] = ST77XX_MADCTL_BGR | ST77XX_MADCTL_MX | ST77XX_MADCTL_MY,
        [QP_ROTATION_270] = ST77XX_MADCTL_BGR | ST77XX_MADCTL_MV | ST77XX_MADCTL_MY,
    };
    qp_comms_command_databyte(device, ST77XX_SET_MADCTL, madctl[rotation]);

    #ifndef ST7735_NO_AUTOMATIC_VIEWPORT_OFFSETS
        st7735_automatic_viewport_offsets(device, rotation);
    #endif // ST7735_NO_AUTOMATIC_VIEWPORT_OFFSETS

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Init board:
// - Draw logo

void keyboard_post_init_kb(void) {    
    backlight_set(BACKLIGHT_DEFAULT_LEVEL);

    wait_ms(150);

    // Initialise the LCD
    lcd = qp_st7735_make_spi_device(80, 160, LCD_CS_PIN, LCD_DC_PIN, LCD_RST_PIN, 4, 0);
    qp_init(lcd, QP_ROTATION_270);
    
    // Turn on the LCD and clear the display
    qp_power(lcd, true);
    qp_rect(lcd, 0, 0, 160, 80, HSV_BLACK, true);

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
