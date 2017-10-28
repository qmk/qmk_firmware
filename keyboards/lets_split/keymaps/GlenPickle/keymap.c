/*******************************************
 * QMK firmware for a let's split keyboard
 *
 * William Wilson
 * June 16, 2017
 ******************************************/

#include "lets_split.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

#define _DVORAK 0
#define _NUMPAD 1
#define _SYMBOLS 2
#define _FN 3
#define _MACROS 4
#define _QWERTY 5
#define _QNUMPAD 6
#define _QSYMBOLS 7
#define _QFN 8
#define _QMACROS 9
#define _LOCK 10

#define KC_ KC_TRNS
#define _______ KC_TRNS

#define KC_NMPD TG(_NUMPAD)
#define KC_SYMB TG(_SYMBOLS)
#define KC_QNUM TG(_QNUMPAD)
#define KC_QSYM TG(_QSYMBOLS)
#define KC_QSFN LT(_QFN,KC_MINS)
#define KC_SPFN LT(_FN,KC_MINS)
#define KC_SPCT MT(MOD_LCTL, KC_LBRC)
#define KC_SPLT MT(MOD_LALT, KC_EQL)
#define KC_GBRC MT(MOD_RGUI, KC_RBRC)
#define KC_MESC LT(_MACROS, KC_ESC)
#define KC_QESC LT(_QMACROS, KC_ESC)
#define KC_GLPK M(0)
#define KC_JERY M(1)
#define KC_IMGR M(2)
#define KC_INCL M(3)
#define KC_EML M(4)
#define KC_PULL M(5)
#define KC_PUSH M(6)
#define KC_SPCS M(7)
#define KC_PSWD M(8)
#define KC_DNCU M(9)
#define KC_DNCD M(10)
#define KC_DSCU M(11)
#define KC_DSCD M(12)
#define KC_QNCU M(13)
#define KC_QNCD M(14)
#define KC_QSCU M(15)
#define KC_QSCD M(16)
#define KC_QWCU M(17)
#define KC_QWCD M(18)
#define KC_LTOG M(19)
#define KC_STEP M(20)
#define KC_LOCK M(21)
#define KC_ULCK M(22)
#define KC_CTST M(23)

#define KC_CAD LALT(LCTL(KC_DEL))
#define KC_DVRK TO(_DVORAK)
#define KC_QWRT TO(_QWERTY)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_DVORAK] = KC_KEYMAP(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
     MESC,QUOT,COMM,DOT , P  , Y  ,      F  , G  , C  , R  , L  ,SLSH,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     TAB , A  , O  , E  , U  , I  ,      D  , H  , T  , N  , S  , ENT,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     LSPO,SCLN, Q  , J  , K  , X  ,      B  , M  , W  , V  , Z  ,RSPC,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     SPCT,SPFN,SPLT,AMPR,DNCU,BSPC,     SPC ,DSCU,ASTR,EXLM,BSLS,GBRC
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  ),

  [_NUMPAD] = KC_KEYMAP(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
         ,    ,    ,    ,    ,    ,         ,  7 ,  8 ,  9 ,MINS,SLSH,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,         ,  4 ,  5 ,  6 ,PLUS, ENT,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     LSFT,    ,    ,    ,    ,    ,         ,  1 ,  2 ,  3 ,ASTR, EQL,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
         ,    ,    ,    ,    ,BSPC,     SPC ,  0 ,  0 , DOT,SLSH,RGUI
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  ),

  [_SYMBOLS] = KC_KEYMAP(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
         ,EXLM, AT ,HASH,DLR ,PERC,     CIRC,AMPR,ASTR,LPRN,RPRN,SLSH,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
      F1 , F2 , F3 , F4 , F5 , F6 ,     TILD,EQL ,UNDS,LCBR,RCBR,PIPE,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
      F7 , F8 , F9 , F10, F11, F12,     GRV ,PLUS,MINS,LBRC,RBRC,BSLS,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
         ,    ,    ,    , NO ,BSPC,     SPC ,DSCD,    ,    ,    ,RGUI
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  ),

  [_FN] = KC_KEYMAP(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
         ,    ,    ,    , DEL,BSPC,         ,HOME, UP , END, INS,PSCR,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
         ,    ,    ,LSFT,LCTL, ENT,         ,LEFT,DOWN,RGHT, DEL,    ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,         ,PGUP,PGDN,    ,    ,    ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
         ,    ,    ,    ,    ,DEL ,         ,    ,    ,    ,    ,   
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  ),

  [_MACROS] = KC_KEYMAP(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
         ,    ,PULL,PUSH,PSWD,    ,         ,GLPK,    ,    ,IMGR,QWCU,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
         ,    ,    ,EML ,    ,INCL,     CAD ,    ,LTOG,    ,    ,    ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     CAPS,    ,    ,JERY,    ,    ,         ,    ,    ,    ,    ,CAPS,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
         ,    ,    ,    ,    ,LOCK,     SPCS,    ,    ,    ,    ,   
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  ),

  [_QWERTY] = KC_KEYMAP(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
     QESC, Q  , W  , E  , R  , T  ,      Y  , U  , I  , O  , P  ,QUOT,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     TAB , A  , S  , D  , F  , G  ,      H  , J  , K  , L  ,SCLN, ENT,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     LSPO, Z  , X  , C  , V  , B  ,      N  , M  ,COMM,DOT ,SLSH,RSPC,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     SPCT,QSFN,SPLT,AMPR,QNCU,BSPC,     SPC ,QSCU,ASTR,EXLM,LBRC,GBRC
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  ),

  [_QNUMPAD] = KC_KEYMAP(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
         ,    ,    ,    ,    ,    ,         ,  7 ,  8 ,  9 ,MINS,QUOT,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,         ,  4 ,  5 ,  6 ,PLUS, ENT,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     LSFT,    ,    ,    ,    ,    ,         ,  1 ,  2 ,  3 ,ASTR, EQL,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
         ,    ,    ,    ,QNCD,BSPC,     SPC ,  0 ,  0 , DOT,SLSH,RGUI
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  ),

  [_QSYMBOLS] = KC_KEYMAP(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
         ,EXLM, AT ,HASH,DLR ,PERC,     CIRC,AMPR,ASTR,LPRN,RPRN,QUOT,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
      F1 , F2 , F3 , F4 , F5 , F6 ,     TILD,EQL ,UNDS,LCBR,RCBR,PIPE,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
      F7 , F8 , F9 , F10, F11, F12,     GRV ,PLUS,MINS,LBRC,RBRC,BSLS,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
         ,    ,    ,    , NO ,BSPC,     SPC ,QSCD,    ,    ,    ,RGUI
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  ),

  [_QFN] = KC_KEYMAP(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
         ,    ,    ,    , DEL,BSPC,         ,HOME, UP , END, INS,PSCR,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
         ,    ,    ,LSFT,LCTL, ENT,         ,LEFT,DOWN,RGHT, DEL,   ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,         ,PGUP,PGDN,    ,    ,    ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
         ,    ,    ,    ,    ,DEL ,         ,    ,    ,    ,    ,   
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  ),

  [_QMACROS] = KC_KEYMAP(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
         ,    ,    ,EML ,    ,LTOG,         ,    ,INCL,    ,PSWD,QWCD,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
         ,    ,    ,CAD ,    ,GLPK,         ,JERY,    ,IMGR,    ,    ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,         ,    ,PULL,PUSH,    ,    ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
         ,    ,    ,    ,    ,LOCK,     SPCS,    ,    ,    ,    ,   
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  ),

  [_LOCK] = KC_KEYMAP(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
      NO , NO , NO , NO , NO ,ULCK,      NO , NO , NO , NO , NO , NO ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
      NO , NO , NO , NO , NO , NO ,      NO , NO , NO , NO , NO , NO ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
      NO , NO , NO , NO , NO , NO ,      NO , NO , NO , NO , NO , NO ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
      NO , NO , NO , NO , NO , NO ,      NO , NO , NO , NO , NO , NO 
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  ) 
 
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) // this is the function signature -- just copy/paste it into your keymap file as it is.
{
  switch(id) {
    /* type my username */
    case 0: // this would trigger when you hit a key mapped as M(0)
      if (record->event.pressed) {
                SEND_STRING("GlenPickle");
        return false; // This is false because it has to return something.
      }
      break;
    /* make fun of my father in law */
    case 1:
      if (record->event.pressed) {
        SEND_STRING("My friend Louisa got straight A's all the way from kindergarten to her PhD. One day while we were out biking in Europe we ran into John Nash knife fighting with Sifu. I was busy fighting a student of mine with my Aikido, or else I would have hypnotized both John Nash and Sifu. I HATE A WHITE SAUCE.");
        return false;
      }
      break;
    /* link to the build log for this keyboard */
    case 2:
      if (record->event.pressed) {
        SEND_STRING("http://imgur.com/gallery/PRDJm");
        return false;
      }
      break;
    /* include some kind of library or header */
    case 3:
      if (record->event.pressed) {
        SEND_STRING("#include <>");
        return MACRO( T(LEFT), END);
      }
      break;
    /* type my email address */
    case 4:
      if (record->event.pressed) {
        SEND_STRING("wilson.r.william@gmail.com");
        return false;
      }
      break;
    case 5:
      if (record->event.pressed) {
        SEND_STRING("git pull");
        return MACRO( T(ENT), END );
      }
      break;
    case 6:
      if (record->event.pressed){
        SEND_STRING("git push");
        return MACRO( T(ENT), END );
      }
      break;
    case 7:
      if (record->event.pressed){
        SEND_STRING("   ");
        return false;
      }
      break;
    case 8:
      if (record->event.pressed){
        SEND_STRING("password");
        return MACRO ( T(ENT), END );
      }
      break;
    case 9:
      if (record->event.pressed){
	layer_on(_NUMPAD);
	#ifdef RGBLIGHT_ENABLE
        rgblight_setrgb(0x00,0x00,0xff);
	#endif
      }
      else {
         layer_off(_NUMPAD);
         #ifdef RGBLIGHT_ENABLE
         rgblight_setrgb(0x00,0xff,0x00);
         #endif
         return false;
      }
      break;
    case 10:
      if (record->event.pressed){
	layer_off(_NUMPAD);
	#ifdef RGBLIGHT_ENABLE
        rgblight_setrgb(0x00,0xff,0x00);
	#endif
        return false;
      }
      break;
    case 11:
      if (record->event.pressed){
 	layer_on(_SYMBOLS);
	#ifdef RGBLIGHT_ENABLE
        rgblight_setrgb(0xff,0x00,0x00);
	#endif
        return false;
      }
      break;
    case 12:
      if (record->event.pressed){
	layer_off(_SYMBOLS);
	#ifdef RGBLIGHT_ENABLE
        rgblight_setrgb(0x00,0xff,0x00);
	#endif
        return false;
      }
      break;
    case 13:
      if (record->event.pressed){
	layer_on(_QNUMPAD);
	#ifdef RGBLIGHT_ENABLE
        rgblight_setrgb(0x00,0x00,0xff);
	#endif
        return false;
      }
      break;
    case 14:
      if (record->event.pressed){
	layer_off(_QNUMPAD);
	#ifdef RGBLIGHT_ENABLE
        rgblight_setrgb(0xff,0x00,0xff);
	#endif
        return false;
      }
      break;
    case 15:
      if (record->event.pressed){
	layer_on(_QSYMBOLS);
	#ifdef RGBLIGHT_ENABLE
        rgblight_setrgb(0xff,0x00,0x00);
	#endif
        return false;
      }
      break;
    case 16:
      if (record->event.pressed){
	layer_off(_QSYMBOLS);
	#ifdef RGBLIGHT_ENABLE
        rgblight_setrgb(0xff,0x00,0xff);
	#endif
        return false;
      }
      break;
    case 17:
      if (record->event.pressed){
	layer_on(_QWERTY);
	#ifdef RGBLIGHT_ENABLE
        rgblight_setrgb(0xff,0x00,0xff);
	#endif
        return false;
      }
      break;
    case 18:
      if (record->event.pressed){
	layer_off(_QMACROS);
        layer_off(_QWERTY);
	#ifdef RGBLIGHT_ENABLE
        rgblight_setrgb(0x00,0xff,0x00);
	#endif
        return false;
      }
      break;
     case 19:
      if (record->event.pressed){
        rgblight_toggle();
	#ifdef RGBLIGHT_ENABLE
	startup_animation();
	#endif
        return false;
      }
      break;
     case 20:
      if (record->event.pressed){
	#ifdef RGBLIGHT_ENABLE
        rgblight_step();
	#endif
        return false;
      }
     break;
    case 21:
      if (record->event.pressed){
	layer_on(_LOCK);
	#ifdef RGBLIGHT_ENABLE
	rgblight_mode(8);
        #endif
        return MACRO( D(LGUI), T(L), U(LGUI), END );
      }
      break;
    case 22:
      if (record->event.pressed){
	layer_off(_LOCK);
	layer_off(_MACROS);
	send_string(" ");
	#ifdef RGBLIGHT_ENABLE
	rgblight_mode(1);
	rgblight_setrgb(0x00,0xff,0x00);
	#endif
        return MACRO( D(LCTL), D(LALT), D(DEL), U(LCTL), U(LALT), U(DEL), END );
      }
      break;
    case 23:
      if (record->event.pressed){
	#ifdef RGBLIGHT_ENABLE
        startup_animation();
	#endif
        return false;
      }
      break;
 }
  return MACRO_NONE;
};
