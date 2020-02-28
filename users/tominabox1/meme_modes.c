// Meme Modes
__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }

bool spongebob_mode = false;
bool spongebob_case = false;
bool aesthetic_mode = false;
uint8_t mod_state;

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

    case KC_SLSH:
    if (record->event.pressed) {
      mod_state = get_mods();                                 // save mod state for comparison and later restoration
      if ((mod_state & MOD_MASK_CTRL) && (mod_state & MOD_MASK_SHIFT)) {                         // if either ctrl is held
        unregister_mods(MOD_BIT(KC_LCTRL) | MOD_BIT(KC_RCTRL) | MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSFT)); // unregister both ctrl
        tap_code(KC_SCLN);                                    // send ":" unmolested
        set_mods(mod_state);                                  // restore mod state
        return false;                                         // done processing
      }

      else if (mod_state & MOD_MASK_CTRL) {                         // if either ctrl is held
        unregister_mods(MOD_BIT(KC_LCTRL) | MOD_BIT(KC_RCTRL)); // unregister both ctrl
        tap_code16(KC_COLN);                                    // send ":" unmolested
        set_mods(mod_state);                                  // restore mod state
        return false;                                         // done processing
      }

      else {                                                  // else, if ctrl isn't held
      tap_code(KC_SLSH);                                    // send "/"
      return false;                                         // done processing
    }
  }
  return false; break;
}
return process_record_keymap(keycode, record);
}
