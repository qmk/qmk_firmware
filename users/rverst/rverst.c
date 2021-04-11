/* Copyright 2021 Robert Verst <robert@verst.eu> @rverst
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "rverst.h"
#include "print.h"

#ifdef UNICODEMAP_ENABLE
#    include "unicode.h"
#endif

userspace_config_t userspace_config;

uint8_t get_mode(void) {
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

void set_mode(uint8_t mode, bool save) {
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

void switch_mode(uint8_t mode) {
#ifdef UNICODEMAP_ENABLE
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

bool is_unicode(uint8_t mode) { return (mode == MAC_UNI) || (mode == WINDOWS_UNI) || (mode == LINUX_UNI); }

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
    // debug_enable = true;
    // debug_matrix=true;
    // debug_keyboard = true;

#ifdef RGBLIGHT_ENABLE

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
    if (!process_record_keymap(keycode, record)) {
        return false;
    }

    if (!record->event.pressed) {
        return true;
    }

    bool ls = (get_mods() | get_weak_mods()) & MOD_BIT(KC_LSFT);
    bool rs = (get_mods() | get_weak_mods()) & MOD_BIT(KC_RSFT);
    bool as = ls || rs;

    int mode = get_mode();

    switch (keycode) {
        case RV_SM0:
        case RV_SM0S:
            set_mode(MAC_UNI, keycode == RV_SM0S);
            return false;
        case RV_SM1:
        case RV_SM1S:
            set_mode(WINDOWS_UNI, keycode == RV_SM1S);
            return false;
        case RV_SM2:
        case RV_SM2S:
            set_mode(LINUX_UNI, keycode == RV_SM2S);
            return false;
        case RV_SM3:
        case RV_SM3S:
            set_mode(MAC, keycode == RV_SM3S);
            return false;
        case RV_SM4:
        case RV_SM4S:
            set_mode(WINDOWS, keycode == RV_SM4S);
            return false;

        case RV_SAYM:
            switch (mode) {
                case MAC:
                    send_string("MacOS (normal)");
                    break;
                case WINDOWS:
                    send_string("Windows (normal)");
                    break;
                case MAC_UNI:
                    send_string("MacOS (unicode)");
                    break;
                case WINDOWS_UNI:
                    send_string("Windows (unicode)");
                    break;
                case LINUX_UNI:
                    send_string("Linux (unicode)");
                    break;
            }
            return false;

        // Lock computer
        case RV_LOCK:
            if (mode == MAC || mode == MAC_UNI) {
                register_code(KC_LGUI);
                register_code(KC_LCTL);
                tap_code(KC_Q);
                unregister_code(KC_LCTL);
                unregister_code(KC_LGUI);
            } else if (mode == WINDOWS || mode == WINDOWS_UNI) {
                register_code(KC_LGUI);
                tap_code(KC_L);
                register_code(KC_LGUI);
            }
            return false;

        // Screenshot
        case RV_SNAP:
            if (mode == MAC || mode == MAC_UNI) {
                if (ls) unregister_code(KC_LSFT);
                if (rs) unregister_code(KC_RSFT);

                register_code(KC_LGUI);
                register_code(KC_LSFT);
                if (as)
                    tap_code(KC_5);
                else
                    tap_code(KC_4);
                unregister_code(KC_LSFT);
                unregister_code(KC_LGUI);

                if (ls) register_code(KC_LSFT);
                if (rs) register_code(KC_RSFT);
            } else if (mode == WINDOWS || mode == WINDOWS_UNI) {
                register_code(KC_LGUI);
                register_code(KC_LSFT);
                tap_code(KC_S);
                register_code(KC_LSFT);
                register_code(KC_LGUI);
            }
            return false;

        // Umlauts - äÄöÖüÜ
        case RV_AUML:
        case RV_OUML:
        case RV_UUML:
            if (is_unicode(mode)) {
                if (keycode == RV_AUML) {
                    if (as)
                        send_unicode_string("Ä");
                    else
                        send_unicode_string("ä");
                } else if (keycode == RV_OUML) {
                    if (as)
                        send_unicode_string("Ö");
                    else
                        send_unicode_string("ö");
                } else if (keycode == RV_UUML) {
                    if (as)
                        send_unicode_string("Ü");
                    else
                        send_unicode_string("ü");
                }
            } else if (mode == MAC) {
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
            } else if (mode == WINDOWS) {
                if (ls) unregister_code(KC_LSFT);
                if (rs) unregister_code(KC_RSFT);

                register_code(KC_RALT);
                tap_code(KC_1);
                if (keycode == RV_AUML) {
                    if (as)
                        tap_code(KC_4);
                    else
                        tap_code(KC_3);
                    tap_code(KC_2);
                } else if (keycode == RV_OUML) {
                    if (as) {
                        tap_code(KC_5);
                        tap_code(KC_3);
                    } else {
                        tap_code(KC_4);
                        tap_code(KC_8);
                    }
                } else if (keycode == RV_UUML) {
                    if (as) {
                        tap_code(KC_5);
                        tap_code(KC_4);
                    } else {
                        tap_code(KC_2);
                        tap_code(KC_9);
                    }
                }
                unregister_code(KC_RALT);

                if (ls) register_code(KC_LSFT);
                if (rs) register_code(KC_RSFT);
            }
            return false;

        // Euro sign - €
        // with legacy-mode for MAC and WINDOWS without unicode support
        case RV_EUR:
            if (is_unicode(mode)) {
                send_unicode_string("€");
            } else if (mode == MAC) {
                register_code(KC_LALT);
                register_code(KC_LSFT);
                tap_code(KC_2);
                unregister_code(KC_LSFT);
                unregister_code(KC_LALT);
            } else if (mode == WINDOWS) {
                register_code(KC_RALT);
                tap_code(KC_0);
                tap_code(KC_1);
                tap_code(KC_2);
                tap_code(KC_8);
                unregister_code(KC_RALT);
            }
            return false;

        // Sharp-S - ß
        // with legacy-mode for MAC and WINDOWS without unicode support
        case RV_SZ:
            if (is_unicode(mode)) {
                if (as) {
                    send_unicode_string("§");
                } else {
                    send_unicode_string("ß");
                }
            } else if (mode == MAC) {
                register_code(KC_LALT);
                tap_code(KC_S);
                unregister_code(KC_LALT);
            } else if (mode == WINDOWS) {
                register_code(KC_RALT);
                tap_code(KC_2);
                tap_code(KC_2);
                tap_code(KC_5);
                unregister_code(KC_RALT);
            }
            return false;

        // Trademark - ™
        case RV_TM:
            if (is_unicode(mode)) {
                send_unicode_string("™");
            }
            return false;

        // Registered trademark - ®
        case RV_RT:
            if (is_unicode(mode)) {
                send_unicode_string("®");
            }
            return false;

        // Copyright - ©
        case RV_CC:
            if (is_unicode(mode)) {
                send_unicode_string("©");
            }
            return false;

        // Degree - °
        case RV_DEG:
            if (is_unicode(mode)) {
                send_unicode_string("°");
            }
            return false;

        // Plus-minus - ±
        case RV_PM:
            if (is_unicode(mode)) {
                send_unicode_string("±");
            }
            return false;

        // Not equal - ≠
        case RV_UNEQ:
            if (is_unicode(mode)) {
                send_unicode_string("≠");
            }
            return false;

        // Superscript one - ¹
        case RV_SUP1:
            if (is_unicode(mode)) {
                send_unicode_string("¹");
            }
            return false;

        // Superscript two - ²
        case RV_SUP2:
            if (is_unicode(mode)) {
                send_unicode_string("²");
            }
            return false;

        // Superscript three - ³
        case RV_SUP3:
            if (is_unicode(mode)) {
                send_unicode_string("³");
            }
            return false;
    }

    return true;
}
