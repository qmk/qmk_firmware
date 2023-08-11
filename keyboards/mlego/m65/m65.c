/*
Copyright 2021-2022 Alin M Elena <alinm.elena@gmail.com>

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

#include "m65.h"

// let us assume we start with both layers off
static bool toggle_lwr = false;
static bool toggle_rse = false;

#ifdef RGBLIGHT_ENABLE

const rgblight_segment_t PROGMEM my_qwerty_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, RGBLED_NUM, HSV_PURPLE});
const rgblight_segment_t PROGMEM my_lwr_layer[]    = RGBLIGHT_LAYER_SEGMENTS({0, RGBLED_NUM, HSV_CYAN});
const rgblight_segment_t PROGMEM my_rse_layer[]    = RGBLIGHT_LAYER_SEGMENTS({0, RGBLED_NUM, HSV_RED});
const rgblight_segment_t PROGMEM my_adj_layer[]    = RGBLIGHT_LAYER_SEGMENTS({0, RGBLED_NUM, HSV_GREEN});

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(my_qwerty_layer, my_lwr_layer, my_rse_layer, my_adj_layer);

#endif

#ifdef OLED_ENABLE

static uint32_t oled_logo_timer = 0;
static bool clear_logo = true;
static const char PROGMEM m65_logo[] = {
    0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa5, 0xa5, 0xa5, 0xa5, 0xa5, 0xa5,
    0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
    0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
    0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
    0};

#endif

#ifdef RGBLIGHT_ENABLE

void set_rgb_layers(layer_state_t state){

    rgblight_set_layer_state(0, layer_state_cmp(state, _QW));
    rgblight_set_layer_state(1, layer_state_cmp(state, _LWR));
    rgblight_set_layer_state(2, layer_state_cmp(state, _RSE));
    rgblight_set_layer_state(3, layer_state_cmp(state, _ADJ));

}

void set_default_rgb_layers(layer_state_t state){
    rgblight_set_layer_state(0, layer_state_cmp(state, _QW));
}

const rgblight_segment_t * const* my_rgb(void){
    return my_rgb_layers;
}

#endif

void set_led_toggle(const uint8_t layer, const bool state){

    switch (layer) {
        case _LWR:
          toggle_lwr = state;
          break;
        case _RSE:
          toggle_rse = state;
          break;
        default:
          break;
    }
}

void toggle_leds(void){

    led_lwr(toggle_lwr);
    led_rse(toggle_rse);
    led_t led_state = host_keyboard_led_state();
    led_caps(led_state.caps_lock);
    if (layer_state_is(_ADJ)) {
        led_lwr(true);
        led_rse(true);
    }

}

#ifdef ENCODER_ENABLE

#    define MEDIA_KEY_DELAY 10

void my_encoders(const uint8_t index, const bool clockwise) {
    if (index == 0) { /* First encoder */
        if (IS_LAYER_ON(_LWR)) {
            if (clockwise) {
                rgblight_decrease_val_noeeprom();
            } else {
                rgblight_increase_val_noeeprom();
            }
        } else if (IS_LAYER_ON(_RSE)) {
            if (clockwise) {
                rgblight_decrease_hue_noeeprom();
            } else {
                rgblight_increase_hue_noeeprom();
            }

        } else {
            if (clockwise) {
                tap_code_delay(KC_VOLD, MEDIA_KEY_DELAY);
            } else {
                tap_code_delay(KC_VOLU, MEDIA_KEY_DELAY);
            }
        }
    }
}

bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) { return false; }
    my_encoders(index, clockwise);
    return false;
}

#endif

#ifdef OLED_ENABLE

void init_timer(void){
   oled_logo_timer = timer_read32();
};

void user_oled_magic(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case _QW:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case _LWR:
            oled_write_P(PSTR("Lower\n"), false);
            break;
        case _RSE:
            oled_write_P(PSTR("Raise\n"), false);
            break;
        case _ADJ:
            oled_write_P(PSTR("ADJ\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("Lower ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("Raise ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CapsLock ") : PSTR("    "), false);
#ifdef WPM_ENABLE
    oled_write_P(PSTR("\nwpm: "), false);
    uint8_t wpm = get_current_wpm();
    oled_write_P(wpm != 0 ? get_u8_str(wpm,' ') : PSTR("   "), false);
#endif
}

void render_logo(void) {
    oled_write_P(m65_logo, false);
}

void clear_screen(void) {
    if (clear_logo){
      for (uint8_t i = 0; i < OLED_DISPLAY_HEIGHT; ++i) {
        for (uint8_t j = 0; j < OLED_DISPLAY_WIDTH; ++j) {
          oled_write_raw_byte(0x0, i*OLED_DISPLAY_WIDTH + j);
        }
      }
      clear_logo = false;
    }
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}

#    define SHOW_LOGO 5000
bool oled_task_kb(void) {
    if (!oled_task_user()) { return false; }
    if ((timer_elapsed32(oled_logo_timer) < SHOW_LOGO)){
        render_logo();
    }else{
      clear_screen();
      user_oled_magic();
    }
    return false;
}

#endif
