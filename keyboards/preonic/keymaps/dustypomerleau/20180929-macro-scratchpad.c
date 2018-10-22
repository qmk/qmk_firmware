```C
enum custom_keycodes {
  MY_MACRO = SAFE_RANGE
};

//...

case MY_MACRO: {
  if (record->event.pressed) {
    key_timer = timer_read();
    register_mods(MOD_BIT(KC_LCTL));
  }
  else if (timer_elapsed(key_timer) < TAPPING_TERM) {
    unregister_mods(MOD_BIT(KC_LCTL));
    register_mods(MOD_BIT(KC_LSFT));
    register_code(KC_EQL);
    unregister_code(KC_EQL);
    unregister_mods(MOD_BIT(KC_LSFT));
  }
  else {
    unregister_mods(MOD_BIT(KC_LCTL));
  }
  return false;
}

//...
```

case CTLPLS: {
  if (record->event.pressed) {
    key_timer = timer_read();
    register_mods(MOD_BIT(KC_LCTL));
  }
  else {
    unregister_mods(MOD_BIT(KC_LCTL));
    if (timer_elapsed(key_timer) < TAPPING_TERM) {
      register_mods(MOD_BIT(KC_LSFT));
      register_code(KC_EQL);
      unregister_code(KC_EQL);
      unregister_mods(MOD_BIT(KC_LSFT));
    }
  }
  return false;
}

//...
```

example:
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if(record->event.pressed) {
    switch (keycode) {
		// Cloud9 macros
		case CLOUD9_TAB_LEFT:
            SEND_STRING(SS_LCTRL("["));
            return true;
			break;
		case CLOUD9_TAB_RIGHT:
            SEND_STRING(SS_LCTRL("]"));
            return true;
			break;
		case CLOUD9_TAB_CLOSE:
            SEND_STRING(SS_LALT("w"));
            return true;
			break;
		case CLOUD9_GOTO_SYMBOL:
            SEND_STRING(SS_LSFT(SS_LCTRL("e")));
            return true;
			break;
		case CLOUD9_GOTO_LINE:
            SEND_STRING(SS_LCTRL("g"));
            return true;
			break;
		case CLOUD9_NAVIGATE:
            SEND_STRING(SS_LCTRL("e"));
            return true;
			break;
	}
  }
