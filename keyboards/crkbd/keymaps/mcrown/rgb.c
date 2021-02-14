#include "rgb.h"
#ifdef RGBLIGHT_ENABLE
/* Following line allows macro to read current RGB settings */
extern rgblight_config_t rgblight_config;
#endif

int RGB_current_mode;

/* Setting ADJUST layer RGB back to default */
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}
