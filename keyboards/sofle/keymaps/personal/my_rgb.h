#ifdef RGBLIGHT_ENABLE


// Setting default values
void matrix_init_user(void) {
     rgblight_enable();
     rgblight_setrgb(RGB_BLUE);
     //rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING);
}

// Defining lighting layers
const rgblight_segment_t PROGMEM my_layer0_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 12, HSV_BLUE} // Light LEDs 0 to 12 blue when layer0 is active. _COLEMAK
);
/*const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 12, HSV_GREEN} // Light LEDs 0 to 12 blue when layer1 is active. _ARTSEY
);*/
const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 12, HSV_RED} // Light LEDs 0 to 12 red when layer2 is active. _LOWER
);
const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 12, HSV_GOLD} // Light LEDs 0 to 12 orange when layer3 is active. _RAISE
);
const rgblight_segment_t PROGMEM my_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 12, HSV_MAGENTA} // Light LEDs 0 to 12 magenta when layer4 is active. _ADJUST
);

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_layer0_layer,
    my_layer1_layer,    // Overrides Colemak layer
    my_layer2_layer,    // Overrides other layers
    my_layer3_layer    // Overrides other layers
    //my_layer4_layer     // Overrides other layers
);

void keyboard_post_init_user(void) {
    rgblight_layers = my_rgb_layers;  // Enable the LED layers
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _COLEMAK));
    rgblight_set_layer_state(1, layer_state_cmp(state, _LOWER));
    rgblight_set_layer_state(2, layer_state_cmp(state, _RAISE));
    //rgblight_set_layer_state(1, layer_state_cmp(state, _ARTSEY));
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(1, layer_state_cmp(state, _LOWER));
    rgblight_set_layer_state(2, layer_state_cmp(state, _RAISE));
    rgblight_set_layer_state(3, layer_state_cmp(state, _ADJUST));
    return state;
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
            switch (get_highest_layer(layer_state)) {
                case _COLEMAK:
                    rgblight_setrgb(RGB_BLUE);
                    break;
                /*case _ARTSEY:
                    rgblight_setrgb(RGB_GREEN);
                    break;*/
                case _LOWER:
                    rgblight_setrgb(RGB_RED);
                    break;
                case _RAISE:
                    rgblight_setrgb(RGB_GOLD);
                break;
            }
            break;
    }
}

void matrix_scan_user(void) {

}

#endif
