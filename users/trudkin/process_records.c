/* Copyright 2020-2021 Terence Rudkin 
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

#include "trudkin.h"


          float my_song[][2] = SONG(GOOD_EATS);

#ifndef NO_SECRETS
    static const char *secret[] = {
    SS_R2C1, 
    SS_R2C2, 
    SS_R2C3, 
    SS_R2C4, 
    SS_R2C5, 
    };
#endif



#ifdef USE_CUA
/* 
** Linux command line  does not use Ctrl-C or Crtl-V as copy and paste 
** but most other applications do. So mussle memory with the left hand produces a lot of unintended ^V 
** Or using the right hand it is either with a mouse or SFT-INS, the CUA method. 
** Both take the right hand off the home keys. Besides on a planck INS is hidden anyway
** All apps I use honor CUA cut & paste and my left hand knows ctrl-x|-c|-v. 
**  
** This API overrides the standard Cut&Paste with the CUA implementation
** which works every where I need.  The CUA_MOD can be assigned to MOD_MASK_xxx or 
** MOD_BIT(mod).  If assigned MOD_MASK_CTRL CTRL-C is lost for when you need to break out. 
** I set to MOD_BIT(KC_LCTRL) I can get CTRL-C with the right hand, or 
** MOD_MASK_GUI is another choice to preserve CTRL-C. The last option would define 
** another way of getting CTRL-C such as TAP DANCE
**  
    */
bool cua_cut_copy_paste(uint16_t  keycode){
    uint8_t temp_mod = mod_config(get_mods());
    uint8_t temp_osm = mod_config(get_oneshot_mods());
    uint16_t cua_keycode =RCTL(KC_INS); 
    switch (keycode) {
    case KC_X:
        cua_keycode = RSFT(KC_DEL);
        break;
    case KC_C:
        cua_keycode = RCTL(KC_INS);
        break;
    case KC_V:
        cua_keycode = RSFT(KC_INS);
        break;
    } 
    if ((temp_mod | temp_osm) & CUA_MOD){
        clear_mods();
        clear_oneshot_mods();
        tap_code16(cua_keycode);
        set_mods(temp_mod);
    } else {
        tap_code16(keycode);
    }
    return false;

}
#endif 


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
#ifdef USE_CUA
        case KC_C:
        case KC_X:
        case KC_V:
            if (record->event.pressed) {
                cua_cut_copy_paste(keycode);
            }
            return false;
            break;
#endif
  case MY_PRINT_LAYOUT:
      if (record->event.pressed) {
          PLAY_SONG(my_song);
//          my_print_layout();
      }
          return false;
          break ;
        case QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
            break;
        case COLEMAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAK);
            }
            return false;
            break;
        case DVORAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_DVORAK);
            }
            return false;
            break;
        case MY_LGUI:
            if (record->tap.count > 0) {
                if (record->event.pressed) {
                    // send advanced keycode, etc.
                    // the 16 bit version of the `tap_code` function is used here
                    // because KC_HASH is a non-basic keycode.
                    tap_code16(KC_PIPE);
                }
    // do not continue with default tap action
    // if the MT was pressed or released, but not held
                return false;
            }
            break;
    case SECRET1 ... SECRET5:
        if (record->event.pressed) {

            send_string_with_delay_P(PSTR(secret[keycode-SECRET1]),TAP_CODE_DELAY);
                   
        }
        break;
        case KC_MAKE:  // Compiles the firmware, and adds the flash command based on keyboard bootloader
            if (!record->event.pressed) {
#ifndef MAKE_BOOTLOADER
                uint8_t temp_mod = mod_config(get_mods());
                uint8_t temp_osm = mod_config(get_oneshot_mods());
                clear_mods();
                clear_oneshot_mods();
#endif
                send_string_with_delay_P(PSTR("make "), TAP_CODE_DELAY);

                send_string_with_delay_P(PSTR( QMK_KEYBOARD ":" QMK_KEYMAP), TAP_CODE_DELAY);
#ifndef MAKE_BOOTLOADER
                if ((temp_mod | temp_osm) & MOD_MASK_SHIFT)
#endif
                {
                    send_string_with_delay_P(PSTR(":flash "), TAP_CODE_DELAY);
#ifndef MAKE_BOOTLOADER
                } else {
                    send_string_with_delay_P(PSTR(""), TAP_CODE_DELAY);
#endif
                }

#ifdef RGB_MATRIX_SPLIT_RIGHT
                send_string_with_delay_P(PSTR(" RGB_MATRIX_SPLIT_RIGHT=yes"), TAP_CODE_DELAY);
#    ifndef OLED_DRIVER_ENABLE
                send_string_with_delay_P(PSTR(" OLED_DRIVER_ENABLE=no"), TAP_CODE_DELAY);
#    endif
#endif
                send_string_with_delay_P(PSTR(SS_TAP(X_ENTER)), TAP_CODE_DELAY);
            }

            break;


    }
    return true;
};
