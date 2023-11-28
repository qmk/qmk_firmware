
#include "../__init__.h"

void process_rep_key(uint16_t keycode, uint8_t mods) {
    if (timer_elapsed(last_key_pressed_time) > MAGIC_KEY_TIMEOUT) {
        keycode = TH_NUM;
    }

    switch (last_queue_key) {
        double_magic_case(KC_F,  CLT_R, "om");
        double_magic_case(KC_L,  CLT_A, "st");
        double_magic_case(CLT_A, KC_B,  "out");
    }

    switch (keycode) {
        magic_case(KC_X,   "es");
        magic_case(LT_I,   "ng");
        magic_case(KC_Y,   "ou");
        magic_case(KC_Q,   "ui");
        magic_case(KC_J,   "oin");
        magic_case(TH_NUM, "for");
        magic_case(KC_W,   "ould");
        magic_case(KC_B,   "ecause");
        default: tap_code16(keycode);
    }
}
