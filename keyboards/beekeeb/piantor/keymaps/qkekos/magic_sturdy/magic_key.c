
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

    switch (queue(-3)) {
        quadruple_magic_case(KC_O,   KC_L,  LT_I,  KC_C, "y");
        quadruple_magic_case(KC_U,   CLT_R, CLT_A, KC_C, "y");
        quadruple_magic_case(CLT_R,  KC_M,  CLT_A, KC_C, "y");
        quadruple_magic_case(TH_NUM, CLT_R, ALT_E, KC_C, "y");
        quadruple_magic_case(KC_C,   KC_R,  CLT_A, KC_C, "y");
    }

    switch (queue(-2)) {
        triple_magic_switch(TH_NUM,
            double_magic_switch(KC_M,
                magic_case(KC_O, "st");
                magic_case(KC_U, "sic");
            );

            double_magic_case(CLT_A, KC_L,  "r");
            double_magic_case(KC_U,  GLT_S, "e");
            double_magic_case(LT_I,  SMT_N, "form");
            double_magic_case(ALT_E, KC_X,  "ample");
        );

        triple_magic_case(KC_V,  CLT_A, KC_C,  "y");
        triple_magic_case(KC_G,  CLT_A, KC_C,  "y");
        triple_magic_case(GLT_S, KC_Y,  GLT_S, "tem");
        triple_magic_case(KC_O,  KC_B,  KC_V,  "iously");
    }

    switch (last_queue_key) {
        double_magic_switch(KC_M,
            magic_case(KC_P,  "l");
            magic_case(CLT_A, "o");
        );

        double_magic_switch(KC_O,
            magic_case(KC_C,  "k");
            magic_case(ALT_T, "her");
        );

        double_magic_switch(KC_W,
            magic_case(ALT_E, "b");
            magic_case(CLT_A, "y");
        );

        double_magic_case(LT_I,   KC_C,  "k");
        double_magic_case(KC_U,   KC_C,  "k");
        double_magic_case(KC_C,   KC_Y,  "c");
        double_magic_case(CLT_A,  KC_C,  "k");
        double_magic_case(ALT_E,  KC_C,  "k");
        double_magic_case(SMT_D,  CLT_A, "y");
        double_magic_case(GLT_S,  KC_O,  "me");
        double_magic_case(KC_V,   LT_I,  "ew");
        double_magic_case(KC_L,   LT_I,  "st");
        double_magic_case(KC_B,   ALT_E, "en");
        double_magic_case(TH_NUM, ALT_E, ".g.");
        double_magic_case(KC_P,   ALT_E, "ople");
    }

    switch (keycode) {
        magic_case(KC_L,   "k");
        magic_case(KC_C,   "y");
        magic_case(KC_P,   "y");
        magic_case(KC_Y,   "p");
        magic_case(KC_K,   "s");
        magic_case(KC_G,   "y");
        magic_case(KC_O,   "a");
        magic_case(KC_U,   "e");
        magic_case(KC_X,   "t");
        magic_case(GLT_S,  "k");
        magic_case(CLT_R,  "l");
        magic_case(SMT_D,  "y");
        magic_case(ALT_E,  "u");
        magic_case(LT_I,   "on");
        magic_case(KC_V,   "er");
        magic_case(KC_Q,   "ue");
        magic_case(KC_M,   "ent");
        magic_case(KC_J,   "ust");
        magic_case(KC_Z,   "one");
        magic_case(SMT_N,  "ion");
        magic_case(TH_NUM, "the");
        magic_case(ALT_T,  "ment");
        magic_case(KC_W,   "hich");
        magic_case(KC_F,   "irst");
        magic_case(KC_B,   "efore");
        remember_magic_case(CLT_A, "b", KC_B);
    }
}
