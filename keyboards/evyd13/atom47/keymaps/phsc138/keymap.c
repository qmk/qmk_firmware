/* Copyright 2022 PHSC138
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

// These are all aliases for the function layers.
enum custom_layers {
    _BASE,
    _PROG,
    _GAME,
    _FN,
    _FN1,
    _NUM
};


// Tap Dance
typedef struct {
    char is_press_action;
    int state;
} tap;

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD = 2,
    DOUBLE_TAP = 3,
    DOUBLE_HOLD = 4,
    DOUBLE_SINGLE_TAP = 5, // Send two single taps
    TRIPLE_TAP = 6,
    TRIPLE_HOLD = 7
};

// Tap dance enums
enum {
    PN_SWAP = 0,
    LAPO = 1,
    LCPO = 2,
    RAPC = 3,
    RCPC = 4,
    D20 = 5
};

enum custom_keycodes {
    PROF_MAC = QK_USER
};


uint8_t cur_dance (tap_dance_state_t *state);
void pn_finished (tap_dance_state_t *state, void *user_data);
void pn_reset (tap_dance_state_t *state, void *user_data);


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// TREE: 'pn' to enter custom layers:
    // _BASE
        // _FN
        // _FN1
        // _NUM
        // _PROG
    // _PROG
        // _FN
        // _FN1
        // _NUM
        // _GAME
    // _GAME
    // _BASE

// Tap pn for toggle to _PROG, or hold for numpad
[_BASE] = LAYOUT_split_space(
    QK_GESC,  KC_Q,     KC_W,     KC_E,        KC_R,        KC_T,       KC_Y,    KC_U,      KC_I,    KC_O,       KC_P,     KC_DEL,   KC_BSPC,
    KC_TAB,   KC_A,     KC_S,     KC_D,        KC_F,        KC_G,       KC_H,    KC_J,      KC_K,    KC_L,       KC_SCLN,            KC_ENT,
    KC_LSFT,  KC_Z,     KC_X,     KC_C,        KC_V,        KC_B,       KC_N,    KC_M,      KC_COMM, KC_DOT,     KC_RSFT,            MO(_FN1),
    KC_LCTL,  KC_LGUI,  KC_LALT,  TD(PN_SWAP),              KC_SPC,              KC_SPC,             MO(_FN),    KC_RALT,  KC_APP,   KC_RCTL),


// LEFT AND RIGHT SHIFT: '(' and ')' when tapped, shift when held
// LEFT AND RIGHT CTRL: '{' and '}' when tapped, ctrl when held
// LEFT AND RIGHT ALT: '[' and ']' when tapped, ctrl when held
[_PROG] = LAYOUT_split_space(
    _______,  _______,  _______,  _______,     _______,     _______,    _______, _______,   _______, _______,    _______,   _______, _______,
    _______,  _______,  _______,  _______,     _______,     _______,    _______, _______,   _______, _______,    _______,            _______,
    SC_LSPO,  _______,  _______,  _______,     _______,     _______,    _______, _______,   _______, _______,    SC_RSPC,            _______,
    TD(LCPO), _______,  TD(LAPO), TO(_GAME),                _______,             _______,            _______,    TD(RAPC),  _______, TD(RCPC)),


// Macro for right space is bhop
// Maco for 'fn' is move forward
// Macro for 'fn1' is spin constantly
// Macro for right shift is D20
[_GAME] = LAYOUT_split_space(
    _______,  _______,  _______,  _______,     _______,     _______,    _______, _______,   _______, _______,    _______,   _______, _______,
    _______,  _______,  _______,  _______,     _______,     _______,    _______, _______,   _______, _______,    _______,            _______,
    _______,  _______,  _______,  _______,     _______,     _______,    _______, _______,   _______, _______,    TD(D20),            XXXXXXX,
    _______,  _______,  _______,  TO(_BASE),                _______,             XXXXXXX,            XXXXXXX,    _______,   XXXXXXX, _______),


[_FN] = LAYOUT_split_space(
    _______,  KC_VOLD,  KC_VOLU,  KC_MUTE,     QK_RBT,      _______,    KC_CALC, KC_PGUP,   _______, KC_PGDN,    KC_PSCR,   KC_SCRL,  KC_PAUS,
    KC_CAPS,  KC_MPRV,  KC_MPLY,  KC_MNXT,     _______,     _______,    KC_LEFT, KC_DOWN,   KC_UP,   KC_RIGHT,   KC_INS,              _______,
    _______,  _______,  _______,  _______,     _______,     KC_HOME,    KC_END,  BL_TOGG,   BL_DOWN,  BL_UP,     _______,             _______,
    _______,  _______,  _______,  _______,                  _______,             _______,            _______,    _______,   _______,  _______),


[_FN1] = LAYOUT_split_space(
    KC_GRV,   KC_F1,    KC_F2,    KC_F3,       KC_F4,       KC_F5,      KC_F6,   KC_F7,     KC_F8,   KC_F9,      KC_F10,    KC_F11,   KC_F12,
    KC_1,     KC_2,     KC_3,     KC_4,        KC_5,        KC_6,       KC_7,    KC_8,      KC_9,    KC_0,       KC_MINS,             KC_EQL,
    _______,  _______,  _______,  _______,     _______,     KC_QUOT,    KC_SLSH, KC_LBRC,   KC_RBRC, KC_BSLS,    KC_RSFT,             _______,
    _______,  _______,  _______,  _______,     _______,     _______,             _______,            _______,    _______,             _______),


[_NUM] = LAYOUT_split_space(
    _______,  _______,  _______,  _______,     _______,     _______,    KC_7,    KC_8,      KC_9,    _______,    PROF_MAC,  _______,  _______,
    _______,  _______,  _______,  _______,     _______,     _______,    KC_4,    KC_5,      KC_6,    _______,    _______,             _______,
    _______,  _______,  _______,  _______,     _______,     KC_1,       KC_2,    KC_3,      KC_DOT,  _______,    _______,             _______,
    _______,  _______,  _______,  _______,     _______,     KC_0,                 _______,           _______,    DB_TOGG,             QK_BOOT),
};


/*--- Profile Macro ---*/
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case PROF_MAC:
      if (record->event.pressed) {
        // When keycode PROF_MAC is pressed
        SEND_STRING("if [ $shell = 'zsh' ]; then echo \"echo \"Lock your computer -PHSC138\"\" >> ~/.zshrc\nclear; else echo \"echo \"Lock your computer -PHSC138\"\" >> ~/.profile\nclear; fi\n");
      } else {
        // When keycode QMKBEST is released
      }
      break;
  }
  return true;
};
/*--- End Profile Macro ---*/

/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicitive that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */
uint8_t cur_dance(tap_dance_state_t *state) {
    if(state->count == 1) {
        if(state->interrupted || !state->pressed) return SINGLE_TAP;
        //key has not been interrupted, but they key is still held. Means you want to send a 'HOLD'.
        else return SINGLE_HOLD;
    } else if(state->count == 2) {
        /*
         * DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
         * action when hitting 'pp'. Suggested use case for this return value is when you want to send two
         * keystrokes of the key, and not the 'double tap' action/macro.
        */
        if(state->interrupted) return DOUBLE_SINGLE_TAP;
        else if(state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    //Assumes no one is trying to type the same letter three times (at least not quickly).
    //If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    //an exception here to return a 'TRIPLE_SINGLE_TAP', and define that enum just like 'DOUBLE_SINGLE_TAP'
    if(state->count == 3) {
        if(state->interrupted || !state->pressed) return TRIPLE_TAP;
        else return TRIPLE_HOLD;
    }
    else return 8; //magic number. At some point this method will expand to work for more presses
}

//instanalize an instance of 'tap' for the 'pn' tap dance.
static tap pn_tap_state = {
    .is_press_action = 1,
    .state = 0
};

void pn_finished(tap_dance_state_t *state, void *user_data) {
    pn_tap_state.state = cur_dance(state);
    switch(pn_tap_state.state) {
        case SINGLE_TAP: layer_on(_PROG); break;
        case SINGLE_HOLD: layer_on(_NUM); break;
        //case DOUBLE_TAP: register_code(KC_ESC); break;
        //case DOUBLE_HOLD: register_code(KC_LALT); break;
        //case DOUBLE_SINGLE_TAP: register_code(KC_X); unregister_code(KC_X); register_code(KC_X);
        //Last case is for fast typing. Assuming your key is `f`:
        //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
    }
}

void pn_reset(tap_dance_state_t *state, void *user_data) {
    switch(pn_tap_state.state) {
        //case SINGLE_TAP: unregister_code(KC_X); break;
        case SINGLE_HOLD: layer_off(_NUM); break;
        //case DOUBLE_TAP: unregister_code(KC_ESC); break;
        //case DOUBLE_HOLD: unregister_code(KC_LALT);
        //case DOUBLE_SINGLE_TAP: unregister_code(KC_X);
    }
    pn_tap_state.state = 0;
}

static tap lalt_tap_state = {
    .is_press_action = 1,
    .state = 0
};

void lalt_finished(tap_dance_state_t *state, void *user_data) {
    lalt_tap_state.state = cur_dance(state);
    switch(lalt_tap_state.state) {
        case SINGLE_TAP: register_code(KC_LBRC); break;
        case SINGLE_HOLD: register_code(KC_LALT); break;
    }
}

void lalt_reset(tap_dance_state_t *state, void *user_data) {
    switch(lalt_tap_state.state) {
        case SINGLE_TAP: unregister_code(KC_LBRC); break;
        case SINGLE_HOLD: unregister_code(KC_LALT); break;
    }
    lalt_tap_state.state = 0;
}

static tap ralt_tap_state = {
    .is_press_action = 1,
    .state = 0
};

void ralt_finished(tap_dance_state_t *state, void *user_data) {
    ralt_tap_state.state = cur_dance(state);
    switch(ralt_tap_state.state) {
        case SINGLE_TAP: register_code(KC_RBRC); break;
        case SINGLE_HOLD: register_code(KC_RALT); break;
    }
}

void ralt_reset(tap_dance_state_t *state, void *user_data) {
    switch(ralt_tap_state.state) {
        case SINGLE_TAP: unregister_code(KC_RBRC); break;
        case SINGLE_HOLD: unregister_code(KC_RALT); break;
    }
    ralt_tap_state.state = 0;
}

static tap rctl_tap_state = {
    .is_press_action = 1,
    .state = 0
};

void rctl_finished(tap_dance_state_t *state, void *user_data) {
    rctl_tap_state.state = cur_dance(state);
    switch(rctl_tap_state.state) {
        case SINGLE_TAP: register_code(KC_RSFT); register_code(KC_RBRC); break;
        case SINGLE_HOLD: register_code(KC_RCTL); break;
    }
}

void rctl_reset(tap_dance_state_t *state, void *user_data) {
    switch(rctl_tap_state.state) {
        case SINGLE_TAP: unregister_code(KC_RSFT); unregister_code(KC_RBRC); break;
        case SINGLE_HOLD: unregister_code(KC_RCTL); break;
    }
    rctl_tap_state.state = 0;
}

static tap lctl_tap_state = {
    .is_press_action = 1,
    .state = 0
};

void lctl_finished(tap_dance_state_t *state, void *user_data) {
    lctl_tap_state.state = cur_dance(state);
    switch(lctl_tap_state.state) {
        case SINGLE_TAP: register_code(KC_LSFT); register_code(KC_LBRC); break;
        case SINGLE_HOLD: register_code(KC_LCTL); break;
    }
}

void lctl_reset(tap_dance_state_t *state, void *user_data) {
    switch(lctl_tap_state.state) {
        case SINGLE_TAP: unregister_code(KC_LSFT); unregister_code(KC_LBRC); break;
        case SINGLE_HOLD: unregister_code(KC_LCTL); break;
    }
    lctl_tap_state.state = 0;
}

static tap d20_tap_state = {
    .is_press_action = 1,
    .state = 0,
};

int d20_srand = 0;
uint32_t timer_seed;

void d20_finished(tap_dance_state_t *state, void *user_data) {
    d20_tap_state.state = cur_dance(state);
    switch(d20_tap_state.state) {
        case SINGLE_HOLD: {
            if(d20_srand == 0){
                timer_seed = timer_read32();
                srand((unsigned int)timer_seed);
                d20_srand = 1;
            }

            SEND_STRING("Seed: ");
            // uint32_t has max size of 4294967296
            char SEED_STR_SIZE = 16;
            // Initialize seed_str
            char seed_str[SEED_STR_SIZE];
            for (int iter=0;iter < SEED_STR_SIZE;iter++) seed_str[iter] = 0;

            int i = SEED_STR_SIZE - 2; // Leave null byte on end of string
            while (timer_seed && i >= 0) {
                seed_str[i] = timer_seed % 10 + '0';
                timer_seed /= 10;
                i -= 1;
            }
            i++;

            // Move all characters over i spaces
            char move = i;
            while (i < SEED_STR_SIZE -1) {
                seed_str[i-move] = seed_str[i];
                seed_str[i] = 0;
                i += 1;
            }

            send_string(seed_str);
            break;
            // Else allow fall through
        }
        case SINGLE_TAP: {
            if(d20_srand == 0){
                timer_seed = timer_read();
                srand((unsigned int)timer_seed);
                d20_srand = 1;
            }

            unsigned char roll = rand() % 20 + 1;
            char res[3];
            res[0] = (char)((char)(roll / 10) + '0');
            res[1] = (char)(roll % 10 + '0');

            send_string(res);

            break;
                         }
    }
}

void d20_reset(tap_dance_state_t *state, void *user_data) {
    d20_tap_state.state = 0;
}

tap_dance_action_t tap_dance_actions[] = {
    [PN_SWAP]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, pn_finished, pn_reset),
    [LAPO]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lalt_finished, lalt_reset),
    [RAPC]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ralt_finished, ralt_reset),
    [LCPO]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lctl_finished, lctl_reset),
    [RCPC]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rctl_finished, rctl_reset),
    [D20]      = ACTION_TAP_DANCE_FN_ADVANCED(NULL, d20_finished, d20_reset),
};
