
#include "../__init__.h"

void process_rep_key(void) {
    switch (queue(-3)) {
        triple_magic_switch(KC_D,
            double_magic_case(KC_E, KC_F, "ault");
            double_magic_case(KC_I, KC_F, "ficult");
        );

        triple_magic_case(KC_A,   KC_N, KC_Y, "way");
        triple_magic_case(KC_SPC, KC_A, KC_B, "out");
        triple_magic_case(KC_C,   KC_A, KC_P, "able");
        triple_magic_case(KC_U,   KC_N, KC_I, "versity");
    }

    switch (queue(-2)) {
        double_magic_switch(KC_SPC,
            magic_case(KC_I, "i");
            magic_case(KC_B, "ecause");
        );

        double_magic_case(KC_F, KC_R, "om");
        double_magic_case(KC_L, KC_A, "st");
        double_magic_case(KC_M, KC_A, "ke");
        double_magic_case(KC_S, KC_C, "hool");
    }

    switch (queue(-1)) {
        magic_case(KC_X,   "es");
        magic_case(KC_I,   "ng");
        magic_case(KC_Y,   "ou");
        magic_case(KC_Q,   "ui");
        magic_case(KC_J,   "oin");
        magic_case(KC_SPC, "for");
        magic_case(KC_W,   "ould");
        default: tap_code16(queue(-1)); enqueue(queue(-1));
    }
}
