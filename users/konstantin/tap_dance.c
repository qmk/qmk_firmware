#include "tap_dance.h"
#include "konstantin.h"

#define ACTION_TAP_DANCE_DOUBLE_MODS(mod1, mod2) {                    \
    .fn        = { td_double_mods_each, NULL, td_double_mods_reset }, \
    .user_data = &(qk_tap_dance_pair_t){ mod1, mod2 },                \
  }

void td_double_mods_each(qk_tap_dance_state_t *state, void *user_data) {
  qk_tap_dance_pair_t *data = (qk_tap_dance_pair_t *)user_data;
  // Single tap → mod1, double tap → mod2, triple tap etc. → mod1+mod2
  if (state->count == 1 || state->count == 3) {
    register_code(data->kc1);
  } else if (state->count == 2) {
    unregister_code(data->kc1);
    register_code(data->kc2);
  }
  // Prevent tap dance from sending the mods as weak mods
  state->weak_mods &= ~(MOD_BIT(data->kc1) | MOD_BIT(data->kc2));
}

void td_double_mods_reset(qk_tap_dance_state_t *state, void *user_data) {
  qk_tap_dance_pair_t *data = (qk_tap_dance_pair_t *)user_data;
  if (state->count == 1 || state->count >= 3) {
    unregister_code(data->kc1);
  }
  if (state->count >= 2) {
    unregister_code(data->kc2);
  }
}

#define ACTION_TAP_DANCE_MOD_LAYER(mod, layer) {                  \
    .fn        = { td_mod_layer_each, NULL, td_mod_layer_reset }, \
    .user_data = &(qk_tap_dance_dual_role_t){ mod, layer },       \
  }

void td_mod_layer_each(qk_tap_dance_state_t *state, void *user_data) {
  qk_tap_dance_dual_role_t *data = (qk_tap_dance_dual_role_t *)user_data;
  // Single tap → mod, double tap → layer, triple tap etc. → mod+layer
  if (state->count == 1 || state->count == 3) {
    register_code(data->kc);
  } else if (state->count == 2) {
    unregister_code(data->kc);
    // Prevent tap dance from sending the mod as a weak mod
    state->weak_mods &= ~MOD_BIT(data->kc);
    layer_on(data->layer);
  }
}

void td_mod_layer_reset(qk_tap_dance_state_t *state, void *user_data) {
  qk_tap_dance_dual_role_t *data = (qk_tap_dance_dual_role_t *)user_data;
  if (state->count == 1 || state->count >= 3) {
    unregister_code(data->kc);
  }
  if (state->count >= 2) {
    layer_off(data->layer);
  }
}

struct {
  bool fn_on;  // Layer state when tap dance started
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

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_DST_A_R] = ACTION_TAP_DANCE_DOUBLE(DST_ADD, DST_REM),

  [TD_RAL_LAL] = ACTION_TAP_DANCE_DOUBLE_MODS(KC_RALT, KC_LALT),
  [TD_RAL_RGU] = ACTION_TAP_DANCE_DOUBLE_MODS(KC_RALT, KC_RGUI),
  [TD_RCT_RSF] = ACTION_TAP_DANCE_DOUBLE_MODS(KC_RCTL, KC_RSFT),

  [TD_LSFT_FN] = ACTION_TAP_DANCE_MOD_LAYER(KC_LSFT, L_FN),
  [TD_RCTL_FN] = ACTION_TAP_DANCE_MOD_LAYER(KC_RCTL, L_FN),
  [TD_FN_RCTL] = ACTION_TAP_DANCE_FN_ADVANCED(td_fn_rctrl_each, NULL, td_fn_rctrl_reset),
};
