#include "dz60_vim.h"

enum layer_names {
    _NORMAL,
    _INSERT,
    _VISUAL,
    _VIM,
    _FN
};

void keyboard_post_init_user(void) {
    rgblight_setrgb(212, 134, 0); // Normal mode
    // Customise these values to desired behaviour
    //debug_enable=true;
    //debug_matrix=true;
    //debug_keyboard=true;
    //debug_mouse=true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_mode(1);
    switch (get_highest_layer(state)) {
        case _NORMAL: // Normal mode
            rgblight_setrgb(212, 134, 0); // Normal mode
            break;
        case _INSERT: // Insert mode
            rgblight_setrgb(153, 182, 0); // Insert mode
            //rgblight_mode(2);
            break;
        case _VISUAL: // Visual mode
            rgblight_setrgb(234, 105, 98); // Visual mode
            break;
        case _FN: // Function mode
            rgblight_setrgb(RGB_BLUE); // Normal mode
            break;
        case _VIM: // Vim mode
            rgblight_setrgb(RGB_AZURE);
            break;
        default: // error mode
            rgblight_setrgb(RGB_RED);
            break;
    }
    return state;
}
