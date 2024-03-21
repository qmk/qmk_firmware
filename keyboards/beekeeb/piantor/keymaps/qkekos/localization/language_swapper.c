
#include "../__init__.h"

enum languages current_lang = ENG;
enum language_modes language_mode = TRIPLE;

char *get_language_str(enum languages language) {
    switch (language) {
        case ENG:
            return "en";

        case RU:
            return "ru";

        case UA:
            return "ua";

        default:
            return "en";
    }
}

void swap_to(enum languages new_lang) {
    bool do_invert = current_lang == ENG || new_lang == ENG;

    uprintf("qmk_language_swap: %s\n", get_language_str(new_lang));
    current_lang = new_lang;

    if (do_invert) {
        layer_invert(QWERTY);
        autocorrect_toggle();
        toggle_magic_training();
    }
}

void tri_eng_tap_action(void)   { swap_to(RU);  }
void tri_ru_tap_action(void)    { swap_to(ENG); }
void tri_ua_tap_action(void)    { swap_to(ENG); }

void tri_eng_hold_action(void)  { swap_to(UA);  }
void tri_ru_hold_action(void)   { swap_to(UA);  }
void tri_ua_hold_action(void)   { swap_to(RU);  }

void double_ru_tap_action(void) { tri_ua_tap_action(); }

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
