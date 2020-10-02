
void keyboard_post_init_rgb(void) {
#if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_STARTUP_ANIMATION)
    /*if (userspace_config.rgb_layer_change) { rgblight_enable_noeeprom(); }*/
    /*if (rgblight_config.enable) {*/
        /*layer_state_set_user(layer_state);*/
        /*uint16_t old_hue = rgblight_config.hue;*/
        uint16_t old_hue = 170;
        rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
        for (uint16_t i = 255; i > 0; i--) {
            rgblight_sethsv_noeeprom( ( i + old_hue) % 255, 255, 255);
            matrix_scan();
            wait_ms(10);
        }
    /*}*/
#endif
    /*layer_state_set_user(layer_state);*/
}
