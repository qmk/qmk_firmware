#pragma once
#include "quantum.h"
#include "custom_tap_dance.h"

enum layer_number {
    _QWERTY = 0,
#ifndef GAMELAYER_DISABLE
    _GAME,
#endif
    _LOWER,
    _RAISE,
#ifdef TRILAYER_ENABLED
    _ADJUST
#endif
};

bool process_record_keymap(uint16_t keycode, keyrecord_t *record);
