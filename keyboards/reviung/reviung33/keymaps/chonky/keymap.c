k#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
   BASE = 0,
   SYM,
   MACRO,
   NUM
};

enum custom_keycodes {
    DESK1 = LGUI(LCTL(KC_LEFT)),
    DESK2 = LGUI(LCTL(KC_RIGHT)),
    EVKEY = C(A(KC_A)), // EVKey
    //home row mods
    LGUI = LGUI_T(KC_A),
    LALT = LALT_T(KC_S),
    LCTL = LCTL_T(KC_D),
    LSFT = LSFT_T(KC_F),
    RSFT = RSFT_T(KC_J),
    RCTL = RCTL_T(KC_K),
    RALT = RALT_T(KC_L),
    RGUI = RGUI_T(KC_SCLN),
    // Layer-tap thumbs
    SYMTAB = LT(SYM,KC_TAB),
    MCESC  =  LT(MACRO,KC_ESC),
    NUMSPC = LT(NUM,KC_SPC),
    //Macro
    CHROME,
    TELEGR,
    DISC,
    TIMER
};
// Combo
enum combos {
  COMB_BKSPC,
  COMB_ENT,
  COMB_DEL
};
// Tap dance
enum tap_dance {
    TDBR1,
    TDBR2,
    TDBR3,
    DOTDOT,
    COMCOM
};

#define BR1  TD(TDBR1)
#define BR2  TD(TDBR2)
#define BR3  TD(TDBR3)
#define LINE TD(DOTDOT)
#define WORD  TD(COMCOM)

// Tap Dance
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;
typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

td_state_t cur_dance(qk_tap_dance_state_t *state);

// For the x tap dance. Put it here so it can be used in any keymap
void x_finished(qk_tap_dance_state_t *state, void *user_data);
void x_reset(qk_tap_dance_state_t *state, void *user_data);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_reviung33(
        KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P,
        LGUI, LALT, LCTL, LSFT, KC_G, KC_H, RSFT, RCTL, RALT, RGUI,
        KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, LINE, WORD, KC_SLSH,
        SYMTAB, NUMSPC, MCESC),

    [SYM] = LAYOUT_reviung33(
        KC_GRV, KC_BTN1, KC_MS_U, KC_BTN2, KC_EXLM, KC_PMNS, KC_UNDS, KC_PIPE, KC_TILD, KC_PERC,
        KC_AT, KC_MS_L, KC_MS_D, KC_MS_R, KC_QUOT, KC_RPRN, KC_HASH, KC_DLR, _______, _______,
        KC_ASTR, KC_WH_L, KC_WH_R, KC_WH_U, KC_DQT, KC_AMPR, _______, KC_BRIU, KC_BRID, KC_BSLS,
        _______, KC_WH_D, _______),

    [NUM] = LAYOUT_reviung33(
        BR2, KC_HOME, KC_UP, KC_END, KC_VOLD, KC_VOLU, KC_7, KC_8, KC_9, KC_PLUS,
        BR1, KC_LEFT, KC_DOWN, KC_RIGHT, KC_MUTE, _______, KC_4, KC_5, KC_6, KC_EQL,
        BR3, KC_PGDN, _______, KC_PGUP, _______, KC_0, KC_1, KC_2, KC_3, KC_MINS,
        _______, _______, _______),

    [MACRO] = LAYOUT_reviung33(
        QK_BOOT, QK_MAKE, CHROME, RGB_MOD, TELEGR, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,
        RGB_VAD, RGB_SAI, DISC, RGB_RMOD, TIMER, KC_F6, KC_F7, KC_F8, KC_F9, EVKEY,
        RGB_VAI, RGB_SAD, RGB_HUI, RGB_TOG, _______, KC_F10, KC_F11, KC_F12, DESK1, DESK2,
        _______, RGB_HUD, _______),
};

// macro
  bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
       case CHROME:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI("r") SS_DELAY(200) "chrome" SS_TAP(X_ENT));
            }
            break;
       case TELEGR:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI("r") SS_DELAY(200) "C:\\Users\\khanh\\AppData\\Roaming\\Telegram Desktop\\telegram.exe" SS_TAP(X_ENT));
            }
            break;
       case DISC:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI("r") SS_DELAY(200) "C:\\Users\\khanh\\AppData\\Local\\Discord\\Update.exe --processStart Discord.exe" SS_TAP(X_ENT));
            }
            break;
       case TIMER:
           if (record->event.pressed) {
               SEND_STRING(SS_LGUI("r") SS_DELAY(200) "shutdown -s -t 1800" SS_TAP(X_ENT));
           }
           break;
      }
    return true;
};

// Combo
const uint16_t PROGMEM comb_bkspc[] = {RSFT, RCTL, COMBO_END};
const uint16_t PROGMEM comb_ent[] = {RCTL, RALT, COMBO_END};
const uint16_t PROGMEM comb_del[] = {KC_I, KC_O, COMBO_END};
combo_t key_combos[COMBO_COUNT] = {
    [COMB_BKSPC] = COMBO(comb_bkspc, KC_BSPC),
    [COMB_ENT] = COMBO(comb_ent, KC_ENT),
    [COMB_DEL] = COMBO(comb_del, KC_DEL),

};

// Create an instance of 'td_tap_t' for the 'x' tap dance.
static td_tap_t xtap_state = {
    .is_press_action = true,
    .state = TD_NONE
};


td_state_t dance_state(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
        else return TD_TRIPLE_HOLD;
    } else return TD_UNKNOWN;
}

// 2 tap comma= delete one word
void td_com(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = dance_state(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_DOT);
            break;
        case TD_DOUBLE_TAP:
           SEND_STRING(SS_LCTL(SS_TAP(X_DEL)));
            //SEND_STRING(SS_LCTL(SS_TAP(X_BSPC)));
            //  case TD_DOUBLE_HOLD:
            // SEND_STRING(SS_LCTL(SS_TAP(X_DEL)));
        default: break;
    }
}
// dot dot for delete 1 line
void td_dot(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = dance_state(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_COMM);
            break;
        case TD_DOUBLE_TAP:
            SEND_STRING(SS_TAP(X_HOME) SS_LSFT(SS_TAP(X_END)) SS_TAP(X_DEL));
            break;
        default: break;
    }
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [DOTDOT] = ACTION_TAP_DANCE_FN(td_dot),
    [COMCOM] = ACTION_TAP_DANCE_FN(td_com),
    [TDBR1] = ACTION_TAP_DANCE_DOUBLE(KC_LPRN, KC_RPRN),
    [TDBR2] = ACTION_TAP_DANCE_DOUBLE(KC_LCBR, KC_RCBR),
    [TDBR3] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_RBRC)
};


