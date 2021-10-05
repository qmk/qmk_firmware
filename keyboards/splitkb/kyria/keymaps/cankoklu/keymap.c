/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


	
	// more color options https://beta.docs.qmk.fm/using-qmk/hardware-features/lighting/feature_rgblight
	// find magnetic usbc and trrs
	
	// close tab, reopen tab
	


#include QMK_KEYBOARD_H

enum layers {
    _QWERTY = 0,
    _NAV,
	_SEL,
	_SYM,
    _NUM,
    _FUNCTION,
	_WINDOW,
};

enum custom_keycodes {
  LINKIFY = SAFE_RANGE,
  THUMBUP,
  SMILEY,
  SHRUG,
  CANBRACKET,
  REQUESTACCESS,
  ARRORI,
};



// Aliases for readability
#define QWERTY   DF(_QWERTY)


#define SYM      MO(_SYM)
#define NUM      MO(_NUM)

#define NAV      MO(_NAV)
#define SEL      MO(_SEL)
#define FKEYS    MO(_FUNCTION)
#define WINDOW   MO(_WINDOW)

#define CTL_ESC  MT(MOD_LCTL, KC_ESC)
#define CTL_QUOT MT(MOD_RCTL, KC_QUOTE)
#define CTL_MINS MT(MOD_RCTL, KC_MINUS)
#define ALT_ENT  MT(MOD_LALT, KC_ENT)

#define GUI_QUOT MT(MOD_RGUI, KC_QUOTE)
#define GUI_CAPS MT(MOD_LGUI, KC_CAPS)
#define ALT_ESC  MT(MOD_LALT, KC_ESC)

#define A_NAV    LT(NAV, KC_A)
#define S_SEL    LT(SEL, KC_S)
#define D_NUM    LT(NUM, KC_D)

// #define SQUEST   LT(SYM, S(KC_QUES))
	
// Note: LAlt/Enter (ALT_ENT) is not the same thing as the keyboard shortcut Alt+Enter.
// The notation `mod/tap` denotes a key that activates the modifier `mod` when held down, and
// produces the key `tap` when tapped (i.e. pressed and released).

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	
   /*
    * Base Layer: QWERTY
    *
    * ,-------------------------------------------.                              ,-------------------------------------------.
    * |  Tab   |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  Bksp  |
    * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
    * |Ctrl/Esc|   A  |   S  |   D  |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : |Ctrl/' "|
    * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
    * | LShift |   Z  |   X  |   C  |   V  |   B  | [ {  |CapsLk|  |F-keys|  ] } |   N  |   M  | ,  < | . >  | /  ? | RShift |
    * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
    *                        |Adjust| LGUI | LAlt/| Space| Nav  |  | Sym  | Space| AltGr| RGUI | Menu |
    *                        |      |      | Enter|      |      |  |      |      |      |      |      |
    *                        `----------------------------------'  `----------------------------------'
    
       [_QWERTY] = LAYOUT(
        KC_TAB  , KC_Q ,  KC_W   ,  KC_E  ,   KC_R ,   KC_T ,                                        KC_Y,   KC_U ,  KC_I ,   KC_O ,  KC_P , KC_BSPC,
        CTL_ESC , KC_A ,  KC_S   ,  KC_D  ,   KC_F ,   KC_G ,                                        KC_H,   KC_J ,  KC_K ,   KC_L ,KC_SCLN,CTL_QUOT,
        KC_LSFT , KC_Z ,  KC_X   ,  KC_C  ,   KC_V ,   KC_B , KC_LBRC,KC_CAPS,     FKEYS  , KC_RBRC, KC_N,   KC_M ,KC_COMM, KC_DOT ,KC_SLSH, KC_RSFT,
                                   ADJUST , KC_LGUI, ALT_ENT, KC_SPC , NAV   ,     SYM    , KC_SPC ,KC_RALT, KC_RGUI, KC_APP
       ),
	*/
	
	
/*
 * Base Layer: QWERTY
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |ALT/ESC |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  +     |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |GUI/CAPS|A/NAV |S/SEL | D/NUM|   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : |RGUI/' "|
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  | [ {  | NUM  |  |F-keys|  ] } |   N  |   M  | ,  < | . >  | /  ? | RShift |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'	
 *                        |WINDOW| LCTR | DEL  | Space| TAB  |  | Bksp | ENTER|  SYM | RCTR |   ?  |
 *                        |      |      |      |      |      |  |      |      |      |   -  |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_QWERTY] = LAYOUT(
     ALT_ESC  , KC_Q ,  KC_W   ,  KC_E  ,   KC_R ,   KC_T ,                                        KC_Y,   KC_U ,  KC_I ,   KC_O ,  KC_P ,  KC_PLUS,
     GUI_CAPS , A_NAV,  S_SEL  ,  D_NUM ,   KC_F ,   KC_G ,                                        KC_H,   KC_J ,  KC_K ,   KC_L ,KC_SCLN,GUI_QUOT,
     KC_LSPO , KC_Z ,  KC_X   ,   KC_C  ,   KC_V ,   KC_B , KC_LBRC, DF(_NUM),      FKEYS    , KC_RBRC,  KC_N,   KC_M ,KC_COMM, KC_DOT ,KC_SLSH, KC_RSPC,
                                 WINDOW , KC_LCTL, KC_DEL, KC_SPC , KC_TAB,   KC_BSPC  , KC_ENT ,  SYM,    CTL_MINS,  KC_QUES
    ),




/*
 * Nav Layer: Media, navigation
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              | PgUp | Alt← |   ↑  | Alt→ | Home |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |   x  |      |      |      |Bullet|                              | PgDn |  ←   |   ↓  |   →  | End  |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |NList | -->  |VolUp |  |      |Pause |      | Gui← |      | Gui→ |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |Ind L |Ind R |MicMut|VolMut|VolDn |  |M Prev|M Play|M Next|      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NAV] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                         KC_PGUP, A(KC_LEFT),   KC_UP, A(KC_RIGHT), KC_HOME, _______,
      _______, _______, _______, _______,       _______, G(S(KC_8)),                                      KC_PGDN, KC_LEFT,    KC_DOWN,    KC_RIGHT,  KC_END, _______,
      _______, _______, _______, _______,       _______, G(S(KC_7)), ARRORI,   KC_VOLU, _______, KC_PAUSE,_______, G(KC_LEFT), _______, G(KC_RIGHT),  _______, _______,
                                 G(KC_LBRC), G(KC_RBRC), G(C(KC_M)), KC_MUTE,  KC_VOLD, KC_MPRV, KC_MPLY, KC_MNXT, _______,    _______
    ),


/*
 * Nav Layer: Select, copy/paste  ALL of right side is Shift+
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |Shrug |      |      |      |                              | PgUp | Alt← |   ↑  | Alt→ | Home |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |   x  |      |      |Enter |                              | PgDn |  ←   |   ↓  |   →  | End  |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |GEnter| Cut  |PstClr|  |      |      |      | Gui← |      | Gui→ |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        | Undo | Redo |Linki |Copy  | Paste|  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_SEL] = LAYOUT(
      _______, _______, SHRUG,   _______,_______,_______,                                        S(KC_PGUP), S(A(KC_LEFT)),   S(KC_UP), S(A(KC_RIGHT)), S(KC_HOME), _______,
      _______, _______, _______, _______, _______,  KC_ENT,                                        S(KC_PGDN), S(KC_LEFT),    S(KC_DOWN),    S(KC_RIGHT),  S(KC_END), _______,
      _______, _______, _______, _______, _______,  G(KC_ENT), G(KC_X), G(S(KC_V)), _______, _______,    _______, S(G(KC_LEFT)),    _______, S(G(KC_RIGHT)),    _______, _______,
                                 G(KC_Z), G(KC_Y),  LINKIFY, G(KC_C), G(KC_V),    _______, _______,    _______, _______,          _______
    ),


/*
 * Sym Layer: Numbers and symbols
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |    `   |  1   |  2   |  3   |  4   |  5   |                              |   6  |  7   |  8   |  9   |  0   |   =    |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |    ~   |  !   |  @   |  #   |  $   |  %   |                              |   ^  |  &   |  *   |  (   |  )   |   +    |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |    |   |   \  |  :   |  ;   |  -   |  [   |  {   |      |  |   ↑  |   }  |   ]  |  _   |  ,   |  .   |  /   |   ?    |
 * `----------------------+------+-------------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |   ↓  |      |   x  |  ←   |  →   |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_SYM] = LAYOUT(
      KC_GRV ,   KC_1 ,   KC_2 ,   KC_3 ,   KC_4 ,   KC_5 ,                                       KC_6 ,   KC_7 ,   KC_8 ,   KC_9 ,   KC_0 , KC_EQL ,
     KC_TILD , KC_EXLM,  KC_AT , KC_HASH,  KC_DLR, KC_PERC,                                     KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PLUS,
     KC_PIPE , KC_BSLS, KC_COLN, KC_SCLN, KC_MINS, KC_LBRC, KC_LCBR, _______,   KC_UP, KC_RCBR, KC_RBRC, KC_UNDS, KC_COMM,  KC_DOT, KC_SLSH, KC_QUES,
                                 _______, _______, _______, _______, _______, KC_DOWN, _______, _______, KC_LEFT, KC_RIGHT
    ),

/*
 * NUM Layer: Numbers and symbols
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |    `   |      |      |      |  (   |  )   |                              |   +  |  7   |  8   |  9   |  *   |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |    ~   |  !   |  @   |  #   |  $   |  %   |                              |   =  |  4   |  5   |  6   |  =   |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |    |   |   \  |  :   |  ;   |  -   |  _   |      |  X   |  |      |      |   -  |  1   |  2   |  3   |  /   |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |Access|Smiley|Thumb |      |      |  |      |      |  0   |  .   |  .   |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NUM] = LAYOUT(
      KC_GRV ,_______ , _______, _______, KC_LPRN, KC_RPRN,                                     KC_PLUS ,  KC_7 ,    KC_8,  KC_9, KC_ASTR, _______,
     KC_TILD , KC_EXLM,  KC_AT , KC_HASH,  KC_DLR, KC_PERC,                                     KC_EQL,     KC_4,    KC_5,  KC_6, KC_EQL,  _______,
     KC_PIPE , KC_BSLS, KC_COLN, KC_SCLN, KC_MINS, KC_UNDS, _______, QWERTY, _______, _______, KC_MINS,    KC_1,    KC_2,  KC_3, KC_SLSH, _______,
                            REQUESTACCESS, SMILEY, THUMBUP, _______, _______, _______, _______, KC_0,     KC_DOT, KC_DOT
    ),


/*
 * Function Layer: Function keys
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  F1  | F2   | F3   | F4   | F5   |                              |  F6  | F7   | F8   | F9   | F10  | F11    |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * | TOG    | SAI  | HUI  | VAI  | MOD  |      |                              |      |      |      |      |      | F12    |
 * +--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        | SAD  | HUD  | VAD  | RMOD |      |      |      |  |   X  |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_FUNCTION] = LAYOUT(
      _______,    KC_F1 ,    KC_F2 ,    KC_F3 ,    KC_F4 , KC_F5  ,                                      KC_F6 ,  KC_F7 ,  KC_F8 , KC_F9 ,  KC_F10 ,  KC_F11,
       RGB_TOG,  RGB_SAI,   RGB_HUI,   RGB_VAI,   RGB_MOD, _______,                                    _______, _______, _______, _______,  _______,  KC_F12,
       _______,  RGB_SAD,   RGB_HUD,   RGB_VAD,  RGB_RMOD, _______,_______, _______, _______, _______, _______, _______, _______, _______,  _______, _______,
                                        _______, _______,  _______,_______, _______, _______, _______, _______, _______, _______
    ),

/*
 * Window Layer: Key shortcuts to manage rectangle
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |Mission |      |      |      |      |      |                              |      | CW<  |AWUP  | >CW  |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * | ShApps |      |      |      |      |      |                              |      | AW<  | ACW F| >AW  |      |   O     |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      |      | CWS< |AWDWN | >CWS |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |   X  |SLEEP |      |REOPEN|CLTAB |  | ACW< | ACW> |      |      |      |
 *                        |      |      |      | TAB  |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_WINDOW] = LAYOUT(
      C(KC_UP), _______, _______, _______, _______, _______,                                                                        _______, C(G(KC_LEFT)),    A(G(KC_UP)),  C(G(KC_RIGHT)),      _______, _______,
      C(KC_DOWN), _______, _______, _______, _______, _______,                                                                        _______, A(G(KC_LEFT)),    A(C(G(KC_F))), A(G(KC_RIGHT)),     _______, _______,
      _______, _______, _______, _______, _______, _______,           _______,    _______,    _______, _______,                    _______, S(C(G(KC_LEFT))), A(G(KC_DOWN)), S(C(G(KC_RIGHT))),  _______, _______,
                                 _______, A(C(S(G(KC_F12)))), _______,G(S(KC_T)), G(KC_W),    A(C(G(KC_LEFT))), A(C(G(KC_RIGHT))), _______, _______, _______
    ),




// /*
//  * Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),
};




bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
        
/*------------------------------|
*         Ett Custom Stuff      |
*-------------------------------|*/
      case ARRORI:
      if (record->event.pressed)
      {
        SEND_STRING("--> ");
      }
      return false;
      break;	
	  	  
      case LINKIFY:
      if (record->event.pressed)
      {
        SEND_STRING(SS_LGUI("k") SS_LGUI("v") SS_TAP(X_ENTER));
      }
      return false;
      break;
 
      case THUMBUP:
      if (record->event.pressed)
      {
        SEND_STRING("1t1" SS_TAP(X_DOWN) SS_TAP(X_ENTER));
      }
      return false;
      break;
 
      case SMILEY:
      if (record->event.pressed)
      {
         SEND_STRING("1s1" SS_TAP(X_DOWN) SS_TAP(X_ENTER));
      }
      return false;
      break;
	  
      case SHRUG:
      if (record->event.pressed)
      {
         SEND_STRING("1d1" SS_TAP(X_DOWN) SS_TAP(X_ENTER));
	  }
      return false;
      break;
	  
      case CANBRACKET:
      if (record->event.pressed)
      {
        SEND_STRING("[Can]");
      }
      return false;
      break;
 
      case REQUESTACCESS:
      if (record->event.pressed)
      {
          SEND_STRING("1r1" SS_TAP(X_DOWN) SS_TAP(X_ENTER));
      }
      return false;
      break;
	 

      }
    return true;
};

