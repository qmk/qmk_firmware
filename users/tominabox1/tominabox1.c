#include "tominabox1.h"

void dance_esc_tab (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed)  return register_code16(KC_ESC);
    else return register_code16(KC_TAB);
  }
}

void dance_esc_tab_reset (qk_tap_dance_state_t *state, void *user_data) {
        unregister_code16(KC_ESC);
        unregister_code16(KC_TAB);
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_TAB_ESC] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_esc_tab, dance_esc_tab_reset),
};

uint16_t get_tapping_term(uint16_t keycode) {
    switch (keycode) {
        case LSFT_T(KC_CAPS):
            return 250;
        case KC_ENT_LOW:
            return 150;
        case KC_SPC_RSE:
            return 270;
        case LCTL_T(KC_TAB):
            return 200;
        default:
            return TAPPING_TERM;
    }
};

__attribute__ ((weak))
layer_state_t layer_state_set_keymap (layer_state_t state) {
  return state;
}

layer_state_t layer_state_set_user (layer_state_t state) {
  state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
  return layer_state_set_keymap (state);
}

enum combo_events {
  EMAIL,
  COMBO_RESET,
  CAPS_COMBO
};

const uint16_t PROGMEM email[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM combo_reset[] = {KC_W, KC_ESC, COMBO_END};
const uint16_t PROGMEM caps_combo[] = {KC_K, KC_V, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [EMAIL] = COMBO_ACTION(email),
  [COMBO_RESET] = COMBO_ACTION(combo_reset),
  [CAPS_COMBO] = COMBO_ACTION(caps_combo),
};

__attribute__ ((weak))
void process_combo_keymap(uint8_t combo_index, bool pressed) {
}

void process_combo_event(uint8_t combo_index, bool pressed) {
  switch(combo_index) {
    case EMAIL:
    if (pressed) {
      SEND_STRING("tom.campie@gmail.com");
    }
    break;
    case COMBO_RESET:
    if (pressed) {
      reset_keyboard();
    }
    break;
    case CAPS_COMBO:
    if (pressed) {
      register_code16(KC_CAPS);
      wait_ms(100);
      unregister_code16(KC_CAPS);
    }
    break;
  }
}
