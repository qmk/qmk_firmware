// Copyright 2025 lucky(@lucky-zang)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "rgb_record.h"
#include "rgb_matrix.h"
#include "eeprom.h"
#include "eeconfig.h"
#include <stddef.h>

#define RGBREC_STATE_ON  1
#define RGBREC_STATE_OFF 0
#define RGBREC_COLOR_NUM (sizeof(rgbrec_kj_lists) / sizeof(rgbrec_kj_lists[0]))

typedef struct {
    uint8_t state;
    uint8_t channel;
    uint16_t value;
} rgbrec_info_t;

typedef uint16_t (*rgbrec_effects_t)[MATRIX_COLS];

rgbrec_effects_t p_rgbrec_effects = NULL;

static uint16_t rgbrec_kj_lists[] = RGB_RECORD_KJ_LISTS;
static uint8_t rgbrec_buffer[MATRIX_ROWS * MATRIX_COLS * 2];

//clang-format off
static const uint8_t rgbmatrix_buff[]   = {13, 15, 16, 24, 25, 26, 29, 37, 33, 34, 35, 43, 2, 5, 6, 9};
static const uint8_t sixth_gear_buff[]  = {6, 13, 15, 16, 25, 26, 34};
static uint8_t rgb_hsvs[RGB_HSV_MAX][2] = {
    {0,255},
    {85,255},
    {170,255},
    {43,255},
    {191,255},
    {128,255},
    {0,0},
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

static inline RGB kj_to_rgb(uint8_t h, uint8_t s) {

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
    if (channel >= RGBREC_CHANNEL_NUM) {
        return;
    }

    uint32_t offset = RGBREC_EECONFIG_CHANNEL_OFFSET(channel);
    eeconfig_update_user_datablock(rgbrec_buffer, offset, sizeof(rgbrec_buffer));
}

bool rgbrec_end(uint8_t channel, bool save_choose) {

    if (channel >= RGBREC_CHANNEL_NUM) {

        return false;
    }

    if ((rgbrec_info.state == RGBREC_STATE_ON) && (channel == rgbrec_info.channel)) {
        rgbrec_info.state = RGBREC_STATE_OFF;
        if (save_choose)
            rgbrec_update_current_channel(rgbrec_info.channel);

        return true;
    }

    return false;
}

static inline void rgb_matrix_set_kj(int index, uint16_t kj) {

    RGB rgb = kj_to_rgb(KJ_GET_H(kj), KJ_GET_S(kj));
    rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
}

void rgbrec_play(uint8_t led_min, uint8_t led_max) {
    uint8_t row = 0xFF, col = 0xFF;
    uint16_t kj_color;

    rgbrec_info.value = rgb_matrix_get_val();

    for (uint8_t i = led_min; i < led_max; i++) {
        if (find_matrix_row_col(i, &row, &col)) {
            if (p_rgbrec_effects != NULL) {
                kj_color = p_rgbrec_effects[row][col];
                rgb_matrix_set_kj(i, kj_color);
            }
        }
    }
}

void rgbrec_get_kj_buffer(uint16_t offset, uint16_t size, uint8_t *data) {
    uint32_t kj_total_size = (uint32_t)EECONFIG_RGBREC_USE_SIZE;

    if ((uint32_t)offset >= kj_total_size) {
        memset(data, 0, size);
        return;
    }

    uint32_t readable = (uint32_t)size;
    if ((uint32_t)offset + readable > kj_total_size) {
        readable = kj_total_size - (uint32_t)offset;
    }

    eeconfig_read_user_datablock(data, RGBREC_EECONFIG_OFFSET + (uint32_t)offset, readable);

    if (readable < (uint32_t)size) {
        memset(data + readable, 0, size - (uint16_t)readable);
    }
}

void rgbrec_set_kj_buffer(uint16_t offset, uint16_t size, uint8_t *data) {
    uint32_t kj_total_size = (uint32_t)EECONFIG_RGBREC_USE_SIZE;

    if ((uint32_t)offset >= kj_total_size) {
        return;
    }

    uint32_t writeable = (uint32_t)size;
    if ((uint32_t)offset + writeable > kj_total_size) {
        writeable = kj_total_size - (uint32_t)offset;
    }

    eeconfig_update_user_datablock(data, RGBREC_EECONFIG_OFFSET + (uint32_t)offset, writeable);
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
    if (channel >= RGBREC_CHANNEL_NUM) {
        return;
    }

    uint32_t offset = RGBREC_EECONFIG_CHANNEL_OFFSET(channel);
    eeconfig_read_user_datablock(rgbrec_buffer, offset, sizeof(rgbrec_buffer));
}

bool rgbrec_is_started(void) {

    return (rgbrec_info.state == RGBREC_STATE_ON);
}

static inline void cycle_rgb_next_color(uint8_t row, uint8_t col) {

    if (p_rgbrec_effects == NULL) {

        return;
    }

    for (uint8_t index = 0; index < RGBREC_COLOR_NUM; index++) {
        if (rgbrec_kj_lists[index] == p_rgbrec_effects[row][col]) {
            index                      = ((index + 1) % RGBREC_COLOR_NUM);
            p_rgbrec_effects[row][col] = rgbrec_kj_lists[index];

            return;
        }
    }

    p_rgbrec_effects[row][col] = rgbrec_kj_lists[0];
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
    eeconfig_update_user_datablock((const uint8_t *)rgbrec_default_effects,
                                   RGBREC_EECONFIG_OFFSET,
                                   (uint32_t)EECONFIG_RGBREC_USE_SIZE);

    {
        uint8_t conf_zero[EECONFIG_CONFINFO_USE_SIZE];
        memset(conf_zero, 0, sizeof(conf_zero));
        eeconfig_update_user_datablock(conf_zero, CONFINFO_EECONFIG_OFFSET, (uint32_t)EECONFIG_CONFINFO_USE_SIZE);
    }
}

uint8_t find_index(void) {

    for (uint8_t index = 0; index < (sizeof(rgbmatrix_buff) / sizeof(rgbmatrix_buff[0])); index++) {
        if (rgb_matrix_get_mode() == rgbmatrix_buff[index]) {

            return index;
        }
    }

    return 0;
}

uint8_t record_color_read_data(void) {  
    uint8_t kj_mode = find_index();
    uint8_t kj_c = 0;

    uint32_t offset = CONFINFO_EECONFIG_OFFSET + 4 + kj_mode;
    eeconfig_read_user_datablock(&kj_c, offset, 1);

    if (kj_c > RGB_HSV_MAX) {
        return 0;
    } else {
        return kj_c;
    }
}

void record_rgbmatrix_increase(uint8_t *last_mode) {
    uint8_t index;

    index = find_index();
    if (rgbrec_info.state != RGBREC_STATE_ON) {
        index = (index + 1) % (sizeof(rgbmatrix_buff) / sizeof(rgbmatrix_buff[0]));
    }
    *last_mode = rgbmatrix_buff[index];
    rgb_matrix_mode(rgbmatrix_buff[index]);
    //record_color_hsv(false);
    
    uint8_t rgb_hsv_index =  record_color_read_data();
    rgb_matrix_sethsv(rgb_hsvs[rgb_hsv_index][0], rgb_hsvs[rgb_hsv_index][1], rgb_matrix_get_val());

}

void rgbrec_switch_channel(uint8_t channel) {
    if (channel >= RGBREC_CHANNEL_NUM) {
        return;
    }

    rgbrec_read_current_channel(channel);
    rgbrec_end(channel,true);                  
    rgbrec_show(channel);
}

uint16_t rgbrec_get_kj_data(uint8_t channel, uint8_t row, uint8_t column) {
    if (channel >= RGBREC_CHANNEL_NUM || row >= MATRIX_ROWS || column >= MATRIX_COLS) {
        return 0x0000;
    }

    uint32_t offset = RGBREC_EECONFIG_CHANNEL_OFFSET(channel) + ((uint32_t)row * (uint32_t)MATRIX_COLS + (uint32_t)column) * 2U;
    uint8_t low = 0, high = 0;

    eeconfig_read_user_datablock(&low, offset, 1);
    eeconfig_read_user_datablock(&high, offset + 1, 1);

    return (uint16_t)low | ((uint16_t)high << 8);
}

void rgbrec_set_kj_data(uint8_t channel, uint8_t row, uint8_t column, uint16_t kj) {
    if (channel >= RGBREC_CHANNEL_NUM || row >= MATRIX_ROWS || column >= MATRIX_COLS) {
        return;
    }

    uint32_t offset = RGBREC_EECONFIG_CHANNEL_OFFSET(channel) + ((uint32_t)row * (uint32_t)MATRIX_COLS + (uint32_t)column) * 2U;
    uint8_t buf[2];
    buf[0] = (uint8_t)(kj & 0xFF);
    buf[1] = (uint8_t)(kj >> 8);

    eeconfig_update_user_datablock(buf, offset, 2);
}

uint8_t kj_record_color_read_data(void) {
    uint8_t kj_c = 0;
    eeconfig_read_user_datablock(&kj_c, CONFINFO_EECONFIG_OFFSET + 4U, 1);
    if (kj_c > RGB_HSV_MAX) {
        return 0;
    } else {
        return kj_c;
    }
}
uint8_t record_color_hsv(bool status) {
    uint8_t now_mode = rgb_matrix_get_mode();
    uint8_t temp = 0;

    for (uint8_t i = 0; i < (sizeof(sixth_gear_buff) / sizeof(sixth_gear_buff[0])); i++) {
        if (now_mode == sixth_gear_buff[i]) {
            temp = RGB_HSV_MAX - 1;
            break;
        }
    }

    if (!temp) {
        temp = RGB_HSV_MAX;
    }

    uint8_t rgb_hsv_index = record_color_read_data();

    rgb_hsv_index = (rgb_hsv_index + 1) % temp;

    rgb_matrix_sethsv(rgb_hsvs[rgb_hsv_index][0], rgb_hsvs[rgb_hsv_index][1], rgb_matrix_get_val());

    uint8_t kj_mode = find_index();
    uint32_t offset = CONFINFO_EECONFIG_OFFSET + 4 + kj_mode;
    eeconfig_update_user_datablock(&rgb_hsv_index, offset, 1);

    dprintf("rgb_hsv_index = %d\r\n", rgb_hsv_index);
    return rgb_hsv_index;
}

void kj_record_color_s_add(void) {
    uint8_t rgb_hsv_index = record_color_read_data();

    switch (rgb_hsv_index) {
        case 0: rgb_hsv_index = 0; break;
        case 1: rgb_hsv_index = 0; break;
        case 2: rgb_hsv_index = 1; break;
        case 3: rgb_hsv_index = 2; break;
        case 4: rgb_hsv_index = 3; break;
        case 5: rgb_hsv_index = 4; break;
        case 6: rgb_hsv_index = 5; break;
    }

    rgb_matrix_sethsv(rgb_hsvs[rgb_hsv_index][0], rgb_hsvs[rgb_hsv_index][1], rgb_matrix_get_val());

    uint8_t kj_mode = find_index();
    uint32_t offset = CONFINFO_EECONFIG_OFFSET + 4 + kj_mode;
    eeconfig_update_user_datablock(&rgb_hsv_index, offset, 1);
}

void kj_record_color_s_ins(void) {
    uint8_t rgb_hsv_index = record_color_read_data();

    switch (rgb_hsv_index) {
        case 0: rgb_hsv_index = 1; break;
        case 1: rgb_hsv_index = 2; break;
        case 2: rgb_hsv_index = 3; break;
        case 3: rgb_hsv_index = 4; break;
        case 4: rgb_hsv_index = 5; break;
        case 5: rgb_hsv_index = 6; break;
        case 6: rgb_hsv_index = 6; break;
    }

    rgb_matrix_sethsv(rgb_hsvs[rgb_hsv_index][0], rgb_hsvs[rgb_hsv_index][1], rgb_matrix_get_val());

    uint8_t kj_mode = find_index();
    uint32_t offset = CONFINFO_EECONFIG_OFFSET + 4 + kj_mode;
    eeconfig_update_user_datablock(&rgb_hsv_index, offset, 1);
}

