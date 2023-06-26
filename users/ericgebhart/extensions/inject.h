#if defined( CONSOLE_ENABLE) && defined(CONSOLE_KEY_LOGGER_ENABLE)
  if (pressed) {
    combo_t *combo = &key_combos[combo_index];
    uint8_t idx = 0;
    uint16_t combo_keycode;
    while ((combo_keycode = pgm_read_word(&combo->keys[idx])) != COMBO_END) {
      uprintf("0x%04X,NA,NA,%u,%u,0x%02X,0x%02X,0\n",
              combo_keycode,
              /* <missing row information> */
              /* <missing column information> */
              get_highest_layer(layer_state),
              pressed,
              get_mods(),
              get_oneshot_mods()
              );
      idx++;
    }
  }
#endif
