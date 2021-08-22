#include QMK_KEYBOARD_H

#include <stdio.h>

// tap dance section start
enum tap_dance_codes {
  DANCE_0,
  I_QUOT,
  O_LSFT_QUOT,
  SLASH_RSHIFT,
  CMD_T_SFT,
  CMD_V_SHIFT,
  MINUS_UNDERSCORE,
  EQUAL_PLUS,
  A_CTL,
};
// tap dance section end

// basic key mappings
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_split_3x6_3(
  //,--------------------------------------.            ,--------------------------------------------|
      KC_NO,  KC_Q,  KC_W, KC_E, KC_R, KC_T,          KC_Y, KC_U, TD(I_QUOT),    TD(O_LSFT_QUOT),   KC_P,    KC_NO,
  //|--------+--------+--------+--------+---------|     |--------+--------+--------+--------+--------|
      KC_LGUI, TD(A_CTL), KC_S, KC_D, KC_F, KC_G,    KC_H, KC_J, KC_K,    KC_L,   KC_ENT,  KC_SCOLON,
  //|--------+--------+--------+--------+---------|     |--------+--------+--------+--------+--------|
      KC_LSFT, LSFT_T(KC_Z), KC_X, KC_C, KC_V, KC_B,    KC_N, KC_M, KC_COMM, KC_DOT, RSFT_T(KC_SLSH), TO(4),
  //|--------+--------+--------+--------+---------|     |--------+--------+--------+--------+--------|
                          MO(3),   KC_LSFT,  MO(1),     KC_SPC,   MO(2), TO(5)
                          //`--------------------------'  `----------------------'
  ),
  [1] = LAYOUT_split_3x6_3(
  //,--------------------------------------.    ,--------------------------------------------|
      KC_NO, KC_ESC, LGUI(KC_W), LGUI(LSFT(KC_P)), LGUI(KC_R), TD(CMD_T_SFT),             KC_CIRC, KC_AMPR, KC_LPRN, KC_RPRN, KC_PIPE, KC_NO,
  //|--------+--------+--------+--------+--|    |--------+--------+--------+--------+--------|
      LGUI(KC_TAB), LGUI(KC_A), KC_TAB, LGUI(KC_K), LGUI(KC_F), LGUI(KC_L),            KC_ASTR, LCTL(KC_H), TD(MINUS_UNDERSCORE), TD(EQUAL_PLUS), KC_COLN, LGUI(KC_ENTER),
  //|--------+--------+--------+--------+--|    |--------+--------+--------+--------+--------|
      LGUI(KC_GRAVE), LGUI(KC_Z), LGUI(KC_X), LCTL(KC_C), LGUI_T(KC_C), TD(CMD_V_SHIFT),    KC_BSPC, KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR, KC_NO,
  //|--------+--------+--------+--------+--|    |--------+--------+--------+--------+--------|
                  KC_NO, KC_NO, KC_TRNS, LGUI(KC_SPC), KC_NO, KC_NO
                  //`--------------------------'  `----------------------'
  ),
  [2] = LAYOUT_split_3x6_3(
  //,--------------------------------------.    ,--------------------------------------------|
       KC_NO, KC_1, KC_2, KC_3, KC_4, KC_5,     LGUI(KC_GRV), LGUI(KC_U), KC_UP, LGUI(KC_O), LCTL(LGUI(LSFT(KC_4))), KC_NO,
  //|--------+--------+--------+--------+--|    |--------+--------+--------+--------+--------|
       KC_NO, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC,  KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, LGUI_T(KC_Y), KC_NO,
  //|--------+--------+--------+--------+--|    |--------+--------+--------+--------+--------|
       KC_NO, LGUI_T(KC_1), KC_NO, KC_NO, KC_TILD, KC_GRV,    LALT(KC_BSPACE), LALT(KC_LEFT), LGUI_T(KC_I), LALT(KC_RGHT), KC_END, KC_NO,
  //|--------+--------+--------+--------+--|    |--------+--------+--------+--------+--------|
                        KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO
                  //`--------------------------'  `----------------------'
  ),
  [3] = LAYOUT_split_3x6_3(
  //,--------------------------------------.    ,--------------------------------------------|
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,     KC_PGUP, KC_7, KC_8, KC_9, KC_BSLS, KC_NO,
  //|--------+--------+--------+--------+--|    |--------+--------+--------+--------+--------|
      KC_NO, KC_NO, LGUI(KC_LBRC), KC_NO, LGUI(KC_RBRC), KC_NO,     KC_PGDN, KC_4, KC_5, KC_6, KC_NO, KC_NO,
  //|--------+--------+--------+--------+--|    |--------+--------+--------+--------+--------|
      KC_NO, KC_NO, LGUI(KC_MINS), KC_NO, LGUI(KC_PLUS), LGUI(KC_BSPC),     KC_NO, KC_1, KC_2, KC_3, KC_NO, KC_NO,
  //|--------+--------+--------+--------+--|    |--------+--------+--------+--------+--------|
                        KC_TRNS, KC_NO, KC_NO, KC_NO, KC_0, KC_NO
                  //`--------------------------'  `----------------------'
  ),
  [4] = LAYOUT_split_3x6_3(
  //,--------------------------------------.    ,--------------------------------------------|
      KC_NO, LGUI(KC_A), LGUI(KC_W), KC_BSPC, KC_TAB, KC_NO,     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
  //|--------+--------+--------+--------+--|    |--------+--------+--------+--------+--------|
      KC_NO, KC_LSFT, KC_LGUI, LGUI(KC_C), LALT(LGUI(KC_V)), LGUI(KC_V),     KC_NO, LGUI(KC_U), KC_UP, LGUI(KC_O), KC_NO, KC_NO,
  //|--------+--------+--------+--------+--|    |--------+--------+--------+--------+--------|
      KC_NO, LGUI(KC_Z), KC_X, KC_HASH, KC_ENT, LGUI(KC_BSPC),       KC_X, KC_LEFT, KC_DOWN, KC_RGHT, TO(0), KC_NO,
  //|--------+--------+--------+--------+--|    |--------+--------+--------+--------+--------|
                          KC_NO, KC_NO, KC_ESC, KC_SPC, KC_NO, KC_NO
                  //`--------------------------'  `----------------------'
  ),
  [5] = LAYOUT_split_3x6_3(
  //,--------------------------------------.    ,--------------------------------------------|
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,       KC_WH_D, KC_BTN1, KC_MS_U, KC_BTN2, KC_NO, KC_NO,
  //|--------+--------+--------+--------+--|    |--------+--------+--------+--------+--------|
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,       KC_WH_U, KC_MS_L, KC_MS_D, KC_MS_R, KC_NO, KC_NO,
  //|--------+--------+--------+--------+--|    |--------+--------+--------+--------+--------|
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,       KC_NO, KC_NO, KC_NO, KC_NO, TO(0), KC_NO,
  //|--------+--------+--------+--------+--|    |--------+--------+--------+--------+--------|
                          KC_NO, KC_NO, KC_NO, KC_NO, KC_ACL0, KC_NO
                  //`--------------------------'  `----------------------'
  )
};

// tap dance operations start
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

static tap dance_state[9];

uint8_t dance_step(qk_tap_dance_state_t *state);

uint8_t dance_step(qk_tap_dance_state_t *state) {
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


void on_dance_0(qk_tap_dance_state_t *state, void *user_data);
void dance_0_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_0_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_0(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_Z);
        tap_code16(KC_Z);
        tap_code16(KC_Z);
    }
    if(state->count > 3) {
        tap_code16(KC_Z);
    }
}

void dance_0_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state[0].step = dance_step(state);
    switch (dance_state[0].step) {
        case SINGLE_TAP: register_code16(KC_Z); break;
        case SINGLE_HOLD: register_code16(KC_LSHIFT); break;
        case DOUBLE_TAP: register_code16(KC_Z); register_code16(KC_Z); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_Z); register_code16(KC_Z);
    }
}

void dance_0_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[0].step) {
        case SINGLE_TAP: unregister_code16(KC_Z); break;
        case SINGLE_HOLD: unregister_code16(KC_LSHIFT); break;
        case DOUBLE_TAP: unregister_code16(KC_Z); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_Z); break;
    }
    dance_state[0].step = 0;
}
void on_dance_1(qk_tap_dance_state_t *state, void *user_data);
void dance_1_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_1_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_1(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_I);
        tap_code16(KC_I);
        tap_code16(KC_I);
    }
    if(state->count > 3) {
        tap_code16(KC_I);
    }
}

void dance_1_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state[1].step = dance_step(state);
    switch (dance_state[1].step) {
        case SINGLE_TAP: register_code16(KC_I); break;
        case SINGLE_HOLD: register_code16(KC_QUOTE); break;
        case DOUBLE_TAP: register_code16(KC_I); register_code16(KC_I); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_I); register_code16(KC_I);
    }
}

void dance_1_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[1].step) {
        case SINGLE_TAP: unregister_code16(KC_I); break;
        case SINGLE_HOLD: unregister_code16(KC_QUOTE); break;
        case DOUBLE_TAP: unregister_code16(KC_I); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_I); break;
    }
    dance_state[1].step = 0;
}
void on_dance_2(qk_tap_dance_state_t *state, void *user_data);
void dance_2_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_2_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_2(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_O);
        tap_code16(KC_O);
        tap_code16(KC_O);
    }
    if(state->count > 3) {
        tap_code16(KC_O);
    }
}

void dance_2_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state[2].step = dance_step(state);
    switch (dance_state[2].step) {
        case SINGLE_TAP: register_code16(KC_O); break;
        case SINGLE_HOLD: register_code16(LSFT(KC_QUOTE)); break;
        case DOUBLE_TAP: register_code16(KC_O); register_code16(KC_O); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_O); register_code16(KC_O);
    }
}

void dance_2_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[2].step) {
        case SINGLE_TAP: unregister_code16(KC_O); break;
        case SINGLE_HOLD: unregister_code16(LSFT(KC_QUOTE)); break;
        case DOUBLE_TAP: unregister_code16(KC_O); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_O); break;
    }
    dance_state[2].step = 0;
}
void on_dance_3(qk_tap_dance_state_t *state, void *user_data);
void dance_3_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_3_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_3(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_SLASH);
        tap_code16(KC_SLASH);
        tap_code16(KC_SLASH);
    }
    if(state->count > 3) {
        tap_code16(KC_SLASH);
    }
}

void dance_3_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state[3].step = dance_step(state);
    switch (dance_state[3].step) {
        case SINGLE_TAP: register_code16(KC_SLASH); break;
        case SINGLE_HOLD: register_code16(KC_RSHIFT); break;
        case DOUBLE_TAP: register_code16(KC_SLASH); register_code16(KC_SLASH); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_SLASH); register_code16(KC_SLASH);
    }
}

void dance_3_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[3].step) {
        case SINGLE_TAP: unregister_code16(KC_SLASH); break;
        case SINGLE_HOLD: unregister_code16(KC_RSHIFT); break;
        case DOUBLE_TAP: unregister_code16(KC_SLASH); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_SLASH); break;
    }
    dance_state[3].step = 0;
}
void on_dance_4(qk_tap_dance_state_t *state, void *user_data);
void dance_4_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_4_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_4(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(LGUI(KC_T));
        tap_code16(LGUI(KC_T));
        tap_code16(LGUI(KC_T));
    }
    if(state->count > 3) {
        tap_code16(LGUI(KC_T));
    }
}

void dance_4_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state[4].step = dance_step(state);
    switch (dance_state[4].step) {
        case SINGLE_TAP: register_code16(LGUI(KC_T)); break;
        case DOUBLE_TAP: register_code16(LGUI(LSFT(KC_T))); break;
        case DOUBLE_SINGLE_TAP: tap_code16(LGUI(KC_T)); register_code16(LGUI(KC_T));
    }
}

void dance_4_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[4].step) {
        case SINGLE_TAP: unregister_code16(LGUI(KC_T)); break;
        case DOUBLE_TAP: unregister_code16(LGUI(LSFT(KC_T))); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(LGUI(KC_T)); break;
    }
    dance_state[4].step = 0;
}
void on_dance_5(qk_tap_dance_state_t *state, void *user_data);
void dance_5_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_5_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_5(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(LGUI(KC_V));
        tap_code16(LGUI(KC_V));
        tap_code16(LGUI(KC_V));
    }
    if(state->count > 3) {
        tap_code16(LGUI(KC_V));
    }
}

void dance_5_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state[5].step = dance_step(state);
    switch (dance_state[5].step) {
        case SINGLE_TAP: register_code16(LGUI(KC_V)); break;
        case DOUBLE_TAP: register_code16(LGUI(LSFT(KC_V))); break;
        case DOUBLE_SINGLE_TAP: tap_code16(LGUI(KC_V)); register_code16(LGUI(KC_V));
    }
}

void dance_5_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[5].step) {
        case SINGLE_TAP: unregister_code16(LGUI(KC_V)); break;
        case DOUBLE_TAP: unregister_code16(LGUI(LSFT(KC_V))); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(LGUI(KC_V)); break;
    }
    dance_state[5].step = 0;
}
void on_dance_6(qk_tap_dance_state_t *state, void *user_data);
void dance_6_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_6_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_6(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_MINUS);
        tap_code16(KC_MINUS);
        tap_code16(KC_MINUS);
    }
    if(state->count > 3) {
        tap_code16(KC_MINUS);
    }
}

void dance_6_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state[6].step = dance_step(state);
    switch (dance_state[6].step) {
        case SINGLE_TAP: register_code16(KC_MINUS); break;
        case SINGLE_HOLD: register_code16(LSFT(KC_MINUS)); break;
        case DOUBLE_TAP: register_code16(KC_MINUS); register_code16(KC_MINUS); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_MINUS); register_code16(KC_MINUS);
    }
}

void dance_6_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[6].step) {
        case SINGLE_TAP: unregister_code16(KC_MINUS); break;
        case SINGLE_HOLD: unregister_code16(LSFT(KC_MINUS)); break;
        case DOUBLE_TAP: unregister_code16(KC_MINUS); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_MINUS); break;
    }
    dance_state[6].step = 0;
}
void on_dance_7(qk_tap_dance_state_t *state, void *user_data);
void dance_7_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_7_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_7(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_EQUAL);
        tap_code16(KC_EQUAL);
        tap_code16(KC_EQUAL);
    }
    if(state->count > 3) {
        tap_code16(KC_EQUAL);
    }
}

void dance_7_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state[7].step = dance_step(state);
    switch (dance_state[7].step) {
        case SINGLE_TAP: register_code16(KC_EQUAL); break;
        case SINGLE_HOLD: register_code16(LSFT(KC_EQUAL)); break;
        case DOUBLE_TAP: register_code16(KC_EQUAL); register_code16(KC_EQUAL); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_EQUAL); register_code16(KC_EQUAL);
    }
}

void dance_7_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[7].step) {
        case SINGLE_TAP: unregister_code16(KC_EQUAL); break;
        case SINGLE_HOLD: unregister_code16(LSFT(KC_EQUAL)); break;
        case DOUBLE_TAP: unregister_code16(KC_EQUAL); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_EQUAL); break;
    }
    dance_state[7].step = 0;
}

void on_dance_8(qk_tap_dance_state_t *state, void *user_data);
void dance_8_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_8_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_8(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_A);
        tap_code16(KC_A);
        tap_code16(KC_A);
    }
    if(state->count > 3) {
        tap_code16(KC_A);
    }
}

void dance_8_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state[1].step = dance_step(state);
    switch (dance_state[1].step) {
        case SINGLE_TAP: register_code16(KC_A); break;
        case SINGLE_HOLD: register_code16(KC_LCTRL); break;
        case DOUBLE_TAP: register_code16(KC_A); register_code16(KC_A); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_A); register_code16(KC_A);
    }
}

void dance_8_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[1].step) {
        case SINGLE_TAP: unregister_code16(KC_A); break;
        case SINGLE_HOLD: unregister_code16(KC_LCTRL); break;
        case DOUBLE_TAP: unregister_code16(KC_A); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_A); break;
    }
    dance_state[1].step = 0;
}


qk_tap_dance_action_t tap_dance_actions[] = {
        [DANCE_0] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_0, dance_0_finished, dance_0_reset),
        [I_QUOT] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_1, dance_1_finished, dance_1_reset),
        [O_LSFT_QUOT] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_2, dance_2_finished, dance_2_reset),
        [SLASH_RSHIFT] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_3, dance_3_finished, dance_3_reset),
        [CMD_T_SFT] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_4, dance_4_finished, dance_4_reset),
        [CMD_V_SHIFT] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_5, dance_5_finished, dance_5_reset),
        [MINUS_UNDERSCORE] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_6, dance_6_finished, dance_6_reset),
        [EQUAL_PLUS] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_7, dance_7_finished, dance_7_reset),
        [A_CTL] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_8, dance_8_finished, dance_8_reset),
};
// tap dance operations end

