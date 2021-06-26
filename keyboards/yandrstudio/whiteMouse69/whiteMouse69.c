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
        {72 ,71 ,70 ,69 ,68 ,67 ,66 ,65 ,64 ,63 ,62 ,61 ,60 ,59 ,58},
        {57 ,56 ,55 ,54 ,53 ,52 ,51 ,50 ,49 ,48 ,47 ,46 ,45 ,44 ,43 ,}, \
        {42 ,41 ,40 ,39 ,38 ,37 ,36 ,35 ,34 ,33 ,32 ,31 ,30 ,29 }, \
        {28 ,27 ,26 ,25 ,24 ,23 ,22 ,21 ,20 ,19 ,18 ,17 ,16 ,15 ,14 }, \
        {13 ,12 ,11 ,10 ,NO_LED,9 ,8 ,NO_LED,7 ,6 ,5 ,4 ,3 ,2 ,1 }, \
    },
    {
      // LED Index to Physical Position
      {32,128},{32,120},{32,112},{32,101},{32,90},{32,82},{32,74},{32,66},{32,58},{32,50},{32,42},{32,34},{32,26},{32,18},{32,5},
      {24,128},{24,120},{24,107},{24,94},{24,86},{24,78},{24,70},{24,62},{24,54},{24,46},{24,38},{24,30},{24,22},{24,14},{24,3},
      {16,110},{16,100},{16,92},{16,84},{16,76},{16,68},{16,60},{16,52},{16,44},{16,36},{16,28},{16,20},{16,12},{16,2},
      {8,120},{8,108},{8,96},{8,88},{8,80},{8,72},{8,64},{8,56},{8,48},{8,40},{8,32},{8,24},{8,16},{8,8},{8,0},
      {0,120},{0,112},{0,104},{0,96},{0,80},{0,72},{0,56},{0,48},{0,40},{0,32},{0,24},{0,16},{0,0},

    },
    {
      // LED Index to Flag
      4
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
