
#include "../__init__.h"


void pass_td(tap_dance_state_t *state, void *user_data) {
    if (state->count % 2 == 0) tap_code16(KC_ENT);
    else SEND_STRING(PASSWORD_STR);
}

void exlm_td(tap_dance_state_t *state, void *user_data) {
    double_sequence_td(
        ,
        execute_without_mods(
            tap_code16(C(KC_LEFT));
            tap_code16(KC_SPC);
            tap_code16(C(KC_RIGHT));
            send_lang_independant_string(" None:");
        ),
        execute_without_mods(
            tap_code16(S(KC_ENT));
            tap_code16(S(KC_ENT));
            send_lang_independant_string("```");
            tap_code16(KC_UP);
        ),
        send_lang_independant_string("="),

        ,
        send_lang_independant_string("->"),
        send_lang_independant_string("```"),
        send_lang_independant_string("!")
    );
}

void eql_td(tap_dance_state_t *state, void *user_data) {
    if (state->count % 3 == 0 && is_shift_held()) {
        send_lang_independant_string(" 1");
    } else if (state->count % 3 == 0 && is_ctrl_held()) {
        send_lang_independant_string(";");
    } else double_sequence_td(
        execute_without_mods(tap_code(KC_ENT)),
        send_lang_independant_string("="),
        send_lang_independant_string(")"),
        send_lang_independant_string("="),

        send_lang_independant_string("{"),
        send_lang_independant_string("+"),
        send_lang_independant_string("("),
        send_lang_independant_string("=")
    );
}

void dqt_td(tap_dance_state_t *state, void *user_data) {
    double_sequence_td(
        , , , {
            send_lang_independant_string("\"\"");
            tap_code(KC_ENT);
        },

        send_lang_independant_string("}"),
        send_lang_independant_string("'"),
        send_lang_independant_string(")"),
        send_lang_independant_string("\"")
    );
}

void bsls_td(tap_dance_state_t *state, void *user_data) {
    double_sequence_td(
        send_lang_independant_string("~"),
        send_lang_independant_string("|"),
        send_lang_independant_string("`"),
        send_lang_independant_string("n"),

        send_lang_independant_string("~"),
        send_lang_independant_string("|"),
        send_lang_independant_string("`"),
        send_lang_independant_string("\\")
    );
}

void unds_td(tap_dance_state_t *state, void *user_data) {
    if (state->count % 3 == 0 && is_shift_held()) {
        send_lang_independant_string(" 1");
    } else double_sequence_td(
        send_lang_independant_string("="),
        send_lang_independant_string("="),
        send_lang_independant_string("]"),
        send_lang_independant_string("_"),

        send_lang_independant_string("<"),
        send_lang_independant_string("-"),
        send_lang_independant_string("["),
        send_lang_independant_string("_")
    );
}

void coln_td(tap_dance_state_t *state, void *user_data) {
    double_sequence_td(
        send_lang_independant_string("="),
        send_lang_independant_string(";"),
        execute_without_mods(tap_code(KC_ENT)),
        execute_without_mods(tap_code(KC_ENT)),

        send_lang_independant_string(">"),
        send_lang_independant_string(";"),
        send_lang_independant_string("]"),
        send_lang_independant_string(":")
    );
}

void arr_td(tap_dance_state_t *state, void *user_data) {
    double_sequence_td(
        , ,
        send_lang_independant_string("${"),
        {
            send_lang_independant_string(" {");
            execute_without_mods(tap_code(KC_ENT));
        },

        {
            send_lang_independant_string("() => {");
            execute_without_mods(tap_code(KC_ENT));
        },
        ,
        send_lang_independant_string("${"),
        send_lang_independant_string("=>")
    );
}

void eclp_td(tap_dance_state_t *state, void *user_data) {
    triple_sequence_td(
        ,
        execute_without_mods(delete_line()),
        execute_without_mods(delete_line()),
        {
            if (highest_layer >= NAV) {
                tap_code16(C(S((KC_T))));
            } else {
                send_lang_independant_string("...");
            }
        },

        ,
        execute_without_mods(delete_line()),
        execute_without_mods(tap_code16(C(KC_V))),
        {
            if (highest_layer >= NAV) {
                tap_code16(C(S((KC_T))));
            } else {
                send_lang_independant_string("...");
            }
        },

        ,
        execute_without_mods(copy_line()),
        execute_without_mods(delete_line()),
        {
            if (highest_layer >= NAV) {
                tap_code16(C(S((KC_T))));
            } else {
                send_lang_independant_string("...");
            }
        }
    );
}

void sall_td(tap_dance_state_t *state, void *user_data) {
    if (state->count % 2 == 0) tap_code16(C(KC_C));
    else tap_code16(C(KC_A));
}

void md_td(tap_dance_state_t *state, void *user_data) {
    sequence_td(
        {
            send_lang_independant_string("[](<>)");
            execute_without_mods(multi_tap(KC_LEFT, 5));
        },

        {
            send_lang_independant_string("[]()");
            execute_without_mods(multi_tap(KC_LEFT, 3));
        },

        ,

        {
            send_lang_independant_string("<>");
            tap_code16(KC_LEFT);
        }
    );
}

void quote_line(const char *string) {
    tap_code16(KC_HOME);
    send_lang_independant_string(string);
    tap_code16(KC_END);
}

void select_line(void) {
    tap_code16(KC_END);
    tap_code16(S(KC_HOME));
}

void cut_line(void) {
    select_line();
    tap_code16(C(KC_X));
}

void copy_line(void) {
    select_line();

    tap_code16(C(KC_C));
    tap_code16(KC_END);
}

void delete_line(void) {
    select_line();
    tap_code16(KC_BSPC);
}
