#include "viterbi.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _NUMNAV   0
#define _DIABLO   1
#define _GAMEPAD  2
#define _MACROS   3
#define _MEDIA    4
#define _COVECUBE 5


enum custom_keycodes {
    KC_DIABLO_CLEAR = SAFE_RANGE,
    KC_P00,
    KC_MAKE,
    KC_OVERWATCH,
    KC_SALT,
    KC_MORESALT,
    KC_SALTHARD,
    KC_GOODGAME,
    KC_SYMM,
    KC_DOOMFIST,
    KC_JUSTGAME,
    KC_GLHF,
    KC_TORB,
    KC_AIM
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define MACROS   TG(_MACROS)
#define DIABLO   TG(_DIABLO)
#define GAMEPAD  TG(_GAMEPAD)
#define MEDIA    TG(_MEDIA)
#define COVECUBE TG(_COVECUBE)


bool is_overwatch = false;


#ifdef RGBLIGHT_ENABLE
#define rgblight_set_blue        rgblight_sethsv (0xFF,  0xFF, 0xFF);
#define rgblight_set_red         rgblight_sethsv (0x00,  0xFF, 0xFF);
#define rgblight_set_green       rgblight_sethsv (0x78,  0xFF, 0xFF);
#define rgblight_set_orange      rgblight_sethsv (0x1E,  0xFF, 0xFF);
#define rgblight_set_teal        rgblight_sethsv (0xC3,  0xFF, 0xFF);
#define rgblight_set_magenta     rgblight_sethsv (0x12C, 0xFF, 0xFF);
#define rgblight_set_yellow      rgblight_sethsv (0x3C,  0xFF, 0xFF);
#define rgblight_set_purple      rgblight_sethsv (0x10E, 0xFF, 0xFF);
#endif

#ifdef TAP_DANCE_ENABLE
//define diablo macro timer variables
static uint16_t diablo_timer[4];
static uint8_t diablo_times[] = { 0, 1, 3, 5, 10, 30 };
static uint8_t diablo_key_time[4];


bool check_dtimer(uint8_t dtimer) {
    // has the correct number of seconds elapsed (as defined by diablo_times)
    return (timer_elapsed(diablo_timer[dtimer]) < (diablo_key_time[dtimer] * 1000)) ? false : true;
};


enum {
    TD_DIABLO_1 = 0,
    TD_DIABLO_2,
    TD_DIABLO_3,
    TD_DIABLO_4
};


// Cycle through the times for the macro, starting at 0, for disabled.
// Max of six values, so don't exceed
void diablo_tapdance_master(qk_tap_dance_state_t *state, void *user_data, uint8_t diablo_key) {
    if (state->count >= 7) {
        diablo_key_time[diablo_key] = diablo_times[0];
        reset_tap_dance(state);
    }
    else {
        diablo_key_time[diablo_key] = diablo_times[state->count - 1];
    }
}


// Would rather have one function for all of this, but no idea how to do that...
void diablo_tapdance1(qk_tap_dance_state_t *state, void *user_data) {
    diablo_tapdance_master(state, user_data, 0);
}

void diablo_tapdance2(qk_tap_dance_state_t *state, void *user_data) {
    diablo_tapdance_master(state, user_data, 1);
}

void diablo_tapdance3(qk_tap_dance_state_t *state, void *user_data) {
    diablo_tapdance_master(state, user_data, 2);
}

void diablo_tapdance4(qk_tap_dance_state_t *state, void *user_data) {
    diablo_tapdance_master(state, user_data, 3);
}



//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // tap once to disable, and more to enable timed micros
    [TD_DIABLO_1] = ACTION_TAP_DANCE_FN(diablo_tapdance1),
    [TD_DIABLO_2] = ACTION_TAP_DANCE_FN(diablo_tapdance2),
    [TD_DIABLO_3] = ACTION_TAP_DANCE_FN(diablo_tapdance3),
    [TD_DIABLO_4] = ACTION_TAP_DANCE_FN(diablo_tapdance4),

};
#endif


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_NUMNAV] = KEYMAP(
      MACROS,  DIABLO,  GAMEPAD, KC_NLCK, KC_SLCK, KC_COLN, KC_PSLS,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      MEDIA,   KC_CALC, COVECUBE,KC_P7,   KC_P8,   KC_P9,   KC_PAST,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      KC_HOME, KC_DEL,  KC_PGUP, KC_P4,   KC_P5,   KC_P6,   KC_PMNS,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      KC_END,  KC_UP,   KC_PGDN, KC_P1,   KC_P2,   KC_P3,   KC_PPLS,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      KC_LEFT, KC_DOWN, KC_RGHT, KC_P0,   KC_P00,  KC_PDOT, KC_PENT,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX \
  ),

  [_DIABLO] = KEYMAP(
      KC_ESC,  DIABLO,  KC_V,    KC_D,    XXXXXXX, XXXXXXX, KC_L,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      KC_TAB,  KC_S,    KC_F,    KC_I,    KC_M,    KC_T,    KC_J,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      KC_Q,    KC_1,    KC_2,    KC_3,    KC_4,    KC_G,    KC_F,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      KC_LCTL, (TD_DIABLO_1), TD(TD_DIABLO_2), TD(TD_DIABLO_3), TD(TD_DIABLO_4), KC_Z, KC_DIABLO_CLEAR,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      KC_LALT, KC_F4,   KC_F5,   KC_F8,   KC_F9,   KC_F10,  SFT_T(KC_SPACE),          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX \
  ),
 
  [_GAMEPAD] = KEYMAP(  // Game pad layout designed primarily for Overwatch
      MACROS,  KC_ESC,  GAMEPAD, KC_1,    KC_2,    KC_3,    KC_4,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      MEDIA,   KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      KC_Z,    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      KC_Y,    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      KC_F1,   KC_U,    KC_I,    KC_Y,    KC_V,    KC_SPC,  KC_V,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX \
  ),

  [_MACROS] = KEYMAP(
      MACROS,      XXXXXXX,     GAMEPAD,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      KC_SYMM,     KC_TORB,     KC_DOOMFIST, XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      KC_GLHF,     KC_GOODGAME, XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      KC_SALT,     KC_MORESALT, KC_SALTHARD, KC_JUSTGAME, KC_AIM,      XXXXXXX,     XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX \
  ),

  [_COVECUBE] = KEYMAP(
      COVECUBE,    XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX \
  ),

  [_MEDIA] = KEYMAP(
      RESET,   KC_MAKE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      MEDIA,   XXXXXXX, RGB_SAI, RGB_VAI, RGB_M_P, RGB_M_B, RGB_M_R,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      RGB_TOG, RGB_MOD, RGB_SAD, RGB_VAD, RGB_M_SW,RGB_M_SN,RGB_M_K,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      KC_MPLY, KC_MSTP, KC_MPRV, KC_MNXT, RGB_M_K, RGB_M_X, RGB_M_G,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      KC_MUTE, KC_VOLD, KC_VOLU, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX \
  )


};



bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uint16_t kc;
    if (is_overwatch) { 
        kc = KC_BSPC;  
    }
    else {
        kc = KC_ENTER;
    }
    // Once a delay command is added to "SEND_STRING", 
    // replace these with X_BSPC and X_ENTER instead. 
    // and add "SS_TAP(kc) SS_DELAY(50)" to all of the
    // SEND_STRING commands, to compress things. 
    switch (keycode) {
#ifdef TAP_DANCE_ENABLE
    case KC_DIABLO_CLEAR:  // reset all Diable timers, disabling them
        if (record->event.pressed) {
            uint8_t dtime;

            for (dtime = 0; dtime < 4; dtime++) {
                diablo_key_time[dtime] = diablo_times[0];
            }
        }
        return false;
        break;
#endif
    case KC_P00:
        if (!record->event.pressed) {
            register_code(KC_P0);
            unregister_code(KC_P0);
            register_code(KC_P0);
            unregister_code(KC_P0);
        }
        return false;
        break;
    case KC_MAKE:
        if (!record->event.pressed) {
            SEND_STRING("make " QMK_KEYBOARD ":" QMK_KEYMAP SS_TAP(X_ENTER));
        }
        return false;
        break;
    case KC_OVERWATCH:  // reset all Diable timers, disabling them
        if (record->event.pressed) {
            is_overwatch = !is_overwatch;
        }
#ifdef RGBLIGHT_ENABLE
        is_overwatch ? rgblight_mode(17) : rgblight_mode(18);
#endif
        return false;
        break;
    case KC_SALT:
        if (!record->event.pressed) {
            register_code(kc);
            unregister_code(kc);
            _delay_ms(50);
            SEND_STRING("Salt, salt, salt..." SS_TAP(X_ENTER));
        }
        return false;
        break;
    case KC_MORESALT:
        if (!record->event.pressed) {
            register_code(kc);
            unregister_code(kc);
            _delay_ms(50);
            SEND_STRING("Please sir, can I have some more salt?!" SS_TAP(X_ENTER));
        }
        return false;
        break;
    case KC_SALTHARD:
        if (!record->event.pressed) {
            register_code(kc);
            unregister_code(kc);
            _delay_ms(50);
            SEND_STRING("Your salt only makes my penis that much harder, and even more aggressive!" SS_TAP(X_ENTER));
        }
        return false;
        break;
    case KC_GOODGAME:
        if (!record->event.pressed) {
            register_code(kc);
            unregister_code(kc);
            _delay_ms(50);
            SEND_STRING("Good game, everyone!" SS_TAP(X_ENTER));
        }
        return false;
        break;
    case KC_GLHF:
        if (!record->event.pressed) {
            register_code(kc);
            unregister_code(kc);
            _delay_ms(50);
            SEND_STRING("Good luck, have fun!!!" SS_TAP(X_ENTER));
        }
        return false;
        break;
    case KC_SYMM:
        if (!record->event.pressed) {
            register_code(kc);
            unregister_code(kc);
            _delay_ms(50);
            SEND_STRING("Left click to win!" SS_TAP(X_ENTER));
        }
        return false;
        break;
    case KC_JUSTGAME:

        if (!record->event.pressed) {
            register_code(kc);
            unregister_code(kc);
            _delay_ms(50);
            SEND_STRING("It may be a game, but if you don't want to actually try, please go play AI, so that people that actually want to take the game seriously and \"get good\" have a place to do so without trolls like you throwing games." SS_TAP(X_ENTER));
        }
        return false;
        break;
    case KC_TORB:

        if (!record->event.pressed) {
            register_code(kc);
            unregister_code(kc);
            _delay_ms(50);
            SEND_STRING("That was positively riveting! SS_TAP(X_ENTER)");
        }
        return false;
        break;
    case KC_AIM:

        if (!record->event.pressed) {
            register_code(kc);
            unregister_code(kc);
            _delay_ms(50);
            SEND_STRING("That aim is absolutely amazing. It's almost like you're a machine!" SS_TAP(X_ENTER));
            _delay_ms(50);
            SEND_STRING("Wait! That aim is TOO good!  You're clearly using an aim hack! CHEATER!" SS_TAP(X_ENTER));
        }
        return false;
        break;


    }
    return true;
}

#ifdef TAP_DANCE_ENABLE

// Sends the key press to system, but only if on the Diablo layer
void send_diablo_keystroke(uint8_t diablo_key) {
    if (biton32(layer_state) == _DIABLO) {
        switch (diablo_key) {
        case 0:
            SEND_STRING("1");
            break;
        case 1:
            SEND_STRING("2");
            break;
        case 2:
            SEND_STRING("3");
            break;
        case 3:
            SEND_STRING("4");
            break;
        }
    }
}

// Checks each of the 4 timers/keys to see if enough time has elapsed
// Runs the "send string" command if enough time has passed, and resets the timer.
void run_diablo_macro_check(void) {
    uint8_t dtime;

    for (dtime = 0; dtime < 4; dtime++) {
        if (check_dtimer(dtime) && diablo_key_time[dtime]) {
            diablo_timer[dtime] = timer_read();
            send_diablo_keystroke(dtime);
        }
    }

}
#endif


void matrix_init_user(void) { // Runs boot tasks for keyboard
#ifdef RGBLIGHT_ENABLE
    rgblight_enable();
    rgblight_set_teal;
    rgblight_mode(1);
#endif
};


void matrix_scan_user(void) {  // runs frequently to update info
#ifdef TAP_DANCE_ENABLE
    // Run Diablo 3 macro checking code.
    run_diablo_macro_check();
#endif
};


uint32_t layer_state_set_kb(uint32_t state) {
#ifdef RGBLIGHT_ENABLE
    rgblight_enable();
    switch (biton32(state)) {
    case _NUMNAV:
        rgblight_set_teal;
        rgblight_mode(2);
        break;
    case _MACROS:
        rgblight_set_orange;
        is_overwatch ? rgblight_mode(17) : rgblight_mode(18);
        break;
    case _DIABLO:
        rgblight_set_red;
        rgblight_mode(5);
        break;
    case _GAMEPAD:
        rgblight_set_yellow;
        rgblight_mode(1);
        break;
    case _MEDIA:
        rgblight_set_blue;
        rgblight_mode(1);
        break;
    case _COVECUBE:
        rgblight_set_green;
        rgblight_mode(2);
    }
#endif
    return state;
}
