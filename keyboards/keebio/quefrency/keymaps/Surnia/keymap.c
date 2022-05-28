#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

enum {
  _BASE,
  _NUM,
  _ANCIL,
  FIND,
  SHCAPS,
  QWERTY = SAFE_RANGE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) { //macro areas. names defined in enum, function defined here. 
        switch (keycode) {
                case FIND:
                        if (record->event.pressed){
                                SEND_STRING(SS_LCTL("f")); //SS = press and hold, then send respective string inside
                        }
                break;
        }
        return true;
};

//tap dance!
qk_tap_dance_action_t tap_dance_actions[] = {
        [SHCAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* _BASE layer 0, Standard full layout. 
*,----------------------------------------------------------     ------------------------------------------------------.
 *| MS3 | ESC |  |  `  |  1  |  2  |  3  |  4  |  5  |  6  |     |  7  |  8  |  9  |  0  |  -  |  =  |BkSp | Del | Hme |
 *|------------  -------------------------------------------     ------------------------------------------------------|
 *| F1  | F2  |  | Tab    |  Q  |  W  |  E  |  R  |  T  |     |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |   \    |PgUp |
 *|------------  ----------------------------------------     ---------------------------------------------------------|
 *| F3  | F4  |  | LCtrl   |  A  |  S  |  D  |  F  |  G  |     |  H  |  J  |  K  |  L  |  ;  |  '  |    Enter    |PgDn |
 *|------------  -----------------------------------------     --------------------------------------------------------|
 *| F5  | F6  |  | ShCaps      |  Z  |  X  |  C  |  V  |  B  |     |  N  |  M  |  ,  |  .  |  /  | Rshift  | Up  | End |
 *|------------  ---------------------------------------------     ----------------------------------------------------|
 *| F7  | F8  |  | Caps |  GUI  |  Alt  |   Space    | MO(1) |     |   Space(2)    | Alt |TT(1)|RCtrl| <-  | Dn  |  -> |
 *`------------  ---------------------------------------------     ----------------------------------------------------.
 */

  [_BASE] = LAYOUT_65_with_macro(
    KC_BTN3, KC_ESC,  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,  KC_DEL, KC_HOME, \
    KC_F1,   KC_F2,   KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,  KC_PGUP, \
    KC_F3,   KC_F4,   KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  KC_PGDN, \
    KC_F5,   KC_F6,   SHCAPS,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_END, \
    KC_F7,   KC_F8,  KC_CAPS, KC_LGUI, KC_LALT, KC_SPC,   MO(1),                    KC_SPC,  KC_SPC,  KC_RALT, TT(1),   KC_RCTL, KC_LEFT, KC_DOWN,  KC_RGHT
  ),
  
/* _NUM Layer 1, Standard full layout. 
*,----------------------------------------------------------     ------------------------------------------------------.
 *|RGBTG|RGB+ |  |RSat+|RSat-|     |     |     |     |TG(2)|     |  7  |  8  |  9  |  /  |     |     | TNS | TNS | TNS |
 *|------------  -------------------------------------------     ------------------------------------------------------|
 *| F9  | F10 |  | Tab    |MWhL|MsUp |MWhR |MWhU |  T  |     |  Y  |  4  |  5  |  6  |  *  |Copy |Paste|  Calc   | TNS |
 *|------------  ----------------------------------------     ---------------------------------------------------------|
 *| F11 | F12 |  |   MS2   |MsLf |MsDn |MsRt |MWhD |  G  |     |FIND |  1  |  2  |  3  |  +  |  '  |    Enter    | TNS |
 *|------------  -----------------------------------------     --------------------------------------------------------|
 *|RHue+|RBri+|  | Shift       |MsAc0|MsAc1|MsAc2|  V  |  B  |     | TAB |  0  |     |  .  |  -  | Rshift  | Up  | TNS |
 *|------------  ---------------------------------------------     ----------------------------------------------------|
 *|Rhue-|RBri-|  | Caps |  MS3  |  Alt  |    MS1     | MO(1) |     |   Space(2)    | Alt |TT(1)|RCtrl| <-  | Dn  |  -> |
 *`------------  ---------------------------------------------     ----------------------------------------------------.
 */
  [_NUM] = LAYOUT_65_with_macro(
    RGB_TOG, RGB_MOD, RGB_SAI, RGB_SAD, _______, _______, _______, TG(2),       _______, KC_P7,   KC_P8,   KC_P9,   KC_PSLS, _______, KC_PSCR, KC_BSPC, KC_DEL,  KC_HOME, \
    KC_F9,   KC_F10,  _______, KC_WH_L, KC_MS_U, KC_WH_R, KC_WH_U, _______,     _______, KC_P4,   KC_P5,   KC_P6,   KC_PAST, C(KC_C), C(KC_V), KC_CALC, KC_PGUP, \
    KC_F11,  KC_F12,  KC_BTN2, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, _______,     FIND,    KC_P1,   KC_P2,   KC_P3,   KC_PPLS, _______, _______, KC_PGDN, \
    RGB_HUI, RGB_VAI, _______, KC_ACL0, KC_ACL1, KC_ACL2, _______, _______,     KC_TAB, KC_P0,   KC_NO,   KC_PDOT, KC_PMNS, KC_RSFT, KC_UP,   KC_END, \
    RGB_HUD, RGB_VAD, _______, KC_BTN3, _______, KC_BTN1, KC_TRNS,                   _______, _______, KC_RALT, KC_TRNS, KC_RCTL, KC_LEFT, KC_DOWN, KC_RIGHT
  ), 

/* _ANCIL Layer 2, Standard full layout. 
*,----------------------------------------------------------     ------------------------------------------------------.
 *|RGBTG|RGB+ |  |RSat+|RSat-|     |     |     |     |TG(2)|     |  7  |  8  |  9  |  /  |     |     | TNS | TNS | TNS |
 *|------------  -------------------------------------------     ------------------------------------------------------|
 *| F9  | F10 |  | Tab    |MWhL|MsUp |MWhR |MWhU |  T  |     |  Y  |  4  |  5  |  6  |  *  |Copy |Paste|   \    | TNS |
 *|------------  ----------------------------------------     ---------------------------------------------------------|
 *| F11 | F12 |  |   MS2   |MsLf |MsDn |MsRt |MWhD |  G  |     |FIND |  1  |  2  |  3  |  +  |  '  |    Enter    | TNS |
 *|------------  -----------------------------------------     --------------------------------------------------------|
 *|RHue+|RBri+|  | Shift       |MsAc0|MsAc1|MsAc2|  V  |  B  |     | TAB |  0  |     |  .  |  -  | Rshift  | Up  | TNS |
 *|------------  ---------------------------------------------     ----------------------------------------------------|
 *|Rhue-|RBri-|  | Caps |  MS3  |  Alt  |    MS1     | MO(1) |     |   Space(2)    | Alt |TT(1)|RCtrl| <-  | Dn  |  -> |
 *`------------  ---------------------------------------------     ----------------------------------------------------.
 */
  [_ANCIL] = LAYOUT_65_with_macro(
    RGB_TOG, RGB_MOD, RGB_RMOD, _______, _______, _______, _______, KC_TRNS,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,\
    RGB_SAI, RGB_SPI, _______,  _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______,\
    RGB_SAD, RGB_SPD, _______,  _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______, _______, \
    RGB_HUI, RGB_VAI, _______,  _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______, _______, \
    RGB_HUD, RGB_VAD, _______,  _______, _______, _______, KC_TRNS,              _______, _______, _______, KC_TRNS, _______, _______, _______, _______,
  ),
};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_WH_D);
        } else {
            tap_code(KC_WH_U);
        }
    }
/*    else if (index == 1) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }   */
}

/*
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { // First encoder
        switch(biton32(layer_state)){
            case _BASE:
              if (clockwise) {
                  tap_code(KC_WH_D);
              } else {
                  tap_code(KC_WH_U);
              }
            break;
            case _NUM:
                if (clockwise) {
                    tap_code16(KC_TAB);
                } else {
                    tap_code16(S(KC_TAB));
                }
            break;
        }
    } else if (index == 1) { // Second encoder
        if (clockwise) {
            tap_code(KC_DOWN);
        } else {
            tap_code(KC_UP);
        }
    }
    return true;
}
*/