#pragma once

enum rj_layers {
    L_BASE,

#ifdef USER_INCLUDE_QWERTY
    L_QWERTY,
#endif

#ifdef USER_INCLUDE_GAMING_LAYER
    L_GAMING,
#endif

    L_NUMBERS,
    L_SYMBOLS,
    L_NAVIGATION,
    L_FN,
    _LAYER_SAFE_RANGE
};
