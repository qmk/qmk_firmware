extern keymap_config_t keymap_config;

/* uncomment to reset
void matrix_init_user(void) {
    eeconfig_init();
};
*/

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_dynamic_macro(keycode, record)) {
        return false;
    }
    return true;
}

// work in progress
uint32_t layer_state_set_user(uint32_t state) {
    switch (biton32(state)) {
        case DEF:
            set_all_leds_to(0,0,0);
            break;
        case FUN:
            // TODO light the fn keys
            // set_led_to(?, 0, 128, 0);
            // set_led_to(?, 0, 128, 0);
            break;
    }
    return state;
}

