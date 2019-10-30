#include "tominabox1.h"

void dance_cln_finished (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code16(S(KC_2));
    } else {
        SEND_STRING("tom.campie@gmail.com");
    }
}

void dance_cln_reset (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code16(S(KC_2));
    } else {
    }
}

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
    [KC_EMAIL] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_cln_finished, dance_cln_reset),
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
        #ifdef KEYBOARD_lazydesigners_dimple
        switch (biton32(state)) {
          case _GAMER:
            rgblight_enable_noeeprom();
            rgblight_mode(0);
            rgblight_sethsv_noeeprom(190, 200, 170);
            break;
          default:
            rgblight_disable();
            break;
        }
        #endif // dimple
  return layer_state_set_keymap (state);
}
