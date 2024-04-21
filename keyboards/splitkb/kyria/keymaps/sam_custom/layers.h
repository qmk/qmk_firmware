#pragma once

// if you need more than 8 layers, remove
//      #define LAYER_STATE_8BIT
// from config.h, which is there for space saving
enum layers {
    _QWERTY = 0,
    _NUMPAD,
    _SYMBOL,
    _SHIFT,
    _WINDOW,
    _MAGIC,
};
