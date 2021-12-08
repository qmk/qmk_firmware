# Layer Indication Code 

At least for RGB Light, the `layer_state_set` function is used to detect the current highest layer, and change the underglow based on that layer.  

This works for both the regular layers, and for the default layers, too.

I use the sethsv variants of the commands, so that different modes can be used, as well. 

RGB Matrix uses a custom, per board implementation, at the moment. 

# RGB Light Startup Animation

On startup, if enabled, the board will cycle through the entire hue wheel, starting and ending on the default layer color. 

```c
void keyboard_post_init_rgb(void) {
#if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_STARTUP_ANIMATION)
    if (userspace_config.rgb_layer_change) { rgblight_enable_noeeprom(); }
    if (rgblight_config.enable) {
        layer_state_set_user(layer_state);
        uint16_t old_hue = rgblight_config.hue;
        rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
        for (uint16_t i = 255; i > 0; i--) {
            rgblight_sethsv_noeeprom( ( i + old_hue) % 255, 255, 255);
            matrix_scan();
            wait_ms(10);
        }
    }
#endif
    layer_state_set_user(layer_state);
}
```

This could probably benefit from some cleanup and better handling. 


# RGB Light Twinkling 

This enables random twinkling of the LEDs when typing. 

# RGB Light Mod Indicators

Allows feedback of which mods (oneshot or otherwise) are enabled. 
