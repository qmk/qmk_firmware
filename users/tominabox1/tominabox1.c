#include "tominabox1.h"
__attribute__ ((weak))
void keyboard_post_init_keymap(void) {
}

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  //debug_matrix=true;
  debug_keyboard=true;
  //debug_mouse=true;
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
    [TD_TAB_ESC]   = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_esc_tab, dance_esc_tab_reset),
    [TD_Q_ESC]     = ACTION_TAP_DANCE_DOUBLE(KC_Q, KC_ESC),
    [TD_QUES_ENT]  = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, KC_ENT),
    [TD_CTRL_Z]    = ACTION_TAP_DANCE_DOUBLE(KC_Z, LCTL(KC_Z)),
    [TD_CTRL_Y]    = ACTION_TAP_DANCE_DOUBLE(KC_Y, LCTL(KC_Y)),
    [TD_CTRL_C]    = ACTION_TAP_DANCE_DOUBLE(KC_C, LCTL(KC_C)),
    [TD_CTRL_V]    = ACTION_TAP_DANCE_DOUBLE(KC_V, LCTL(KC_V)),
    [TD_CTRL_A]    = ACTION_TAP_DANCE_DOUBLE(KC_A, LCTL(KC_A)),
    [TD_O_BSLS]    = ACTION_TAP_DANCE_DOUBLE(KC_O, KC_BSLS),
    [TD_QUOTE]     = ACTION_TAP_DANCE_DOUBLE(KC_QUOTE, KC_DQT),
    [TD_QCOL]      = ACTION_TAP_DANCE_DOUBLE(KC_QUOTE, KC_SCLN),
    [TD_WTAB]      = ACTION_TAP_DANCE_DOUBLE(KC_W, KC_TAB)
};

uint16_t get_tapping_term(uint16_t keycode) {
    switch (keycode) {
        case RSFT_T(KC_DOT):
            return 150;
        case KC_ENT_LOW:
            return 150;
        case LT(_LOWER, KC_SPC):
            return 270;
        case LCTL_T(KC_TAB):
            return 120;
        case TD(TD_WTAB):
            return 120;
        case LCTL_T(KC_A):
            return 250;
        case LSFT_T(KC_Z):
            return 120;
        case TD(TD_O_BSLS):
            return 100;
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
  // EMAIL,
  COMBO_RESET,
  CAPS_COMBO,
  CRET,
  COMBOPP,
  COMBO_NEXT,
  COMBO_PREV,
  // COMBO_BACK,
  //COMBO_ARTAB,
  COMBO_NUMBAK,
  COMBO_ESC,
  COMBO_TAB,
  COMBO_DELETE,
  COMBO_ALT
};

// const uint16_t PROGMEM email[] = {TD(TD_Q_ESC), TD(TD_WTAB), COMBO_END};
const uint16_t PROGMEM combo_reset[] = {TD(TD_Q_ESC), KC_F, COMBO_END};
#ifdef KEYBOARD_crkbd_rev1
const uint16_t PROGMEM caps_combo[] = {KC_M, KC_V, COMBO_END};
#endif
#ifndef KEYBOARD_crkbd_rev1
const uint16_t PROGMEM caps_combo[] = {KC_K, KC_V, COMBO_END};
#endif
const uint16_t PROGMEM cret[] = {KC_QUOT, KC_O, COMBO_END};
const uint16_t PROGMEM combo_pp[] = {KC_7, KC_9, COMBO_END};
const uint16_t PROGMEM combo_next[] = {KC_8, KC_9, COMBO_END};
const uint16_t PROGMEM combo_prev[] = {KC_7, KC_8, COMBO_END};
// const uint16_t PROGMEM combo_back[] = {TD(TD_QCOL), KC_Y,  COMBO_END};
//const uint16_t PROGMEM combo_artab[] = {KC_A, KC_R, COMBO_END};
const uint16_t PROGMEM combo_numbak[] = {KC_0, KC_9, COMBO_END};
const uint16_t PROGMEM combo_esc[] = {KC_1, KC_2, COMBO_END};
const uint16_t PROGMEM tab_combo[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM del_combo[] = {KC_1, KC_0, COMBO_END};
const uint16_t PROGMEM alt_combo[] = {KC_COMM, KC_DOT, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  // [EMAIL] = COMBO_ACTION(email),
  [COMBO_RESET] = COMBO_ACTION(combo_reset),
  [CAPS_COMBO] = COMBO(caps_combo, KC_CAPS),
  [CRET] = COMBO(cret, KC_ENT),
  [COMBOPP] = COMBO(combo_pp,KC_MPLY),
  [COMBO_NEXT] = COMBO(combo_next,KC_MNXT),
  [COMBO_PREV] = COMBO(combo_prev,KC_MPRV),
  // [COMBO_BACK] = COMBO(combo_back,KC_BSPC),
  //[COMBO_ARTAB] = COMBO(combo_artab,KC_TAB),
  [COMBO_NUMBAK] = COMBO(combo_numbak,KC_BSPC),
  [COMBO_ESC] = COMBO(combo_esc, KC_ESC),
  [COMBO_TAB] = COMBO(tab_combo, KC_TAB),
  [COMBO_DELETE] = COMBO(del_combo, KC_DEL),
  [COMBO_ALT] = COMBO(alt_combo, KC_LALT)
};

__attribute__ ((weak))
void process_combo_keymap(uint8_t combo_index, bool pressed) {
}

void process_combo_event(uint8_t combo_index, bool pressed) {
  switch(combo_index) {
//     case EMAIL:
//     if (pressed) {
//       SEND_STRING("tom.campie@gmail.com");
//     }
// break;
    case COMBO_RESET:
    if (pressed) {
      reset_keyboard();
    }
    break;
  }
}
__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }

bool spongebob_mode = false;
bool spongebob_case = false;
bool aesthetic_mode = false;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (spongebob_mode) {
    switch(keycode) {
      case KC_A ... KC_Z:
        if (record->event.pressed) {
          (spongebob_case ^= 1) == 0 ? tap_code16(S(keycode)) : tap_code(keycode);
          return false; break;
        }
    }
  }
  if (aesthetic_mode) {
    switch(keycode) {
#ifdef UCIS_ENABLE
      //case ED(A):
      case KC_A:
        if (record->event.pressed) {
          send_unicode_hex_string("039B");
          tap_code(KC_SPC);
        }
        return false; break;
      case KC_E:
        if (record->event.pressed) {
          send_unicode_hex_string("039E");
          tap_code(KC_SPC);
        }
        return false; break;
#else
      //case ED(A):
      case KC_A:
      case KC_E:
        if (record->event.pressed) {
          register_code(KC_LSFT);
          tap_code16(keycode);
          unregister_code(KC_LSFT);
          tap_code(KC_SPC);
        }
        return false; break;
#endif
      case KC_1 ... KC_0:
      case KC_B ... KC_D:
      case KC_F ... KC_Z:
      //case LS(Z):
        if (record->event.pressed) {
          tap_code16(S(keycode));
          tap_code(KC_SPC);
        }
        return false; break;
      case KC_BSPC:
        if (record->event.pressed) {
          tap_code(KC_BSPC);
          tap_code(KC_BSPC);
        }
        return false; break;
      case KC_SPC:
        if (record->event.pressed) {
          tap_code(KC_SPC);
          tap_code(KC_SPC);
          tap_code(KC_SPC);
        }
        return false; break;
    }
  }
  switch(keycode) {
    case SPONGEBOB:
      if (record->event.pressed) {
        spongebob_mode ^= 1;
      }
      return false; break;
	case AESTHETIC:
      if (record->event.pressed) {
        aesthetic_mode ^= 1;
      }
      return false; break;
  }
  return process_record_keymap(keycode, record);
}
