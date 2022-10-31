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

#pragma once

#include QMK_KEYBOARD_H

enum userspace_mode {
    MAC = 0,
    WINDOWS,
    MAC_UNI,
    WINDOWS_UNI,
    LINUX_UNI,
};

enum userspace_keycodes {
    RV_NON = SAFE_RANGE,
    RV_SM0,   // set Mac Unicode mode
    RV_SM1,   // set Window Unicode mode
    RV_SM2,   // set Linux Unicode mode
    RV_SM3,   // set Mac lagecy mode
    RV_SM4,   // set Windows legacy mode
    RV_SM0S,  // set Mac Unicode mode and save
    RV_SM1S,  // set Windows Unicode mode and save
    RV_SM2S,  // set Linux Unicode and save
    RV_SM3S,  // set Mac legacy mode
    RV_SM4S,  // set Windows legacy and save
    RV_SAYM,  // say mode
    RV_LOCK,  // lock computer
    RV_AUML,  // äÄ
    RV_OUML,  // öÖ
    RV_UUML,  // üÜ
    RV_EUR,   // €
    RV_SZ,    // ß§
    RV_TM,    // ™
    RV_RT,    // ®
    RV_CC,    // ©
    RV_DEG,   // °
    RV_SNAP,  // Screenshot
    RV_PM,    // ±
    RV_UNEQ,  // ≠
    RV_SUP1,  // ¹
    RV_SUP2,  // ²
    RV_SUP3,  // ³
    RV_VINC,  // vim increase vertical split size (<c-w> 4>)
    RV_VDEC,  // vim decrease vertical split size (<c-w> 4<)
    RV_SINC,  // vim increase vertical split size (<c-w> 4+)
    RV_SDEC,  // vim decrease vertical split size (<c-w> 4-)
    RV_SEQU,  // vim equal split size (<c-w> =)
};

typedef union {
    uint32_t raw;
    struct {
        bool mode_1 : 1;
        bool mode_2 : 1;
        bool mode_3 : 1;
    };
} userspace_config_t;

extern userspace_config_t userspace_config;

uint8_t  get_mode(void);
void     set_mode(uint8_t mode, bool save);
void     switch_mode(uint8_t mode);
bool     is_unicode(uint8_t mode);

void keyboard_pre_init_keymap(void);
void keyboard_post_init_keymap(void);
void eeconfig_init_keymap(void);
bool process_record_keymap(uint16_t keycode, keyrecord_t *record);

