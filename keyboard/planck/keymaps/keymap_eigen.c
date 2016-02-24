#include "keymap_common.h"
#include "backlight.h"
#include "debug.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = { /* QWERTY    
    * 0:Qwerty
    * ,-----------------------------------------------------------------------.
    * |Esc  | q   | w   | f   | p   | g   | j   | l   | u   | y   | ;   | BS  |
    * |-----------------------------------------------------------------------|
    * |BS   | a   | r   | s   | t   | d   | h   | n   | e   | i   | o   |  '  |
    * |-----------------------------------------------------------------------|
    * |Shift| z   | x   | c   | v   | b   | k   | m   |,   | .   | /   | Enter|
    * |-----------------------------------------------------------------------|
    * |FN4  | LCTL| LGUI| LALT|Lower|   Space   |Raise|Left |Down | Up  |Right|
    * `-----------------------------------------------------------------------'
    */
  {KC_ESC,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN,   KC_BSPC},
  {KC_TAB,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,  KC_QUOT},
  {FUNC(8), KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT},
  {KC_LCTL, KC_LCTL, FUNC(5), KC_LALT, FUNC(2), FUNC(3), FUNC(3), FUNC(1),   KC_LEFT, KC_DOWN, KC_UP,  KC_RGHT}
                                                // Space is repeated to accommadate for both spacebar wiring positions
},
[1] = { /* Gaming
    * 1: Gaming Layer
    * ,-----------------------------------------------------------------------.
    * | ESC |     |  1  |  2  |  3  |  4  |     |     |     | /RC |     |     |
    * |-----------------------------------------------------------------------|
    * |     |  5  |  6  |  7  |  W  |  8  |  9  |     |     |     |     |     |
    * |-----------------------------------------------------------------------|
    * |     |  0  |  -  |  A  |  S  |  D  |  =  |     |     |     |     |     |
    * |-----------------------------------------------------------------------|
    * |QWERT|     |LCTRL| LSFT| LALT|   Space   | TAB |     |     |Raise|     |
    * `-----------------------------------------------------------------------'
    */
  {KC_ESC, KC_NO, KC_1, KC_2, KC_3, KC_4, KC_NO, KC_NO, KC_NO,   M(1), KC_NO, KC_NO},
  {KC_NO,   KC_5, KC_6, KC_7, KC_W, KC_8,  KC_9, KC_NO, KC_NO,  KC_NO, KC_NO, KC_NO},
  {KC_NO,   KC_0, KC_MINS, KC_A, KC_S, KC_D,  KC_EQL, KC_NO, KC_NO,  KC_NO, KC_NO, KC_NO},
  {FUNC(9), KC_NO, KC_LCTL, KC_LSFT, KC_LALT, KC_SPC, KC_SPC, KC_TAB, KC_NO, KC_NO, FUNC(1), KC_NO}
},
[2] = { /* Raise
    * 2: fn Right/Raise layer
    * The top row are standard numbers, 1-9, and minus and equals.
    * Middle 2 rows add symbols back.
	* Bottom row changes arrow to Home, Page Up, Page Down, and End.
    * ,-----------------------------------------------------------------------.
    * |  `  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  BS |
    * |-----------------------------------------------------------------------|
    * |     | Game|QWERT|     |     |     |     |  -  |  =  |  [  |  ]  |  \  |
    * |-----------------------------------------------------------------------|
    * |     |     |     |     |     |     |     |     |     |     |     |     |
    * |-----------------------------------------------------------------------|
    * |     |     |     |     |     |   Space   |     |Home |PgDn |PgUp | End |
    * `-----------------------------------------------------------------------'
    */
  { KC_GRV,    KC_1,    KC_2,     KC_3,      KC_4,    KC_5,     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC},
  {KC_TRNS, FUNC(7), FUNC(6),    RESET,   KC_TRNS, KC_TRNS,  KC_TRNS, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS},
  {KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,   KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS, KC_TRNS},
  {KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,   KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,   KC_HOME, KC_PGDN, KC_PGUP, KC_END}
},
[3] = { /* Lower
    * 3: Symbols Left/Lower layer
	* Top row is number symbols.
	* Adds alt symbbols for brackets, etc.
	* Bottom row is media control.
    * ,-----------------------------------------------------------------------.
    * |  ~  |  !  |  @  |  #  |  $  |  %  |  ^  |  &  |  *  |  (  |  )  |  BS |
    * |-----------------------------------------------------------------------|
    * |     |     |     |     |     |     |     |  _  |  +  |  {  |  }  |  |  |
    * |-----------------------------------------------------------------------|
    * |     |     |     |     |     |     |     |     |     |     |     |     |
    * |-----------------------------------------------------------------------|
    * |     |PrevT|NextT|     |     |     |     |     |Mute |Vol- |Vol+ | P/P |
    * `-----------------------------------------------------------------------'
    */
  {S(KC_GRV), S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_5), S(KC_6), S(KC_7), S(KC_8), S(KC_9), S(KC_0), KC_BSPC},
  {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, S(KC_MINS), S(KC_EQL),  S(KC_LBRC), S(KC_RBRC), S(KC_BSLS)},
  {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS},
  {KC_TRNS, KC_MPRV, KC_MNXT, KC_TRNS, FUNC(2),   KC_TRNS,   KC_TRNS,   KC_TRNS, KC_MUTE, KC_VOLD, KC_VOLU, KC_MPLY}
},
[4] = { /* TENKEY
    * 4: Numpad layer
    * ,-----------------------------------------------------------------------.
    * |     | Num7| Num8| Num9|     |     |CALC |     |     |     |     |     |
    * |-----------------------------------------------------------------------|
    * |     | Num4| Num5| Num6|     |     |     |     |     |     |     |     |
    * |-----------------------------------------------------------------------|
    * |     | Num1| Num2| Num3|     |     |     |     |     |     |     |     |
    * |-----------------------------------------------------------------------|
    * |     | Num0| Num0| Num.|     |     |     |     |     |     |     |     |
    * `-----------------------------------------------------------------------'
    */
  {KC_TRNS, KC_KP_7, KC_KP_8, KC_KP_9,   KC_TRNS, KC_TRNS,KC_CALC,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS},
  {KC_TRNS, KC_KP_4, KC_KP_5, KC_KP_6,   KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS},
  {KC_TRNS, KC_KP_1, KC_KP_2, KC_KP_3,   KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS},
  {KC_TRNS, KC_KP_0, KC_KP_0, KC_KP_DOT, KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS},
},
[5] = { /* Funtion Keys
    * 5: Function
	* Backlight control at Arrows
    * ,-----------------------------------------------------------------------.
    * | F1  | F2  | F3  | F4  |F5   | F6  | F7  | F8  | F9  | F10 | F11 | F12 |
    * |-----------------------------------------------------------------------|
    * |     |     |     |     |     |     |     |     |     |     |     |     |
    * |-----------------------------------------------------------------------|
    * |     |     |     |     |     |     |     |     |     |     |     |     |
    * |-----------------------------------------------------------------------|
    * |     |     |     |     |     |     |     |     |     |Light|BL DN|BL UP|
    * `-----------------------------------------------------------------------'
    */
  {KC_FN1,   KC_FN2,   KC_FN3,   KC_FN4,    KC_FN5,  KC_FN6,   KC_FN7,  KC_FN8,    KC_FN9,   KC_FN10,   KC_FN11, KC_FN12},
	{KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS, KC_TRNS},
	{KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS, KC_TRNS},
	{KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,   KC_TRNS,   BL_TOGG,   BL_DEC, BL_INC},
},
[6] = { /* In-Game QWERTY    
    * 0:Qwerty
    * ,-----------------------------------------------------------------------.
    * |     | q   | w   | e   | r   | t   | y   | u   | i   | o   | p   | BS  |
    * |-----------------------------------------------------------------------|
    * |     | a   | s   | d   | f   | g   | h   | j   | k   | l   |     |  "  |
    * |-----------------------------------------------------------------------|
    * |Shift| z   | x   | c   | v   | b   | n   | m   |  ,  |  .  |  /  |Enter|
    * |-----------------------------------------------------------------------|
    * |     |     |     |     |     |   Space   |     |     |     |     |     |
    * `-----------------------------------------------------------------------'
    */
  {KC_TRNS,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,   KC_BSPC},
  {KC_TRNS,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_TRNS,  S(KC_QUOT)},
  {FUNC(8), KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT},
  {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS}
                                                // Space is repeated to accommadate for both spacebar wiring positions
},
[7] = { /* More Functions
    * 7: Function
	* More Space Later
    * ,-----------------------------------------------------------------------.
    * | F13 | F14 | F15 | F16 |F17  | F18 | F19 | F20 | F21 | F22 | F23 | F24 |
    * |-----------------------------------------------------------------------|
    * |     |     |     |     |     |     |     |     |     |     |     |     |
    * |-----------------------------------------------------------------------|
    * |     |     |     |     |     |     |     |     |     |     |     |     |
    * |-----------------------------------------------------------------------|
    * |     |     |     |     |     |     |     |     |     |     |     |     |
    * `-----------------------------------------------------------------------'
    */
  {KC_FN13,   KC_FN14,   KC_FN15,   KC_FN16,    KC_FN17,  KC_FN18,   KC_FN19,  KC_FN20,    KC_FN21,   KC_FN22,   KC_FN23, KC_FN24},
	{KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS, KC_TRNS},
	{KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS, KC_TRNS},
	{KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS, KC_TRNS},
},
};

const uint16_t PROGMEM fn_actions[] = {
        [1] = ACTION_LAYER_MOMENTARY(2),               // to RAISE
        [2] = ACTION_LAYER_MOMENTARY(3),               // to LOWER
        [3] = ACTION_LAYER_TAP_KEY(4,KC_SPC),          // to TENKEY
	[4] = ACTION_LAYER_MOMENTARY(5),               // to Function
	[5] = ACTION_LAYER_TAP_KEY(7,KC_LGUI),         // to More Functions
	
        [6] = ACTION_DEFAULT_LAYER_SET(0),             // QWERTY
        [7] = ACTION_DEFAULT_LAYER_SET(1),             // Gaming
	[8] = ACTION_MODS_TAP_KEY(MOD_LSFT, KC_CAPS),  //Shift on press, Caps on tap
	[9] = ACTION_LAYER_TAP_TOGGLE(6),              //QWERTY in game
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) 
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:   
        if (record->event.pressed) {
          register_code(KC_RSFT);
          backlight_step();
        } else {
          unregister_code(KC_RSFT);
        }
        break;
		case 1:
        return MACRODOWN(TYPE(KC_SLSH), TYPE(KC_R), TYPE(KC_C), TYPE(KC_ENT) , END);
      break;
      } 
    return MACRO_NONE;
};