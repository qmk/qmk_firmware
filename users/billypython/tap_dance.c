#include "tap_dance.h"

#define ACTION_TAP_DANCE_DOUBLE_MODS(mod1, mod2) { \
    .fn = { td_double_mods_each, NULL, td_double_mods_reset }, \
    .user_data = &(tap_dance_pair_t){ mod1, mod2 }, \
  }

void td_double_mods_each(tap_dance_state_t *state, void *user_data) {
  tap_dance_pair_t *mods = (tap_dance_pair_t *)user_data;
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

void td_double_mods_reset(tap_dance_state_t *state, void *user_data) {
  tap_dance_pair_t *mods = (tap_dance_pair_t *)user_data;
  if (state->count == 1 || state->count >= 3) {
    unregister_code(mods->kc1);
  }
  if (state->count >= 2) {
    unregister_code(mods->kc2);
  }
}

tap_dance_action_t tap_dance_actions[] = {
  [TD_RSF_RCT] = ACTION_TAP_DANCE_DOUBLE_MODS(KC_RSFT, KC_RCTL),
};
