#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* LAYER 0
 * ,---------------------------------------,
 * |   1   |   2   |   3   |   4   |   5   |  Knob
 * '---------------------------------------'
 */
[0] = LAYOUT( \
  KC_NO,       KC_NO,      KC_MEDIA_PREV_TRACK,       KC_MEDIA_PLAY_PAUSE,      KC_MEDIA_NEXT_TRACK
),

};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code(KC_AUDIO_VOL_UP);
        } else {
            tap_code(KC_AUDIO_VOL_DOWN);
        }
    }
}


