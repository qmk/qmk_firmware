#pragma once

#include "quantum.h"

#define BASE 0
#define CODE 1 // code layer
#define CODEFLOW 2
#define SYMB 3
#define MDIA 4 // media keys
#define VIM  5
#define GAME 6
#define GAME_ARROW 7

// Tap dance config shared between my keyboards
enum tap_dance_declarations {
    TD_SYM_VIM = 0,
    TD_COPY_PASTE,
};

enum custom_keys {
    DLEFT = SAFE_RANGE,
    DRIGHT,
    PSCREEN_APP
};

void tap_dance_sym_vim_finished(qk_tap_dance_state_t*, void*);
void tap_dance_sym_vim_reset(qk_tap_dance_state_t*, void*);
void tap_dance_process_keycode(uint16_t);
bool try_handle_macro(uint16_t keycode, keyrecord_t *record);
