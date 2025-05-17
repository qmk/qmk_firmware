#include QMK_KEYBOARD_H
//#include "autocorrect.h"
#include "autocorrect_data.h"

const uint16_t PROGMEM escape[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM tab[] = {KC_Z, KC_X, COMBO_END};
const uint16_t PROGMEM delete[] = {KC_Y, KC_SCLN, COMBO_END};
const uint16_t PROGMEM quote[] = {KC_DOT, KC_SLSH, COMBO_END};

combo_t key_combos[] = {
  COMBO(escape, KC_ESC),
  COMBO(tab, KC_TAB),
  COMBO(delete, KC_DEL),
  COMBO(quote, KC_QUOT),
};


bool process_record_user(uint16_t keycode, keyrecord_t *record)  {
  return process_autocorrect(keycode, record);
};



enum layers {
    _COLEMAK,
    _NUMSYM,
    _MSFN
    //_SET
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * COLEMAK-DH
 * ,----------------------------------.              ,----------------------------------.
 * |    Escape   |      |      |      |              |      |      |      |    Delete   |
 * |   Q  |   W  |   F  |   P  |   B  |              |   J  |   L  |   U  |   Y  |   ;  |
 * |------+------+------+------+------|              |------+------+------+------+------|
 * |      |      |      |      |      |              |      |      |      |      |      |
 * |Shft/A| Ctl/R| Alt/S| CMD/T|   G  |              |   M  | CMD/N| Alt/E| Ctl/I|Shft/O|
 * |------+------+------+------+------|              |------+------+------+------+------|
 * |      |      |      |      |      |              |      |      |      |    Quote    |
 * |   Z  |   X  |   C  |   D  |   V  |              |   K  |   H  |   ,  |   .  |   /  |
 * `------+------+------+------+------+--------------+------+------+------+------+------'
 *                      | Fn/Ms|  SPC | BSPC |  ENT  | LSFT |NumSym|
 *                      `------------------------------------------'
 */

[_COLEMAK] = LAYOUT(
  KC_Q,   KC_W,    KC_F,    KC_P,    KC_B,                     KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN,
  SFT_T(KC_A), CTL_T(KC_R), ALT_T(KC_S), GUI_T(KC_T), KC_G,                     KC_M, GUI_T(KC_N), ALT_T(KC_E), CTL_T(KC_I), SFT_T(KC_O),
  KC_Z,   KC_X,    KC_C,    KC_D,    KC_V,                     KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH,
                            TG(_MSFN), KC_SPC, KC_BSPC, KC_ENT,  OSM(MOD_LSFT),  MO(_NUMSYM)
),
/*
 * NUMBERS & SYMBOLS
 * ,----------------------------------.              ,----------------------------------.
 * |   1  |   2  |   3  |   4  |   5  |              |   6  |   7  |   8  |   9  |   0  |
 * |------+------+------+------+------|              |------+------+------+------+------|
 * |   !  |   @  |   #  |   $  |   %  |              |   ^  |   &  |   *  |   (  |   )  |
 * |------+------+------+------+------|              |------+------+------+------+------|
 * |      |      |   `  |   ~  |   _  |              |   -  |   +  |   =  |   [  |   ]  |
 * `------+------+------+------+------+--------------+------+------+------+------+------'
 *                      | TRNS | TRNS | TRNS | TRNS  | TRNS | TRNS |
 *                      `------------------------------------------'
 */

 [_NUMSYM] = LAYOUT(
  KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
  KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC,                 KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN,  KC_RPRN,
  KC_NO, KC_NO, KC_GRV, KC_TILD, KC_UNDS,                  KC_MINS, KC_PLUS,  KC_EQL, KC_LBRC,  KC_RBRC,
                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS
),
/*
 * MOUSE & FUNCTION
 * ,----------------------------------.              ,----------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |      |              | MSWUP|      | MSUP |      |AutoCr|
 * |------+------+------+------+------|              |------+------+------+------+------|
 * |  F5  |  F6  |  F7  |  F8  |      |              |MSWDWN| MSLF | MSDW | MSRT |      |
 * |------+------+------+------+------|              |------+------+------+------+------|
 * |  F9  |  F10 |  F11 |  F12 |      |              |  UP  |  DWN |  LFT |  RT  |      |
 * `------+------+------+------+------+--------------+------+------+------+------+------'
 *                      |      | LCLK | RCLK |       |      |      |
 *                      `------------------------------------------'
 */

 [_MSFN] = LAYOUT(
  KC_F1,  KC_F2,   KC_F3,   KC_F4,   KC_NO,                    MS_WHLU, KC_NO,    MS_UP,   KC_NO,   AC_TOGG,
  KC_F5,  KC_F6,   KC_F7,   KC_F8,   KC_NO,                    MS_WHLD, MS_LEFT,  MS_DOWN, MS_RGHT,   KC_NO,
  KC_F9,  KC_F10,  KC_F11,  KC_F12,  KC_NO,                    KC_UP, KC_DOWN,  KC_LEFT, KC_RGHT,   KC_NO,
                            KC_TRNS, MS_BTN1, MS_BTN2, KC_NO,  KC_NO,   KC_NO
),

};


