bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {               // This will do most of the grunt work with the keycodes.
    case ALT_TAB:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LALT);
        } 
        alt_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;
  }
  return true;
}

void matrix_scan_user(void) {     // The very important timer. 
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1000) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
}

/**
 * Key Mods Function
 *
 * This turns 3d, 4b, 4d and 4e into arrow keys when tapped,
 * and RSFT, RCTL, RGUI and HYPR, respectively.
 *
 * @DEPRECATED -- view: https://docs.qmk.fm/#/custom_quantum_functions
 */
const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_MODS_TAP_KEY(MOD_RSFT, KC_UP),
    [1] = ACTION_MODS_TAP_KEY(MOD_RCTL, KC_DOWN),
    [2] = ACTION_MODS_TAP_KEY(MOD_RGUI, KC_LEFT),
    [3] = ACTION_MODS_TAP_KEY(MOD_HYPR, KC_RIGHT),
};
