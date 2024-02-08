
#include "../__init__.h"

void process_magic_key(void) {
    if (alt_rep_key_count >= 2) {
        switch (queue(-4)) {
            quadruple_magic_case(KC_SPC, KC_A, KC_L, KC_R, "eady");
            quadruple_magic_case(KC_J,   KC_U, KC_D, KC_G, "ment");
        }

        switch (queue(-3)) {
            triple_magic_case(KC_M, KC_P, KC_L, "y");
            triple_magic_case(KC_Q, KC_U, KC_E, "ue");
            default: record_send_string("n"); return;
        }
    }

    switch(queue(-5)) {
        quintuple_magic_case(KC_O, KC_C, KC_R, KC_A, KC_C, "y");
    }

    switch (queue(-4)) {
        quadruple_magic_case(KC_O,   KC_L, KC_I, KC_C, "y");
        quadruple_magic_case(KC_U,   KC_R, KC_A, KC_C, "y");
        quadruple_magic_case(KC_R,   KC_M, KC_A, KC_C, "y");
        quadruple_magic_case(KC_SPC, KC_R, KC_E, KC_C, "y");
    }

    switch (queue(-3)) {
        triple_magic_switch(KC_SPC,
            double_magic_switch(KC_M,
                magic_case(KC_O, "st");
                magic_case(KC_U, "sic");
            );

            double_magic_switch(KC_A,
                magic_case(KC_L, "r");
                magic_case(KC_N, "other");
            );

            double_magic_switch(KC_E,
                magic_case(KC_D, "ge");
                magic_case(KC_X, "ample");
            );

            double_magic_case(KC_U, KC_S, "e");
            double_magic_case(KC_T, KC_I, "me");
            double_magic_case(KC_I, KC_N, "form");
        );

        triple_magic_switch(KC_B,
            double_magic_switch(KC_E,
                magic_case(KC_C, "ome");
                magic_case(KC_T, "ween");
                magic_case(KC_L, "ieve");
            );

            double_magic_case(KC_U, KC_D, "get");
        );

        triple_magic_switch(KC_V,
            double_magic_switch(KC_A,
                magic_case(KC_C, "y");
                magic_case(KC_R, "ious");
            );

            double_magic_case(KC_I, KC_D, "eo");
        );

        triple_magic_switch(KC_R,
            double_magic_case(KC_I, KC_D, "ge");
            double_magic_case(KC_E, KC_D, "ge");
        );

        triple_magic_switch(KC_S,
            double_magic_case(KC_Y, KC_S, "tem");
            double_magic_case(KC_E, KC_R, "ius");
        );

        triple_magic_switch(KC_G,
            double_magic_case(KC_A, KC_C, "y");
            double_magic_case(KC_E, KC_N, "ious");
        );

        triple_magic_switch(KC_D,
            double_magic_case(KC_I, KC_F, "feren");
            double_magic_case(KC_E, KC_F, "initely");
        );

        triple_magic_case(KC_J, KC_U, KC_D, "g");
        triple_magic_case(KC_L, KC_E, KC_D, "ge");
        triple_magic_case(KC_O, KC_B, KC_V, "ious");
        triple_magic_case(KC_H, KC_I, KC_L, "arious");
    }

    switch (queue(-2)) {
        double_magic_switch(KC_M,
            magic_case(KC_P, "l");
            magic_case(KC_A, "o");
        );

        double_magic_switch(KC_O,
            magic_case(KC_C, "k");
            magic_case(KC_T, "her");
        );

        double_magic_switch(KC_W,
            magic_case(KC_E, "b");
            magic_case(KC_A, "y");
        );

        double_magic_switch(KC_V,
            magic_case(KC_I, "ew");
            magic_case(KC_E, "ry");
            magic_case(KC_A, "lue");
        );

        double_magic_switch(KC_SPC,
            magic_case(KC_T, "hat");
            magic_case(KC_E, ".g.");
        );

        double_magic_switch(KC_U,
            magic_case(KC_C, "k");
            magic_case(KC_P, "date");
        );

        double_magic_switch(KC_P,
            magic_case(KC_L, "y");
            magic_case(KC_A, "ge");
            magic_case(KC_E, "ople");
            magic_case(KC_R, "evious");
        );

        double_magic_case(KC_I, KC_C, "k");
        double_magic_case(KC_C, KC_Y, "c");
        double_magic_case(KC_A, KC_C, "k");
        double_magic_case(KC_E, KC_C, "k");
        double_magic_case(KC_D, KC_A, "y");
        double_magic_case(KC_B, KC_E, "en");
        double_magic_case(KC_S, KC_O, "me");
        double_magic_case(KC_L, KC_I, "st");
    }

    switch (queue(-1)) {
        magic_case(KC_S,   "k");
        magic_case(KC_R,   "l");
        magic_case(KC_D,   "y");
        magic_case(KC_E,   "u");
        magic_case(KC_A,   "b");
        magic_case(KC_L,   "k");
        magic_case(KC_C,   "y");
        magic_case(KC_P,   "y");
        magic_case(KC_Y,   "p");
        magic_case(KC_K,   "s");
        magic_case(KC_G,   "y");
        magic_case(KC_O,   "a");
        magic_case(KC_U,   "e");
        magic_case(KC_X,   "t");
        magic_case(KC_I,   "on");
        magic_case(KC_V,   "er");
        magic_case(KC_Q,   "ue");
        magic_case(KC_N,   "ion");
        magic_case(KC_M,   "ent");
        magic_case(KC_J,   "ust");
        magic_case(KC_Z,   "one");
        magic_case(KC_SPC, "the");
        magic_case(KC_T,   "ment");
        magic_case(KC_W,   "hich");
        magic_case(KC_F,   "irst");
        magic_case(KC_B,   "efore");
    }
}
