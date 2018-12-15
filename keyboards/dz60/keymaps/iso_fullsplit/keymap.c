#include QMK_KEYBOARD_H

// Helpful defines
#define _______ KC_TRNS
#define XXXXXXX KC_NO


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* ISO UK 60 plus layout by jono, this is just my personal layout you could also split the backspace if you wanted too.
   *
   * ,-------------------------------------------------------------------------.
   * |Esc | 1  | 2  | 3  | 4  | 5  | 6  | 7  | 8  | 9  | 0  | -  | =  |Backsp  |
   * |-------------------------------------------------------------------------|
   * | Tab  | q  | w  | e  | r  | t  | y  | u  | i  | o  | p  | [  | ]  |enter |
   * |--------------------------------------------------------------------     |
   * |  Caps  | a  | s  | d  | f  | g  | h  | j  | k  | l  | ;  | '  | #  |    |
   * |-------------------------------------------------------------------------|
   * |Shft |bsls| z  | x  | c  | v  | b  | n  | m  | ,  | .  | /  | Shift |volU|
   * |-------------------------------------------------------------------------|
   * |Ctrl | Gui | Alt |  Space   | FN  |   Space    |Lft |Dwn |Up  | Rgt |volD|
   * `-------------------------------------------------------------------------'
   */
 [0] = LAYOUT_60_c_iso(
	//  1          2          3          4          5          6          7          8          9          10         11         12         13         14       15
	    KC_ESC,    KC_1,      KC_2,      KC_3,      KC_4,      KC_5,      KC_6,      KC_7,      KC_8,      KC_9,      KC_0,      KC_MINS,   KC_EQL,    KC_NO,   KC_BSPC,
            KC_TAB,    KC_Q,      KC_W,      KC_E,      KC_R,      KC_T,      KC_Y,      KC_U,      KC_I,      KC_O,      KC_P,      KC_LBRC,   KC_RBRC,
            KC_CAPS,   KC_A,      KC_S,      KC_D,      KC_F,      KC_G,      KC_H,      KC_J,      KC_K,      KC_L,      KC_SCLN,   KC_QUOT,   KC_NUHS,   KC_ENT,          
            KC_LSFT,   KC_BSLS,   KC_Z,      KC_X,      KC_C,      KC_V,      KC_B,      KC_N,      KC_M,      KC_COMM,   KC_DOT,    KC_SLSH,   KC_RSFT,   KC_AUDIO_VOL_UP,
            KC_LCTRL,  KC_LGUI,   KC_LALT,   KC_SPC,    MO(1),     KC_SPC,    KC_LEFT,   KC_DOWN,   KC_UP,     KC_RIGHT,  KC_AUDIO_VOL_DOWN
 ),

 [1] = LAYOUT_60_c_iso(
  	//  1          2          3          4          5          6          7          8          9          10         11         12         13         14       15
	    KC_GRV,    KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,     KC_F6,     KC_F7,     KC_F8,     KC_F9,     KC_F10,    KC_F11,    KC_F12,    KC_NO,   KC_DEL,
            _______,   KC_MS_BTN1,KC_MS_UP,  KC_MS_BTN2,_______,   _______,   _______,   _______,   _______,   _______,   KC_PSCR,   _______,   _______,
            RGB_TOG,   KC_MS_LEFT,KC_MS_DOWN,KC_MS_RIGHT,_______,  _______,   _______,   KC_LEFT,   KC_DOWN,   KC_UP,     KC_RIGHT,  _______,   _______,   RESET,
            _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   KC_HOME,   KC_PGDOWN, KC_PGUP,   KC_END,    _______,   _______,
            _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______
 ),

};

