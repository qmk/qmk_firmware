/* Copyright 2019 Yiancar
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
#ifndef RGB_BACKLIGHT_NK65
#error RGB_BACKLIGHT_NK65 not defined, recheck config.h
#endif

#include "nk65.h"
#include "drivers/led/issi/is31fl3733.h"

#if defined(RGB_MATRIX_ENABLE) || defined(RGB_BACKLIGHT_NK65)
const is31fl3733_led_t PROGMEM g_is31fl3733_leds[IS31FL3733_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |      G location
 *   |  |      |      B location
 *   |  |      |      | */
    {0, B_1,   A_1,   C_1}, //LA1
    {0, E_1,   D_1,   F_1}, //LA2
    {0, H_1,   G_1,   I_1}, //LA3
    {0, K_1,   J_1,   L_1}, //LA4
    {0, B_2,   A_2,   C_2}, //LA5
    {0, E_2,   D_2,   F_2}, //LA6
    {0, H_2,   G_2,   I_2}, //LA7
    {0, K_2,   J_2,   L_2}, //LA8
    {0, B_3,   A_3,   C_3}, //LA9
    {0, E_3,   D_3,   F_3}, //LA10
    {0, H_3,   G_3,   I_3}, //LA11
    {0, K_3,   J_3,   L_3}, //LA12
    {0, B_4,   A_4,   C_4}, //LA13
    {0, E_4,   D_4,   F_4}, //LA14
    {0, H_4,   G_4,   I_4}, //LA15
    {0, K_4,   J_4,   L_4}, //LA16
    {0, B_5,   A_5,   C_5}, //LA17
    {0, E_5,   D_5,   F_5}, //LA18
    {0, H_5,   G_5,   I_5}, //LA19
    {0, K_5,   J_5,   L_5}, //LA20
    {0, B_6,   A_6,   C_6}, //LA21
    {0, E_6,   D_6,   F_6}, //LA22
    {0, H_6,   G_6,   I_6}, //LA23
    {0, K_6,   J_6,   L_6}, //LA24
    {0, B_7,   A_7,   C_7}, //LA25
    {0, E_7,   D_7,   F_7}, //LA26
    {0, H_7,   G_7,   I_7}, //LA27
    {0, K_7,   J_7,   L_7}, //LA28
    {0, B_8,   A_8,   C_8}, //LA29
    {0, E_8,   D_8,   F_8}, //LA30
    {0, H_8,   G_8,   I_8}, //LA31
    {0, K_8,   J_8,   L_8}, //LA32
    {0, B_9,   A_9,   C_9}, //LA33
    {0, E_9,   D_9,   F_9}, //LA34
    {0, H_9,   G_9,   I_9}, //LA35
    {0, K_9,   J_9,   L_9}, //LA36
    {0, B_10,  A_10,  C_10}, //LA37
    {0, E_10,  D_10,  F_10}, //LA38
    {0, H_10,  G_10,  I_10}, //LA39
    {0, K_10,  J_10,  L_10}, //LA40
    {0, B_11,  A_11,  C_11}, //LA41
    {0, E_11,  D_11,  F_11}, //LA42
    {0, H_11,  G_11,  I_11}, //LA43
    {0, K_11,  J_11,  L_11}, //LA44
    {0, B_12,  A_12,  C_12}, //LA45
    {0, E_12,  D_12,  F_12}, //LA46
    {0, H_12,  G_12,  I_12}, //LA47
    {0, K_12,  J_12,  L_12}, //LA48
    {0, B_13,  A_13,  C_13}, //LA49
    {0, E_13,  D_13,  F_13}, //LA50
    {0, H_13,  G_13,  I_13}, //LA51
    {0, K_13,  J_13,  L_13}, //LA52
    {0, B_14,  A_14,  C_14}, //LA53
    {0, E_14,  D_14,  F_14}, //LA54
    {0, H_14,  G_14,  I_14}, //LA55
    {0, K_14,  J_14,  L_14}, //LA56
    {0, B_15,  A_15,  C_15}, //LA57
    {0, E_15,  D_15,  F_15}, //LA58
    {0, H_15,  G_15,  I_15}, //LA59
    {0, K_15,  J_15,  L_15}, //LA60
    {0, B_16,  A_16,  C_16}, //LA61
    {0, E_16,  D_16,  F_16}, //LA62
    {0, H_16,  G_16,  I_16}, //LA63
    {0, K_16,  J_16,  L_16}, //LA64

    {1, B_1,   A_1,   C_1}, //LB1
    {1, E_1,   D_1,   F_1}, //LB2
    {1, H_1,   G_1,   I_1}, //LB3
    {1, K_1,   J_1,   L_1}, //LB4
    {1, B_2,   A_2,   C_2}, //LB5
    {1, E_2,   D_2,   F_2}, //LB6
    {1, H_2,   G_2,   I_2}, //LB7
    {1, K_2,   J_2,   L_2}, //LB8
    {1, B_3,   A_3,   C_3}, //LB9
    {1, E_3,   D_3,   F_3}, //LB10
    {1, H_3,   G_3,   I_3}, //LB11
    {1, K_3,   J_3,   L_3}, //LB12
    {1, B_4,   A_4,   C_4}, //LB13
    {1, E_4,   D_4,   F_4}, //LB14
    {1, H_4,   G_4,   I_4}, //LB15
    {1, K_4,   J_4,   L_4}, //LB16
    {1, B_5,   A_5,   C_5}, //LB17
    {1, E_5,   D_5,   F_5}, //LB18
    {1, H_5,   G_5,   I_5}, //LB19
    {1, K_5,   J_5,   L_5}, //LB20
    {1, B_6,   A_6,   C_6}, //LB21
    {1, E_6,   D_6,   F_6}, //LB22
    {1, H_6,   G_6,   I_6}, //LB23
    {1, K_6,   J_6,   L_6}, //LB24
    {1, B_7,   A_7,   C_7}, //LB25
    {1, E_7,   D_7,   F_7}, //LB26
    {1, H_7,   G_7,   I_7}, //LB27
    {1, K_7,   J_7,   L_7}, //LB28
    {1, B_8,   A_8,   C_8}, //LB29
    {1, E_8,   D_8,   F_8}, //LB30
    {1, H_8,   G_8,   I_8}, //LB31
    {1, K_8,   J_8,   L_8}, //LB32
    {1, B_9,   A_9,   C_9}, //LB33
    {1, E_9,   D_9,   F_9}, //LB34
    {1, H_9,   G_9,   I_9}, //LB35
    {1, K_9,   J_9,   L_9}, //LB36
    {1, B_10,  A_10,  C_10}, //LB37
    {1, E_10,  D_10,  F_10}, //LB38
    {1, H_10,  G_10,  I_10}, //LB39
    {1, K_10,  J_10,  L_10}, //LB40
    {1, B_11,  A_11,  C_11}, //LB41
    {1, E_11,  D_11,  F_11}, //LB42
    {1, H_11,  G_11,  I_11}, //LB43
    {1, K_11,  J_11,  L_11}, //LB44
    {1, B_12,  A_12,  C_12}, //LB45
    {1, E_12,  D_12,  F_12}, //LB46
    {1, H_12,  G_12,  I_12}, //LB47
    {1, K_12,  J_12,  L_12}, //LB48
    {1, B_13,  A_13,  C_13}, //LB49
    {1, E_13,  D_13,  F_13}, //LB50
    {1, H_13,  G_13,  I_13}, //LB51
    {1, K_13,  J_13,  L_13}, //LB52
    {1, B_14,  A_14,  C_14}, //LB53
    {1, E_14,  D_14,  F_14}, //LB54
    {1, H_14,  G_14,  I_14}, //LB55
    {1, K_14,  J_14,  L_14}, //LB56
    {1, B_15,  A_15,  C_15}, //LB57
    {1, E_15,  D_15,  F_15}, //LB58
    {1, H_15,  G_15,  I_15}, //LB59
    {1, K_15,  J_15,  L_15}, //LB60
    {1, B_16,  A_16,  C_16}, //LB61
    {1, E_16,  D_16,  F_16}, //LB62
    {1, H_16,  G_16,  I_16}, //LB63
    {1, K_16,  J_16,  L_16}, //LB64
};
#endif

/* Indicator LEDS are part of the LED driver
 * Top LED is blue only. LED driver 2 RGB 7 Green channel
 * Middle LED is blue and red. LED driver 2 RGB 6 Red and Blue channel
 * Bottom LED is red only LED driver 2 RGB 6 Green channel.
 */
void led_update_ports(led_t led_state) {
    if (led_state.caps_lock) {
        is31fl3733_set_color( 7+64-1, 0, 255, 0 );
    } else {
        is31fl3733_set_color( 7+64-1, 0, 0, 0 );
    }
}

__attribute__((weak)) layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t R = 0;
    uint8_t G = 0;
    uint8_t B = 0;
    if (state & (1UL << 1)) {
        R = 255;
        B = 255;
    }
    if (state & (1UL << 2)) {
        G = 255;
    }

    is31fl3733_set_color( 6+64-1, R, G, B );
  return state;
}
