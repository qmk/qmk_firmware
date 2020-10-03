#include "kb.h"

#define CTRL_A LCTL_T(KC_A)
#define ALT_S  LALT_T(KC_S)
#define CMD_D  LCMD_T(KC_D)
#define SFT_F  LSFT_T(KC_F)

#define SFT_J    RSFT_T(KC_J)
#define CMD_K    RCMD_T(KC_K)
#define ALT_L    RALT_T(KC_L)
#define CTRL_CLN RCTL_T(KC_SCLN)

#define CTRL_1 LCTL_T(KC_1)
#define ALT_2  LALT_T(KC_2)
#define CMD_3  LCMD_T(KC_3)
#define SFT_4  LSFT_T(KC_4)

#define SFT_7    RSFT_T(KC_7)
#define CMD_8    RCMD_T(KC_8)
#define ALT_9    RALT_T(KC_9)
#define CTRL_0   RCTL_T(KC_0)

#define NEXT_W  LCMD(KC_GRV)
#define LANG    LCMD(KC_SPC)
#define SPOTL   LALT(KC_SPC)
#define L2SPC   LT(2, KC_SPC)


bool is_cmd_tab_active = false;

enum custom_keycodes {
  CMD_TAB = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// L0
	KEYMAP(
    KC_GRV,   KC_Q,     KC_W,     KC_E,     KC_R,   KC_T,     KC_Y,     KC_U,   KC_I,     KC_O,     KC_P,      KC_LBRC,
    KC_TAB,   CTRL_A,   ALT_S,    CMD_D,    SFT_F,  KC_G,     KC_H,     SFT_J,  CMD_K,    ALT_L,    CTRL_CLN,  KC_QUOT,
    KC_BSLS,  KC_Z,     KC_X,     KC_C,     KC_V,   KC_B,     KC_N,     KC_M,   KC_COMM,  KC_DOT,   KC_SLSH,   KC_RBRC,
    TG(1),    CMD_TAB,  NEXT_W,   KC_ESC,   L2SPC,  KC_LEAD,  KC_ENT,   L2SPC,  KC_BSPC,  LANG,     SPOTL,     TG(1)),

// L1
	KEYMAP(
    _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_DEL,
    _______,  CTRL_1,   ALT_2,    CMD_3,    SFT_4,    KC_5,     KC_6,     SFT_7,    CMD_8,    ALT_9,    CTRL_0,   _______,
    _______,  KC_F11,   KC_F12,   KC_F13,   KC_LBRC,  KC_MINS,  KC_EQL,   KC_RBRC,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______),

// L2
	KEYMAP(
    KC_SLEP,       XXXXXXX,  XXXXXXX,  KC_MS_WH_UP,   XXXXXXX,  KC_MS_BTN1,     KC_MS_BTN2,  KC_HOME,  KC_PGUP,  XXXXXXX,   XXXXXXX,  KC_MUTE,
    KC_MS_WH_LEFT, KC_LSFT,  KC_LCTL,  KC_LALT,       KC_LCMD,  KC_MS_WH_RIGHT, KC_LEFT,     KC_DOWN,  KC_UP,    KC_RIGHT,  KC_PGDN,  KC_DEL,
    KC_BRID,       XXXXXXX,  XXXXXXX,  KC_MS_WH_DOWN, XXXXXXX,  XXXXXXX,        XXXXXXX,     KC_END,   KC_PGDN,  XXXXXXX,   XXXXXXX,  KC_BRIU,
    KC_VOLD,       _______,  _______,  _______,       _______,  _______,        _______,     _______,  _______,  _______,   _______,  KC_VOLU),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case CMD_TAB:
        if (record->event.pressed) {
            register_code(KC_LCMD);
            register_code(KC_TAB);
            unregister_code(KC_TAB);
        } else {
            unregister_code(KC_LCMD);
        }
        break;
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
