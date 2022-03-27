#include QMK_KEYBOARD_H

// easy layout wrappers
#define LAYOUT_wrapper(...)                 LAYOUT(__VA_ARGS__)
#define LAYOUT_5x6_wrapper(...)             LAYOUT_5x6(__VA_ARGS__)






// ---------------------- Keymaps section ----------------------

#define KC_MLSF OSM(MOD_LSFT)
#define KC_MRSF OSM(MOD_RSFT)

#define OS_LGUI OSM(MOD_LGUI)
#define OS_RGUI OSM(MOD_RGUI)
#define OS_LSFT OSM(MOD_LSFT)
#define OS_RSFT OSM(MOD_RSFT)
#define OS_LCTL OSM(MOD_LCTL)
#define OS_RCTL OSM(MOD_RCTL)
#define OS_LALT OSM(MOD_LALT)
#define OS_RALT OSM(MOD_RALT)
#define OS_MEH  OSM(MOD_MEH)
#define OS_HYPR OSM(MOD_HYPR)
#define MOUSE_L LSFT(KC_WH_D)
#define MOUSE_R LSFT(KC_WH_U)
#define OSX_LOCK LCTL(LGUI(KC_Q))


// Left-hand home row mods
#define GUI_A LGUI_T(KC_A)
#define ALT_S LALT_T(KC_S)
#define CTL_D LCTL_T(KC_D)
#define SFT_F LSFT_T(KC_F)

// Right-hand home row mods
#define SFT_J RSFT_T(KC_J)
#define CTL_K RCTL_T(KC_K)
#define ALT_L LALT_T(KC_L)
#define GUI_SCLN RGUI_T(KC_SCLN)



// layout parts for easy reuse between keyboard keymaps
// ,-----+-----+-----+-----+-----,   ,-----+-----+-----+-----+-----,
// |  1  |  2  |  3  |  4  |  5  |   |  6  |  7  |  8  |  9  |  0  |
// ,-----+-----+-----+-----+-----,   ,-----+-----+-----+-----+-----,
#define ________________NUMBERS_L__________________  KC_1, KC_2, KC_3, KC_4, KC_5
#define ________________NUMBERS_R__________________  KC_6, KC_7, KC_8, KC_9, KC_0

// ,-----+-----+-----+-----+-----,   ,-----+-----+-----+-----+-----,
// | F1  | F2  | F3  | F4  | F5  |   | F6  | F7  | F8  | F9  | F10 |
// ,-----+-----+-----+-----+-----,   ,-----+-----+-----+-----+-----,
#define ______________________F_L__________________  KC_F1, KC_F2, KC_F3, KC_F4, KC_F5
#define ______________________F_R__________________  KC_F6, KC_F7, KC_F8, KC_F9, KC_F10

// ,-----+-----+-----+-----+-----,   ,-----+-----+-----+-----+-----,
// |  Q  |  W  |  E  |  R  |  T  |   |  Y  |  U  |  I  |  O  |  P  |
// ,-----+-----+-----x-----x-----,   ,-----x-----x-----+-----+-----,
// |  A  |  S  |  D  |  F  |  G  |   |  H  |  J  |  K  |  L  |  ;  |
// ,-----+-----+-----x-----x-----,   ,-----x-----x-----+-----+-----,
// |  Z  |  X  |  C  |  V  |  B  |   |  N  |  M  |  ,  |  .  |  /  |
// ,-----+-----+-----+-----+-----,   ,-----+-----+-----+-----+-----,
#define _________________QWERTY_L1_________________  KC_Q   , KC_W   , KC_E   , KC_R   , KC_T
#define _________________QWERTY_L2_________________  KC_A   , KC_S   , KC_D   , KC_F   , KC_G
#define _________________QWERTY_L3_________________  KC_Z   , KC_X   , KC_C   , KC_V   , KC_B

#define _________________QWERTY_R1_________________  KC_Y   , KC_U   , KC_I   , KC_O   , KC_P
#define _________________QWERTY_R2_________________  KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN
#define _________________QWERTY_R3_________________  KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH

#define _____________MOD_QWERTY_L2_________________  GUI_A, ALT_S, CTL_D, SFT_F, KC_G
#define _____________MOD_QWERTY_R2_________________  KC_H, SFT_J, CTL_K, ALT_L, GUI_SCLN

// ,-----+-----+-----+-----+-----,   ,-----+-----+-----+-----+-----,
// |  !  |  @  |  {  |  }  |  _  |   |  \  |  7  |  8  |  9  |     |
// ,-----+-----+-----x-----x-----,   ,-----x-----x-----+-----+-----,
// |  #  |  $  |  (  |  )  |  -  |   |  =  |  4  |  5  |  6  |  |  |
// ,-----+-----+-----x-----x-----,   ,-----x-----x-----+-----+-----,
// |  %  |  ^  |  [  |  ]  |  +  |   |  *  |  1  |  2  |  3  |  /  |
// ,-----+-----+-----+-----+-----,   ,-----+-----+-----+-----+-----,
#define _________________SYMBOL_L1_________________  KC_EXLM, KC_AT  , KC_LCBR, KC_RCBR, KC_UNDS
#define _________________SYMBOL_L2_________________  KC_HASH, KC_DLR , KC_LPRN, KC_RPRN, KC_MINS
#define _________________SYMBOL_L3_________________  KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_PLUS

#define _________________SYMBOL_R1_________________  KC_BSLS, KC_P7, KC_P8 , KC_P9, KC_PAST
#define _________________SYMBOL_R2_________________  KC_EQL , KC_P4, KC_P5, KC_P6, KC_PPLS
#define _________________SYMBOL_R3_________________  KC_ASTR, KC_P1, KC_P2, KC_P3, KC_PMNS

enum layers {
  BASE, // default layer
  WIN, // Switch keys that are needed in windows
  SYMB, // symbols
  MDIA // media keys
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [BASE] = LAYOUT_5x6_wrapper(
     KC_EQL , ________________NUMBERS_L__________________,                         ________________NUMBERS_R__________________, KC_MINS,
     KC_ESC , _________________QWERTY_L1_________________,                         _________________QWERTY_R1_________________, KC_BSLS,
     KC_F1  , _____________MOD_QWERTY_L2_________________,                         _____________MOD_QWERTY_R2_________________, KC_QUOT,
     OS_LSFT, _________________QWERTY_L3_________________,                         _________________QWERTY_R3_________________, OS_RSFT,
                      KC_LEFT,KC_RGHT,                                                       KC_UP, KC_DOWN,
                                     KC_BSPC, KC_SPC,                         KC_TAB, KC_ENT,
                                     KC_LGUI, MO(SYMB),                       MO(SYMB), TT(MDIA),
                                     KC_DEL, KC_GRV,                          TT(WIN), KC_LALT
  ),
  [WIN] = LAYOUT_5x6_wrapper(

     _______, _______, _______, _______, _______, _______,                        _______, _______, _______, _______, _______, _______,
     _______, _______, _______, _______, _______, _______,                        _______, _______, _______, _______, _______, _______,
     _______, _________________QWERTY_L2_________________,                        _______, _______, _______, _______, _______, _______,
     _______, _______, _______, _______, _______, _______,                        _______, _______, _______, _______, _______, _______,
                                             _______, _______,            _______, _______,
                                             _______, _______,            _______, _______,
                                             KC_LCTL, _______,            _______, _______,
                                             _______, _______,            _______, _______
  ),

  [SYMB] = LAYOUT_5x6_wrapper(
       KC_F12 , ______________________F_L__________________,                      ______________________F_R__________________, KC_F11,
       _______, _________________SYMBOL_L1_________________,                      _________________SYMBOL_R1_________________, KC_NLCK,
       _______, _________________SYMBOL_L2_________________,                      _________________SYMBOL_R2_________________, _______,
       _______, _________________SYMBOL_L3_________________,                      _________________SYMBOL_R3_________________, _______,
                                               _______, _______,            KC_P0 , KC_PDOT,
                                               _______, _______,            _______, _______,
                                               RESET  , _______,            _______, _______,
                                               RGB_TOG, _______,            _______, _______
  ),
  [MDIA] = LAYOUT_5x6_wrapper(

     RGB_MOD, RGB_HUI, _______, _______, _______, _______,                        _______, _______, _______, _______, _______, _______,
     	RGB_M_SN, RGB_HUD, _______, KC_MS_U, _______, KC_WH_U,                        _______, _______, KC_WH_U, _______, _______, _______,
     RGB_VAI, RGB_SAI, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D,                        _______, MOUSE_L, KC_WH_D, MOUSE_R, _______, _______,
     RGB_VAD, RGB_SAD, _______, _______, _______, _______,                        _______, _______, _______, _______, _______, _______,
                                             _______, _______,            _______, _______,
                                             KC_BTN1, KC_BTN2,            _______, _______,
                                             KC_BTN3, KC_BTN4,            _______, _______,
                                             KC_BTN5, _______,            _______, _______

   ),
};
