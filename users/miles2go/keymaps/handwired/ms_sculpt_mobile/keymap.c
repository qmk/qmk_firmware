//placeholder until the new keymaps tree is built
//#include QMK_KEYBOARD_H


#include "virtser.h"
#include <print.h>
#include "milestogo.h"


#define LAYOUT_local LAYOUT_mobile_XUW
#define LAYOUT LAYOUT_mobile_XUW


#ifndef USERSPACE_ACTIVE
enum layer_keycodes {
    QWR = SAFE_RANGE,
    CDH,
    SYM,
    MOV,
    NUM,
    TRAN
};

enum layer_names {
_QWR,
_CDH,
_SYM,
_MOV,
_TRAN
};

#endif

// Shorter spacing
#define XXXX  KC_NO
#define ____  KC_TRNS

// Custom macros

/* Fn Keys */
#define TT_SYM MO(_SYM)
#define TT_NUM MO(_NUM)
#define SSFT ACTION_MODS_ONESHOT(MOD_LSFT)
#define SSYM LT(_SYM, KC_SPC)
#define MVTAB LT(_MOV,KC_TAB)
#define BKMV TT(_MOV)
#define MV2 LT(_MOV, KC_2)
#define MV3 LT(_MOV, KC_3)
#define MV4 LT(_MOV, KC_4)
#define MV8 LT(_MOV, KC_8)
#define MV9 LT(_MOV, KC_9)
#define MV0 LT(_MOV, KC_0)



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*  QWERTY
*
* |ESC | F1 | F2 | F3 | F4 | F5 | F6 | f7 | F8 | F9 | F10| F11| F12|Vol-|Vol+|_CDH|
*  -------------------------------------------------------------------------------'
* | ESC |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 |  0 |  - |  = |Bakspace| Del|
* ---------------------------------------------------------------------------
* | tab  |  q |  w |  e |  r |  t |  y |  u |  i |  o |  p |  [ |  ] |  \    |    |
*  -------------------------------------------------------------------------------'
* |Bak/Mov|  a |  s |  d |  f |  g |  h |  j |  k |  l |  ; |  ' | enter     |PgUp|
* --------------------------------------------------------------------------------
* |Lsft    |  z |  x |  c |  v |  b |  n |  m |  , |  . |  / |      Rsft| Up| PgDn|
* ---------------------------------------------------------------------------------
* |Lctl   |Lgui  |Lalt |       Space/Sym      | GUI |  Sym |  Rctl |Left|Down|Rght|
* ---------------------------------------------------------------------------------
*/

[_QWERTY] = LAYOUT_local(
KC_ESC,   KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8,   KC_F9, KC_F10,    KC_F11,   KC_F12, KC_VOLD, KC_VOLU, TG(_CDH),
KC_GRAVE, KC_1, KC_2, KC_3 ,KC_4, KC_5, KC_6, KC_7, KC_8,   KC_9, KC_0,     KC_MINS, KC_EQL, KC_BSPC, KC_DEL,
KC_TAB,   KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I,   KC_O, KC_P,    KC_LBRC,  KC_RBRC,KC_BSLS,
BKMV,    KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K,   KC_L, KC_SCLN, KC_QUOT,  KC_ENT, KC_PGUP,
KC_LSFT,  KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM,KC_DOT,KC_SLSH,KC_RSFT,  KC_UP,  KC_PGDN,
KC_LCTL,  KC_LGUI, KC_LALT, KC_SPC, KC_RGUI, TT_SYM,KC_CDH, KC_LEFT, KC_DOWN, KC_RIGHT
),


[_CDH] = LAYOUT_local(
____,    ____, ____, ____, ____, ____,   ____, ____, ____,   ____,   ____,    ____,     ____,   ____,    ____,    ____,
KC_GRAVE, KC_1, KC_2, KC_3 ,KC_4, KC_5,   KC_6, KC_7, KC_8,   KC_9,   KC_0,    KC_MINUS, KC_EQL, KC_BSPC, KC_DEL,
KC_TAB,  KC_Q, KC_W, KC_F, KC_P, KC_B,   KC_J, KC_L, KC_U,   KC_Y,   KC_SCLN, ____,    ____,    ____,
KC_LCTL, KC_A, KC_R, KC_S, KC_T, KC_G,   KC_M, KC_N, KC_E,   KC_I,   KC_O,    KC_QUOT, KC_ENT,  KC_2,
KC_LSFT, KC_Z, KC_X, KC_C, DHPASTE,KC_V, KC_K, KC_H, KC_COMM,KC_DOT, KC_SLSH, KC_RSFT, ____,    KC_1,
TG(_MOV),     ____, ____ , ____, ____, ____, KC_QWERTY, ____, ____,   ____
),

/*  SYMBOL layer, several to chose from
*/

[_SYM] = LAYOUT_wrapper(
____,     ____, ____, ____, ____, ____, ____, ____, ____,   ____, ____,    ____,     ____,   ____,    ____,     ____,
____,     ____, ____, ____, ____, ____, ____, ____, ____,   ____, ____,    ____,     ____,   ____,    ____,
____,  _________________EXCEL_L1__________________, _________________EXCEL_R1__________________,  ____,   ____,  ____,
____,  _________________EXCEL_L2__________________, _________________EXCEL_R2__________________,  KC_GRV, ____,  ____,
____,  _________________EXCEL_L3__________________, _________________EXCEL_R3__________________,  B_SAVE, ____,  ____,
____,     ____, ____, ____, ____, ____, ____, ____, ____,   ____
),

#ifndef USE_BABLPASTE

[_MOV] = LAYOUT_local(
____,     XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX,   XXXX, XXXX,    XXXX,     XXXX,   XXXX,    XXXX,   ____  ,
____,     XXXX, XXXX, XXXX, XXXX, XXXX,      XXXX, XXXX, XXXX, XXXX, XXXX,     XXXX, XXXX,   XXXX, XXXX,
____,     XXXX, XXXX, XXXX, XXXX, XXXX,      XXXX, XXXX, KC_UP, XXXX, XXXX,    XXXX, XXXX,   XXXX,
____,     XXXX, XXXX, XXXX, XXXX, XXXX,      XXXX, KC_LEFT, KC_DOWN, KC_RIGHT,XXXX,   XXXX, XXXX,   XXXX,
____,     XXXX, XXXX, XXXX, XXXX, XXXX,      XXXX, XXXX, XXXX, XXXX, XXXX,     XXXX, XXXX,   XXXX,
____,     XXXX, XXXX, XXXX, XXXX, XXXX,      XXXX, XXXX, XXXX, XXXX
)

#else
/* MOVE babble version version

* |ESC   | MAC|Read|Linx| VI |    |    |    |    |    |    |    |   |    |   |    |
*  -------------------------------------------------------------------------------'
* |      |                                                 |  - | = |Bakspace| Del|
* ---------------------------------------------------------------------------
* | tab  |                                                 |  [ |  ] |  \    |    |
*  -------------------------------------------------------------------------------'
* |Bak/Mov|                                                |  ' |Launch App  |PgUp|
* ---------------------------------------------------------------------------------
* |Lsft    |                                                 |      Rsft| Up| PgDn|
* ---------------------------------------------------------------------------------
* |       |Lgui  |Lalt |   Exit Move Mode     | GUI |  Sym |  Rctl |Left|Down|Rght|
* ---------------------------------------------------------------------------------
*/
/*    ,--------------------------------------------.  ,--------------------------------------------.
 * 01 | ESC    |FindPrev|  Find  |FindNext| \n cell|  |ParStart|LineStrt|   Up   |  EOL   | ParEnd |
 *    |--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------|
 * 02 | SelA   | Do_DEL | Shift  |   Undo |Hsplit+ |  | WrdLft | Left   | Down   | Right  | WrdRght|
 *    |--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------|
 * 03 |Vspli+  | Cut    | Copy   | Paste  | Paste  |  | WinPrv | Tab--  | NewTab | Tab++  | WinNxt |
 *    `--------------------------------------------'  `--------------------------------------------'
 */

[_MOV] = LAYOUT_wrapper(
  ____,    ____________BABBLE_SWITCH_L________________, ____________BABBLE_SWITCH_R________________,    XXXX,   XXXX,   XXXX,   XXXX,    ____,
  ____,    ____________BABBLE_MOV_LNUM________________, ____________BABBLE_MOV_RNUM________________,    XXXX,   XXXX,   XXXX,   XXXX,
  ____,    ____________BABBLE_MOV_L1__________________, ____________BABBLE_MOV_R1__________________,    XXXX,   XXXX,   XXXX,
  ____,    ____________BABBLE_MOV_L2__________________, ____________BABBLE_MOV_R2__________________,    XXXX, B_RUNAPP, XXXX,
  ____,    ____________BABBLE_MOV_L3__________________, ____________BABBLE_MOV_R2__________________,   XXXX,  XXXX,   XXXX,
  ____,    ____,   ____,  TG(_MOV), XXXX, XXXX, XXXX,  XXXX, XXXX,   XXXX
),
// Move in a direction, deleting as we go, or do opposite of Mov layer action */
/*    ,--------------------------------------------.  ,--------------------------------------------.
 * 01 |  Esc   |        |Replace |MultiSel|PasteVal|  |     .  |LineStrt|   .    |  EOL   |    .   |
 *    |--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------|
 * 02 |        | Do_Mov | Shift  | Redo   |Hsplit- |  | WrdLft | Left   |   .    | Right  | WrdRght|
 *    |--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------|
 * 03 |Vsplit- | Cut    | Copy   | Paste  |Paste   |  |  App-- | ZoomOut| NewWin | ZoomIn | App+   |
 *    `--------------------------------------------'  `--------------------------------------------'
 */ 
[_DMOV] = LAYOUT_wrapper(
  ____,    ____________BABBLE_SWITCH_L________________,  ____________BABBLE_SWITCH_R________________,   XXXX,   XXXX,   XXXX,     ____,
  ____,    ____________BABBLE_MOV_LNUM________________,  ____________BABBLE_MOV_RNUM________________,   XXXX,   XXXX,   XXXX,    XXXX,
  ____,    _________BABBLE_DELMOV_L1__________________ , _________BABBLE_DELMOV_R1__________________ ,  XXXX,   XXXX,   XXXX,
  ____,    _________BABBLE_DELMOV_L2__________________ , _________BABBLE_DELMOV_R2__________________ ,  XXXX,   XXXX,   XXXX,
  ____,    _________BABBLE_DELMOV_L3__________________ , _________BABBLE_DELMOV_R3__________________ ,  XXXX,   XXXX,   XXXX,
  ____,    XXXX,   XXXX,  XXXX, XXXX, XXXX, XXXX, XXXX, XXXX,  XXXX, XXXX
),

#endif // Bablepaste
/*
[_TRAN] = LAYOUT_local(
  ____,     ____, ____, ____, ____, ____, ____, ____, ____,   ____, ____,    ____,     ____,   ____,    ____,     ____,
  ____,     ____, ____, ____, ____, ____,      ____, ____, ____, ____, ____,    ____, ____,   ____, ____,
  ____,     ____, ____, ____, ____, ____,      ____, ____, ____, ____, ____,    ____, ____,   ____,
  ____,     ____, ____, ____, ____, ____,      ____, ____, ____, ____, ____,    ____, ____,   ____,
  ____,     ____, ____, ____, ____, ____,      ____, ____, ____, ____, ____,    ____, ____,   ____,
  ____,     ____, ____, ____, ____, ____,      ____, ____, ____, ____
)
*/
};

#ifndef USERSPACE_ACTIVE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QWR:
            if (record->event.pressed) {
                layer_off(_CDH);
            }
            return false;
            break;

        case CDH:
            if (record->event.pressed) {
                layer_on(_CDH);
            }
            return false;
            break;

        case SYM:
            if (record->event.pressed) {
                layer_on(_SYM);
            } else {
              layer_off(_SYM);
            }
            return false;
            break;

        case SAVE: 
             if (record->event.pressed) {
               SEND_STRING(SS_LCTL("s"));
            }
            return false;
            break;
        /* Colemak mod-dh moves the D key to the qwerty V position
            This hack makes apple-V_position do what I mean */
        case DHPASTE:
            if(get_mods() & MOD_BIT(KC_LGUI) ) {
                if (record->event.pressed) {
                    clear_keyboard_but_mods();
                    register_code(KC_V);
                } else {
                    unregister_code(KC_V);
                }
            } else {
                if (record->event.pressed) {
                    register_code(KC_D);
                } else {
                    unregister_code(KC_D);
                }
            }
            return false;
            break;

        return false;
        break;
    }

    return true;
}
#endif

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  // debug_enable=true;
  //debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}


void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
    #ifdef RGB_DI_PIN
        rgblight_setrgb(RGB_GREEN);
    #endif
    #endif //RGB_matrix  
}

// Runs whenever there is a layer state change.
layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t layer = get_highest_layer(state);
    switch (layer) {
        case 0:
            #ifdef RGBLIGHT_COLOR_LAYER_0
                rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
            #else
                #ifdef RGBLIGHT_ENABLE
                    rgblight_init();
                #endif
            #endif
            break;

        case 1:
            #ifdef RGBLIGHT_COLOR_LAYER_1
                rgblight_setrgb(RGBLIGHT_COLOR_LAYER_1);
            #endif
            break;

        case 2: // symbol
            #ifdef RGBLIGHT_COLOR_LAYER_2
                rgblight_setrgb(RGBLIGHT_COLOR_LAYER_2);
            #endif
            break;

        case 3: // move
            #ifdef RGBLIGHT_COLOR_LAYER_3
                rgblight_setrgb(RGBLIGHT_COLOR_LAYER_3);
            #endif
            #ifdef USE_BABLPASTE
                babble_led_user(); // poke led to update
            #endif  // bablepaste
            break;

        case 4: //delmove ideally we'd turn on a red pixel in addition to the layer indicator. 
            #ifdef RGBLIGHT_COLOR_LAYER_4
                rgblight_setrgb(RGBLIGHT_COLOR_LAYER_4);
            #endif
            break;

        case 5:
            #ifdef RGBLIGHT_COLOR_LAYER_5
                rgblight_setrgb(RGBLIGHT_COLOR_LAYER_5);
            #endif
            break;

        default:
          break;
      }
    #ifdef VIRTSER_ENABLE
      //virtser_send(layer + 48); // ascii 0 is 48
    #endif
  return state;
};

// custom tapping term lengths. 
uint16_t get_tapping_term(uint16_t keycode) {
    switch (keycode) {
        case LT(_MOV, KC_TAB):
            return TAPPING_TERM ;
            break;
        default:
        return TAPPING_TERM;
    }
}



#ifdef VIRTSER_ENABLE
/* listen on serial for commands. Either a set of lower case letters mapped to colors, 
/  or upper case letters that change RGB mode. 
/  special command C takes 3 numbers as arguments, terminated with a newline or comma or excess digits.
Command C takes 3-5octets of RGB settings. Numbers can be terminated with a comma or period. 
3 octets = set all LED, 4th argument specfies specfic LED, 4+5 specify start and stop LEDs.
*/ 

uint8_t ser_rgbByte[18] ; //ascii string 
uint8_t ser_cmd_started =0 ; // are we in process
uint8_t ser_got_RGBbytes =0 ; // how many bytes we've recived. 
uint8_t rgb_r[6]; // R, g, b, P1, p2
uint8_t bs=0; // how many bytes into our rgbBytestring.

void virtser_recv(uint8_t serIn) { 
#ifdef RGBLIGHT_ENABLE 
    if ((serIn == 10 ) || (serIn ==  13) || ser_got_RGBbytes >=5) { //reached newline or max digits

        if (ser_cmd_started) {
            ser_cmd_started =0 ; // end loop at newline
            virtser_send('|');

            if (ser_got_RGBbytes==3) {
                rgblight_setrgb( rgb_r[0], rgb_r[1], rgb_r[2]);
            }

            if (ser_got_RGBbytes ==4) {
                if (( rgb_r[3] >=0)  && (rgb_r[3] <= RGBLED_NUM) ) { // is pos1 plausible
                    rgblight_setrgb_at ( rgb_r[0], rgb_r[1], rgb_r[2], rgb_r[3]);
                } else {
                        rgblight_setrgb( rgb_r[0], rgb_r[1], rgb_r[2]);
                }
            }

            if (ser_got_RGBbytes == 5) { // are start and end positions plausible? 
                if ( (rgb_r[4] >0)  && (rgb_r[4] <= RGBLED_NUM) && (rgb_r[4] > rgb_r[3]) && 
                 (rgb_r[3] >=0)  && (rgb_r[3] <= (RGBLED_NUM -1))  ) {
                    rgblight_setrgb_range(rgb_r[0], rgb_r[1], rgb_r[2], rgb_r[3], rgb_r[4]);
               } else {
                   rgblight_setrgb( rgb_r[0], rgb_r[1], rgb_r[2]);
               }
            }
        } else { // newline outside of command loop, or something that can be ignored. 
          //virtser_send('.');
        }
    } 

    if (1 == ser_cmd_started) { // collecting bytes. 
        if  (   // it is time to compute a byte
          ( ( (serIn == ',') || (serIn == '.') ) && (bs > 0) ) || // signal done with the byte. 
            (bs ==2 )){ //or we know this is last.
        
            if ( (serIn <= '9') && (serIn >='0') ) { //3rd asci digit 
                ser_rgbByte[bs] = serIn;
                bs++;
            //  virtser_send(serIn);
            }

            if (bs>3) {
                rgb_r[ser_got_RGBbytes]=255;
                ser_got_RGBbytes ++;
            }
            if (bs==3) {
              rgb_r[ser_got_RGBbytes] = (ser_rgbByte[0] -'0')*100 + (ser_rgbByte[1] -'0')*10 + (ser_rgbByte[2] -'0' );
              ser_got_RGBbytes ++;
            }
            if (bs ==2 ) {
               rgb_r[ser_got_RGBbytes] = (ser_rgbByte[0] -'0')*10 +  (ser_rgbByte[1] -'0' );
               ser_got_RGBbytes ++;
            }
            if (bs ==1) {
               rgb_r[ser_got_RGBbytes] = (ser_rgbByte[0] -'0');
               ser_got_RGBbytes ++;
            }  // {else wipe & start over}

          bs=0;
    //  virtser_send(ser_got_RGBbytes+'0');

        } else { // haven't got enough for our byte / no terminal marker
            if ( (serIn <= '9') && (serIn >='0') ) { //ascii only 
                ser_rgbByte[bs] = serIn;
                bs++;
            //    virtser_send(serIn);
            }
        }
    } else { //not in command loop - next is command w/o arguments, or start of one. 
        switch (serIn) {
            case 'C': // color switch
                ser_cmd_started=1;
                ser_got_RGBbytes = bs =0;
                virtser_send('/');
                break;
        
            case 'r': //red
                rgblight_setrgb(RGB_RED);
                break;
         
            case 'g': 
                rgblight_setrgb(RGB_GREEN);
                break;
   
            case 'b':  // color switch
                rgblight_setrgb(RGB_BLUE);
                break;

            case 'w':  // color switch
                rgblight_setrgb(RGB_WHITE);
                break;

            case 'o':  // color black/off
                rgblight_setrgb(0,0,0);
                break;
               
            case 'T':  // toggle
                rgblight_toggle();
                break;
            
            case 'P': // pulse led
                rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING);
                break; 
            case 'S':  // Static
                rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
                break;
           
            case 'U':  // Rainbow
                rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_MOOD);
                break;
                   
            default: 
           //     virtser_send(serIn);
                break;

        }
    }
#endif // RGBLIGHT_ENABLE
}

#endif // VirtSerial
