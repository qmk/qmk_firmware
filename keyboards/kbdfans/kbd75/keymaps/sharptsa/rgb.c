#include "rgb.h"

const uint8_t RGB_BRIGHTNESS = 125;

// Fast swirling rainbow
const uint8_t RGBLED_RAINBOW_SWIRL_INTERVALS[] PROGMEM = {5, 5, 5};

// Light LEDs when caps lock is active.
const rgblight_segment_t PROGMEM capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
  {0, 3, 0, 255, RGB_BRIGHTNESS}, // Left LEDs in dimmed red
  {8, 3, 0, 255, RGB_BRIGHTNESS}
  );

// Layer 1 RGB
const rgblight_segment_t PROGMEM layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
  {5, 3, 30, 255, RGB_BRIGHTNESS},  // Right LEDs in dimmed golden rod
  {13, 3, 30, 255, RGB_BRIGHTNESS}
  );

// Layer 2 RGB
const rgblight_segment_t PROGMEM layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
  {5, 3, 213, 255, RGB_BRIGHTNESS},  // Right LEDs in dimmed magenta
  {13, 3, 213, 255, RGB_BRIGHTNESS}
  );

const rgblight_segment_t PROGMEM auto_shift_layer[] = RGBLIGHT_LAYER_SEGMENTS(
  {3, 2, 85, 255, RGB_BRIGHTNESS},  // Middle LEDs in dimmed green
  {11, 2, 85, 255, RGB_BRIGHTNESS}
  );

// Light LEDs when autoshift is disabled.
const rgblight_segment_t* const PROGMEM rgb_layers[] = RGBLIGHT_LAYERS_LIST(
  capslock_layer,
  layer1_layer,
  layer2_layer,
  auto_shift_layer
  );

void keyboard_post_init_rgb_light(void) {
   rgblight_layers = rgb_layers; // Enable the LEDs layers
}

// All LEDs in dimmed blue
void set_default_keyboard_rgb(void) {
  rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
  rgblight_sethsv(170, 255, RGB_BRIGHTNESS);
}

void set_led_dance(void) {
  rgblight_sethsv(255, 255, 255);
  rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL);
}

void set_autoshift_disabled_rgb(void) {
  rgblight_set_layer_state(3, !get_autoshift_state());
}
