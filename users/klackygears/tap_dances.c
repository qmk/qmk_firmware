#include "tap_dances.h"

/*
void macroTogKey(qk_tap_dance_state_t *state, void *user_data) {
  keyrecord_t kr;

  if (state->count == 1)
  {
    kr.event.pressed = false;
    process_record_dynamic_macro( DYN_MACRO_PLAY1, &kr );
  }
  else if (state->count == 2)
  {
    kr.event.pressed = true;
    process_record_dynamic_macro( DYN_REC_STOP, &kr );
  }
  else if (state->count == 3)
  {
    kr.event.pressed = false;
    process_record_dynamic_macro( DYN_REC_START1, &kr );
  }
}

void macroTogKey2(qk_tap_dance_state_t *state, void *user_data) {
  keyrecord_t kr;

  if (state->count == 1)
  {
    kr.event.pressed = false;
    process_record_dynamic_macro( DYN_MACRO_PLAY2, &kr );
  }
  else if (state->count == 2)
  {
    kr.event.pressed = true;
    process_record_dynamic_macro( DYN_REC_STOP, &kr );
  }
  else if (state->count == 3)
  {
    kr.event.pressed = false;
    process_record_dynamic_macro( DYN_REC_START2, &kr );
  }
}
*/

void pstinsrt(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count > 1) {
        register_code(KC_LALT);
        tap_code(KC_I);
        tap_code(KC_E);
        unregister_code(KC_LALT);
    } else {
        tap_code16(C(KC_V));
    }
    reset_tap_dance(state);
}

void ccopy(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count > 1) {
        tap_code16(C(KC_X));

        // SEND_STRING( SS_DOWN(KC_LCTL) SS_TAP(KC_X) SS_UP(KC_LCTL));
    } else {
        tap_code16(C(KC_C));
    }
    reset_tap_dance(state);
}

void pstspecial(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count > 1) {
        register_code(KC_LALT);
        tap_code(KC_E);
        tap_code(KC_S);
        unregister_code(KC_LALT);
        tap_code(KC_V);
    } else {
        register_code(KC_LALT);
        tap_code(KC_E);
        tap_code(KC_S);
        unregister_code(KC_LALT);
        tap_code(KC_T);
    }
    reset_tap_dance(state);
}

void deldel(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count > 1) {
        register_code(KC_LALT);
        tap_code(KC_E);
        tap_code(KC_D);
        unregister_code(KC_LALT);
    } else {
        tap_code(KC_DEL);
    }
    reset_tap_dance(state);
}

void findreplace(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count > 1) {
        tap_code16(C(KC_H));
    } else {
        tap_code16(C(KC_F));
    }
    reset_tap_dance(state);
}

void cyclawin(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count > 1) {
        tap_code16(C(S(KC_F6)));
    } else {
        tap_code16(C(KC_F6));
    }
    reset_tap_dance(state);
}

void SCRNSNP(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count > 1) {
        tap_code16(A(KC_PSCR));
    } else {
        tap_code(KC_LGUI);
        tap_code(KC_S);
        tap_code(KC_N);
        tap_code16(C(KC_N));
    }
    reset_tap_dance(state);
}

void mcccpy(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count > 1) {
        tap_code16(G(KC_X));
    } else {
        tap_code16(G(KC_C));
    }
    reset_tap_dance(state);
}

void mcpstin(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count > 1) {
        tap_code16(G(KC_I));
    } else {
        tap_code16(G(KC_V));
    }
    reset_tap_dance(state);
}

void enttab(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count > 1) {
        tap_code(KC_ENT);
    } else {
        tap_code(KC_TAB);
    }
    reset_tap_dance(state);
}

void rgb_toggle(qk_tap_dance_state_t *state, void *user_data) {
#ifdef RGBLIGHT_ENABLE
    if (state->count == 1) {
        rgblight_step();
    } else {
        rgblight_increase_hue();
    }
#endif
}

// Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_PSTI] = ACTION_TAP_DANCE_FN(pstinsrt),
    [TD_PTSP] = ACTION_TAP_DANCE_FN(pstspecial),
    [TD_FNDR] = ACTION_TAP_DANCE_FN(findreplace),
    [TD_CCPY] = ACTION_TAP_DANCE_FN(ccopy),
    [TD_DDEL] = ACTION_TAP_DANCE_FN(deldel),
    [TD_ACCW] = ACTION_TAP_DANCE_FN(cyclawin),
    [TD_CAPESC] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS),
    [TD_DTEX] = ACTION_TAP_DANCE_DOUBLE(KC_DOT, KC_EXLM),
    [TD_COMQUES] = ACTION_TAP_DANCE_DOUBLE(KC_COMM, KC_QUES),
    [TD_MINPLS] = ACTION_TAP_DANCE_DOUBLE(KC_PMNS, KC_PPLS),
    [TD_DIVMLT] = ACTION_TAP_DANCE_DOUBLE(KC_PSLS, KC_PAST),
    [TD_DOTEQL] = ACTION_TAP_DANCE_DOUBLE(KC_DOT, KC_EQL),
    [TD_SCNSP] = ACTION_TAP_DANCE_FN(SCRNSNP),
    [TD_MCCCPY] = ACTION_TAP_DANCE_FN(mcccpy),
    [TD_MCPSTIN] = ACTION_TAP_DANCE_FN(mcpstin),
    [TD_ENTAB] = ACTION_TAP_DANCE_FN(enttab),
    [TD_XSPC] = ACTION_TAP_DANCE_DOUBLE(KC_SPACE, KC_X),
    [TD_RGB] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rgb_toggle, NULL)
};
