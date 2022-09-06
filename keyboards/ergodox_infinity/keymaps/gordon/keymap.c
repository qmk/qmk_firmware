#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"
#include "process_keycode/process_tap_dance.h"
#include "gordon.h"

#include "keymap_german.h"

#include "keymap_nordic.h"


enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD,
};


// Custom tapping terms for each key.
// Requires changes to action_taping.c
// uint16_t get_tapping_term(keyevent_t* event) {
//     uint16_t keycode = keymap_key_to_keycode(layer_switch_get_layer(event->key), event->key);
//     if (keycode == NAV_E ) {
//         return TAPPING_TERM + 50;
//     }
//     return TAPPING_TERM;
// }


// _XXXXXX_ is a symbol that means, "DO NOT ASSIGN THIS KEY TO ANTYING", because the key
//        underneath this layer is the key that sends you to/from this layer.
//        Meaning, if you were to put something here - then you will be stuck in this layer.
//        It is simply a visual reminder not to use that key for this layer.
//        Example: On the numpad layer, under the letter `D` is `_XXXXXXX_`, because pressing and holding
//          `D` sends you to the numpad layer

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


//**************************FIRST LAYER - LAYER ZERO **************************************
  [_QWERTY] = LAYOUT_ergodox(

    SHF6_AF7, F1_F13  ,    F2_F14,   TD(F3D), F4_ALTF4,    F5_F15,   KC_F11,
    SPRK_TCK  , Q_ESC   ,  CTR_SH_W,     NAV_E, ALT_SH_R,      KC_T, PRINTSCR,
    KC_TAB  , KC_A    ,     MEH_S,  NUMPAD_D,   CTRL_F,     WIN_G,
    OSL(_ONESHOT), CTRL_Z  ,   HYPER_X,   MOUSE_C,    ALT_V,      KC_B, OSL(_MOUSE),
    KC_MINUS, KC_GRAVE, KC_DELETE,   KC_LEFT, KC_RIGHT,

                                              LSFT(KC_INSERT),  TT(_QWERTY_KIDS),
                                                          ________ ,
                                    KC_LSHIFT, SYMB_BSP,  KC_INSERT   ,

                 F12_RUN,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10, TD(CALCCOMP),
                CALTDEL ,    KC_Y,      KC_U,     KC_I,     KC_O,      KC_P,  MODRESET,
                             WIN_H,   CTRL_J, APP_SW_K,    MEH_L,  COL_MOUS, END_HOME,
             OSL(_ONESHOT),     KC_N,  ALT_M, COMMA_TD, HYPE_DOT,  KC_SLASH, ID_MAN_IP,
                                       KC_UP,  KC_DOWN,KC_DELETE,    KC_TILD,    KC_UNDS,

  TT(_STREET_FIGHTER),  ________,
         KC_PGUP,
  KC_PGDOWN, LT(_NAV,KC_ENTER), SPAC_TXT),


  //**************************SYMBOLS LAYER**************************
  [_SYMBOLS] = LAYOUT_ergodox(
    ________, ________, ________, ________, ________, ________,  ________,
    ________, DEREF   ,    KC_AT,  KC_LCBR,  KC_RCBR,  KC_CIRC,  ________,
    ________,  KC_EXLM,  KC_HASH,  KC_LPRN,  KC_RPRN,  ________,
    ________,KC_DOLLAR,  KC_PERC, LSQUIGLY, RSQUIGLY, ________,  ________,
    ________,TICK3    ,  ________,  ________,  ________,

                                    ________,________,
                                             ________,
                           ________,_XXXXXX_,________,


                  ________, ________, ________, ________, ________, ________, NUMLOCK,
                  ________,TIL_SLASH,  KC_PIPE,  KC_PLUS,  KC_AMPR, ________, CAPLOCK,
                             EQRIGHT,  KC_DQUO, KC_EQUAL, KC_QUOTE,KC_SCOLON, ________,
                  ________, KC_M, BK_SLASH,  ASTERSK,   KC_DOT, KC_SLASH, ________,
                  ________,________ ,________,TILD3,________,
                                                              ________,________,
                                                                       ________,
                                                     ________,________,_XXXXXX_),

  //**************************MOUSE MOVEMENT LAYER**************************
  [_MOUSE] = LAYOUT_ergodox(UP_ENTER_RESET,________,________,________,________,________,MODRESET,
                    RESET,KC_SECRET_5,________,KC_MS_UP,KC_SECRET_4,KC_MS_WH_UP,________,
                    ________,________,KC_MS_LEFT,KC_MS_DOWN,KC_MS_RIGHT,KC_MS_WH_DOWN,
                    KC_SECRET_5,KC_SECRET_4,KC_SECRET_3,_XXXXXX_,KC_SECRET_2,KC_SECRET_1,_XXXXXX_,
                    ________,________,HYPR(KC_F15),KC_MS_WH_LEFT,KC_MS_WH_RIGHT,

                                                       ________,________,
                                                                ________,
                                          KC_MS_BTN1,KC_MS_BTN2,________,


                    ________,________,________,________,________,________,________,
                    ________,________,________,KC_UP,________,KC_MEDIA_PLAY_PAUSE,________,
                    ________,KC_LEFT,KC_DOWN,KC_RIGHT,_XXXXXX_,________,
                    ________,KC_MEDIA_NEXT_TRACK,KC_AUDIO_VOL_UP,KC_AUDIO_VOL_DOWN,KC_MUTE,________,________,
                    KC_MS_WH_UP,KC_MS_WH_DOWN,________,________,________,
                    ________,________,
                    ________,
                    ________,KC_WWW_BACK,KC_WWW_FORWARD),




  //**************************WINDOWS NAVIGATION LAYER**************************

  [_NAV] = LAYOUT_ergodox(________,________,________,________,________,________,________,
                  ________,________,SNAPLEFT,_XXXXXX_,SNAPRGHT,________,________,
                  ________,KC_WWW_BACK,PREVTAB,________,NEXTTAB,SNAPUP,
                  ________,________,WORKLEFT,________,WORKRIGHT,SNAPDOWN,________,
                  ________,________,________,________,________,

                  ________,________,
                           ________,
         ________,________,________,


         ________,________,________,________,________,________,________,
         ________,________,SNAPUP  ,KC_UP   ,SNAPDOWN,________,________,
                  ________,KC_LEFT ,KC_DOWN ,KC_RIGHT,________,________,
         ________,________,________,________,________,________,________,
         ________,________,________,________,________,


         ________,________,
         ________,
         ________,________,________),

  //****************************NUMPAD LAYER****************************
  [_NUMPAD] = LAYOUT_ergodox(________,________,________,________,________,________,________,
                     ________,________,________,________,________,________,________,
                     ________,KC_DOT  ,KC_SPACE,_XXXXXX_, KC_ESC ,________,
                     ________,DBMS_OUT,________,________,________,________,________,
                     ________,________,________,________,________,

                     ________,________,
                     ________,
                     KC_PLUS,KC_MINUS,________,

                     BL_TOGG ,BL_STEP ,________,________,________,________,________,
                     ________,________,KC_7    ,KC_8    ,KC_9    ,________,________,
                              ________,KC_4    ,KC_5    ,KC_6    ,________,________,
                     ________,KC_DOT,  KC_1    ,KC_2    ,KC_3    ,________,________,
                                       KC_0    ,KC_DOT ,  KC_DOT   ,________,________,

                                       ________,________,
                                       ________,
                                       ________,________,KC_0),

  //****************************APP SWITCH LAYER****************************
  [_APPSWITCH] = LAYOUT_ergodox(________,________,________,________,________,________,________,
                        ________,________   ,  ________ , ________  ,________   ,________,________,
                        ________,APP_5,APP_6,APP_7,APP_8,________,
                        ________,DBMS_OUT,________,________,________,________,________,
                        ________,________,________,________,________,

                                                                  ________,________,
                                                                           ________,
                                                         KC_PLUS,________,________,

                     ________,________,________,________,________,________,________,
                     ________,________,APP_3   ,________,APP_4   ,________,________,
                              ________,APP_1   ,_XXXXXX_,APP_2   ,________,________,
                     ________,________,________,________,________,________,________,
                                       ________,________,________,________,________,

                    ________,________,
                    ________,
                    ________,________,________),


  [_ONESHOT] = LAYOUT_ergodox(  UP_ENTER_RESET , ________, ________, ________, ________, ________, ________,
                        ________, ________, ________, KC_UP   , ________, ________, ________,
                        ________, ________, KC_LEFT , KC_DOWN , KC_RIGHT, ________,
                        MAGIC_TOGGLE_NKRO, ________, ________, ________, ________, ________, ________,
                        ________, ________, ________, ________, ________,

                        ________, ________,
                        ________,
                        ________, ________, ________,

                        ________, ________, ________, ________, ________, ________, ________,
                        ________, ________, KC_7, KC_8, KC_9, KC_PLUS, ________,
                                  ________, KC_4, KC_5, KC_6, KC_EQUAL, ________,
                        ________, ________, KC_1, KC_2, KC_3, KC_ASTR, ________,
                        ________, ________, KC_0, ________, ________,

                        ________, ________,
                        ________,
                        ________, ________, ________),
  //****************************TEXT/INTELLIJ NAVIGATION LAYER****************************
  [_TEXTNAV] = LAYOUT_ergodox(________,________,________,________,________,________,________,
                      ________,MEH(KC_Q),LSFT(KC_ESCAPE),MEH(KC_D),MEH(KC_2),LALT(LSFT(KC_UP)),________,
                      ________,________,LCTL(KC_LEFT),LCTL(KC_B),LCTL(KC_RIGHT),LALT(LSFT(KC_DOWN)),
                      ________,________,________,LCTL(LSFT(KC_COMMA)),MEH(KC_DOT),LALT(KC_MS_WH_UP),________,
                      ________,________,________,________,________,

                      ________,________,________,________,________,________,

                      LALT(LSFT(KC_F9)),________,________,________,________,________,________,________,MEH(KC_5),LALT(LSFT(KC_Z)),
                      ________,LALT(KC_Z),________,________,________,LCTL(LSFT(KC_LEFT)),LALT(LCTL(KC_S)),LCTL(LSFT(KC_RIGHT)),
                      LCTL(LSFT(KC_COMMA)),________,________,________,________,________,________,________,________,________,
                      ________,________,________,________,________,________,________,________,________,_XXXXXX_),
  [_QWERTY_KIDS] = LAYOUT_ergodox(

      KC_NO ,   KC_NO  , KC_NO ,     KC_NO ,   KC_NO ,      KC_NO ,     KC_NO ,
      KC_NO ,   KC_Q   , KC_W,     KC_E, KC_R,      KC_T,   KC_NO ,
      KC_NO ,   KC_A   , KC_S,  KC_D,   KC_F,       KC_G ,
      KC_NO ,   KC_Z   ,   KC_X,   KC_C,    KC_V,      KC_B,   KC_NO ,
    KC_MINUS, KC_GRAVE, KC_DELETE,   KC_LEFT, KC_RIGHT,

                                                KC_NO ,    TT(_QWERTY_KIDS) ,
                                                            KC_NO  ,
                                    KC_LSHIFT, KC_BSPACE,    KC_NO    ,

                   KC_NO ,      KC_NO ,      KC_NO ,      KC_NO ,      KC_NO ,      KC_NO ,   KC_NO ,
                  KC_NO  ,    KC_Y,      KC_U, KC_I,     KC_O,      KC_P,    KC_NO ,
                             KC_H,   KC_J,     KC_K,    KC_L,    KC_SCOLON , KC_NO,
               KC_NO ,     KC_N,    KC_M,   KC_COMMA ,   KC_DOT ,  KC_SLASH,   KC_NO ,
                                       KC_UP,  KC_DOWN,   KC_DELETE,    KC_TILD,    KC_UNDS,

    KC_NO ,    KC_NO ,
         KC_NO,
  KC_NO, KC_ENTER, KC_SPACE),

  [_STREET_FIGHTER] = LAYOUT_ergodox(

      KC_NO ,   KC_NO  , KC_NO ,     KC_NO ,   KC_NO ,      KC_NO ,     KC_NO ,
      KC_NO ,   KC_NO   , DIE_1000X_LEFT,     KC_UP, DIE_1000X_RIGHT,      KC_NO,   KC_NO ,
      KC_NO ,   KC_NO   , KC_LEFT,  KC_DOWN,   KC_RIGHT,       KC_NO ,
      KC_NO ,   KC_NO   ,   KC_NO,   KC_NO,    KC_NO,      KC_NO,   KC_NO ,
    KC_NO, KC_NO, KC_NO,   KC_NO, KC_NO,

                                                ________ ,    ________ ,
                                                            ________  ,
                                    ________, ________,    ________    ,

                   KC_NO,  KC_NO ,      KC_NO ,      KC_NO , KC_NO ,   KC_NO , KC_NO ,
                  KC_NO  , KC_NO,      KC_G, KC_H,     KC_J,      KC_NO,    KC_NO ,
                             KC_NO,   KC_B,     KC_N,    KC_M,    KC_K , KC_NO,
               KC_NO ,     KC_NO,    KC_NO,   KC_NO ,   KC_NO ,  KC_NO,   KC_NO ,
                                       KC_NO,  KC_NO,   KC_NO,    KC_NO,    KC_NO,

    TT(_STREET_FIGHTER) ,    ________ ,
         ________,
  ________, ________, ________),


  //************************Windows navigation to directories*************************
  [_DIRNAV] = LAYOUT_ergodox(
         ________,________,________,________,________,________,________,
         ________,________,________,________,________,________,________,
         ________,________,KC_A,________,________,________,
         ________,________,________,________,________,________,________,
         ________,________,________,________,________,

                  ________,________,
                           ________,
         ________,________,________,


         ________,________,________,________,________,________,________,
         ________,________,________,________,________,________,________,
                  ________,________,_______,________,________,________,
         ________,________,________,________,________,________,________,
         ________,________,________,________,________,


         ________,________,
         ________,
         ________,________,________),


  [_TEXT_MACROS] = LAYOUT_ergodox(
         ________,________,________,________,________,________,________,
         ________,________,________,________,________,________,________,
         ________,________,KC_A,________,________,________,
         ________,________,________,________,________,________,________,
         ________,________,________,________,________,

                  ________,________,
                           ________,
         ________,________,________,


         ________,________,________,________,________,________,________,
         ________,________,________,________,________,________,________,
                  ________,________,_______,________,________,________,
         ________,________,________,________,________,________,________,
         ________,________,________,________,________,


         ________,________,
         ________,
         ________,________,________)


/* FOR FORMATTING FUTURE LAYERS
   NO KEY CODES SHOULD BE MORE THAN 8 CHARACTERS
   GOES LEFT HAND THEN RIGHT HAND
  [_DIRNAV] = LAYOUT_ergodox(
         ________,________,________,________,________,________,________,
         ________,________,________,________,________,________,________,
         ________,________,________,________,________,________,
         ________,________,________,________,________,________,________,
         ________,________,________,________,________,

                  ________,________,
                           ________,
         ________,________,________,


         ________,________,________,________,________,________,________,
         ________,________,________,________,________,________,________,
                  ________,________,________,________,________,________,
         ________,________,________,________,________,________,________,
         ________,________,________,________,________,


         ________,________,
         ________,
         ________,________,________), */




};

void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_on();
    ergodox_led_all_on();

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
   //    _delay_ms(45);

    switch (layer)
    {
    case _SYMBOLS:
      ergodox_right_led_1_on();
      break;
    case _MOUSE:
      ergodox_right_led_2_on();
      break;
    case _NUMPAD:
      ergodox_right_led_3_on();
      break;
    case _NAV:
      ergodox_right_led_1_on();
      ergodox_right_led_2_on();
      break;
    case _MACROS:
      //layer unused right now
      break;
    case _FUNCTION:
      //layer unused right nowex
      break;
    case _APPSWITCH:
      ergodox_right_led_2_on();
      ergodox_right_led_3_on();
      break;
    case _ONESHOT:
      ergodox_right_led_1_on();
      ergodox_right_led_2_on();
      ergodox_right_led_3_on();
      break;
    case _TEXTNAV:
      ergodox_right_led_1_on();
      ergodox_right_led_3_on();
      break;
    case _QWERTY_KIDS:
      ergodox_right_led_1_on();
      ergodox_right_led_2_on();
      ergodox_right_led_3_on();
      break;
    case _STREET_FIGHTER:
      ergodox_right_led_2_on();
      ergodox_right_led_3_on();
    default:
      break;
    }
};
