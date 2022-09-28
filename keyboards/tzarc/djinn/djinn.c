// Copyright 2018-2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#include <string.h>
#include "quantum.h"
#include <hal_pal.h>
#include "djinn.h"
#include "serial.h"
#include "split_util.h"
#include "qp.h"

painter_device_t lcd;

// clang-format off
#ifdef SWAP_HANDS_ENABLE
const keypos_t PROGMEM hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
   { { 6,  6 }, { 5,  6 }, { 4,  6 }, { 3,  6 }, { 2,  6 }, { 1,  6 }, { 0,  6 } },
   { { 6,  7 }, { 5,  7 }, { 4,  7 }, { 3,  7 }, { 2,  7 }, { 1,  7 }, { 0,  7 } },
   { { 6,  8 }, { 5,  8 }, { 4,  8 }, { 3,  8 }, { 2,  8 }, { 1,  8 }, { 0,  8 } },
   { { 6,  9 }, { 5,  9 }, { 4,  9 }, { 3,  9 }, { 2,  9 }, { 1,  9 }, { 0,  9 } },
   { { 0,  0 }, { 0,  0 }, { 0,  0 }, { 6, 10 }, { 5, 10 }, { 4, 10 }, { 3, 10 } },
   { { 0,  0 }, { 6, 11 }, { 5, 11 }, { 4, 11 }, { 3, 11 }, { 2, 11 }, { 1, 11 } },

   { { 6,  0 }, { 5,  0 }, { 4,  0 }, { 3,  0 }, { 2,  0 }, { 1,  0 }, { 0,  0 } },
   { { 6,  1 }, { 5,  1 }, { 4,  1 }, { 3,  1 }, { 2,  1 }, { 1,  1 }, { 0,  1 } },
   { { 6,  2 }, { 5,  2 }, { 4,  2 }, { 3,  2 }, { 2,  2 }, { 1,  2 }, { 0,  2 } },
   { { 6,  3 }, { 5,  3 }, { 4,  3 }, { 3,  3 }, { 2,  3 }, { 1,  3 }, { 0,  3 } },
   { { 0,  0 }, { 0,  0 }, { 0,  0 }, { 6,  4 }, { 5,  4 }, { 4,  4 }, { 3,  4 } },
   { { 0,  0 }, { 6,  5 }, { 5,  5 }, { 4,  5 }, { 3,  5 }, { 2,  5 }, { 1,  5 } },
};
#    ifdef ENCODER_MAP_ENABLE
const uint8_t PROGMEM encoder_hand_swap_config[NUM_ENCODERS] = { 1, 0 };
#    endif // ENCODER_MAP_ENABLE
#endif // SWAP_HANDS_ENABLE
// clang-format on

void board_init(void) {
    usbpd_init();
}

//----------------------------------------------------------
// Initialisation

void keyboard_post_init_kb(void) {
    // Register keyboard state sync split transaction
    transaction_register_rpc(RPC_ID_SYNC_STATE_KB, kb_state_sync_slave);

    // Reset the initial shared data value between master and slave
    memset(&kb_state, 0, sizeof(kb_state));

    // Turn off increased current limits
    setPinOutput(RGB_CURR_1500mA_OK_PIN);
    writePinLow(RGB_CURR_1500mA_OK_PIN);
    setPinOutput(RGB_CURR_3000mA_OK_PIN);
    writePinLow(RGB_CURR_3000mA_OK_PIN);

    // Turn on the RGB
    setPinOutput(RGB_POWER_ENABLE_PIN);
    writePinHigh(RGB_POWER_ENABLE_PIN);

#ifdef EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN
    setPinOutput(EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN);
    writePinHigh(EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN);
#endif // EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN

    // Turn on the LCD
    setPinOutput(LCD_POWER_ENABLE_PIN);
    writePinHigh(LCD_POWER_ENABLE_PIN);

    // Let the LCD get some power...
    wait_ms(150);

    // Initialise the LCD
    lcd = qp_ili9341_make_spi_device(240, 320, LCD_CS_PIN, LCD_DC_PIN, LCD_RST_PIN, 4, 0);
    qp_init(lcd, QP_ROTATION_0);

    // Turn on the LCD and clear the display
    kb_state.lcd_power = 1;
    qp_power(lcd, true);
    qp_rect(lcd, 0, 0, 239, 319, HSV_BLACK, true);

    // Turn on the LCD backlight
    backlight_enable();
    backlight_level(BACKLIGHT_LEVELS);

    // Allow for user post-init
    keyboard_post_init_user();
}

//----------------------------------------------------------
// RGB brightness scaling dependent on USBPD state

#if defined(RGB_MATRIX_ENABLE)
RGB rgb_matrix_hsv_to_rgb(HSV hsv) {
    float scale;

#    ifdef DJINN_SUPPORTS_3A_FUSE
    // The updated BOM on the Djinn has properly-spec'ed fuses -- 1500mA/3000mA hold current
    switch (kb_state.current_setting) {
        default:
        case USBPD_500MA:
            scale = 0.35f;
            break;
        case USBPD_1500MA:
            scale = 0.75f;
            break;
        case USBPD_3000MA:
            scale = 1.0f;
            break;
    }
#    else
    // The original BOM on the Djinn had wrongly-spec'ed fuses -- 750mA/1500mA hold current
    switch (kb_state.current_setting) {
        default:
        case USBPD_500MA:
        case USBPD_1500MA:
            scale = 0.35f;
            break;
        case USBPD_3000MA:
            scale = 0.75f;
            break;
    }
#    endif

    hsv.v = (uint8_t)(hsv.v * scale);
    return hsv_to_rgb(hsv);
}
#endif

//----------------------------------------------------------
// UI Placeholder, implemented in themes

__attribute__((weak)) void draw_ui_user(void) {}

//----------------------------------------------------------
// Housekeeping

void housekeeping_task_kb(void) {
    // Update kb_state so we can send to slave
    kb_state_update();

    // Data sync from master to slave
    kb_state_sync();

    // Work out if we've changed our current limit, update the limiter circuit switches
    static uint8_t current_setting = USBPD_500MA;
    if (current_setting != kb_state.current_setting) {
        current_setting = kb_state.current_setting;

#ifdef DJINN_SUPPORTS_3A_FUSE
        // The updated BOM on the Djinn has properly-spec'ed fuses -- 1500mA/3000mA hold current
        switch (current_setting) {
            default:
            case USBPD_500MA:
                writePinLow(RGB_CURR_1500mA_OK_PIN);
                writePinLow(RGB_CURR_3000mA_OK_PIN);
                break;
            case USBPD_1500MA:
                writePinHigh(RGB_CURR_1500mA_OK_PIN);
                writePinLow(RGB_CURR_3000mA_OK_PIN);
                break;
            case USBPD_3000MA:
                writePinHigh(RGB_CURR_1500mA_OK_PIN);
                writePinHigh(RGB_CURR_3000mA_OK_PIN);
                break;
        }
#else
        // The original BOM on the Djinn had wrongly-spec'ed fuses -- 750mA/1500mA hold current
        switch (current_setting) {
            default:
            case USBPD_500MA:
            case USBPD_1500MA:
                writePinLow(RGB_CURR_1500mA_OK_PIN);
                writePinLow(RGB_CURR_3000mA_OK_PIN);
                break;
            case USBPD_3000MA:
                writePinHigh(RGB_CURR_1500mA_OK_PIN);
                writePinLow(RGB_CURR_3000mA_OK_PIN);
                break;
        }
#endif

        // If we've changed the current limit, toggle rgb off and on if it was on, to force a brightness update on all LEDs
        if (is_keyboard_master() && rgb_matrix_is_enabled()) {
            rgb_matrix_disable_noeeprom();
            rgb_matrix_enable_noeeprom();
        }
    }

    // Turn on/off the LCD
    static bool lcd_on = false;
    if (lcd_on != (bool)kb_state.lcd_power) {
        lcd_on = (bool)kb_state.lcd_power;
        qp_power(lcd, lcd_on);
    }

    // Enable/disable RGB
    if (lcd_on) {
        // Turn on RGB
        writePinHigh(RGB_POWER_ENABLE_PIN);
        // Modify the RGB state if different to the LCD state
        if (rgb_matrix_is_enabled() != lcd_on) {
            // Wait for a small amount of time to allow the RGB capacitors to charge, before enabling RGB output
            wait_ms(10);
            // Enable RGB
            rgb_matrix_enable_noeeprom();
        }
    } else {
        // Turn off RGB
        writePinLow(RGB_POWER_ENABLE_PIN);
        // Disable the PWM output for the RGB
        if (rgb_matrix_is_enabled() != lcd_on) {
            rgb_matrix_disable_noeeprom();
        }
    }

    // Match the backlight to the LCD state
    if (is_keyboard_master() && is_backlight_enabled() != lcd_on) {
        if (lcd_on)
            backlight_enable();
        else
            backlight_disable();
    }

    // Draw the UI
    if (kb_state.lcd_power) {
        draw_ui_user();
    }

    // Go into low-scan interrupt-based mode if we haven't had any matrix activity in the last 250 milliseconds
    if (last_input_activity_elapsed() > 250) {
        matrix_wait_for_interrupt();
    }
}
