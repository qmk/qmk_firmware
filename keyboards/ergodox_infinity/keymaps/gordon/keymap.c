#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"
#include "process_keycode/process_tap_dance.h"
#include "gordon.h"

#include "keymap_german.h"

#include "keymap_nordic.h"


#define TLSLSH   M(TIL_SLASH)
#define F1_F13   TD(F1F13)
#define F2_F14   TD(F2F14)
#define F5_F15   TD(F5F15)
#define F4_ALTF4 TD(ALTF4)
#define END_ESC  TD(ENDESC)
#define SHF6_AF7 TD(F6F7)
#define F12_RUN  TD(F12ETAPS)
#define COMMA_TD TD(COMMA)

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD,
};

//Tap dance enums
enum {
  F12TAP = 0,
  F12ETAPS,
  CALCCOMP,
  REFRESH, //send R, or Control+R if double tapped.
  ENDESC,
  XESC, //'quad function'. x, control, escape, alt
  ALY2, //'quad function': a, Hyper, ctrl+a, layer 2
  PRLOCK,
  F6F7, // Shift F6 or Alt F7
  TABCOMBO,
  FCTRL,
  F3D,
  ALTF4,
  COMMA,
  AT,
  HTAB,
  F1F13,
  F2F14,
  F5F15
};



// Custom tapping terms for each key.
// Requires changes to action_taping.c
/* uint16_t get_tapping_term(keyevent_t* event) {
    uint16_t keycode = keymap_key_to_keycode(layer_switch_get_layer(event->key), event->key);
    if (keycode == LT(3,KC_E) ) {
        return TAPPING_TERM + 50;
    }
    return TAPPING_TERM;
} */

            
// Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  // simple tap dance
  [F12ETAPS] = ACTION_TAP_DANCE_DOUBLE(KC_F12,LSFT(LCTL(KC_F10))),  
  [REFRESH] = ACTION_TAP_DANCE_DOUBLE(KC_R,LCTL(KC_R)),
  [ENDESC] = ACTION_TAP_DANCE_DOUBLE(KC_END, KC_ESC),
  [CALCCOMP] = ACTION_TAP_DANCE_DOUBLE(KC_CALCULATOR, KC_MY_COMPUTER),
  [ALTF4] = ACTION_TAP_DANCE_DOUBLE(KC_F4,LALT(KC_F4)),
  [F6F7] = ACTION_TAP_DANCE_DOUBLE(LSFT(KC_F6), LALT(KC_F7)),
  [F1F13] = ACTION_TAP_DANCE_DOUBLE(KC_F1, KC_F13),
  [F2F14] = ACTION_TAP_DANCE_DOUBLE(KC_F2, KC_F14),
  [F5F15] = ACTION_TAP_DANCE_DOUBLE(KC_F5, KC_F15),
  [TABCOMBO] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tab_finished, tab_reset),
  [F3D] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, bt_finished, bt_reset),
  [COMMA] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, comma_finished, comma_reset),
  [HTAB] = ACTION_TAP_DANCE_FN_ADVANCED(NULL,h_finished, h_reset)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


//**************************FIRST LAYER - LAYER ZERO ************************************** 
  [_QWERTY] = KEYMAP(

    SHF6_AF7,   F1_F13,    F2_F14,   TD(F3D), F4_ALTF4,    F5_F15,   KC_F11,
    ________,     KC_Q,  CTR_SH_W,     NAV_E, CTR_AL_R,      KC_T, PRINTSCR,
      KC_TAB,     KC_A,     MEH_S,  NUMPAD_D,   CTRL_F,     WIN_G,
    ALT_SHFT,   CTRL_Z,   HYPER_X,   MOUSE_C,    ALT_V,      KC_B, TT(_MOUSE),
    KC_MINUS, KC_GRAVE, KC_DELETE,   KC_LEFT, KC_RIGHT,
                                    
                                              KC_INSERT,  KC_DELETE, 
                                                           ALT_HOME,
                                    KC_LSHIFT, SYMB_BSP,    END_ESC,

                 F12_RUN,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10, TD(CALCCOMP),
                ________,     KC_Y,     KC_U,     KC_I,     KC_O,      KC_P,  ________,
                             WIN_H,   CTRL_J,     KC_K,    MEH_L,  COL_MOUS,  ________,
                 KC_LEAD,     KC_N,    ALT_M, COMMA_TD, HYPE_DOT,  KC_SLASH, TD(TABCOMBO),
                                       KC_UP,  KC_DOWN,   KC_ESC,    KC_TILD,    KC_UNDS,

  KC_ESCAPE,  KC_DELETE,
         ALT_T(KC_PGUP),
  RCTL_T(KC_PGDOWN), LT(_NAV,KC_ENTER), SPAC_SYM),


  //**************************SYMBOLS LAYER**************************
  [_SYMBOLS] = KEYMAP(
    ________, ________, ________, ________, ________, ________,  ________,
    ________,   TLSLSH,    KC_AT,  KC_LCBR,  KC_RCBR,  KC_CIRC,  ________,
    ________,  KC_EXLM,  KC_PIPE,  KC_LPRN,  KC_RPRN, M(DEREF),
    ________,KC_DOLLAR,  KC_PERC, LSQUIGLY, RSQUIGLY, ________,  ________,
    ________,  M(TICK3),  ________,  ________,  ________,  

                                    ________,________,
                                             ________,
                           ________,________,________,


                  ________, ________, ________, ________, ________, ________, NUMLOCK,
                  ________,   TLSLSH,  KC_PIPE,  KC_PLUS,  KC_AMPR, ________, CAPLOCK,
                          M(EQRIGHT),  KC_DQUO, KC_EQUAL, KC_QUOTE,KC_SCOLON, ________,
                  ________,  KC_PIPE, BK_SLASH,  ASTERSK,   KC_DOT, KC_SLASH, ________,
                  ________,________,________,M(TILD3),________,
                                                              ________,________,
                                                                       ________,
                                                     ________,________,________),
  
  //**************************MOUSE MOVEMENT LAYER**************************
  [_MOUSE] = KEYMAP(RESET,________,________,________,________,________,________,
                    RESET,________,________,KC_MS_UP,________,KC_MS_WH_UP,CALTDEL,
                    ________,________,KC_MS_LEFT,KC_MS_DOWN,KC_MS_RIGHT,KC_MS_WH_DOWN,
                    KC_SECRET_1,________,HYPR(KC_F13),________,HYPR(KC_F14),KC_SECRET_2,________,
                    ________,________,HYPR(KC_F15),KC_MS_WH_LEFT,KC_MS_WH_RIGHT,
                    
                                                       ________,________,
                                                                ________,
                                          KC_MS_BTN1,KC_MS_BTN2,________,
                                          
                                         
                    ________,________,________,________,________,________,________,
                    KC_MS_WH_UP,________,________,KC_UP,________,________,________,
                    ________,KC_LEFT,KC_DOWN,KC_RIGHT,________,________,
                    KC_MS_WH_DOWN,________,KC_PGUP,KC_PGDOWN,KC_MEDIA_NEXT_TRACK,________,________,
                    KC_AUDIO_VOL_UP,KC_AUDIO_VOL_DOWN,KC_AUDIO_MUTE,KC_MEDIA_PLAY_PAUSE,________,
                    ________,________,
                    ________,
                    ________,________,KC_WWW_BACK),




  //**************************WINDOWS NAVIGATION LAYER**************************

  [_NAV] = KEYMAP(________,________,________,________,________,________,________,
                  ________,________,SNAPLEFT,________,SNAPRGHT,LALT(KC_LEFT),________,
                  ________,LCTL(KC_W),PREVTAB,LGUI(KC_D),NEXTTAB,________,
                  ________,________,WORKLEFT,________,WORKRIGHT,________,________,
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
  [_NUMPAD] = KEYMAP(________,________,________,________,________,________,________,
                     ________,________,________,________,________,________,________,
                     ________,________,________,________,________,________,
                     ________,________,________,________,________,________,________,
                     ________,________,________,________,________,
                     
                     ________,________,
                     ________,
                     ________,________,________,
                     
                     BL_TOGG ,BL_STEP ,________,________,________,________,________,
                     ________,________,KC_7    ,KC_8    ,KC_9    ,________,________,
                              ________,KC_4    ,KC_5    ,KC_6    ,________,________,
                     ________,________,KC_1    ,KC_2    ,KC_3    ,________,________,
                                       KC_0    ,KC_0 ,  KC_DOT   ,________,________,
                                       
                                       ________,________,
                                       ________,
                                       ________,________,KC_0),
  //****************************TEXT/INTELLIJ NAVIGATION LAYER****************************
  [_TEXTNAV] = KEYMAP(________,________,________,________,________,________,________,
                      ________,MEH(KC_Q),LSFT(KC_ESCAPE),MEH(KC_D),MEH(KC_2),LALT(LSFT(KC_UP)),________,
                      ________,LALT(KC_F7),LCTL(KC_LEFT),LCTL(KC_B),LCTL(KC_RIGHT),LALT(LSFT(KC_DOWN)),
                      ________,________,________,LCTL(LSFT(KC_COMMA)),MEH(KC_DOT),LALT(KC_MS_WH_UP),________,________,________,________,________,________,________,________,________,________,LCTL(KC_DELETE),________,LALT(LSFT(KC_F9)),________,________,________,________,________,________,________,MEH(KC_5),LALT(LSFT(KC_Z)),________,LALT(KC_Z),________,________,________,LCTL(LSFT(KC_LEFT)),LALT(LCTL(KC_S)),LCTL(LSFT(KC_RIGHT)),LCTL(LSFT(KC_COMMA)),________,________,________,________,________,________,________,________,________,________,________,________,________,________,________,________,________,________,________)
};

const uint16_t PROGMEM fn_actions[] = {
  [1] = ACTION_LAYER_TAP_TOGGLE(1)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
      switch(id) {
        case INFOQM: {
          if (record->event.pressed) {
            SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
          }
          break;
        }

        case TIL_SLASH: {
          if (record->event.pressed) {
            SEND_STRING ("~/.");
          }
          break;
        }

        case DEREF: {
          if (record->event.pressed) {
            SEND_STRING ("->");
          }
          break;
        }
        
        case EQRIGHT: {
          if (record->event.pressed) {
            SEND_STRING ("=>");
          }
          break;
        }

        case TICK3: {
          if (record->event.pressed) {
            SEND_STRING ("```");
          }
          break;
        }

        case TILD3: {
          if (record->event.pressed) {
            SEND_STRING ("~~~");
          }
          break;
        }

        case ALTTAB_START: {
          register_code(KC_LALT);
          layer_on(8);
        }

        case ALTTAB_END: {
          unregister_code(KC_LALT);
          layer_off(8);
        }



      }
      return MACRO_NONE;
};

void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_on();
    ergodox_led_all_on();

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
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
