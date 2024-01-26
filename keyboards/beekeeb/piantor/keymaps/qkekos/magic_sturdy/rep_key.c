
#include "../__init__.h"

void process_rep_key(void) {
    switch (queue(-3)) {
        triple_magic_case(TH_NUM, CLT_A, KC_B, "out");
        triple_magic_case(CLT_A,  SMT_N, KC_Y, "way");
    }

    switch (queue(-2)) {
        double_magic_switch(TH_NUM,
            magic_case(KC_B, "ecause");
            magic_case(LT_I, "i");
        );

        double_magic_case(KC_F,   CLT_R, "om");
        double_magic_case(KC_L,   CLT_A, "st");
    }

    switch (queue(-1)) {
        magic_case(KC_X,   "es");
        magic_case(LT_I,   "ng");
        magic_case(KC_Y,   "ou");
        magic_case(KC_J,   "oin");
        magic_case(TH_NUM, "for");
        magic_case(KC_W,   "ould");
        remember_magic_case(KC_Q, "ui", LT_I);
        default: tap_code16(queue(-1));
    }
}
