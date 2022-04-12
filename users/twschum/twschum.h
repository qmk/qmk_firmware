#pragma once
#include <stdarg.h>
#include "quantum.h"
#include "xtonhasvim.h"

/**************************
 * QMK Features Used
 **************************
 * RGBLIGHT_ENABLE
 *  - Adds layer indication via RGB underglow
 *  - see the `layer_definitions` enum and following _*_HSV #defines
 *
 *
 *
 **************************
 * Custom Feature Flags
 **************************
 *
 * TWSCHUM_TAPPING_CTRL_PREFIX
 * - Adds feature that makes sending nested sequences of C-a, C-b[, C-b, ...]
 *   as simple as C-a b [b ...]
 * - Not necessarily super useful outside specialized nested tmux sessions,
 *   but it was a fun state-machine to build
 *
 * TWSCHUM_VIM_LAYER
 * - Fork of xtonhasvim, adding vim-emulation
 *
 * TWSCHUM_IS_MAC
 * - Flag for handling media keys and other settings between OSX and Win/Unix
 *   without having to include bootmagic
 *
 **************************
 * Features Wishlist
 **************************
 * use VIM_Q as macro recorder!
 * Dynamic macros
 * Leader functions
 * Uniicode leader commands??? (symbolic unicode)
 * Mac mode vs not: -probably bootmagic or use default with dynamic swap out here
 *    KC_MFFD(KC_MEDIA_FAST_FORWARD) and KC_MRWD(KC_MEDIA_REWIND) instead of KC_MNXT and KC_MPRV
 */

/* Each layer gets a color, overwritable per keyboard */
enum layers_definitions {
    _Base,
    _Vim,
    _Fn,
    _Nav,
    _Num,
    _Cfg,
    _None,
};
#ifdef RGBLIGHT_ENABLE
#define _Base_HSV_ON  HSV_WHITE
#define _Base_HSV_OFF 0, 0, 0
#define _Vim_HSV      HSV_ORANGE
#define _Fn_HSV       HSV_GREEN
#define _Nav_HSV      HSV_AZURE
#define _Num_HSV      HSV_GOLD
#define _Cfg_HSV      HSV_RED
#define _None_HSV     HSV_WHITE
#endif

enum extra_keycodes {
    TWSCHUM_START = VIM_SAFE_RANGE,
    KC_MAKE, // types the make command for this keyboard
#ifdef TWSCHUM_TAPPING_CTRL_PREFIX
    CTRL_A,
    CTRL_B,
    EN_CTRL_SHORTCUTS,
#endif
#ifdef RGBLIGHT_ENABLE
    TG_LAYER_RGB, // Toggle between standard RGB underglow, and RGB underglow to do layer indication
    TG_L0_RGB, // Toggle color on or off of layer0
#endif
    SALT_CMD, // macro
    LESS_PD, // macro
    CODE_PASTE, // macro
    KEYMAP_SAFE_RANGE, // range to start for the keymap
};
#define SALT_CMD_MACRO "sudo salt \\* cmd.run ''"SS_TAP(X_LEFT)
#define LESS_PD_MACRO "sudo less /pipedream/cache/"
// TODO mac vs linux
#define CODE_PASTE_MACRO SS_LSFT("\n")"```"SS_LSFT("\n")SS_LALT("v")SS_LSFT("\n")"```"


/* PP_NARG macro returns the number of arguments passed to it.
 * https://groups.google.com/forum/#!topic/comp.std.c/d-6Mj5Lko_s
 */
#define PP_NARG(...) PP_NARG_(__VA_ARGS__,PP_RSEQ_N())
#define PP_NARG_(...) PP_ARG_N(__VA_ARGS__)
#define PP_MAX_ARGS 64
#define PP_ARG_N( \
          _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, \
         _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
         _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
         _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
         _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
         _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
         _61,_62,_63,N,...) N
#define PP_RSEQ_N() 63,62,61,60,        \
         59,58,57,56,55,54,53,52,51,50, \
         49,48,47,46,45,44,43,42,41,40, \
         39,38,37,36,35,34,33,32,31,30, \
         29,28,27,26,25,24,23,22,21,20, \
         19,18,17,16,15,14,13,12,11,10, \
         9,8,7,6,5,4,3,2,1,0

#define send_keys(...) send_n_keys(PP_NARG(__VA_ARGS__), __VA_ARGS__)
static inline void send_n_keys(int n, ...) {
    uint8_t i = 0;
    uint16_t keycodes[PP_MAX_ARGS];
    va_list keys;
    va_start(keys, n);
    for (; i < n; ++i) {
        keycodes[i] = (uint16_t)va_arg(keys, int); // cast suppresses warning
        register_code(keycodes[i]);
    }
    for (; n > 0; --n) {
        unregister_code(keycodes[n-1]);
    }
    va_end(keys);
}
#define repeat_send_keys(n, ...) {for (int i=0; i < n; ++i) {send_keys(__VA_ARGS__);}}

/* State functions for nested c-a & c-b leader keystrokes */
struct Tapping_ctrl_key_t {
    bool down;
    int8_t count;
    const uint16_t keycode;
};
