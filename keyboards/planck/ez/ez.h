/* Copyright 2018 Jack Humbert <jack.humb@gmail.com>
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

#include "planck.h"

#ifdef KEYBOARD_planck_ez_glow
#    include "glow.h"
#endif

#define LAYOUT_planck_1x2uC( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, \
    k30, k31, k32, k33, k34,    k35,   k37, k38, k39, k3a, k3b \
) \
{ \
    { k00, k01, k02, k03, k04, k05   }, \
    { k10, k11, k12, k13, k14, k15   }, \
    { k20, k21, k22, k23, k24, k25   }, \
    { k30, k31, k32, k3a, k3b, KC_NO }, \
    { k06, k07, k08, k09, k0a, k0b   }, \
    { k16, k17, k18, k19, k1a, k1b   }, \
    { k26, k27, k28, k29, k2a, k2b   }, \
    { k37, k38, k39, k33, k34, k35   } \
}

#define LAYOUT_ortho_4x12( \
    k00, k01, k02, k03, k04, k05, k06,   k07, k08, k09, k0a, k0b, \
    k10, k11, k12, k13, k14, k15, k16,   k17, k18, k19, k1a, k1b, \
    k20, k21, k22, k23, k24, k25, k26,   k27, k28, k29, k2a, k2b, \
    k30, k31, k32, k33, k34, k35, KC_NO, k37, k38, k39, k3a, k3b  \
) \
LAYOUT_planck_1x2uC( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, \
    k30, k31, k32, k33, k34,    k35,   k37, k38, k39, k3a, k3b  \
)

#define LAYOUT_planck_mit LAYOUT_planck_1x2uC
#define LAYOUT_planck_grid LAYOUT_ortho_4x12

void planck_ez_right_led_on(void);
void planck_ez_right_led_off(void);
void planck_ez_right_led_level(uint8_t level);
void planck_ez_left_led_on(void);
void planck_ez_left_led_off(void);
void planck_ez_left_led_level(uint8_t level);

enum planck_ez_keycodes {
    LED_LEVEL = SAFE_RANGE,
    TOGGLE_LAYER_COLOR,
    EZ_SAFE_RANGE,
};

#ifndef WEBUSB_ENABLE
#    define WEBUSB_PAIR KC_NO
#endif

typedef union {
  uint32_t raw;
  struct {
    uint8_t      led_level :3;
    bool         disable_layer_led   :1;
    bool         rgb_matrix_enable   :1;
  };
} keyboard_config_t;

extern keyboard_config_t keyboard_config;
