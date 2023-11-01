// Copyright 2023 @Marek128b
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }
    if (host_keyboard_led_state().caps_lock) 
	{
        rgb_matrix_set_color(0, RGB_RED);
    }
	
	if (host_keyboard_led_state().num_lock) 
	{
        rgb_matrix_set_color(1, RGB_RED);
    }

	if (host_keyboard_led_state().scroll_lock) 
	{
        rgb_matrix_set_color(2, RGB_RED);
    }
	
	switch (get_highest_layer(layer_state))
	{
        case 1: 
            rgb_matrix_set_color(3, RGB_CYAN);
        break;
        case 2: 
            rgb_matrix_set_color(3, RGB_MAGENTA);
        break;
        case 3:
            rgb_matrix_set_color(3, RGB_YELLOW);
        break;
    } 
    return true;
}
