#include QMK_KEYBOARD_H

#define TOP     LCTL(KC_HOME)
#define BOTTOM  LCTL(KC_END)
#define DSKTP_L LCTL(LGUI(KC_LEFT))
#define DSKTP_R LCTL(LGUI(KC_RGHT))

#define FN      MO(L_FN)
#define FN_FNLK TT(L_FN)
#define LCT_CPS LCTL_T(KC_CAPS)

#define DESKTOP TD(TD_DESKTOP)
#define LSFT_FN TD(TD_LSFT_FN)
#define RAL_RGU TD(TD_RAL_RGU)

enum layers {
  L_BASE,
  L_FN,
};

enum custom_keycodes {
  CLEAR = SAFE_RANGE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case CLEAR:
    if (record->event.pressed) {
      SEND_STRING(SS_LCTRL("a") SS_TAP(X_DELETE));
    }
    return false;

  default:
    return true;
  }
}

void td_lsft_fn_each(qk_tap_dance_state_t *state, void *user_data) {
  // Single tap → LShift, double tap → Fn, triple tap etc. → Fn+LShift
  if (state->count == 1 || state->count == 3) {
    register_code(KC_LSFT);
  } else if (state->count == 2) {
    unregister_code(KC_LSFT);
    // Prevent tap dance from sending LShift as a weak mod
    state->weak_mods &= ~MOD_BIT(KC_LSFT);
    layer_on(L_FN);
  }
}

void td_lsft_fn_reset(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1 || state->count >= 3) {
    unregister_code(KC_LSFT);
  }
  if (state->count >= 2) {
    layer_off(L_FN);
  }
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
  if (state->count == 1 || state->count >= 3) {
    unregister_code(mods->kc1);
  }
  if (state->count >= 2) {
    unregister_code(mods->kc2);
  }
}

enum tap_dance {
  TD_DESKTOP,
  TD_LSFT_FN,
  TD_RAL_RGU,
};

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_DESKTOP] = ACTION_TAP_DANCE_DOUBLE(LCTL(LGUI(KC_D)), LCTL(LGUI(KC_F4))), // Add/close virtual desktop
  [TD_LSFT_FN] = ACTION_TAP_DANCE_FN_ADVANCED(td_lsft_fn_each, NULL, td_lsft_fn_reset),
  [TD_RAL_RGU] = ACTION_TAP_DANCE_DOUBLE_MODS(KC_RALT, KC_RGUI),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Base layer
   * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
   * │Esc│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ \ │ ` │
   * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
   * │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │Bspc │
   * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
   * │LCtCps│ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │ Enter  │
   * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤
   * │LShiftFn│ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │RShift│FnL│
   * └─────┬──┴┬──┴──┬┴───┴───┴───┴───┴───┴───┴──┬┴───┴┬───┬─┴───┘
   *       │LGu│LAlt │           Space           │RAlGu│RCt│
   *       └───┴─────┴───────────────────────────┴─────┴───┘
   */
  [L_BASE] = LAYOUT(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_GRV,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
    LCT_CPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
    LSFT_FN, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, FN_FNLK,
    XXXXXXX, KC_LGUI, KC_LALT,                   KC_SPC,                    RAL_RGU, KC_RCTL, XXXXXXX
  ),

  /* Function layer
   * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
   * │   │F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│F11│F12│PSc│Ins│
   * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
   * │     │Hom│ ↑ │End│PgU│Top│   │UCM│   │M1 │M↑ │M2 │M3 │ Del │
   * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
   * │      │ A │ S │ D │PgD│Btm│   │   │MW↑│M← │M↓ │M→ │        │
   * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤
   * │        │Mut│VoD│VoU│Ply│Prv│Nxt│MW←│MW→│M4 │M5 │      │   │
   * └─────┬──┴┬──┴──┬┴───┴───┴───┴───┴───┴───┴──┬┴───┴┬───┬─┴───┘
   *       │Dst│Dstp←│            MW↓            │Dstp→│App│
   *       └───┴─────┴───────────────────────────┴─────┴───┘
   */
  [L_FN] = LAYOUT(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_INS,
    _______, KC_HOME, KC_UP,   KC_END,  KC_PGUP, TOP,     _______, UC_MOD,  _______, KC_BTN1, KC_MS_U, KC_BTN2, KC_BTN3, KC_DEL,
    _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, BOTTOM,  _______, _______, KC_WH_U, KC_MS_L, KC_MS_D, KC_MS_R, _______,
    _______, KC_MUTE, KC_VOLD, KC_VOLU, KC_MPLY, KC_MPRV, KC_MNXT, KC_WH_L, KC_WH_R, KC_BTN4, KC_BTN5, _______, _______,
    XXXXXXX, DESKTOP, DSKTP_L,                   KC_WH_D,                   DSKTP_R, KC_APP,  XXXXXXX
  ),
};
