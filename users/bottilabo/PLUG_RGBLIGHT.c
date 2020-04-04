
// define variables for reactive RGB
static int RGB_current_mode;

void PLUG_RGBLIGHT_matrix_init_user(void) {
    RGB_current_mode = rgblight_get_mode();
}

void PLUG_RGBLIGHT_matrix_scan_user(void) {
}

bool PLUG_RGBLIGHT_process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case RGB_MOD:
        if (record->event.pressed) {
            rgblight_mode(RGB_current_mode);
            rgblight_step();
            RGB_current_mode = rgblight_get_mode(); 
        }
        break;

    case RGBRST:
        if (record->event.pressed) {
            eeconfig_update_rgblight_default();
            rgblight_enable();
            RGB_current_mode = rgblight_get_mode();
        }
      break;
  }
  return true;
}
