/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
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
#define MT_MT LT(3,KC_TAB)    //hold:"META" tap:"tab"
#define MT_EE LT(2,KC_ESC)   //hold:"EMACS" tap:"ESC"
#define MT_NE LT(1,KC_ENT)     //hold:"NMB" tap:"Enter"
#define MT_FK LT(4,KC_K)        //hold:"Function" tap:"k"
#define MT_FD LT(4,KC_D)        //hold:"Function" tap:"D"
#define MT_SS LSFT_T(KC_SPC)      //hold:"Shift" tap:"Space"
//#define MT_AM LALT_T(KC_MHEN)   //hold:"LALT" tap:"MHEN"
//#define MT_AH RALT_T(KC_HENK)   //hold:"RALT" tap:"HENK"

#define MC_BR LCTL(KC_DOT)        //CTRL + .          'Bunsetsu Right'
#define MC_BL LCTL(KC_COMM)       //CTRL + ,          'Bunsetsu Left'
#define MC_PSC G(S(KC_S))         //Print screen
#define MC_DTR G(C(KC_RIGHT))     //Desk top move right
#define MC_DTL G(C(KC_LEFT))      //Desk top move left
#define MC_LCK G(KC_L)            //Screen Lock
#define MC_MIN G(KC_M)            //Window Minimize
#define MC_SRH G(KC_S)            //Search
#define MC_MAX G(KC_UP)           //Window Maxmize

#define JP_AT KC_LBRC    // @
#define JP_CIRC KC_EQL   // ^, ~
#define JP_COLN KC_QUOT  // :, *
#define JP_LBRC KC_RBRC  // [
#define JP_RBRC KC_NUHS  // ]
#define JP_LCBR LSFT(JP_LBRC)  // {
#define JP_RCBR LSFT(JP_RBRC)  // }
#define JP_LPRN LSFT(KC_8)     // (
#define JP_RPRN LSFT(KC_9)     // )
#define JP_QUOT LSFT(KC_7) //',"
#define JP_AMPR LSFT(KC_6)     // &
#define JP_UNDS LSFT(KC_INT1)   //_
#define JP_PLUS LSFT(KC_SCLN)  // +
#define JP_EQL LSFT(KC_MINS)   // =
#define JP_ASTR LSFT(JP_COLN)  // *
#define JP_GRV LSFT(JP_AT)    //`
#define JP_PIPE LSFT(KC_INT3) //|
#define JP_TILD LSFT(KC_EQL)    //~

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------|   |------------------------------------------------------.
       JP_GRV,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_MINS,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
        MT_EE,    KC_A,    KC_S,   MT_FD,    KC_F,    KC_G,        KC_H,    KC_J,   MT_FK,    KC_L, KC_SCLN, JP_QUOT,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
        MT_MT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, JP_PIPE,
  //|--------+--------+--------+--------+--------+--------/   \--------+--------+--------+---------+--------+--------'
                                 KC_LCTL, KC_MHEN,   MT_SS,       MT_NE, KC_HENK,  KC_RALT
  //                           `--------+--------+--------'   `--------+--------+---------'
  ),

  [1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------|   |-----------------------------------------------------.
      JP_TILD, KC_EXLM,   JP_AT, KC_HASH,  KC_DLR, KC_PERC,     JP_CIRC, JP_AMPR, JP_ASTR, JP_LPRN, JP_RPRN, JP_PLUS,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
        MO(2),   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  JP_EQL,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
        MO(3), JP_UNDS, KC_MINS, JP_LPRN, JP_LCBR, JP_LBRC,     JP_RBRC, JP_RCBR, JP_RPRN, KC_DOT,  JP_PLUS, KC_JYEN,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
                                 RST_MOD, _______, KC_LSFT,     _______, _______, _______
  //                           `--------+--------+--------'   `--------+--------+---------'
  ),

  [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------|   |-----------------------------------------------------.
       MC_SRH, C(KC_A), C(KC_X),  KC_END,  KC_PGUP, MC_MIN,     C(KC_V),S(KC_TAB), KC_TAB,   INS_L,  MC_PSC,  KC_ESC,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      _______, KC_HOME,  KILL_L,  KC_DEL,C(KC_F),   MC_DTR,     KC_BSPC, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,   KC_F2,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
        MO(3),  MC_MAX, C(KC_Y), C(KC_C), KC_PGDN,  MC_DTL,  KC_MS_BTN3,  KC_ENT,   MC_BL,   MC_BR, C(KC_Z),LCA(KC_DEL),
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
                                   RST_MOD,TG(5), KC_LSFT,    MO(1), _______, _______
  //                           `--------+--------+--------'   `--------+--------+--------'
  ),

  [3] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------|   |-----------------------------------------------------.
       SND_ID, _______,_______,C(KC_END),C(KC_PGUP),_______,    _______, _______,S(KC_TAB),_______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
        MO(2),C(KC_HOME),_______,_______, C(KC_H), _______,  C(KC_BSPC),C(KC_LEFT),C(KC_DOWN),C(KC_UP),C(KC_RGHT),_______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      _______, _______,_______,_______,C(KC_PGDN),  MC_LCK,  KC_MS_BTN3,  KC_ENT, _______, _______, C(KC_Z), _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
                                 RST_MOD, _______, KC_LSFT,     _______, _______, _______
  //                           `--------+--------+--------'   `--------+--------+--------'
  ),

  [4] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------|   |-----------------------------------------------------.
      _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,     _______, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
        MO(2),   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  A(KC_LEFT), KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R,A(KC_RIGHT),
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
        MO(3),  KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,   _______,KC_MS_BTN1,KC_MS_BTN3,KC_MS_BTN2,_______,_______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
                                 RST_MOD, _______, _______,     _______, _______, _______
  //                           `--------+--------+--------'   `--------+--------+--------'
  ),

  [5] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------|   |-----------------------------------------------------.
       KC_ESC, XXXXXXX, SEL_CUT,S(KC_END),XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
       TO(0),S(KC_HOME),XXXXXXX, SEL_DEL,SEL_FIND, SEL_REP,   SEL_DEL,S(KC_LEFT),S(KC_DOWN),S(KC_UP),S(KC_RGHT),XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
        MO(3), C(KC_Z), XXXXXXX, SEL_CPY, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
                                 RST_MOD,   MO(2), _______,     _______, _______, _______
  //                           `--------+--------+--------'   `--------+--------+--------'
  ),

  [6] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        RESET, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_ENT, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'
  )
};

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_master) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

#define L_BASE 0
#define L_NMB 2
#define L_EMACS 4
#define L_META 8
#define L_FN 16
#define L_SCT 32

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (layer_state) {
        case L_BASE:
            oled_write_ln_P(PSTR("Default"), false);
            break;
        case L_NMB:
            oled_write_ln_P(PSTR("Number"), false);
            break;
        case L_EMACS:
            oled_write_ln_P(PSTR("Emacs"), false);
            break;
        case L_META:
            oled_write_ln_P(PSTR("Meta"), false);
            break;
        case L_FN:
            oled_write_ln_P(PSTR("Function"), false);
            break;
        case L_SCT:
              oled_write_ln_P(PSTR("Select"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undefined"), false);
            break;
    }
}


char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);
}

void oled_render_keylog(void) {
    oled_write(keylog_str, false);
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

void oled_task_user(void) {
    if (is_master) {
        oled_render_layer_state();
        oled_render_keylog();
    } else {
        oled_render_logo();
    }
}

#endif // OLED_DRIVER_ENABLE


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
        layer_move(2);
      }
      return false;
      break;

    case SEL_CPY:
      if(record->event.pressed){
        SEND_STRING(SS_LCTL("c") );
        layer_move(2);
      }
      return false;
      break;

    case SEL_CUT:
      if(record->event.pressed){
        SEND_STRING(SS_LCTL("x"));
        layer_move(2);
      }
      return false;
      break;

    case SEL_FIND:
      if(record->event.pressed){
        SEND_STRING(SS_LCTL("f"));
        layer_move(2);
      }
      return false;
      break;

    case SEL_REP:
      if(record->event.pressed){
        SEND_STRING(SS_LCTL("h"));
        layer_move(2);
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
          layer_move(0);
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
