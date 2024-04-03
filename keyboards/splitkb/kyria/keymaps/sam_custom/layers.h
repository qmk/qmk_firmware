#pragma once

// if you need more than 8 layers, remove
//      #define LAYER_STATE_8BIT
// from conf.gh, which is there for space saving
enum layers {
    _QWERTY = 0,
    _NUMPAD,
    _SYMBOL,
    _SHIFT,
    _MAGIC,
    _WINDOW,
};
