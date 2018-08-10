#pragma once

#include "quantum.h"

#define BASE 0
#define CODE 1 // code layer
#define SYMB 2
#define MDIA 3 // media keys
#define VIM  4
#define GAME 5

// Tap dance config shared between my keyboards
enum tap_dance_declarations {
    TD_SYM_VIM = 0
};

void tap_dance_layer_finished(qk_tap_dance_state_t*, void*);
void tap_dance_layer_reset(qk_tap_dance_state_t*, void*);
void tap_dance_process_record(uint16_t);
