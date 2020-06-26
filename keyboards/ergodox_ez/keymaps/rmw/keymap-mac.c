#include "rmw.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [QWERTY] = LAYOUT_ergodox(
    TD(FRBK2),      KC_1,           KC_2,       KC_3,        KC_4,          KC_5,    KC_F4, 
    KC_TAB,         KC_Q,           KC_W,       KC_E,        KC_R,          KC_T,    TO(EDIT), 
    OSL(EDIT),      KC_A,  LT(NUMPAD,KC_S),      KC_D,  LT(FSYM,KC_F),   KC_G, 
    LCTL(KC_LEFT),  KC_Z,           KC_X,       KC_C,        KC_V,    SFT_T(KC_B),   KC_TAB, 
    TD(CTLALL),     OSL(ADJUST),    TD(GUCTL),  TD(SGCA),  TD(AGC), 
                                                               OS_CMD,    OS_CTL   , 
                                                                          KC_ESCAPE, 
                                                   KC_BSPACE,  TD(SHENT), OSL(EDIT), 

        KC_F5,       KC_6,             KC_7,       KC_8,    KC_9,             KC_0,          KC_BSPC, 
        TO(NUMPAD),   KC_Y,             KC_U,       KC_I,    KC_O,             KC_P,          KC_BSLS, 
                     KC_H,     LT(JSYM,KC_J),   KC_K,    KC_L,    LT(EDIT,KC_SCLN),       KC_QUOTE, 
        CTL_T(KC_B), KC_N,             KC_M,       KC_COMM, KC_DOT,  LT(MEDIA,KC_SLSH),    LCTL(KC_RIGHT), 
        TD(GCA),    TD(CTLALL),        KC_LBRC,    KC_RBRC, KC_MS_BTN1,
      OS_CALT,     KC_TAB, 
      KC_DEL, 
      KC_CAPS,  SFTENT,  KC_SPC), 


  [MINIMAK4] = LAYOUT_ergodox(
    TD(FRBK2),       KC_1,           KC_2,       KC_3,        KC_4,    KC_5,    KC_F4, 
    KC_TAB,         KC_Q,           KC_W,       KC_D,        KC_R,    KC_K,    TO(EDIT), 
    OSL(EDIT),      KC_A,  LT(NUMPAD,KC_S),      KC_T,  LT(FSYM,KC_F),  KC_G, 
    OSM(MOD_LSFT),  KC_Z,           KC_X,       KC_C,        KC_V,    SFT_T(KC_B), KC_TAB, 
    TD(CTLALL),     OSL(ADJUST),    TD(GUCTL),  TD(SGCA),  TD(AGC), 
                                                               OS_CMD,    OS_CTL   , 
                                                                          KC_ESCAPE, 
                                                   KC_BSPACE,  TD(SHENT), OSL(EDIT), 
        KC_F5,       KC_6,             KC_7,       KC_8,    KC_9,             KC_0,          KC_BSPC, 
        TO(NUMPAD),   KC_Y,             KC_U,       KC_I,    KC_O,             KC_P,          KC_BSLS, 
                     KC_H,     LT(JSYM,KC_J),   KC_E,    KC_L,    LT(EDIT,KC_SCLN),       KC_QUOTE, 
        CTL_T(KC_B), KC_N,             KC_M,       KC_COMM, KC_DOT,  LT(MEDIA,KC_SLSH),     KC_MS_BTN1, 
        TD(GCA),    TD(CTLALL),        LGUI(KC_GRV),    KC_RBRC, KC_MS_BTN1,
      OS_ALT,     KC_TAB, 
      KC_DEL, 
      KC_CAPS,  SFT_T(KC_ENT),  KC_SPC), 

  [NUMPAD] = LAYOUT_ergodox(VRSN, KC_F11, KC_F12, KC_F1, KC_F2, KC_F3, _______, 
    _______, _______, KC_PGUP, KC_UP, KC_PGDOWN, _______, TO(QWERTY), 
    _______, _______, KC_LEFT, KC_DOWN, KC_RIGHT, _______, 
    _______, LGUI(KC_Z), LGUI(KC_X), LGUI(KC_C), LGUI(KC_V), LGUI(KC_Y), _______,
    _______, _______, _______, _______, _______, 
    _______, _______, KC_PSCREEN, _______, _______, TO(QWERTY), 

    _______, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, _______, 
    TO(EDIT), _______, KC_7,   KC_8,   KC_9, KC_KP_MINUS, _______, 
              _______, KC_4,   KC_5,   KC_6, KC_KP_PLUS, _______, 
    _______,  KC_COMM, KC_1,   KC_2,   KC_3, KC_KP_SLASH, _______, 
                       KC_0,   KC_DOT, KC_EQUAL, KC_KP_ASTERISK, _______,  
    _______,  _______, KC_INSERT, TO(EDIT), _______, _______), 

  [EDIT] = LAYOUT_ergodox(_______, _______, KC_MS_WH_UP, KC_MS_BTN1, KC_MS_BTN2, _______, _______, 
    _______, LGUI(LALT(KC_ESCAPE)), KC_MS_WH_DOWN, LALT(S(KC_LEFT)), LALT(S(KC_RIGHT)), _______, TO(NUMPAD), 
    _______, _______, LGUI(KC_GRV), LALT(KC_LEFT), LALT(KC_RIGHT), _______, 
    LCTL(KC_RIGHT), LGUI(KC_Z), LGUI(KC_X), LGUI(KC_C), LGUI(KC_V), LGUI(KC_Y), _______, 
    _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, TO(NUMPAD), 
    _______, _______, _______, S(KC_UP), _______, _______, KC_DELETE, 
    TO(QWERTY), LGUI(KC_T), KC_PGUP, KC_UP, KC_PGDOWN, KC_PSCREEN, _______, 
             LGUI(KC_LEFT), KC_LEFT, KC_DOWN, KC_RIGHT, LGUI(KC_RIGHT), _______, 
    _______, S(LGUI(KC_LEFT)), S(KC_LEFT), S(KC_DOWN), S(KC_RIGHT), S(LGUI(KC_RIGHT)), LCTL(KC_LEFT), 
    _______, _______, FORM_GET, FORM_PUT, _______, 
    _______, _______, _______, S(KC_F10), _______, _______), 

  [FSYM] = LAYOUT_ergodox(_______, _______, _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, _______, _______, 
    _______, _______, KC_TILD, KC_EXLM, _______, _______, 
    LCTL(KC_RIGHT), _______, _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, 
    _______, _______, _______, DEL_WRD, _______, _______, 
    _______, _______, _______, _______, _______, _______, _______, 
    _______, KC_CIRC,  KC_AMPR , KC_ASTR, KC_GRV ,  _______, _______, 
             KC_EQUAL, KC_MINUS, KC_UNDS, KC_BSLS, KC_COLON, KC_DQT ,
    _______, _______,  KC_PLUS , KC_SLSH, KC_PIPE, _______ , _______, 
    _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, _______), 

  [JSYM] = LAYOUT_ergodox(_______, _______, _______, _______, _______, _______, _______, 
    _______, KC_GRV,  KC_AT  , KC_LCBR, KC_RCBR, _______, _______, 
    _______, KC_HASH, KC_DLR , KC_LPRN,    KC_RPRN,    KC_LEFT, 
    _______, KC_PERC, KC_CIRC, KC_LBRACKET, KC_RBRACKET, _______, _______, 
    _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, _______, _______, 
    _______, _______, KC_QUES, KC_SLSH, KC_COLON, _______, 
    _______, _______, _______, _______, _______, _______, LCTL(KC_LEFT), 
    _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, LGUI(KC_DOWN), _______), 

  [MEDIA] = LAYOUT_ergodox(_______, _______, KC_MS_BTN4, _______, KC_MS_BTN5, _______, _______, 
    _______, KC_MS_WH_UP, KC_MS_WH_LEFT, KC_MS_UP, KC_MS_WH_RIGHT, _______, _______, 
    _______, KC_MS_WH_DOWN, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, _______, 
    _______, _______, KC_MS_ACCEL0, KC_MS_ACCEL1, KC_MS_ACCEL2, _______, _______, 
    _______, _______, _______, _______, KC_MS_BTN3, 
    _______, _______, _______, KC_MS_BTN1, KC_MS_BTN2, _______, 
    _______, _______, _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, _______, 
    _______, _______, KC_AUDIO_VOL_DOWN, KC_AUDIO_MUTE, KC_AUDIO_VOL_UP, _______, _______, 
    KC_MEDIA_REWIND, KC_MEDIA_FAST_FORWARD, _______, _______, _______, 
    _______, _______, _______, _______, KC_MS_BTN1, KC_MEDIA_PLAY_PAUSE), 

  [ADJUST] = LAYOUT_ergodox(_______, _______, _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, _______, _______, 
    _______, TO(EDIT), TO(NUMPAD), TO(FSYM), TO(JSYM), TO(MEDIA), 
    _______, _______, _______, _______, _______, _______, _______, 
    _______, TO(QWERTY), DF(MINIMAK4), DF(QWERTY), _______, 
    _______, _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, _______), 

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
    case FORM_GET:
      if (record->event.pressed) {
        tap_code(KC_BTN1);
        tap_code16(G(KC_A));
        tap_code16(G(KC_C));
      }
      return false;
    case FORM_PUT:
      if (record->event.pressed) {
        tap_code(KC_BTN1);
        tap_code16(G(KC_A));
        tap_code16(G(KC_V));
      }
      return false;
  }
  return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
  switch (get_highest_layer(state)) {
    case QWERTY:
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    break;
    case NUMPAD:
    ergodox_right_led_1_on();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    break;
    case EDIT:
    ergodox_right_led_1_off();
    ergodox_right_led_2_on();
    ergodox_right_led_3_off();
    break;
    case FSYM:
    ergodox_right_led_1_on();
    ergodox_right_led_2_on();
    ergodox_right_led_3_off();
    break;
    case JSYM:
    ergodox_right_led_1_on();
    ergodox_right_led_2_off();
    ergodox_right_led_3_on();
    break;
    case MEDIA:
    ergodox_right_led_1_off();
    ergodox_right_led_2_on();
    ergodox_right_led_3_on();      
    break;
    case ADJUST:
    ergodox_right_led_1_on();
    ergodox_right_led_2_on();
    ergodox_right_led_3_on();      
    break;
  }
  return state;
}
