#include QMK_KEYBOARD_H

#include "spidey3.h"
#include "velocikey.h"

uint32_t rgb_mode;
uint16_t rgb_hue;
uint8_t rgb_sat;
uint8_t rgb_val;
bool rgb_saved = 0;

void spidey_swirl(void) {
  dprint("Setting Spidey Swirl!\n");
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
const rgblight_segment_t PROGMEM _layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS( {10, 3, HSV_MAGENTA} );
const rgblight_segment_t PROGMEM _layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS( {10, 1, HSV_GREEN} );
const rgblight_segment_t PROGMEM _yes_layer[] = RGBLIGHT_LAYER_SEGMENTS( {9, 6, HSV_GREEN} );
const rgblight_segment_t PROGMEM _no_layer[] = RGBLIGHT_LAYER_SEGMENTS( {9, 6, HSV_RED} );

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM _rgb_layers[] =
    RGBLIGHT_LAYERS_LIST( _capslock_layer, _layer1_layer, _layer2_layer, _layer3_layer, _yes_layer, _no_layer );
const uint8_t PROGMEM _n_rgb_layers = sizeof(_rgb_layers) / sizeof(_rgb_layers[0]) - 1;

void clear_rgb_layers() {
    for (uint8_t i=0; i<_n_rgb_layers; i++) {
        rgblight_set_layer_state(i, false);
    }
}

void do_rgb_layers(layer_state_t state, uint8_t start, uint8_t end) {
    dprint("do_rgb_layers()\n");
    for (uint8_t i=start; i<end; i++) {
      bool is_on = layer_state_cmp(state, i);
      dprintf("\tlayer[%d]=%u\n", i, is_on);
      rgblight_set_layer_state(i, is_on);
    }
}

void keyboard_post_init_user_rgb(void) {
    do_rgb_layers(default_layer_state, 1u, RGB_LAYER_BASE_REGULAR);
    do_rgb_layers(layer_state, RGB_LAYER_BASE_REGULAR, RGB_LAYER_BASE_ACKS);
    do_rgb_layers(0, RGB_LAYER_BASE_ACKS, _n_rgb_layers);
    // Enable the LED layers
    rgblight_layers = _rgb_layers;
}

layer_state_t default_layer_state_set_user_rgb(layer_state_t state) {
    dprint("default_layer_state_set_user_rgb()\n");
    do_rgb_layers(state, 1u, RGB_LAYER_BASE_REGULAR);
    return state;
}

layer_state_t layer_state_set_user_rgb(layer_state_t state) {
    dprint("layer_state_set_user_rgb()\n");
    do_rgb_layers(state, RGB_LAYER_BASE_REGULAR, RGB_LAYER_BASE_ACKS);
    return state;
}

bool led_update_user_rgb(led_t led_state) {
    dprintf("caps_lock=%u\n", led_state.caps_lock);
    rgblight_set_layer_state(0, led_state.caps_lock);
    return true;
}

void rgb_layer_ack(bool yn, bool pressed) {
  uint8_t layer = RGB_LAYER_BASE_ACKS + (yn ? 0 : 1);
  rgblight_set_layer_state(layer, pressed);
}

extern keymap_config_t keymap_config;

bool process_record_user_rgb(uint16_t keycode, keyrecord_t *record) {
  bool pressed = record->event.pressed;

  switch (keycode) {
    case SPI_GLO:
      if (pressed) {
        spidey_swirl();
      }
      return false;

    // Acks follow...
    case DEBUG:
      rgb_layer_ack(debug_enable, pressed);
      return false;

    case SPI_LNX:
    case SPI_OSX:
    case SPI_WIN:
      rgb_layer_ack(true, pressed);
      return false;

    // Tricky!
    // For these, on press the toggle hasn't happened yet,
    // so we need a little logic to invert, assuming that
    // on key press the flag WILL be toggled, and on key
    // release the flag has already been toggled.

#ifdef VELOCIKEY_ENABLE
    case VLK_TOG:
      rgb_layer_ack(pressed != velocikey_enabled(), pressed);
      return true;
#endif

#ifdef NKRO_ENABLE
    case NK_TOGG:
    case NK_ON:
    case NK_OFF:
      rgb_layer_ack(pressed != keymap_config.nkro, pressed);
      return true;
#endif
  }

  return true;
}
