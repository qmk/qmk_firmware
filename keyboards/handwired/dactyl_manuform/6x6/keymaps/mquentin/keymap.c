#include QMK_KEYBOARD_H
#include "keymap_french.h"

#define BASE 0
#define MOUSE 1
#define RESET_ACCESS 11
#define RST_LR 12

#define ESC_RSTA LT(RESET_ACCESS, KC_ESC)
#define TG_MOUSE TG(MOUSE)

#define RESET__ QK_BOOT

// empty layer
// [RESET]=LAYOUT_6x6(
//   _______, _______,   _______, _______, _______, _______,                _______, _______, _______, _______, _______, _______,
//   _______, _______,   _______, _______, _______, _______,                _______, _______, _______, _______, _______, _______,
//   _______, _______,   _______, _______, _______, _______,                _______, _______, _______, _______, _______, _______,
//   _______, _______,   _______, _______, _______, _______,                _______, _______, _______, _______, _______, _______,
//   _______, _______,   _______, _______, _______, _______,                _______, _______, _______, _______, _______, _______,
//                      _______, _______,                                          _______, _______,
//                                 _______, _______,             _______, _______,
//                                   _______, _______,        _______, _______,
//                                   _______, _______,        _______, _______
// ),


// All infos with Images: https://github.com/mquentin/qmk_firmware/blob/master/keyboards/handwired/dactyl_manuform/6x6/keymaps/mquentin/readme.md
// To compile: qmk compile -kb handwired/dactyl_manuform/6x6 -km mquentin
// To flash: qmk flash -kb handwired/dactyl_manuform/6x6 -km mquentin
// to reset: press and hold ESC_RSTA then KC_ENTER THEN KC_LGUI

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE]=LAYOUT_6x6(
    ESC_RSTA,    KC_F1,   KC_F2,    KC_F3,    KC_F4,    KC_F5,              KC_F6,  KC_F7,  KC_F8,    KC_F9,   KC_F10,  FR_EQL,
    FR_SUP2,     FR_AMPR, FR_EACU,  FR_DQUO,  FR_QUOT,  FR_LPRN,            FR_MINS,FR_EGRV,FR_UNDS,  FR_CCED, FR_AGRV, FR_RPRN,
    KC_CAPS_LOCK, FR_A,    FR_Z,     FR_E,     FR_R,     FR_T,               FR_Y,   FR_U,   FR_I,     FR_O,    FR_P,    FR_CIRC,
    KC_F12,      FR_Q,    FR_S,     FR_D,     FR_F,     FR_G,               FR_H,   FR_J,   FR_K,     FR_L,    FR_M,    FR_UGRV,
    KC_F11,      FR_W,    FR_X,     FR_C,     FR_V,     FR_B,               FR_N,   FR_COMM,FR_SCLN,  FR_COLN, FR_DLR,  FR_ASTR,
                            FR_LABK,  KC_TAB,                                               KC_RALT,    FR_EXLM,
                                                KC_SPACE,  KC_LGUI,         KC_BSPC,  KC_ENTER,
                                                  KC_LCTL, KC_LSFT,         KC_UP,    KC_RIGHT,
                                                  KC_LALT,  TG_MOUSE,    KC_LEFT, KC_DOWN
  ),
  // Right-hand mouse layer. Tap the left-thumb * key (TG_MOUSE = TG(MOUSE))
  // to toggle it on/off -- no holding needed while you mouse.
  //   Movement is available in two places:
  //     - home row (inverted-T under the letters): I = up, J = left, K = down, L = right
  //     - right-thumb arrow keys (mirror base KC_UP/KC_RIGHT/KC_LEFT/KC_DOWN)
  //   Wheel: U/O = up/down, ,/: = left/right.
  //   Right thumb (BSPC/ENTER/RAlt) = left/right/middle click.
  //   Left home row S/D/F = hold for fast/medium/slow cursor speed (MS_ACL2/1/0).
  [MOUSE]=LAYOUT_6x6(
    _______, _______, _______, _______, _______, _______,         _______, _______, _______,  _______,  _______, _______,
    _______, _______, _______, _______, _______, _______,         _______, _______, _______,  _______,  _______, _______,
    _______, _______, _______, _______, _______, _______,         _______, MS_WHLU, MS_UP,    MS_WHLD,  _______, _______,
    _______, _______, MS_ACL2, MS_ACL1, MS_ACL0, _______,         _______, MS_LEFT, MS_DOWN,  MS_RGHT,  _______, _______,
    _______, _______, _______, _______, _______, _______,         _______, MS_WHLL, _______,  MS_WHLR,  _______, _______,
                      _______, _______,                                             MS_BTN3, _______,
                                  _______, _______,             MS_BTN1, MS_BTN2,
                                    _______, _______,        MS_UP,   MS_RGHT,
                                    _______, _______,        MS_LEFT, MS_DOWN
  ),
  [RESET_ACCESS]=LAYOUT_6x6(
    _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______,
                      _______, _______,                                             _______, _______,
                                  _______, _______,             _______, _______,
                                    _______, _______,        _______, _______,
                                    _______, MO(RST_LR),      _______, _______
  ),
  [RST_LR]=LAYOUT_6x6(
    _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______,
                      _______, _______,                                             _______, _______,
                                  _______, RESET__,                     _______, _______,
                                        _______, _______,         _______, _______,
                                        _______, _______,         _______, _______
  ),

};
