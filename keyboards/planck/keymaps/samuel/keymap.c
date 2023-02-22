#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// where the 'T_' communicates how the key does something different when tapped.
enum planck_keycodes {
//DVORAK = SAFE_RANGE,
KC_T_LALT = SAFE_RANGE,
KC_T_RALT,
KC_T_LGUI,
KC_T_RGUI,
KC_T_LCTL,
KC_T_RCTL,
KC_T_LSFT,
KC_T_RSFT,
KC_T_LRSE,
KC_T_RRSE,
KC_EZRGHT,
KC_EZLEFT,
KC_EZUP,
KC_EZDOWN,
KC_EZUNDO,
KC_EZCOPY,
KC_EZCUT,
KC_EZPSTE,
KC_EZSHFT,
KC_EZCTRL,
KC_EZGUI,
KC_EZALT,
KC_DVORAK,
KC_QWERTY,
KC_COM
};

enum planck_layers {
_DVORAK,
_QWERTY,
_RISE,
_COMMAND
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_DVORAK] = LAYOUT_planck_grid(
KC_T_LRSE, KC_QUOT, KC_COMM, KC_DOT, KC_P, KC_Y, KC_F, KC_G, KC_C, KC_R, KC_L, KC_T_RRSE,
KC_T_LSFT, KC_A, KC_O, KC_E, KC_U, KC_I, KC_D, KC_H, KC_T, KC_N, KC_S, KC_T_RSFT,
KC_T_LCTL, KC_SCLN, KC_Q, KC_J, KC_K, KC_X, KC_B, KC_M, KC_W, KC_V, KC_Z, KC_T_RCTL,
KC_T_LGUI, KC_T_LALT, KC_UP, KC_DOWN, KC_SPC, KC_EQL, KC_GRAVE, KC_SPC, KC_LEFT, KC_RIGHT, KC_T_RALT, KC_T_RGUI
),
[_QWERTY] = LAYOUT_planck_grid(
KC_T_LRSE, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_T_RRSE,
KC_T_LSFT, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_T_RSFT,
KC_T_LCTL, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_QUOT, KC_T_RCTL,
KC_T_LGUI, KC_T_LALT, KC_UP, KC_DOWN, KC_SPC, KC_EQL, KC_GRAVE, KC_SPC, KC_LEFT, KC_RIGHT, KC_T_RALT, KC_DVORAK
),
[_RISE] = LAYOUT_planck_grid(
KC_TRANSPARENT, KC_EZUNDO, KC_EZCOPY, KC_EZCUT, KC_EZPSTE, KC_INS, KC_ASTR, KC_7, KC_8, KC_9, KC_TRANSPARENT, KC_TRANSPARENT,
KC_EZSHFT, KC_ESC, KC_CAPS, KC_PGUP, KC_PGDN, KC_HOME, KC_AMPR, KC_4, KC_5, KC_6, KC_0, KC_EZSHFT,
KC_EZCTRL, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_1, KC_2, KC_3, KC_COM, KC_EZCTRL,
KC_EZGUI, KC_EZALT, KC_EZUP, KC_EZDOWN, KC_SPC, KC_PIPE, KC_BSLS, KC_END, KC_EZLEFT, KC_EZRGHT, KC_EZALT, KC_EZGUI
),
[_COMMAND] = LAYOUT_planck_grid(
KC_TRANSPARENT, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_TRANSPARENT,
KC_TRANSPARENT, KC_F11, KC_F12, KC_F13, KC_F14, KC_F15, KC_F16, KC_F17, KC_F18, KC_F19, KC_F20, KC_TRANSPARENT,
KC_TRANSPARENT, KC_F21, KC_F22, KC_F23, KC_F24, KC_QWERTY, KC_DVORAK, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
)
};

static uint16_t tap_timer = 0;
char last_mod = 10;

void mod_press(uint16_t tap_code, uint16_t hold_code, int id) {
    /* this first if body makes double modified keys impossible, but stops the */
    /* delay when modifying a tap key which would result in the tap key not */
    /* getting modified. */
    if (last_mod != id && last_mod != 10) {
        tap_code16(tap_code);
        last_mod = 10;
    } else {
        tap_timer = timer_read();
        last_mod = id;
        register_code(hold_code);
    }
}

void mod_lift(uint16_t tap_code, uint16_t hold_code, int id) {
    unregister_code(hold_code);
    if (last_mod == id && timer_elapsed(tap_timer) < TAPPING_TERM) {
        tap_code16(tap_code);
    }
    last_mod = 10;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {

case KC_DVORAK:
if (record->event.pressed) {
    set_single_persistent_default_layer(_DVORAK);
}
return true;
break;

case KC_QWERTY:
if (record->event.pressed) {
    set_single_persistent_default_layer(_QWERTY);
}
return true;
break;

case KC_COM:
if (record->event.pressed) {
    layer_on(_COMMAND);
    set_oneshot_layer(_COMMAND, ONESHOT_START);
    last_mod = 10;
} else {
    clear_oneshot_layer_state (ONESHOT_PRESSED);
}
return false;
break;

case KC_T_LALT:
	if (record->event.pressed) {
	   mod_press(KC_LPRN, KC_LALT, 0);
	} else {
	   mod_lift(KC_LPRN, KC_LALT, 0);
	}
	return false;
	break;
case KC_T_RALT:
	if (record->event.pressed) {
	   mod_press(KC_RPRN, KC_RALT, 1);
	} else {
	   mod_lift(KC_RPRN, KC_RALT, 1);
	}
	return false;
	break;
case KC_T_LGUI:
	if (record->event.pressed) {
	   mod_press(KC_SLASH, KC_LGUI, 2);
	} else {
	   mod_lift(KC_SLASH, KC_LGUI, 2);
	}
	return false;
	break;
case KC_T_RGUI:
	if (record->event.pressed) {
	   mod_press(KC_MINS, KC_RGUI, 3);
	} else {
	   mod_lift(KC_MINS, KC_RGUI, 3);
	}
	return false;
	break;
case KC_T_LCTL:
	if (record->event.pressed) {
	   mod_press(KC_LEFT_BRACKET, KC_LCTL, 4);
	} else {
	   mod_lift(KC_LEFT_BRACKET, KC_LCTL, 4);
	}
	return false;
	break;
case KC_T_RCTL:
	if (record->event.pressed) {
	   mod_press(KC_RIGHT_BRACKET, KC_RCTL, 5);
	} else {
	   mod_lift(KC_RIGHT_BRACKET, KC_RCTL, 5);
	}
	return false;
	break;
case KC_T_LSFT:
	if (record->event.pressed) {
	   mod_press(KC_TAB, KC_LSFT, 6);
	} else {
	   mod_lift(KC_TAB, KC_LSFT, 6);
	}
	return false;
	break;
case KC_T_RSFT:
	if (record->event.pressed) {
	   mod_press(KC_ENTER, KC_RSFT, 7);
	} else {
	   mod_lift(KC_ENTER, KC_RSFT, 7);
	}
	return false;
	break;

case KC_T_LRSE:
if (record->event.pressed) {
    tap_timer = timer_read();
    last_mod = 8;
    layer_on(_RISE);
} else {
    layer_off(_RISE);
    if (last_mod == 8 && timer_elapsed(tap_timer) < TAPPING_TERM) {
        tap_code16(KC_DELETE);
        last_mod = 10;
    }
}
return false;
break;
case KC_T_RRSE:
if (record->event.pressed) {
    tap_timer = timer_read();
    last_mod = 9;
    layer_on(_RISE);
} else {
    layer_off(_RISE);
    if (last_mod == 9 && timer_elapsed(tap_timer) < TAPPING_TERM) {
        tap_code16(KC_BACKSPACE);
        last_mod = 10;
    }
}
return false;
break;

case KC_EZSHFT:
if (record->event.pressed) {
    set_oneshot_mods(MOD_LSFT);
    last_mod = 10;
}
return false;
break;
case KC_EZCTRL:
if (record->event.pressed) {
    set_oneshot_mods(MOD_LCTL);
    last_mod = 10;
}
return false;
break;
case KC_EZALT:
if (record->event.pressed) {
    set_oneshot_mods(MOD_LALT);
    last_mod = 10;
}
return false;
break;
case KC_EZGUI:
if (record->event.pressed) {
    set_oneshot_mods(MOD_LGUI);
    last_mod = 10;
}
return false;
break;

case KC_EZRGHT:
if (record->event.pressed) {
    register_code(KC_LCTL);
    tap_code16(S(KC_RGHT));
    unregister_code(KC_LCTL);
    last_mod = 10;
}
return false;
break;
case KC_EZLEFT:
if (record->event.pressed) {
    register_code(KC_LCTL);
    tap_code16(S(KC_LEFT));
    unregister_code(KC_LCTL);
    last_mod = 10;
}
return false;
break;
case KC_EZDOWN:
if (record->event.pressed) {
    register_code(KC_LCTL);
    tap_code16(S(KC_DOWN));
    unregister_code(KC_LCTL);
    last_mod = 10;
}
return false;
break;
case KC_EZUP:
if (record->event.pressed) {
    register_code(KC_LCTL);
    tap_code16(S(KC_UP));
    unregister_code(KC_LCTL);
    last_mod = 10;
}
return false;
break;

case KC_EZUNDO:
if (record->event.pressed) {
    tap_code16(C(KC_Z));
    last_mod = 10;
}
return false;
break;
case KC_EZCOPY:
if (record->event.pressed) {
    tap_code16(C(KC_C));
    last_mod = 10;
}
return false;
break;
case KC_EZCUT:
if (record->event.pressed) {
    tap_code16(C(KC_X));
    last_mod = 10;
}
return false;
break;
case KC_EZPSTE:
if (record->event.pressed) {
    tap_code16(C(KC_V));
    last_mod = 10;
}
return false;
break;

}
last_mod = 10;
return true;
}
