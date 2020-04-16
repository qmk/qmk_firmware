#include QMK_KEYBOARD_H
#include "klackygears.h"

extern keymap_config_t keymap_config;


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_WINBASE] = LAYOUT_wrapper( \
             _______________DVORAK_L1___________________, KC_ESC,       KC_GAMER, _______________DVORAK_R1___________________, \
    RGB_TOG, _______________DVORAK_L2___________________, KC_____,      KC_____, _______________DVORAK_R2___________________, RGB_TOG, \
    RGB_MOD, _______________WINDVK_L3___________________, KC_____,      KC_____, _______________WINDVK_R3___________________, RGB_MOD, \
             KC_____, KC_____,          __________________WIN_THUMB_CLUSTER_V2______________     ,          KC_____, KC_____, \
                                        KC_NO,   KC_NO,   KC_NO,        KC_NO,   KC_NO,   KC_NO \
  ),

  [_MACBASE] = LAYOUT_wrapper( \
             _______________DVORAK_L1___________________, KC_ESC,       KC_____, _______________DVORAK_R1___________________, \
    RGB_TOG, _______________DVORAK_L2___________________, KC_____,      KC_____, _______________DVORAK_R2___________________, RGB_TOG, \
    RGB_MOD, _______________MACDVK_L3___________________, KC_____,      KC_____, _______________MACDVK_R3___________________, RGB_MOD, \
             KC_____, KC_____,            __________________MAC_THUMB_CLUSTER_V2______________    ,         KC_____, KC_____, \
                                        KC_NO,   KC_NO,   KC_NO,        KC_NO,   KC_NO,   KC_NO   \
  ),


  [_QWERTY] = LAYOUT_wrapper( \
             _________________QWERTY_L1_________________, KC_ESC,       KC_____, _________________QWERTY_R1_________________, \
    KC_CAPS, _________________QWERTY_L2_________________, KC_____,      KC_____, _________________QWERTY_R2_________________, KC_ENT, \
    KC_LSFT, _________________QWERTY_L3_________________, KC_____,      KC_____, _________________QWERTY_R3_________________, KC_RSFT, \
             KC_LCTL, KC_LALT,      KC_LGUI, MO(_MNMB), MO(_SYMB),      MO(_SYMB), MO(_MNMB), KC_RGUI,  MO(_MDIA), MO(_FUNC), \
                                         KC_LSFT, KC_SPC,  KC_SPC,      KC_SPC,  KC_SPC,  KC_RSFT \
  ),

  [_GAMER] = LAYOUT_wrapper( \
             KC_R,    KC_Q,    KC_W,    KC_E,    KC_1,      KC_ESC,        KC_WINBASE, _________________RGB_1_____________________, \
    RGB_TOG, KC_F,    KC_A,    KC_S,    KC_D,    KC_2, LSFT(KC_F2),        KC_____, _________________RGB_2_____________________, RGB_TOG, \
    RGB_MOD, KC_LSFT, KC_X,    KC_Z,    KC_C,    KC_3,        KC_M,        KC_____, _________________MEDIA_____________________, RGB_MOD, \
             KC_LCTL, KC_LALT,       MO(_GAMR1), KC_LSFT,   KC_SPC,        KC_____, KC_____, KC_____,           KC_____, KC_____, \
                                     KC_NO,      KC_LSFT,  KC_LSFT,        KC_____, KC_____, KC_____ \
  ),

  [_GAMR1] = LAYOUT_wrapper( \
             KC_____, KC_____, KC_____, KC_____, KC_____, KC_____,        KC_____, _________________RGB_1_____________________, \
    RGB_TOG, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,       KC_6,        KC_____, _________________RGB_2_____________________, RGB_TOG, \
    RGB_MOD, KC_____, KC_____, KC_____, KC_____, KC_____, KC_____,        KC_____, _________________MEDIA_____________________, RGB_MOD, \
             KC_____, KC_____,          KC_____, KC_____, KC_____,        KC_____, KC_____, KC_____,           KC_____, KC_____, \
                                        KC_____, KC_____, KC_____,        KC_____, KC_____, KC_____ \
  ),

  [_SYMB] = LAYOUT_wrapper( \
             _________________PUNC_L1_ALT_______________, KC_____,      KC_____, _________________PUNC_R1___________________, \
    KC_____, _________________PUNC_L3___________________, KC_____,      KC_____, _________________PUNC_R2___________________, KC_____, \
    RGB_MOD, _________________PUNC_L3_ALT_______________, KC_____,      KC_____, _________________PUNC_R3___________________, KC_____, \
             KC_____, KC_____,          KC_____, KC_____, KC_DEL,       KC_CAPS, KC_____, KC_____,          KC_____, KC_____, \
                                        KC_____, KC_____, KC_DEL,       KC_CAPS, KC_____, KC_____ \
  ),

  [_FUNC] = LAYOUT_wrapper( \
             _____________FUNC_L1_______________________,    KC_____,      KC_____, KC_____, _____________FUNC_1_______________,\
    KC_____, ________MAC_MISSION_CTRL__________, LGUI(KC_L), KC_____,      KC_____, KC_____, _____________FUNC_2_______________, KC_____, \
    RGB_MOD, _____________FUNC_L3_______________________,    KC_____,      KC_____, KC_____, _____________FUNC_3_______________, KC_____, \
             KC_____, KC_____,          KC_____, KC_____,    KC_____,      KC_CAPS, KC_____, KC_____,          KC_____, KC_____, \
                                        KC_____, KC_____,    KC_____,      KC_CAPS, KC_____, KC_____ \
  ),

  [_MNMB] = LAYOUT_wrapper( \
             _________________MACNAV_L1_________________, KC_____,      KC_____, _________________NUMB_R1___________________, \
    KC_____, _________________MACNAV_L2_________________, KC_____,      KC_____, _________________NUMB_R2___________________, KC_____, \
    RGB_MOD, _________________MACNAV_L3_________________, KC_____,      KC_____, _________________NUMB_R3_MAC_______________, KC_____, \
             KC_____, KC_____,          KC_____, KC_____, KC_____,      KC_____, RSFT_T(KC_ENT), KC_RSFT,   KC_____, KC_____, \
                                        KC_____, KC_____, KC_____,      KC_____, RSFT_T(KC_ENT), KC_RSFT \
  ),


  [_NUMB] = LAYOUT_wrapper( \
             _________________WINNAV_L1_________________, KC_____,      KC_____, _________________NUMB_R1___________________, \
    KC_____, _________________WINNAV_L2_________________, KC_____,      KC_____, _________________NUMB_R2___________________, KC_____, \
    RGB_MOD, _________________WINNAV_L3_________________, KC_____,      KC_____, _________________NUMB_R3_WIN_______________, KC_____, \
             KC_____, KC_____,          KC_____, KC_____, KC_____,      KC_____, RSFT_T(KC_ENT), KC_RSFT,   KC_____, KC_____, \
                                        KC_____, KC_____, KC_____,      KC_____, RSFT_T(KC_ENT), KC_RSFT \
  ),

   [_MDIA] = LAYOUT_wrapper( \
             _________________LYOUT_____________________, KC_____,      RGB_TOG, _________________RGB_1_____________________, \
    KC_____, _________________KC_BLANK__________________, KC_____,      KC_____, _________________RGB_2_____________________, KC_____, \
    RGB_MOD, _________________KC_BLANK__________________, KC_____,      KC_____, _________________MEDIA_____________________, KC_____, \
             KC_____, KC_____,          KC_____, KC_____, KC_____,      KC_____, KC_____, KC_____,          KC_____, KC_____, \
                                        KC_____, KC_____, KC_____,      KC_____, KC_____, KC_____ \
  )

  };
