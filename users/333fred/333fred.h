/*
  Copyright (c) 2020 Fred Silberberg

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/

#pragma once

#include "quantum.h"
#include "layout_macros.h"

#define BASE 0
#define CODEFLOW 1
#define SYMB 2
#define MDIA 3 // media keys
#define VIM 4
#define GAME 5
#define GAME_ARROW 6

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
