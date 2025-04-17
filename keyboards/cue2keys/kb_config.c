// Copyright 2025 esplo
// SPDX-License-Identifier: GPL-3.0-or-later

#include "kb_config.h"

void my_kb_config_init(kb_config_t* kb_config) {
    kb_config->mouse_layer_on                  = 1;
    kb_config->mouse_layer_off_delay_ms        = 13;
    kb_config->angle_L                         = 0;
    kb_config->angle_R                         = 0;
    kb_config->pointer_speed_magnification     = 4;
    kb_config->invert_drag_scroll_x            = 0;
    kb_config->invert_drag_scroll_y            = 0;
    kb_config->drag_scroll_speed_magnification = 4;
    kb_config->trackball_led_off_timeout       = 1;
    kb_config->_dummy_tb                       = 0;
    kb_config->re_resolution_1                 = 2;
    kb_config->re_resolution_2                 = 2;
    kb_config->re_resolution_3                 = 2;
    kb_config->re_resolution_4                 = 2;
    kb_config->re_resolution_5                 = 2;
    kb_config->re_resolution_6                 = 2;
    kb_config->re_resolution_7                 = 2;
    kb_config->re_resolution_8                 = 2;
    kb_config->re_resolution_9                 = 2;
    kb_config->re_resolution_10                = 2;
    kb_config->re_resolution_11                = 2;
    kb_config->re_resolution_12                = 2;
    kb_config->re_resolution_13                = 2;
    kb_config->re_resolution_14                = 2;
    kb_config->re_resolution_15                = 2;
    kb_config->re_resolution_16                = 2;
}

void debug_output_kb_config(kb_config_t* kb_config) {
#ifdef CONSOLE_ENABLE
    {
        static uint32_t timer = 0;
        if (timer_elapsed32(timer) > 1000) {
            dprintf("=== kb_config ===\n");
            dprintf("%s = %" PRIu32 "\n", "mouse_layer_on", (uint32_t)kb_config->mouse_layer_on);
            dprintf("%s = %" PRIu32 "\n", "mouse_layer_off_delay_ms", (uint32_t)kb_config->mouse_layer_off_delay_ms);
            dprintf("%s = %" PRIu32 "\n", "angle_L", (uint32_t)kb_config->angle_L);
            dprintf("%s = %" PRIu32 "\n", "angle_R", (uint32_t)kb_config->angle_R);
            dprintf("%s = %" PRIu32 "\n", "pointer_speed_magnification", (uint32_t)kb_config->pointer_speed_magnification);
            dprintf("%s = %" PRIu32 "\n", "invert_drag_scroll_x", (uint32_t)kb_config->invert_drag_scroll_x);
            dprintf("%s = %" PRIu32 "\n", "invert_drag_scroll_y", (uint32_t)kb_config->invert_drag_scroll_y);
            dprintf("%s = %" PRIu32 "\n", "drag_scroll_speed_magnification", (uint32_t)kb_config->drag_scroll_speed_magnification);
            dprintf("%s = %" PRIu32 "\n", "trackball_led_off_timeout", (uint32_t)kb_config->trackball_led_off_timeout);
            dprintf("%s = %" PRIu32 "\n", "_dummy_tb", (uint32_t)kb_config->_dummy_tb);
            dprintf("%s = %" PRIu32 "\n", "re_resolution_1", (uint32_t)kb_config->re_resolution_1);
            dprintf("%s = %" PRIu32 "\n", "re_resolution_2", (uint32_t)kb_config->re_resolution_2);
            dprintf("%s = %" PRIu32 "\n", "re_resolution_3", (uint32_t)kb_config->re_resolution_3);
            dprintf("%s = %" PRIu32 "\n", "re_resolution_4", (uint32_t)kb_config->re_resolution_4);
            dprintf("%s = %" PRIu32 "\n", "re_resolution_5", (uint32_t)kb_config->re_resolution_5);
            dprintf("%s = %" PRIu32 "\n", "re_resolution_6", (uint32_t)kb_config->re_resolution_6);
            dprintf("%s = %" PRIu32 "\n", "re_resolution_7", (uint32_t)kb_config->re_resolution_7);
            dprintf("%s = %" PRIu32 "\n", "re_resolution_8", (uint32_t)kb_config->re_resolution_8);
            dprintf("%s = %" PRIu32 "\n", "re_resolution_9", (uint32_t)kb_config->re_resolution_9);
            dprintf("%s = %" PRIu32 "\n", "re_resolution_10", (uint32_t)kb_config->re_resolution_10);
            dprintf("%s = %" PRIu32 "\n", "re_resolution_11", (uint32_t)kb_config->re_resolution_11);
            dprintf("%s = %" PRIu32 "\n", "re_resolution_12", (uint32_t)kb_config->re_resolution_12);
            dprintf("%s = %" PRIu32 "\n", "re_resolution_13", (uint32_t)kb_config->re_resolution_13);
            dprintf("%s = %" PRIu32 "\n", "re_resolution_14", (uint32_t)kb_config->re_resolution_14);
            dprintf("%s = %" PRIu32 "\n", "re_resolution_15", (uint32_t)kb_config->re_resolution_15);
            dprintf("%s = %" PRIu32 "\n", "re_resolution_16", (uint32_t)kb_config->re_resolution_16);
            dprintf("=== the end of kb_config ===\n");
            timer = timer_read32();
        }
    }
#endif
}

bool process_kb_config_modification(kb_config_t* kb_config, uint16_t keycode, keyrecord_t* record) {
    if (record->event.pressed) {
        switch (keycode) {
            case AUTO_MOUSE_LAYER_P1:
                kb_config->mouse_layer_on = ((uint64_t)kb_config->mouse_layer_on + 2 + 1) % 2;
                return false;
            case AUTO_MOUSE_LAYER_OFF_DELAY_P1:
                kb_config->mouse_layer_off_delay_ms = ((uint64_t)kb_config->mouse_layer_off_delay_ms + 64 + 1) % 64;
                return false;
            case AUTO_MOUSE_LAYER_OFF_DELAY_M1:
                kb_config->mouse_layer_off_delay_ms = ((uint64_t)kb_config->mouse_layer_off_delay_ms + 64 - 1) % 64;
                return false;
            case ANGLE_L_ADJUSTMENT_P1:
                kb_config->angle_L = ((uint64_t)kb_config->angle_L + 360 + 1) % 360;
                return false;
            case ANGLE_L_ADJUSTMENT_M1:
                kb_config->angle_L = ((uint64_t)kb_config->angle_L + 360 - 1) % 360;
                return false;
            case ANGLE_L_ADJUSTMENT_P30:
                kb_config->angle_L = ((uint64_t)kb_config->angle_L + 360 + 30) % 360;
                return false;
            case ANGLE_L_ADJUSTMENT_M30:
                kb_config->angle_L = ((uint64_t)kb_config->angle_L + 360 - 30) % 360;
                return false;
            case ANGLE_R_ADJUSTMENT_P1:
                kb_config->angle_R = ((uint64_t)kb_config->angle_R + 360 + 1) % 360;
                return false;
            case ANGLE_R_ADJUSTMENT_M1:
                kb_config->angle_R = ((uint64_t)kb_config->angle_R + 360 - 1) % 360;
                return false;
            case ANGLE_R_ADJUSTMENT_P30:
                kb_config->angle_R = ((uint64_t)kb_config->angle_R + 360 + 30) % 360;
                return false;
            case ANGLE_R_ADJUSTMENT_M30:
                kb_config->angle_R = ((uint64_t)kb_config->angle_R + 360 - 30) % 360;
                return false;
            case POINTER_SPEED_MAGNIFICATION_P1:
                kb_config->pointer_speed_magnification = ((uint64_t)kb_config->pointer_speed_magnification + 16 + 1) % 16;
                return false;
            case POINTER_SPEED_MAGNIFICATION_M1:
                kb_config->pointer_speed_magnification = ((uint64_t)kb_config->pointer_speed_magnification + 16 - 1) % 16;
                return false;
            case INVERT_DRAG_SCROLL_X_P1:
                kb_config->invert_drag_scroll_x = ((uint64_t)kb_config->invert_drag_scroll_x + 2 + 1) % 2;
                return false;
            case INVERT_DRAG_SCROLL_Y_P1:
                kb_config->invert_drag_scroll_y = ((uint64_t)kb_config->invert_drag_scroll_y + 2 + 1) % 2;
                return false;
            case DRAG_SCROLL_SPEED_MAGNIFICATION_P1:
                kb_config->drag_scroll_speed_magnification = ((uint64_t)kb_config->drag_scroll_speed_magnification + 16 + 1) % 16;
                return false;
            case DRAG_SCROLL_SPEED_MAGNIFICATION_M1:
                kb_config->drag_scroll_speed_magnification = ((uint64_t)kb_config->drag_scroll_speed_magnification + 16 - 1) % 16;
                return false;
            case TRACKBALL_LED_OFF_TIMEOUT_P1:
                kb_config->trackball_led_off_timeout = ((uint64_t)kb_config->trackball_led_off_timeout + 4 + 1) % 4;
                return false;
            case TRACKBALL_LED_OFF_TIMEOUT_M1:
                kb_config->trackball_led_off_timeout = ((uint64_t)kb_config->trackball_led_off_timeout + 4 - 1) % 4;
                return false;
            case ROTARY_ENCODER_1_RESOLUTION_P1:
                kb_config->re_resolution_1 = ((uint64_t)kb_config->re_resolution_1 + 4 + 1) % 4;
                return false;
            case ROTARY_ENCODER_2_RESOLUTION_P1:
                kb_config->re_resolution_2 = ((uint64_t)kb_config->re_resolution_2 + 4 + 1) % 4;
                return false;
            case ROTARY_ENCODER_3_RESOLUTION_P1:
                kb_config->re_resolution_3 = ((uint64_t)kb_config->re_resolution_3 + 4 + 1) % 4;
                return false;
            case ROTARY_ENCODER_4_RESOLUTION_P1:
                kb_config->re_resolution_4 = ((uint64_t)kb_config->re_resolution_4 + 4 + 1) % 4;
                return false;
            case ROTARY_ENCODER_5_RESOLUTION_P1:
                kb_config->re_resolution_5 = ((uint64_t)kb_config->re_resolution_5 + 4 + 1) % 4;
                return false;
            case ROTARY_ENCODER_6_RESOLUTION_P1:
                kb_config->re_resolution_6 = ((uint64_t)kb_config->re_resolution_6 + 4 + 1) % 4;
                return false;
            case ROTARY_ENCODER_7_RESOLUTION_P1:
                kb_config->re_resolution_7 = ((uint64_t)kb_config->re_resolution_7 + 4 + 1) % 4;
                return false;
            case ROTARY_ENCODER_8_RESOLUTION_P1:
                kb_config->re_resolution_8 = ((uint64_t)kb_config->re_resolution_8 + 4 + 1) % 4;
                return false;
            case ROTARY_ENCODER_9_RESOLUTION_P1:
                kb_config->re_resolution_9 = ((uint64_t)kb_config->re_resolution_9 + 4 + 1) % 4;
                return false;
            case ROTARY_ENCODER_10_RESOLUTION_P1:
                kb_config->re_resolution_10 = ((uint64_t)kb_config->re_resolution_10 + 4 + 1) % 4;
                return false;
            case ROTARY_ENCODER_11_RESOLUTION_P1:
                kb_config->re_resolution_11 = ((uint64_t)kb_config->re_resolution_11 + 4 + 1) % 4;
                return false;
            case ROTARY_ENCODER_12_RESOLUTION_P1:
                kb_config->re_resolution_12 = ((uint64_t)kb_config->re_resolution_12 + 4 + 1) % 4;
                return false;
            case ROTARY_ENCODER_13_RESOLUTION_P1:
                kb_config->re_resolution_13 = ((uint64_t)kb_config->re_resolution_13 + 4 + 1) % 4;
                return false;
            case ROTARY_ENCODER_14_RESOLUTION_P1:
                kb_config->re_resolution_14 = ((uint64_t)kb_config->re_resolution_14 + 4 + 1) % 4;
                return false;
            case ROTARY_ENCODER_15_RESOLUTION_P1:
                kb_config->re_resolution_15 = ((uint64_t)kb_config->re_resolution_15 + 4 + 1) % 4;
                return false;
            case ROTARY_ENCODER_16_RESOLUTION_P1:
                kb_config->re_resolution_16 = ((uint64_t)kb_config->re_resolution_16 + 4 + 1) % 4;
                return false;
        }
    }

    return true;
}

void oled_kb_config_output(kb_config_t* kb_config, uint8_t page) {
    oled_write_P(PSTR("Config("), false);
    static char page_str[4];
    itoa(page + 1, page_str, 10);
    oled_write_P(page_str, false);
    oled_write_P(PSTR(") -- "), false);

    switch (page) {
        case 0: {
            static char type_count_str[8];
            oled_write_P(PSTR("mlo:"), false);
            itoa(kb_config->mouse_layer_on, type_count_str, 10);
            oled_write_P(type_count_str, false);
        }
            oled_write_P(PSTR(", "), false);
            {
                static char type_count_str[8];
                oled_write_P(PSTR("mod:"), false);
                itoa(kb_config->mouse_layer_off_delay_ms, type_count_str, 10);
                oled_write_P(type_count_str, false);
            }
            oled_write_P(PSTR(", "), false);
            {
                static char type_count_str[8];
                oled_write_P(PSTR("agl:"), false);
                itoa(kb_config->angle_L, type_count_str, 10);
                oled_write_P(type_count_str, false);
            }
            oled_write_P(PSTR(", "), false);
            {
                static char type_count_str[8];
                oled_write_P(PSTR("agr:"), false);
                itoa(kb_config->angle_R, type_count_str, 10);
                oled_write_P(type_count_str, false);
            }
            oled_write_P(PSTR(", "), false);
            {
                static char type_count_str[8];
                oled_write_P(PSTR("psm:"), false);
                itoa(kb_config->pointer_speed_magnification, type_count_str, 10);
                oled_write_P(type_count_str, false);
            }
            oled_write_P(PSTR(", "), false);
            {
                static char type_count_str[8];
                oled_write_P(PSTR("idsX:"), false);
                itoa(kb_config->invert_drag_scroll_x, type_count_str, 10);
                oled_write_P(type_count_str, false);
            }
            oled_write_P(PSTR(", "), false);
            break;
        case 1: {
            static char type_count_str[8];
            oled_write_P(PSTR("idsY:"), false);
            itoa(kb_config->invert_drag_scroll_y, type_count_str, 10);
            oled_write_P(type_count_str, false);
        }
            oled_write_P(PSTR(", "), false);
            {
                static char type_count_str[8];
                oled_write_P(PSTR("dsm:"), false);
                itoa(kb_config->drag_scroll_speed_magnification, type_count_str, 10);
                oled_write_P(type_count_str, false);
            }
            oled_write_P(PSTR(", "), false);
            {
                static char type_count_str[8];
                oled_write_P(PSTR("tlt:"), false);
                itoa(kb_config->trackball_led_off_timeout, type_count_str, 10);
                oled_write_P(type_count_str, false);
            }
            oled_write_P(PSTR(", "), false);
            {
                static char type_count_str[8];
                oled_write_P(PSTR("rr1:"), false);
                itoa(kb_config->re_resolution_1, type_count_str, 10);
                oled_write_P(type_count_str, false);
            }
            oled_write_P(PSTR(", "), false);
            {
                static char type_count_str[8];
                oled_write_P(PSTR("rr2:"), false);
                itoa(kb_config->re_resolution_2, type_count_str, 10);
                oled_write_P(type_count_str, false);
            }
            oled_write_P(PSTR(", "), false);
            break;
        case 2: {
            static char type_count_str[8];
            oled_write_P(PSTR("rr3:"), false);
            itoa(kb_config->re_resolution_3, type_count_str, 10);
            oled_write_P(type_count_str, false);
        }
            oled_write_P(PSTR(", "), false);
            {
                static char type_count_str[8];
                oled_write_P(PSTR("rr4:"), false);
                itoa(kb_config->re_resolution_4, type_count_str, 10);
                oled_write_P(type_count_str, false);
            }
            oled_write_P(PSTR(", "), false);
            {
                static char type_count_str[8];
                oled_write_P(PSTR("rr5:"), false);
                itoa(kb_config->re_resolution_5, type_count_str, 10);
                oled_write_P(type_count_str, false);
            }
            oled_write_P(PSTR(", "), false);
            {
                static char type_count_str[8];
                oled_write_P(PSTR("rr6:"), false);
                itoa(kb_config->re_resolution_6, type_count_str, 10);
                oled_write_P(type_count_str, false);
            }
            oled_write_P(PSTR(", "), false);
            {
                static char type_count_str[8];
                oled_write_P(PSTR("rr7:"), false);
                itoa(kb_config->re_resolution_7, type_count_str, 10);
                oled_write_P(type_count_str, false);
            }
            oled_write_P(PSTR(", "), false);
            {
                static char type_count_str[8];
                oled_write_P(PSTR("rr8:"), false);
                itoa(kb_config->re_resolution_8, type_count_str, 10);
                oled_write_P(type_count_str, false);
            }
            oled_write_P(PSTR(", "), false);
            break;
        case 3: {
            static char type_count_str[8];
            oled_write_P(PSTR("rr9:"), false);
            itoa(kb_config->re_resolution_9, type_count_str, 10);
            oled_write_P(type_count_str, false);
        }
            oled_write_P(PSTR(", "), false);
            {
                static char type_count_str[8];
                oled_write_P(PSTR("rr10:"), false);
                itoa(kb_config->re_resolution_10, type_count_str, 10);
                oled_write_P(type_count_str, false);
            }
            oled_write_P(PSTR(", "), false);
            {
                static char type_count_str[8];
                oled_write_P(PSTR("rr11:"), false);
                itoa(kb_config->re_resolution_11, type_count_str, 10);
                oled_write_P(type_count_str, false);
            }
            oled_write_P(PSTR(", "), false);
            {
                static char type_count_str[8];
                oled_write_P(PSTR("rr12:"), false);
                itoa(kb_config->re_resolution_12, type_count_str, 10);
                oled_write_P(type_count_str, false);
            }
            oled_write_P(PSTR(", "), false);
            {
                static char type_count_str[8];
                oled_write_P(PSTR("rr13:"), false);
                itoa(kb_config->re_resolution_13, type_count_str, 10);
                oled_write_P(type_count_str, false);
            }
            oled_write_P(PSTR(", "), false);
            {
                static char type_count_str[8];
                oled_write_P(PSTR("rr14:"), false);
                itoa(kb_config->re_resolution_14, type_count_str, 10);
                oled_write_P(type_count_str, false);
            }
            oled_write_P(PSTR(", "), false);
            break;
        case 4: {
            static char type_count_str[8];
            oled_write_P(PSTR("rr15:"), false);
            itoa(kb_config->re_resolution_15, type_count_str, 10);
            oled_write_P(type_count_str, false);
        }
            oled_write_P(PSTR(", "), false);
            {
                static char type_count_str[8];
                oled_write_P(PSTR("rr16:"), false);
                itoa(kb_config->re_resolution_16, type_count_str, 10);
                oled_write_P(type_count_str, false);
            }
            oled_write_P(PSTR(", "), false);
            break;
        default:
            oled_write_ln_P(PSTR("no config"), false);
    }
    oled_write_ln_P("", false);
}
