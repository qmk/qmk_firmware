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

#include "quantum.h"
#include "333fred.h"

void layer_state_set_rgb(uint32_t state) {
  switch (biton32(state)) {
    case BASE:
      // purple
      rgblight_sethsv_noeeprom(210, 255, 20);
      break;
    case SYMB:
      // blue
      rgblight_sethsv_noeeprom(191, 255, 20);
      break;
    case VIM:
      // green
      rgblight_sethsv_noeeprom(85, 255, 20);
      break;
    case GAME:
      // red
      rgblight_sethsv_noeeprom(0, 255, 20);
      break;
  }
}

void keyboard_post_init_user(void) {
  rgblight_enable_noeeprom();
  layer_state_set_rgb(1); // Set layer 0 (bit 1) on
}
