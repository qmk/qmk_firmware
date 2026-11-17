static uint16_t last_keycode = KC_NO;
static uint16_t second_last_keycode = KC_NO;
static uint8_t last_mods = 0;
static uint8_t last_os_mods = 0;
static uint8_t second_last_mods = 0;
static uint8_t second_last_os_mods = 0;

enum skip_repeat_keycodes {
  KC_SKIP_REPEAT = SAFE_RANGE,
};

bool should_process_key_skip_repeat(uint16_t keycode) {
    return !(keycode == KC_LCTL || keycode == KC_RCTL || keycode == KC_LGUI || keycode == KC_RGUI || keycode == KC_LALT || keycode == KC_RALT || keycode == KC_LSFT || keycode == KC_RSFT || keycode == KC_CAPS || keycode == KC_SCRL || keycode == KC_PSCR || keycode == KC_NUM || keycode == CW_TOGG || keycode == OS_LSFT || keycode == OS_RSFT);
}

void set_keys_skip_repeat(uint8_t keycode, uint8_t mods, uint8_t os_mods) {
    second_last_keycode = last_keycode;
    second_last_mods = last_mods;
    second_last_os_mods = last_os_mods;
    last_keycode = keycode;
    last_mods = mods;
    last_os_mods = os_mods;
}

bool process_skip_repeat(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed || !should_process_key_skip_repeat(keycode)) {
        return keycode != KC_SKIP_REPEAT;
    }

    uint8_t mods = get_mods();
    uint8_t os_mods = get_oneshot_mods();

    switch(keycode) {
        case KC_SKIP_REPEAT:
            if (second_last_keycode != KC_NO) {
                if (!mods && !os_mods) {
                    set_mods(second_last_mods);
                    set_oneshot_mods(second_last_os_mods);
                }

#ifdef CAPS_WORD_ENABLE
                if (is_caps_word_on()) {
                    add_weak_mods(MOD_BIT(KC_LSFT));
                }
#endif

                tap_code(second_last_keycode);
                last_keycode = second_last_keycode;

#ifdef REPEAT_KEY_ENABLE
                set_last_mods(get_mods());
                set_last_keycode(second_last_keycode);
#endif
            }
            return false;
#ifdef REPEAT_KEY_ENABLE
        case QK_REP:
            keycode = get_last_keycode();
            last_mods = get_last_mods();
	    last_os_mods = 0;
            break;
#endif
    }

    set_keys_skip_repeat(keycode, mods, os_mods);
    return true;
}

bool remember_last_key_skip_repeat(uint16_t keycode, keyrecord_t* record, uint8_t* remembered_mods) {
    switch (keycode) {
        case KC_SKIP_REPEAT:
            return false;
    }

    return true;
}
