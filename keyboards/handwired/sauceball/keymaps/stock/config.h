// Copyright 2023 xia0 (@xia0)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Sensitivity fine-tuning
// values are percentage of full speed
#define SENSITIVITY_X 50
#define SENSITIVITY_Y 50
#define SENSITIVITY_H 3
#define SENSITIVITY_V 3

// Drag scroll settings
#define PS2_MOUSE_SCROLL_BTN_MASK 0   // disables default behaviour of drag scroll on mouse3 - comment out for default
#define PS2_MOUSE_SCROLL_BTN_SEND 300 // if no scrolling occurs within this many ms, do normal button behaviour
#define DRAG_SCROLL_KEY KC_BTN3       // define which key to activate drag scroll when held
#define DRAG_SCROLL_DIRECTION -1      // scroll direction 1 = natural, -1 = reverse
