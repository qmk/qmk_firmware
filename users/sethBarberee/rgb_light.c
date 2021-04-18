#include "rgb_light.h"

#if defined(RGBLIGHT_ENABLE)
layer_state_t layer_state_set_rgb_light(layer_state_t state){
    switch(get_highest_layer(state)) {
      case _QWERTY:
        rgblight_sethsv_noeeprom(HSV_RED);
        break;
      case _LOWER:
        rgblight_sethsv_noeeprom(HSV_GREEN);
        break;
      case _RAISE:
        rgblight_sethsv_noeeprom(HSV_BLUE);
        break;
      case _ADJUST:
        rgblight_sethsv_noeeprom(HSV_GOLDENROD);
        break;
      default:
        rgblight_sethsv_noeeprom(HSV_PINK);
        break;

    }
    return state;
}

void keyboard_post_init_rgb_light(void)
{
    layer_state_set_rgb_light(layer_state);
    rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 3);
}
#endif

