#pragma once
#include QMK_KEYBOARD_H

// Custom keycodes and macros
enum userspace_custom_keycodes {
    QK_MAKE = SAFE_RANGE,  // QMK make command
    QK_FLSH,               // QMK flash command
    QK_VERS,               // QMK version

    // Programming macros
    PRG_EQ,                // ==
    PRG_NE,                // !=
    PRG_GEQ,               // >=
    PRG_LEQ,               // <=
    PRG_ARR,               // =>
    PS_ITEM,               // $_        (PowerShell - $PSItem variable)
    FS_PIPE,               // |>        (F# pipe operator)
    FS_ARR,                // ->        (F# lambda / pattern matching)
    SHEBANG,               // #!

    // USER_CAPS_WORD_ENABLE
    CAPWORD,

#ifdef USER_NUM_WORD_ENABLE
    NUMWORD,
#endif

    // USER_ENABLE_CUSTOM_SHIFT_CODES
    // Custom characters that send different symbols than usual when shifted
    KCC_COM,                // , or !
    KCC_DOT,                // . or @
    KCC_QUO,                // ' or ~

    // USER_MOUSE_JIGGLE_ENABLE
    MS_JIGL,

    // USER_ENABLE_SUPER_ALT_TAB
    SALTTAB,

    // USER_ENABLE_SECRETS
    K_SECR1,
    K_SECR2,
    K_SECR3,
    K_SECR4,

    DYNAMIC_MACRO_RANGE
};
