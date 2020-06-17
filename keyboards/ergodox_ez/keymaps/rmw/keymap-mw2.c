// IF this is set to true, use the MacOS X version of the keymap. Else, use the Windows version.
bool mac = true;
// I want Second Key, Thumb Row, Right Hand plus L to produce LGUI(KC_L) on Win and LCTL(LGUI(KC_Q)) on MAC...

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE
  ,EPRM
  ,VRSN
  ,OS_CSFT = OSM(MOD_LSFT | MOD_LCTL)
  ,OS_ALT  = OSM(MOD_LALT)
  ,OS_CTL  = OSM(MOD_LCTL)
  ,OS_CMD  = OSM(MOD_LGUI)
  // Mac/Win split keycodes
  ,MAC_WIN
  ,MVW_LEFT
  ,MVW_RIGHT
  ,SELW_LEFT
  ,SELW_RIGHT
  ,MED_NEXT
  ,MED_PREV
  ,R_UNDO
  ,R_CUT
  ,R_COPY
  ,R_PASTE
  ,R_REDO
  ,NEW_TAB
  ,TASK_MAN
  ,R_HOME
  ,R_END
  ,SEL_HOME
  ,SEL_END
  ,R_ALC  // alt or command, depending
  ,R_CNC  // command or control, depending
  ,R_WNC  // Windows or control depending
  // end Mac/Win split keycodes
  ,FORM_GET
  ,FORM_PUT
  ,KILLMODS // write a little function that unsets all mods?
};

#define SFTENT SFT_T(KC_ENT)

enum layers {
    QWERTY  
   ,EXCEL 
   ,EDIT 
   ,RIGHTSYM 
   ,LEFTSYM 
   ,MEDIA 
   ,MINIMAK4 // does this work up here? or does it need to be lower?
   ,ADJUST 
};

// Tap Dance enum
enum {
 SHCAP = 0
 ,TDGUI
 ,SHENT
 ,FRBK
 ,FRBK2
 ,UMOD
 ,UMOD2
 ,GCA 
 ,AGC 
 ,SGCA
 ,CTLALL 
 ,GUCTL 
 ,CTLAND
};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    [SHCAP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, caps, shift_reset)
   ,[TDGUI] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, shiftgui, gui_reset)
   ,[SHENT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, shiftenter, shift_reset)
   ,[FRBK]  = ACTION_TAP_DANCE_DOUBLE(KC_WWW_BACK,KC_WWW_FORWARD)
   ,[FRBK2]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, forward_back_mac, ubermod_reset)
   ,[GCA]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ubermod_mac, ubermod_reset) // GUI->CTL->ALT
   ,[AGC]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ubermod2_mac, ubermod_reset) // ALT->GUI->CTL
   ,[SGCA] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, shift_and_mac, CASG_reset) // SG->SC->SA
   ,[CTLALL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ctrl_all_mac, ubermod_reset) // C->CG->CAG
   ,[GUCTL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, guictl, ubermod_reset) 
};

// Figure out something to replace layer 0 BRACKETs

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [QWERTY] = LAYOUT_ergodox( 
    // LEFT HAND
    TD(FRBK2),      KC_1,           KC_2,       KC_3,        KC_4,    KC_5,    KC_F4, 
    KC_TAB,         KC_Q,           KC_W,       KC_E,        KC_R,    KC_T,    TO(EDIT), 
    OSL(EDIT),      KC_A,  LT(EXCEL,KC_S),  KC_D, LT(RIGHTSYM,KC_F),  KC_G, 
    OSM(MOD_LSFT),  KC_Z,           KC_X,       KC_C,        KC_V,    SFT_T(KC_B), KC_TAB, 
    TD(CTLALL),     OSL(ADJUST),    TD(GUCTL),  TD(SGCA),  TD(AGC), 
                                                               OS_CMD,     OS_CTL   , 
                                                                          KC_ESCAPE, 
                                                   KC_BSPACE,  TD(SHENT), OSL(EDIT), 
    // RIGHT HAND
    KC_F5,       KC_6,          KC_7,       KC_8,       KC_9,             KC_0,     KC_BSPC, 
    TO(EXCEL),   KC_Y,          KC_U,       KC_I,       KC_O,             KC_P,     KC_BSLS, 
                 KC_H,  LT(LEFTSYM,KC_J),   KC_K,       KC_L,    LT(EDIT,KC_SCLN),  KC_QUOTE, 
    CTL_T(KC_B), KC_N,          KC_M,       KC_COMM,    KC_DOT,  LT(MEDIA,KC_SLSH), TD(SHENT), 
                               TD(GCA),    TD(CTLALL), KC_LBRC,  KC_RBRC,           KC_MS_BTN1,
    OS_ALT,     KC_TAB, 
    KC_DEL, 
    KC_CAPS,  SFTENT,  KC_SPC), 

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
        CTL_T(KC_B), KC_N,             KC_M,       KC_COMM, KC_DOT,  LT(MEDIA,KC_SLSH),     TD(SHENT), 
        TD(GCA),    TD(CTLALL),        KC_LBRC,    KC_RBRC, KC_MS_BTN1,
      OS_ALT,     KC_TAB, 
      KC_DEL, 
      KC_CAPS,  SFTENT,  KC_SPC), 

  [EXCEL] = LAYOUT_ergodox(
    VRSN, KC_F11, KC_F12, KC_F1, KC_F2, KC_F3, _______, 
    _______, _______, KC_PGUP, KC_UP, KC_PGDOWN, _______, TO(0), 
    _______, _______, KC_LEFT, KC_DOWN, KC_RIGHT, _______, 
    _______, R_UNDO , R_CUT  , R_COPY , R_PASTE , R_REDO , _______,
    _______, _______, _______, _______, _______, 
    _______, _______, KC_PSCREEN, _______, _______, TO(0), 

    _______, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, _______, 
    TO(EDIT), _______, KC_7,   KC_8,   KC_9, KC_KP_MINUS, _______, 
              _______, KC_4,   KC_5,   KC_6, KC_KP_PLUS, _______, 
    _______,  KC_COMM, KC_1,   KC_2,   KC_3, KC_KP_SLASH, _______, 
                       KC_0,   KC_DOT, KC_EQUAL, KC_KP_ASTERISK, _______,  
    _______,  _______, KC_INSERT, TO(EDIT), _______, _______), 

  [EDIT] = LAYOUT_ergodox(
    KC_ESCAPE, LALT(LCTL(KC_DELETE)), KC_MS_WH_UP, KC_MS_BTN1, KC_MS_BTN2, _______, _______, 
    _______, TASK_MAN, KC_MS_WH_DOWN, SELW_LEFT, SELW_RIGHT, _______, TO(EXCEL), 
    _______, _______, LGUI(KC_GRV), MVW_LEFT, MVW_RIGHT, _______, 
    _______, R_UNDO , R_CUT  , R_COPY , R_PASTE , R_REDO , _______,
    _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, TO(EXCEL), 

    _______, _______, _______, S(KC_UP), _______, _______, KC_DELETE, 
    TO(0), NEW_TAB, KC_PGUP, KC_UP, KC_PGDOWN, KC_PSCREEN, _______, 
             R_HOME, KC_LEFT, KC_DOWN, KC_RIGHT, R_END, _______, 
    _______, SEL_HOME, S(KC_LEFT), S(KC_DOWN), S(KC_RIGHT), SEL_END, _______, 
    _______, _______, FORM_GET, FORM_PUT, _______, 
    _______, _______, _______, S(KC_F10), _______, _______), 

  [RIGHTSYM] = LAYOUT_ergodox(
    _______, _______, _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, _______, _______, 
    _______, _______, KC_TILD, KC_EXLM, _______, _______, 
    _______, _______, _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, _______, 

    _______, _______, _______, _______, _______, _______, _______, 
    _______, KC_CIRC,  KC_AMPR , KC_ASTR, KC_GRV ,  _______, _______, 
             KC_EQUAL, KC_MINUS, KC_UNDS, KC_BSLS, KC_COLON, KC_DQT ,
    _______, _______,  KC_PLUS , KC_SLSH, KC_PIPE, _______ , _______, 
    _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, _______), 

  [LEFTSYM] = LAYOUT_ergodox(
    _______, _______, _______, S(KC_COMM), S(KC_DOT), _______, _______, 
    _______, KC_GRV,  KC_AT  , KC_LCBR,     KC_RCBR,     _______, _______, 
    _______, KC_HASH, KC_DLR , KC_LPRN,     KC_RPRN,     KC_LEFT, 
    _______, KC_PERC, KC_CIRC, KC_LBRACKET, KC_RBRACKET, _______, _______, 
    _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, _______, 

    _______, _______, _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, _______, _______, 
    _______, _______, KC_QUES, KC_SLSH, KC_COLON, _______, 
    _______, _______, _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, _______), 

  [MEDIA] = LAYOUT_ergodox(
    _______, _______, KC_MS_BTN4, _______, KC_MS_BTN5, _______, _______, 
    _______, KC_MS_WH_UP, KC_MS_WH_LEFT, KC_MS_UP, KC_MS_WH_RIGHT, _______, _______, 
    _______, KC_MS_WH_DOWN, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, _______, 
    _______, _______, KC_MS_ACCEL0, KC_MS_ACCEL1, KC_MS_ACCEL2, _______, _______, 
    _______, _______, _______, _______, KC_MS_BTN3, 
    _______, _______, _______, KC_MS_BTN1, KC_MS_BTN2, _______, 

    _______, _______, _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, _______, 
    _______, _______, KC_AUDIO_VOL_DOWN, KC_AUDIO_MUTE, KC_AUDIO_VOL_UP, _______, _______, 
    MED_PREV, MED_NEXT, _______, _______, _______, 
    _______, _______, _______, _______, KC_MS_BTN1, KC_MEDIA_PLAY_PAUSE), 

  [ADJUST] = LAYOUT_ergodox(
    _______, _______, _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, _______, _______, 
    _______, TO(EDIT), TO(EXCEL), TO(RIGHTSYM), TO(LEFTSYM), TO(MEDIA), 
    _______, MAC_WIN, _______, _______, _______, _______, _______, 
    _______, TO(QWERTY), DF(MINIMAK4), DF(QWERTY), _______,  
    _______, _______, _______, _______, _______, _______, 

    _______, _______, _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, _______), 

};

char * macwin_codes[17][2] = {
  {
    SS_LALT(SS_TAP(X_LEFT)),               // WIN - Move left by one word 
    // note: this is so it works on a win vm on mac. change to 
    //SS_LCTRL(SS_TAP(X_LEFT))             // for regular Windows
    SS_LALT(SS_TAP(X_LEFT))                // MAC
  },{
    SS_LALT(SS_TAP(X_RIGHT)),              // WIN - Move right by one word
    // Same here.
    SS_LALT(SS_TAP(X_RIGHT))               // MAC
  },{
    SS_LCTRL(SS_LSFT(SS_TAP(X_LEFT))),     // WIN - Select the word to the left
    SS_LALT(SS_LSFT(SS_TAP(X_LEFT)))       // MAC
  },{
    SS_LCTRL(SS_LSFT(SS_TAP(X_RIGHT))),    // WIN - Select the word to the right
    SS_LALT(SS_LSFT(SS_TAP(X_RIGHT)))      // MAC
  },{
    SS_TAP(X_MEDIA_NEXT_TRACK),            // WIN - Media Next
    SS_TAP(X_MEDIA_FAST_FORWARD)           // MAC
  },{  
    SS_TAP(X_MEDIA_PREV_TRACK),            // WIN - Media Previous
    SS_TAP(X_MEDIA_REWIND)                 // MAC
  },{  
    SS_LCTRL(SS_TAP(X_Z)),                 // WIN - UNDO
    SS_LGUI(SS_TAP(X_Z))                   // MAC,
  },{  
    SS_LCTRL(SS_TAP(X_X)),                 // WIN - CUT
    SS_LGUI(SS_TAP(X_X))                   // MAC,
  },{  
    SS_LCTRL(SS_TAP(X_C)),                 // WIN - COPY
    SS_LGUI(SS_TAP(X_C))                   // MAC,
  },{
    SS_LCTRL(SS_TAP(X_V)),                 // WIN - PASTE
    SS_LGUI(SS_TAP(X_V))                   // MAC,
  },{   
    SS_LCTRL(SS_TAP(X_Y)),                 // WIN - REDO
    SS_LGUI(SS_TAP(X_Y))                   // MAC,
  },{   
    SS_LCTRL(SS_TAP(X_T)),                 // WIN - NEW TAB
    SS_LGUI(SS_TAP(X_T))                   // MAC,
  },{
    SS_LCTRL(SS_LSFT(SS_TAP(X_ESCAPE))),   // WIN - TASK MAN
    SS_LALT(SS_LGUI(SS_TAP(X_ESCAPE)))     // MAC
  },{
    SS_TAP(X_HOME),                        // WIN - Go to beginning of line
    SS_LGUI(SS_TAP(X_LEFT))                // MAC
  },{
    SS_TAP(X_END),                         // WIN - Go to end of line
    SS_LGUI(SS_TAP(X_RIGHT))               // MAC
  },{
    SS_LSFT(SS_TAP(X_HOME)),               // WIN - Go to beginning of line
    SS_LSFT(SS_LGUI(SS_TAP(X_LEFT)))       // MAC
  },{
    SS_LSFT(SS_TAP(X_END)),                // WIN - Go to end of line
    SS_LSFT(SS_LGUI(SS_TAP(X_RIGHT)))      // MAC
  }
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
    case FORM_GET:
      if (record->event.pressed) {
        tap_code(KC_BTN1);
        if (mac) {
          tap_code16(G(KC_A));
          tap_code16(G(KC_C));
        }
        else {
          tap_code16(C(KC_A));
          tap_code16(C(KC_C));
        }
      }
      return false;
    case FORM_PUT:
      if (record->event.pressed) {
        tap_code(KC_BTN1);
        if (mac) {
          tap_code16(G(KC_A));
          tap_code16(G(KC_V));
        }
        else {
          tap_code16(C(KC_A));
          tap_code16(C(KC_V));
        }
      }
      return false;

    case MAC_WIN:
      if (record->event.pressed) {
        mac = !mac;
      }
      return false;

    case MVW_LEFT ... SEL_END: 
      if (record->event.pressed) {
        uint16_t index = keycode - MVW_LEFT;
        // Choose based on which key was pressed and whether OS is Win or Mac.
        if (mac){
          send_string(macwin_codes[index][1]);
          // something here needs to clear the one-shot layer.
        }
        else {
          send_string(macwin_codes[index][0]);
          // something here needs to clear the one-shot layer.
        }
      }
      return false;
  }
    return true;
}

void matrix_scan_user(void) {
    uint8_t layer = biton32(layer_state);
    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        case 3:
            ergodox_right_led_3_on();
            break;
        case 4:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            break;
        case 5:
            ergodox_right_led_1_on();
            ergodox_right_led_3_on();
            break;
        case 6:
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            break;
        case 7:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            break;
        default:
            break;
    }
};
