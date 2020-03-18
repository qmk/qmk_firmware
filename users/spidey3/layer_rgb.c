#include QMK_KEYBOARD_H

#include <spidey3.h>
#include <velocikey.h>

extern rgblight_config_t rgblight_config;

uint32_t rgb_mode;
uint16_t rgb_hue;
uint8_t rgb_sat;
uint8_t rgb_val;
bool rgb_saved = 0;

void spidey_swirl(void) {
#ifdef CONSOLE_ENABLE
  if (debug_enable) { print("SPIDEY3: Setting Spidey Swirl!\n"); }
#endif
  rgblight_enable();
  rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL);
  rgblight_sethsv(213, 255, 128);
#ifdef VELOCIKEY_ENABLE
  if (!velocikey_enabled())
	velocikey_toggle();
#endif
}

void eeconfig_init_user_rgb(void)
{
  spidey_swirl();
}

const rgblight_segment_t PROGMEM _capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS( {0, 2, HSV_AZURE}, {14, 2, HSV_AZURE} );
const rgblight_segment_t PROGMEM _layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS( {7, 1, HSV_PURPLE} );
const rgblight_segment_t PROGMEM _layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS( {9, 2, HSV_GREEN} );

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM _rgb_layers[] = RGBLIGHT_LAYERS_LIST( _capslock_layer, _layer1_layer, _layer2_layer );
const uint8_t PROGMEM _n_rgb_layers = sizeof(_rgb_layers) / sizeof(_rgb_layers[0]) - 1;

void do_rgb_layers(layer_state_t state, uint8_t start, uint8_t end) {
#ifdef CONSOLE_ENABLE
    if (debug_enable) { print("SPIDEY3: do_rgb_layers()\n"); }
#endif
    for (uint8_t i=start; i<end; i++) { 
      bool is_on = layer_state_cmp(state, i);
#ifdef CONSOLE_ENABLE
      if (debug_enable) { uprintf("         layer[%d]=%u\n", i, is_on); }
#endif
      rgblight_set_layer_state(i, is_on);
    }
}

void keyboard_post_init_user_rgb(void) {
    do_rgb_layers(default_layer_state, 1u, RGB_LAYER_BASE_REGULAR);
    do_rgb_layers(layer_state, RGB_LAYER_BASE_REGULAR, _n_rgb_layers);
    // Enable the LED layers
    rgblight_layers = _rgb_layers;
}

layer_state_t default_layer_state_set_user_rgb(layer_state_t state) {
#ifdef CONSOLE_ENABLE
    if (debug_enable) { print("SPIDEY3: default_layer_state_set_user_rgb()\n"); }
#endif
    do_rgb_layers(state, 1u, RGB_LAYER_BASE_REGULAR);
    return state;
}

layer_state_t layer_state_set_user_rgb(layer_state_t state) {
#ifdef CONSOLE_ENABLE
    if (debug_enable) { print("SPIDEY3: layer_state_set_user_rgb()\n"); }
#endif
    do_rgb_layers(state, RGB_LAYER_BASE_REGULAR, _n_rgb_layers);
    return state;
}

bool led_update_user_rgb(led_t led_state) {
#ifdef CONSOLE_ENABLE
    if (debug_enable) { uprintf("SPIDEY3: caps_lock=%u\n", led_state.caps_lock); }
#endif
    rgblight_set_layer_state(0, led_state.caps_lock);
    return true;
}

bool process_record_user_rgb(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {
    case SPI_GLO:
      if (record->event.pressed) {
        spidey_swirl();
      }
      break;
  }

  return true;
}

