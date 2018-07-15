#include "kuatsure.h"

void tmux_prefix(void) {
  register_code(KC_LCTL);
  register_code(KC_SPC);

  unregister_code(KC_LCTL);
  unregister_code(KC_SPC);
}

void tmux_pane_zoom(void) {
  tmux_prefix();

  register_code(KC_Z);
  unregister_code(KC_Z);
}

void tmux_pane_switch(uint16_t keycode) {
  tmux_prefix();

  register_code(KC_Q);
  unregister_code(KC_Q);

  register_code(keycode);
  unregister_code(keycode);
}

void tmux_window_switch(uint16_t keycode) {
  tmux_prefix();

  register_code(keycode);
  unregister_code(keycode);
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

    // Whole Screen Shot
    SEQ_ONE_KEY(KC_A) {
      register_code(KC_LGUI);
      register_code(KC_LSFT);
      register_code(KC_3);

      unregister_code(KC_3);
      unregister_code(KC_LSFT);
      unregister_code(KC_LGUI);
    }

    // Selective Screen Shot
    SEQ_ONE_KEY(KC_S) {
      register_code(KC_LGUI);
      register_code(KC_LSFT);
      register_code(KC_4);

      unregister_code(KC_4);
      unregister_code(KC_LSFT);
      unregister_code(KC_LGUI);
    }

    // TMUX - shift to pane 1 and zoom
    SEQ_ONE_KEY(KC_J) {
      tmux_pane_switch(KC_1);
      tmux_pane_zoom();
    }

    // TMUX - shift to pane 2 and zoom
    SEQ_ONE_KEY(KC_K) {
      tmux_pane_switch(KC_2);
      tmux_pane_zoom();
    }

    // TMUX - shift to pane 3 and zoom
    SEQ_ONE_KEY(KC_L) {
      tmux_pane_switch(KC_3);
      tmux_pane_zoom();
    }

    // TMUX - shift to last pane and zoom
    SEQ_ONE_KEY(KC_SCOLON) {
      tmux_prefix();

      register_code(KC_SCOLON);
      unregister_code(KC_SCOLON);

      tmux_pane_zoom();
    }

    // TMUX - shift to first window
    SEQ_ONE_KEY(KC_U) {
      tmux_window_switch(KC_1);
    }

    // TMUX - shift to second window
    SEQ_ONE_KEY(KC_I) {
      tmux_window_switch(KC_2);
    }

    // TMUX - shift to third window
    SEQ_ONE_KEY(KC_O) {
      tmux_window_switch(KC_3);
    }
  }
}
