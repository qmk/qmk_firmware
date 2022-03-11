#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"
#include "process_keycode/process_tap_dance.h"
#include "gordon.h"

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD
};

enum combos {
  DF_ESCAPE,
  SDF_WINNAV_LAYER,
  JKL_WINNAV_2,
  XCV_NUMPAD
};


const uint16_t PROGMEM df_esc_combo[] = {NUMPAD_D, CTRL_F, COMBO_END}; //Send escape by tapping D&F
const uint16_t PROGMEM sdf_combo[] = {MEH_S, NUMPAD_D, CTRL_F, COMBO_END};
const uint16_t PROGMEM jkl_winsnap2_combo[] = {F16_SNAP, F17_SNAP, F18_SNAP, COMBO_END};
const uint16_t PROGMEM xcv_numpad_combo[] = {HYPER_X, MOUSE_C, ALT_V, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [DF_ESCAPE] = COMBO(df_esc_combo, KC_ESCAPE),
  [SDF_WINNAV_LAYER] = COMBO_ACTION(sdf_combo),
  [JKL_WINNAV_2] = COMBO_ACTION(jkl_winsnap2_combo),
  [XCV_NUMPAD] = COMBO_ACTION(xcv_numpad_combo)
};

//Handle advanced keycodes/functions for combos
void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    case SDF_WINNAV_LAYER:
      if (pressed) {
        layer_invert(_WINDOWS_NAV);
      }
      break;
    case JKL_WINNAV_2:
      if (pressed) {
        layer_on(_TEXT_MACROS);
      }
      break;  
    case XCV_NUMPAD:
      if (pressed) {
        layer_invert(_NUMPAD);
      }
      break;
  }
};


//custom tapping terms
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case WINDOW_I: //need a longer tapping term for "I" simply due to typing habits
            return 499;
        default:
            return TAPPING_TERM;
    }
}

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
    F13SNAP  , Q_ESC   ,  CTR_SH_W,     NAV_E, ALT_SH_R,      KC_T, PRINTSCR,
    KC_TAB  , KC_A    ,     MEH_S,  NUMPAD_D,   CTRL_F,     WIN_G,
    OSL(_ONESHOT), CTRL_Z  ,   HYPER_X,   MOUSE_C,    ALT_V,      KC_B, KC_LEAD,
    KC_MINUS, KC_GRAVE, KC_DELETE,   KC_LEFT, KC_RIGHT,

                                              LSFT(KC_INSERT),  TT(_WINDOWS_NAV),
                                                          ________ ,
                                    KC_LSHIFT, SYMB_BSP,  LT(_WINDOWS_NAV, KC_INSERT)   ,

                 F12_RUN,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10, KC_CALCULATOR,
                CALTDEL ,    KC_Y,      KC_U,     WINDOW_I,     KC_O,      KC_P,  MODRESET,
                             WIN_H,   CTRL_J, APP_SW_K,    MEH_L,  COL_MOUS, END_HOME,
             OSL(_ONESHOT),     KC_N,  KC_M, COMMA_TD, HYPE_DOT,  KC_SLASH, TT(_QWERTY_KIDS),
                                       KC_UP,  KC_DOWN,KC_DELETE,    KC_TILD,    KC_UNDS,

  TT(_STREET_FIGHTER),  ________,
         KC_PGUP,
  KC_PGDOWN, LT(_NAV,KC_ENTER), SPAC_TXT),


  //**************************SYMBOLS LAYER**************************
  [_SYMBOLS] = LAYOUT_ergodox(
    RESET, ________, ________, ________, ________, ________,  ________,
    ________, DEREF   ,    KC_AT,  KC_LCBR,  KC_RCBR,  KC_CIRC,  ________,
    ________,  KC_EXLM,  KC_HASH,  KC_LPRN,  KC_RPRN,  KC_MINUS,
    ________,KC_DOLLAR,  KC_PERC, KC_LBRACKET, KC_RBRACKET, KC_GRAVE,  TIL_SLASH,
    COMMA_TD,TICK3    ,  _XXXXXX_,  KC_LT,  KC_GT,

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
  // LAYER #2
  [_MOUSE] = LAYOUT_ergodox(UP_ENTER_RESET,________,________,________,________,________,MODRESET,
                    RESET,________,________,KC_MS_UP,KC_SECRET_4,KC_MS_WH_UP,________,
                    ________,________,KC_MS_LEFT,KC_MS_DOWN,KC_MS_RIGHT,KC_MS_WH_DOWN,
                    ________,KC_SECRET_4,KC_SECRET_3,_XXXXXX_,KC_SECRET_2,KC_SECRET_1,_XXXXXX_,
                    ________,________,HYPR(KC_F15),KC_MS_WH_LEFT,KC_MS_WH_RIGHT,

                                                       ________,________,
                                                                ________,
                                          KC_MS_BTN1,KC_MS_BTN2,________,


                    ________,________,________,________,________,________,RESET,
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
                  ________,________,________,KC_A,KC_B,

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
                      ________,________,KC_HOME,________,KC_END,________,________,
                      ________,________,LCTL(KC_LEFT),________,LCTL(KC_RIGHT),LALT(LSFT(KC_DOWN)),
                      ________,________,LCTL(KC_HOME),________,LCTL(KC_END),LCTL(KC_END),________,
                      ________,________,________,________,________,

                      ________,________,________,________,________,________,

                      ________,________,________,________,________,________,________,________,________,LSFT(KC_HOME),
                      ________,LSFT(KC_END),________,________,________,LCTL(LSFT(KC_LEFT)),________,LCTL(LSFT(KC_RIGHT)),
                      ________,________,________,________,LCTL(LSFT(KC_HOME)),________,LCTL(LSFT(KC_END)),________,________,________,
                      ________,________,________,________,________,________,________,________,________,_XXXXXX_),
  //LAYER #8
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

  ///LAYER #9
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


  //************************ ADVANCED WINDOWS SNAPPING *************************
  //LAYER #10
  [_WINDOWS_NAV] = LAYOUT_ergodox(
         ________,________,________,________,________,________,________,
         ________,________,________,________,________,________,________,
         ________,________,________,________,________,________,
         ________,________,________,________,________,________,________,
         ________,________,________,________,________,

                  ________,________,
                           ________,
         ________,________,________,


         ________,________,________,________,________,________,________,
         ________,________,F13_SNAP,F14_SNAP,F15_SNAP,________,________,
                  ________,F16_SNAP,F17_SNAP,F18_SNAP,________,________,
         ________,________,F19_SNAP,F20_SNAP,F21_SNAP,________,________,
         ________,________,________,________,________,


         ________,________,
         ________,
         ________,________,________),


  [_TEXT_MACROS] = LAYOUT_ergodox(
         ________,________,________,________,________,________,________,
         ________,________,________,________,________,________,________,
         ________,________,________,TO(0),________,________,
         ________,________,________,________,________,________,________,
         ________,________,________,________,________,

                  ________,________,
                           ________,
         ________,________,________,


         ________,________,________,________,________,________,________,
         ________,________,LCTL(LALT(KC_F13)),LCTL(LALT(KC_F14)),LCTL(LALT(KC_F15)),________,________,
                  ________,LCTL(LALT(KC_F16)),LCTL(LALT(KC_F17)),LCTL(LALT(KC_F18)),________,________,
         ________,________,LCTL(LALT(KC_F19)),LCTL(LALT(KC_F20)),LCTL(LALT(KC_F21)),________,________,
         ________,________,________,________,________,


         ________,________,
         ________,
         ________,________,________),

           [_EXTRA1] = LAYOUT_ergodox(
         ________,________,________,________,________,________,________,
         ________,________,________,________,________,________,________,
         ________,________,________,TO(0),________,________,
         ________,________,________,________,________,________,________,
         ________,________,________,________,________,

                  ________,________,
                           ________,
         ________,________,________,


         ________,________,________,________,________,________,________,
         ________,________,LSFT(LALT(KC_F13)),LSFT(LALT(KC_F14)),LSFT(LALT(KC_F15)),________,________,
                  ________,LSFT(LALT(KC_F16)),LSFT(LALT(KC_F17)),LSFT(LALT(KC_F18)),________,________,
         ________,________,LSFT(LALT(KC_F19)),LSFT(LALT(KC_F20)),LSFT(LALT(KC_F21)),________,________,
         ________,________,________,________,________,


         ________,________,
         ________,
         ________,________,________),
          [_EXTRA2] = LAYOUT_ergodox(
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

// void ergodox_right_led_dan1_on(void){
//     user_data_keyboard.led_on |= (1u << 3);
//     visualizer_set_user_data(&user_data_keyboard);
// }

// bool is_alt_tab_active = false; // ADD this near the begining of keymap.c
// uint16_t alt_tab_timer = 0;     // we will be using them soon.


void matrix_scan_user(void) {



    uint8_t layer = biton32(layer_state);


    // ergodox_board_led_on();

    // ergodox_board_led_off();
    // ergodox_right_led_1_off();
    // ergodox_right_led_2_off();
    // ergodox_right_led_3_off();

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    
   //    _delay_ms(45);

    // if (is_alt_tab_active) {
    //   if (timer_elapsed(alt_tab_timer) > 1000) {
    //     unregister_code(KC_LALT);
    //     is_alt_tab_active = false;
    //   }
    // }
    




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
      ergodox_right_led_2_on(); 
      ergodox_right_led_2_on(); 
      break;
    case _STREET_FIGHTER:
      ergodox_right_led_2_on();
      ergodox_right_led_3_on();
      break;
    case _WINDOWS_NAV:
      ergodox_right_led_3_on();
      // ergodox_right_led_4_on();      
      break;
    case _TEXT_MACROS:
      ergodox_right_led_1_on();  
      break;
    case _EXTRA1:
      ergodox_right_led_2_on();  
      break;
    case _EXTRA2:
      ergodox_right_led_3_on(); 
      break;  
      // ergodox_right_led_dan1_on();
    default:
      break;
    }
};
