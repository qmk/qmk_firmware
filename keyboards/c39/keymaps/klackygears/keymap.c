#include QMK_KEYBOARD_H

#include "klackygears.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
// #define _QWERTY 0
// #define _FN1 1

// Defines for task manager and such
#define CALTDEL LCTL(LALT(KC_DEL))
#define TSKMGR LCTL(LSFT(KC_ESC))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


[_MACBASE] = LAYOUT_wrapper( \
    _______________DVORAK_L1___________________, KC_____,             KC_____,           KC_____,   _______________DVORAK_R1___________________,
    _______________DVORAK_L2___________________, MO(_FUNC),           MO(_MDIA),         KC_TAB,         _______________DVORAK_R2___________________,
    _______________MACDVK_L3___________________, MT(MOD_LSFT,KC_SPC), LT(_MNMB,KC_BSPC), LT(_SYMB,KC_ENT), _______________MACDVK_R3___________________
),


[_WINBASE] = LAYOUT_wrapper( \
    _______________DVORAK_L1___________________, KC_____,  KC_____, KC_____, _______________DVORAK_R1___________________,
    _______________DVORAK_L2___________________, MO(_FUNC),           MO(_MDIA),         KC_TAB, _______________DVORAK_R2___________________,
    _______________WINDVK_L3___________________, MT(MOD_LSFT,KC_SPC), LT(_MNMB,KC_BSPC), LT(_SYMB,KC_ENT), _______________WINDVK_R3___________________
),


[_QWERTY] = LAYOUT_wrapper( \
    _________________QWERTY_L1_________________, KC_____,  KC_____, KC_____, _________________QWERTY_R1_________________,
    _________________QWERTY_L2_________________, MO(_FUNC),           MO(_MDIA),         KC_TAB, _________________QWERTY_R2_________________,
    _________________QWERTY_L3_________________, MT(MOD_LSFT,KC_SPC), LT(_MNMB,KC_BSPC), LT(_SYMB,KC_ENT), _________________QWERTY_R3_________________
),


[_SYMB] = LAYOUT_wrapper( \
    _________________PUNC_L1_ALT_______________, KC_____, KC_____, KC_____, _________________PUNC_R1___________________,
    _________________PUNC_L3___________________, KC_____, KC_____, KC_____, _________________PUNC_R2___________________,
    _________________PUNC_L3_ALT_______________, KC_____, KC_____, KC_____, _________________PUNC_R3___________________
),


[_FUNC] = LAYOUT_wrapper( \
    _____________FUNC_L1_______________________, KC_____, KC_____, KC_____, CALTDEL, _____________FUNC_1_______________,
    KC_____, KC_____, KC_____, KC_____, KC_____, KC_____, KC_____, KC_____, TSKMGR,  _____________FUNC_2_______________,
    _____________FUNC_L3_______________________, KC_____, KC_____, KC_____, KC_____, _____________FUNC_3_______________
),


[_MNMB] = LAYOUT_wrapper( \
    _________________MACNAV_L1_________________, KC_____, KC_____, KC_____, _________________NUMB_R1___________________,
    _________________MACNAV_L2_________________, KC_____, KC_____, KC_____, _________________NUMB_R2___________________,
    _________________MACNAV_L3_________________, KC_____, KC_____, KC_____, _________________NUMB_R3_MAC_______________
),


[_NUMB] = LAYOUT_wrapper( \
    _________________WINNAV_L1_________________, KC_____, KC_____, KC_____, _________________NUMB_R1___________________,
    _________________WINNAV_L2_________________, KC_____, KC_____, KC_____, _________________NUMB_R2___________________,
    _________________WINNAV_L3_________________, KC_____, KC_____, KC_____, _________________NUMB_R3_WIN_______________
),


[_MDIA] =  LAYOUT_wrapper( \
    _________________LYOUT_____________________, KC_____, KC_____, KC_____, _________________KC_BLANK__________________,
    KC_____, ________MAC_MISSION_CTRL__________, KC_____, KC_____, KC_____, _________________KC_BLANK__________________,
    _________________KC_BLANK__________________, KC_____, KC_____, KC_____, _________________MEDIA_____________________
),

};
