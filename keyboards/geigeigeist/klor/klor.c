// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include "klor.h"

#ifdef OLED_ENABLE
oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}

void render_keyboard_status(void) {
    static const char PROGMEM sep_v[]  = {0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0};
    static const char PROGMEM sep_h1[] = {0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0};
    static const char PROGMEM sep_h2[] = {0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0};
    static const char PROGMEM face_1[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0xE1, 0};
    static const char PROGMEM face_2[] = {0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xE1, 0};
    static const char PROGMEM os_m_1[] = {0x95, 0x96, 0};
    static const char PROGMEM os_m_2[] = {0xB5, 0xB6, 0};
    static const char PROGMEM os_w_1[] = {0x97, 0x98, 0};
    static const char PROGMEM os_w_2[] = {0xB7, 0xB8, 0};
    static const char PROGMEM s_lock[] = {0x8F, 0x90, 0};
    static const char PROGMEM n_lock[] = {0x91, 0x92, 0};
    static const char PROGMEM c_lock[] = {0x93, 0x94, 0};
    static const char PROGMEM b_lock[] = {0xE1, 0xE1, 0};
    static const char PROGMEM hap_en[] = {0xB1, 0xB2, 0};
#    ifdef AUDIO_ENABLE
    static const char PROGMEM aud_en[] = {0xAF, 0xB0, 0};
    static const char PROGMEM aud_di[] = {0xCF, 0xD0, 0};
#    endif
    oled_write_ln_P(sep_v, false);
    oled_write_P(keymap_config.swap_lctl_lgui ? os_m_1 : os_w_1, false);
    oled_write_P(sep_h1, false);
    oled_write_P(face_1, false);
    oled_write_P(keymap_config.swap_lctl_lgui ? os_m_2 : os_w_2, false);
    oled_write_P(sep_h1, false);
    oled_write_P(face_2, false);
    oled_write_ln_P(sep_v, false);

    led_t led_usb_state = host_keyboard_led_state();
    oled_write_P(led_usb_state.num_lock ? n_lock : b_lock, false);
    oled_write_P(led_usb_state.caps_lock ? c_lock : b_lock, false);
    oled_write_P(led_usb_state.scroll_lock ? s_lock : b_lock, false);
    oled_write_P(sep_h2, false);

#    ifndef AUDIO_ENABLE
    oled_write_P(b_lock, false);
#    endif
    oled_write_P(b_lock, false);

#    ifdef AUDIO_ENABLE
    oled_write_P(is_audio_on() ? aud_en : aud_di, false);
#    endif
    oled_write_P(hap_en, false);
}

bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }
    if (is_keyboard_master()) {
        render_keyboard_status();
    } else {
        oled_write_raw_P(klor_face, sizeof(klor_face));
    }
    return false;
}
#endif
