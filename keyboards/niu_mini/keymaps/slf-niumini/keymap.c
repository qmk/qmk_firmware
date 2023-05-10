#include QMK_KEYBOARD_H

// Left-hand home row mods
// #define GUI_A LGUI_T(KC_A)
// #define ALT_S LALT_T(KC_S)
// #define SFT_D LSFT_T(KC_D)
// #define CTL_F LCTL_T(KC_F)

// Right-hand home row mods
// #define CTL_J RCTL_T(KC_J)
// #define SFT_K RSFT_T(KC_K)
// #define ALT_L LALT_T(KC_L)
// #define GUI_SCLN RGUI_T(KC_SCLN)



// Tap Dance keycodes
enum td_keycodes {
    L_BRAX, // Used in the keymap, add additional keycodes for each tapdance.
    R_BRAX,
    QUOTS,  
    TACHE   
};

// Define a type containing as many tapdance states as you need
typedef enum {
    SINGLE_TAP,
    DOUBLE_TAP,           // SINGLE_HOLD,
    TRIPLE_TAP            // DOUBLE_SINGLE_TAP
} td_state_t;

// Create a global instance of the tapdance state type
static td_state_t td_state;

// Declare your tapdance functions:

// Function to determine the current tapdance state
uint8_t cur_dance(qk_tap_dance_state_t *state);

// `finished` and `reset` functions for each tapdance keycode
void lbrax_finished(qk_tap_dance_state_t *state, void *user_data);
void lbrax_reset(qk_tap_dance_state_t *state, void *user_data);

void rbrax_finished(qk_tap_dance_state_t *state, void *user_data);
void rbrax_reset(qk_tap_dance_state_t *state, void *user_data);

void quots_finished(qk_tap_dance_state_t *state, void *user_data);
void quots_reset(qk_tap_dance_state_t *state, void *user_data);

void tache_finished(qk_tap_dance_state_t *state, void *user_data);
void tache_reset(qk_tap_dance_state_t *state, void *user_data);


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_planck_mit(KC_Q, KC_W, KC_E, KC_R, KC_T, KC_NO, KC_NO, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_A, KC_S, KC_D, KC_F, KC_G, KC_NO, KC_NO, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_NUBS, KC_SLSH, KC_N, KC_M, KC_COMM, KC_DOT, KC_ENT, LCTL_T(KC_ESC), KC_LALT, KC_LGUI, KC_LSFT, MO(1), KC_SPC, MO(2), KC_LSFT, TD(QUOTS), KC_LALT, LCTL_T(KC_TAB)),
	[1] = LAYOUT_planck_mit(KC_EXLM, KC_DQUO, LSFT(KC_3), KC_DLR, KC_PERC, KC_NO, KC_NO, KC_CIRC, KC_AMPR, KC_ASTR, KC_DEL, KC_BSPC, KC_F24, LALT(KC_F3), KC_NO, KC_NO, TD(L_BRAX), KC_NO, KC_NO, TD(R_BRAX), KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, LCTL(KC_F12), LALT(KC_X), KC_NO, KC_NO, KC_NO, TD(QUOTS), TD(TACHE), KC_MINS, KC_EQL, KC_COMM, KC_DOT, KC_ENT, KC_TRNS, KC_NO, KC_NO, MO(3), KC_NO, KC_SPC, MO(3), KC_NO, KC_NO, KC_NO, KC_TRNS),
	[2] = LAYOUT_planck_mit(KC_1, KC_2, KC_3, KC_4, KC_5, KC_NO, KC_NO, KC_6, KC_7, KC_8, KC_9, KC_0, KC_F24, LALT(KC_F3), KC_NO, KC_NO, TD(L_BRAX), KC_NO, KC_NO, TD(R_BRAX), KC_HOME, KC_PGDN, KC_PGUP, KC_END, LCTL(KC_F12), LALT(KC_X), KC_NO, KC_NO, KC_NO, TD(QUOTS), TD(TACHE), KC_MINS, KC_EQL, KC_COMM, KC_DOT, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, MO(3), KC_NO, KC_NO, MO(3), KC_NO, KC_NO, KC_TRNS),
	[3] = LAYOUT_planck_mit(KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_NO, KC_NO, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_ASTG, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, LCA(KC_LEFT), LCA(KC_DOWN), LCA(KC_UP), LCA(KC_RGHT), KC_LCTL, LALT(KC_DEL), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_LCTL, KC_NO, KC_TRNS, KC_NO, KC_TRNS, KC_LSFT, KC_NO, KC_NO, KC_TRNS)
};



// tapping term per key
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LCTL_T(KC_ESC):
        //            return TAPPING_TERM + 1250;
            return 500;
        case LALT_T(KC_TAB):
            return 500;
        default:
            return TAPPING_TERM;
    }
}


// Determine the tapdance state to return
uint8_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        return SINGLE_TAP;
    } else if (state->count == 2) {
        return DOUBLE_TAP;
    } else if (state->count == 3) {
        return TRIPLE_TAP;
    } else {
        reset_tap_dance (state);
        return 3;
    }
}


// Handle the possible states for each tapdance keycode you define:

void lbrax_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case SINGLE_TAP:
            register_mods(MOD_BIT(KC_LSFT)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            register_code16(KC_9);
            break;
        case DOUBLE_TAP:
            register_code16(KC_LBRC);
            break;
        case TRIPLE_TAP: 
            register_mods(MOD_BIT(KC_LSFT)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            register_code16(KC_LBRC);
    }
}

void lbrax_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case SINGLE_TAP:
            unregister_code16(KC_9);
            unregister_mods(MOD_BIT(KC_LSFT)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            break;
        case DOUBLE_TAP:
            unregister_code16(KC_LBRC);
            break;
        case TRIPLE_TAP:
            unregister_code16(KC_LBRC);
            unregister_mods(MOD_BIT(KC_LSFT)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
    }
}

// Handle the possible states for each tapdance keycode you define:

void rbrax_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case SINGLE_TAP:
            register_mods(MOD_BIT(KC_LSFT)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            register_code16(KC_0);
            break;
        case DOUBLE_TAP:
            register_code16(KC_RBRC);
            break;
        case TRIPLE_TAP: // Allow nesting of 2 parens `((` within tapping term
            register_mods(MOD_BIT(KC_LSFT)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            register_code16(KC_RBRC);
    }
}

void rbrax_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case SINGLE_TAP:
            unregister_code16(KC_0);
            unregister_mods(MOD_BIT(KC_LSFT)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            break;
        case DOUBLE_TAP:
            unregister_code16(KC_RBRC);
            break;
        case TRIPLE_TAP:
            unregister_code16(KC_RBRC);
            unregister_mods(MOD_BIT(KC_LSFT)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
    }
}

void quots_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case SINGLE_TAP:
            // register_mods(MOD_BIT(KC_LSFT)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            register_code16(KC_QUOT);
            break;
        case DOUBLE_TAP:
            register_code16(KC_AT);
            break;
        case TRIPLE_TAP: // Allow nesting of 2 parens `((` within tapping term
            // register_mods(MOD_BIT(KC_LSFT)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            register_code16(KC_DQUO);
    }
}

void quots_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case SINGLE_TAP:
            unregister_code16(KC_QUOT);
            // unregister_mods(MOD_BIT(KC_LSFT)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            break;
        case DOUBLE_TAP:
            unregister_code16(KC_AT);
            break;
        case TRIPLE_TAP:
            unregister_code16(KC_DQUO);
            // unregister_mods(MOD_BIT(KC_LSFT)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
    }
}

void tache_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case SINGLE_TAP:
            // register_mods(MOD_BIT(KC_LSFT)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            register_code16(KC_NUHS);
            break;
        case DOUBLE_TAP:
            register_mods(MOD_BIT(KC_LSFT)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here        
            register_code16(KC_NUHS);
            break;
        case TRIPLE_TAP: // Allow nesting of 2 parens `((` within tapping term
            // register_mods(MOD_BIT(KC_LSFT)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            register_code16(KC_GRV);
    }
}

void tache_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case SINGLE_TAP:
            unregister_code16(KC_NUHS);
            // unregister_mods(MOD_BIT(KC_LSFT)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            break;
        case DOUBLE_TAP:
            unregister_code16(KC_NUHS);
            unregister_mods(MOD_BIT(KC_LSFT)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            break;
        case TRIPLE_TAP:
            unregister_code16(KC_GRV);
            // unregister_mods(MOD_BIT(KC_LSFT)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
    }
}


// Define `ACTION_TAP_DANCE_FN_ADVANCED()` for each tapdance keycode, passing in `finished` and `reset` functions
qk_tap_dance_action_t tap_dance_actions[] = {
    [L_BRAX] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lbrax_finished, lbrax_reset),
    [R_BRAX] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rbrax_finished, rbrax_reset),
    [QUOTS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, quots_finished, quots_reset),
    [TACHE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tache_finished, tache_reset)
};

