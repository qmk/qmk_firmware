#include <stdio.h>
#include QMK_KEYBOARD_H

enum layers {
    _QWERTY = 0,
    _RAISE,
    _LOWER,
    _ADJUST
};

#ifdef ENCODER_ENABLE

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

void encoder_alt_tab(bool clockwise) {
  if (!is_alt_tab_active) {
    is_alt_tab_active = true;
    register_code(KC_LGUI);
  }

	if (clockwise) {
		alt_tab_timer = timer_read();
		tap_code16(S(KC_TAB));
	} else {
		alt_tab_timer = timer_read();
		tap_code16(KC_TAB);
	}
}

void matrix_scan_user(void) {
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1250) {
      unregister_code(KC_LGUI);
      is_alt_tab_active = false;
    }
  }
}

// Mouse scroll
void encoder_mouse_scroll(bool clockwise) {
    // Volume control
    if (clockwise) {
        tap_code(KC_MS_WH_DOWN);
        tap_code(KC_MS_WH_DOWN);
    } else {
        tap_code(KC_MS_WH_UP);
        tap_code(KC_MS_WH_UP);
    }
}

// Volume control
void encoder_volume_control(bool clockwise) {
    if (clockwise) {
        tap_code(KC_VOLD);
    } else {
        tap_code(KC_VOLU);
    }
}

// left/right
void encoder_left_right(bool clockwise) {
    if (clockwise) {
        tap_code(KC_LEFT);
    } else {
        tap_code(KC_RGHT);
    }
}

// page up/down
void encoder_page_up_down(bool clockwise) {
    if (clockwise) {
        tap_code(KC_PGUP);
    } else {
        tap_code(KC_PGDN);
    }
}

// zoom in/out
void encoder_zoom_in_out(bool clockwise) {
    if (clockwise) {
        tap_code16(LCTL(KC_MINS));
    } else {
        tap_code16(LCTL(KC_PLUS));
    }
}

// mouse vertical
void encoder_mouse_vertical(bool clockwise) {
    if (clockwise) {
        tap_code(KC_MS_U);
        tap_code(KC_MS_U);
    } else {
        tap_code(KC_MS_D);
        tap_code(KC_MS_D);
    }
}

// mouse horizontal
void encoder_mouse_horizontal(bool clockwise) {
    if (clockwise) {
        tap_code(KC_MS_L);
        tap_code(KC_MS_L);
    } else {
        tap_code(KC_MS_R);
        tap_code(KC_MS_R);
    }
}



bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
				switch (get_highest_layer(layer_state)) {
						case _QWERTY:
								encoder_mouse_scroll(clockwise);
								break;
						case _LOWER:
								break;
						case _RAISE:
								encoder_volume_control(clockwise);
								break;
						case _ADJUST:
                encoder_mouse_vertical(clockwise);
								break;
						default:
								break;
				}
    }
    else if (index == 1) {
				switch (get_highest_layer(layer_state)) {
						case _QWERTY:
						    encoder_zoom_in_out(clockwise);
								break;
						case _LOWER:
                encoder_alt_tab(clockwise);
								break;
						case _RAISE:
								break;
						case _ADJUST:
                encoder_mouse_horizontal(clockwise);
								break;
						default:
								break;
				}
    }
    return false;
}

#endif

