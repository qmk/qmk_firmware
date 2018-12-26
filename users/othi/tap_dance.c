#include "othi.h"
void dance_CTL_NM_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
	set_oneshot_mods(MOD_LCTL);
  } else {
    register_code (KC_LCTL);
	layer_on(NM_MODE);
  }
}

void dance_CTL_NM_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (KC_LCTL);
  } else {
    unregister_code (KC_LCTL);
	layer_off(NM_MODE);
  }
}

void dance_GUI_NM_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
	register_code (KC_LGUI);
  } else {
    register_code (KC_LGUI);
	layer_on(NM_MODE);
  }
}

void dance_GUI_NM_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (KC_LGUI);
  } else {
    unregister_code (KC_LGUI);
	layer_off(NM_MODE);
  }
}

void dance_ALT_NM_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
	register_code (KC_LALT);
  } else {
    register_code (KC_LALT);
	layer_on(NM_MODE);
  }
}

void dance_ALT_NM_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (KC_LALT);
  } else {
    unregister_code (KC_LALT);
	layer_off(NM_MODE);
  }
}

void dance_SFT_NM_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
	register_code (KC_LSFT);
	set_oneshot_mods(MOD_LSFT);
  } else {
    register_code (KC_LSFT);
	layer_on(NM_MODE);
  }
}

void dance_SFT_NM_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (KC_LSFT);
  } else {
    unregister_code (KC_LSFT);
	layer_off(NM_MODE);
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
 [CTL_NM] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_CTL_NM_finished, dance_CTL_NM_reset),
 [GUI_NM] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_GUI_NM_finished, dance_GUI_NM_reset),
 [ALT_NM] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_ALT_NM_finished, dance_ALT_NM_reset),
 [SFT_NM] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_SFT_NM_finished, dance_SFT_NM_reset)
};

