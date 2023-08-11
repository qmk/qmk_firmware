/* © 2023  Tony Zorman <soliditsallgood@mailbox.org> (@slotThe)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

// NOTE: `M-x occur RET /// RET' gives a good overview.

/// General macros

#define LSPR_SC  LGUI_T(KC_SCLN)
#define LALT_BR  LALT_T(KC_LBRC)
#define LSFT_INS LSFT(KC_INS)
#define OSMSFT   OSM(MOD_LSFT)
#define Z_SFT    LSFT_T(KC_Z)
#define ZE_SFT   LSFT_T(KC_0)
#define SL_SFT   RSFT_T(KC_SLSH)
#define RETSPR   LGUI_T(KC_ENT)

/// Tap dance declarations

// So far, tap dances do different things on
//
//   - a single press,
//   - a double press,
//   - when held,
//
// so expect this many keys as comments.
enum tap_dances {
  ALT_BR,  // [ ] lalt  (also works shifted, which gets us { and } for free)
  CTL_PR,  // ( ) lctl
  SFT_CI,  // ^ ^ lsft  (working around LSFT_T not being able to output shifted keys)
  SFT_EX,  // ! ! lsft  (ditto)
};

#define CTLPAR TD(CTL_PR)
#define ALTBRC TD(ALT_BR)
#define SFTCRC TD(SFT_CI)
#define SFTEXL TD(SFT_EX)

/// Macro declarations

enum custom_keycodes {
  // ->              <-    =<<   >>=   <*>  <*    *>    <$>   <&>   <|>   =>     ::
  RARR = SAFE_RANGE, LARR, LBND, RBND, APP, RAPP, LAPP, FMAP, PAMF, AALT, IMPLS, DCOL,
};

/// Key overrides

const key_override_t **key_overrides = (const key_override_t *[]){
  &ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL), // S-BSP ≡ DEL
  // Emacs got me used to these, so let's convince other programs that
  // we are in fact sending the correct keys.
  &ko_make_basic(MOD_MASK_CTRL, KC_I, KC_TAB),     // C-i ≡ Tab
  &ko_make_basic(MOD_MASK_CTRL, KC_M, KC_ENT),     // C-m ≡ Return
  NULL // Null terminate the array of overrides
};

/// Layers

enum layer_names { _COLEMAK_DH, _LOWER, _RAISE, _ADJUST };

#define LOWER    MO(_LOWER)
#define RAISE    MO(_RAISE)
#define ADJUST   MO(_ADJUST)
#define D_RAISE  LT(_RAISE, KC_DOT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Colemak base layer
     .-----.-----.-----.-----.-----.           .-----.-----.-----.-----.-----.
     |  Q  |  W  |  F  |  P  |  B  |           |  J  |  L  |  U  |  Y  | ;+S |
     .-----.-----.-----.-----.-----.           .-----.-----.-----.-----.-----.
     |  A  |  R  |  S  |  T  |  G  |           |  M  |  N  |  E  |  I  |  O  |
     .-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.
     | S+Z |  X  |  C  |  D  |  V  | ARP | REP |  K  |  H  |  ,  |  .  | S+/ |
     .-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.
     | ESC | TAB | SPR | L1  | SPC | A[] | BSC | C() | L2  |  -  |  '  | RET |
     .-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.
  */
  [_COLEMAK_DH] = LAYOUT(
    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                      KC_J,    KC_L,    KC_U,    KC_Y,    LSPR_SC,
    KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                      KC_M,    KC_N,    KC_E,    KC_I,    KC_O,
    Z_SFT,   KC_X,    KC_C,    KC_D,    KC_V,    QK_AREP, QK_REP,  KC_K,    KC_H,    KC_COMM, D_RAISE, SL_SFT,
    KC_ESC,  KC_TAB,  KC_LGUI, LOWER,   KC_SPC,  ALTBRC,  KC_BSPC, CTLPAR,  RAISE,   KC_MINS, KC_QUOT, KC_ENT),

  /* Layer 1 (LOWER)
     .-----.-----.-----.-----.-----.           .-----.-----.-----.-----.-------.
     |  &  | *>  | >>= | <&> |     |           |  =  |  +  |  *  |  -  | RET+M |
     .-----.-----.-----.-----.-----.           .-----.-----.-----.-----.-------.
     | ::  | =>  | =<< | <|> |  @  |           | LFT |  UP | DWN | RGT |   \   |
     .-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-------.
     | !+S | <*  | <*> | <$> | <-  |     | MEN |  -> |  $  |  #  |  %  |  ^+S  |
     .-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-------.
     |     |     |     |     |     |     |     |     | L3  | ALT |     |  S-I  |
     .-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-------.
  */
  [_LOWER] = LAYOUT(
    KC_AMPR, RAPP,    RBND,    PAMF,    _______,                   KC_EQL,  KC_PLUS, KC_ASTR, KC_MINS, RETSPR,
    DCOL,    IMPLS,   LBND,    AALT,    KC_AT,                     KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_BSLS,
    SFTEXL,  LAPP,    APP,     FMAP,    LARR,    _______, KC_APP,  RARR,    KC_DLR,  KC_HASH, KC_PERC, SFTCRC,
    _______, _______, _______, _______, _______, _______, _______, _______, ADJUST,  KC_LALT, _______, LSFT_INS),

  /* Layer 2 (RAISE)
     .-----.-----.-----.-----.-----.           .-----.-----.-----.-----.-----.
     |     |  7  |  8  |  9  |     |           |     |  +  |  *  |  -  |     |
     .-----.-----.-----.-----.-----.           .-----.-----.-----.-----.-----.
     |  :  |  4  |  5  |  6  |  =  |           |  &  |  `  |  _  |  '  |  "  |
     .-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.
     | 0+S |  1  |  2  |  3  |     |     |     |     |  !  |  #  |  %  | ^+S |
     .-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.
     |     |     |     | L3  |     |     |     |     |     |     |     |     |
     .-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.
  */
  [_RAISE] = LAYOUT(
    KC_DOT,  KC_7,    KC_8,    KC_9,    _______,                   _______, KC_PLUS, KC_ASTR, KC_MINS, _______,
    KC_COLN, KC_4,    KC_5,    KC_6,    KC_EQL,                    KC_AMPR, KC_GRV,  KC_UNDS, KC_QUOT, KC_DQT,
    ZE_SFT,  KC_1,    KC_2,    KC_3,    _______, _______, _______, _______, KC_EXLM, KC_HASH, KC_PERC, SFTCRC,
    _______, _______, _______, ADJUST,  _______, _______, _______, _______, _______, _______, _______, _______),

  /* Layer 3 (ADJUST)
     .-----.-----.-----.-----.-----.           .-----.-----.-----.-----.-----.
     |     |     |     |     |     |           |     | F7  | F8  | F9  | F10 |
     .-----.-----.-----.-----.-----.           .-----.-----.-----.-----.-----.
     |     |     |     |     |     |           |     | F4  | F5  | F6  | F11 |
     .-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.
     |     |     |     |     |     |     |     |     | F1  | F2  | F3  | F12 |
     .-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.
     |     |     |     |     |     |     |     |     |     |     |     |     |
     .-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.
  */
  [_ADJUST] = LAYOUT(
    _______, _______, _______, _______, AC_TOGG,                   _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,
    _______, _______, _______, _______, _______,                   _______, KC_F4,   KC_F5,   KC_F6,   KC_F11,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_F1,   KC_F2,   KC_F3,   KC_F12,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______)
};

/// Macro definitions

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case RARR:
    if (record->event.pressed) SEND_STRING("->");  break;
  case LARR:
    if (record->event.pressed) SEND_STRING("<-");  break;
  case LBND:
    if (record->event.pressed) SEND_STRING("=<<"); break;
  case RBND:
    if (record->event.pressed) SEND_STRING(">>="); break;
  case APP:
    if (record->event.pressed) SEND_STRING("<*>"); break;
  case RAPP:
    if (record->event.pressed) SEND_STRING("*>");  break;
  case LAPP:
    if (record->event.pressed) SEND_STRING("<*");  break;
  case FMAP:
    if (record->event.pressed) SEND_STRING("<$>"); break;
  case PAMF:
    if (record->event.pressed) SEND_STRING("<&>"); break;
  case AALT:
    if (record->event.pressed) SEND_STRING("<|>"); break;
  case IMPLS:
    if (record->event.pressed) SEND_STRING("=>");  break;
  case DCOL:
    if (record->event.pressed) SEND_STRING("::");  break;
  }
  return true;
};

//// Tap dance definitions

// Heavily inspired by:
//
//     https://docs.qmk.fm/?ref=blog.splitkb.com#/feature_tap_dance?id=example-4

typedef enum {
  TD_NONE,
  TD_UNKNOWN,
  TD_SINGLE_TAP,
  TD_SINGLE_HOLD,
  TD_DOUBLE_TAP,
} td_state_t;

typedef struct {
  bool is_press_action;
  td_state_t state;
} td_tap_t;

// Return an integer that corresponds to what kind of tap dance should
// be executed.
//
// Interrupted: If the state of a dance is "interrupted", that means
//  that another key has been hit under the tapping term.
//
// Pressed: Whether or not the key is still being pressed. If this value
//  is true, that means the tapping term has ended, but the key is still
//  being pressed down. This generally means the key is being "held".
td_state_t cur_dance(tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->pressed)         return TD_SINGLE_HOLD;
    else                        return TD_SINGLE_TAP;
  } else if (state->count == 2) return TD_DOUBLE_TAP;
  else                          return TD_UNKNOWN;
}

//// ALT_BR

static td_tap_t alt_br_state = {
  .is_press_action = true,
  .state = TD_NONE
};

void lalt_br_finished(tap_dance_state_t *state, void *user_data) {
  alt_br_state.state = cur_dance(state);
  switch (alt_br_state.state) {
  case TD_SINGLE_TAP:  register_code(KC_LBRC); break;
  case TD_SINGLE_HOLD: register_code(KC_LALT); break;
  case TD_DOUBLE_TAP:  register_code(KC_RBRC); break;
  default:             break;
  }
}

void lalt_br_reset(tap_dance_state_t *state, void *user_data) {
  switch (alt_br_state.state) {
  case TD_SINGLE_TAP:  unregister_code(KC_LBRC); break;
  case TD_SINGLE_HOLD: unregister_code(KC_LALT); break;
  case TD_DOUBLE_TAP:  unregister_code(KC_RBRC); break;
  default:             break;
  }
  alt_br_state.state = TD_NONE;
}

//// LCTL_PR

static td_tap_t lctl_pr_state = {
  .is_press_action = true,
  .state = TD_NONE
};

void lctl_pr_finished(tap_dance_state_t *state, void *user_data) {
  lctl_pr_state.state = cur_dance(state);
  switch (lctl_pr_state.state) {
  case TD_SINGLE_TAP:  register_code16(KC_LPRN); break;
  case TD_SINGLE_HOLD: register_code(KC_LCTL);   break;
  case TD_DOUBLE_TAP:  register_code16(KC_RPRN); break;
  default:             break;
  }
}

void lctl_pr_reset(tap_dance_state_t *state, void *user_data) {
  switch (lctl_pr_state.state) {
  case TD_SINGLE_TAP:  unregister_code16(KC_LPRN); break;
  case TD_SINGLE_HOLD: unregister_code(KC_LCTL);   break;
  case TD_DOUBLE_TAP:  unregister_code16(KC_RPRN); break;
  default:             break;
  }
  lctl_pr_state.state = TD_NONE;
}

//// SFT_CI

static td_tap_t lsft_ci_state = {
  .is_press_action = true,
  .state = TD_NONE
};

void lsft_ci_finished(tap_dance_state_t *state, void *user_data) {
  lsft_ci_state.state = cur_dance(state);
  switch (lsft_ci_state.state) {
  case TD_SINGLE_TAP:  register_code16(KC_CIRC); break;
  case TD_SINGLE_HOLD: register_code(KC_LSFT);   break;
  default:             break;
  }
}

void lsft_ci_reset(tap_dance_state_t *state, void *user_data) {
  switch (lsft_ci_state.state) {
  case TD_SINGLE_TAP:  unregister_code16(KC_CIRC); break;
  case TD_SINGLE_HOLD: unregister_code(KC_LSFT);   break;
  default:             break;
  }
  lsft_ci_state.state = TD_NONE;
}

//// SFT_EX

static td_tap_t lsft_ex_state = {
  .is_press_action = true,
  .state = TD_NONE
};

void lsft_ex_finished(tap_dance_state_t *state, void *user_data) {
  lsft_ex_state.state = cur_dance(state);
  switch (lsft_ex_state.state) {
  case TD_SINGLE_TAP:  register_code16(KC_EXLM); break;
  case TD_SINGLE_HOLD: register_code(KC_LSFT);   break;
  default:             break;
  }
}

void lsft_ex_reset(tap_dance_state_t *state, void *user_data) {
  switch (lsft_ex_state.state) {
  case TD_SINGLE_TAP:  unregister_code16(KC_EXLM); break;
  case TD_SINGLE_HOLD: unregister_code(KC_LSFT);   break;
  default:             break;
  }
  lsft_ex_state.state = TD_NONE;
}

//// Actually define the tap-dance actions

tap_dance_action_t tap_dance_actions[] = {
  [ALT_BR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lalt_br_finished, lalt_br_reset),
  [CTL_PR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lctl_pr_finished, lctl_pr_reset),
  [SFT_CI] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lsft_ci_finished, lsft_ci_reset),
  [SFT_EX] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lsft_ex_finished, lsft_ex_reset),
};
