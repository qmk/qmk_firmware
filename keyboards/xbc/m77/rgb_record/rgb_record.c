// Copyright 2025 lucky(@lucky-zang)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "rgb_record.h"
#include "rgb_matrix.h"
#include "eeprom.h"
#include <stddef.h>

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

uint8_t find_index(void) {

    for (uint8_t index = 0; index < (sizeof(rgbmatrix_buff) / sizeof(rgbmatrix_buff[0])); index++) {
        if (rgb_matrix_get_mode() == rgbmatrix_buff[index]) {

            return index;
        }
    }

    return 0;
}

uint8_t record_color_read_data(void) {
    uint8_t kj_mode    = find_index();
    const uint8_t *ptr = (const uint8_t *)(((uint32_t)CONFINFO_EECONFIG_ADDR + 4) + kj_mode);
    uint8_t kj_c       = eeprom_read_byte(ptr);

    if (kj_c > RGB_HSV_MAX) {
        return 0;
    } else {
        return kj_c;
    }
}

extern bool kj_get_rgb_mode_status(void);
void record_rgbmatrix_increase(uint8_t *last_mode) {
    uint8_t index;

    index = find_index();
    index = (index + 1) % (sizeof(rgbmatrix_buff) / sizeof(rgbmatrix_buff[0]));
    *last_mode = rgbmatrix_buff[index];
    rgb_matrix_mode(rgbmatrix_buff[index]);
    
    uint8_t rgb_hsv_index =  record_color_read_data();
    rgb_matrix_sethsv(rgb_hsvs[rgb_hsv_index][0], rgb_hsvs[rgb_hsv_index][1], rgb_matrix_get_val());

}

uint8_t kj_record_color_read_data(void) {
    const uint8_t *ptr = (const uint8_t *)(((uint32_t)CONFINFO_EECONFIG_ADDR + 4));
    uint8_t kj_c       = eeprom_read_byte(ptr);

    if (kj_c > RGB_HSV_MAX) {
        return 0;
    } else {
        return kj_c;
    }
}

uint8_t record_color_hsv(bool status) {
    uint8_t now_mode = rgb_matrix_get_mode();
    uint8_t temp = 0;

    for (uint8_t i = 0; i < (sizeof(sixth_gear_buff)/sizeof(sixth_gear_buff[0])); i++) {
        if (now_mode == sixth_gear_buff[i]) {
            temp = RGB_HSV_MAX - 1;
            break;
        }
    }

    if (!temp) {
        temp = RGB_HSV_MAX;
    }

    uint8_t rgb_hsv_index = kj_record_color_read_data();

    rgb_hsv_index = (rgb_hsv_index + 1) % temp;

    rgb_matrix_sethsv(rgb_hsvs[rgb_hsv_index][0],rgb_hsvs[rgb_hsv_index][1], rgb_matrix_get_val());

    uint8_t *ptr = (uint8_t *)(((uint32_t)CONFINFO_EECONFIG_ADDR + 4));
    eeprom_write_byte(ptr, rgb_hsv_index);
    dprintf("rgb_hsv_index = %d\r\n",rgb_hsv_index);
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

    rgb_matrix_sethsv(rgb_hsvs[rgb_hsv_index][0],rgb_hsvs[rgb_hsv_index][1], rgb_matrix_get_val());

    uint8_t *ptr = (uint8_t *)(((uint32_t)CONFINFO_EECONFIG_ADDR + 4) + find_index());
    eeprom_write_byte(ptr, rgb_hsv_index);
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

    rgb_matrix_sethsv(rgb_hsvs[rgb_hsv_index][0],rgb_hsvs[rgb_hsv_index][1], rgb_matrix_get_val());

    uint8_t *ptr = (uint8_t *)(((uint32_t)CONFINFO_EECONFIG_ADDR + 4) + find_index());
    eeprom_write_byte(ptr, rgb_hsv_index);
}

