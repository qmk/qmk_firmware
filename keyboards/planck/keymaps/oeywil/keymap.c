#include QMK_KEYBOARD_H
#include "no_keycodes.h"

#if __has_include("secrets.h")
#  include "secrets.h"
#else
#  define mail_str ""
#  define pwd_str ""
#endif

// layer definitions
enum planck_layers {
  _DEFAULT,
  _LOWER,
  _RAISE,
  _GAME,
  _GLOW
};

// sounds
#ifdef AUDIO_ENABLE
  float gamesong[][2] = SONG(MARIO_MUSHROOM);
  float defsong[][2] = SONG(PLOVER_GOODBYE_SOUND);
  float failed[][2] = SONG(TERMINAL_SOUND);
#endif

// leader key
bool leader_succeed;
bool leader_layer_game;
bool leader_layer_def;
LEADER_EXTERNS();

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leader_succeed = leading = false;
    leader_layer_game = false;
    leader_layer_def = false;

    SEQ_TWO_KEYS(KC_P, KC_P) {
      SEND_STRING(pwd_str);
      leader_succeed = true;
    }
    SEQ_TWO_KEYS(KC_P, KC_M) {
      SEND_STRING(mail_str);
      leader_succeed = true;
    }
    SEQ_TWO_KEYS(KC_B, KC_B) {
      SEND_STRING("build"SS_TAP(X_ENTER));
      leader_succeed = true;
    }
    SEQ_TWO_KEYS(KC_B, KC_F) {
      SEND_STRING("flash"SS_TAP(X_ENTER));
      reset_keyboard();
      leader_succeed = true;
    }
    SEQ_TWO_KEYS(KC_L, KC_G) {
      layer_on(_GAME);
      leader_layer_game = true;
    }
    SEQ_TWO_KEYS(KC_L, KC_D) {
      layer_off(_GAME);
      leader_layer_def = true;
    }
    leader_end();
  }
}

void leader_end(void) {
  if (leader_succeed) {
    // do nothing
  } else if (leader_layer_game) {
    #ifdef AUDIO_ENABLE
      PLAY_SONG(gamesong);
    #endif
  } else if (leader_layer_def) {
    #ifdef AUDIO_ENABLE
      PLAY_SONG(defsong);
    #endif
  } else {
    #ifdef AUDIO_ENABLE
      PLAY_SONG(failed);
    #endif
  }
}

// tap dance definitions
typedef struct {
  bool is_press_action;
  int state;
} tap;

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  DOUBLE_SINGLE_TAP = 5,
  TRIPLE_TAP = 6,
  TRIPLE_HOLD = 7
};

enum {
  TD_LSFT = 0,
  TD_LCTL,
  TD_RSFT,
  TD_RCTL
};

int cur_dance (qk_tap_dance_state_t *state);
void lsft_finished (qk_tap_dance_state_t *state, void *user_data);
void lsft_reset (qk_tap_dance_state_t *state, void *user_data);
void rsft_finished (qk_tap_dance_state_t *state, void *user_data);
void rsft_reset (qk_tap_dance_state_t *state, void *user_data);
void lctl_finished (qk_tap_dance_state_t *state, void *user_data);
void lctl_reset (qk_tap_dance_state_t *state, void *user_data);
void rctl_finished (qk_tap_dance_state_t *state, void *user_data);
void rctl_reset (qk_tap_dance_state_t *state, void *user_data);

// layer declarations
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Default
   * ,-----------------------------------------------------------------------------------.
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   Å  | BkSp |
   * |------+------+------+------+------+-------------+------+------+------+------+------|
   * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   Ø  |   Æ  |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   P  |   ,  |   .  | Shift|
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * | Ctrl | Lead | Win  | Alt  | Lower| Space| Enter| Raise| AltGr| App  | Lead | Ctrl |
   * `-----------------------------------------------------------------------------------'
   */
  [_DEFAULT] = LAYOUT_planck_grid(
    KC_TAB,      KC_Q,    KC_W,    KC_E,    KC_R,       KC_T,   KC_Y,   KC_U,       KC_I,    KC_O,    NO_AA,   KC_BSPC,
    KC_ESC,      KC_A,    KC_S,    KC_D,    KC_F,       KC_G,   KC_H,   KC_J,       KC_K,    KC_L,    NO_OE,   NO_AE,
    TD(TD_LSFT), KC_Z,    KC_X,    KC_C,    KC_V,       KC_B,   KC_N,   KC_M,       KC_P,    KC_COMM, KC_DOT,  TD(TD_RSFT),
    TD(TD_LCTL), KC_LEAD, KC_LGUI, KC_LALT, MO(_LOWER), KC_SPC, KC_ENT, MO(_RAISE), KC_ALGR, KC_APP,  KC_LEAD, TD(TD_RCTL)
  ),
  /* Lower
   * ,-----------------------------------------------------------------------------------.
   * | Tab  | <Word| Up   | Word>| PgUp |      |      |      |  F7  |  F8  |  F9  |  Del |
   * |------+------+------+------+------+-------------+------+------+------+------+------|
   * | BkSp | Left | Down | Right| PgDn |      |      |      |  F4  |  F5  |  F6  |      |
   * |------+------+------+------+------+------|------+------+------+------+------+------|
   * | Shift| Home |      | End  |      |      |      |      |  F1  |  F2  |  F3  | Shift|
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * | Ctrl |      | Win  | Alt  | Lower| M_PP |M_Next|      |      | Mute | VolD | VolUp|
   * `-----------------------------------------------------------------------------------'
   */
  [_LOWER] = LAYOUT_planck_grid(
    KC_TRNS, LCTL(KC_LEFT), KC_UP,   LCTL(KC_RIGHT), KC_PGUP, KC_NO,   KC_NO,   KC_NO, KC_F7, KC_F8,   KC_F9, KC_DEL,
    KC_BSPC, KC_LEFT,       KC_DOWN, KC_RIGHT,       KC_PGDN, KC_NO,   KC_NO,   KC_NO, KC_F4, KC_F5,   KC_F6, KC_NO,
    KC_TRNS, KC_HOME,       KC_NO,   KC_END,         KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_F1, KC_F2,   KC_F3, KC_TRNS,
    KC_TRNS, KC_NO,         KC_TRNS, KC_TRNS,        KC_TRNS, KC_MPLY, KC_MNXT, KC_NO, KC_NO, KC_MUTE, KC_VOLD, KC_VOLU
  ),
  /* Raise
   * ,-----------------------------------------------------------------------------------.
   * | Tab  |   !  |   ?  |   #  |   *  |   |  |   =  |   /  |   7  |   8  |   9  | Ins  |
   * |------+------+------+------+------+-------------+------+------+------+------+------|
   * | BkSp |   @  |   &  |   $  |   %  |   ~  |   +  |   \  |   4  |   5  |   6  |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   '  |   "  |   ¨  |      |      |   -  |   0  |   1  |   2  |   3  | Shift|
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * | Ctrl |      | Win  | Alt  |      | Space| Enter| Raise| AltGr|      |      |      |
   * `-----------------------------------------------------------------------------------'
   */
  [_RAISE] = LAYOUT_planck_grid(
    KC_TRNS, NO_EXCL, NO_QEST, NO_HASH, NO_ASTE, NO_PIPE, NO_EQUA, NO_FSLS, KC_7,    KC_8,  KC_9,  KC_INS,
    KC_BSPC, NO_ALFA, NO_AMPE, NO_USDO, NO_PERC, NO_TILD, NO_PLUS, NO_BSLS, KC_4,    KC_5,  KC_6,  KC_NO,
    KC_TRNS, NO_APOS, NO_QUOT, NO_UMLA, KC_NO,   KC_NO,   NO_DASH, KC_0,    KC_1,    KC_2,  KC_3,  KC_TRNS,
    KC_TRNS, KC_NO,   KC_TRNS, KC_TRNS, KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO
  ),
  /* Game
   * ,-----------------------------------------------------------------------------------.
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |      | BkSp |
   * |------+------+------+------+------+-------------+------+------+------+------+------|
   * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   P  |   ,  |   .  |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * | Ctrl | Lead |      | Alt  | Lower| Space| Enter| Lower|      |      | Lead |      |
   * `-----------------------------------------------------------------------------------'
   */
  [_GAME] = LAYOUT_planck_grid(
    KC_TAB,  KC_Q,    KC_W,  KC_E,    KC_R,      KC_T,   KC_Y,   KC_U,      KC_I, KC_O,    KC_NO,   KC_BSPC,
    KC_ESC,  KC_A,    KC_S,  KC_D,    KC_F,      KC_G,   KC_H,   KC_J,      KC_K, KC_L,    KC_NO,   KC_NO,
    KC_LSFT, KC_Z,    KC_X,  KC_C,    KC_V,      KC_B,   KC_N,   KC_M,      KC_P, KC_COMM, KC_DOT,  KC_NO,
    KC_LCTL, KC_LEAD, KC_NO, KC_LALT, MO(_GLOW), KC_SPC, KC_ENT, MO(_GLOW), KC_NO, KC_NO,  KC_LEAD, KC_NO
  ),
  /* Game lower
   * ,-----------------------------------------------------------------------------------.
   * |  Tab |   1  |   2  |   3  |      |      |      |      |      |      |      | Steam|
   * |------+------+------+------+------+-------------+------+------+------+------+------|
   * |  Esc |   4  |   5  |   6  |      |      |      |      |      |      |      | F12  |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   7  |   8  |   9  |   0  |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * | Ctrl |      |      |  Alt |      | PlyPa| Next |      |      | Mute | VolD | VolUp|
   * `-----------------------------------------------------------------------------------'
   */
  [_GLOW] = LAYOUT_planck_grid(
    KC_TRNS, KC_1,    KC_2,    KC_3,    KC_PPLS, KC_NO,   KC_NO,   KC_NO, KC_NO,   KC_NO,   KC_NO,   LSFT(KC_F7),
    KC_TRNS, KC_4,    KC_5,    KC_6,    KC_PMNS, KC_NO,   KC_NO,   KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_F12,
    KC_TRNS, KC_7,    KC_8,    KC_9,    KC_0,    KC_NO,   KC_NO,   KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_MUTE,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY, KC_MNXT, KC_NO, KC_TRNS, KC_MUTE, KC_VOLD, KC_VOLU
  )
};

// tap dance declarations
int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed)  return SINGLE_TAP;
    else return SINGLE_HOLD;
  }
  else if (state->count == 2) {
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  if (state->count == 3) {
    if (state->interrupted || !state->pressed)  return TRIPLE_TAP;
    else return TRIPLE_HOLD;
  }
  else return 8;
}

static tap xtap_state = {
  .is_press_action = true,
  .state = 0
};

void lsft_finished (qk_tap_dance_state_t *state, void *user_data) {
  xtap_state.state = cur_dance(state);
  switch (xtap_state.state) {
    case SINGLE_TAP:
      register_code16(LSFT(KC_8));
      break;
    case SINGLE_HOLD:
      register_code(KC_LSFT);
      break;
    case DOUBLE_TAP:
      register_code(KC_NUBS);
      break;
    case DOUBLE_SINGLE_TAP:
      register_code(KC_NUBS);
      break;
  }
}

void lsft_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (xtap_state.state) {
    case SINGLE_TAP:
      unregister_code16(LSFT(KC_8));
      break;
    case SINGLE_HOLD:
      unregister_code(KC_LSFT);
      break;
    case DOUBLE_TAP:
      unregister_code(KC_NUBS);
      break;
    case DOUBLE_SINGLE_TAP:
      unregister_code(KC_NUBS);
      break;
  }
  xtap_state.state = 0;
}

void rsft_finished (qk_tap_dance_state_t *state, void *user_data) {
  xtap_state.state = cur_dance(state);
  switch (xtap_state.state) {
    case SINGLE_TAP:
      register_code16(LSFT(KC_9));
      break;
    case SINGLE_HOLD:
      register_code(KC_RSFT);
      break;
    case DOUBLE_TAP:
      register_code16(LSFT(KC_NUBS));
      break;
    case DOUBLE_SINGLE_TAP:
      register_code16(LSFT(KC_NUBS));
      break;
  }
}

void rsft_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (xtap_state.state) {
    case SINGLE_TAP:
      unregister_code16(LSFT(KC_9));
      break;
    case SINGLE_HOLD:
      unregister_code(KC_RSFT);
      break;
    case DOUBLE_TAP:
      unregister_code16(LSFT(KC_NUBS));
      break;
    case DOUBLE_SINGLE_TAP:
      unregister_code16(LSFT(KC_NUBS));
      break;
  }
  xtap_state.state = 0;
}

void lctl_finished (qk_tap_dance_state_t *state, void *user_data) {
  xtap_state.state = cur_dance(state);
  switch (xtap_state.state) {
    case SINGLE_TAP:
      register_mods(MOD_BIT(KC_ALGR));
      register_code(KC_7);
      break;
    case SINGLE_HOLD:
      register_code(KC_LCTL);
      break;
    case DOUBLE_TAP:
      register_mods(MOD_BIT(KC_ALGR));
      register_code(KC_8);
      break;
    case DOUBLE_SINGLE_TAP:
      register_mods(MOD_BIT(KC_ALGR));
      register_code(KC_8);
break;
  }
}

void lctl_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (xtap_state.state) {
    case SINGLE_TAP:
      unregister_code(KC_7);
      unregister_mods(MOD_BIT(KC_ALGR));
      break;
    case SINGLE_HOLD:
      unregister_code(KC_LCTL);
      break;
    case DOUBLE_TAP:
      unregister_code(KC_8);
      unregister_mods(MOD_BIT(KC_ALGR));
      break;
    case DOUBLE_SINGLE_TAP:
      unregister_code(KC_8);
      unregister_mods(MOD_BIT(KC_ALGR));
break;
  }
  xtap_state.state = 0;
}

void rctl_finished (qk_tap_dance_state_t *state, void *user_data) {
  xtap_state.state = cur_dance(state);
  switch (xtap_state.state) {
    case SINGLE_TAP:
      register_mods(MOD_BIT(KC_ALGR));
      register_code(KC_0);
      break;
    case SINGLE_HOLD:
      register_code(KC_RCTL);
      break;
    case DOUBLE_TAP:
      register_mods(MOD_BIT(KC_ALGR));
      register_code(KC_9);
      break;
    case DOUBLE_SINGLE_TAP:
      register_mods(MOD_BIT(KC_ALGR));
      register_code(KC_9);
      break;
  }
}

void rctl_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (xtap_state.state) {
    case SINGLE_TAP:
      unregister_code(KC_0);
      unregister_mods(MOD_BIT(KC_ALGR));
      break;
    case SINGLE_HOLD:
      unregister_code(KC_RCTL);
      break;
    case DOUBLE_TAP:
      unregister_code(KC_9);
      unregister_mods(MOD_BIT(KC_ALGR));
      break;
    case DOUBLE_SINGLE_TAP:
      unregister_code(KC_9);
      unregister_mods(MOD_BIT(KC_ALGR));
      break;
  }
  xtap_state.state = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_LSFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lsft_finished, lsft_reset),
  [TD_RSFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rsft_finished, rsft_reset),
  [TD_LCTL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lctl_finished, lctl_reset),
  [TD_RCTL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rctl_finished, rctl_reset),
};
