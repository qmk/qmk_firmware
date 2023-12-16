#include "rgb_util.h"

const rgblight_segment_t PROGMEM capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 20, HSV_MAGENTA}
    // {12, 4, HSV_RED}       // Light 4 LEDs, starting with LED 12
);

const rgblight_segment_t PROGMEM number_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 20, HSV_WHITE}
);

const rgblight_segment_t PROGMEM lower_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 20, HSV_CYAN}
);

const rgblight_segment_t PROGMEM rise_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 20, HSV_ORANGE}
);

const rgblight_segment_t PROGMEM adjust_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 20, HSV_CHARTREUSE}
);

const rgblight_segment_t* const PROGMEM rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    capslock_layer,
    number_layer,
    lower_layer,
    rise_layer,
	adjust_layer
);

void rgb_layers_init(void) {
    // Enable the LED layers
    rgblight_layers = rgb_layers;
}

layer_state_t rgb_set_layer_state(layer_state_t state) {
    // Both layers will light up if both kb layers are active
    for (int i = 0; i < sizeof(rgb_layers); i++) {
        rgblight_set_layer_state(i, layer_state_cmp(state, i));
    }
	return state;
}

bool rgb_set_led_state(led_t led_state) {
    rgblight_set_layer_state(0, led_state.caps_lock);
	return true;
}
