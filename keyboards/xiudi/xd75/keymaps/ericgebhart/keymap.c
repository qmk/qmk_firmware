/*
  Copyright 2018 Eric Gebhart <e.a.gebhart@gmail.com>

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

#include "ericgebhart.h"

#define BASE Base_5x15
#define BEPO Base_bepo_5x15
#define TRANS Transient_5x15

// tell the keymap we want to specify number rows.
// 4x10 input instead 3x10.
#define BASE_NUMBER_ROW    // turn on 4 row base templates.

#include "map.h"

/********************************************************************************/
/* Using layers to do RGB underlighting */
/********************************************************************************/

const rgblight_segment_t PROGMEM on_bepo[] = RGBLIGHT_LAYER_SEGMENTS(
                                                                     {0, 2, HSV_AZURE}
                                                                     );

const rgblight_segment_t PROGMEM bepo[] = RGBLIGHT_LAYER_SEGMENTS(
                                                                  {3, 2, HSV_MAGENTA}
                                                                  );

const rgblight_segment_t PROGMEM dvorak[] = RGBLIGHT_LAYER_SEGMENTS(
                                                                    {3, 2, HSV_AZURE}
                                                                    );

const rgblight_segment_t PROGMEM media[] = RGBLIGHT_LAYER_SEGMENTS(
                                                                   {5, 1, HSV_GREEN}
                                                                   );

const rgblight_segment_t PROGMEM symbol[] = RGBLIGHT_LAYER_SEGMENTS(
                                                                    {4, 2, HSV_GOLD}
                                                                    );

const rgblight_segment_t PROGMEM keypad[] = RGBLIGHT_LAYER_SEGMENTS(
                                                                    {4, 2, HSV_BLUE}
                                                                    );

const rgblight_segment_t PROGMEM layers[] = RGBLIGHT_LAYER_SEGMENTS(
                                                                    {5, 1, HSV_RED}
                                                                    );

const rgblight_segment_t PROGMEM rgb[] = RGBLIGHT_LAYER_SEGMENTS(
                                                                 {5, 1, HSV_ORANGE}
                                                                 );

const rgblight_segment_t* const PROGMEM rgb_layers[] = RGBLIGHT_LAYERS_LIST(on_bepo, bepo, dvorak, media, symbol,
                                                                            keypad, layers, rgb);

void keyboard_post_init_user(void) {
  rgblight_sethsv_noeeprom(HSV_PURPLE);
  rgblight_layers = rgb_layers;
}

layer_state_t layer_state_set_user(layer_state_t state) {
  // rgblight_set_layer_state(0, !on_qwerty());
  rgblight_set_layer_state(0, layer_state_cmp(state, _DVORAK));

  rgblight_set_layer_state(1, layer_state_cmp(state, _BEPO));
  rgblight_set_layer_state(2, layer_state_cmp(state, _DVORAK));
  //|| layer_state_cmp(state, DVORAK_ON_BEPO)));
  rgblight_set_layer_state(3, layer_state_cmp(state, _NAV));
  rgblight_set_layer_state(4, layer_state_cmp(state, _SYMB) );

  //(layer_state_cmp(state, SYMB) || (layer_state_cmp(state, SYMB_ON_BEPO))));
  rgblight_set_layer_state(5, layer_state_cmp(state, _KEYPAD) );
  ///(layer_state_cmp(state, KEYPAD) || (layer_state_cmp(state, KEYPAD_ON_BEPO))));
  rgblight_set_layer_state(6, layer_state_cmp(state, _LAYERS));
  rgblight_set_layer_state(7, layer_state_cmp(state, _RGB));
  return state;
}

/* void suspend_power_down_user(void) { */
/*   rgblight_disable(); */
/* } */

/* void suspend_wakeup_init_user(void) { */
/*   rgblight_enable(); */
/* } */

/* bool is_shift_pressed = false; */

/* bool led_update_user(led_t led_state) { */
/*   rgblight_set_layer_state(2, is_shift_pressed != led_state.caps_lock); */
/*   return true; */
/* } */

/* bool process_record_user(uint16_t keycode, keyrecord_t* record) { */
/*   switch (keycode) { */
/*   case KC_LSFT: */
/*   case KC_RSFT: */
/*     is_shift_pressed = record->event.pressed; */
/*     rgblight_set_layer_state(2, is_shift_pressed != host_keyboard_led_state().caps_lock); */
/*   default: */
/*     return true; */
/*   } */
/* } */
