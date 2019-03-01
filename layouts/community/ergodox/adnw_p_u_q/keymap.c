#include QMK_KEYBOARD_H
#include "keymap_german.h"


#define BASE 0 // default layer / VIM
#define ARW 1 // arrow layer / Terminal
#define DIAK 2 // diakritika layer
#define BRACK 3 // brackets layer
#define SYMBOLS 4 // symbols
#define MEDIA 5 // media keys / Mouse-Navigation


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer / VIM 
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |   1  |   2  |   3  |   4  |   5  |      |           |      |   6  |   7  |   8  |   9  |   0  | Media  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   P  |   U  | Dia-L|   ,  |   Q  |      |           |      |   V  |   C  |   L  |   M  |   B  |        |
 * |--------+------+------+------+------+------| G    |           | gg   |------+------+------+------+------+--------|
 * | Symbols|   H  |   I  |   E  |   A  |   O  |------|           |------|   D  |   T  |   R  |   N  |   S  | ARW    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | LShift |   K  |   Y  |   .  |   '  |   X  |str-D |           |str-U |   J  |   G  |   Z  |   W  |   F  | RShift | 
 * * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | Ctrl |  Alt |      |      |      |                                       |   H  |   J  |   K  |   L  | Ctrl | 
 *   `----------------------------------'                                       `----------------------------------'
 *                    LShift is Tab on Click                                                                                             
 *                                                                                                            
 *                                        ,-------------.       ,-------------.
 *                                        | ^    | /    |       | ?    | $    |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      |str+a |       |str+c |        |      |
 *                                 | Brack| Space|------|       |------|  Enter |BSpace| 
 *                                 | -Lay |/shift| Tab/ |       |      |        |      |
 *                                 |      |	 |  GUI	|       | ESC  |        |      |
 *                                 `--------------------'       `----------------------'
 *                                 GUI is one shot
 *                                 str + a is for tmux etc.
 * 				   str + c is for stopping programs
 */
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_NO, KC_1, KC_2, KC_3, KC_4, KC_5, KC_NO,
        TG(SYMBOLS), DE_P, DE_U, OSL(DIAK), DE_COMM, DE_Q, LSFT(DE_G),
        OSL(SYMBOLS), DE_H, DE_I, DE_E, DE_A, DE_O,
     	SFT_T(KC_TAB), DE_K, DE_Y, DE_DOT, DE_QUOT, DE_X, LCTL(DE_D),
        KC_LCTRL, KC_LALT, KC_NO, KC_NO, KC_NO,
        

	// left hand thumb-cluster
                        DE_CIRC, DE_SLSH,
		                 LCTL(DE_A),
	OSL(BRACK), SFT_T(KC_SPACE), GUI_T(KC_TAB),


        // right hand
        KC_NO, KC_6, KC_7, KC_8, KC_9, KC_0, TG(MEDIA),
        DE_G, DE_V, DE_C, DE_L, DE_M, DE_B, KC_NO,
                  DE_D, DE_T, DE_R, DE_N, DE_S, TG(ARW),
        LCTL(DE_U), DE_J, DE_G, DE_Z, DE_W, DE_F, KC_RSFT,
                         KC_H, KC_J, KC_K, KC_L, KC_RCTRL,

	// right thumb-cluster
        DE_QST, DE_DLR,
        LCTL(DE_C),
        KC_ESCAPE, KC_ENTER, KC_BSPACE
),


/* Keymap 1: Arrow Layer / Terminal
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      |      |      |      |      |  	     |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |P-Down|           |P-Up  |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       | Left | Bot  | Top  | Right|      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | Home |      |       |      | End  |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// Arrows
[ARW] = LAYOUT_ergodox(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGDOWN,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_HOME, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,

       // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       	         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_PGUP,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                          KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_TRNS,
       KC_TRNS, KC_END,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS 
),


/* Keymap 2: Diakritika Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |   Ü  |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |   Ä  |   Ö  |------|           |------|      |      |      |      |   ß  |  	     |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// Diakritika
[DIAK] = LAYOUT_ergodox(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, DE_UE, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, DE_AE, DE_OE,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,

       // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       	         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, DE_SS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS 
),


/* Keymap 3: Brackets Layer 
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |   (  |   {  |   [  |      |------|           |------|      |  ]   |  }   |  )   |      |  	     |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// BRACK
[BRACK] = LAYOUT_ergodox(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, DE_LPRN, DE_LCBR, DE_LBRC, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,

       // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       	         KC_TRNS, DE_RBRC, DE_RCBR, DE_RPRN, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS 
),


/* Keymap 4: Symbol Layer
 *
 *
 * Original:
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |           | F7   |  F8  |  F9  |  F10 |  F11 |  F12 |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |  ²   |  °   |  ~   |  @   |  !   |      |           |      |  ?   |  &   |  §   |  "   |  ³   |        |
 * |--------+------+------+------+------+------|   (  |           |  )   |------+------+------+------+------+--------|
 * |        |  ´   |  '   |  :   |  ^   |  <   |------|           |------|  >   |  $   |  ;   |  |   |  `   |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |  €   |  +   |  =   |  *   |  /   |   {  |           |  }   |  \   |  %   |  #   |  -   |  _   |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 */
// SYMBOLS
[SYMBOLS] = LAYOUT_ergodox(
       // left hand
       KC_TRNS,  KC_F1,  KC_F2,   KC_F3,   KC_F4,   KC_F5,  KC_F6, //DE_LBRC,
       KC_TRNS,DE_SQ2, DE_RING, DE_TILD, DE_AT,   DE_EXLM, DE_LPRN,
       KC_TRNS,DE_ACUT,DE_QUOT, DE_COLN, DE_CIRC, DE_LESS,
       KC_TRNS,DE_EURO,DE_PLUS, DE_EQL,  DE_ASTR, DE_SLSH, DE_LCBR,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,

                                       KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                               KC_TRNS,KC_TRNS,KC_TRNS,

       // right hand
       //DE_RBRC, 
       KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,  KC_F12,  KC_TRNS,
       DE_RPRN, DE_QST,  DE_AMPR, DE_PARA, DE_DQOT,  DE_SQ3,  KC_TRNS,
                DE_MORE, DE_DLR,  DE_SCLN, DE_PIPE,  DE_GRV,  KC_TRNS,
       DE_RCBR, DE_BSLS, DE_PERC, DE_HASH, DE_MINS,  DE_UNDS, KC_TRNS,
                         KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,

       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),

/* Keymap 5: Numbers
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      | Num  |  /   |  *   |  -     |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      | 7    |  8   |  9   |  +     |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      |      | 4    |  5   |  6   |  +     |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      | 1    |  2   |  3   | Enter  |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |  0   | ,    |      |      | Enter|
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
// NUMBERS
[NUMBERS] = LAYOUT_ergodox(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,

       // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_7, KC_8, KC_9, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_4, KC_5, KC_8, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_1, KC_2, KC_3, KC_TRNS,
                          KC_0, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS 
),


*/

/* Keymap 6: Media and mouse keys 
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        | Sleep|      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        | Wake |      |      |      |      |------|           |------|      |MsLeft|MsDown| MsUp |MsRght|        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |  Mute| VolDn| VolUp|                                       |  Play| Prev | Next | Stop |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |  Lclk|------|       |------|Rclk  |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
[MEDIA] = LAYOUT_ergodox(
       KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
       KC_TRNS, KC_SLEP, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
       KC_TRNS, KC_WAKE, KC_NO, KC_NO, KC_NO, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
       KC_TRNS, KC_TRNS, KC_MUTE, KC_VOLD, KC_VOLU,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                 KC_TRNS, KC_BTN1, KC_TRNS,
    // right hand
       KC_TRNS,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,
       KC_TRNS,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,
                 KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_TRNS,
       KC_TRNS,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,
                          KC_MPLY, KC_MPRV, KC_MNXT, KC_MSTP, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_BTN2, KC_TRNS
),
};

// Runs constantly in the background, in a loop.
void matrix_scan_user_keyboard(void) {
    ergodox_board_led_on();
    ergodox_led_all_on();
}
