/* Copyright 2017 @TurboMech /u/TurboMech <discord> @A9entOran9e#6134
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

#include "turbomech.h"
#include "quantum.h"
//#include "action_layer.h"
#include "action.h"
//#include "rgblight.h"

__attribute__ ((weak))
void matrix_init_keymap(void) {}

__attribute__ ((weak))
void matrix_scan_keymap(void) {}

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}
__attribute__ ((weak))
uint32_t layer_state_set_keymap (uint32_t state) {
  return state;
}
__attribute__ ((weak))
void led_set_keymap(uint8_t usb_led) {}

//#define default_layer _QWERTY (0)
//extern keymap_config_t keymap_config;

extern rgblight_config_t rgblight_config;


//#ifdef RGBLIGHT_ENABLE
/*change the rgblight_setrgb(#, #, #) to what you want CAPS lock - currenlty red*/
 //#define rgblight_set_caps       rgblight_setrgb(255, 0, 0)
 //#define rgblight_base           rgblight_mode(RGB_current_mode)
//#endif
//
//bool rgb_layer_change = true;
//bool RGB_INIT = false;
//bool TOG_STATUS = false;
#ifdef RGBLIGHT_ENABLE
bool rgb_layer_change = true;
#endif
int RGB_current_mode;

/*void matrix_init_user(void) {
  #ifdef RGBLIGHT_ENABLE
  rgblight_enable();
  if (true) {
  eeconfig_read_rgblight();
  rgblight_get_mode();
  eeconfig_update_rgblight_default();


 // eeconfig_debug_rgblight();
  //rgblight_init();
  }
  #endif

}
*/

/*void matrix_init_user(void) {
  #ifdef RGBLIGHT_ENABLE
  eeconfig_read_rgblight();
  eeconfig_update_rgblight_default();
  //rgblight_init();
  //rgblight_mode(RGB_current_mode);
  //rgblight_mode(RGB_current_mode);
  //RGB_current_mode = rgblight_config.mode;
  #endif
}*/


void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
  default_layer = _QWERTY;
 // eeconfig_update_rgblight(rgblight_config.raw);
}

 //Setting ADJUST layer RGB back to default
/*void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    rgblight_mode(RGB_current_mode);
    layer_on(layer1);
  } else {
    layer_off(layer2);
  }
}*/


void matrix_init_user(void) {

  uint8_t default_layer = eeconfig_read_default_layer();

  rgblight_enable();

  if(true) {
   if (default_layer & (1UL << _QWERTY)) {
      //RGB_current_mode = rgblight_config.mode;
      rgblight_mode(11);
      }
 else {
      rgblight_mode (12);
      }

    /*else if (default_layer & (1UL << _DVORAK)) {
      rgblight_set_green;
    }
    //else if (default_layer & (1UL << _WORKMAN)) {
      rgblight_set_purple;
    }
    else {
      rgblight_set_teal;*/


  }


}

static bool is_capslocked = false;
void led_set_user(uint8_t usb_led) {
  if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
    is_capslocked = true;
   //     DDRB |= (1 << 2); PORTB &= ~(1 << 2);
  } else {
    is_capslocked = false;
  //  DDRB &= ~(1 << 2); PORTB &= ~(1 << 2);
  }
}
  //rgblight_set();


//static uint8_t is_capslocked = false;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case _QWERTY:
      persistent_default_layer_set(1UL << _QWERTY);
      return false;
      break;
    case KC_MAKE_ALU84:
      if (!record->event.pressed) {
        SEND_STRING("make alu84:TurboMech:dfu");
        SEND_STRING(SS_TAP(X_ENTER));
    }
    return false;
    break;
    case KC_QMK:
      if (!record->event.pressed) {
        SEND_STRING("cd QMK/qmk_firmware");
        SEND_STRING(SS_TAP(X_ENTER));
      }
      return false;
      break;
    case KC_RESET:
      if (!record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_enable();
          rgblight_mode(1);
          rgblight_setrgb(255, 255, 255);
        #endif
        //_delay_ms(2000);
        reset_keyboard();
      }
      return false;
      break;
    /*case RGB_MOD:
      //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
      if (record->event.pressed) {
       rgblight_mode(RGB_current_mode);
       RGB_current_mode = rgblight_config.mode;
        rgblight_step();
       // rgblight_mode(RGB_current_mode);
     //RGB_current_mode = rgblight_config.mode;
        // _delay_ms(50);
       // rgblight_set();
        RGB_current_mode = rgblight_config.mode;
    }
      else //if (rgblight_config.enable)
      {
        _delay_ms(50);
        rgblight_set();
        //rgblight_mode(rgblight_config.mode);
      // eeconfig_update_rgblight(rgblight_config.raw);
      }

     return true;
      break;*/

    /*case MO(1):
      if (record->event.realeased) {
        rgblight_mode(1);
        rgblight_set_red;
      }
      return true;
      break;*/

   /*case KC_CAPS:
     if (record->event.pressed) {
        rgblight_mode(RGB_current_mode);
       register_code(KC_CAPS);
        rgblight_mode(1);
        rgblight_set_red;
      }
      else {
        unregister_code(KC_CAPS);
        rgblight_mode(RGB_current_mode);

      }
      return false;
       break;*/

       /* rgblight_mode(RGB_current_mode);
        register_code(KC_CAPS);
        rgblight_mode(1);
        rgblight_set_red;
      }
      else {
        unregister_code(KC_CAPS);
        rgblight_mode(RGB_current_mode);*/

    //  }
    //  return true;
     //  break;
    /*case KC_RESET:
      if (record->event.pressed) {
      layer_off(_FUNCTION);
      rgblight_mode(RGB_current_mode);
     RGB_current_mode = rgblight_config.mode;
      layer_clear();
      _delay_ms(1000);
        reset_keyboard();
     }
     else{
      //layer_off(_FUNCTION);
     _delay_ms(1000);
     rgblight_mode(RGB_current_mode);
     RGB_current_mode = rgblight_config.mode;

     //eeconfig_update_rgblight_default();
      }

      return false;
      break;
    }*/


      return true;
      break;





/*case RGB_MOD:
case RGB_SMOD:
case RGB_HUI:
case RGB_HUD:
case RGB_SAI:
case RGB_SAD:
case RGB_VAI:
case RGB_VAD:
case RGB_MODE_PLAIN:
case RGB_MODE_BREATHE:
case RGB_MODE_RAINBOW:
case RGB_MODE_SWIRL:
case RGB_MODE_SNAKE:
case RGB_MODE_KNIGHT:
case RGB_MODE_XMAS:
case RGB_MODE_GRADIENT:
    if (record->event.pressed) {
      rgb_layer_change = false;
    }
    break;
  }
  return true;*/
  }


 return process_record_keymap(keycode, record);

}

uint32_t layer_state_set_user(uint32_t state) {
#ifdef RGBLIGHT_ENABLE
  uint8_t default_layer = eeconfig_read_default_layer();
  if (rgb_layer_change) {
    switch (biton32(state)) {
    case _FUNCTION:
      rgblight_set_blue;
     rgblight_mode(1);
     break;
    case _QWERTY:

      rgblight_mode(11);
      break;
  // case _MOUS:
    //  rgblight_set_yellow;
    //  rgblight_mode(1);
   //   break;
    //case _MACROS:
      //rgblight_set_orange;
      //is_overwatch ? rgblight_mode(17) : rgblight_mode(18);
      //break;
    //case _MEDIA:
      //rgblight_set_green;
      //rgblight_mode(22);
      //break;
    default:
      if (is_capslocked) {
        rgblight_mode(1);
        rgblight_set_red;
      }
        else { if (default_layer & (1UL << _QWERTY)) {
        rgblight_mode(11);
        }

        else if (default_layer & (1UL << _FUNCTION)) {
         rgblight_set_cyan;
        }
        //else if (default_layer & (1UL << _WORKMAN)) {
        //  rgblight_set_purple;
       // }
        else {
          rgblight_set_orange;
        }
      }
      rgblight_mode(1);
      break;
    }
  }
#endif
  return state;
}


!!** possible for later

void set_single_persistent_default_layer(uint8_t default_layer);

void set_single_persistent_default_layer(uint8_t default_layer) {
  #if defined(AUDIO_ENABLE) && defined(DEFAULT_LAYER_SONGS)
    PLAY_SONG(default_layer_songs[default_layer]);
  #endif
  eeconfig_update_default_layer(1U<<default_layer);
  default_layer_set(1U<<default_layer);

void matrix_init_kb(void);

void matrix_init_user(void);

!!** line 31

__attribute__ ((weak))
void matrix_init_keymap(void) {}

__attribute__ ((weak))
void matrix_scan_keymap(void) {}

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}
__attribute__ ((weak))
uint32_t layer_state_set_keymap (uint32_t state) {
  return state;
}
__attribute__ ((weak))
void led_set_keymap(uint8_t usb_led) {}

Alt +30C4
¯\_(ツ)_/¯

Alt +00AF
