/* Copyright 2019 bemeier
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#define BMLED_SMOOTH_NVALS 3
#define BMLED_SMOOTH_INTERVAL 20 

#include "quantum.h"
//#include "dynamic_macro.h"

#define EECONFIG_BMEK_0 (uint32_t *) 36
#define EECONFIG_BMEK_1 (uint32_t *) 40
#define EECONFIG_BMEK_2 (uint32_t *) 44
#define EECONFIG_BMEK_3 (uint32_t *) 48
#define EECONFIG_BMEK_4 (uint32_t *) 52

typedef union {
  struct {
    uint32_t raw_hue0;
    uint32_t raw_hue1;
    uint32_t raw_hue2;
    uint32_t raw_hue3;
    uint32_t raw_bri_sat_fade;
  };
  struct {
    float layer_hues[4];
    uint8_t brightness;
    uint8_t saturation;
	uint8_t fade_span;
    uint8_t unused;
  };
} kb_config_big_t;

enum bm_keycodes {
  BM_RST = SAFE_RANGE,
  BM_LED,
  BM_WIPE,
  BM_HI_1,
  BM_HI_2,
  BM_HI_3,
  BM_HI_4,
  BM_HD_1,
  BM_HD_2,
  BM_HD_3,
  BM_HD_4,
  BM_SI,
  BM_SD,
  BM_BI,
  BM_BD,
  BM_FI,
  BM_FD,
  BM_MULT,
  BM_SAFE_RANGE
};

#define LAYOUT(\
    KC_40, KC_41, KC_42, KC_43, KC_44, KC_45, KC_46, KC_47,     KC_48, KC_49, KC_4A, KC_4B, KC_4C, KC_4D, KC_4E, KC_3E,\
   KC_30,  KC_31,  KC_32, KC_33, KC_34, KC_35, KC_36,         KC_37, KC_38, KC_39, KC_3A, KC_3B, KC_3C, KC_3D,    KC_2E,\
  KC_20,   KC_21,   KC_22, KC_23, KC_24, KC_25, KC_26,         KC_27, KC_28, KC_29, KC_2A, KC_2B,     KC_2C,       KC_2D,\
 KC_10,    KC_11,     KC_12,  KC_13, KC_14, KC_15, KC_16,    KC_17, KC_18, KC_19, KC_1A,  KC_1B, KC_1C,  KC_1D,     KC_1E,\
                      KC_02,  KC_03,        KC_05,                  KC_08,        KC_0A,  KC_0B                            \
   ) { \
   { KC_NO, KC_NO, KC_02, KC_03, KC_NO, KC_05, KC_NO, KC_NO, KC_08, KC_NO, KC_0A, KC_0B, KC_NO, KC_NO, KC_NO },\
   { KC_10, KC_11, KC_12, KC_13, KC_14, KC_15, KC_16, KC_17, KC_18, KC_19, KC_1A, KC_1B, KC_1C, KC_1D, KC_1E },\
   { KC_20, KC_21, KC_22, KC_23, KC_24, KC_25, KC_26, KC_27, KC_28, KC_29, KC_2A, KC_2B, KC_2C, KC_2D, KC_2E },\
   { KC_30, KC_31, KC_32, KC_33, KC_34, KC_35, KC_36, KC_37, KC_38, KC_39, KC_3A, KC_3B, KC_3C, KC_3D, KC_3E },\
   { KC_40, KC_41, KC_42, KC_43, KC_44, KC_45, KC_46, KC_47, KC_48, KC_49, KC_4A, KC_4B, KC_4C, KC_4D, KC_4E } \
}


