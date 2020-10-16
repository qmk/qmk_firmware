/* Copyright 2020 Gautham Yerroju <gautham.yerroju@gmail.com>
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
#include "gotham.h"

#if defined(OLED_ANIMATIONS_ENABLE)
#    if defined(OLED_ANIM_STARFIELD)
#        include "oled_animations/starfield.h"
#    elif defined(OLED_ANIM_IMAGE_BOUNCE)
#        include "oled_animations/image_bounce.h"
#    endif
#endif

#ifdef ENCODER_ENABLE
#    include "encoder_utils.h"
#    include <stdio.h>
#endif

#ifdef THUMBSTICK_ENABLE
#    include "thumbstick.h"
#endif

#ifdef OLED_DISPLAY_128X64
#    define OLED_CHAR_COUNT (21 + 1)
#    define OLED_STR_UNKNOWN "???"
#    define OLED_STR_LAYER_NONE "-----"

#    define OLED_STR_LAYOUT "Lyout: "
#    define OLED_STR_QWERTY "Qwerty"
#    define OLED_STR_COLEMAK "Colemak"
#    define OLED_STR_COLEMAK_DH "Colemak DH"
#    define OLED_STR_COLEMAK_DHM "Colemak DHm"
#    define OLED_STR_DVORAK "Dvorak"
#    define OLED_STR_WORKMAN "Workman"
#    define OLED_CHAR_COUNTORMAN "Norman"
#    define OLED_STR_GAME "Game"
#    define OLED_STR_GAMENAV "Arrows"
#    define OLED_STR_GAMENUM "Numbers"

#    define OLED_STR_LAYER "Layer: "
#    define OLED_STR_LOWER "Lower"
#    define OLED_STR_RAISE "Raise"
#    define OLED_STR_ADJUST "Adjust"

#    define OLED_STR_MAC_MODE "Mac mode"

#    define OLED_STR_ENC_MODE "Enc %d: "
#    define OLED_STR_ENC_MODE_VOLUME "Volume"
#    define OLED_STR_ENC_MODE_WORD_NAV "Word Nav"
#    define OLED_STR_ENC_MODE_LEFT_RIGHT "Left / Right"
#    define OLED_STR_ENC_MODE_UP_DOWN "Up / Down"
#    define OLED_STR_ENC_MODE_PAGING "Paging"

#    define OLED_STR_THUMBSTICK_MODE "JoySt: "
#    define OLED_STR_THUMBSTICK_MODE_MOUSE "Mouse"
#    define OLED_STR_THUMBSTICK_MODE_ARROWS "Arrows"
#    define OLED_STR_THUMBSTICK_MODE_SCROLL "Scroll"
#else
#    define OLED_CHAR_COUNT (5 + 1)
#    define OLED_STR_UNKNOWN "???"
#    define OLED_STR_LAYER_NONE "-----"

#    define OLED_STR_LAYOUT "Lyt: "
#    define OLED_STR_QWERTY "Qrty"
#    define OLED_STR_COLEMAK "Cole"
#    define OLED_STR_COLEMAK_DH "ColDH"
#    define OLED_STR_COLEMAK_DHM "ColDm"
#    define OLED_STR_DVORAK "Dvrk"
#    define OLED_STR_WORKMAN "Wkmn"
#    define OLED_CHAR_COUNTORMAN "Norm"
#    define OLED_STR_GAME "Game"
#    define OLED_STR_GAMENAV "Nav"
#    define OLED_STR_GAMENUM "Num"

#    define OLED_STR_LAYER "Lyr: "
#    define OLED_STR_LOWER "Lower"
#    define OLED_STR_RAISE "Raise"
#    define OLED_STR_ADJUST "Adjst"

#    define OLED_STR_MAC_MODE "macOS"

#    define OLED_STR_ENC_MODE "En%d: "
#    define OLED_STR_ENC_MODE_VOLUME "Vol"
#    define OLED_STR_ENC_MODE_WORD_NAV "Word"
#    define OLED_STR_ENC_MODE_LEFT_RIGHT "L / R"
#    define OLED_STR_ENC_MODE_UP_DOWN "U / D"
#    define OLED_STR_ENC_MODE_PAGING "Page"

#    define OLED_STR_THUMBSTICK_MODE "Joy: "
#    define OLED_STR_THUMBSTICK_MODE_MOUSE "Mouse"
#    define OLED_STR_THUMBSTICK_MODE_ARROWS "Arrow"
#    define OLED_STR_THUMBSTICK_MODE_SCROLL "Scrol"
#endif

#ifndef OLED_CUSTOM_TIMEOUT
#    define OLED_CUSTOM_TIMEOUT 5000
#endif

#if OLED_CUSTOM_TIMEOUT > 0
void oled_sleep_timer_reset(void);
#    ifdef SPLIT_KEYBOARD
bool oled_reset_flag_get(void);
void oled_reset_flag_set(bool value);
#    endif
#endif

oled_rotation_t oled_init_keymap(oled_rotation_t rotation);
oled_rotation_t oled_init_user(oled_rotation_t rotation);
bool            process_record_keymap_oled(uint16_t keycode, keyrecord_t *record);
bool            process_record_user_oled(uint16_t keycode, keyrecord_t *record);

void render_keyboard_info(void);
void render_layout(void);
void render_layer(void);
#ifdef ENCODER_ENABLE
void render_encoder(uint8_t index);
void render_encoders(void);
#endif
#ifdef THUMBSTICK_ENABLE
void render_thumbstick(void);
#endif
void render_mac_mode(void);

void render_status(void);
void render_status_main(void);
void render_status_secondary(void);
