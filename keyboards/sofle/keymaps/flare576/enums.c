#pragma once
enum _layers {
    /* _M_XYZ = Mac Os, _W_XYZ = Win/Linux */
    _BASE,
    _MOUS,
    _SYMS,
    _MDIA,
    _NPAD,
    _GAME,
};

enum custom_keycodes {
    _COMP1  = SAFE_RANGE,
    _COMP2,
    V_C_W,
    T_M_A,
    V_FS,
    T_FS,
};

enum custom_tapdance {
    TD_PLAY,
    TD_HOME,
};
