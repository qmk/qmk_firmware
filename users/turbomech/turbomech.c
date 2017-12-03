#include "turbomech.h"
#include "quantum.h"
#include "action_layer.h"
#include "action.h"
#include "eeconfig.h"
#include "rgblight.h"



extern keymap_config_t keymap_config;

extern rgblight_config_t rgblight_config;


#ifdef RGBLIGHT_ENABLE
/*change the rgblight_setrgb(#, #, #) to what you want CAPS lock - currenlty red*/
 #define rgblight_set_caps       rgblight_setrgb(255, 0, 0)
 //#define rgblight_base           rgblight_mode(RGB_current_mode)
#endif

//bool rgb_layer_change = true;
//bool RGB_INIT = false;
bool TOG_STATUS = false;
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


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case MO(1):
       if (record->event.pressed) {
        layer_on(_FUNCTION);
        rgblight_mode(1);
        rgblight_set_caps;
        //rgblight_set_caps;
    }
      else {
       layer_off(_FUNCTION);
        //rgblight_mode(RGB_current_mode);
       RGB_current_mode = rgblight_config.mode;
           }


      return true;
      break;

    case RGB_MOD:
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
      break;

    //case MO(1):
       //if (record->event.realeased) {
        //rgblight_mode(1);
        //rgblight_set_red;
     // }
    //  return true;
     // break;

    case KC_CAPS:
     if (record->event.pressed) {
        rgblight_mode(RGB_current_mode);
       register_code(KC_CAPS);
        rgblight_mode(1);
        rgblight_set_caps;
      }
      else {
        unregister_code(KC_CAPS);
        rgblight_mode(RGB_current_mode);

      }
      return false;
       break;
    case KC_RESET:
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
    }


      return true;





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


