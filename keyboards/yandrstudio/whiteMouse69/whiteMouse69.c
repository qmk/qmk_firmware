/* Copyright 2021 JasonRen(biu)
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
#include QMK_KEYBOARD_H



#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = {
    {
        {71 ,70 ,69 ,68 ,67 ,66 ,65 ,64 ,63 ,62 ,61 ,60 ,59 ,58 ,57},
        {56 ,55 ,54 ,53 ,52 ,51 ,50 ,49 ,48 ,47 ,46 ,45 ,44 ,43 ,42}, \
        {41 ,40 ,39 ,38 ,37 ,36 ,35 ,34 ,33 ,32 ,31 ,30 ,29 ,28}, \
        {27 ,26 ,25 ,24 ,23 ,22 ,21 ,20 ,19 ,18 ,17 ,16 ,15 ,14 ,13}, \
        {12 ,11 ,10 ,9 ,NO_LED,8 ,7 ,NO_LED,6 ,5 ,4 ,3 ,2 ,1 ,0}, \
    },
    {
      // LED Index to Physical Position
      {32,128}, {32,120}, {32,112}, {32,104}, {32,96},   {32,88},  {32,80},  {32,72}, {32,64},  {32,56},  {32,48},  {32,40},  {32,32},       {32,20},      {32,5},
        {24,133}, {24,122}, {24,114}, {24,106},  {24,98},   {24,90},  {24,82},  {24,74}, {24,66},  {24,58},  {24,50},     {24,37},      {24,24},  {24,16},  {24,5},
          {16,133}, {16,120}, {16,112},  {16,104},  {16,96},   {16,88},  {16,80},  {16,72}, {16,64},  {16,56},          {16,40},         {16,24},  {16,16},  {16,5},
            {8,123},    {8,112},   {8,104},   {8,96},   {8,88},   {8,80},     {8,72},   {8,64},   {8,56},   {8,48},  {8,40},   {8,32},   {8,24},   {8,16},    {8,5},
      {0,132},  {0,128},  {0,120},              {0,104},               {0,88},{0,80},                {0,56},   {0,48},  {0,40},   {0,32},   {0,24},   {0,16},   {0,5},

    },
    {
      // LED Index to Flag
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
      4, 4 
    }
};


#endif

#ifdef RGB_DISABLE_WHEN_USB_SUSPENDED
void suspend_power_down_kb(void) {
    rgb_matrix_set_suspend_state(true);
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    rgb_matrix_set_suspend_state(false);
    suspend_wakeup_init_user();
}
#endif
