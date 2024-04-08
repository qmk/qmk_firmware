// Copyright 2024 moonwellprogrammer
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum tap_dance_codes {
  DANCE_1,
  DANCE_2,
  DANCE_3,
  DANCE_15,
  DANCE_32,
  DANCE_33,
  DANCE_54,
  DANCE_55,
  DANCE_56,
  DANCE_57,
  DANCE_58,
  DANCE_59,
  DANCE_60, 
  DANCE_63,
  BKSL_HME,
  PIPE_END,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_split_3x5_3(
      KC_Q,         KC_W,           KC_E,               KC_R,               KC_T,           KC_Y,           KC_U,                   KC_I,               KC_O,          KC_P,
      KC_A,         KC_S,           MT(MOD_LALT,KC_D),  MT(MOD_LGUI,KC_F),  KC_G,  	        KC_H,           MT(MOD_RGUI,KC_J),      MT(MOD_RALT,KC_K),  KC_L,          KC_SCLN,
      KC_Z,         KC_X,           KC_C,               KC_V,               KC_B,           KC_N,           KC_M,                   TD(DANCE_2),        TD(DANCE_1),   TD(DANCE_3),
	                                KC_BSPC,            TO(1),              OSM(MOD_LSFT),  OSM(MOD_RCTL),  MT(MOD_MEH,KC_SPACE),   KC_ENT
  ),

  [1] = LAYOUT_split_3x5_3(
    KC_ESCAPE,      KC_AT,          LSFT(KC_3),         LSFT(KC_4),             KC_PERC,        KC_CIRC,        KC_AMPR,            KC_ASTR,            KC_SCLN,        KC_BSPC,
    KC_TAB,         KC_EQL,         LALT(KC_RBRC),      LALT(LSFT(KC_RBRC)),    TD(DANCE_32),   TD(BKSL_HME),   LSFT(KC_LBRC),      LSFT(KC_RBRC),      TD(PIPE_END),   KC_ENT,
    KC_TILD,        TD(DANCE_33),   LALT(KC_LBRC),      LALT(LSFT(KC_LBRC)),    KC_DQUO,        KC_LBRC,        KC_LPRN,            KC_RPRN,            KC_RBRC,        TO(3),
		    					    KC_BSPC,            TO(2),                  OSM(MOD_LSFT),  KC_RALT,        TO(0),              KC_ENT
  ),

  [2] = LAYOUT_split_3x5_3(
    KC_ESCAPE,      KC_MEDIA_PLAY_PAUSE,    KC_MEDIA_PREV_TRACK,    KC_MEDIA_NEXT_TRACK,    LSFT(KC_MINS),      KC_MINS,    KC_7,   KC_8,   KC_9,   _______,
    KC_TAB,         _______,                KC_AUDIO_VOL_DOWN,      KC_AUDIO_VOL_UP,        LSFT(KC_EQL),       KC_EQL,     KC_4,   KC_5,   KC_6,   KC_ENTER,
    QK_RBT,         KC_KP_ASTERISK,         KC_BRIGHTNESS_DOWN,     KC_BRIGHTNESS_UP,       KC_KP_DOT,          KC_0,       KC_1,   KC_2,   KC_3,   _______,
	                                        KC_BSPC,                TO(1),                  KC_LGUI,            KC_RALT,    TO(0),  KC_ENT
  ),

  [3] = LAYOUT_split_3x5_3(
    TD(DANCE_54),   KC_MS_WH_LEFT,  KC_MS_UP,       KC_MS_WH_RIGHT, TD(DANCE_55),           LGUI(KC_LBRC),      LCTL(LSFT(KC_TAB)),     RCTL(KC_TAB),       LGUI(KC_RBRC),      _______, 
	TD(DANCE_56),   KC_MS_LEFT,     KC_MS_DOWN,     KC_MS_RIGHT,    MT(MOD_LGUI,KC_DEL),    TD(DANCE_60),       MT(MOD_RGUI,KC_DOWN),   MT(MOD_RALT,KC_UP), TD(DANCE_63),       KC_ENTER,     
    TD(DANCE_58),   KC_MS_BTN2,     KC_MS_WH_UP,    KC_MS_WH_DOWN,  _______,                KC_MS_BTN1,         KC_MS_ACCEL0,           KC_MS_ACCEL1,       KC_MS_ACCEL2,       XXXXXXX, 
                                    KC_BSPC,         TO(1),         _______,                KC_RALT,            TO(0),                  KC_ENT
  )
};


extern bool g_suspend_state;
#define GET_TAP_KC(dual_role_key) dual_role_key & 0xFF
uint16_t last_keycode = XXXXXXX;
uint8_t last_modifier = 0;

typedef struct {
    bool is_press_action;
    uint8_t step;
} tap;

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP,
    MORE_TAPS
};

static tap dance_state = {
    .is_press_action = true,
    .step = 0
};

//-------------------------------------------------------------------------------------------------

void on_dance_2(tap_dance_state_t *state, void *user_data);
uint8_t dance_2_dance_step(tap_dance_state_t *state);
void dance_2_finished(tap_dance_state_t *state, void *user_data);
void dance_2_reset(tap_dance_state_t *state, void *user_data);

void on_dance_2(tap_dance_state_t *state, void *user_data) {
	if(state->count == 3) {
		tap_code16(KC_COMM);
		tap_code16(KC_COMM);
		tap_code16(KC_COMM);
	}
	if(state->count > 3) {
		tap_code16(KC_COMM);
	}
}

uint8_t dance_2_dance_step(tap_dance_state_t *state) {
	if (state->count == 1) {
		if (state->interrupted || !state->pressed) return SINGLE_TAP;
		else return SINGLE_HOLD;
	} else if (state->count == 2) {
		if (state->interrupted) return DOUBLE_SINGLE_TAP;
		else if (state->pressed) return DOUBLE_HOLD;
		else return DOUBLE_TAP;
	}
	return MORE_TAPS;
}
void dance_2_finished(tap_dance_state_t *state, void *user_data) {
	dance_state.step = dance_2_dance_step(state);
	switch (dance_state.step) {
		case SINGLE_TAP: register_code16(KC_COMM); break;
		case SINGLE_HOLD: register_code16(KC_MINS); break;
		case DOUBLE_TAP: register_code16(KC_COMM); register_code16(KC_COMM); break;
		case DOUBLE_SINGLE_TAP: tap_code16(KC_COMM); register_code16(KC_COMM);
	}
}

void dance_2_reset(tap_dance_state_t *state, void *user_data) {
	wait_ms(10);
	switch (dance_state.step) {
		case SINGLE_TAP: unregister_code16(KC_COMM); break;
		case SINGLE_HOLD: unregister_code16(KC_MINS); break;
		case DOUBLE_TAP: unregister_code16(KC_COMM); break;
		case DOUBLE_SINGLE_TAP: unregister_code16(KC_MINS); break;
	}
	dance_state.step = 0;
}

//-------------------------------------------------------------------------------------------------

void on_dance_3(tap_dance_state_t *state, void *user_data);
uint8_t dance_3_dance_step(tap_dance_state_t *state);
void dance_3_finished(tap_dance_state_t *state, void *user_data);
void dance_3_reset(tap_dance_state_t *state, void *user_data);

void on_dance_3(tap_dance_state_t *state, void *user_data) {
	if(state->count == 3) {
		tap_code16(KC_SLASH);
		tap_code16(KC_SLASH);
		tap_code16(KC_SLASH);
	}
	if(state->count > 3) {
		tap_code16(KC_SLASH);
	}
}

uint8_t dance_3_dance_step(tap_dance_state_t *state) {
	if (state->count == 1) {
		if (state->interrupted || !state->pressed) return SINGLE_TAP;
		else return SINGLE_HOLD;
	} else if (state->count == 2) {
		if (state->interrupted) return DOUBLE_SINGLE_TAP;
		else if (state->pressed) return DOUBLE_HOLD;
		else return DOUBLE_TAP;
	}
	return MORE_TAPS;
}
void dance_3_finished(tap_dance_state_t *state, void *user_data) {
	dance_state.step = dance_3_dance_step(state);
	switch (dance_state.step) {
		case SINGLE_TAP: register_code16(KC_SLASH); break;
		case SINGLE_HOLD: register_code16(S(KC_MINS)); break;
		case DOUBLE_TAP: register_code16(KC_SLASH); register_code16(KC_SLASH); break;
		case DOUBLE_SINGLE_TAP: tap_code16(KC_SLASH); register_code16(KC_SLASH);
	}
}

void dance_3_reset(tap_dance_state_t *state, void *user_data) {
	wait_ms(10);
	switch (dance_state.step) {
		case SINGLE_TAP: unregister_code16(KC_SLASH); break;
		case SINGLE_HOLD: unregister_code16(S(KC_MINS)); break;
		case DOUBLE_TAP: unregister_code16(KC_SLASH); break;
		case DOUBLE_SINGLE_TAP: unregister_code16(KC_SLASH); break;
	}
	dance_state.step = 0;
}

//-------------------------------------------------------------------------------------------------

void on_dance_1(tap_dance_state_t *state, void *user_data);
uint8_t dance_1_dance_step(tap_dance_state_t *state);
void dance_1_finished(tap_dance_state_t *state, void *user_data);
void dance_1_reset(tap_dance_state_t *state, void *user_data);

void on_dance_1(tap_dance_state_t *state, void *user_data) {
	if(state->count == 3) {
		tap_code16(KC_DOT);
		tap_code16(KC_DOT);
		tap_code16(KC_DOT);
	}
	if(state->count > 3) {
		tap_code16(KC_DOT);
	}
}

uint8_t dance_1_dance_step(tap_dance_state_t *state) {
	if (state->count == 1) {
		if (state->interrupted || !state->pressed) return SINGLE_TAP;
		else return SINGLE_HOLD;
	} else if (state->count == 2) {
		if (state->interrupted) return DOUBLE_SINGLE_TAP;
		else if (state->pressed) return DOUBLE_HOLD;
		else return DOUBLE_TAP;
	}
	return MORE_TAPS;
}
void dance_1_finished(tap_dance_state_t *state, void *user_data) {
	dance_state.step = dance_1_dance_step(state);
	switch (dance_state.step) {
		case SINGLE_TAP: register_code16(KC_DOT); break;
		case SINGLE_HOLD: register_code16(KC_EXLM); break;
		case DOUBLE_TAP: register_code16(KC_DOT); register_code16(KC_DOT); break;
		case DOUBLE_SINGLE_TAP: tap_code16(KC_DOT); register_code16(KC_DOT);
	}
}

void dance_1_reset(tap_dance_state_t *state, void *user_data) {
	wait_ms(10);
	switch (dance_state.step) {
		case SINGLE_TAP: unregister_code16(KC_DOT); break;
		case SINGLE_HOLD: unregister_code16(KC_EXLM); break;
		case DOUBLE_TAP: unregister_code16(KC_DOT); break;
		case DOUBLE_SINGLE_TAP: unregister_code16(KC_DOT); break;
	}
	dance_state.step = 0;
}

//-------------------------------------------------------------------------------------------------

void on_dance_15(tap_dance_state_t *state, void *user_data);
uint8_t dance_15_dance_step(tap_dance_state_t *state);
void dance_15_finished(tap_dance_state_t *state, void *user_data);
void dance_15_reset(tap_dance_state_t *state, void *user_data);

void on_dance_15(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_SPACE);
        tap_code16(KC_SPACE);
        tap_code16(KC_SPACE);
    }
    if(state->count > 3) {
        tap_code16(KC_SPACE);
    }
}

uint8_t dance_15_dance_step(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}
void dance_15_finished(tap_dance_state_t *state, void *user_data) {
    dance_state.step = dance_15_dance_step(state);
    switch (dance_state.step) {
        case SINGLE_TAP: register_code16(KC_SPACE); break;
        case SINGLE_HOLD: register_code16(KC_UNDS); break;
        case DOUBLE_TAP: register_code16(KC_SPACE); register_code16(KC_SPACE); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_SPACE); register_code16(KC_SPACE);
    }
}

void dance_15_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state.step) {
        case SINGLE_TAP: unregister_code16(KC_SPACE); break;
        case SINGLE_HOLD: unregister_code16(KC_UNDS); break;
        case DOUBLE_TAP: unregister_code16(KC_SPACE); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_SPACE); break;
    }
    dance_state.step = 0;
}

//-------------------------------------------------------------------------------------------------

void on_dance_32(tap_dance_state_t *state, void *user_data);
uint8_t dance_32_dance_step(tap_dance_state_t *state);
void dance_32_finished(tap_dance_state_t *state, void *user_data);
void dance_32_reset(tap_dance_state_t *state, void *user_data);

void on_dance_32(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_QUOTE);
        tap_code16(KC_QUOTE);
        tap_code16(KC_QUOTE);
    }
    if(state->count > 3) {
        tap_code16(KC_QUOTE);
    }
}

uint8_t dance_32_dance_step(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}
void dance_32_finished(tap_dance_state_t *state, void *user_data) {
    dance_state.step = dance_32_dance_step(state);
    switch (dance_state.step) {
        case SINGLE_TAP: register_code16(KC_QUOTE); break;
        case SINGLE_HOLD: register_code16(LGUI(KC_QUOTE)); break;
        case DOUBLE_TAP: register_code16(KC_GRAVE); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_QUOTE); register_code16(KC_QUOTE);
    }
}

void dance_32_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state.step) {
        case SINGLE_TAP: unregister_code16(KC_QUOTE); break;
        case SINGLE_HOLD: unregister_code16(LGUI(KC_QUOTE)); break;
        case DOUBLE_TAP: unregister_code16(KC_GRAVE); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_QUOTE); break;
    }
    dance_state.step = 0;
}

//-------------------------------------------------------------------------------------------------

void on_dance_33(tap_dance_state_t *state, void *user_data);
uint8_t dance_33_dance_step(tap_dance_state_t *state);
void dance_33_finished(tap_dance_state_t *state, void *user_data);
void dance_33_reset(tap_dance_state_t *state, void *user_data);

void on_dance_33(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(LALT(KC_3));
        tap_code16(LALT(KC_3));
        tap_code16(LALT(KC_3));
    }
    if(state->count > 3) {
        tap_code16(LALT(KC_3));
    }
}

uint8_t dance_33_dance_step(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}
void dance_33_finished(tap_dance_state_t *state, void *user_data) {
    dance_state.step = dance_33_dance_step(state);
    switch (dance_state.step) {
        case SINGLE_TAP: register_code16(LALT(KC_3)); break;
        case SINGLE_HOLD: register_code16(LALT(LSFT(KC_2))); break;
        case DOUBLE_TAP: register_code16(LALT(KC_3)); register_code16(LALT(KC_3)); break;
        case DOUBLE_SINGLE_TAP: tap_code16(LALT(KC_3)); register_code16(LALT(KC_3));
    }
}

void dance_33_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state.step) {
        case SINGLE_TAP: unregister_code16(LALT(KC_3)); break;
        case SINGLE_HOLD: unregister_code16(LALT(LSFT(KC_2))); break;
        case DOUBLE_TAP: unregister_code16(LALT(KC_3)); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(LALT(KC_3)); break;
    }
    dance_state.step = 0;
}

//-------------------------------------------------------------------------------------------------

void on_dance_54(tap_dance_state_t *state, void *user_data);
uint8_t dance_54_dance_step(tap_dance_state_t *state);
void dance_54_finished(tap_dance_state_t *state, void *user_data);
void dance_54_reset(tap_dance_state_t *state, void *user_data);

void on_dance_54(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_ESCAPE);
        tap_code16(KC_ESCAPE);
        tap_code16(KC_ESCAPE);
    }
    if(state->count > 3) {
        tap_code16(KC_ESCAPE);
    }
}

uint8_t dance_54_dance_step(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}
void dance_54_finished(tap_dance_state_t *state, void *user_data) {
    dance_state.step = dance_54_dance_step(state);
    switch (dance_state.step) {
        case SINGLE_TAP: register_code16(KC_ESCAPE); break;
        case SINGLE_HOLD: register_code16(LALT(LGUI(KC_ESCAPE))); break;
        case DOUBLE_TAP: register_code16(KC_ESCAPE); register_code16(KC_ESCAPE); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_ESCAPE); register_code16(KC_ESCAPE);
    }
}

void dance_54_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state.step) {
        case SINGLE_TAP: unregister_code16(KC_ESCAPE); break;
        case SINGLE_HOLD: unregister_code16(LALT(LGUI(KC_ESCAPE))); break;
        case DOUBLE_TAP: unregister_code16(KC_ESCAPE); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_ESCAPE); break;
    }
    dance_state.step = 0;
}

//-------------------------------------------------------------------------------------------------

void on_dance_55(tap_dance_state_t *state, void *user_data);
uint8_t dance_55_dance_step(tap_dance_state_t *state);
void dance_55_finished(tap_dance_state_t *state, void *user_data);
void dance_55_reset(tap_dance_state_t *state, void *user_data);

void on_dance_55(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_Q);
        tap_code16(KC_Q);
        tap_code16(KC_Q);
    }
    if(state->count > 3) {
        tap_code16(KC_Q);
    }
}

uint8_t dance_55_dance_step(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}
void dance_55_finished(tap_dance_state_t *state, void *user_data) {
    dance_state.step = dance_55_dance_step(state);
    switch (dance_state.step) {
        case SINGLE_TAP: register_code16(KC_Q); break;
        case SINGLE_HOLD: register_code16(KC_H); break;
        case DOUBLE_TAP: register_code16(KC_Q); register_code16(KC_Q); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_Q); register_code16(KC_Q);
    }
}

void dance_55_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state.step) {
        case SINGLE_TAP: unregister_code16(KC_Q); break;
        case SINGLE_HOLD: unregister_code16(KC_H); break;
        case DOUBLE_TAP: unregister_code16(KC_Q); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_Q); break;
    }
    dance_state.step = 0;
}

//-------------------------------------------------------------------------------------------------

void on_dance_56(tap_dance_state_t *state, void *user_data);
uint8_t dance_56_dance_step(tap_dance_state_t *state);
void dance_56_finished(tap_dance_state_t *state, void *user_data);
void dance_56_reset(tap_dance_state_t *state, void *user_data);

void on_dance_56(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_TAB);
        tap_code16(KC_TAB);
        tap_code16(KC_TAB);
    }
    if(state->count > 3) {
        tap_code16(KC_TAB);
    }
}

uint8_t dance_56_dance_step(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}
void dance_56_finished(tap_dance_state_t *state, void *user_data) {
    dance_state.step = dance_56_dance_step(state);
    switch (dance_state.step) {
        case SINGLE_TAP: register_code16(KC_TAB); break;
        case SINGLE_HOLD: register_code16(LGUI(KC_TAB)); break;
        case DOUBLE_TAP: register_code16(KC_TAB); register_code16(KC_TAB); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_TAB); register_code16(KC_TAB);
    }
}

void dance_56_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state.step) {
        case SINGLE_TAP: unregister_code16(KC_TAB); break;
        case SINGLE_HOLD: unregister_code16(LGUI(KC_TAB)); break;
        case DOUBLE_TAP: unregister_code16(KC_TAB); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_TAB); break;
    }
    dance_state.step = 0;
}

//-------------------------------------------------------------------------------------------------

void on_dance_57(tap_dance_state_t *state, void *user_data);
uint8_t dance_57_dance_step(tap_dance_state_t *state);
void dance_57_finished(tap_dance_state_t *state, void *user_data);
void dance_57_reset(tap_dance_state_t *state, void *user_data);

void on_dance_57(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_DELETE);
        tap_code16(KC_DELETE);
        tap_code16(KC_DELETE);
    }
    if(state->count > 3) {
        tap_code16(KC_DELETE);
    }
}

uint8_t dance_57_dance_step(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}
void dance_57_finished(tap_dance_state_t *state, void *user_data) {
    dance_state.step = dance_57_dance_step(state);
    switch (dance_state.step) {
        case SINGLE_TAP: register_code16(KC_DELETE); break;
        case SINGLE_HOLD: register_code16(LCTL(KC_K)); break;
        case DOUBLE_TAP: register_code16(KC_DELETE); register_code16(KC_DELETE); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_DELETE); register_code16(KC_DELETE);
    }
}

void dance_57_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state.step) {
        case SINGLE_TAP: unregister_code16(KC_DELETE); break;
        case SINGLE_HOLD: unregister_code16(LCTL(KC_K)); break;
        case DOUBLE_TAP: unregister_code16(KC_DELETE); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_DELETE); break;
    }
    dance_state.step = 0;
}

//-------------------------------------------------------------------------------------------------

void on_dance_58(tap_dance_state_t *state, void *user_data);
uint8_t dance_58_dance_step(tap_dance_state_t *state);
void dance_58_finished(tap_dance_state_t *state, void *user_data);
void dance_58_reset(tap_dance_state_t *state, void *user_data);

void on_dance_58(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_GRAVE);
        tap_code16(KC_GRAVE);
        tap_code16(KC_GRAVE);
    }
    if(state->count > 3) {
        tap_code16(KC_GRAVE);
    }
}

uint8_t dance_58_dance_step(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}
void dance_58_finished(tap_dance_state_t *state, void *user_data) {
    dance_state.step = dance_58_dance_step(state);
    switch (dance_state.step) {
        case SINGLE_TAP: register_code16(KC_GRAVE); break;
        case SINGLE_HOLD: register_code16(LGUI(KC_GRAVE)); break;
        case DOUBLE_TAP: register_code16(KC_GRAVE); register_code16(KC_GRAVE); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_GRAVE); register_code16(KC_GRAVE);
    }
}

void dance_58_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state.step) {
        case SINGLE_TAP: unregister_code16(KC_GRAVE); break;
        case SINGLE_HOLD: unregister_code16(LGUI(KC_GRAVE)); break;
        case DOUBLE_TAP: unregister_code16(KC_GRAVE); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_GRAVE); break;
    }
    dance_state.step = 0;
}

//-------------------------------------------------------------------------------------------------

void on_dance_59(tap_dance_state_t *state, void *user_data);
uint8_t dance_59_dance_step(tap_dance_state_t *state);
void dance_59_finished(tap_dance_state_t *state, void *user_data);
void dance_59_reset(tap_dance_state_t *state, void *user_data);

void on_dance_59(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_SPACE);
        tap_code16(KC_SPACE);
        tap_code16(KC_SPACE);
    }
    if(state->count > 3) {
        tap_code16(KC_SPACE);
    }
}

uint8_t dance_59_dance_step(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}
void dance_59_finished(tap_dance_state_t *state, void *user_data) {
    dance_state.step = dance_59_dance_step(state);
    switch (dance_state.step) {
        case SINGLE_TAP: register_code16(KC_SPACE); break;
        case SINGLE_HOLD: register_code16(LGUI(KC_O)); break;
        case DOUBLE_TAP: register_code16(KC_SPACE); register_code16(KC_SPACE); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_SPACE); register_code16(KC_SPACE);
    }
}

void dance_59_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state.step) {
        case SINGLE_TAP: unregister_code16(KC_SPACE); break;
        case SINGLE_HOLD: unregister_code16(LGUI(KC_O)); break;
        case DOUBLE_TAP: unregister_code16(KC_SPACE); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_SPACE); break;
    }
    dance_state.step = 0;
}

//-------------------------------------------------------------------------------------------------

void on_dance_60(tap_dance_state_t *state, void *user_data);
uint8_t dance_60_dance_step(tap_dance_state_t *state);
void dance_60_finished(tap_dance_state_t *state, void *user_data);
void dance_60_reset(tap_dance_state_t *state, void *user_data);

void on_dance_60(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_LEFT);
        tap_code16(KC_LEFT);
        tap_code16(KC_LEFT);
    }
    if(state->count > 3) {
        tap_code16(KC_LEFT);
    }
}

uint8_t dance_60_dance_step(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}
void dance_60_finished(tap_dance_state_t *state, void *user_data) {
    dance_state.step = dance_60_dance_step(state);
    switch (dance_state.step) {
        case SINGLE_TAP: register_code16(KC_LEFT); break;
        case SINGLE_HOLD: register_code16(LALT(KC_LEFT)); break;
        case DOUBLE_TAP: register_code16(KC_LEFT); register_code16(KC_LEFT); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_LEFT); register_code16(KC_LEFT);
    }
}

void dance_60_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state.step) {
        case SINGLE_TAP: unregister_code16(KC_LEFT); break;
        case SINGLE_HOLD: unregister_code16(LGUI(KC_LEFT)); break;
        case DOUBLE_TAP: unregister_code16(KC_LEFT); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_LEFT); break;
    }
    dance_state.step = 0;
}

//-------------------------------------------------------------------------------------------------

void on_dance_63(tap_dance_state_t *state, void *user_data);
uint8_t dance_63_dance_step(tap_dance_state_t *state);
void dance_63_finished(tap_dance_state_t *state, void *user_data);
void dance_63_reset(tap_dance_state_t *state, void *user_data);

void on_dance_63(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_RIGHT);
        tap_code16(KC_RIGHT);
        tap_code16(KC_RIGHT);
    }
    if(state->count > 3) {
        tap_code16(KC_RIGHT);
    }
}

uint8_t dance_63_dance_step(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}
void dance_63_finished(tap_dance_state_t *state, void *user_data) {
    dance_state.step = dance_63_dance_step(state);
    switch (dance_state.step) {
        case SINGLE_TAP: register_code16(KC_RIGHT); break;
        case SINGLE_HOLD: register_code16(LGUI(KC_RIGHT)); break;
        case DOUBLE_TAP: register_code16(KC_RIGHT); register_code16(KC_RIGHT); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_RIGHT); register_code16(KC_RIGHT);
    }
}

void dance_63_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state.step) {
        case SINGLE_TAP: unregister_code16(KC_RIGHT); break;
        case SINGLE_HOLD: unregister_code16(LALT(KC_RIGHT)); break;
        case DOUBLE_TAP: unregister_code16(KC_RIGHT); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_RIGHT); break;
    }
    dance_state.step = 0;
}

//-------------------------------------------------------------------------------------------------

void on_bksl_hme(tap_dance_state_t *state, void *user_data);
uint8_t bksl_hme_dance_step(tap_dance_state_t *state);
void bksl_hme_finished(tap_dance_state_t *state, void *user_data);
void bksl_hme_reset(tap_dance_state_t *state, void *user_data);

void on_bksl_hme(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_BSLS);
        tap_code16(KC_BSLS);
        tap_code16(KC_BSLS);
    }
    if(state->count > 3) {
        tap_code16(KC_BSLS);
    }
}

uint8_t bksl_hme_dance_step(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}
void bksl_hme_finished(tap_dance_state_t *state, void *user_data) {
    dance_state.step = bksl_hme_dance_step(state);
    switch (dance_state.step) {
        case SINGLE_TAP: register_code16(KC_BSLS); break;
        case SINGLE_HOLD: register_code16(KC_HOME); break;
        case DOUBLE_TAP: register_code16(KC_BSLS); register_code16(KC_BSLS); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_BSLS); register_code16(KC_BSLS);
    }
}

void bksl_hme_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state.step) {
        case SINGLE_TAP: unregister_code16(KC_BSLS); break;
        case SINGLE_HOLD: unregister_code16(KC_HOME); break;
        case DOUBLE_TAP: unregister_code16(KC_BSLS); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_BSLS); break;
    }
    dance_state.step = 0;
}

//-------------------------------------------------------------------------------------------------

void on_pipe_end(tap_dance_state_t *state, void *user_data);
uint8_t pipe_end_dance_step(tap_dance_state_t *state);
void pipe_end_finished(tap_dance_state_t *state, void *user_data);
void pipe_end_reset(tap_dance_state_t *state, void *user_data);

void on_pipe_end(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_PIPE);
        tap_code16(KC_PIPE);
        tap_code16(KC_PIPE);
    }
    if(state->count > 3) {
        tap_code16(KC_PIPE);
    }
}

uint8_t pipe_end_dance_step(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}
void pipe_end_finished(tap_dance_state_t *state, void *user_data) {
    dance_state.step = pipe_end_dance_step(state);
    switch (dance_state.step) {
        case SINGLE_TAP: register_code16(KC_PIPE); break;
        case SINGLE_HOLD: register_code16(KC_END); break;
        case DOUBLE_TAP: register_code16(KC_PIPE); register_code16(KC_PIPE); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_PIPE); register_code16(KC_PIPE);
    }
}

void pipe_end_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state.step) {
        case SINGLE_TAP: unregister_code16(KC_PIPE); break;
        case SINGLE_HOLD: unregister_code16(KC_END); break;
        case DOUBLE_TAP: unregister_code16(KC_PIPE); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_PIPE); break;
    }
    dance_state.step = 0;
}

//-------------------------------------------------------------------------------------------------

tap_dance_action_t tap_dance_actions[] = {
        [DANCE_1] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_1, dance_1_finished, dance_1_reset),
        [DANCE_2] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_2, dance_2_finished, dance_2_reset),
        [DANCE_3] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_3, dance_3_finished, dance_3_reset),
        [DANCE_15] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_15, dance_15_finished, dance_15_reset),       
        [DANCE_32] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_32, dance_32_finished, dance_32_reset),
        [DANCE_33] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_33, dance_33_finished, dance_33_reset),
        [DANCE_54] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_54, dance_54_finished, dance_54_reset),
        [DANCE_55] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_55, dance_55_finished, dance_55_reset),
        [DANCE_56] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_56, dance_56_finished, dance_56_reset),
        [DANCE_57] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_57, dance_57_finished, dance_57_reset),
        [DANCE_58] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_58, dance_58_finished, dance_58_reset),
        [DANCE_59] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_59, dance_59_finished, dance_59_reset),
        [DANCE_60] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_60, dance_60_finished, dance_60_reset),
        [DANCE_63] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_63, dance_63_finished, dance_63_reset),
        [BKSL_HME] = ACTION_TAP_DANCE_FN_ADVANCED(on_bksl_hme, bksl_hme_finished, bksl_hme_reset),
        [PIPE_END] = ACTION_TAP_DANCE_FN_ADVANCED(on_pipe_end, pipe_end_finished, pipe_end_reset),
};
