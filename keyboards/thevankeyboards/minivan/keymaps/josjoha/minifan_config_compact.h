/*
 * License (GPL):
  
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

* © 2020,2021 by Jos Boersema
 */

#pragma once

/* 
 * If MINIFAN_CONFIG_COMPACT in ./user_config.h ⬇
 */
      
//#define BASE_QWERTY__DEF_BASE 
//#define BASE_QWERTY__ALT_BASE
//#define BASE_QWERTY_BASEARROW__DEF_BASE // ➡ base_qwerty_basearrow.h
//#define BASE_QWERTY_BASEARROW__ALT_BASE // ➡ base_qwerty_basearrow.h
  #define BASE_DVORAK__DEF_BASE
//#define BASE_DVORAK__ALT_BASE
//#define BASE_DVORAK_DESCRAMBLE__ALT_BASE 
//#define BASE_COLEMAK__DEF_BASE
//#define BASE_COLEMAK__ALT_BASE 
//#define BASE_WORKMAN__DEF_BASE
//#define BASE_WORKMAN__ALT_BASE
//#define BASE_NUMPAD__ALT_BASE // ➡ base_numpad.h
//#define BASE_HEBREW__DEF_BASE // ➡ base_hebrew.h
  #define BASE_HEBREW__ALT_BASE // ➡ base_hebrew.h

//#define MINIFAN_SINGLE_LAYOUT 

//#define STARTUP_ALTERNATE 
//#define STARTUP_SIDE_LEDS_OFF
//#define STARTUP_MID_LED_OFF 
//#define STARTUP_SPEED
//#define STARTUP_COUNT

//#define MORE_KEY__COMMAND 
//#define MORE_KEY__ARROW  

//#define TRANSMINIVAN_LAYOUT ....... 
//#define TRANSMINIVAN_LEFTSIDE  
  #define TRANS_LEFT XXXXXXX    
//#define TRANSMINIVAN_MIDLEFT   
  #define TRANS_MIDLEFT XXXXXXX 
//#define TRANSMINIVAN_RIGHTSIDE 
  #define TRANS_RIGHT XXXXXXX   

//#define MORE_key1_BASE TG ( _RAR ) 
//#define MORE_key1_BASE KC_DEL     
  #define MORE_key1_BASE KC__XGUI  
//#define MORE_key1      KC_DEL   
  #define MORE_key1      KC__XGUI
  #define MOREKEY2_ARROW_CLUSTER 
//#define MOREKEY2_ADD_NAVIGATION 
  #define MORE_key2 _MOV_UP 
//#define MORE_key2 KC_DEL 

  #define ARROWS_TRIANGLE 
//#define VI_SWITCHERYDOO 

  #define NUMPAD_COMMON_SQUARE 

  #define SPEED_COUNTDOWN 25 
  #define SPEED_HUE_STEP 8 
  #define SPEED_HUE_START 160 
  #define WORDS_PER_MINUTE 

//#define BASE_RIGHT_ALT 
//#define SWITCH_GUIS 
//#define UNICODE_CURRENCY 0x20ac 
//#define POINT_ON_CHECKBOXES 
//#define SWITCH_BASE_ROW1_23 
//#define SWITCH_HOLD_ACC_NSY 
  #define SWITCH_LSHIFT_PAD_MOV
  #define SWITCH_RSHIFT_FUN_RAR
//#define SPACE_LEFT__ENTER_RIGHT 

//#define REMOVE_PAD 
//#define REMOVE_ACC 
//#define _ACC_KEY_ALT_LAYER _BON 
//#define _ACC_KEY_ALT_LAYER _DRA 
//#define REMOVE_DRA 
//#define _DRA_KEY_ALT_LAYER _ACC 
//#define _DRA_KEY_ALT_LAYER _BON
//#define REMOVE_BON 
//#define _BON_KEY_ALT_LAYER _ACC 
//#define _BON_KEY_ALT_LAYER _DRA 
//#define ALL_DRA_BON_EVISCERATIONS 
  #define BOX_DRAWINGS 
  #define SUB_SCRIPT_NUMS 
  #define FULL_DRA_2NDROW 
  #define FULL_DRA_4THROW 
  #define FULL_BON_4THROW 

//#define LEDS_OFF_BASE_DEF 
//#define LEDS_OFF_BASE_ALT
