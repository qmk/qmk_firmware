#include QMK_KEYBOARD_H
#include "version.h"

enum custom_keycodes {
  RGB_SLD = ML_SAFE_RANGE,
  ST_MACRO_0,
  ST_MACRO_1,
  ST_MACRO_2,
  ST_MACRO_3,
  ST_MACRO_4,
  ST_MACRO_5,
  ST_MACRO_6,
  ST_MACRO_7,
  ST_MACRO_8,
  ST_MACRO_9,
  ST_MACRO_10,
  ST_MACRO_11,
  ST_MACRO_12,
  ST_MACRO_13,
  ST_MACRO_14,
  ST_MACRO_15,
  ST_MACRO_16,
  ST_MACRO_17,
  ST_MACRO_18,
  ST_MACRO_19,
  ST_MACRO_20,
  ST_MACRO_21,
};


enum tap_dance_codes {
  DANCE_0,
  DANCE_1,
  DANCE_2,
  DANCE_3,
};

enum layers {
    LAYER_QWERTY,
    LAYER_ARROWS
};

#define __BUILDER_KEYMAP__ "const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS]"
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[QWERTY] = LAYOUT(KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_GRV, KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC, KC_TAB, LCTL_T(KC_A), LALT_T(KC_S), LGUI_T(KC_D), LSFT_T(KC_F), ALL_T(KC_G), ALL_T(KC_H), RSFT_T(KC_J), RGUI_T(KC_K), RALT_T(KC_L), RCTL_T(KC_SCLN), KC_QUOT, KC_NO, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_MUTE, KC_NO, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_TILD, TT(4), TT(5), TT(2), KC_F3, KC_SPC, KC_ENT, TT(3), TT(2), TT(5), TT(4)),
    [LAYER_ARROWS] = LAYOUT(KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
    [2] = LAYOUT(KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_F12, KC_TRNS, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE, KC_TRNS, KC_EQL, KC_MINS, KC_PLUS, KC_LCBR, KC_RCBR, KC_TRNS, KC_TRNS, KC_LBRC, KC_RBRC, KC_SCLN, KC_COLN, KC_BSLS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MO(4), KC_TRNS, KC_TRNS, KC_TRNS),
    [3] = LAYOUT(KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, SGUI(KC_4), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_INS, KC_PSCR, KC_APP, LCTL(KC_LEFT), LCTL(KC_RGHT), LGUI(KC_UP), LALT(KC_LEFT), KC_UP, LALT(KC_RGHT), LALT(KC_BSPC), KC_BSPC, KC_TRNS, KC_LALT, KC_LCTL, KC_LSFT, KC_NO, KC_CAPS, LGUI(KC_DOWN), KC_LEFT, KC_DOWN, KC_RGHT, KC_DEL, KC_BSPC, KC_TRNS, LGUI(KC_Z), LGUI(KC_X), LGUI(KC_C), LGUI(KC_V), CW_TOGG, KC_TRNS, KC_TRNS, KC_NO, LGUI(KC_LEFT), KC_NO, LGUI(KC_RGHT), KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
    [4] = LAYOUT(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, QK_BOOT, KC_NO, KC_NO, KC_NO, CG_TOGG, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, CG_TOGG, KC_NO, KC_NO, KC_NO, KC_NO, KC_VOLD, KC_MUTE, KC_VOLU, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MPRV, KC_MPLY, KC_MNXT, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
    [5] = LAYOUT(KC_NO, KC_NO, KC_PAST, KC_PSLS, KC_PPLS, KC_PMNS, KC_NO, KC_P7, KC_P8, KC_P9, KC_PAST, KC_NO, KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_NO, KC_P4, KC_P5, KC_P6, KC_PSLS, KC_BSPC, KC_TAB, KC_6, KC_7, KC_8, KC_9, KC_0, KC_COLN, KC_P1, KC_P2, KC_P3, KC_PPLS, KC_NO, KC_LSFT, KC_UNDS, KC_PEQL, KC_PCMM, KC_COLN, KC_PDOT, KC_NO, KC_NO, KC_PEQL, KC_P0, KC_PCMM, KC_PDOT, KC_PMNS, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_SPC, KC_ENT, KC_NO, KC_NO, KC_TRNS, KC_NO)
};

//extern rgb_config_t rgb_matrix_config;

//void keyboard_post_init_user(void) {
//  rgb_matrix_enable();
//}

#define __BUILDER_LEDMAP__ "const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3]"
//const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
//[QWERTY] = { {29,113,204}, {235,219,0}, {55,255,0}, {55,255,0}, {55,255,0}, {55,255,0}, {55,255,0}, {55,255,0},
//{55,255,0}, {55,255,0}, {55,255,0}, {55,255,0}, {235,219,0}, {204,0,51}, {29,113,204}, {29,113,204}, {29,113,204},
//{29,113,204}, {29,113,204}, {29,113,204}, {29,113,204}, {29,113,204}, {29,113,204}, {29,113,204}, {204,0,51},
//{235,219,0}, {29,113,204}, {29,113,204}, {29,113,204}, {29,113,204}, {29,113,204}, {29,113,204}, {29,113,204},
//{29,113,204}, {29,113,204}, {235,219,0}, {235,219,0}, {235,219,0}, {29,113,204}, {29,113,204}, {29,113,204},
//{29,113,204}, {235,219,0}, {29,113,204}, {29,113,204}, {235,219,0}, {235,219,0}, {235,219,0}, {29,113,204},
//{29,113,204}, {29,113,204}, {29,113,204}, {29,113,204}, {29,113,204}, {29,113,204}, {29,113,204}, {29,113,204},
//{29,113,204}}
//};
//
//void set_layer_color(int layer) {
//  for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
//    HSV hsv = {
//      .h = pgm_read_byte(&ledmap[layer][i][0]),
//      .s = pgm_read_byte(&ledmap[layer][i][1]),
//      .v = pgm_read_byte(&ledmap[layer][i][2]),
//    };
//    if (!hsv.h && !hsv.s && !hsv.v) {
//        rgb_matrix_set_color( i, 0, 0, 0 );
//    } else {
//        RGB rgb = hsv_to_rgb( hsv );
//        float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
//        rgb_matrix_set_color( i, f * rgb.r, f * rgb.g, f * rgb.b );
//    }
//  }
//}
//
//void rgb_matrix_indicators_user(void) {
//  if (keyboard_config.disable_layer_led) { return; }
//  switch (biton32(layer_state)) {
//    case 0:
//      set_layer_color(0);
//      break;
//    case 1:
//      set_layer_color(1);
//      break;
//    case 2:
//      set_layer_color(2);
//      break;
//    case 3:
//      set_layer_color(3);
//      break;
//    case 4:
//      set_layer_color(4);
//      break;
//    case 5:
//      set_layer_color(5);
//      break;
//    case 6:
//      set_layer_color(6);
//      break;
//    case 7:
//      set_layer_color(7);
//      break;
//    case 9:
//      set_layer_color(9);
//      break;
//    case 10:
//      set_layer_color(10);
//      break;
//   default:
//    if (rgb_matrix_get_flags() == LED_FLAG_NONE)
//      rgb_matrix_set_color_all(0, 0, 0);
//    break;
//  }
//}
//
//bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//  switch (keycode) {
//    case ST_MACRO_0:
//    if (record->event.pressed) {
//      SEND_STRING(SS_LALT(SS_LCTL(SS_LGUI(SS_LSFT(SS_TAP(X_R))))) SS_DELAY(100) SS_TAP(X_Q));
//
//    }
//    break;
//    case ST_MACRO_1:
//    if (record->event.pressed) {
//      SEND_STRING(SS_LALT(SS_LCTL(SS_LGUI(SS_LSFT(SS_TAP(X_R))))) SS_DELAY(100) SS_TAP(X_W));
//
//    }
//    break;
//    case ST_MACRO_2:
//    if (record->event.pressed) {
//      SEND_STRING(SS_LALT(SS_LCTL(SS_LGUI(SS_LSFT(SS_TAP(X_R))))) SS_DELAY(100) SS_TAP(X_E));
//
//    }
//    break;
//    case ST_MACRO_3:
//    if (record->event.pressed) {
//      SEND_STRING(SS_LALT(SS_LCTL(SS_LGUI(SS_LSFT(SS_TAP(X_R))))) SS_DELAY(100) SS_TAP(X_A));
//
//    }
//    break;
//    case ST_MACRO_4:
//    if (record->event.pressed) {
//      SEND_STRING(SS_LALT(SS_LCTL(SS_LGUI(SS_LSFT(SS_TAP(X_R))))) SS_DELAY(100) SS_TAP(X_S));
//
//    }
//    break;
//    case ST_MACRO_5:
//    if (record->event.pressed) {
//      SEND_STRING(SS_LALT(SS_LCTL(SS_LGUI(SS_LSFT(SS_TAP(X_R))))) SS_DELAY(100) SS_TAP(X_D));
//
//    }
//    break;
//    case ST_MACRO_6:
//    if (record->event.pressed) {
//      SEND_STRING(SS_LALT(SS_LCTL(SS_LGUI(SS_LSFT(SS_TAP(X_R))))) SS_DELAY(100) SS_TAP(X_Z));
//
//    }
//    break;
//    case ST_MACRO_7:
//    if (record->event.pressed) {
//      SEND_STRING(SS_LALT(SS_LCTL(SS_LGUI(SS_LSFT(SS_TAP(X_R))))) SS_DELAY(100) SS_TAP(X_X));
//
//    }
//    break;
//    case ST_MACRO_8:
//    if (record->event.pressed) {
//      SEND_STRING(SS_LALT(SS_LCTL(SS_LGUI(SS_LSFT(SS_TAP(X_R))))) SS_DELAY(100) SS_TAP(X_C));
//
//    }
//    break;
//    case ST_MACRO_9:
//    if (record->event.pressed) {
//      SEND_STRING(SS_LALT(SS_LCTL(SS_LGUI(SS_LSFT(SS_TAP(X_R))))) SS_DELAY(100) SS_TAP(X_Y));
//
//    }
//    break;
//    case ST_MACRO_10:
//    if (record->event.pressed) {
//      SEND_STRING(SS_LALT(SS_LCTL(SS_LGUI(SS_LSFT(SS_TAP(X_R))))) SS_DELAY(100) SS_TAP(X_U));
//
//    }
//    break;
//    case ST_MACRO_11:
//    if (record->event.pressed) {
//      SEND_STRING(SS_LALT(SS_LCTL(SS_LGUI(SS_LSFT(SS_TAP(X_R))))) SS_DELAY(100) SS_TAP(X_H));
//
//    }
//    break;
//    case ST_MACRO_12:
//    if (record->event.pressed) {
//      SEND_STRING(SS_LALT(SS_LCTL(SS_LGUI(SS_LSFT(SS_TAP(X_R))))) SS_DELAY(100) SS_TAP(X_J));
//
//    }
//    break;
//    case ST_MACRO_13:
//    if (record->event.pressed) {
//      SEND_STRING(SS_LALT(SS_LCTL(SS_LGUI(SS_LSFT(SS_TAP(X_R))))) SS_DELAY(100) SS_TAP(X_N));
//
//    }
//    break;
//    case ST_MACRO_14:
//    if (record->event.pressed) {
//      SEND_STRING(SS_LALT(SS_LCTL(SS_LGUI(SS_LSFT(SS_TAP(X_R))))) SS_DELAY(100) SS_TAP(X_M));
//
//    }
//    break;
//    case ST_MACRO_15:
//    if (record->event.pressed) {
//      SEND_STRING(SS_LGUI(SS_TAP(X_SPACE)) SS_DELAY(100) SS_TAP(X_N) SS_DELAY(100) SS_TAP(X_F)  SS_DELAY(100) SS_TAP(X_ENTER));
//
//    }
//    break;
//    case ST_MACRO_16:
//    if (record->event.pressed) {
//      SEND_STRING(SS_LGUI(SS_TAP(X_SPACE)) SS_DELAY(100) SS_TAP(X_I) SS_DELAY(100) SS_TAP(X_T)  SS_DELAY(100) SS_TAP(X_ENTER));
//
//    }
//    break;
//    case ST_MACRO_17:
//    if (record->event.pressed) {
//      SEND_STRING(SS_LGUI(SS_TAP(X_SPACE)) SS_DELAY(100) SS_TAP(X_A) SS_DELAY(100) SS_TAP(X_G)  SS_DELAY(100) SS_TAP(X_ENTER));
//
//    }
//    break;
//    case ST_MACRO_18:
//    if (record->event.pressed) {
//      SEND_STRING(SS_LGUI(SS_TAP(X_SPACE)) SS_DELAY(100) SS_TAP(X_S) SS_DELAY(100) SS_TAP(X_L) SS_DELAY(100) SS_TAP(X_ENTER));
//
//    }
//    break;
//    case ST_MACRO_19:
//    if (record->event.pressed) {
//      SEND_STRING(SS_LGUI(SS_TAP(X_SPACE)) SS_DELAY(100) SS_TAP(X_D) SS_DELAY(100) SS_TAP(X_G)  SS_DELAY(100) SS_TAP(X_ENTER));
//
//    }
//    break;
//    case ST_MACRO_20:
//    if (record->event.pressed) {
//      SEND_STRING(SS_LGUI(SS_TAP(X_SPACE)) SS_DELAY(100) SS_TAP(X_I) SS_DELAY(100) SS_TAP(X_J)  SS_DELAY(100) SS_TAP(X_ENTER));
//
//    }
//    break;
//    case ST_MACRO_21:
//    if (record->event.pressed) {
//      SEND_STRING(SS_LGUI(SS_TAP(X_SPACE)) SS_DELAY(100) SS_TAP(X_O) SS_DELAY(100) SS_TAP(X_U) SS_DELAY(100) SS_TAP(X_T)  SS_DELAY(100) SS_TAP(X_ENTER));
//
//    }
//    break;
//    case RGB_SLD:
//      if (record->event.pressed) {
//        rgblight_mode(1);
//      }
//      return false;
//  }
//  return true;
//}

typedef struct {
    bool is_press_action;
    uint8_t step;
} tap;

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP,
    MORE_TAPS
};

static tap dance_state[4];

uint8_t dance_step(qk_tap_dance_state_t *state);

uint8_t dance_step(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}


void on_dance_0(qk_tap_dance_state_t *state, void *user_data);
void dance_0_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_0_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_0(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_3);
        tap_code16(KC_3);
        tap_code16(KC_3);
    }
    if(state->count > 3) {
        tap_code16(KC_3);
    }
}

void dance_0_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state[0].step = dance_step(state);
    switch (dance_state[0].step) {
        case SINGLE_TAP: register_code16(KC_3); break;
        case SINGLE_HOLD: register_code16(LCTL(KC_F3)); break;
        case DOUBLE_TAP: register_code16(KC_3); register_code16(KC_3); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_3); register_code16(KC_3);
    }
}

void dance_0_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[0].step) {
        case SINGLE_TAP: unregister_code16(KC_3); break;
        case SINGLE_HOLD: unregister_code16(LCTL(KC_F3)); break;
        case DOUBLE_TAP: unregister_code16(KC_3); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_3); break;
    }
    dance_state[0].step = 0;
}
void on_dance_1(qk_tap_dance_state_t *state, void *user_data);
void dance_1_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_1_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_1(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_4);
        tap_code16(KC_4);
        tap_code16(KC_4);
    }
    if(state->count > 3) {
        tap_code16(KC_4);
    }
}

void dance_1_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state[1].step = dance_step(state);
    switch (dance_state[1].step) {
        case SINGLE_TAP: register_code16(KC_4); break;
        case SINGLE_HOLD: register_code16(LGUI(LSFT(KC_4))); break;
        case DOUBLE_TAP: register_code16(KC_4); register_code16(KC_4); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_4); register_code16(KC_4);
    }
}

void dance_1_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[1].step) {
        case SINGLE_TAP: unregister_code16(KC_4); break;
        case SINGLE_HOLD: unregister_code16(LGUI(LSFT(KC_4))); break;
        case DOUBLE_TAP: unregister_code16(KC_4); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_4); break;
    }
    dance_state[1].step = 0;
}
void on_dance_2(qk_tap_dance_state_t *state, void *user_data);
void dance_2_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_2_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_2(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_QUOTE);
        tap_code16(KC_QUOTE);
        tap_code16(KC_QUOTE);
    }
    if(state->count > 3) {
        tap_code16(KC_QUOTE);
    }
}

void dance_2_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state[2].step = dance_step(state);
    switch (dance_state[2].step) {
        case SINGLE_TAP: register_code16(KC_QUOTE); break;
        case SINGLE_HOLD: register_code16(LALT(LGUI(KC_QUOTE))); break;
        case DOUBLE_TAP: register_code16(KC_QUOTE); register_code16(KC_QUOTE); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_QUOTE); register_code16(KC_QUOTE);
    }
}

void dance_2_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[2].step) {
        case SINGLE_TAP: unregister_code16(KC_QUOTE); break;
        case SINGLE_HOLD: unregister_code16(LALT(LGUI(KC_QUOTE))); break;
        case DOUBLE_TAP: unregister_code16(KC_QUOTE); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_QUOTE); break;
    }
    dance_state[2].step = 0;
}
void on_dance_3(qk_tap_dance_state_t *state, void *user_data);
void dance_3_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_3_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_3(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(LGUI(KC_SPACE));
        tap_code16(LGUI(KC_SPACE));
        tap_code16(LGUI(KC_SPACE));
    }
    if(state->count > 3) {
        tap_code16(LGUI(KC_SPACE));
    }
}

void dance_3_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state[3].step = dance_step(state);
    switch (dance_state[3].step) {
        case SINGLE_TAP: register_code16(LGUI(KC_SPACE)); break;
        case DOUBLE_TAP: register_code16(LGUI(LSFT(KC_SPACE))); break;
        case DOUBLE_SINGLE_TAP: tap_code16(LGUI(KC_SPACE)); register_code16(LGUI(KC_SPACE));
    }
}

void dance_3_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[3].step) {
        case SINGLE_TAP: unregister_code16(LGUI(KC_SPACE)); break;
        case DOUBLE_TAP: unregister_code16(LGUI(LSFT(KC_SPACE))); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(LGUI(KC_SPACE)); break;
    }
    dance_state[3].step = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
        [DANCE_0] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_0, dance_0_finished, dance_0_reset),
        [DANCE_1] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_1, dance_1_finished, dance_1_reset),
        [DANCE_2] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_2, dance_2_finished, dance_2_reset),
        [DANCE_3] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_3, dance_3_finished, dance_3_reset),
};

