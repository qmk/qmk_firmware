#include "kb.h"

#define SUPER_A  LSFT_T(KC_A)
#define SUPER_S  LCTL_T(KC_S)
#define SUPER_D  LALT_T(KC_D)
#define SUPER_F  LCMD_T(KC_F)

#define SUPER_J    RCMD_T(KC_J)
#define SUPER_K    RALT_T(KC_K)
#define SUPER_L    RCTL_T(KC_L)
#define SUPER_CLN  RSFT_T(KC_SCLN)

#define SUPER_1    LSFT_T(KC_1)
#define SUPER_2    LCTL_T(KC_2)
#define SUPER_3    LALT_T(KC_3)
#define SUPER_4    LCMD_T(KC_4)

#define SUPER_7    RCMD_T(KC_7)
#define SUPER_8    RALT_T(KC_8)
#define SUPER_9    RCTL_T(KC_9)
#define SUPER_0    RSFT_T(KC_0)
#define TERM       HYPR(KC_T)
#define LANG       LCMD(KC_SPC)
#define SPOTL      LALT(KC_SPC)
#define L1SPC      LT(1, KC_SPC)
#define L2SPC      LT(2, KC_SPC)
#define L2SFT      LM(1, MOD_RSFT)


bool is_cmd_tab_active = false;

enum custom_keycodes {
  CMD_TAB = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// L0
	KEYMAP(
    KC_ESC,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,    KC_I,     KC_O,     KC_P,      KC_BSPC,
    KC_TAB,   SUPER_A,  SUPER_S,  SUPER_D,  SUPER_F,  KC_G,     KC_H,     SUPER_J, SUPER_K,  SUPER_L,  SUPER_CLN, KC_QUOT,
    KC_GRV,   KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,   KC_ENT,
    CMD_TAB,  KC_BSLS,  TERM,     KC_LCMD,  L1SPC,    KC_LEAD,  KC_HYPR,  L2SPC,   L2SFT,    KC_LBRC,  KC_RBRC,   SPOTL),

// L1
	KEYMAP(
    _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_BSPC,
    _______,  SUPER_1,  SUPER_2,  SUPER_3,  SUPER_4,  KC_5,     KC_6,     SUPER_7,  SUPER_8,  SUPER_9,  SUPER_0,   _______,
    _______,  KC_F11,   KC_F12,   KC_F13,   KC_LBRC,  KC_MINS,  KC_EQL,   KC_RBRC,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______),

// L2
	KEYMAP(
    _______,       XXXXXXX,  XXXXXXX,  KC_MS_WH_UP,   XXXXXXX,  KC_MS_BTN1,     KC_MS_BTN2,  KC_HOME,  KC_PGUP,  XXXXXXX,   XXXXXXX,  KC_MUTE,
    KC_MS_WH_LEFT, KC_LSFT,  KC_LCTL,  KC_LALT,       KC_LCMD,  KC_MS_WH_RIGHT, KC_LEFT,     KC_DOWN,  KC_UP,    KC_RIGHT,  KC_PGDN,  KC_DEL,
    XXXXXXX,       XXXXXXX,  XXXXXXX,  KC_MS_WH_DOWN, XXXXXXX,  XXXXXXX,        KC_SLEP,     KC_END,   KC_PGDN,  XXXXXXX,   XXXXXXX,  XXXXXXX,
    _______,       KC_BRID,  KC_BRIU,  _______,       _______,  _______,        _______,     _______,  _______,  KC_VOLD,   KC_VOLU,  _______),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case CMD_TAB:
        if (record->event.pressed) {
            register_code(KC_LCMD);
            register_code(KC_TAB);
            unregister_code(KC_TAB);
            layer_on(2);
        } else {
            unregister_code(KC_LCMD);
            layer_off(2);
        }
        break;
    case KC_ESC:
        layer_clear();
  }
  return true;
}

LEADER_EXTERNS();

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    // Cancel task CTRL+C
    SEQ_ONE_KEY(KC_C) {
      SEND_STRING(SS_LCTL("c"));
    }
    // copy
    SEQ_ONE_KEY(KC_Y) {
      SEND_STRING(SS_LCMD("c"));
    }
    // cut
    SEQ_ONE_KEY(KC_X) {
      SEND_STRING(SS_LCMD("x"));
    }
    // paste
    SEQ_ONE_KEY(KC_P) {
      SEND_STRING(SS_LCMD("v"));
    }
    // undo
    SEQ_ONE_KEY(KC_U) {
      SEND_STRING(SS_LCMD("z"));
    }
    // redo
    SEQ_ONE_KEY(KC_R) {
      SEND_STRING(SS_LCMD(SS_LSFT("z")));
    }
    // delete line
    SEQ_TWO_KEYS(KC_D, KC_D) {
      register_code(KC_LGUI);

      register_code(KC_RIGHT);
      unregister_code(KC_RIGHT);

      register_code(KC_BSPACE);
      unregister_code(KC_BSPACE);

      unregister_code(KC_LGUI);
    }
    // go to the beginning of the string
    SEQ_ONE_KEY(KC_H) {
      register_code(KC_LCMD);
      register_code(KC_LEFT);
      unregister_code(KC_LEFT);
      unregister_code(KC_LCMD);
    }
    // go to the end of the string
    SEQ_ONE_KEY(KC_L) {
      register_code(KC_LCMD);
      register_code(KC_RIGHT);
      unregister_code(KC_RIGHT);
      unregister_code(KC_LCMD);
    }
  }
}
