/*
Copyright 2021 gregorio

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "./lib/oled.h"

bool process_record_user_oled(uint16_t keycode, keyrecord_t *record) {
    return process_record_user(keycode, record);
}

void change_oled_mode(void) {
    oled_mode = (oled_mode + 1) % _NUM_OLED_MODES;
}

void render_layer_section(void) {
    // Layer indicators
    static const char PROGMEM layer_0[] = {0xc8, 0xc9, 0};
    static const char PROGMEM layer_1[] = {0xca, 0xcb, 0};
    static const char PROGMEM layer_2[] = {0xcc, 0xcd, 0};
    static const char PROGMEM layer_3[] = {0xce, 0xcf, 0};

    oled_set_cursor(oled_max_chars()-15, 0);
    oled_write_P(PSTR("LAYER"), false);
    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_P(layer_0, false);
            break;
        case 1:
            oled_write_P(layer_1, false);
            break;
        case 2:
            oled_write_P(layer_2, false);
            break;
        case 3:
            oled_write_P(layer_3, false);
            break;
        default:
            oled_write_P(PSTR("? "), false);
            break;
    }
}

void render_encoder_section(void) {
    static const char PROGMEM enc_vol[] = {0x88, 0x89, 0x8a, 0x8b, 0};
    static const char PROGMEM enc_med[] = {0xa8, 0xa9, 0xaa, 0xab, 0};
    static const char PROGMEM enc_brt[] = {0x8c, 0x8d, 0x8e, 0x8f, 0};

    oled_set_cursor(oled_max_chars()-7, 0);
    oled_write_P(PSTR("ENC"), false);
    switch (encoder_mode) {
        default:
        case ENC_MODE_VOLUME:
            oled_write_P(enc_vol, false);
            break;
        case ENC_MODE_MEDIA:
            oled_write_P(enc_med, false);
            break;
        case ENC_MODE_BRIGHTNESS:
            oled_write_P(enc_brt, false);
            break;
    }
}

void render_numlock_section(void) {
    static const char PROGMEM num_on[] = {0x80, 0x81, 0x82, 0x83, 0};
    static const char PROGMEM num_off[] = {0xa0, 0xa1, 0xa2, 0xa3, 0};
    static const char PROGMEM cap_on[] = {0x84, 0x85, 0x86, 0x87, 0};
    static const char PROGMEM cap_off[] = {0xa4, 0xa5, 0xa6, 0xa7, 0};
    static const char PROGMEM scr_on[] = {0xba, 0xbb, 0xbc, 0xbd, 0};
    static const char PROGMEM scr_off[] = {0xda, 0xdb, 0xdc, 0xdd, 0};

    led_t led_state = host_keyboard_led_state();

    oled_set_cursor(oled_max_chars()-12, 3);
    // num lock
    oled_write_P(led_state.num_lock ? num_on : num_off, false);
    oled_write_P(led_state.caps_lock ? cap_on : cap_off, false);
    oled_write_P(led_state.scroll_lock ? scr_on : scr_off, false);
}

void render_mode_section(void) {
    static const char PROGMEM pad_on[] = {0xb0, 0xb1, 0xb2, 0xb3, 0};
    static const char PROGMEM pad_off[] = {0xc4, 0xc5, 0xc6, 0xc7, 0};
    static const char PROGMEM cal_on[] = {0x90, 0x91, 0x92, 0x93, 0};
    static const char PROGMEM cal_off[] = {0xc0, 0xc1, 0xc2, 0xc3, 0};

    if (oled_mode == OLED_MODE_CALC) {
        oled_set_cursor(0, 0);
        oled_write_P(pad_off, false);
        oled_set_cursor(0, 1);
        oled_write_P(cal_on, false);
    } else {
        oled_set_cursor(0, 0);
        oled_write_P(pad_on, false);
        oled_set_cursor(0, 1);
        oled_write_P(cal_off, false);
    }
}

void render_calc_section(void) {
    static const char PROGMEM add_on[] = {0xd4, 0xd5, 0};
    static const char PROGMEM add_off[] = {0x94, 0x95, 0};
    static const char PROGMEM sub_on[] = {0xd6, 0xd7, 0};
    static const char PROGMEM sub_off[] = {0x96, 0x97, 0};
    static const char PROGMEM mul_on[] = {0xd8, 0xd9, 0};
    static const char PROGMEM mul_off[] = {0x9c, 0x9d, 0};
    static const char PROGMEM div_on[] = {0xb8, 0xb9, 0};
    static const char PROGMEM div_off[] = {0x9e, 0x9f, 0};
    static const char PROGMEM sqr_on[] = {0x98, 0x99, 0};
    static const char PROGMEM sqr_off[] = {0xbe, 0xbf, 0};
    static const char PROGMEM rec_on[] = {0x9a, 0x9b, 0};
    static const char PROGMEM rec_off[] = {0xde, 0xdf, 0};
    static const char PROGMEM neg_on[] = {0xb4, 0xb5, 0};
    static const char PROGMEM neg_off[] = {0xb6, 0xb7, 0};


    if (oled_mode == OLED_MODE_CALC) {
        if (get_highest_layer(layer_state) == 1) {
            oled_set_cursor(oled_max_chars()-8, 0);

            switch (calc_operator_display) {
                case '+':
                    oled_write_P(div_off, false);
                    oled_write_P(mul_off, false);
                    oled_write_P(sub_off, false);
                    oled_write_P(add_on, false);
                    break;
                case '-':
                    oled_write_P(div_off, false);
                    oled_write_P(mul_off, false);
                    oled_write_P(sub_on, false);
                    oled_write_P(add_off, false);
                    break;
                case '*':
                    oled_write_P(div_off, false);
                    oled_write_P(mul_on, false);
                    oled_write_P(sub_off, false);
                    oled_write_P(add_off, false);
                    break;
                case '/':
                    oled_write_P(div_on, false);
                    oled_write_P(mul_off, false);
                    oled_write_P(sub_off, false);
                    oled_write_P(add_off, false);
                    break;
                case 's':
                case 'r':
                case 'n':
                    layer_on(2);
                    break;
                default:
                    oled_write_P(div_off, false);
                    oled_write_P(mul_off, false);
                    oled_write_P(sub_off, false);
                    oled_write_P(add_off, false);
                    break;
            }
        } else if (get_highest_layer(layer_state) == 2) {
            oled_set_cursor(oled_max_chars()-6, 0);

            switch (calc_operator_display) {
                case '+':
                case '-':
                case '*':
                case '/':
                    layer_off(2);
                    break;
                case 's':
                    oled_write_P(neg_off, false);
                    oled_write_P(sqr_on, false);
                    oled_write_P(rec_off, false);
                    break;
                case 'r':
                    oled_write_P(neg_off, false);
                    oled_write_P(sqr_off, false);
                    oled_write_P(rec_on, false);
                    break;
                case 'n':
                    oled_write_P(neg_on, false);
                    oled_write_P(sqr_off, false);
                    oled_write_P(rec_off, false);
                    break;
                default:
                    oled_write_P(neg_off, false);
                    oled_write_P(sqr_off, false);
                    oled_write_P(rec_off, false);
                    break;
            }
        }

        if (calc_display_lines == 1) {
            oled_set_cursor(oled_max_chars()-strlen(calc_result_display)-2, 3);
            oled_write_char(calc_operator_display, false);
        } else if (calc_display_lines == 2) {
            oled_set_cursor(oled_max_chars()-strlen(calc_status_display), 2);
            oled_write(calc_status_display, false);
        }
        oled_set_cursor(oled_max_chars()-strlen(calc_result_display), 3);
        oled_write(calc_result_display, false);
    }
}

static void render_logo(void) {
    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}

void render_frame(void) {
    if (oled_logo_expired) {
        if (oled_mode == OLED_MODE_DEFAULT) {
            render_mode_section();
            render_layer_section();
            render_encoder_section();
            render_numlock_section();
        } else if (oled_mode == OLED_MODE_CALC) {
            render_mode_section();
            render_calc_section();
        } else if (oled_mode == OLED_MODE_OFF) {
            if (is_oled_on()) {
                oled_off();
            }
        }
    } else {
        render_logo();
        oled_logo_expired = timer_elapsed(oled_logo_timer) > OLED_LOGO_TIMEOUT;
    }
}

__attribute__((weak)) void oled_task_user(void) {
    if (timer_elapsed(oled_frame_timer) > OLED_FRAME_TIMEOUT) {
        oled_clear();
        oled_frame_timer = timer_read();
        render_frame();
    }

    if (get_highest_layer(layer_state) == 1) {
        oled_mode = OLED_MODE_CALC;
    } else if (get_highest_layer(layer_state) == 2) {
        if (IS_LAYER_ON(1)) {
            oled_mode = OLED_MODE_CALC;
        } else {
            oled_mode = OLED_MODE_DEFAULT;
        }
    } else if (get_highest_layer(layer_state) == 3) {
        oled_mode = OLED_MODE_OFF;
    } else {
        oled_mode = OLED_MODE_DEFAULT;
    }
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    oled_logo_timer = timer_read();
    oled_frame_timer = timer_read();
    return rotation;
}
