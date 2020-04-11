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

const rgblight_segment_t PROGMEM _capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS( {0, 2, HSV_AZURE}, {RGBLED_NUM-2, 2, HSV_AZURE} ); // 0
const rgblight_segment_t PROGMEM _scrolllock_layer[] = RGBLIGHT_LAYER_SEGMENTS( {2, 2, HSV_PURPLE}, {RGBLED_NUM-4, 2, HSV_PURPLE} ); // 1

#define LAYER_OFFSET 2
const rgblight_segment_t PROGMEM _layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS( {RGBLED_NUM/2-1, 1, HSV_PURPLE} ); // 2
const rgblight_segment_t PROGMEM _layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS( {10, 3, HSV_MAGENTA} ); // 3
const rgblight_segment_t PROGMEM _layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS( {10, 1, HSV_GREEN} ); // 4

#define ACK_OFFSET 5
const rgblight_segment_t PROGMEM _no_layer[] = RGBLIGHT_LAYER_SEGMENTS( {9, 6, HSV_RED} ); // 5
const rgblight_segment_t PROGMEM _yes_layer[] = RGBLIGHT_LAYER_SEGMENTS( {9, 6, HSV_GREEN} ); // 6
const rgblight_segment_t PROGMEM _startup_layer[] = RGBLIGHT_LAYER_SEGMENTS( {0, RGBLED_NUM, HSV_BLUE} ); // 7

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM _rgb_layers[] =
    RGBLIGHT_LAYERS_LIST( _capslock_layer, _scrolllock_layer, _layer1_layer, _layer2_layer, _layer3_layer, _no_layer, _yes_layer, _startup_layer );
const uint8_t PROGMEM _n_rgb_layers = sizeof(_rgb_layers) / sizeof(_rgb_layers[0]) - 1;

void clear_rgb_layers() {
    dprint("clear_rgb_layers()\n");
    for (uint8_t i=0; i<_n_rgb_layers; i++) {
        rgblight_set_layer_state(i, false);
    }
}

void do_rgb_layers(layer_state_t state, uint8_t start, uint8_t end) {
    for (uint8_t i=start; i<end; i++) {
      bool is_on = layer_state_cmp(state, i);
      dprintf("layer[%u]=%u\n", i, is_on);
      rgblight_set_layer_state(LAYER_OFFSET + i - 1, is_on);
    }
}

void keyboard_post_init_user_rgb(void) {
    // Enable the LED layers
    rgblight_layers = _rgb_layers;
    do_rgb_layers(default_layer_state, LAYER_BASE_DEFAULT+1, LAYER_BASE_REGULAR);
    do_rgb_layers(layer_state, LAYER_BASE_REGULAR, LAYER_BASE_END);
    rgblight_blink_layer(ACK_OFFSET + 2, RGB_LAYER_WELCOME_DURATION);
}

layer_state_t default_layer_state_set_user_rgb(layer_state_t state) {
    do_rgb_layers(state, 1u, LAYER_BASE_REGULAR);
    return state;
}

layer_state_t layer_state_set_user_rgb(layer_state_t state) {
    do_rgb_layers(state, LAYER_BASE_REGULAR, LAYER_BASE_END);
    return state;
}

bool led_update_user_rgb(led_t led_state) {
    dprintf("num=%u, cap=%u, scl=%u, cmp=%u, kan=%u\n", 
	led_state.num_lock, led_state.caps_lock, led_state.scroll_lock, 
	led_state.compose, led_state.kana);
    rgblight_set_layer_state(0, led_state.caps_lock);
    rgblight_set_layer_state(1, led_state.scroll_lock);
    return true;
}

void rgb_layer_ack(bool yn) {
    uint8_t layer = ACK_OFFSET + (yn?1:0);
    dprintf("rgb_layer_ack(%u) ==> %u\n", yn, layer);
    rgblight_blink_layer(layer, RGB_LAYER_ACK_DURATION);
}

extern keymap_config_t keymap_config;
extern rgblight_config_t rgblight_config;

bool process_record_user_rgb(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case SPI_GLO:
                spidey_swirl();
                return false;
        }
    }

    return true;
}

void post_process_record_user_rgb(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {
        // Acks follow...
        case DEBUG:
            rgb_layer_ack(debug_enable);
            break;

        case SPI_LNX:
        case SPI_OSX:
        case SPI_WIN:
            rgb_layer_ack(true);
            break;

        case RGB_TOG:
            rgb_layer_ack(rgblight_config.enable);
            break;

#ifdef VELOCIKEY_ENABLE
        case VLK_TOG:
            rgb_layer_ack(velocikey_enabled());
            break;
#endif

#ifdef NKRO_ENABLE
        case NK_TOGG:
        case NK_ON:
        case NK_OFF:
            rgb_layer_ack(keymap_config.nkro);
            break;
#endif
    }

}
