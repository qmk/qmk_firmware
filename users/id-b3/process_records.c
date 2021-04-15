/*
Copyright 2021 id-b3
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
*/

#include "id-b3.h"

//__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }
    // If console is enabled, it will print the matrix position and status of each key pressed

#ifdef TRACKBALL_ENABLE
void run_trackball_cleanup(void) {
    if (trackball_is_scrolling()) {
        trackball_set_rgbw(RGB_CYAN, 0x00);
    } else if (trackball_get_precision() != 0) {
        trackball_set_rgbw(RGB_GREEN, 0x00);
    } else {
        trackball_set_rgbw(255, 153, 30, 30);
    }
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	
#ifdef OLED_DRIVER_ENABLE
		//process_record_user_oled(keycode, record);
#endif

#ifdef DICE_ROLLER_ENABLE
//MACROS
  switch (keycode) {
    case ROLL_D3:
      if (record->event.pressed) {//oled_dice(3);
		if (get_mods() && MOD_BIT(KC_LSFT)) {
			unregister_code(KC_LSFT);
			SEND_STRING("/gmroll d3+");
			}
		else {SEND_STRING("/r d3+");}
		} break;
	case ROLL_D4:
      if (record->event.pressed) {//oled_dice(4);
		if (get_mods() && MOD_BIT(KC_LSFT)) {
			unregister_code(KC_LSFT);
			SEND_STRING("/gmroll d4+");
			}
		else {SEND_STRING("/r d4+");}
		} break;
	case ROLL_D6:
      if (record->event.pressed) {//oled_dice(6);
		if (get_mods() && MOD_BIT(KC_LSFT)) {
						unregister_code(KC_LSFT);
			SEND_STRING("/gmroll d6+");
			}
		else {SEND_STRING("/r d6+");}
		} break;
	case ROLL_D8:
      if (record->event.pressed) {//oled_dice(8);
		if (get_mods() && MOD_BIT(KC_LSFT)) {
						unregister_code(KC_LSFT);
			SEND_STRING("/gmroll d8+");
			}
		else {SEND_STRING("/r d8+");}
		} break;
	case ROLL_D10:
      if (record->event.pressed) {//oled_dice(10);
		if (get_mods() && MOD_BIT(KC_LSFT)) {
						unregister_code(KC_LSFT);
			SEND_STRING("/gmroll d10+");
			}
		else {SEND_STRING("/r d10+");}
		} break;
	case ROLL_D12:
      if (record->event.pressed) {//oled_dice(12);
		if (get_mods() && MOD_BIT(KC_LSFT)) {
						unregister_code(KC_LSFT);
			SEND_STRING("/gmroll d12+");
			}
		else {SEND_STRING("/r d12+");}
		} break;
	case ROLL_D20:
      if (record->event.pressed) {//oled_dice(20);
		if (get_mods() && MOD_BIT(KC_LSFT)) {
						unregister_code(KC_LSFT);
			SEND_STRING("/gmroll d20+");
			}
		else {SEND_STRING("/r d20+");}
		} break;
	case ROLL_D100:
      if (record->event.pressed) {//oled_dice(100);
		if (get_mods() && MOD_BIT(KC_LSFT)) {
						unregister_code(KC_LSFT);
			SEND_STRING("/gmroll d100+");
			}
		else {SEND_STRING("/r d100+");}
		} break;
    case PM_SCROLL:
	#ifdef TRACKBALL_ENABLE
	  trackball_set_scrolling(record->event.pressed);
	  run_trackball_cleanup();
	  #endif
	  //run_trackball_cleanup();
	  return false;
  }
  
  	#endif  // OLED
  return true;
}

	#ifdef TRACKBALL_ENABLE
uint32_t layer_state_set_user(uint32_t state) {
    trackball_set_rgbw(0, 0, 0, 60);
    uint8_t layer = biton32(state);
    switch(layer) {
        case _COLEMAK:
            trackball_set_rgbw(0, 0, 50, 110);
			trackball_set_scrolling(false);
			trackball_set_carret(false);
            break;
        case _SYMNUM:
            trackball_set_rgbw(10, 100, 40, 20);
			trackball_set_carret(true);
			trackball_set_scrolling(false);
            break;
        case _GAMING:
            trackball_set_rgbw(200, 30, 0, 40);
			trackball_set_scrolling(true);
			trackball_set_carret(false);
            break;
        case _NAVIGATION:
            trackball_set_rgbw(180, 90, 10, 30);
			trackball_set_scrolling(true);
			trackball_set_carret(false);
            break;
    }
    return state;
}
	  #endif
