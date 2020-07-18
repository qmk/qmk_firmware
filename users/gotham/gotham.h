#ifndef USERSPACE
#define USERSPACE

#pragma once
#include QMK_KEYBOARD_H

#include "version.h"
#include "wrappers.h"
#include "process_records.h"

enum userspace_layers {
    _QWERTY = 0,
    _COLEMAK,
    _DVORAK,
    _WORKMAN,
    _NORMAN,
    _GAME,
    _GAMENUM,
    _LOWER,
    _RAISE,
    _ADJUST,
};

#endif
