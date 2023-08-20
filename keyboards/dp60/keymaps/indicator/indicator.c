/**
 * indicator.c
 *
  Copyright 2020 astro <yuleiz@gmail.com>
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

#include "dp60.h"

#include "rgblight.h"


// caps led
const rgblight_segment_t PROGMEM dp60_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {18, 1, HSV_RED}
);

// scroll led
const rgblight_segment_t PROGMEM dp60_scrolllock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {19, 1, HSV_GREEN}
);

// num led
const rgblight_segment_t PROGMEM dp60_numlock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {20, 1, HSV_BLUE}
);

// light 21 to 26 for layer 1-5
const rgblight_segment_t PROGMEM dp60_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {21, 1, HSV_PURPLE}
);
const rgblight_segment_t PROGMEM dp60_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {22, 1, HSV_CYAN}
);
const rgblight_segment_t PROGMEM dp60_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {23, 1, HSV_YELLOW}
);
const rgblight_segment_t PROGMEM dp60_layer4_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {24, 1, HSV_PINK}
);
const rgblight_segment_t PROGMEM dp60_layer5_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {25, 1, HSV_ORANGE}
);

// rgb light layers
const rgblight_segment_t* const PROGMEM dp60_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    dp60_capslock_layer,
    dp60_scrolllock_layer,
    dp60_numlock_layer,
    dp60_layer1_layer,
    dp60_layer2_layer,
    dp60_layer3_layer,
    dp60_layer4_layer,
    dp60_layer5_layer
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = dp60_rgb_layers;
}

extern rgblight_config_t rgblight_config;
extern void              rgblight_layers_write(void);
extern void              indicator_write(LED_TYPE *start_led, uint8_t num_leds);

void rgblight_call_driver(LED_TYPE *start_led, uint8_t num_leds)
{
    ws2812_setleds(start_led, RGBLED_NUM-RGB_INDICATOR_NUM);

    indicator_write(start_led + (RGBLED_NUM - RGB_INDICATOR_NUM), RGB_INDICATOR_NUM);
}

void led_update_ports(led_t led_state) {
    rgblight_set_layer_state(0, led_state.caps_lock);
    rgblight_set_layer_state(1, led_state.scroll_lock);
    rgblight_set_layer_state(2, led_state.num_lock);
}

layer_state_t layer_state_set_kb(layer_state_t state) {
    state = layer_state_set_user(state);
    rgblight_set_layer_state(3, layer_state_cmp(state, 1));
    rgblight_set_layer_state(4, layer_state_cmp(state, 2));
    rgblight_set_layer_state(5, layer_state_cmp(state, 3));
    rgblight_set_layer_state(6, layer_state_cmp(state, 4));
    rgblight_set_layer_state(7, layer_state_cmp(state, 5));
    return state;
}
