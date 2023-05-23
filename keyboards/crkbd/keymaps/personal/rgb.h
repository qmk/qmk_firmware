/*#ifdef RGBLIGHT_ENABLE

// Defining lighting layers
const rgblight_segment_t PROGMEM my_layer0_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0,  54, HSV_BLUE} // Light LEDs 0 to 5 blue when layer0 is active. _COLEMAK
 //   ,{27, 6, HSV_BLUE} // Light LEDs 27 to 32 blue when layer0 is active. _COLEMAK
);
const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0,  54, HSV_RED} // Light LEDs 0 to 6 red when layer2 is active. _LOWER
 //   ,{27, 6, HSV_RED} // Light LEDs 27 to 32 blue when layer0 is active. _COLEMAK
);
const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0,  54, HSV_GOLD} // Light LEDs 0 to 6 orange when layer3 is active. _RAISE
 //   ,{27, 6, HSV_GOLD} // Light LEDs 27 to 32 blue when layer0 is active. _COLEMAK
);
const rgblight_segment_t PROGMEM my_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0,  54, HSV_MAGENTA} // Light LEDs 0 to 6 magenta when layer4 is active. _ADJUST
//    ,{27, 6, HSV_MAGENTA} // Light LEDs 27 to 32 blue when layer0 is active. _COLEMAK
);

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_layer0_layer,
    my_layer1_layer,    // Overrides Colemak layer
    my_layer2_layer,    // Overrides other layers
    my_layer3_layer    // Overrides other layers
);

layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _COLEMAK));
    rgblight_set_layer_state(1, layer_state_cmp(state, _LOWER));
    rgblight_set_layer_state(2, layer_state_cmp(state, _RAISE));
    rgblight_set_layer_state(3, layer_state_cmp(state, _ADJUST));
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(1, layer_state_cmp(state, _LOWER));
    rgblight_set_layer_state(2, layer_state_cmp(state, _RAISE));
    rgblight_set_layer_state(3, layer_state_cmp(state, _ADJUST));
    return state;
}

void keyboard_post_init_user(void) {
    rgblight_layers = my_rgb_layers;  // Enable the LED layers
}

// Setting default values
void matrix_init_user(void) {
     rgblight_enable();
     rgblight_setrgb(RGB_BLUE);
     rgblight_mode(RGBLIGHT_MODE_BREATHING);
     rgblight_set_effect_range(0, 54);
}

// Changing colors after the flag has been flipped...
void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_LOWER:
            rgblight_setrgb(RGB_RED);
            break;
        case KC_RAISE:
            rgblight_setrgb(RGB_GOLD);
            break;
        case KC_ADJUST:
            rgblight_setrgb(RGB_MAGENTA);
            break;
        default:
            rgblight_setrgb(RGB_BLUE);
            break;
    }
}

void matrix_scan_user(void) {

}

#endif*/
