#pragma once
#include "gotham.h"

#if defined(OLED_ANIMATIONS_ENABLE)
#    if defined(OLED_ANIM_DVD_LOGO)
#        include "oled_animations/dvd_logo.h"
#    elif defined(OLED_ANIM_STARFIELD)
#        include "oled_animations/starfield.h"
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
#    define OLED_STR_DVORAK "Dvorak"
#    define OLED_STR_WORKMAN "Workman"
#    define OLED_CHAR_COUNTORMAN "Norman"
#    define OLED_STR_GAME "Game"
#    define OLED_STR_GAMENUM "Numbers"

#    define OLED_STR_LAYER "Layer: "
#    define OLED_STR_LOWER "Lower"
#    define OLED_STR_RAISE "Raise"
#    define OLED_STR_ADJUST "Adjust"

#    define OLED_STR_ENC_MODE "Enc %d: "
#    define OLED_STR_ENC_MODE_VOLUME "Volume"
#    define OLED_STR_ENC_MODE_WORD_NAV "Word Nav"
#    define OLED_STR_ENC_MODE_LEFT_RIGHT "Left / Right"
#    define OLED_STR_ENC_MODE_UP_DOWN "Up / Down"
#    define OLED_STR_ENC_MODE_PAGING "Paging"
#else
#    define OLED_CHAR_COUNT (5 + 1)
#    define OLED_STR_UNKNOWN "???"
#    define OLED_STR_LAYER_NONE "-----"

#    define OLED_STR_LAYOUT "Lyt: "
#    define OLED_STR_QWERTY "Qrty"
#    define OLED_STR_COLEMAK "Cole"
#    define OLED_STR_DVORAK "Dvrk"
#    define OLED_STR_WORKMAN "Wkmn"
#    define OLED_CHAR_COUNTORMAN "Norm"
#    define OLED_STR_GAME "Game"
#    define OLED_STR_GAMENUM "Num"

#    define OLED_STR_LAYER "Lyr: "
#    define OLED_STR_LOWER "Lower"
#    define OLED_STR_RAISE "Raise"
#    define OLED_STR_ADJUST "Adjst"

#    define OLED_STR_ENC_MODE "En%d: "
#    define OLED_STR_ENC_MODE_VOLUME "Vol"
#    define OLED_STR_ENC_MODE_WORD_NAV "Word"
#    define OLED_STR_ENC_MODE_LEFT_RIGHT "L / R"
#    define OLED_STR_ENC_MODE_UP_DOWN "U / D"
#    define OLED_STR_ENC_MODE_PAGING "Page"
#endif

#ifndef OLED_CUSTOM_TIMEOUT
#    define OLED_CUSTOM_TIMEOUT 5000
#endif

#if OLED_CUSTOM_TIMEOUT > 0
void oled_sleep_timer_reset(void);
bool oled_reset_flag_get(void);
void oled_reset_flag_set(bool value);
#endif

bool process_record_user_oled(uint16_t keycode, keyrecord_t *record);

oled_rotation_t oled_init_keymap(oled_rotation_t rotation);
bool            process_record_keymap_oled(uint16_t keycode, keyrecord_t *record);

void render_kyria_logo(void);
void render_layer(void);
void render_status(void);
void render_status_main(void);
void render_status_secondary(void);
#ifdef ENCODER_ENABLE
void render_encoder(uint8_t index);
void render_encoders(void);
#endif
// #ifdef THUMBSTICK_ENABLE
// void render_thumbstick(thumbstick_mode_t mode);
// #endif
