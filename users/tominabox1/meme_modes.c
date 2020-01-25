// Meme Modes
__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }

bool spongebob_mode = false;
bool spongebob_case = false;
bool aesthetic_mode = false;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (spongebob_mode) {
    switch(keycode) {
      case KC_A ... KC_Z:
        if (record->event.pressed) {
          (spongebob_case ^= 1) == 0 ? tap_code16(S(keycode)) : tap_code(keycode);
          return false; break;
        }
    }
  }
  if (aesthetic_mode) {
    switch(keycode) {
      case KC_A:
      case KC_E:
        if (record->event.pressed) {
          register_code(KC_LSFT);
          tap_code16(keycode);
          unregister_code(KC_LSFT);
          tap_code(KC_SPC);
        }
        return false; break;
      case KC_B ... KC_D:
      case KC_F ... KC_Z:
        if (record->event.pressed) {
          tap_code16(S(keycode));
          tap_code(KC_SPC);
        }
        return false; break;
      case KC_BSPC:
        if (record->event.pressed) {
          tap_code(KC_BSPC);
          tap_code(KC_BSPC);
        }
        return false; break;
      case KC_SPC:
        if (record->event.pressed) {
          tap_code(KC_SPC);
          tap_code(KC_SPC);
          tap_code(KC_SPC);
        }
        return false; break;
    }
  }
  switch(keycode) {
    case SPONGEBOB:
      if (record->event.pressed) {
        spongebob_mode ^= 1;
      }
      return false; break;
	case AESTHETIC:
      if (record->event.pressed) {
        aesthetic_mode ^= 1;
      }
      return false; break;
  }
  return process_record_keymap(keycode, record);
}
