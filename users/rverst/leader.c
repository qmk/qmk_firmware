#include "leader.h"

#ifdef AUDIO_ENABLE
float leader_audio_start[][2] = SONG(ONE_UP_SOUND );
float leader_audio_ok[][2] = SONG(ALL_STAR);
float leader_audio_nok[][2] = SONG(RICK_ROLL);
#endif

#ifdef RGBLIGHT_ENABLE
int leader_color_start = 1;
int leader_color_ok = 2;
int leader_color_nok = 3;
#endif

bool leader_succeed;

LEADER_EXTERNS();


void matrix_scan_leader(void) {

    LEADER_DICTIONARY() {
        leader_succeed = leading = false;
        int mode = os_mode();

        SEQ_ONE_KEY(KC_A) {

        }

        // mac - set mode for MacOS
        SEQ_THREE_KEYS(KC_M, KC_A, KC_C) {
            set_mode(MAC);
            leader_succeed = true;
        }

        // lxn - set mode for Linux
        SEQ_THREE_KEYS(KC_L, KC_N, KC_X) {
            set_mode(LINUX);
            leader_succeed = true;
        }

        // linux - set mode for Linux
        SEQ_FIVE_KEYS(KC_L, KC_I, KC_N, KC_U, KC_X) {
            set_mode(LINUX);
            leader_succeed = true;
        }

        // win - set mode for Windows
        SEQ_THREE_KEYS(KC_W, KC_I, KC_N) {
            set_mode(WINDOWS);
            leader_succeed = true;
        }
        leader_end();
    }
}

__attribute__((weak))
void leader_start_keymap(void) {}

void leader_start(void) {
#ifdef AUDIO_ENABLE
      PLAY_SONG(leader_audio_start);
#endif
#ifdef RGBLIGHT_ENABLE
      rgblight_sethsv_noeeprom(HSV_GREEN);
      rgblight_mode_noeeprom(RGBLIGHT_MODE_KNIGHT)
#endif
    leader_start_keymap();
}

__attribute__((weak))
void leader_end_keymap(void) {}

void leader_end(void) {
    if (leader_succeed) {
#ifdef AUDIO_ENABLE
      PLAY_SONG(leader_audio_ok);
#endif
    } else {
#ifdef AUDIO_ENABLE
      PLAY_SONG(leader_audio_nok);
#endif
    }
    leader_end_keymap();
}
