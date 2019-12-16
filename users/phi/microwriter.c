#include "microwriter.h"

uint16_t default_table[] = {
    /* _____ */ KC_NO,
    /* ____* */ KC_U,
    /* ___*_ */ KC_S,
    /* ___** */ KC_G,
    /* __*__ */ KC_O,
    /* __*_* */ KC_Q,
    /* __**_ */ KC_N,
    /* __*** */ KC_B,
    /* _*___ */ KC_E,
    /* _*__* */ KC_V,
    /* _*_*_ */ KC_T,
    /* _*_** */ KC_COMM,
    /* _**__ */ KC_A,
    /* _**_* */ KC_MINS,
    /* _***_ */ KC_DOT,
    /* _**** */ KC_M,
    /* *____ */ KC_SPC,
    /* *___* */ KC_H,
    /* *__*_ */ KC_K,
    /* *__** */ KC_J,
    /* *_*__ */ KC_C,
    /* *_*_* */ KC_Z,
    /* *_**_ */ KC_Y,
    /* *_*** */ KC_X,
    /* **___ */ KC_I,
    /* **__* */ KC_L,
    /* **_*_ */ KC_R,
    /* **_** */ KC_W,
    /* ***__ */ KC_D,
    /* ***_* */ KC_QUOT,
    /* ****_ */ KC_F,
    /* ***** */ KC_P
};

uint16_t number_table[] = {
    /* _____ */ KC_NO,
    /* ____* */ KC_6,
    /* ___*_ */ KC_NO,
    /* ___** */ KC_7,
    /* __*__ */ KC_0,
    /* __*_* */ KC_NO,
    /* __**_ */ KC_NLCK, // N
    /* __*** */ KC_8,
    /* _*___ */ KC_NO,
    /* _*__* */ KC_NO,
    /* _*_*_ */ KC_NO,
    /* _*_** */ KC_NO,
    /* _**__ */ KC_NO,
    /* _**_* */ KC_NO,
    /* _***_ */ KC_NO,
    /* _**** */ KC_9,
    /* *____ */ KC_1,
    /* *___* */ KC_NO,
    /* *__*_ */ KC_NO,
    /* *__** */ KC_NO,
    /* *_*__ */ KC_NO,
    /* *_*_* */ KC_NO,
    /* *_**_ */ KC_NO,
    /* *_*** */ KC_NO,
    /* **___ */ KC_2,
    /* **__* */ KC_NO,
    /* **_*_ */ KC_NO,
    /* **_** */ KC_NO,
    /* ***__ */ KC_3,
    /* ***_* */ KC_NO,
    /* ****_ */ KC_4,
    /* ***** */ KC_5
};

uint16_t function_table[] = {
    /* _____ */ KC_ENT,
    /* ____* */ KC_NO, // U, H
    /* ___*_ */ KC_LSFT, // S, K
    /* ___** */ KC_LGUI, // G, J
    /* __*__ */ KC_LCTL, // O, C
    /* __*_* */ KC_NO, // Q, Z
    /* __**_ */ KC_NLCK, // N, Y
    /* __*** */ KC_BSPC, // B, X
    /* _*___ */ KC_ESC, // E, I
    /* _*__* */ KC_LANG1, // V, L
    /* _*_*_ */ KC_TAB, // T, R
    /* _*_** */ KC_NO, // W
    /* _**__ */ KC_LALT, // A, D
    /* _**_* */ KC_NO,
    /* _***_ */ KC_NO, // F
    /* _**** */ KC_PSCR, // M, P
};

uint8_t current_chord = 0;
bool number_mode = false;
bool lang1 = false;
bool skip_mod_clear = false;

void execute_chord (void) {
    uint16_t code;

    if (current_chord & (1 << MW_FUNCTION)) {
        code = function_table[current_chord & ~(1 << MW_FUNCTION)];
    } else if (number_mode) {
        code = number_table[current_chord];
    } else {
        code = default_table[current_chord];
    }

    switch (code) {
      case KC_LSFT:
        register_mods(MOD_LSFT);
        skip_mod_clear = true;
        break;
      case KC_LGUI:
        register_mods(MOD_LGUI);
        skip_mod_clear = true;
        break;
      case KC_LCTL:
        register_mods(MOD_LCTL);
        skip_mod_clear = true;
        break;
      case KC_NLCK:
        number_mode = !number_mode;
        break;
      case KC_LANG1:
        tap_code(lang1 ? KC_LANG2 : KC_LANG1);
        lang1 = !lang1;
        break;
      case KC_LALT:
        register_mods(MOD_LALT);
        skip_mod_clear = true;
        break;
      default:
        tap_code(code);
        break;
    }
}

bool executed = false;

bool process_microwriter (enum finger_index index, keyrecord_t *record) {
    if (record->event.pressed) {
        current_chord |= 1 << index;
        executed = false;
        skip_mod_clear = false;
    } else {
        if (!executed) execute_chord();
        executed = true;
        current_chord &= ~(1 << index);
        if (!current_chord && !skip_mod_clear) unregister_mods(~0);
    }
    return false;
}
