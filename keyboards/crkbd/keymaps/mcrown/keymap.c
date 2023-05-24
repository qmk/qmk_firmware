/** @file keymap.c
 *  @brief keymao.c that includes key layout and keylogs functions
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
 *
 * @author Mario Corona (mariocc@comunidad.unam.mx) 2021
 *
 */

#include "mcrown.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] =  LAYOUT_wrapper(
          /*,-------------------------------------------------|-----|--------------------------------------------------------|.*/
          _____________________QWERTY_L1______________________,      _____________________QWERTY_R1______________________,
          /*|--------+--------+--------+--------+--------+----|     |--------+--------+--------+--------+--------+-----------|*/
          _____________________QWERTY_L2______________________,      _____________________QWERTY_R2______________________,
          /*|--------+--------+--------+--------+--------+----|     |--------+--------+--------+--------+--------+-----------|*/
          _____________________QWERTY_L3______________________,      _____________________QWERTY_R3______________________,
          /*|--------+--------+--------+--------+--------+----|     |--------+--------+--------+--------+--------+-----------|*/
                            _____________MOD_LEFT_____________,      _____________MOD_RIGHT____________
                        /*|-----------------------------------|     |----------------------------------|*/
  ),

  [_LOWER] =  LAYOUT_wrapper(
          /*,-------------------------------------------------|-----|--------------------------------------------------------|.*/
          _____________________LOWER_L1_______________________,      _____________________LOWER_R1_______________________,
          /*|--------+--------+--------+--------+--------+----|     |--------+--------+--------+--------+--------+-----------|*/
          _____________________LOWER_L2_______________________,      _____________________LOWER_R2_______________________,
          /*|--------+--------+--------+--------+--------+----|     |--------+--------+--------+--------+--------+-----------|*/
          _____________________LOWER_L3_______________________,      _____________________LOWER_R3_______________________,
          /*|--------+--------+--------+--------+--------+----|     |--------+--------+--------+--------+--------+-----------|*/
                            _____________MOD_LEFT_____________,      _____________MOD_RIGHT____________
                        /*|-----------------------------------|     |----------------------------------|*/
  ),

  [_RAISE] = LAYOUT_wrapper(
          /*,-------------------------------------------------|-----|--------------------------------------------------------|.*/
          _____________________RAISE_L1_______________________,      _____________________RAISE_R1_______________________,
          /*|--------+--------+--------+--------+--------+----|     |--------+--------+--------+--------+--------+-----------|*/
          _____________________RAISE_L2_______________________,      _____________________RAISE_R2_______________________,
          /*|--------+--------+--------+--------+--------+----|     |--------+--------+--------+--------+--------+-----------|*/
          _____________________RAISE_L3_______________________,      _____________________RAISE_R3_______________________,
          /*|--------+--------+--------+--------+--------+----|     |--------+--------+--------+--------+--------+-----------|*/
                            _____________MOD_LEFT_____________,      _____________MOD_RIGHT____________
                        /*|-----------------------------------|     |----------------------------------|*/
  ),

  [_ADJUST] = LAYOUT_wrapper(
          /*,-------------------------------------------------|-----|--------------------------------------------------------|.*/
          _____________________ADJUST_L1______________________,      _____________________ADJUST_R1______________________,
          /*|--------+--------+--------+--------+--------+----|     |--------+--------+--------+--------+--------+-----------|*/
          _____________________ADJUST_L2______________________,      _____________________ADJUST_R2______________________,
          /*|--------+--------+--------+--------+--------+----|     |--------+--------+--------+--------+--------+-----------|*/
          _____________________ADJUST_L3______________________,      _____________________ADJUST_R3______________________,
          /*|--------+--------+--------+--------+--------+----|     |--------+--------+--------+--------+--------+-----------|*/
                            _____________MOD_LEFT_____________,      _____________MOD_RIGHT____________
                        /*|-----------------------------------|     |----------------------------------|*/
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record){
    bool user_records_press=true;

    if (record->event.pressed){
        add_keylog(keycode);
    }

    switch (keycode){
        case QWERTY:
            if (record->event.pressed){
                set_single_persistent_default_layer(_QWERTY);
            }
            break;

        case LOWER:
            if(record->event.pressed){
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }else{
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            break;

        case RAISE:
            if (record->event.pressed){
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }else{
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            break;

        case ADJUST:
            if (record->event.pressed){
                layer_on(_ADJUST);
            }else{
                layer_off(_ADJUST);
            }
            break;

        case RGB_MOD:
            #ifdef RGBLIGHT_ENABLE
            if(record->event.pressed){
                rgblight_mode(RGB_current_mode);
                rgblight_step();
                RGB_current_mode = rgblight_get_mode();
            }
            #endif
            break;

        case RGBRST:
            #ifdef RGBLIGHT_ENABLE
            if(record->event.pressed){
                eeconfig_update_rgblight_default();
                rgblight_enable();
                RGB_current_mode = rgblight_get_mode();
            }
            #endif
            break;

        default:
            user_records_press=false;
            break;
    }

    return false==user_records_press;
}
