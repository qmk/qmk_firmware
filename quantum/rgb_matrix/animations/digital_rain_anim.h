// This is is a modification/enancement of the stock digital_rain animation
// It's a bit of a hack, but it turned out pretty nice
// You can now adjust the speed and hue of the animation using the standard config values


#if defined(RGB_MATRIX_FRAMEBUFFER_EFFECTS) && !defined(DISABLE_RGB_MATRIX_DIGITAL_RAIN_RELOADED)
RGB_MATRIX_EFFECT(DIGITAL_RAIN_RELOADED)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

#        ifndef RGB_DIGITAL_RAIN_DROPS
// lower the number for denser effect/wider keyboard
#            define RGB_DIGITAL_RAIN_DROPS 18
#        endif

bool DIGITAL_RAIN_RELOADED(effect_params_t* params) {

    // For a classic effect use these in your config.h
    //    #define RGB_MATRIX_STARTUP_HUE 0x50
    //    #define RGB_MATRIX_STARTUP_SPD 0xba

    // Add support for hue selection via keyboard config keys
    HSV hsvSetting = rgb_matrix_config.hsv;

    // algorithm ported from https://github.com/tremby/Kaleidoscope-LEDEffect-DigitalRain
    const uint8_t drop_ticks     = 100 - rgb_matrix_config.speed *0.4;
    const uint8_t pure_intensity = 0xfe;
    const uint8_t max_intensity  = 0xff;

    static uint8_t drop = 0;
    static uint8_t minBrightness = 5;

    if (params->init) {
       // rgb_matrix_set_color_all(minBrightness, minBrightness, minBrightness);
       RGB rgbInit  = hsv_to_rgb(hsvSetting);
       rgb_matrix_set_color_all(rgbInit.r, rgbInit.g, rgbInit.b);
       memset(g_rgb_frame_buffer, minBrightness, sizeof(g_rgb_frame_buffer));
       drop = 0;
    } else {
       // hack to update underglow on massdrop alt
       RGB rgbInit  = hsv_to_rgb(hsvSetting);
       rgb_matrix_set_color_all(rgbInit.r, rgbInit.g, rgbInit.b);
    }


    // Update LED Color/Values ------------------
    for (uint8_t col = 0; col < MATRIX_COLS; col++) {
        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            if (row == 0 && drop == 0 && rand() < RAND_MAX / RGB_DIGITAL_RAIN_DROPS) {
                // top row, pixels have just fallen and we're
                // making a new rain drop in this column
                g_rgb_frame_buffer[row][col] = max_intensity;
            } else if (g_rgb_frame_buffer[row][col] > minBrightness && g_rgb_frame_buffer[row][col] < max_intensity) {
                // neither fully bright nor dark, decay it
                g_rgb_frame_buffer[row][col]--;
            }
            // set the pixel colour
            uint8_t led[LED_HITS_TO_REMEMBER];
            uint8_t led_count = rgb_matrix_map_row_column_to_led(row, col, led);

            // TODO: multiple leds are supported mapped to the same row/column
            if (led_count > 0) {
                if (g_rgb_frame_buffer[row][col] > pure_intensity) {
                    // this bit could be better, use the stored value and force a minium of 200 to assure the "tip" is white
                    uint8_t booster = g_rgb_frame_buffer[row][col];
                    rgb_matrix_set_color(led[0], 180 + booster, 180 + booster, 180 + booster);
                } else {
                    // use the formerly green value as the brightness, which is pretty much what it was doing
                    const uint8_t ledBrightness =  (uint8_t)((uint16_t)max_intensity * g_rgb_frame_buffer[row][col] / pure_intensity);
                    // set the config-based HSV value to the animated one (but keeping the hue and saturation)
                    hsvSetting.v = ledBrightness >= minBrightness ? ledBrightness : minBrightness;
                    RGB rgb  = hsv_to_rgb(hsvSetting);
                    // apply to the current led, make sure we have a slight gray (my personal preference) for leds that aren't animating
                    rgb_matrix_set_color(
                        led[0],
                        rgb.r <minBrightness ? minBrightness: rgb.r,
                        rgb.g <minBrightness ? minBrightness: rgb.g,
                        rgb.b <minBrightness ? minBrightness: rgb.b
                    );
                }
            }
        }
    }

    // Update "Positions" ------------------
    if (++drop > drop_ticks) {
        // reset drop timer
        drop = 0;
        for (uint8_t row = MATRIX_ROWS - 1; row > 0; row--) {
            for (uint8_t col = 0; col < MATRIX_COLS; col++) {
                // if ths is on the bottom row and bright allow decay
                if (row == MATRIX_ROWS - 1 && g_rgb_frame_buffer[row][col] == max_intensity) {
                    g_rgb_frame_buffer[row][col]--;
                }
                // check if the pixel above is bright
                if (g_rgb_frame_buffer[row - 1][col] == max_intensity) {
                    // allow old bright pixel to decay
                    g_rgb_frame_buffer[row - 1][col]--;
                    // make this pixel bright
                    g_rgb_frame_buffer[row][col] = max_intensity;
                }
            }
        }
    }
    return false;
}

#    endif  // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif      // defined(RGB_MATRIX_FRAMEBUFFER_EFFECTS) && !defined(DISABLE_RGB_MATRIX_DIGITAL_RAIN)
