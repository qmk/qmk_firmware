
#include "../__init__.h"

void process_magic_key(uint16_t keycode, uint8_t mods) {
    if (alt_rep_key_count >= 2) {
        switch (keycode) {
            case KC_Q:
                break;

            default:
                SEND_STRING("n");
                return;
        }
    }

    if (timer_elapsed(last_key_pressed_time) > MAGIC_KEY_TIMEOUT) {
        keycode = TH_NUM;
    }

    switch (penultimate_queue_key) {
        triple_magic_switch(TH_NUM,
            double_magic_switch(KC_M,
                magic_case(KC_O, "st");
                magic_case(KC_U, "sic");
            );

            double_magic_case(KC_U, LHR_S, "e");
            double_magic_case(HR_I, MHR_N, "form");
            double_magic_case(LHR_E, KC_X, "ample");
        );

        triple_magic_case(LHR_S, KC_Y, LHR_S, "tem");
    }

    switch (last_queue_key) {
        double_magic_switch(KC_M,
            magic_case(KC_P, "l");
            magic_case(LHR_A, "o");
        );

        double_magic_switch(KC_O,
            magic_case(KC_C, "k");
            magic_case(LHR_T, "her");
        );

        double_magic_case(HR_I, KC_C, "k");
        double_magic_case(KC_U, KC_C, "k");
        double_magic_case(KC_C, KC_Y, "c");
        double_magic_case(KC_W, LHR_E, "b");
        double_magic_case(LHR_A, KC_C, "k");
        double_magic_case(KC_V, HR_I, "ew");
        double_magic_case(KC_L, HR_I, "st");
        double_magic_case(LHR_E, KC_C, "k");
        double_magic_case(LHR_S, KC_O, "me");
        double_magic_case(MHR_D, LHR_A, "y");
        double_magic_case(KC_B, LHR_E, "en");
        double_magic_case(KC_P, LHR_E, "ople");
        double_magic_case(TH_NUM, LHR_E, ".g.");
    }

    switch (keycode) {
        magic_case(KC_L, "k");
        magic_case(KC_C, "y");
        magic_case(KC_P, "y");
        magic_case(KC_Y, "p");
        magic_case(KC_K, "s");
        magic_case(KC_G, "y");
        magic_case(KC_O, "a");
        magic_case(KC_U, "e");
        magic_case(KC_X, "t");
        magic_case(LHR_S, "k");
        magic_case(LHR_R, "l");
        magic_case(MHR_D, "y");
        magic_case(LHR_E, "u");
        magic_case(HR_I, "on");
        magic_case(KC_V, "er");
        magic_case(KC_Q, "ue");
        magic_case(KC_M, "ent");
        magic_case(KC_J, "ust");
        magic_case(KC_Z, "one");
        magic_case(MHR_N, "ion");
        magic_case(KC_W, "hich");
        magic_case(KC_F, "irst");
        magic_case(TH_NUM, "the");
        magic_case(LHR_T, "ment");
        magic_case(KC_B, "efore");
        remember_magic_case(LHR_A, "b", KC_B);
    }
}
