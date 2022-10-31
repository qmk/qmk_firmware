#include QMK_KEYBOARD_H

#include <stdio.h>
// tap dance section start
enum tap_dance_codes {
  I_QUOT,
  O_LSFT_QUOT,
  CMD_T_SFT,
  CMD_V_SHIFT,
  MINUS_UNDERSCORE,
  EQUAL_PLUS,
  A_CTL,
  SLACK_ADDRESS,
};
// tap dance section end

// basic key mappings
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // basic layer
  //  offer all letters and most frequent keys,
  // letter keys are organized in qwerty layout to avoid additional learning curve for other layouts,
  //  also considering mobile device still uses qwerty
  // Q and P is places to the sides of the keyboard to avoid pinky or ring finger to reach top corner keys
  //  so far Q and P is working fine most of time, occasionly hit enter when trying to hit P.
  // KC_LGUI and KC_LALT on top left to serve occasion use case of cmd click or option click
  // quotes ' and " is used often, hence using tap dance for now, they are working good so far.
  // KC_BSPC is used as secondary backspace, sometime it is more convenient when doing a lot of delete
  // KC_LCTRL is used often, as a vim user, many keys are using left ctrl, using pinky to hit ctrl works fine.
  // command, dot, splash are using as closer to the original standard keyboard layout, no issues so far.
  // TO(4) is needed to handle files management related layer.
  // MO(3) provides quick access to number layer
  // KC_LSFT is often used for cap letters, currently does have difficulties when hitting left section letters.
  // MO(1) provides command layer
  // MO(2) provides navigation layer
  // KC_RSHIFT is not often used
  [0] = LAYOUT_split_3x6_3(
    KC_LGUI,  KC_LALT, KC_W, KC_E,  KC_R,    KC_T,    KC_Y,   KC_U,  TD(I_QUOT), TD(O_LSFT_QUOT), KC_NO,    KC_BSPC,
    KC_Q,     KC_A,    KC_S, KC_D,  KC_F,    KC_G,    KC_H,   KC_J,  KC_K,       KC_L,            KC_ENT,   KC_P,
    KC_LCTRL, KC_Z,    KC_X, KC_C,  KC_V,    KC_B,    KC_N,   KC_M,  KC_COMM,    KC_DOT,          KC_SLASH, TO(4),
                             MO(3), KC_LSFT, MO(1),   KC_SPC, MO(2), KC_RSHIFT
  ),
  // command layer
  //  offer cmd based combination keys on the left and symbols on the right,
  //  goal is to reduce learning curve, make it feels like original qwerty keyboard
  // top left LGUI(KC_W) is used when primarily using mouse on right hand, provide easy way to cmd w to close tab.
  // LGUI(KC_S) provides cmd s, original cmd s is taken by tab, tab is more often used and needs a better place
  // LGUI(LSFT(KC_P)) is used to trigger 1Password
  // TD(CMD_T_SFT) is to provide one tap to open a new tab, two tab perform shift cmd t, opens last closed tab
  // LGUI(KC_BSPACE) is for delete file
  // LGUI(KC_TAB) is used for switch app in mac
  // KC_TAB is working good, once get used to it, this becomes a natrual location for tab, and easy to press.
  // LGUI(KC_F) is put at the d because more accesible f is left for more important ESC
  // ESC is important due to heavy vim usage and place f is easy enough to use
  // TD(SLACK_ADDRESS) is used for cmd k and cmd l, this is to save space, so cmd k opens search in slack and
  //   cmd l focus to address bar in a browser
  // LCTL(KC_H) is due to heavy tmux user, tmux start key is ctrl H, hence put in the most accessible j location
  // MINUS_UNDERSCORE provides - and _, EQUAL_PLUS provides = and +,
  // KC_BSPC provides backspace in normal cases, when two hands are on the keyboard
  // LGUI(KC_SPC) is for mac spotlight search
  // two KC_NO can be used later, left of LGUI(KC_Z) and right of LGUI(KC_SPC)
  [1] = LAYOUT_split_3x6_3(
    LGUI(KC_W),       KC_NO,      LGUI(KC_S), LGUI(LSFT(KC_P)), LGUI(KC_R), TD(CMD_T_SFT),        KC_CIRC,      KC_AMPR,    KC_LPRN,              KC_RPRN,        KC_NO,   LGUI(KC_BSPC),
    LGUI(KC_TAB),     LGUI(KC_A), KC_TAB,     LGUI(KC_F),       KC_ESC,     TD(SLACK_ADDRESS),    KC_ASTR,      LCTL(KC_H), TD(MINUS_UNDERSCORE), TD(EQUAL_PLUS), KC_COLN, KC_SCOLON,
    LGUI(LSFT(KC_4)), LGUI(KC_Z), LGUI(KC_X), LCTL(KC_C),       LGUI(KC_C), LGUI(KC_V),           KC_BSPC,      KC_LBRC,    KC_RBRC,              KC_LCBR,        KC_RCBR, KC_NO,
                                            KC_NO,            KC_NO,      KC_NO,                LGUI(KC_SPC), KC_NO,      KC_NO
  ),
  // navigation layer
  //   provides numbers, symbols on the left and navigation and other commands on the right
  // although there is dedicated number layer at layer 3, but for vim user, 2 to 5 lines command is often used,
  //   put 1 to 5 number in traditional ways help make it easier, this can be futher thought about later
  // KC_1 is put to the left of KC_EXLM instead of top, because top location is harder to press
  // LGUI(KC_GRV) is used to switch instances of same app
  // LGUI(KC_U) and LGUI(KC_O) are used to switch between mac workspace
  // LGUI(KC_W) provides close window when two hands are on keyboard
  // KC_HOME is to go to the head of a text
  // LGUI(KC_Y) Paste app trigger
  // LGUI(LSFT(KC_4)) screenshot
  // LCTL(KC_SPC) language input source switch
  // LGUI(KC_1) quickly switched to the first tab of browser
  // LALT(KC_BSPACE) delete a word
  // LALT(KC_LEFT) and LALT(KC_RGHT) go left and right faster
  // LGUI(KC_I) open workspace switcher in mac
  // KC_END go to the end of text
  [2] = LAYOUT_split_3x6_3(
     LCTL(LGUI(KC_Q)),        KC_NO,      KC_2,  KC_3,    KC_4,    KC_5,     LGUI(KC_GRV),    LGUI(KC_U),    KC_UP,      LGUI(KC_O),    KC_NO,      LGUI(KC_W),
     KC_1,         KC_EXLM,    KC_AT, KC_HASH, KC_DLR,  KC_PERC,  KC_HOME,         KC_LEFT,       KC_DOWN,    KC_RGHT,       LGUI(KC_Y), LGUI(LSFT(KC_4)),
     LCTL(KC_SPC), LGUI(KC_1), KC_NO, KC_NO,   KC_TILD, KC_GRV,   LALT(KC_BSPACE), LALT(KC_LEFT), LGUI(KC_I), LALT(KC_RGHT), KC_END,     KC_NO,
                                      KC_NO,   KC_NO,   KC_NO,    KC_NO,           KC_TRNS,       KC_NO
  ),
  // nums
  [3] = LAYOUT_split_3x6_3(
  //,--------------------------------------.    ,--------------------------------------------|
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,     KC_PGUP, KC_7, KC_8, KC_9, KC_NO, LGUI(KC_Q),
  //|--------+--------+--------+--------+--|    |--------+--------+--------+--------+--------|
      KC_NO, KC_NO, LGUI(KC_LBRC), KC_NO, LGUI(KC_RBRC), LGUI(KC_L),     KC_PGDN, KC_4, KC_5, KC_6, KC_PIPE, KC_BSLS,
  //|--------+--------+--------+--------+--|    |--------+--------+--------+--------+--------|
      KC_NO, KC_NO, LGUI(KC_MINS), KC_NO, LGUI(KC_PLUS), LGUI(KC_BSPC),     KC_NO, KC_1, KC_2, KC_3, TO(0), KC_NO,
  //|--------+--------+--------+--------+--|    |--------+--------+--------+--------+--------|
                        KC_TRNS, KC_NO, KC_NO, KC_NO, KC_0, KC_NO
                  //`--------------------------'  `----------------------'
  ),
  //left hand
  [4] = LAYOUT_split_3x6_3(
  //,--------------------------------------.    ,--------------------------------------------|
      KC_NO, LGUI(KC_A), LGUI(KC_W), KC_BSPC, KC_TAB, KC_NO,     LGUI(KC_UP), LGUI(KC_U), KC_UP, LGUI(KC_O), KC_NO, KC_BSPC,
  //|--------+--------+--------+--------+--|    |--------+--------+--------+--------+--------|
      LGUI(KC_A), KC_LSFT, KC_LGUI, LGUI(KC_C), LALT(LGUI(KC_V)), LGUI(KC_V),     KC_X, KC_LEFT, KC_DOWN, KC_RGHT, LGUI(KC_Z), KC_NO,
  //|--------+--------+--------+--------+--|    |--------+--------+--------+--------+--------|
      KC_NO, LGUI(KC_Z), KC_X, KC_HASH, KC_ENT, LGUI(KC_BSPC),       LGUI(KC_DOWN), LGUI(KC_C), LALT(LGUI(KC_V)), LGUI(KC_BSPC), KC_NO, KC_NO,
  //|--------+--------+--------+--------+--|    |--------+--------+--------+--------+--------|
                          TO(0), KC_NO, KC_SPC, KC_SPC, KC_NO, KC_NO
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

void on_dance_10(qk_tap_dance_state_t *state, void *user_data);
void dance_10_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_10_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_10(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(LGUI(KC_K));
        tap_code16(LGUI(KC_K));
        tap_code16(LGUI(KC_K));
    }
    if(state->count > 3) {
        tap_code16(LGUI(KC_K));
    }
}

void dance_10_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state[1].step = dance_step(state);
    switch (dance_state[1].step) {
        case SINGLE_TAP: register_code16(LGUI(KC_K)); break;
        case SINGLE_HOLD: register_code16(LGUI(KC_K)); break;
        case DOUBLE_TAP: register_code16(LGUI(KC_L)); break;
        case DOUBLE_SINGLE_TAP: tap_code16(LGUI(KC_K)); register_code16(LGUI(KC_K));
    }
}

void dance_10_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[1].step) {
        case SINGLE_TAP: unregister_code16(LGUI(KC_K)); break;
        case SINGLE_HOLD: unregister_code16(LGUI(KC_K)); break;
        case DOUBLE_TAP: unregister_code16(LGUI(KC_L)); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(LGUI(KC_K)); break;
    }
    dance_state[1].step = 0;
}


qk_tap_dance_action_t tap_dance_actions[] = {
        [I_QUOT] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_1, dance_1_finished, dance_1_reset),
        [O_LSFT_QUOT] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_2, dance_2_finished, dance_2_reset),
        [CMD_T_SFT] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_4, dance_4_finished, dance_4_reset),
        [CMD_V_SHIFT] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_5, dance_5_finished, dance_5_reset),
        [MINUS_UNDERSCORE] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_6, dance_6_finished, dance_6_reset),
        [EQUAL_PLUS] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_7, dance_7_finished, dance_7_reset),
        [A_CTL] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_8, dance_8_finished, dance_8_reset),
        [SLACK_ADDRESS] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_10, dance_10_finished, dance_10_reset),
};
// tap dance operations end

