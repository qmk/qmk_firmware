 /* Copyright 2021 still <stillconfusing@gmail.com>
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

#include QMK_KEYBOARD_H
#include "my_keycodes.h"

#define RGB_BASE_COLOR 128, 255, 165
#define HSV_cORANGE 10, 255, 255

#define LAYER_LED 13
#define LAYER_LED_COUNT 1

enum RGB_LAYERS { FN1, FN2, FN3, NUM, CAPS, BLNK, RGB_NO, RGB_YES };

const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 2, HSV_GREEN},
    {15, 3, HSV_GREEN}
);

const rgblight_segment_t PROGMEM my_numlock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {6, 5, HSV_RED}
);

// fn layer's rgb
const rgblight_segment_t PROGMEM fn1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {LAYER_LED, LAYER_LED_COUNT, HSV_RED}
);

const rgblight_segment_t PROGMEM fn2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {LAYER_LED, LAYER_LED_COUNT, HSV_ORANGE}
);

const rgblight_segment_t PROGMEM fn3_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {LAYER_LED, LAYER_LED_COUNT, HSV_cORANGE}
);

const rgblight_segment_t PROGMEM blank[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 18, HSV_BLACK}
);

const rgblight_segment_t PROGMEM rgb_no[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 18, HSV_RED}
);

const rgblight_segment_t PROGMEM rgb_yes[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 18, HSV_GREEN}
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    fn1_layer,
    fn2_layer,
    fn3_layer,
    my_numlock_layer,
    my_capslock_layer,
    blank,
    rgb_no,
    rgb_yes
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
    rgblight_sethsv(RGB_BASE_COLOR);
}

static bool lastCaps = 0;
static bool lastNum = 0;
bool led_update_user(led_t led_state) {
    if (led_state.caps_lock && !lastCaps){
        rgblight_blink_layer_repeat(BLNK, 175, 2);
        lastCaps = 1;
    } else {
        lastCaps = led_state.caps_lock;
    }
    if (!led_state.num_lock && !lastNum){	
        rgblight_blink_layer_repeat(BLNK, 175, 2);
        lastNum = 1;
    } else {
        lastNum = !led_state.num_lock;
    }
    rgblight_set_layer_state(CAPS, led_state.caps_lock);
    rgblight_set_layer_state(NUM, !led_state.num_lock);
    writePin(LED_NUM_LOCK_PIN, !is_backlight_enabled());
    writePin(LED_CAPS_LOCK_PIN, !is_backlight_enabled());
    return false;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(FN1, layer_state_cmp(state, 1));
    rgblight_set_layer_state(FN2, layer_state_cmp(state, 2));
    rgblight_set_layer_state(FN3, layer_state_cmp(state, 3));
    return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case pHSV:
            if (record->event.pressed){
                char hue[4];
                itoa(rgblight_get_hue(), hue, 10);
                hue[4] = '\0';
                send_string(hue);
                SEND_STRING(", ");
                char sat[4];
                itoa(rgblight_get_sat(), sat, 10);
                sat[4] = '\0';
                send_string(sat);
                SEND_STRING(", ");
                char val[4];
                itoa(rgblight_get_val(), val, 10);
                val[4] = '\0';
                send_string(val);
                SEND_STRING(" ");
            }
        return true;
    case BL_OFF:
    case BL_ON:
        led_update_user(host_keyboard_led_state());
        return true; 
    default:
        return true;
    }
}
