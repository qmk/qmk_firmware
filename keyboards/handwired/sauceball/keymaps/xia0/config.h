// Copyright 2023 xia0 (@xia0)
// SPDX-License-Identifier: GPL-2.0-or-later

// modify movement rates as a percentage
// use this to reduce mouse sensitivity especially for drag-scrolling
#define SENSITIVITY_X 50
#define SENSITIVITY_Y 50
#define SENSITIVITY_H 3
#define SENSITIVITY_V 3

// since we are implementing our own drag scroll, we should disable default behaviour which will allow us to drag with middle mouse without scrolling.
// by default, this behaviour is set to middle mouse as i think the ps/2 functionality of qmk has trackpoint modules in mind.
// comment out the next line to use the default behaviour (middle mouse = drag scroll)
#define PS2_MOUSE_SCROLL_BTN_MASK 0
#define PS2_MOUSE_SCROLL_BTN_SEND 300

// define custom key to activate drag scroll when held
#define DRAG_SCROLL_KEY KC_BTN3

// scrolling direction
//   1 = natural, -1 = reverse
#define DRAG_SCROLL_DIRECTION -1
