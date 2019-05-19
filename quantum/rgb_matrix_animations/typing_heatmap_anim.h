#if defined(RGB_MATRIX_FRAMEBUFFER_EFFECTS) && !defined(DISABLE_RGB_MATRIX_TYPING_HEATMAP)
RGB_MATRIX_EFFECT(TYPING_HEATMAP)
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

void process_rgb_matrix_typing_heatmap(keyrecord_t *record) {
    uint8_t row = record->event.key.row;
    uint8_t col = record->event.key.col;
    uint8_t m_row = row - 1;
    uint8_t p_row = row + 1;
    uint8_t m_col = col - 1;
    uint8_t p_col = col + 1;

    if (m_col < col)
      rgb_frame_buffer[row][m_col] = qadd8(rgb_frame_buffer[row][m_col], 16);
    rgb_frame_buffer[row][col] = qadd8(rgb_frame_buffer[row][col], 32);
    if (p_col < MATRIX_COLS)
      rgb_frame_buffer[row][p_col] = qadd8(rgb_frame_buffer[row][p_col], 16);

    if (p_row < MATRIX_ROWS) {
      if (m_col < col)
        rgb_frame_buffer[p_row][m_col] = qadd8(rgb_frame_buffer[p_row][m_col], 13);
      rgb_frame_buffer[p_row][col] = qadd8(rgb_frame_buffer[p_row][col], 16);
      if (p_col < MATRIX_COLS)
        rgb_frame_buffer[p_row][p_col] = qadd8(rgb_frame_buffer[p_row][p_col], 13);
    }

    if (m_row < row) {
      if (m_col < col)
        rgb_frame_buffer[m_row][m_col] = qadd8(rgb_frame_buffer[m_row][m_col], 13);
      rgb_frame_buffer[m_row][col] = qadd8(rgb_frame_buffer[m_row][col], 16);
      if (p_col < MATRIX_COLS)
        rgb_frame_buffer[m_row][p_col] = qadd8(rgb_frame_buffer[m_row][p_col], 13);
    }
}

bool TYPING_HEATMAP(effect_params_t* params) {
  // Modified version of RGB_MATRIX_USE_LIMITS to work off of matrix row / col size
  uint8_t led_min = RGB_MATRIX_LED_PROCESS_LIMIT * params->iter;
  uint8_t led_max = led_min + RGB_MATRIX_LED_PROCESS_LIMIT;
  if (led_max > sizeof(rgb_frame_buffer))
    led_max = sizeof(rgb_frame_buffer);

  if (params->init) {
    rgb_matrix_set_color_all(0, 0, 0);
    memset(rgb_frame_buffer, 0, sizeof rgb_frame_buffer);
  }

  // Render heatmap & decrease
  for (int i = led_min; i < led_max; i++) {
    uint8_t row = i % MATRIX_ROWS;
    uint8_t col = i / MATRIX_ROWS;
    uint8_t val = rgb_frame_buffer[row][col];

    // set the pixel colour
    uint8_t led[LED_HITS_TO_REMEMBER];
    uint8_t led_count = rgb_matrix_map_row_column_to_led(row, col, led);
    for (uint8_t j = 0; j < led_count; ++j)
    {
      if (!HAS_ANY_FLAGS(g_led_config.flags[led[j]], params->flags))
        continue;

      HSV hsv = { 170 - qsub8(val, 85), rgb_matrix_config.sat, scale8((qadd8(170, val) - 170) * 3, rgb_matrix_config.val) };
      RGB rgb = hsv_to_rgb(hsv);
      rgb_matrix_set_color(led[j], rgb.r, rgb.g, rgb.b);
    }

    rgb_frame_buffer[row][col] = qsub8(val, 1);
  }

  return led_max < sizeof(rgb_frame_buffer);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif // defined(RGB_MATRIX_FRAMEBUFFER_EFFECTS) && !defined(DISABLE_RGB_MATRIX_TYPING_HEATMAP)
