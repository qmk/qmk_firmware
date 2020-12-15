#include "rverst.h"
#include "print.h"

#ifdef UNICODE
#include "unicode.h"
#endif

userspace_config_t userspace_config;

int get_mode(void) {
    int m = 0;
    if (userspace_config.mode_1) {
        m += 1;
    }
    if (userspace_config.mode_2) {
        m += 2;
    }
    if (userspace_config.mode_3) {
        m += 4;
    }

    return m;
}

void set_mode(int mode, bool save) {
    if (mode == get_mode()) {
        return;
    }
    switch_mode(mode);

    if (mode > 7) {
        mode = 7;
    }
    if (mode >= 4) {
        userspace_config.mode_3 = true;
        mode -= 4;
    } else {
        userspace_config.mode_3 = false;
    }
    if (mode >= 2) {
        userspace_config.mode_2 = true;
        mode -= 2;
    } else {
        userspace_config.mode_2 = false;
    }
    if (mode > 0) {
        userspace_config.mode_1 = true;
    } else {
        userspace_config.mode_1 = false;
    }

    if (save) {
        eeconfig_update_user(userspace_config.raw);
    }
}

void switch_mode(int mode) {
#ifdef UNICODE
    switch (mode) {
        case MAC_UNI:
            set_unicode_input_mode(UC_MAC);
            break;
        case WINDOWS_UNI:
            set_unicode_input_mode(UC_WINC);
            break;
        case LINUX_UNI:
            set_unicode_input_mode(UC_LNX);
            break;
    }
#endif
}

//**********************
// keyboard_pre_init
//**********************
__attribute__((weak)) void keyboard_pre_init_keymap(void) {}

void keyboard_pre_init_user(void) {
    userspace_config.raw = eeconfig_read_user();
    switch_mode(get_mode());
    keyboard_pre_init_keymap();
}

//************************
// keyboard_post_init
//************************
__attribute__((weak)) void keyboard_post_init_keymap(void) {}

void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
    debug_enable = true;
    // debug_matrix=true;
    // debug_keyboard = true;

#ifdef RGBLIGHT_ENABLE
    rgblight_sethsv_noeeprom(HSV_BLUE);
#endif

    keyboard_post_init_keymap();
}

//**********************
// eeconfig_init
//**********************

__attribute__((weak)) void eeconfig_init_keymap(void) {}

void eeconfig_init_user(void) {
    userspace_config.raw = 0;
    eeconfig_update_user(userspace_config.raw);
    eeconfig_init_keymap();
    keyboard_init();
}

//**********************
// process_record
//**********************
__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode < SAFE_RANGE) {
        return true;
    }

    if (!record->event.pressed) {
        return process_record_keymap(keycode, record);
    }

    bool ls = keyboard_report->mods & MOD_BIT(KC_LSFT);
    bool rs = keyboard_report->mods & MOD_BIT(KC_RSFT);
    bool as = ls || rs;

    int mode = get_mode();

    switch (keycode) {
        case RV_SM0:
        case RV_SM0S:
            set_mode(MAC, keycode == RV_SM0S);
            return false;
        case RV_SM1:
        case RV_SM1S:
            set_mode(MAC, keycode == RV_SM1S);
            return false;
        case RV_SM2:
        case RV_SM2S:
            set_mode(MAC, keycode == RV_SM2S);
            return false;
        case RV_SM3:
        case RV_SM3S:
            set_mode(MAC_UNI, keycode == RV_SM3S);
            return false;
        case RV_SM4:
        case RV_SM4S:
            set_mode(WINDOWS_UNI, keycode == RV_SM4S);
            return false;
        case RV_SM5:
        case RV_SM5S:
            set_mode(LINUX_UNI, keycode == RV_SM5S);
            return false;

        // Umlauts - äÄöÖüÜ
        case RV_AUML:
        case RV_OUML:
        case RV_UUML:
            if (mode == MAC) {
                if (ls) unregister_code(KC_LSFT);
                if (rs) unregister_code(KC_RSFT);

                register_code(KC_LALT);
                tap_code(KC_U);
                unregister_code(KC_LALT);

                if (as) register_code(KC_LSFT);
                if (keycode == RV_AUML) {
                    tap_code(KC_A);
                } else if (keycode == RV_OUML) {
                    tap_code(KC_O);
                } else if (keycode == RV_UUML) {
                    tap_code(KC_U);
                }
                if (rs) {
                    unregister_code(KC_LSFT);
                    register_code(KC_RSFT);
                }
            } else if (mode > LINUX) {
                if (keycode == RV_AUML) {
                    if (as) send_unicode_string("Ä");
                    else send_unicode_string("ä");
                } else if (keycode == RV_OUML) {
                    if (as) send_unicode_string("Ö");
                    else send_unicode_string("ö");
                } else if (keycode == RV_UUML) {
                    if (as) send_unicode_string("Ü");
                    else send_unicode_string("ü");
                }
            }
            return false;

        // Euro sign - €
        case RV_EUR:
            if (mode == MAC) {
                register_code(KC_LALT);
                register_code(KC_LSFT);
                tap_code(KC_2);
                unregister_code(KC_LSFT);
                unregister_code(KC_LALT);
            } else if (mode > LINUX) {
                send_unicode_string("€");
            }
            return false;

        // Sharp-S - ß
        case RV_SZ:
            if (mode == MAC) {
                register_code(KC_LALT);
                tap_code(KC_S);
                unregister_code(KC_LALT);
            } else if (mode > LINUX) {
                send_unicode_string("ß");
            }
            return false;
    }

    return process_record_keymap(keycode, record);
}
