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
    TD_SYM_VIM = 0
};

void tap_dance_layer_finished(qk_tap_dance_state_t*, void*);
void tap_dance_layer_reset(qk_tap_dance_state_t*, void*);
void tap_dance_process_record(uint16_t);
