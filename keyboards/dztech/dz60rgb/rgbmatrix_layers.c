void rgb_matrix_layer_helper (uint8_t red, uint8_t green, uint8_t blue, bool default_layer) {
  for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
    if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_MODIFIER)) {
        rgb_matrix_set_color( i, red, green, blue );
    }
  }
}

void rgb_matrix_indicators_user(void) {
      uint8_t this_led = host_keyboard_leds();
      if (!g_suspend_state) {
        switch (biton32(layer_state)) {
          case _LAYER1:
            rgb_matrix_layer_helper(0xFF, 0x00, 0x00, false); break;
          case _LAYER2:
            rgb_matrix_layer_helper(0x00, 0xFF, 0x00, false); break;
          case _LAYER3:
            rgb_matrix_layer_helper(0x00, 0x00, 0xFF, false); break;
          case _LAYER4:
            rgb_matrix_layer_helper(0xFF, 0xFF, 0x00, false); break;
                                      }
                            }
      if ( this_led & (1<<USB_LED_CAPS_LOCK)) {
            rgb_matrix_set_color(40, 0xFF, 0xFF, 0xFF);
      }
}
