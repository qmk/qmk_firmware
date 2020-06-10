
enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE
  ,EPRM
  ,VRSN
  ,OS_GSFT = OSM(MOD_LSFT | MOD_LGUI)
  ,OS_CALT = OSM(MOD_LCTL | MOD_LALT)
  ,OS_ALT  = OSM(MOD_LALT)
  ,OS_CTL  = OSM(MOD_LCTL)
  ,OS_CMD  = OSM(MOD_LGUI)
  ,DEL_WRD = LALT(KC_BSPACE)
  ,FORM_GET
  ,FORM_PUT
};

enum layers {
    QWERTY
   ,MINIMAK4
   ,EXCEL 
   ,EDIT 
   ,RIGHTSYM 
   ,LEFTSYM 
   ,MEDIA 
   ,FLOP 
   ,ADJUST 
};

// Tap Dance enum
enum {
  SHCAP = 0
 ,TDGUI 
 ,TDGUI2 
 ,SHENT 
 ,FRBK 
 ,FRBK2 
 ,GCA 
 ,AGC 
 ,SGCA
 ,CTLALL 
 ,GUCTL 
 ,DLTR
};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    [SHCAP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, caps, shift_reset)
   ,[TDGUI] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, shiftgui, gui_reset)
   ,[TDGUI2] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, guictl, ubermod_reset)
   ,[SHENT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, shiftenter, shift_reset)
   ,[FRBK]  = ACTION_TAP_DANCE_DOUBLE(KC_WWW_BACK,KC_WWW_FORWARD)
   ,[FRBK2]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, forward_back_mac, ubermod_reset)
   ,[GCA]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ubermod_mac, ubermod_reset) // GUI->CTL->ALT
   ,[AGC]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ubermod2_mac, ubermod_reset) // ALT->GUI->CTL
   ,[SGCA] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, shift_and_mac, CASG_reset) // SG->SC->SA
   ,[CTLALL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ctrl_all_mac, ubermod_reset) // C->CG->CA->CAG
   ,[GUCTL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, guictl, ubermod_reset) 
   ,[DLTR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, deleter, ubermod_reset) // backspace, backspace, alt backspace, gui backspace
};

// Figure out something to replace layer 0 BRACKETs 

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [QWERTY] = LAYOUT_ergodox(
    TD(FRBK2),      KC_1,           KC_2,       KC_3,        KC_4,          KC_5,    KC_F4, 
    KC_TAB,         KC_Q,           KC_W,       KC_E,        KC_R,          KC_T,    TO(EDIT), 
    OSL(EDIT),      KC_A,  LT(EXCEL,KC_S),      KC_D,  LT(RIGHTSYM,KC_F),   KC_G, 
    LCTL(KC_LEFT),  KC_Z,           KC_X,       KC_C,        KC_V,    SFT_T(KC_B),   KC_TAB, 
    TD(CTLALL),     OSL(ADJUST),    TD(GUCTL),  TD(SGCA),  TD(AGC), 
                                                               OS_CMD,    OS_CTL   , 
                                                                          KC_ESCAPE, 
                                                   KC_BSPACE,  TD(SHENT), OSL(EDIT), 

        KC_F5,       KC_6,             KC_7,       KC_8,    KC_9,             KC_0,          KC_BSPC, 
        TO(EXCEL),   KC_Y,             KC_U,       KC_I,    KC_O,             KC_P,          KC_BSLS, 
                     KC_H,     LT(LEFTSYM,KC_J),   KC_K,    KC_L,    LT(EDIT,KC_SCLN),       KC_QUOTE, 
        CTL_T(KC_B), KC_N,             KC_M,       KC_COMM, KC_DOT,  LT(MEDIA,KC_SLSH),    LCTL(KC_RIGHT), 
        TD(GCA),    TD(CTLALL),        KC_LBRC,    KC_RBRC, KC_MS_BTN1,
      OS_CALT,     KC_TAB, 
      KC_DEL, 
      KC_CAPS,  SFT_T(KC_ENT),  KC_SPC), 


  [MINIMAK4] = LAYOUT_ergodox(
    TD(FRBK2),       KC_1,           KC_2,       KC_3,        KC_4,    KC_5,    KC_F4, 
    KC_TAB,         KC_Q,           KC_W,       KC_D,        KC_R,    KC_K,    TO(EDIT), 
    OSL(EDIT),      KC_A,  LT(EXCEL,KC_S),      KC_T,  LT(RIGHTSYM,KC_F),  KC_G, 
    OSM(MOD_LSFT),  KC_Z,           KC_X,       KC_C,        KC_V,    SFT_T(KC_B), KC_TAB, 
    TD(CTLALL),     OSL(ADJUST),    TD(GUCTL),  TD(SGCA),  TD(AGC), 
                                                               OS_CMD,    OS_CTL   , 
                                                                          KC_ESCAPE, 
                                                   KC_BSPACE,  TD(SHENT), OSL(EDIT), 
        KC_F5,       KC_6,             KC_7,       KC_8,    KC_9,             KC_0,          KC_BSPC, 
        TO(EXCEL),   KC_Y,             KC_U,       KC_I,    KC_O,             KC_P,          KC_BSLS, 
                     KC_H,     LT(LEFTSYM,KC_J),   KC_E,    KC_L,    LT(EDIT,KC_SCLN),       KC_QUOTE, 
        CTL_T(KC_B), KC_N,             KC_M,       KC_COMM, KC_DOT,  LT(MEDIA,KC_SLSH),     KC_MS_BTN1, 
        TD(GCA),    TD(CTLALL),        LGUI(KC_GRV),    KC_RBRC, KC_MS_BTN1,
      OS_ALT,     KC_TAB, 
      KC_DEL, 
      KC_CAPS,  SFT_T(KC_ENT),  KC_SPC), 

  [EXCEL] = LAYOUT_ergodox(VRSN, KC_F11, KC_F12, KC_F1, KC_F2, KC_F3, _______, 
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

  [EDIT] = LAYOUT_ergodox(EPRM, _______, KC_MS_WH_UP, KC_MS_BTN1, KC_MS_BTN2, _______, _______, 
    _______, LGUI(LALT(KC_ESCAPE)), KC_MS_WH_DOWN, LALT(S(KC_LEFT)), LALT(S(KC_RIGHT)), _______, TO(EXCEL), 
    _______, _______, LGUI(KC_GRV), LALT(KC_LEFT), LALT(KC_RIGHT), _______, 
    _______, LGUI(KC_Z), LGUI(KC_X), LGUI(KC_C), LGUI(KC_V), LGUI(KC_Y), _______, 
    _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, TO(EXCEL), 
    _______, _______, _______, S(KC_UP), _______, _______, KC_DELETE, 
    TO(QWERTY), LGUI(KC_T), KC_PGUP, KC_UP, KC_PGDOWN, KC_PSCREEN, _______, 
             LGUI(KC_LEFT), KC_LEFT, KC_DOWN, KC_RIGHT, LGUI(KC_RIGHT), _______, 
    _______, S(LGUI(KC_LEFT)), S(KC_LEFT), S(KC_DOWN), S(KC_RIGHT), S(LGUI(KC_RIGHT)), _______, 
    _______, _______, FORM_GET, FORM_PUT, _______, 
    _______, _______, _______, S(KC_F10), _______, _______), 

  [RIGHTSYM] = LAYOUT_ergodox(_______, _______, _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, _______, _______, 
    _______, _______, KC_TILD, KC_EXLM, _______, _______, 
    _______, _______, _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, 
    _______, _______, _______, DEL_WRD, _______, _______, 
    _______, _______, _______, _______, _______, _______, _______, 
    _______, KC_CIRC,  KC_AMPR , KC_ASTR, KC_GRV ,  _______, _______, 
             KC_EQUAL, KC_MINUS, KC_UNDS, KC_BSLS, KC_COLON, KC_DQT ,
    _______, _______,  KC_PLUS , KC_SLSH, KC_PIPE, _______ , _______, 
    _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, _______), 

  [LEFTSYM] = LAYOUT_ergodox(_______, _______, _______, _______, _______, _______, _______, 
    _______, KC_GRV,  KC_AT  , KC_LCBR, KC_RCBR, _______, _______, 
    _______, KC_HASH, KC_DLR , KC_LPRN,    KC_RPRN,    KC_LEFT, 
    _______, KC_PERC, KC_CIRC, KC_LBRACKET, KC_RBRACKET, _______, _______, 
    _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, _______, _______, 
    _______, _______, KC_QUES, KC_SLSH, KC_COLON, _______, 
    _______, _______, _______, _______, _______, _______, _______, 
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
    _______, TO(EDIT), TO(EXCEL), TO(RIGHTSYM), TO(LEFTSYM), TO(MEDIA), 
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
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;   
    case FORM_GET:
      if (record->event.pressed) {
        //click KC_MS_BTN1
        //register_code16(KC_BTN1);
        //unregister_code16(KC_BTN1);
        tap_code16(KC_MS_BTN1);
        SEND_STRING(SS_LGUI("a"));
        SEND_STRING(SS_LGUI("c"));
      }
      return false;
      break;
    case FORM_PUT:
      if (record->event.pressed) {
        tap_code16(KC_MS_BTN1);
        SEND_STRING(SS_LGUI("a"));
        SEND_STRING(SS_LGUI("v"));
      }
      return false;
      break;
  }
  return true;
}


// LEADER_EXTERNS();

void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
        case 2:
            ergodox_right_led_1_on();
            break;
        case 3:
            ergodox_right_led_2_on();
            break;
        case 4:
            ergodox_right_led_3_on();
            break;
        case 5:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            break;
        case 6:
            ergodox_right_led_1_on();
            ergodox_right_led_3_on();
            break;
        case 7:
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            break;
        case 8:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            break;
        default:
            break;
    }

        // LEADER_DICTIONARY() {
    //   leading = false;
    //   leader_end();

    //   SEQ_ONE_KEY(KC_F) {
    //     register_code(KC_S);
    //     unregister_code(KC_S);
    //   }
    //   SEQ_TWO_KEYS(KC_A, KC_S) {
    //     register_code(KC_H);
    //     unregister_code(KC_H);
    //   }
    //   SEQ_THREE_KEYS(KC_A, KC_S, KC_D) {
    //     register_code(KC_LGUI);
    //     register_code(KC_S);
    //     unregister_code(KC_S);
    //     unregister_code(KC_LGUI);
    //   }
    // }
};
