
#include "../__init__.h"

enum languages current_lang = ENG;
enum language_modes language_mode = TRIPPLE;

void cycle_language(int swaps_count, enum languages new_lang) {
    bool do_invert = current_lang == ENG || new_lang == ENG;

    multi_tap(A(KC_LSFT), swaps_count);
    current_lang = new_lang;

    if (do_invert)
        layer_invert(QWERTY);
}

void tri_eng_tap_action(void)   { cycle_language(1, RU);  }
void tri_ru_tap_action(void)    { cycle_language(2, ENG); }
void tri_ua_tap_action(void)    { cycle_language(1, ENG); }

void tri_eng_hold_action(void)  { cycle_language(2, UA);  }
void tri_ru_hold_action(void)   { cycle_language(1, UA);  }
void tri_ua_hold_action(void)   { cycle_language(2, RU);  }

void double_ru_tap_action(void) { cycle_language(1, ENG); }

void (*tri_tap_actions[])(void) = {
    [ENG] = tri_eng_tap_action,
    [RU] = tri_ru_tap_action,
    [UA] = tri_ua_tap_action
};

void (*tri_hold_actions[])(void) = {
    [ENG] = tri_eng_hold_action,
    [RU] = tri_ru_hold_action,
    [UA] = tri_ua_hold_action
};

void (*double_tap_actions[])(void) = {
    [ENG] = tri_eng_tap_action,
    [RU] = double_ru_tap_action
};

void (*double_hold_actions[])(void) = {
    [ENG] = tri_eng_tap_action,
    [RU] = double_ru_tap_action
};
