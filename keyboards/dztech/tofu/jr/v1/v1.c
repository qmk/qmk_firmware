/* Copyright 2022 DZTECH <moyi4681@live.cn>
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

#include "v1.h"

#ifdef RGB_MATRIX_ENABLE

const is31_led PROGMEM g_is31_leds[DRIVER_LED_TOTAL] = {
    { 1, K_12, J_12, L_12 },
    { 1, K_11, J_11, L_11 },
    { 1, K_10, J_10, L_10 },
    { 1, K_9,  J_9,  L_9 },
    { 1, K_8,  J_8,  L_8 },
    { 1, K_7,  J_7,  L_7 },
    { 1, K_6,  J_6,  L_6 },
    { 1, K_5,  J_5,  L_5 },
    { 1, K_4,  J_4,  L_4 },
    { 1, K_3,  J_3,  L_3 },
    { 1, K_2,  J_2,  L_2 },    
    { 1, K_1,  J_1,  L_1 }, 
    { 1, H_1,  G_1,  I_1 }, 
    { 1, H_2,  G_2,  I_2 }, 
    { 1, H_3,  G_3,  I_3 },
    
    { 0, B_12, A_12, C_12 },
    { 0, B_11, A_11, C_11 }, 
    { 0, B_10, A_10, C_10 },
    { 0, B_9,  A_9,  C_9 }, 
    { 0, B_8,  A_8,  C_8 }, 
    { 0, B_7,  A_7,  C_7 },
    { 0, B_6,  A_6,  C_6 },
    { 0, B_5,  A_5,  C_5 },
    { 0, B_4,  A_4,  C_4 },
    { 0, B_3,  A_3,  C_3 },
    { 0, B_2,  A_2,  C_2 },
    { 0, B_1,  A_1,  C_1 }, 
    { 1, H_6,  G_6,  I_6 }, 
    { 1, H_5,  G_5,  I_5 }, 
    { 1, H_4,  G_4,  I_4 }, 
    
    { 0, E_12, D_12, F_12 },
    { 0, E_11, D_11, F_11 },
    { 0, E_10, D_10, F_10 },
    { 0, E_9,  D_9,  F_9 },
    { 0, E_8,  D_8,  F_8 },
    { 0, E_7,  D_7,  F_7 },
    { 0, E_6,  D_6,  F_6 },
    { 0, E_5,  D_5,  F_5 },
    { 0, E_4,  D_4,  F_4 },
    { 0, E_3,  D_3,  F_3 },
    { 0, E_2,  D_2,  F_2 },
    { 0, E_1,  D_1,  F_1 },          
    { 1, H_7,  G_7,  I_7 }, 
    { 1, H_8,  G_8,  I_8 },   
    
    { 0, H_12, G_12, I_12 },
    { 0, H_11, G_11, I_11 },
    { 0, H_10, G_10, I_10 },
    { 0, H_9,  G_9,  I_9 },
    { 0, H_8,  G_8,  I_8 },
    { 0, H_7,  G_7,  I_7 },
    { 0, H_6,  G_6,  I_6 },
    { 0, H_5,  G_5,  I_5 },
    { 0, H_4,  G_4,  I_4 },
    { 0, H_3,  G_3,  I_3 },
    { 0, H_2,  G_2,  I_2 },
    { 0, H_1,  G_1,  I_1 },
    { 0, K_9,  J_9,  L_9 },
    { 0, K_8,  J_8,  L_8 }, 
    
    { 0, K_12, J_12, L_12 },
    { 0, K_11, J_11, L_11 },
    { 0, K_10, J_10, L_10 },
    { 0, K_7,  J_7,  L_7 },
    { 0, K_4,  J_4,  L_4 },
    { 0, K_3,  J_3,  L_3 },
    { 0, K_2,  J_2,  L_2 },
    { 0, K_1,  J_1,  L_1 },    
    { 0, K_6,  J_6,  L_6 },
    { 0, K_5,  J_5,  L_5 },                                                                                                                          
};
led_config_t g_led_config = { {
    {  0,  1,  2,  3,      4,      5,      6,  7,      8,  9,  10, 11,     12,     13,     14 },
    {  15, 16, 17, 18,     19,     20,     21, 22,     23, 24, 25, 26,     27,     28,     29 },
    {  30, 31, 32, 33,     34,     35,     36, 37,     38, 39, 40, 41,     42,     NO_LED, 43 },
    {  44, 45, 46, 47,     48,     49,     50, 51,     52, 53, 54, 55,     NO_LED, 56,     57 },
    {  58, 59, 60, NO_LED, NO_LED, NO_LED, 61, NO_LED, 62, 63, 64, NO_LED, 65,     66,     67 }
}, {
    {0,0},{15,0},{30,0},{45,0},{60,0},{75,0},{90,0},{105,0},{120,0},{135,0},{150,0},{165,0},{180,0},{203,0},{224,0},
	{4,16},{23,16},{38,16},{53,16},{68,16},{83,16},{98,16},{113,16},{128,16},{143,16},{158,16},{173,16},{188,16},{206,16},{224,16},
	{6,32},{26,32},{41,32},{56,32},{71,32},{86,32},{101,32},{116,32},{131,32},{146,32},{161,32},{176,32},{201,32},{224,32},
	{9,48},{34,48},{49,48},{64,48},{79,48},{94,48},{109,48},{124,48},{139,48},{154,48},{169,48},{189,48},{210,48},{224,48},
    {2,64},{21,64},{39,64},{96,64},{150,64},{165,64},{180,64},{195,64},{210,64},{224,64}
}, {
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    1, 1, 1, 4, 1, 1, 1, 1, 1, 1	
} };

__attribute__ ((weak))
void rgb_matrix_indicators_user(void)
{
    if (host_keyboard_led_state().caps_lock)
    {
        rgb_matrix_set_color(30, 0xFF, 0xFF, 0xFF);
    }
}
#endif
