#include "kuatsure.h"
#include "version.h"

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_LBRC] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_LT),
  [TD_RBRC] = ACTION_TAP_DANCE_DOUBLE(KC_RBRC, KC_GT),
  [TD_SLSH] = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, KC_BSLS),
};

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KB_MAKE:
      if (!record->event.pressed) {
        SEND_STRING("make " QMK_KEYBOARD ":" QMK_KEYMAP SS_TAP(X_ENTER));
      }
      return false;
      break;

    case KB_VRSN:
      if (!record->event.pressed) {
        SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;

    case KB_FLSH:
      if (!record->event.pressed) {
        SEND_STRING(
          "qmk flash -kb " QMK_KEYBOARD " -km " QMK_KEYMAP
        );

        reset_keyboard();
      }
      return false;
      break;
  }

  return process_record_keymap(keycode, record);
}

void tmux_prefix(void) {
  tap_code16(LCTL(KC_SPC));
}

void tmux_pane_zoom(void) {
  tmux_prefix();

  SEND_STRING("z");
}

LEADER_EXTERNS();
void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    // Available seqs
    // SEQ_ONE_KEY, SEQ_TWO_KEYS, SEQ_THREE_KEYS
    // anything you can do in a macro https://docs.qmk.fm/macros.html
    // https://docs.qmk.fm/feature_leader_key.html

    // Stop music and lock computer via alfred
    SEQ_ONE_KEY(KC_H) {
      SEND_STRING(SS_LGUI(" ") SS_TAP(X_LGUI) "afk" SS_TAP(X_ENTER));
    }

    // Stop music and lock computer via alfred
    SEQ_TWO_KEYS(KC_H, KC_H) {
      SEND_STRING(SS_LGUI(" ") SS_TAP(X_LGUI) "afk" SS_TAP(X_ENTER) SS_TAP(X_MEDIA_PLAY_PAUSE));
    }

    // Whole Screen Shot
    SEQ_ONE_KEY(KC_A) {
      SEND_STRING(SS_LGUI(SS_LSFT("3")));
    }

    // Selective Screen Shot
    SEQ_ONE_KEY(KC_S) {
      SEND_STRING(SS_LGUI(SS_LSFT("4")));
    }

    // TMUX - shift to pane 1 and zoom
    SEQ_ONE_KEY(KC_J) {
      tmux_prefix();
      SEND_STRING("q1");
      tmux_pane_zoom();
    }

    // TMUX - shift to first window
    SEQ_TWO_KEYS(KC_J, KC_J) {
      tmux_prefix();
      SEND_STRING("1");
    }

    // TMUX - shift to pane 2 and zoom
    SEQ_ONE_KEY(KC_K) {
      tmux_prefix();
      SEND_STRING("q2");
      tmux_pane_zoom();
    }

    // TMUX - shift to second window
    SEQ_TWO_KEYS(KC_K, KC_K) {
      tmux_prefix();
      SEND_STRING("2");
    }

    // TMUX - shift to pane 3 and zoom
    SEQ_ONE_KEY(KC_L) {
      tmux_prefix();
      SEND_STRING("q3");
      tmux_pane_zoom();
    }

    // TMUX - shift to third window
    SEQ_TWO_KEYS(KC_L, KC_L) {
      tmux_prefix();
      SEND_STRING("3");
    }

    // TMUX - shift to last pane and zoom
    SEQ_ONE_KEY(KC_SEMICOLON) {
      tmux_prefix();
      SEND_STRING(";");
      tmux_pane_zoom();
    }
  }
}
