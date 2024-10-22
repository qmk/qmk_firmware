// Copyright 2024 SDK (@sdk66)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "rgb_record.h"
#include "rgb_matrix.h"
#include "eeprom.h"

#define RGBREC_STATE_ON  1
#define RGBREC_STATE_OFF 0
#define RGBREC_COLOR_NUM (sizeof(rgbrec_hs_lists) / sizeof(rgbrec_hs_lists[0]))

typedef struct {
    uint8_t state;
    uint8_t channel;
    uint16_t value;
} rgbrec_info_t;

typedef uint16_t (*rgbrec_effects_t)[MATRIX_COLS];

rgbrec_effects_t p_rgbrec_effects = NULL;

static uint16_t rgbrec_hs_lists[] = RGB_RECORD_HS_LISTS;
static uint8_t rgbrec_buffer[MATRIX_ROWS * MATRIX_COLS * 2];

//clang-format off
static const uint8_t rgbmatrix_buff[]   = {13, 15, 16, 24, 25, 26, 29, 37, 33, 34, 35, 43, 2, 5, 6, 9};
static const uint8_t sixth_gear_buff[]  = {6, 13, 15, 16, 25, 26, 34};
static uint8_t rgb_hsvs[RGB_HSV_MAX][2] = {
    {0,   255},
    {85,  255},
    {170, 255},
    {43,  255},
    {191, 255},
    {128, 255},
    {4,   80 },
};

//clang-format on
static rgbrec_info_t rgbrec_info = {
    .state   = RGBREC_STATE_OFF,
    .channel = 0,
    .value   = 0xFF,
};

static uint8_t rgbrec_buffer[MATRIX_ROWS * MATRIX_COLS * 2];
extern const uint16_t PROGMEM rgbrec_default_effects[RGBREC_CHANNEL_NUM][MATRIX_ROWS][MATRIX_COLS];

static bool find_matrix_row_col(uint8_t index, uint8_t *row, uint8_t *col) {
    uint8_t i, j;

    for (i = 0; i < MATRIX_ROWS; i++) {
        for (j = 0; j < MATRIX_COLS; j++) {
            if (g_led_config.matrix_co[i][j] != NO_LED) {
                if (g_led_config.matrix_co[i][j] == index) {
                    *row = i;
                    *col = j;

                    return true;
                }
            }
        }
    }

    return false;
}

static inline RGB hs_to_rgb(uint8_t h, uint8_t s) {

    if ((h == 0) && (s == 0)) {
        return hsv_to_rgb((HSV){0, 0, 0});
    } else if ((h == 1) && (s == 1)) {
        return hsv_to_rgb((HSV){0, 0, rgbrec_info.value});
    } else {
        return hsv_to_rgb((HSV){h, s, rgbrec_info.value});
    }
}

void rgbrec_init(uint8_t channel) {

    p_rgbrec_effects    = (rgbrec_effects_t)rgbrec_buffer;
    rgbrec_info.state   = RGBREC_STATE_OFF;
    rgbrec_info.channel = channel;
    rgbrec_info.value   = rgb_matrix_get_val();

    rgbrec_read_current_channel(rgbrec_info.channel);
}

bool rgbrec_show(uint8_t channel) {

    if (channel >= RGBREC_CHANNEL_NUM) {
        return false;
    }

    rgbrec_info.channel = channel;
    rgbrec_read_current_channel(rgbrec_info.channel);

    if (rgb_matrix_get_mode() != RGB_MATRIX_CUSTOM_RGBR_PLAY) {
        rgb_matrix_mode(RGB_MATRIX_CUSTOM_RGBR_PLAY);
    }

    return true;
}

bool rgbrec_start(uint8_t channel) {

    if (channel >= RGBREC_CHANNEL_NUM) {

        return false;
    }

    if (rgbrec_info.state == RGBREC_STATE_OFF) {
        rgbrec_info.state   = RGBREC_STATE_ON;
        rgbrec_info.channel = channel;
        rgbrec_read_current_channel(rgbrec_info.channel);
        if (rgb_matrix_get_mode() != RGB_MATRIX_CUSTOM_RGBR_PLAY) {
            rgb_matrix_mode(RGB_MATRIX_CUSTOM_RGBR_PLAY);
        }

        return true;
    }

    return false;
}

void rgbrec_update_current_channel(uint8_t channel) {
    uint32_t addr = 0;

    if (channel >= RGBREC_CHANNEL_NUM) {
        return;
    }

    addr = (uint32_t)(RGBREC_EECONFIG_ADDR) + (channel * sizeof(rgbrec_buffer));
    eeprom_update_block(rgbrec_buffer, (void *)addr, sizeof(rgbrec_buffer));
}

bool rgbrec_end(uint8_t channel) {

    if (channel >= RGBREC_CHANNEL_NUM) {

        return false;
    }

    if ((rgbrec_info.state == RGBREC_STATE_ON) && (channel == rgbrec_info.channel)) {
        rgbrec_info.state = RGBREC_STATE_OFF;
        rgbrec_update_current_channel(rgbrec_info.channel);

        return true;
    }

    return false;
}

static inline void rgb_matrix_set_hs(int index, uint16_t hs) {

    RGB rgb = hs_to_rgb(HS_GET_H(hs), HS_GET_S(hs));
    rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
}

void rgbrec_play(uint8_t led_min, uint8_t led_max) {
    uint8_t row = 0xFF, col = 0xFF;
    uint16_t hs_color;

    rgbrec_info.value = rgb_matrix_get_val();

    for (uint8_t i = led_min; i < led_max; i++) {
        if (find_matrix_row_col(i, &row, &col)) {
            if (p_rgbrec_effects != NULL) {
                hs_color = p_rgbrec_effects[row][col];
                rgb_matrix_set_hs(i, hs_color);
            }
        }
    }
}

void rgbrec_set_close_all(uint8_t h, uint8_t s, uint8_t v) {

    if (!h && !s && !v) {
        memset(rgbrec_buffer, 0, sizeof(rgbrec_buffer));
    } else {
        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            for (uint8_t col = 0; col < MATRIX_COLS; col++) {
                rgbrec_buffer[row * MATRIX_COLS * col * 2]       = s;
                rgbrec_buffer[(row * MATRIX_COLS * col * 2) + 1] = v;
            }
        }
    }
}

void rgbrec_read_current_channel(uint8_t channel) {
    uint32_t addr = 0;

    if (channel >= RGBREC_CHANNEL_NUM) {

        return;
    }

    addr = (uint32_t)(RGBREC_EECONFIG_ADDR) + (channel * sizeof(rgbrec_buffer));
    eeprom_read_block(rgbrec_buffer, (void *)addr, sizeof(rgbrec_buffer));
}

bool rgbrec_is_started(void) {

    return (rgbrec_info.state == RGBREC_STATE_ON);
}

static inline void cycle_rgb_next_color(uint8_t row, uint8_t col) {

    if (p_rgbrec_effects == NULL) {

        return;
    }

    for (uint8_t index = 0; index < RGBREC_COLOR_NUM; index++) {
        if (rgbrec_hs_lists[index] == p_rgbrec_effects[row][col]) {
            index                      = ((index + 1) % RGBREC_COLOR_NUM);
            p_rgbrec_effects[row][col] = rgbrec_hs_lists[index];

            return;
        }
    }

    p_rgbrec_effects[row][col] = rgbrec_hs_lists[0];
}

bool rgbrec_register_record(uint16_t keycode, keyrecord_t *record) {
    (void)keycode;

    if (rgbrec_info.state == RGBREC_STATE_ON) {
        cycle_rgb_next_color(record->event.key.row, record->event.key.col);

        return true;
    }

    return false;
}

void eeconfig_init_user_datablock(void) {
    uint32_t addr = 0;

    addr = (uint32_t)(RGBREC_EECONFIG_ADDR);
    eeprom_update_block(rgbrec_default_effects, (void *)addr, sizeof(rgbrec_default_effects));
}

uint8_t find_index(void) {

    for (uint8_t index = 0; index < (sizeof(rgbmatrix_buff) / sizeof(rgbmatrix_buff[0])); index++) {
        if (rgb_matrix_get_mode() == rgbmatrix_buff[index]) {

            return index;
        }
    }

    return 0;
}

void record_rgbmatrix_increase(uint8_t *last_mode) {
    uint8_t index;

    index = find_index();
    if (rgbrec_info.state != RGBREC_STATE_ON) {
        index = (index + 1) % (sizeof(rgbmatrix_buff) / sizeof(rgbmatrix_buff[0]));
    }
    *last_mode = rgbmatrix_buff[index];
    rgb_matrix_mode(rgbmatrix_buff[index]);
    record_color_hsv(false);
}

uint8_t record_color_read_data(void) {
    uint8_t hs_mode    = find_index();
    const uint8_t *ptr = (const uint8_t *)(((uint32_t)CONFINFO_EECONFIG_ADDR + 4) + hs_mode);
    uint8_t hs_c       = eeprom_read_byte(ptr);

    if (hs_c > RGB_HSV_MAX) {
        return 0;
    } else {
        return hs_c;
    }
}

void record_color_hsv(bool status) {
    uint8_t temp;
    uint8_t rgb_hsv_index = record_color_read_data();

    for (uint8_t i = 0; i < (sizeof(sixth_gear_buff) / sizeof(sixth_gear_buff[0])); i++) {
        if (rgb_matrix_get_mode() == sixth_gear_buff[i]) {
            temp = RGB_HSV_MAX - 1;
            break;
        } else if (i == (sizeof(sixth_gear_buff) / sizeof(sixth_gear_buff[0]) - 1)) {
            temp = RGB_HSV_MAX;
        }
    }

    if (status) rgb_hsv_index = (rgb_hsv_index + 1) % temp;

    rgb_matrix_sethsv(rgb_hsvs[rgb_hsv_index][0], rgb_hsvs[rgb_hsv_index][1], rgb_matrix_get_val());

    uint8_t *ptr = (uint8_t *)(((uint32_t)CONFINFO_EECONFIG_ADDR + 4) + find_index());
    eeprom_write_byte(ptr, rgb_hsv_index);
}

bool rk_bat_req_flag;

void query(void){
    if (rk_bat_req_flag) {
#    ifdef RGBLIGHT_ENABLE
        for (uint8_t i = 0; i < (RGB_MATRIX_LED_COUNT - RGBLED_NUM); i++) {
            rgb_matrix_set_color(i, 0, 0, 0);
        }
#    else
        rgb_matrix_set_color_all(0x00, 0x00, 0x00);
#    endif
        for (uint8_t i = 0; i < 10; i++) {
            uint8_t mi_index[10] = RGB_MATRIX_BAT_INDEX_MAP;
            if ((i < (*md_getp_bat() / 10)) || (i < 1)) {
                if (*md_getp_bat() >= (IM_BAT_REQ_LEVEL1_VAL)) {
                    rgb_matrix_set_color(mi_index[i], IM_BAT_REQ_LEVEL1_COLOR);
                } else if (*md_getp_bat() >= (IM_BAT_REQ_LEVEL2_VAL)) {
                    rgb_matrix_set_color(mi_index[i], IM_BAT_REQ_LEVEL2_COLOR);
                } else {
                    rgb_matrix_set_color(mi_index[i], IM_BAT_REQ_LEVEL3_COLOR);
                }
            } else {
                rgb_matrix_set_color(mi_index[i], 0x00, 0x00, 0x00);
            }
        }
    }
}
