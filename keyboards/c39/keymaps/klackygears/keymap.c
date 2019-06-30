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

enum unicode_names {
  BANG,
  IRONY,
  SNEK,
  SHRG,
  FCPLM,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


[_MACBASE] = LAYOUT_wrapper( \
    TD(TD_CAPESC), _______________DVORAK_L1___________________, MO(_MDIA),           _______________DVORAK_R1___________________, KC_BSPC,
    TD(TD_ENTAB),  _______________DVORAK_L2___________________, MO(_FUNC),           _______________DVORAK_R2___________________, LT(_MEME,KC_ENT),
    KC_LSHIFT,     __________c39__MACDVK_L3___________________, MT(MOD_LSFT,KC_SPC), __________c39__MACDVK_R3___________________, KC_RSHIFT
),


[_WINBASE] = LAYOUT_wrapper( \
    TD(TD_CAPESC), _______________DVORAK_L1___________________, MO(_MEME),           _______________DVORAK_R1___________________, KC_BSPC,
    TD(TD_ENTAB),  _______________DVORAK_L2___________________, MO(_NUMB),           _______________DVORAK_R2___________________, KC_ENT,
    KC_LSHIFT,     __________c39__WINDVK_L3___________________, MT(MOD_LSFT,KC_SPC), __________c39__WINDVK_R3___________________, KC_RSHIFT
),


[_QWERTY] = LAYOUT_wrapper( \
    KC_____,   _________________QWERTY_L1_________________, TO(_MACBASE), _________________QWERTY_R1_________________, KC_____,
    KC_____,   _________________QWERTY_L2_________________, KC_____,      _________________QWERTY_R2_________________, KC_____,
    KC_LSHIFT, _________________QWERTY_L3_________________, KC_____,      _________________QWERTY_R3_________________, KC_RSHIFT
),


[_SYMB] = LAYOUT_wrapper( \
    KC_____, _________________PUNC_L1_ALT_______________, KC_____, _________________PUNC_R1___________________, KC_____,
    KC_____, _________________PUNC_L3___________________, KC_____, _________________PUNC_R2___________________, KC_____,
    KC_____, _________________PUNC_L3_ALT_______________, KC_____, _________________PUNC_R3___________________, KC_____
),


[_FUNC] = LAYOUT_wrapper( \
    MAKEKF,  _____________FUNC_L1_______________________, KC_____, CALTDEL, _____________FUNC_1_______________, KC_____,
    KC_____, ________MAC_MISSION_CTRL__________, KC_____, KC_____, TSKMGR,  _____________FUNC_2_______________, KC_____,
    KC_____, _____________FUNC_L3_______________________, KC_____, KC_____, _____________FUNC_3_______________, KC_____
),


[_MNMB] = LAYOUT_wrapper( \
    KC_____, _________________MACNAV_L1_________________, KC_____, _________________NUMB_R1___________________, KC_DEL,
    KC_____, _________________MACNAV_L2_________________, KC_____, _________________NUMB_R2___________________, KC_____,
    KC_____, _________________MACNAV_L3_________________, KC_____, _________________NUMB_R3_MAC_______________, KC_____
),


[_NUMB] = LAYOUT_wrapper( \
    KC_____, _________________WINNAV_L1_________________, KC_____, _________________NUMB_R1___________________, KC_____,
    KC_____, _________________WINNAV_L2_________________, KC_____, _________________NUMB_R2___________________, KC_____,
    KC_____, _________________WINNAV_L3_________________, KC_____, _________________NUMB_R3_WIN_______________, KC_____
),


[_MDIA] =  LAYOUT_wrapper( \
    KC_____, _________________LYOUT_____________________, KC_____, _________________RGB_1_____________________, KC_____,
    KC_____, KC_____, ________MAC_MISSION_CTRL__________, KC_____, _________________RGB_2_____________________, KC_____,
    KC_____, _________________KC_BLANK__________________, KC_____, _________________MEDIA_____________________, KC_____
),

[_MEME] =  LAYOUT_wrapper( \
    KC_____, KC_____, KC_____, X(SNEK), X(SHRG), X(FCPLM), KC_____, _________________KC_BLANK__________________, KC_____,
    KC_____, _________________KC_BLANK__________________,  KC_____, _________________KC_BLANK__________________, KC_____,
    KC_____, _________________KC_BLANK__________________,  KC_____, _________________KC_BLANK__________________, KC_____
),

};


const uint32_t PROGMEM unicode_map[] = {
  [BANG]  = 0x203D,  // ‽
  [IRONY] = 0x2E2E,  // ⸮
  [SNEK]  = 0x1F40D, // 🐍
  [SHRG]  = 0x0001F937,
  [FCPLM] = 0xD83E,
};


void matrix_scan_user(void) {


    switch(biton32(layer_state)) {
      case _MNMB:
        rgblight_setrgb_at(0, 0, 255, 8);
      break;
      case _FUNC:
        rgblight_setrgb_at(255, 0, 0, 9);
      break;
      case _SYMB:
        rgblight_setrgb_at(200, 55, 100, 7);
      break;
      case _MDIA:
        rgblight_setrgb_at(255, 255, 255, 6);
      break;
    //   default: //  for any other layers, or the default layer
    //     rgblight_step();
    //     break;
    }

};
