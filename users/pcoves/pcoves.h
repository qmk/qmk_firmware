#pragma once

#include "quantum.h"

#define SECRET_ENABLE (__has_include("secret.h") && !defined(NO_SECRET))

enum {
    AUTRUCHE = SAFE_RANGE,
#ifdef RAINBOW_UNICORN_ENABLE
    RAINBOW_UNICORN_TOGGLE,
#endif
#ifdef UNICODE_ENABLE
    EMOTE0,
    EMOTE1,
    EMOTE2,
    EMOTE3,
#endif
#if SECRET_ENABLE
    SECRET0,
    SECRET1,
    SECRET2,
    SECRET3,
    SECRET4,
#endif
    PCOVES_SAFE_RANGE,
};

__attribute__((weak)) void eeconfig_init_keymap(void);
void eeconfig_init_user(void);

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record);
bool process_record_user(uint16_t keycode, keyrecord_t *record);
