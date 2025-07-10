// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "keymap_german.h"

enum custom_keycodes {
  LMAGIC = SAFE_RANGE,
  RMAGIC,
  MACLCURLY,
  MACRCURLY,
  HRM_GUI_D,
  HRM_GUI_H,
  HRM_ALT_S,
  HRM_CTRL_E,
  HRL_BRACKETS_T,
  HRL_BRACKETS_N,
  TRL_MEDIA_L,
  TRL_MEDIA_P,
};

#define TAPPING_TERM_PER_KEY

#define MACLCURLY ALGR(DE_8)
#define MACRCURLY ALGR(DE_9)
#define HRM_GUI_D MT(MOD_LGUI, DE_D)
#define HRM_ALT_S MT(MOD_LALT | MOD_RALT, DE_S)
#define HRM_GUI_H MT(MOD_LGUI, DE_H)
#define HRM_CTRL_E MT(MOD_LCTL, DE_E)
#define HRL_BRACKETS_T LT(_BRACKETS, DE_T)
#define HRL_BRACKETS_N LT(_BRACKETS, DE_N)
#define TRL_MEDIA_L LT(_MEDIA, DE_L)
#define TRL_MEDIA_P LT(_MEDIA, DE_P)

// Tap Dance Hold configuration
typedef struct {
  uint16_t tap;
  uint16_t hold;
  uint16_t held;
} tap_dance_tap_hold_t;

void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data) {
  tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

  if (state->pressed) {
    if (state->count == 1
#ifndef PERMISSIVE_HOLD
        && !state->interrupted
#endif
    ) {
      register_code16(tap_hold->hold);
      tap_hold->held = tap_hold->hold;
    }
  } else {
    register_code16(tap_hold->tap);
    tap_hold->held = tap_hold->tap;
  }
}

void tap_dance_tap_hold_reset(tap_dance_state_t *state, void *user_data) {
  tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

  if (tap_hold->held) {
    unregister_code16(tap_hold->held);
    tap_hold->held = 0;
  }
}

#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold)                               \
  {                                                                        \
      .fn = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, \
      .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}),        \
  }

enum {
  SPACE_TAB,
  TDH_U_UE,
  TDH_O_OE,
  TDH_A_AE,
};
// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [SPACE_TAB] = ACTION_TAP_DANCE_DOUBLE(KC_SPC, KC_TAB),
    [TDH_U_UE] = ACTION_TAP_DANCE_TAP_HOLD(DE_U, DE_UDIA),
    [TDH_O_OE] = ACTION_TAP_DANCE_TAP_HOLD(DE_O, DE_ODIA),
    [TDH_A_AE] = ACTION_TAP_DANCE_TAP_HOLD(DE_A, DE_ADIA),
};
static void process_tap_dance_hold(uint16_t keycode, keyrecord_t *record) {
  tap_dance_action_t *action;

  action = &tap_dance_actions[QK_TAP_DANCE_GET_INDEX(keycode)];
  if (!record->event.pressed && action->state.count &&
      !action->state.finished) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
    tap_code16(tap_hold->tap);
  }
}

enum custom_layers {
  _COLEMAK,
  _GAME,
  _NAVIGATION,
  _BRACKETS,
  _EXTRA,
  _MEDIA,
};
// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_COLEMAK] = LAYOUT(
     QK_GESC, KC_1, KC_2,  KC_3,      KC_4,           KC_5,                        KC_6,      KC_7, KC_8,      KC_9,       KC_0,   KC_BSPC,
     KC_TAB,  DE_Q, DE_W,  DE_F,      TRL_MEDIA_P,    DE_G,                        DE_J,      TRL_MEDIA_L,     DE_U,       DE_Y,   XXXXXXX, XXXXXXX,
     KC_LCTL, DE_A, DE_R,  HRM_ALT_S, HRL_BRACKETS_T, HRM_GUI_D,                   HRM_GUI_H, HRL_BRACKETS_N,  HRM_CTRL_E, DE_I,   DE_O,   KC_ENTER,
     KC_LSFT, DE_Z, DE_X,  DE_C,      DE_V, DE_B,               KC_HOME, KC_END,   DE_K,      DE_M, DE_COMM,   KC_DOT, KC_SLSH, KC_CAPS,
                            LMAGIC, MO(_NAVIGATION), TD(SPACE_TAB), OSM(MOD_LSFT), MO(_EXTRA), RMAGIC
  ),
  [_GAME] = LAYOUT(
     QK_GESC, KC_1, KC_2, KC_3, KC_4, KC_5,                  KC_6, KC_7, KC_8, KC_9,   KC_0,    KC_BSPC,
     KC_TAB,  DE_Q, DE_W, DE_E, DE_R, DE_T,                  DE_Z, DE_U, DE_I, DE_O,   DE_P, DE_UDIA,
     KC_LCTL, DE_A, DE_S, DE_D, DE_F, DE_G,                  DE_H, DE_J, DE_K, DE_L, DE_ODIA, DE_ADIA,
     KC_LSFT, DE_Y, DE_X, DE_C, DE_V, DE_B, KC_HOME, KC_END, DE_N, DE_M, DE_COMM, KC_DOT, KC_SLSH, KC_CAPS,
               LMAGIC,MO(_NAVIGATION), LT(_BRACKETS,KC_SPC), KC_LSFT,  LT(_EXTRA,KC_ENTER), TO(_COLEMAK)
  ),
  [_NAVIGATION] = LAYOUT(
     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,                                XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
     _______,  XXXXXXX, KC_PGDN, KC_UP,   KC_PGUP, XXXXXXX,                               XXXXXXX, KC_7,   KC_8,   KC_9,   KC_0,   KC_PGDN,
     _______,  KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,                                KC_RCBR, KC_4,   KC_5,   KC_6,   KC_PLUS, KC_PIPE,
     _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         TO(0), _______,        KC_RBRC, KC_1,   KC_2,   KC_3,   DE_SS,   _______,
                                              _______, _______,  KC_DEL, KC_DEL, _______, KC_P0
  ),
  [_BRACKETS] = LAYOUT(
    KC_F12, KC_F1,    KC_F2,      KC_F3,      KC_F4,   KC_F5,                           KC_F6,   KC_F7,   KC_F8,      KC_F9,      KC_F10,  KC_F11,
     _______, XXXXXXX, XXXXXXX,    XXXXXXX,    DE_LABK, XXXXXXX,                         XXXXXXX, DE_RABK, XXXXXXX,    XXXXXXX,    XXXXXXX, QK_BOOT,
     _______, XXXXXXX, MACLCURLY,    ALGR(DE_5), DE_LPRN, XXXXXXX,                       XXXXXXX,  DE_RPRN, ALGR(DE_6), MACRCURLY, XXXXXXX, KC_BSLS,
     _______, XXXXXXX, ALGR(DE_7), XXXXXXX,    XXXXXXX, XXXXXXX,    TO(0), _______,      XXXXXXX, DE_EQL,  ALGR(DE_0), XXXXXXX,    XXXXXXX, XXXXXXX,
                                                _______, _______, KC_BSPC, KC_BSPC, QK_AREP, _______
  ),
  [_EXTRA] = LAYOUT(
     _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,
     _______, XXXXXXX, KC_GRV, KC_TILD, KC_PLUS, DE_SECT,                       XXXXXXX, LSA(DE_7), KC_RCBR, XXXXXXX, XXXXXXX,  XXXXXXX,
     _______, DE_EQL,  DE_PERC, DE_EXLM, DE_DQUO, DE_DLR,                       DE_AMPR, DE_SLSH, DE_QUES, DE_HASH, ALGR(DE_7), XXXXXXX,
     _______, DE_ADIA, DE_ODIA, DE_UDIA, KC_PIPE, XXXXXXX,    TO(0), _______,   XXXXXXX, DE_BSLS, XXXXXXX, XXXXXXX, DE_PIPE,    XXXXXXX,
                                          _______, _______, _______, _______, _______, _______
  ),
  [_MEDIA] = LAYOUT(
     _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,
     _______, XXXXXXX, KC_MUTE, KC_MSTP, KC_VOLU, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RM_TOGG,    XXXXXXX,
     _______, XXXXXXX,  KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX,                     XXXXXXX, RM_NEXT, RM_VALU, RM_HUEU, RM_SPDU,    XXXXXXX,
     _______, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLD, XXXXXXX,    TO(0), _______,   XXXXXXX, RM_PREV, RM_VALD, RM_HUED, RM_SPDD,    XXXXXXX,
                                          _______, _______, _______, _______, _______, _______
  )
};

const char PROGMEM chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] =
  LAYOUT(
        'L', 'L', 'L', 'L', 'L', 'L',        'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L',        'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L',        'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L','*','*','R', 'R', 'R', 'R', 'R', 'R',
                       '*', '*', '*',        '*', '*', '*'
    );
// clang-format on

const uint16_t PROGMEM activate_game_layer[] = {DE_Q, DE_W, DE_Y, COMBO_END};
const uint16_t PROGMEM next_song[] = {DE_N, MT(MOD_LCTL, DE_E), COMBO_END};
const uint16_t PROGMEM play_stop[] = {DE_M, DE_P, COMBO_END};
combo_t key_combos[] = {COMBO(activate_game_layer, TO(1)),
                        COMBO(next_song, KC_MEDIA_NEXT_TRACK),
                        COMBO(play_stop, KC_MEDIA_PLAY_PAUSE)};

bool remember_last_key_user(uint16_t keycode, keyrecord_t *record,
                            uint8_t *remembered_mods) {
  switch (keycode) {
    case CW_TOGG:
    case KC_ESC:
    case KC_BSPC:
    case KC_DEL:

    case LMAGIC:
    case RMAGIC:
      return false;  // Magic keys will ignore the above keycodes.
  }
  return true;  // Other keys can be repeated.
}

// An enhanced version of SEND_STRING: the last key is set such that if
// the Repeat Key is pressed next, it produces `repeat_keycode`.
#define MAGIC_STRING(str, repeat_keycode) \
  magic_send_string_P(PSTR(str), (repeat_keycode))

static void magic_send_string_P(const char *str, uint16_t repeat_keycode) {
  send_string_with_delay_P(str, TAP_CODE_DELAY);  // Send the string.
  set_last_keycode(repeat_keycode);  // 2024-03-09 Disabled sending of string
                                     // for mag-rep / rep-mag consistency.
}

static void process_left_magic(uint16_t keycode,
                               uint8_t mods) {  // LMAGIC definitions
  switch (keycode) {
    case TRL_MEDIA_L: {
      MAGIC_STRING("l", KC_NO);
    } break;
    case KC_M: {
      MAGIC_STRING("m", KC_NO);
    } break;
    case DE_O: {
      MAGIC_STRING("o", KC_NO);
    } break;
    case DE_U: {
      MAGIC_STRING("u", KC_NO);
    } break;

    case MACRCURLY: {
      SEND_STRING(SS_RALT("8"));
    } break;
  }
}

static void process_right_magic(uint16_t keycode,
                                uint8_t mods) {  // RMAGIC definitions
  switch (keycode) {
    case DE_A: {
      MAGIC_STRING("a", KC_NO);
    } break;
    case KC_B: {
      MAGIC_STRING("b", KC_NO);
    } break;
    case TRL_MEDIA_P: {
      MAGIC_STRING("p", KC_NO);
    } break;
    case KC_R: {
      MAGIC_STRING("r", KC_NO);
    } break;
    case HRM_ALT_S: {
      MAGIC_STRING("s", KC_NO);
    } break;
    case HRL_BRACKETS_T: {
      MAGIC_STRING("t", KC_NO);
    } break;
    case DE_W: {
      MAGIC_STRING("w", KC_NO);
    } break;

    case MACLCURLY: {
      SEND_STRING(SS_RALT("9"));
    } break;
  }
}

// layer_state_t layer_state_set_user(layer_state_t state) {
//   switch (get_highest_layer(state)) {
//     // case _NAVIGATION:
//     //     rgb_matrix_mode (RGB_MATRIX_SPLASH);
//     //     break;
//     // case _BRACKETS:
//     //     rgb_matrix_mode (RGB_MATRIX_BAND_SAT);
//     //     break;
//     // case _EXTRA:
//     //     rgb_matrix_mode (RGB_MATRIX_BREATHING);
//     //     break;
//     case _GAME:
//       rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
//       break;
//     default:  //  for any other layers, or the default layer
//       rgb_matrix_mode(RGB_MATRIX_SOLID_REACTIVE_WIDE);
//       // rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_PALETTEFX_FLOW);
//       break;
//   }
//   return state;
// }

// custom keystroke main logic
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch (keycode) {
      case LMAGIC: {
        process_left_magic(get_last_keycode(), get_last_mods());
        set_last_keycode(KC_SPC);
      }
        return false;
      case RMAGIC: {
        process_right_magic(get_last_keycode(), get_last_mods());
        set_last_keycode(KC_SPC);
      }
        return false;
      case TD(TDH_A_AE):
      case TD(TDH_O_OE):
      case TD(TDH_U_UE): {
        process_tap_dance_hold(keycode, record);
      }
    }
  }

  return true;
}

void keyboard_post_init_user(void) {
  rgb_matrix_mode(RGB_MATRIX_SOLID_REACTIVE_WIDE);
  rgb_matrix_sethsv(191, 255, 255);
}
// void keyboard_post_init_user(void) {
//   // Set the effect.
//   rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_PALETTEFX_REACTIVE);
//   // Set the palette and maximize saturation and brightness.
//   uint8_t palette_index = PALETTEFX_AFTERBURN;
//   rgb_matrix_sethsv_noeeprom(RGB_MATRIX_HUE_STEP * palette_index, 255, 255);
//   // Set speed to default.
//   rgb_matrix_set_speed_noeeprom(128);
//   // Make sure RGB Matrix is on.
//   rgb_matrix_enable_noeeprom();
// }
