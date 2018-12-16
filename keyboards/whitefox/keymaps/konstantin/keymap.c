#include QMK_KEYBOARD_H

#define TOP     LCTL(KC_HOME)
#define BOTTOM  LCTL(KC_END)
#define DSKTP_L LCTL(LGUI(KC_LEFT))
#define DSKTP_R LCTL(LGUI(KC_RGHT))

#define FN      MO(L_FN)
#define FN_CAPS LT(L_FN, KC_CAPS)
#define FN_FNLK TT(L_FN)

#define DESKTOP TD(TD_DESKTOP)
#define FN_RCTL TD(TD_FN_RCTL)
#define RAL_LAL TD(TD_RAL_LAL)
#define RAL_RGU TD(TD_RAL_RGU)
#define RCT_RSF TD(TD_RCT_RSF)

#define COMMA   UC(0x002C)
#define L_PAREN UC(0x0028)
#define R_PAREN UC(0x0029)
#define EQUALS  UC(0x003D)
#define TIMES   UC(0x00D7)
#define DIVIDE  UC(0x00F7)
#define MINUS   UC(0x2212)

void eeconfig_init_user(void) {
  set_unicode_input_mode(UC_WINC);
}

enum layers {
  L_BASE,
  L_FN,
  L_NUMPAD,
};

enum custom_keycodes {
  CLEAR = SAFE_RANGE,
  NUMPAD,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case CLEAR:
    if (record->event.pressed) {
      SEND_STRING(SS_LCTRL("a") SS_TAP(X_DELETE));
    }
    return false;

  case NUMPAD:
    if (record->event.pressed) {
      layer_invert(L_NUMPAD);
      bool num_lock = host_keyboard_leds() & 1<<USB_LED_NUM_LOCK;
      if (num_lock != (bool)IS_LAYER_ON(L_NUMPAD)) {
        tap_code(KC_NLCK); // Toggle Num Lock to match layer state.
      }
    }
    return false;

  default:
    return true;
  }
}

struct {
  bool fn_on; // Layer state when tap dance started
  bool started;
} td_fn_rctrl_data;

void td_fn_rctrl_each(qk_tap_dance_state_t *state, void *user_data) {
  if (!td_fn_rctrl_data.started) {
    td_fn_rctrl_data.fn_on = IS_LAYER_ON(L_FN);
    td_fn_rctrl_data.started = true;
  }
  // Single tap → Fn, double tap → RCtrl, triple tap etc. → Fn+RCtrl
  if (state->count == 1 || state->count == 3) {
    layer_on(L_FN);
  } else if (state->count == 2) {
    if (!td_fn_rctrl_data.fn_on) {
      layer_off(L_FN);
    }
    register_code(KC_RCTL);
  }
}

void td_fn_rctrl_reset(qk_tap_dance_state_t *state, void *user_data) {
  if ((state->count == 1 || state->count > 2) && !td_fn_rctrl_data.fn_on) {
    layer_off(L_FN);
  }
  if (state->count >= 2) {
    unregister_code(KC_RCTL);
  }
  td_fn_rctrl_data.started = false;
}

#define ACTION_TAP_DANCE_DOUBLE_MODS(mod1, mod2) { \
    .fn = { td_double_mods_each, NULL, td_double_mods_reset }, \
    .user_data = &(qk_tap_dance_pair_t){ mod1, mod2 }, \
  }

void td_double_mods_each(qk_tap_dance_state_t *state, void *user_data) {
  qk_tap_dance_pair_t *mods = (qk_tap_dance_pair_t *)user_data;
  // Single tap → mod1, double tap → mod2, triple tap etc. → mod1+mod2
  if (state->count == 1 || state->count == 3) {
    register_code(mods->kc1);
  } else if (state->count == 2) {
    unregister_code(mods->kc1);
    register_code(mods->kc2);
  }
  // Prevent tap dance from sending kc1 and kc2 as weak mods
  state->weak_mods &= ~(MOD_BIT(mods->kc1) | MOD_BIT(mods->kc2));
}

void td_double_mods_reset(qk_tap_dance_state_t *state, void *user_data) {
  qk_tap_dance_pair_t *mods = (qk_tap_dance_pair_t *)user_data;
  if (state->count == 1 || state->count > 2) {
    unregister_code(mods->kc1);
  }
  if (state->count >= 2) {
    unregister_code(mods->kc2);
  }
}

enum tap_dance {
  TD_DESKTOP,
  TD_FN_RCTL,
  TD_RAL_LAL,
  TD_RAL_RGU,
  TD_RCT_RSF,
};

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_DESKTOP] = ACTION_TAP_DANCE_DOUBLE(LCTL(LGUI(KC_D)), LCTL(LGUI(KC_F4))), // Add/close virtual desktop
  [TD_FN_RCTL] = ACTION_TAP_DANCE_FN_ADVANCED(td_fn_rctrl_each, NULL, td_fn_rctrl_reset),
  [TD_RAL_LAL] = ACTION_TAP_DANCE_DOUBLE_MODS(KC_RALT, KC_LALT),
  [TD_RAL_RGU] = ACTION_TAP_DANCE_DOUBLE_MODS(KC_RALT, KC_RGUI),
  [TD_RCT_RSF] = ACTION_TAP_DANCE_DOUBLE_MODS(KC_RCTL, KC_RSFT),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Base layer
   * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
   * │Esc│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ \ │ ` │PSc│
   * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┼───┤
   * │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │Bspc │Del│
   * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
   * │FnCaps│ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │ Enter  │PgU│
   * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
   * │ LShift │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │CtlSft│ ↑ │PgD│
   * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬─┬───┼───┼───┤
   * │LCtl│LGui│LAlt│         Space          │AlGu│FnLk│ │ ← │ ↓ │ → │
   * └────┴────┴────┴────────────────────────┴────┴────┘ └───┴───┴───┘
   */
  [L_BASE] = LAYOUT_truefox( \
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_GRV,  KC_PSCR, \
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,          KC_DEL,  \
    FN_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_PGUP, \
    KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RCT_RSF,          KC_UP,   KC_PGDN, \
    KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                    RAL_RGU, FN_FNLK,                   KC_LEFT, KC_DOWN, KC_RGHT  \
  ),

  /* Function layer
   * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
   * │   │F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│F11│F12│Num│Scr│Pau│
   * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┼───┤
   * │ M4  │M2 │M↑ │M1 │M3 │M5 │   │   │   │Stp│Ply│Prv│Nxt│Clear│Ins│
   * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
   * │      │M← │M↓ │M→ │MW↑│   │   │   │   │   │   │   │        │Top│
   * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
   * │        │MA0│MA2│MW←│MW→│   │   │   │VoD│VoU│Mut│ App  │PgU│Btm│
   * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬─┬───┼───┼───┤
   * │    │Dstp│Dst←│          MW↓           │Dst→│    │ │Hom│PgD│End│
   * └────┴────┴────┴────────────────────────┴────┴────┘ └───┴───┴───┘
   */
  [L_FN] = LAYOUT_truefox( \
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  NUMPAD,  KC_SLCK, KC_PAUS, \
    KC_BTN4, KC_BTN2, KC_MS_U, KC_BTN1, KC_BTN3, KC_BTN5, _______, _______, _______, KC_MSTP, KC_MPLY, KC_MPRV, KC_MNXT, CLEAR,            KC_INS,  \
    _______, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_U, _______, _______, _______, _______, _______, _______, _______,          _______,          TOP,     \
    _______,          KC_ACL0, KC_ACL2, KC_WH_L, KC_WH_R, _______, _______, _______, KC_VOLD, KC_VOLU, KC_MUTE, KC_APP,           KC_PGUP, BOTTOM,  \
    _______, DESKTOP, DSKTP_L,                            KC_WH_D,                   DSKTP_R, _______,                   KC_HOME, KC_PGDN, KC_END   \
  ),

  /* Numpad layer
   * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
   * │Num│   │   │   │   │   │   │P7 │P8 │P9 │P- │ − │ = │Num│   │   │
   * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┼───┤
   * │     │   │   │   │   │   │   │P4 │P5 │P6 │P+ │ ( │ ) │     │   │
   * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
   * │      │   │   │   │   │   │   │P1 │P2 │P3 │P* │ × │ PEnter │   │
   * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
   * │        │   │   │   │   │   │P0 │P0 │ , │P. │P/ │  ÷   │   │   │
   * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬─┬───┼───┼───┤
   * │    │    │    │                        │    │    │ │   │   │   │
   * └────┴────┴────┴────────────────────────┴────┴────┘ └───┴───┴───┘
   */
  [L_NUMPAD] = LAYOUT_truefox( \
    NUMPAD,  _______, _______, _______, _______, _______, _______, KC_P7,   KC_P8,   KC_P9,   KC_PMNS, MINUS,   EQUALS,  NUMPAD,  _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, KC_P4,   KC_P5,   KC_P6,   KC_PPLS, L_PAREN, R_PAREN, _______,          _______, \
    _______, _______, _______, _______, _______, _______, _______, KC_P1,   KC_P2,   KC_P3,   KC_PAST, TIMES,            KC_PENT,          _______, \
    _______,          _______, _______, _______, _______, _______, KC_P0,   KC_P0,   COMMA,   KC_PDOT, KC_PSLS, DIVIDE,           _______, _______, \
    _______, _______, _______,                            _______,                   _______, _______,                   _______, _______, _______  \
  ),
};
