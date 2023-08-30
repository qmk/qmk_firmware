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

const rgblight_segment_t PROGMEM my_qwerty_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, RGBLED_NUM, HSV_OFF});
const rgblight_segment_t PROGMEM my_lwr_layer[]    = RGBLIGHT_LAYER_SEGMENTS({0, RGBLED_NUM, HSV_AZURE});
const rgblight_segment_t PROGMEM my_rse_layer[]    = RGBLIGHT_LAYER_SEGMENTS({0, RGBLED_NUM, HSV_CORAL});
const rgblight_segment_t PROGMEM my_adj_layer[]    = RGBLIGHT_LAYER_SEGMENTS({0, RGBLED_NUM, HSV_RED});

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(my_qwerty_layer, my_lwr_layer, my_rse_layer, my_adj_layer);

#endif


#ifdef OLED_ENABLE
static uint32_t oled_logo_timer = 0;
static bool clear_logo = true;
static const char PROGMEM m65_logo[] = {
    0x92, 0x92, 0x93, 0x94, 0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90,
    0x92, 0x92, 0x93, 0x94, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0,
    0xB2, 0x92, 0xB3, 0xB4, 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0,
    0};
#endif

#ifdef RGBLIGHT_ENABLE

void set_rgb_layers(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _QW));
    rgblight_set_layer_state(1, layer_state_cmp(state, _LWR));
    rgblight_set_layer_state(2, layer_state_cmp(state, _RSE));
    rgblight_set_layer_state(3, layer_state_cmp(state, _ADJ));
}

void set_default_rgb_layers(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _QW));
}

const rgblight_segment_t* const* my_rgb(void) {
    return my_rgb_layers;
}

#endif

void set_led_toggle(const uint8_t layer, const bool state) {
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

void toggle_leds(void) {
    led_lwr(toggle_lwr);
    led_rse(toggle_rse);
   led_t led_state = host_keyboard_led_state();
   led_caps(led_state.caps_lock);
    if (layer_state_is(_ADJ)) {
        led_lwr(true);
        led_rse(true);
    }
}

#ifdef OLED_ENABLE

void init_timer(void) {
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

#    ifdef UNICODE_COMMON_ENABLE
    oled_write_P(PSTR("\nunicode: "), false);
    switch (get_unicode_input_mode()) {
      case UNICODE_MODE_LINUX:
        oled_write_P(PSTR("Linux"), false);
        break;
      case UNICODE_MODE_MACOS:
        oled_write_P(PSTR("apple"), false);
        break;
      case UNICODE_MODE_WINDOWS:
        oled_write_P(PSTR("windows"), false);
        break;
      case UNICODE_MODE_WINCOMPOSE:
        oled_write_P(PSTR("windows c"), false);
        break;
      case UNICODE_MODE_BSD:
        oled_write_P(PSTR("bsd"), false);
        break;
      case UNICODE_MODE_EMACS:
        oled_write_P(PSTR("emacs"), false);
        break;
      default:
        oled_write_ln_P(PSTR("not supported"), false);
    }
#    endif

#    ifdef WPM_ENABLE
    oled_write_P(PSTR("\nwpm: "), false);
    uint8_t wpm = get_current_wpm();
    oled_write_P(wpm != 0 ? get_u8_str(wpm, ' ') : PSTR("   "), false);
#    endif
}

void render_logo(void) {
    oled_write_P(m65_logo, false);
}

void clear_screen(void) {
    if (clear_logo) {
        for (uint8_t i = 0; i < OLED_DISPLAY_HEIGHT; ++i) {
            for (uint8_t j = 0; j < OLED_DISPLAY_WIDTH; ++j) {
                oled_write_raw_byte(0x0, i * OLED_DISPLAY_WIDTH + j);
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
    if (!oled_task_user()) {
        return false;
    }
    if ((timer_elapsed32(oled_logo_timer) < SHOW_LOGO)) {
        render_logo();
    } else {
        clear_screen();
        user_oled_magic();
    }
    return false;
}

#endif


bool led_update_kb(led_t led_state) {
    // Disable the default LED update code, so that lock LEDs could be reused to show layer status.
    return false;
}

void matrix_scan_kb(void) {

    toggle_leds();
    matrix_scan_user();

}

bool process_record_kb(uint16_t keycode, keyrecord_t* record) {

    switch (keycode) {
        case (TT(_LWR)):
            if (!record->event.pressed && record->tap.count == TAPPING_TOGGLE) {
                // This runs before the TT() handler toggles the layer state, so the current layer state is the opposite of the final one after toggle.
                set_led_toggle(_LWR, !layer_state_is(_LWR));
            }
            return true;
            break;
        case (TT(_RSE)):
            if (record->event.pressed && record->tap.count == TAPPING_TOGGLE) {
                set_led_toggle(_RSE, !layer_state_is(_RSE));
            }
            return true;
            break;
        default:
            return true;
    }
}

layer_state_t layer_state_set_kb(layer_state_t state) {

#ifdef RGBLIGHT_ENABLE

   set_rgb_layers(state);

#endif

   return update_tri_layer_state(state, _LWR, _RSE, _ADJ);
}

#ifdef RGBLIGHT_ENABLE

layer_state_t default_layer_state_set_kb(layer_state_t state) {

    set_default_rgb_layers(state);
    return state;
}

#endif

void keyboard_post_init_kb(void) {

#ifdef RGBLIGHT_ENABLE
  // Enable the LED layers
  rgblight_layers = my_rgb();
#endif

  init_lwr_rse_led(toggle_lwr, toggle_rse);

#ifdef OLED_ENABLE
  init_timer();
#endif
#ifdef CONSOLE_ENABLE
  debug_enable = true;
  debug_matrix = true;
  debug_keyboard = true;
#endif

  keyboard_post_init_user();

}
