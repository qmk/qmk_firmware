/* Copyright 2023 temp4gh
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

#include "quantum.h"
#include "spi_master.h"
#include "config.h"

#include "ak84bt.h"
#include "print.h"

//k_mode_t user_k_mode;

#ifdef RGB_MATRIX_ENABLE
const is31_led PROGMEM g_is31_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */
      
    {0, G_1,    I_1,    H_1},        
    //{0, G_2,    I_2,    H_2},        
    {0, G_3,    I_3,    H_3},    
    {0, G_4,    I_4,    H_4},    
    {0, G_5,    I_5,    H_5},    
    {0, G_6,    I_6,    H_6},    
    {0, G_7,    I_7,    H_7},    
    {0, G_8,    I_8,    H_8},    
    {0, G_9,    I_9,    H_9},    
    {0, G_10,   I_10,   H_10},    
    {0, G_11,   I_11,   H_11},    
    {0, G_12,   I_12,   H_12},    
    {0, G_13,   I_13,   H_13},    
    {0, G_14,   I_14,   H_14},    
    {0, G_15,   I_15,   H_15},    
  
    {0, D_1,    F_1,    E_1},        
    {0, D_2,    F_2,    E_2},   
    {0, D_3,    F_3,    E_3},    
    {0, D_4,    F_4,    E_4},    
    {0, D_5,    F_5,    E_5},    
    {0, D_6,    F_6,    E_6},    
    {0, D_7,    F_7,    E_7},    
    {0, D_8,    F_8,    E_8},    
    {0, D_9,    F_9,    E_9},    
    {0, D_10,   F_10,   E_10},    
    {0, D_11,   F_11,   E_11},    
    {0, D_12,   F_12,   E_12},    
    {0, D_13,   F_13,   E_13},    
    {0, D_14,   F_14,   E_14},    
    {0, D_15,   F_15,   E_15},    

    {0, A_1,    C_1,    B_1},        
    {0, A_2,    C_2,    B_2},   
    {0, A_3,    C_3,    B_3},    
    {0, A_4,    C_4,    B_4},    
    {0, A_5,    C_5,    B_5},    
    {0, A_6,    C_6,    B_6},    
    {0, A_7,    C_7,    B_7},    
    {0, A_8,    C_8,    B_8},    
    {0, A_9,    C_9,    B_9},    
    {0, A_10,   C_10,   B_10},    
    {0, A_11,   C_11,   B_11},    
    {0, A_12,   C_12,   B_12},    
    {0, A_13,   C_13,   B_13},    
    {0, A_14,   C_14,   B_14},    
    {0, A_15,   C_15,   B_15},    
    
    {1, G_1,    I_1,    H_1},        
    {1, G_2,    I_2,    H_2},   
    {1, G_3,    I_3,    H_3},    
    {1, G_4,    I_4,    H_4},    
    {1, G_5,    I_5,    H_5},    
    {1, G_6,    I_6,    H_6},    
    {1, G_7,    I_7,    H_7},    
    {1, G_8,    I_8,    H_8},    
    {1, G_9,    I_9,    H_9},    
    {1, G_10,   I_10,   H_10},    
    {1, G_11,   I_11,   H_11},    
    {1, G_12,   I_12,   H_12},    
    {1, G_13,   I_13,   H_13},    
    {1, G_14,   I_14,   H_14},    
    {1, G_15,   I_15,   H_15},    

    {1, D_1,    F_1,    E_1},        
    {1, D_2,    F_2,    E_2},   
    {1, D_3,    F_3,    E_3},    
    {1, D_4,    F_4,    E_4},    
    {1, D_5,    F_5,    E_5},    
    {1, D_6,    F_6,    E_6},    
    {1, D_7,    F_7,    E_7},    
    {1, D_8,    F_8,    E_8},    
    {1, D_9,    F_9,    E_9},    
    {1, D_10,   F_10,   E_10},    
    {1, D_11,   F_11,   E_11},    
    {1, D_12,   F_12,   E_12},    
    {1, D_13,   F_13,   E_13},    
    {1, D_14,   F_14,   E_14},    
    {1, D_15,   F_15,   E_15},    

    {1, A_1,    C_1,    B_1},        
    {1, A_2,    C_2,    B_2},   
    {1, A_3,    C_3,    B_3},    
    //{1, A_4,    C_4,    B_4},    
    {1, A_5,    C_5,    B_5},    
    {1, A_6,    C_6,    B_6},    
    {1, A_7,    C_7,    B_7},    
    {1, A_8,    C_8,    B_8},    
    {1, A_9,    C_9,    B_9},    
    {1, A_10,   C_10,   B_10},    
    {1, A_11,   C_11,   B_11},    
    {1, A_12,   C_12,   B_12},    
    {1, A_13,   C_13,   B_13},    
    {1, A_14,   C_14,   B_14},    
    {1, A_15,   C_15,   B_15},

    //LOCK LED         
    {0, G_2,    I_2,    H_2},   //LED D5,lock led 
    {1, A_4,    C_4,    B_4}    //LED D18,lock led    
};

#define N_L NO_LED 
led_config_t g_led_config = { {  
  { 0,   N_L,  1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12, 13, N_L},
  { 14,  15,  16,   17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  N_L},
  { 29,  30,  31,   32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  N_L},
  { 44,  45,  46,   47,  48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  N_L},
  { 59,  60,  61,   62,  63,  64,  65,  66,  67,  68,  69,  70,  71,  72,  73,  N_L},  
  { 74,  75,  76,   SCROLLLOCK_LED_DRV_PIN,  NUMLOCK_LED_DRV_PIN, N_L, 80,  N_L,  N_L,  82,  83,  84,  85,  86,  87,  N_L}
}, {  
  {7, 2},             {34, 2},  {48, 2},  {61, 2},  {75, 2},   {95, 2},  {109, 2},  {122, 2},  {136, 2},  {157, 2},  {170, 2},  {184, 2},  {198, 2},  {217, 2},
  {7, 14},  {20, 14}, {34, 14}, {48, 14}, {61, 14}, {75, 14},  {89, 14}, {102, 14}, {116, 14}, {129, 14}, {143, 14}, {157, 14}, {170, 14}, {190, 14}, {217, 14},
  {10, 24}, {27, 24}, {40, 24}, {54, 24}, {68, 24}, {81, 24},  {95, 24}, {109, 24}, {122, 24}, {136, 24}, {150, 24}, {163, 24}, {177, 24}, {194, 24}, {217, 24},
  {12, 34}, {30, 34}, {44, 34}, {58, 34}, {71, 34}, {85, 34},  {99, 34}, {112, 34}, {126, 34}, {140, 34}, {153, 34}, {167, 34}, {180, 34}, {189, 34}, {217, 34},
  {8, 44},  {24, 44}, {38, 44}, {51, 44}, {65, 44}, {78, 44},  {92, 44}, {106, 44}, {119, 44}, {133, 44}, {147, 44}, {160, 44}, {179, 44}, {201, 46}, {217, 44},
  {8, 54},  {25, 54}, {43, 54}, {67, 57}, {80, 57}, {94, 54}, {107, 57}, {120, 57}, {143, 54}, {157, 54}, {170, 54}, {187, 56}, {201, 56}, {214, 56}, {207,23}, {207, 27}
}, {
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 
} };

uint8_t get_row_col_led_index(int row, int col)
{
    if((row < MATRIX_ROWS) && (col < MATRIX_COLS))
    {
        return(g_led_config.matrix_co[row][col]);
    }

    return(NO_LED);
}
#endif

void matrix_scan_kb(void)
{        
    matrix_scan_user();
}

void keyboard_post_init_kb(void) 
{        
    keyboard_post_init_user();
}

void housekeeping_task_user(void) 
{
}

#define IS31FL3733_POWERON_PIN B2
void init_set_IS31FL3733_poweron(void)
{
    palSetLineMode(IS31FL3733_POWERON_PIN, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLine(IS31FL3733_POWERON_PIN);
}

void board_init(void) 
{
    AFIO->MAPR |= (1<<26);

    palSetLineMode(CAPS_LOCK_DRV_PIN, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLine(CAPS_LOCK_DRV_PIN);    

#if 1    
    palSetPadMode(GPIOA, 13, PAL_MODE_OUTPUT_PUSHPULL); 
    palSetPadMode(GPIOA, 14, PAL_MODE_OUTPUT_PUSHPULL); 
    palSetPadMode(GPIOA, 15, PAL_MODE_OUTPUT_PUSHPULL); 
#endif

    init_set_IS31FL3733_poweron();        
}

