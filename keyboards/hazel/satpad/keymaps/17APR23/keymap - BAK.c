//24MAR23
#include QMK_KEYBOARD_H


enum layers {
  _HOME,       // home base layer
  _LOWER,  
  _RAISE,
  _ADJUST,
  _EXTRAS,
  _FN,
  _SYMBOLS
};

// TAP DANCE DECLARATIONS  ============================================================================
enum {
   T_BR = 0, // [, ]
   // T_PA,     // (, )
    T_SL,     // slash, backslash
    T_UR,     // up, right
    T_DL,     // down, left
    T_UMIN,   // underscore, minus
    T_QUOTE,    // quote, double quote
    T_DOTENT,   // dot, enter
    T_IENT,     // I, enter
    T_TSPC,     // T, space
    T_COMMSPC,  // space, comma
    T_DOTSPC,   // space, dot
    T_QEXC,     // Tap once for ?, twice for !
    T_QESC,     // Tap once for "q", twice for escape  
   // T_NENT,     // N, enter
   // T_TE,     // tab, escape
    T_CP,     // copy, paste
    T_XX,      // open/close paren
    T_YY,      // open/close brackets
    T_ATH,     // @, #
    T_PRAM,    // %, &
    T_SBAK,    // Tap once for semicolon, twice for backspace
};
 

//TAP DANCE DEFINITIONS ===========================================
qk_tap_dance_action_t tap_dance_actions[] = {
 [T_BR] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_RBRC),         // Tap once for [, twice for ]
 // [T_PA] = ACTION_TAP_DANCE_DOUBLE(KC_LPRN, KC_RPRN),
  [T_SL] = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, KC_BSLS),
  [T_UR] = ACTION_TAP_DANCE_DOUBLE(KC_UP, KC_RGHT),
  [T_DL] = ACTION_TAP_DANCE_DOUBLE(KC_DOWN, KC_LEFT),
  [T_UMIN]  = ACTION_TAP_DANCE_DOUBLE(KC_UNDS, KC_MINS),	   // Tap once for Underscore, twice for Minus
  [T_QUOTE] = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, KC_DQUO),     // Tap once for quote, twice for double quote
  [T_DOTENT] = ACTION_TAP_DANCE_DOUBLE(KC_DOT, KC_ENT),      // Tap once for dot, twice for enter
  [T_IENT] = ACTION_TAP_DANCE_DOUBLE(KC_I, KC_ENT),          // Tap once for I, twice for enter
  [T_TSPC] = ACTION_TAP_DANCE_DOUBLE(KC_T, KC_SPC),          // Tap once for "t", twice for space
  [T_COMMSPC] = ACTION_TAP_DANCE_DOUBLE(KC_SPC, KC_COMM),    // Tap once for space, twice for comm
  [T_DOTSPC] = ACTION_TAP_DANCE_DOUBLE(KC_SPC, KC_DOT),      // Tap once for space, twice for dot
  [T_QEXC] = ACTION_TAP_DANCE_DOUBLE(KC_QUES, KC_EXLM),      // Tap once for ?, twice for !  
  [T_QESC] = ACTION_TAP_DANCE_DOUBLE(KC_Q, KC_ESC),          // Tap once for "q", twice for escape 
 // [T_NENT] = ACTION_TAP_DANCE_DOUBLE(KC_N, KC_ENT),          // Tap once for "n", twice for enter
 // [T_TE] = ACTION_TAP_DANCE_DOUBLE(KC_TAB, KC_ESC),      // Tap once for tab, twice for esc
  [T_CP] = ACTION_TAP_DANCE_DOUBLE(LCTL(KC_C), LCTL(KC_V)),
  [T_XX] = ACTION_TAP_DANCE_DOUBLE(KC_LPRN, KC_RPRN),		
  [T_YY] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_RBRC),	
  [T_ATH] = ACTION_TAP_DANCE_DOUBLE(KC_AT, KC_HASH),	
  [T_PRAM] = ACTION_TAP_DANCE_DOUBLE(KC_PERC, KC_AMPR),
  [T_SBAK] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_BSPC),	   // Tap once for semicolon, twice for backspace
  //[X_CTL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, x_finished, x_reset)

};

#define XXXX KC_NO

// Defines for task manager and such
#define CALTDEL LCTL(LALT(KC_DEL))
// #define TSKMGR LCTL(LSFT(KC_ESC))
#define CLIP LCTL(LALT(KC_Q))		     // Clipboard
#define SS  LCTL(LALT(KC_G))		     // Greenshot region
#define FNZ LT(_FN, KC_Z)            // Z when tapped, FN layer MO
#define CTRLX MT(MOD_LCTL, KC_X)     // X when tapped, Ctrl when held
#define TBSHFT MT(MOD_LSFT, KC_TAB)  // Tab when tapped, Shift when held
// #define LOWER MO(_LOWER)
// #define RAISE MO(_RAISE)

/* ==========================================================================
    MACROS
   ==========================================================================
*/

// Macro Declarations
enum custom_keycodes {
  CK_TRIPLEZERO = SAFE_RANGE,
  M01,
  M02,
  M03,
  M04,
  M05,
  M06, 
  M07,
  M08
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * LEGEND:
 *
 * ,--------------------------------.
 * |     Top row: shifted character |
 * | Central row: standard char     |
 * |  Bottom row: hold modifier     |
 * `--------------------------------'
 *
 *  "____" means free to be assigned
 *
 */

/* Workman Home Layer
 * ,----------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |
 * |   Q  |   D  |   R  |   W  |   B  |      |   J  |   F  |   U  |   P  |  ;   |
 * |Escape|  FN  |      |      |SYMBOL|      |SYMBOL|      |      |      |BKSPC |
 * |------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |
 * |   A  |   S  |   H  |   T  |   G  |      |   Y  |   N  |   E  |   O  |   I  |
 * | Shift|      |      |EXTRAS| OSkey|      | OSkey|      |      |      | Enter|
 * |------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |
 * |   Z  |   X  |   M  |   C  |   V  |      |   K  |   L  | Space| Space|  /\  |
 * |  FN  | CTRL |  OS  |  ALT |LOWER |      | RAISE|  Alt |   ,  |   .  |      |
 * '----------------------------------------------------------------------------'
 * 
 *   http://www.keyboard-layout-editor.com/#/gists/fcc6c759cf335abf31f6c200db3b9aca
 *   
 */
  [_HOME] = LAYOUT_3x11(
    T_QESC, LT(_FN, KC_D), KC_R, KC_W, LT(_SYMBOLS, KC_B),   XXXX, LT(_SYMBOLS, KC_J), KC_F, KC_U, KC_P, T_SBAK,
    MT(MOD_LSFT, KC_A), KC_S, KC_H, LT(_EXTRAS, KC_T),   MT(MOD_LGUI, KC_G),  XXXX, MT(MOD_RGUI, KC_Y), KC_N, KC_E, KC_O, T_IENT,
    FNZ, CTRLX,     MT(MOD_LGUI, KC_M),   MT(MOD_LALT, KC_C), LT(_LOWER, KC_V), XXXX, LT(_RAISE, KC_K), MT(MOD_LALT, KC_L), TD(T_COMMSPC),   TD(T_DOTSPC),   KC_SLSH
  ),




/* LOWER LAYER 
 * ,----------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |   &  |   *  |   (  |   )  |
 * |  ()  |  []  | / \  |      |      |      |  / \ |   7  |   8  |   9  |   0  |
 * |      |      |      |      |      |      | ____ | ____ | ____ | ____ | Shift|
 * |------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |   $  |   %  |   ^  |      |
 * |  @ # |  & % |      |      |      |      |  [ ] |   4  |   5  |   6  | Del  |
 * |      |      |      |      |      |      | ____ | ____ | ____ | ____ | Shift|
 * | -----+------+------+------+------+------|------+------+------+------+------|
 * |      |      |      |      | XXXX |      |      |   !  |   @  |   #  |      | 
 * |      |      |      |      | XXXX |      |      |   1  |   2  |   3  |  .   | 
 * |      |      |      |      | XXXX |      | ____ | ____ | ____ | ____ | Enter| 
 * '----------------------------------------------------------------------------'
 */
  [_LOWER] = LAYOUT_3x11(
    T_XX,    T_YY,    T_SL,     XXXX,    XXXX, XXXX,     T_SL, KC_7, KC_8, KC_9, MT(MOD_RSFT, KC_0),
    T_ATH,   T_PRAM,  _______,  XXXX,    XXXX, XXXX,     T_YY, KC_4, KC_5, KC_6, MT(MOD_RSFT, KC_DEL),
    XXXX,    XXXX,    XXXX,     XXXX, _______, XXXX, _______,  KC_1, KC_2, KC_3, TD(T_DOTENT)
  ),

/* RAISE LAYER
 * ,----------------------------------------------------------------------------.
 * |   !  |   @  |   #  |   $  |   %  |      |   ^  |   &  |   *  |   (  |   )  |
 * |   1  |   2  |   3  |   4  |   5  |      |   6  |   7  |   8  |   9  |   0  |
 * | ____ | ____ | ____ | ____ | ____ |      | ____ | ____ |  Alt | Ctrl | Shift|
 * |------+------+------+------+------+------+------+------+------+------+------|
 * |      |   ~  |   _  |   +  |   {  |      |   _  |  |   |   :  |   "  |      |
 * |  TAB |   `  |   -  |   =  |   [  |      |   -  |  \   |   ;  |   '  | Del  |
 * | Shift| ____ | ____ | AltGr| OSkey|      | ____ | AltGr| ____ | ____ | Shift|
 * | -----+------+------+------+------+------|------+------+------+------+------|
 * |      |      |      |      |      |      | XXXX |   >  |   ?  |      |      | 
 * |      |BackSp|  Del | Enter|      |      | XXXX |   .  |   /  | Enter|      | 
 * |      | Ctrl |  Alt | ____ | ____ |      | XXXX |  Alt | Ctrl | Shift|      | 
 * '----------------------------------------------------------------------------'       
 */
  [_RAISE] = LAYOUT_3x11(
    KC_1, KC_2, KC_3, KC_4, KC_5, _______, KC_6, KC_7, MT(MOD_LALT, KC_8), MT(MOD_RCTL,KC_9), MT(MOD_RSFT, KC_0),
    TBSHFT, KC_GRV, KC_MINS, MT(MOD_RALT, KC_EQL), MT(MOD_LGUI, KC_LBRC), _______, T_UMIN, MT(MOD_RALT, KC_BSLS), KC_SCLN, KC_QUOT, MT(MOD_RSFT, KC_DEL),
    KC_LEFT, MT(KC_LCTL, KC_BSPC), MT(KC_LALT, KC_DEL), KC_ENT, _______, XXXX, _______, MT(MOD_LALT, KC_DOT), MT(MOD_RCTL, KC_SLSH), MT(MOD_RSFT, KC_ENT), KC_RGHT
  ),
   
/* ADJUST LAYER  (LOWER + RAISE)
 * ,----------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |
 * | BOOT |      |      |      |      |      |      |      |      |      |CALTDEL|
 * |      | ____ | ____ | ____ | ____ |      | ____ | ____ | ____ | ____ | ____ |
 * |------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |
 * |  TAB |      |      |      |      |      |      |      |      |      | Del  |
 * | Shift| ____ | ____ | ____ | ____ |      | ____ | ____ | ____ | ____ | Shift|
 * | -----+------+------+------+------+------|------+------+------+------+------|
 * |      |      |      |      | XXXX |      | XXXX |      |      |      |      | 
 * |      |      |      |      | XXXX |      | XXXX |      |      |      |  .   | 
 * |      |      |      |      | XXXX |      | XXXX | ____ | ____ | ____ | Enter| 
 * '----------------------------------------------------------------------------'       
 */
  [_ADJUST] = LAYOUT_3x11(
    QK_BOOT,              XXXX, XXXX, XXXX, XXXX,    XXXX, XXXX,    XXXX, XXXX, XXXX, CALTDEL,
    TBSHFT, XXXX, XXXX, XXXX, XXXX,    XXXX, XXXX,    XXXX, XXXX, XXXX, MT(MOD_RSFT, KC_DEL),
    XXXX,                 XXXX, XXXX, XXXX, _______, XXXX, _______, XXXX, XXXX, XXXX, MT(KC_ENT, KC_DOT)
  ),

/* EXTRAS LAYER
 * ,----------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |
 * |  !   |      |      |      |      |      |  /\  |      |      |      |   ;  |
 * |      | ____ | ____ | ____ | ____ |      | ____ | ____ | ____ | ____ | ____ |
 * |------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |
 * |SHIFT |      |      |EXTRAS|      |      |      |      |      |      |   '  |
 * |      | ____ | ____ | ____ | ____ |      | ____ | ____ | ____ | ____ | ____ |
 * | -----+------+------+------+------+------|------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      | 
 * |      |      |      |      |      |      |      |      |   ,  |   .  |   ?  | 
 * |      |      |      |      |      |      |      | ____ | ____ | ____ | ____ | 
 * '----------------------------------------------------------------------------'       
 */
  [_EXTRAS] = LAYOUT_3x11(
    KC_EXLM,  XXXX, XXXX, XXXX, XXXX, XXXX, TD(T_SL), XXXX, XXXX,      XXXX,   KC_SCLN,
    KC_LSFT,     XXXX, XXXX, XXXX, XXXX, XXXX, XXXX,     XXXX, XXXX,      XXXX,   KC_QUOT,
    XXXX,     XXXX, XXXX, XXXX, XXXX, XXXX, XXXX,     XXXX, KC_COMM,   KC_DOT, KC_QUES
  ),


/* FUNCTION LAYER
 * ,----------------------------------------------------------------------------.
 * |1COPY |      |      |      |      |      |      |      |      |      |      |
 * |2PASTE| CLIP |  SS  |      |      |      |  / \ |      |  UP  |      |DELETE|
 * |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |
 * |  TAB | M05  | M06  | M07  | M08  |      |      | LEFT | DOWN | RIGHT| UP   |      
 * | Shift|      |      |      |      |      |      |      |      |      | RIGHT|
 * |------+------+------+------+------+------+------+------+------+------+------|
 * | XXXX |      |      |      |      |      |      |      |      |      |      |  
 * | XXXX | M01  | M02  | M03  | M04  |      |      |   ?  |   ,  |   .  | DOWN |
 * | XXXX |      |      |      |      |      |      |   !  | ____ | ____ | LEFT |
 * '----------------------------------------------------------------------------'       
 */

  [_FN] = LAYOUT_3x11(
    TD(T_CP),             CLIP,  SS,    XXXX,  XXXX, XXXX,  TD(T_SL), XXXX,     KC_UP,   XXXX,    KC_DEL,
    TBSHFT, M05,   M06,   M07,   M08,  XXXX,  XXXX,     KC_LEFT,  KC_DOWN, KC_RGHT, TD(T_UR),
    _______,              M01,   M02,   M03,   M04,  XXXX,  XXXX,     XXXX,     XXXX,    XXXX,    TD(T_DL)
  ),


/* SYMBOLS
 * ,----------------------------------------------------------------------------.
 * |      |      |      |      | XXXX |      | XXXX |      |      |      |      |
 * |   $  |   ^  |   <  |   >  | XXXX |      | XXXX |   |  |   [  |   ]  |   -  |
 * |      |      |      |      | XXXX |      | XXXX |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |
 * |   %  |   :  |   ;  |   +  |   =  |      |      |      |   (  |   )  |   _  |
 * |      |      |      |      |      |      |      |      |      |      |      |
 * | -----+------+------+------+------+------|------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      | 
 * |   &  |   '  |   "  |   *  |   #  |      |   !  |   ?  |   /  |   \  |   @  | 
 * |      |      |      |      |      |      |      |      |      |      |      | 
 * '----------------------------------------------------------------------------'
 * 
 *   http://www.keyboard-layout-editor.com/#/gists/fcc6c759cf335abf31f6c200db3b9aca
 */
  [_SYMBOLS] = LAYOUT_3x11(
    KC_DLR, KC_CIRC, KC_LABK, KC_RABK, XXXX,     _______, XXXX, KC_PIPE, KC_LBRC, KC_RBRC, KC_MINS,
    KC_PERC, KC_COLN, KC_SCLN, KC_PLUS, KC_EQL,  _______, XXXX, XXXX, KC_LPRN, KC_RPRN, KC_UNDS,
    KC_AMPR, KC_QUOT, KC_DQUO, KC_ASTR, KC_HASH, _______, KC_EXLM, KC_QUES, KC_SLSH, KC_BSLS, KC_AT
  ),


    
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

void matrix_init_user(void) {
  // eeconfig_init(); // reset keyboard to a standard default state; useful when new releases messup with eeprom values
  // set num lock on at start (for numonly layer to work)
  if (!host_keyboard_led_state().num_lock) {
      tap_code(KC_NUM_LOCK);
  }
}

void matrix_scan_user(void) {
}


// Macro Definitions
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {

   case M01: 
        if (record->event.pressed) {
            SEND_STRING("//a11");
        }
	      break;
    
   case M02: 
        if (record->event.pressed) {
            SEND_STRING("//a12");
        }
	      break;

    case M03: 
        if (record->event.pressed) {
            SEND_STRING("//a08");
        }         
	      break;

    case M04: 
        if (record->event.pressed) {
            SEND_STRING("//a09");
        }
	      break;
    
    case M05: 
        if (record->event.pressed) {
            SEND_STRING("//th");
       }
	     break;
  
    case M06: 
        if (record->event.pressed) {
            SEND_STRING("//re");
      }
	    break;
    
    case M07: 
        if (record->event.pressed) {
	          SEND_STRING("//yw");
        }
	      break;
    
    case M08: 
        if (record->event.pressed) {
            tap_random_base64();
        }
	      break;
    
   case CK_TRIPLEZERO:
      if (record->event.pressed) {
        SEND_STRING("000");
      } // else { when released }
      break;
  }
  return true;
  };

/*
void keyboard_pre_init_user(void) {
  // Set our LED pins as output
  setPinOutput(D5);
  setPinOutput(B0);
}

bool led_update_user(led_t led_state) {
    writePin(D5, !led_state.num_lock);
    writePin(B0, !led_state.caps_lock);
    return false; // prevent keyboard from processing state
}
*/ 

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_HOME] = { ENCODER_CCW_CW(LCTL(KC_V), LCTL(KC_C)) },
    [_SYMBOLS] = { ENCODER_CCW_CW(KC_SPC, KC_ENT) },                            
    [_RAISE] = { ENCODER_CCW_CW(KC_SPC, KC_ENT) },
    [_LOWER] = { ENCODER_CCW_CW(KC_SPC, KC_ENT) },
    [_ADJUST] = { ENCODER_CCW_CW(KC_SPC, KC_ENT) },
    [_EXTRAS] = { ENCODER_CCW_CW(KC_SPC, KC_ENT) },
    [_FN] = { ENCODER_CCW_CW(KC_SPC, KC_ENT) },
};
 

oled_rotation_t oled_init_user(oled_rotation_t rotation){   
    return OLED_ROTATION_270;
}

/*
bool oled_task_user(void) {
    uint8_t modifiers = get_mods() | get_oneshot_mods();

    oled_set_cursor(0, 11); 
    oled_write_P(PSTR("SHIFT"), (modifiers & MOD_MASK_SHIFT) || is_caps_word_on());
    oled_write_P(PSTR("CNTRL"), (modifiers & MOD_MASK_CTRL));

    return true;
}
*/

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("LAYER\n-----\n"), false);

    switch (get_highest_layer(layer_state)) {
        case _LOWER:
            oled_write_P(PSTR("LOWER"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("RAISE"), false);
            break;
        case _EXTRAS:
            oled_write_P(PSTR("EXTRA"), false);
            break;
        case _FN:
            oled_write_P(PSTR("FUNCT"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR(" ADJ "), false);
            break;
        case _SYMBOLS:
            oled_write_P(PSTR("SYMB"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("HOME"), false);
    }

// Host Keyboard LED Status
   // led_t led_state = host_keyboard_led_state();
   // oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
   // oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
   // oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
  
 return false;
}
#endif

