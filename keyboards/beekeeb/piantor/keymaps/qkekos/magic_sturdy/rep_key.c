
#include "../__init__.h"

void process_rep_key(void) {
    if (rep_key_count == 2) {
        switch(queue(-4)) {
            quadruple_magic_case(KC_P, KC_O, KC_S, KC_S, "ible");
            quadruple_magic_case(KC_T, KC_I, KC_O, KC_N, "ality");
        }
    }

    switch (queue(-3)) {
        triple_magic_switch(KC_D,
            double_magic_case(KC_E, KC_F, "ault");
            double_magic_case(KC_I, KC_F, "ficult");
        );

        triple_magic_switch(KC_A,
            double_magic_case(KC_N, KC_Y, "way");
            double_magic_case(KC_W, KC_K, "ward");
        );

        triple_magic_switch(KC_I,
            double_magic_case(KC_N, KC_C, "rease");
            double_magic_case(KC_M, KC_P, "ossible");
        );

        triple_magic_switch(KC_C,
            double_magic_case(KC_O, KC_U, "rse");
            double_magic_case(KC_A, KC_P, "able");
        );

        triple_magic_case(KC_SPC, KC_A, KC_B, "out");
        triple_magic_case(KC_P,   KC_R, KC_O, "gram");
        triple_magic_case(KC_H,   KC_O, KC_W, "ever");
        triple_magic_case(KC_U,   KC_N, KC_I, "versity");
    }

    switch (queue(-2)) {
        double_magic_switch(KC_SPC,
            magic_case(KC_I, "i");
            magic_case(KC_B, "ecause");
        );

        double_magic_switch(KC_F,
            magic_case(KC_R, "om");
            magic_case(KC_U, "nction");
        );

        double_magic_switch(KC_M,
            magic_case(KC_A, "ke");
            magic_case(KC_U, "st");
        );

        double_magic_case(KC_L, KC_A, "st");
        double_magic_case(KC_S, KC_C, "hool");
    }

    switch (queue(-1)) {
        magic_case(KC_X,   "es");
        magic_case(KC_I,   "ng");
        magic_case(KC_Y,   "ou");
        magic_case(KC_Q,   "ui");
        magic_case(KC_V,   "er");
        magic_case(KC_J,   "oin");
        magic_case(KC_SPC, "for");
        magic_case(KC_W,   "ould");
        default: tap_code16(queue(-1)); enqueue(queue(-1));
    }
}
