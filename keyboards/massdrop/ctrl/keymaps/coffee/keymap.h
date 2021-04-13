#include QMK_KEYBOARD_H

#include <print.h>
#include <string.h>

//bool disable_layer_color;

enum layout_names {
    _MAIN = 0,       // Keys Layout: The main keyboard layout that has all the characters
    _RGB_VOL,
    _NUMPAD,
    _CODE,
};

enum ctrl_keycodes {
    U_T_AUTO = SAFE_RANGE,  // USB Extra Port Toggle Auto Detect / Always Active
    U_T_AGCR,               // USB Toggle Automatic GCR control
    DBG_TOG,                // DEBUG Toggle On / Off
    DBG_MTRX,               // DEBUG Toggle Matrix Prints
    DBG_KBD,                // DEBUG Toggle Keyboard Prints
    DBG_MOU,                // DEBUG Toggle Mouse Prints
    MD_BOOT,                // Restart into bootloader after hold timeout
    TERMINAL,               // CTRL+ALT+T
};

enum coding_keycodes {
    MDPrev = TERMINAL + 1,  // Markdown preview
    OPN_FLD,                // Open folder
    STTNGS,                 // Open settings
    EXTNSH,                 // Open Extensions
    SD_BR,                  // Hide/Show the side bar (files search etc)
    CLS_FDR,                // Close a folder

    GCLONE,               // git clone
    GRESET,               // git reset
    GBRANH,               // git branch
    GCHECK,               // git checkout
    GMERGE,               // git merge
    GREMTE,               // git remote add
    GFETCH,               // git fetch
    GPULL,                // git pull
    GPUSH,                // git push
    GLOG,                 // git log
};

#define DISABLE_RGB_MATRIX_RAINDROPS
#define DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#define DISABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#define DISABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#define DISABLE_RGB_MATRIX_DUAL_BEACON
#define DISABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#define DISABLE_RGB_MATRIX_SOLID_SPLASH
#define DISABLE_RGB_MATRIX_SPLASH
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS

#define DYNAMIC_MACRO_NO_NESTING
