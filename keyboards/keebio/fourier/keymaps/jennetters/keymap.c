#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BASE 0
#define _FN1 1
#define _FN2 2

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
};

#define KC_ KC_TRNS
#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define KC_FN1 MO(_FN1)
#define KC_FN2 MO(_FN2)
#define KC_SPFN1 LT(_FN1, KC_SPACE)
#define KC_SPFN2 LT(_FN2, KC_SPACE)
#define KC_BSFN1 LT(_FN1, KC_BSPC)
#define KC_BSFN2 LT(_FN2, KC_BSPC)
#define KC_RST RESET
#define KC_DBUG DEBUG
#define KC_RTOG RGB_TOG
#define KC_RMOD RGB_MOD
#define KC_RHUI RGB_HUI
#define KC_RHUD RGB_HUD
#define KC_RSAI RGB_SAI
#define KC_RSAD RGB_SAD
#define KC_RVAI RGB_VAI
#define KC_RVAD RGB_VAD

//Tap Dance Declarations
enum {
  ESC_GR = 0,
  Q_1,
  W_2,
  E_3,
  R_4,
  T_5,
  Y_6,
  U_7,
  I_8,
  O_9,
  P_0,
  MIN_LB,
  EQL_RB,
  SCL_QUO
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_BASE] = LAYOUT( 
 // ,----+----+----+----+----+----|----+----+----+----+----+----+----.
 // |ESC | Q1 | W2 | E3 | R4 | T5 | Y6 | U7 | I8 | O9 | P0 | -[ | =] |
 // |----`----`----`----`----`----|----`----`----`----`----`----`----|
 // | TAB | A  | S  | D  | F  | G  | H  | H  | J  | K  | L  |  BKSP  |
 // |-----`----`----`----`----`----|----`----`----`----`----`--------|
 // | SHIFT | Z  | X  | C  | V  | B  | N  | M  | ,  | .  | /  | SHFT |
 // |-------`----`----`----`----`----|----`----`----`----`----`------|
 // | CTL | SYS| ALT | SP    SPACE | SPACE  | FN1 | CTL  | \  | ENT  |
 // `-----+----+-----+----+--------|--------+-----+------+----+------'
 
  TD(ESC_GR), TD(Q_1), TD(W_2), TD(E_3), TD(R_4), TD(T_5), TD(Y_6), TD(U_7), TD(I_8), TD(O_9), TD(P_0),TD(MIN_LB),TD(EQL_RB), \
  KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, TD(SCL_QUO), KC_BSPC, \
  KC_LSPO, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSPC, \
  KC_LCTL, KC_LGUI, KC_LALT, KC_SPACE, KC_SPACE, KC_SPACE, KC_FN1, KC_LCTL, KC_NUBS, KC_ENTER
  ),

  [_FN1] = LAYOUT_kc(
 // ,----+----+----+----+----+----|----+----+----+----+----+----+----.
 // |    |    | UP |    |    |    |    |    |    |    |    |    |    |
 // |----`----`----`----`----`----|----`----`----`----`----`----`----|
 // |     | LT | DN | RT |    |    |    |    |    |    | '  |  DEL   |
 // |-----`----`----`----`----`----|----`----`----`----`----`--------|
 // |       |    |    |    |    |    |    |    |    |    |PIPE|      |
 // |-------`----`----`----`----`----|----`----`----`----`----`------|
 // |     |    |     |    |        |        |     |      |    |      |
 // `-----+----+-----+----+--------|--------+-----+------+----+------'
 
   , , UP, , , , , , , , , , , \
   , LEFT, DOWN, RIGHT, , , , , , , QUOT, DEL, \
   , , , , , , , , , , NUBS, , \
   , , , , , , , , , 
  ),

  [_FN2] = LAYOUT_kc(
 // ,----+----+----+----+----+----|----+----+----+----+----+----+----.
 // |    |    |    |    |    |    |    |    |    |    |    |    |    |
 // |----`----`----`----`----`----|----`----`----`----`----`----`----|
 // |     |   |     |    |    |    |    |    |    |    |    |        |
 // |-----`----`----`----`----`----|----`----`----`----`----`--------|
 // |       |    |    |    |    |    |    |    |    |    |    |      |
 // |-------`----`----`----`----`----|----`----`----`----`----`------|
 // |     |    |     |    |        |        |     |      |    |      |
 // `-----+----+-----+----+--------|--------+-----+------+----+------'

   , , , , , , , , , , , , , \
   , , , , , , , , , , , , \
   , , , , , , , , , , , , \
   , , , , , , , , ,   
  )

};

void esc_gr_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code (KC_ESC);
  } else if (state->count == 2) {
    register_code (KC_GRV);
  } else {
    register_code (KC_LSFT);
    register_code (KC_GRV);
  }
}

void esc_gr_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (KC_ESC);
  } else if (state->count == 2) {
    unregister_code (KC_GRV);
  } else {
    unregister_code (KC_LSFT);
    unregister_code (KC_GRV);
  }
}

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
[ESC_GR] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, esc_gr_finished, esc_gr_reset), //Tap once for ESC, twice for `, thrice for ~
[Q_1]  = ACTION_TAP_DANCE_DOUBLE(KC_Q, KC_1), //Tap once for Q, twice for 1/!
[W_2]  = ACTION_TAP_DANCE_DOUBLE(KC_W, KC_2), //Tap once for W, twice for 2/@
[E_3]  = ACTION_TAP_DANCE_DOUBLE(KC_E, KC_3), //Tap once for E, twice for 3/#
[R_4]  = ACTION_TAP_DANCE_DOUBLE(KC_R, KC_4), //Tap once for R, twice for 4/$
[T_5]  = ACTION_TAP_DANCE_DOUBLE(KC_T, KC_5), //Tap once for T, twice for 5/%
[Y_6]  = ACTION_TAP_DANCE_DOUBLE(KC_Y, KC_6), //Tap once for Y, twice for 6/^
[U_7]  = ACTION_TAP_DANCE_DOUBLE(KC_U, KC_7), //Tap once for U, twice for 7/&
[I_8]  = ACTION_TAP_DANCE_DOUBLE(KC_I, KC_8), //Tap once for I, twice for 8/*
[O_9]  = ACTION_TAP_DANCE_DOUBLE(KC_O, KC_9), //Tap once for O, twice for 9/(
[P_0]  = ACTION_TAP_DANCE_DOUBLE(KC_P, KC_0), //Tap once for P, twice for 0/)
[MIN_LB]  = ACTION_TAP_DANCE_DOUBLE(KC_MINS, KC_LBRC), //Tap once for -, twice for [/{
[EQL_RB]  = ACTION_TAP_DANCE_DOUBLE(KC_EQL, KC_RBRC), //Tap once for =, twice for ]/}
[SCL_QUO] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_QUOT) //Tap once for ;, '/"
// Other declarations would go here, separated by commas, if you have them
};