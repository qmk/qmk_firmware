
#include "../__init__.h"

void process_rep_key(uint16_t keycode, uint8_t mods) {
    switch (prev_last_key) {
        double_magic_case(LHR_A,
            magic_case(KC_B, "out");
        );

        double_magic_case(KC_F,
            magic_case(LHR_R, "om");
        );
    }

    switch (keycode) {
        magic_case(KC_X, "t");
        magic_case(HR_I, "ng");
        magic_case(KC_Y, "ou");
        magic_case(KC_Q, "ui");
        magic_case(KC_F, "or");
        magic_case(KC_J, "oin");
        magic_case(TH_NUM, "for");
        magic_case(KC_W, "ould");
        magic_case(KC_B, "ecause");
        default: tap_code16(keycode);
    }
}
