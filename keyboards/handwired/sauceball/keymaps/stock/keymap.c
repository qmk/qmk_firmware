// Copyright 2023 xia0 (@xia0)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "print.h"
#include "mousekey.h"

enum custom_keycodes {
  NO_SCROLL = QK_USER,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(KC_BTN1, KC_BTN3, NO_SCROLL, KC_BTN2)
};

int is_drag_scrolling = 0;              // should we be scrolling or just moving the cursor
uint16_t drag_scroll_key_timer;         // keep track of how long the drag key is held for

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  //uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);

  switch (keycode) {
    // Extra keycode for drag scroll key but don't scroll
    case NO_SCROLL:
      if (record->event.pressed) {
        register_code(DRAG_SCROLL_KEY);
      } else {
        unregister_code(DRAG_SCROLL_KEY);
      }
      break;

  }

#ifdef PS2_MOUSE_SCROLL_BTN_MASK
  if (PS2_MOUSE_SCROLL_BTN_MASK == 0 && keycode == DRAG_SCROLL_KEY) {
    // if scroll button is not held, send a tap of the key
    // duration of this is defined by PS2_MOUSE_SCROLL_BTN_SEND
    if (record->event.pressed == 1) {
      drag_scroll_key_timer = timer_read();
    }
    else if (timer_elapsed(drag_scroll_key_timer) < PS2_MOUSE_SCROLL_BTN_SEND) {  // key was released within ms defined by PS2_MOUSE_SCROLL_BTN_SEND (default 300)
      
      /*
        following code adapted from https://github.com/qmk/qmk_firmware/blob/master/keyboards/bpiphany/kitten_paw/keymaps/ickerwx/keymap.c
        required due to tap_code not working with PS2_MOUSE_ENABLE 
      */
      switch (DRAG_SCROLL_KEY) {
        case KC_BTN1:
        case KC_BTN2:
        case KC_BTN3:
        case KC_BTN4:
        case KC_BTN5:
        case KC_BTN6:
        case KC_BTN7:
        case KC_BTN8:
          mousekey_clear();
          mousekey_on(DRAG_SCROLL_KEY);
          mousekey_send();
          wait_ms(10);
          mousekey_off(DRAG_SCROLL_KEY);
          mousekey_send();
          break;
        default:
          tap_code(DRAG_SCROLL_KEY);
          break;
      }
      
    }

    is_drag_scrolling = record->event.pressed;
    return false;

  }
#endif

  return true;
}



int move_counters[4]; // array to keep count of "incomplete" moves for low sensitivity settings
const int SENSITIVITY_PERCENTAGES[] = { SENSITIVITY_X, SENSITIVITY_Y, SENSITIVITY_H, SENSITIVITY_V }; // load our sensitivities into array
const char AXIS_NAMES[5] = { 'X', 'Y', 'H', 'V', '\0' }; // for debugging

void ps2_mouse_moved_user(report_mouse_t *mouse_report) {

  // if drag-scrolling, replace the h and v values with x and y
  if (is_drag_scrolling == 1) {
    mouse_report->h = mouse_report->x;
    mouse_report->v = mouse_report->y * DRAG_SCROLL_DIRECTION;
    mouse_report->x = 0;
    mouse_report->y = 0;
  }

  /* mouse sensitivity fine tuning */
  // put mouse_report into an array so we can interate
  int8_t * reports[] = { &mouse_report->x, &mouse_report->y, &mouse_report->h, &mouse_report->v };

  int movement_rounded = 0; // this variable will determine how much to actually move the mouse after processing

  // iterate through all 4 axes (x, y, h and v)
  for (int i = 0; i < 4; i++) {

    if (reports[i] == 0 || SENSITIVITY_PERCENTAGES[i] == 100) continue;  // skip if not moving in this axis or no change required

    // Reset incomplete moves counter if movement has changed direction
    if (abs(move_counters[i] + *reports[i]) < abs(move_counters[i])) {
      move_counters[i] = *reports[i];
    }

    // update incomplete movement tally
    move_counters[i] += *reports[i];
    *reports[i] = 0;

    // check if enough movement has taken place to actually move the pointer for real
    if (abs(move_counters[i] * SENSITIVITY_PERCENTAGES[i]) >= 100) { // only do the movement if it's beyond the threshold
      movement_rounded = round(move_counters[i] * SENSITIVITY_PERCENTAGES[i] / 100); // round down the amount of actual movement intended
      move_counters[i] -= movement_rounded * 100 / SENSITIVITY_PERCENTAGES[i]; // subtract this amount of movement to how much we have "stored up"
      *reports[i] = movement_rounded; // actually do the movement
    }

    //xprintf("%c: %d, %d\n", AXIS_NAMES[i], move_counters[i], movement_rounded);

  }


}
