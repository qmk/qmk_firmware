#include QMK_KEYBOARD_H
#include <stdio.h>

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use NMBbers.

//Declare layers
enum layer_number {
    _QWERTY = 0,
    _NMB,
    _EMACS,
    _META,
    _FN,
    _SCT,
};

//Declare custum keyCodes
enum custom_keycodes {
    QT_SCT = SAFE_RANGE,        //Quit Select
    INS_L,                      //Insert Line
    KILL_L,                     //Kill Line
    SEL_CPY,                    //Selection Copy
    SEL_CUT,                    //Selection Cut
    SEL_DEL,                    //Selection Delete
    SEL_FIND,                   //Selection Find
    SEL_REP,                    //Selection Replace
    SND_ID,                     //Send ID
    RST_MOD,                    //Reset Modefier Key
    SFT_SPC,                    //SHIFT & Space
};

//Alias
#define MT_MT LT(_META,KC_TAB)    //hold:"META" tap:"tab"
#define MT_EE LT(_EMACS,KC_ESC)   //hold:"EMACS" tap:"ESC"
#define MT_NE LT(_NMB,KC_ENT)     //hold:"NMB" tap:"Enter"
#define MT_FK LT(_FN,KC_K)        //hold:"Function" tap:"k"
#define MT_FD LT(_FN,KC_D)        //hold:"Function" tap:"D"
#define MT_SS LSFT_T(KC_SPC)      //hold:"Shift" tap:"Space"

#define MC_BR LCTL(KC_DOT)        //CTRL + .          'Bunsetsu Right'
#define MC_BL LCTL(KC_COMM)       //CTRL + ,          'Bunsetsu Left'
#define MC_PSC G(S(KC_S))         //Print screen
#define MC_DTR G(C(KC_RIGHT))     //Desk top move right
#define MC_DTL G(C(KC_LEFT))      //Desk top move left
#define MC_LCK G(KC_L)            //Screen Lock
#define MC_MIN G(KC_M)            //Window Minimize
#define MC_SRH G(KC_S)            //Search
#define MC_MAX G(KC_UP)           //Window Maxmize

#define JP_AT KC_LBRC             // @
#define JP_CIRC KC_EQL            // ^, ~
#define JP_COLN KC_QUOT           // :, *
#define JP_LBRC KC_RBRC           // [
#define JP_RBRC KC_NUHS           // ]
#define JP_LCBR LSFT(JP_LBRC)     // {
#define JP_RCBR LSFT(JP_RBRC)     // }
#define JP_LPRN LSFT(KC_8)        // (
#define JP_RPRN LSFT(KC_9)        // )
#define JP_QUOT LSFT(KC_7)        //',"
#define JP_AMPR LSFT(KC_6)        // &
#define JP_UNDS LSFT(KC_INT1)     //_
#define JP_PLUS LSFT(KC_SCLN)     // +
#define JP_EQL LSFT(KC_MINS)      // =
#define JP_ASTR LSFT(JP_COLN)     // *
#define JP_GRV LSFT(JP_AT)        //`
#define JP_PIPE LSFT(KC_INT3)     //|
#define JP_TILD LSFT(KC_EQL)      //~

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT( \
  //,-----------------------------------------------------|   |------------------------------------------------------.
       JP_GRV,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_MINS,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
        MT_EE,    KC_A,    KC_S,   MT_FD,    KC_F,   KC_G,         KC_H,    KC_J,   MT_FK,    KC_L, KC_SCLN, JP_QUOT,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
        MT_MT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,RCS_T(JP_PIPE),
  //|--------+--------+--------+--------+--------+--------/   \--------+--------+--------+---------+--------+--------'
                        KC_LCTL, KC_MHEN,   MT_SS, KC_LGUI,     KC_RGUI,   MT_NE, KC_HENK,  KC_RALT /*KC_LANG2,,,,,KC_LANG1*/
  //                  `--------+--------+--------+--------'   `--------+--------+--------+---------'
  ),

  [_NMB] = LAYOUT( \
  //,-----------------------------------------------------|   |-----------------------------------------------------.
      JP_TILD, KC_EXLM,   JP_AT, KC_HASH,  KC_DLR, KC_PERC,     JP_CIRC, JP_AMPR, JP_ASTR, JP_LPRN, JP_RPRN, JP_PLUS,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      _______,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  JP_EQL,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      _______, JP_UNDS, KC_MINS, JP_LPRN, JP_LCBR, JP_LBRC,     JP_RBRC, JP_RCBR, JP_RPRN, KC_DOT,  JP_PLUS, KC_JYEN,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
                        RST_MOD, _______, KC_LSFT, _______,     _______, _______, _______, _______
  //                  `--------+--------+--------+--------'   `--------+--------+--------+--------'
  ),

  [_EMACS] = LAYOUT( \
  //,-----------------------------------------------------|   |-----------------------------------------------------.
       MC_SRH, C(KC_A), C(KC_X),  KC_END,  KC_PGUP, MC_MIN,     C(KC_V),S(KC_TAB), KC_TAB,   INS_L,  MC_PSC,  KC_ESC,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      _______, KC_HOME,  KILL_L,  KC_DEL,C(KC_F),   MC_DTR,     KC_BSPC, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,   KC_F2,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
    MO(_META),  MC_MAX, C(KC_Y), C(KC_C), KC_PGDN,  MC_DTL,  KC_MS_BTN3,  KC_ENT,   MC_BL,   MC_BR, C(KC_Z),LCA(KC_DEL),
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
                        RST_MOD,TG(_SCT), KC_LSFT, _______,     _______,MO(_NMB), _______, _______
  //                  `--------+--------+--------+--------'   `--------+--------+--------+--------'
  ),

  [_META] = LAYOUT( \
  //,-----------------------------------------------------|   |-----------------------------------------------------.
       SND_ID, _______,_______,C(KC_END),C(KC_PGUP),_______,    _______, _______,S(KC_TAB),_______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
   MO(_EMACS),C(KC_HOME),_______,C(KC_DEL),C(KC_H),_______, C(KC_BSPC),C(KC_LEFT),C(KC_DOWN),C(KC_UP),C(KC_RGHT),_______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      _______, _______,_______,_______,C(KC_PGDN),  MC_LCK,  KC_MS_BTN3,  KC_ENT, _______, _______, C(KC_Z), _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
                        RST_MOD, _______, KC_LSFT, _______,     _______,MO(_NMB), _______, _______
  //                  `--------+--------+--------+--------'   `--------+--------+--------+--------'
  ),

  [_FN] = LAYOUT( \
  //,-----------------------------------------------------|   |-----------------------------------------------------.
      _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,     _______, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
   MO(_EMACS),   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  A(KC_LEFT), KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R,A(KC_RIGHT),
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
    MO(_META),  KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,   _______,KC_MS_BTN1,KC_MS_BTN3,KC_MS_BTN2,_______,_______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
                        RST_MOD, _______, KC_LSFT, _______,     _______,MO(_NMB), _______, _______
  //                  `--------+--------+--------+--------'   `--------+--------+--------+--------'
  ),

    [_SCT] = LAYOUT( \
  //,-----------------------------------------------------|   |-----------------------------------------------------.
       KC_ESC, XXXXXXX, SEL_CUT,S(KC_END),XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
   TO(_QWERTY),S(KC_HOME),XXXXXXX,SEL_DEL,SEL_FIND,SEL_REP,   SEL_DEL,S(KC_LEFT),S(KC_DOWN),S(KC_UP),S(KC_RGHT),XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
    MO(_META), C(KC_Z), XXXXXXX, SEL_CPY, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
                        RST_MOD,MO(_EMACS),KC_LSFT,_______,     _______,MO(_NMB), _______, _______
  //                  `--------+--------+--------+--------'   `--------+--------+--------+--------'
  ),
};


#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) return OLED_ROTATION_180;
    return rotation;
}

void render_layer_state(void) {
  switch (get_highest_layer(layer_state)) {
    case _QWERTY:
      oled_write_ln_P(PSTR("Layer: Default"), false);
      break;
    case _NMB:
      oled_write_ln_P(PSTR("Layer: Number"), false);
      break;
    case _EMACS:
      oled_write_ln_P(PSTR("Layer: Emacs"), false);
      break;
    case _META:
      oled_write_ln_P(PSTR("Layer: Meta"), false);
      break;
    case _FN:
      oled_write_ln_P(PSTR("Layer: Function"),false);
      break;
    case _SCT:
      oled_write_ln_P(PSTR("Layer: Select"),false);
      break;

    default:
      oled_write_ln_P(PSTR("Layer: Undefined"), false);
    }
}

void render_logo(void) {
    static const char PROGMEM logo[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0};
    oled_write_P(logo, false);
}

char keylog_str[24]  = {};
char keylogs_str[21] = {};
int  keylogs_str_idx = 0;

const char code_to_name[60] = {' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'R', 'E', 'B', 'T', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ';', '\'', ' ', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
    char name = ' ';
    if (keycode < 60) {
        name = code_to_name[keycode];
    }

    // update keylog
    snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c", record->event.key.row, record->event.key.col, keycode, name);

    // update keylogs
    if (keylogs_str_idx == sizeof(keylogs_str) - 1) {
        keylogs_str_idx = 0;
        for (int i = 0; i < sizeof(keylogs_str) - 1; i++) {
            keylogs_str[i] = ' ';
        }
    }

    keylogs_str[keylogs_str_idx] = name;
    keylogs_str_idx++;
}

const char *read_keylog(void) { return keylog_str; }
const char *read_keylogs(void) { return keylogs_str; }

void oled_task_user(void) {
    if (is_keyboard_master()) {
        render_layer_state();
        oled_write_ln(read_keylog(), false);
        oled_write_ln(read_keylogs(), false);
    } else {
        render_logo();
    }
}
#endif


static bool SHIFT_PRESSED = false;
static bool EXCEPTIONALY_SHIFT_PRESSED = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
    set_keylog(keycode, record);
#endif
  }

  switch (keycode) {
    case MT_SS:
      if(record->event.pressed){
        SHIFT_PRESSED = true;
      }else{
        SHIFT_PRESSED = false;
      }
      break;

    case KILL_L:
      if(record->event.pressed){
        SEND_STRING(SS_DOWN(X_LSFT) SS_TAP(X_END) SS_UP(X_LSFT) SS_TAP(X_DEL));
      }
      return false;
      break;

    case INS_L:
      if(record->event.pressed){
        SEND_STRING(SS_TAP(X_HOME) SS_TAP(X_ENT));
      }
      return false;
      break;

    case SEL_DEL:
      if(record->event.pressed){
        SEND_STRING(SS_TAP(X_DEL));
        layer_move(_EMACS);
      }
      return false;
      break;

    case SEL_CPY:
      if(record->event.pressed){
        SEND_STRING(SS_LCTL("c") );
        layer_move(_EMACS);
      }
      return false;
      break;

    case SEL_CUT:
      if(record->event.pressed){
        SEND_STRING(SS_LCTL("x"));
        layer_move(_EMACS);
      }
      return false;
      break;

    case SEL_FIND:
      if(record->event.pressed){
        SEND_STRING(SS_LCTL("f"));
        layer_move(_EMACS);
      }
      return false;
      break;

    case SEL_REP:
      if(record->event.pressed){
        SEND_STRING(SS_LCTL("h"));
        layer_move(_EMACS);
      }
      return false;
      break;

    case SND_ID:
      if(record->event.pressed){
        SEND_STRING("aaa031963"SS_TAP(X_TAB));
      }
      return false;
      break;

    case RST_MOD:
      if(record->event.pressed){
          clear_keyboard();
          layer_move(_QWERTY);
        }
      return false;
      break;

    default:
      if(SHIFT_PRESSED || EXCEPTIONALY_SHIFT_PRESSED){
        switch(keycode){
          case KC_MINS:
            if(record->event.pressed){
              register_code(KC_INT1);
              EXCEPTIONALY_SHIFT_PRESSED = true;
            }else{
              unregister_code(KC_LSFT);
              if(SHIFT_PRESSED){
                register_code(KC_LSFT);
              }
              EXCEPTIONALY_SHIFT_PRESSED =false;
            }
            return false;
            break;

          case KC_SCLN:
            if(record->event.pressed){
              unregister_code(KC_LSFT);
              register_code(KC_QUOT);
              EXCEPTIONALY_SHIFT_PRESSED = true;
            }else{
              unregister_code(KC_LSFT);
              if(SHIFT_PRESSED){
                register_code(KC_LSFT);
              }
              EXCEPTIONALY_SHIFT_PRESSED =false;
            }
            return false;
            break;

          case JP_QUOT:
            if(record->event.pressed){
              register_code(KC_2);
              EXCEPTIONALY_SHIFT_PRESSED = true;
            }else{
              unregister_code(KC_LSFT);
              if(SHIFT_PRESSED){
                register_code(KC_LSFT);
              }
              EXCEPTIONALY_SHIFT_PRESSED =false;
            }
            return false;
            break;

          case JP_GRV:
            if(record->event.pressed){
              register_code(KC_EQL);
              EXCEPTIONALY_SHIFT_PRESSED = true;
            }else{
              unregister_code(KC_LSFT);
              if(SHIFT_PRESSED){
                register_code(KC_LSFT);
              }
            EXCEPTIONALY_SHIFT_PRESSED = false;
            }
            return false;
            break;

        }
      }
    }
  return true;
}
