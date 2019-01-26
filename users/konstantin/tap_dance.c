#include "tap_dance.h"
#include "konstantin.h"

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
  if ((state->count == 1 || state->count >= 3) && !td_fn_rctrl_data.fn_on) {
    layer_off(L_FN);
  }
  if (state->count >= 2) {
    unregister_code(KC_RCTL);
  }
  td_fn_rctrl_data.started = false;
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

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_DESKTOP] = ACTION_TAP_DANCE_DOUBLE(LCTL(LGUI(KC_D)), LCTL(LGUI(KC_F4))), // Add/close virtual desktop

  [TD_RAL_LAL] = ACTION_TAP_DANCE_DOUBLE_MODS(KC_RALT, KC_LALT),
  [TD_RAL_RGU] = ACTION_TAP_DANCE_DOUBLE_MODS(KC_RALT, KC_RGUI),
  [TD_RCT_RSF] = ACTION_TAP_DANCE_DOUBLE_MODS(KC_RCTL, KC_RSFT),

  [TD_FN_RCTL] = ACTION_TAP_DANCE_FN_ADVANCED(td_fn_rctrl_each, NULL, td_fn_rctrl_reset),
  [TD_LSFT_FN] = ACTION_TAP_DANCE_FN_ADVANCED(td_lsft_fn_each, NULL, td_lsft_fn_reset),
};
