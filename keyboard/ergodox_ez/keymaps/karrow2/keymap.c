#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  ESC   | 1  ! | 2  @ | 3  # | 4  $ | 5  % | -  _ |           |=    +| 6  ^ | 7  & | 8  * | 9  ( | 0  ) |APPS/ALT|
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | `    ~ |  Q   |  W   |  E   |  R   |  T   |      |           |      |  Y   |  U   |  I   |  O   |  P   | \ /CMD |
 * |--------+------+------+------+------+------|  (   |           |   )  |------+------+------+------+------+--------|
 * |TEMP SYM|  A   |  S   |  D   |  F   |  G   |------|           |------|  H   |  J   |  K   |  L   | ;  : | ' /CTRL|
 * |--------+------+------+------+------+------|TOGGLE|           |TOGGLE|------+------+------+------+------+--------|
 * | LSHIFT |  Z   |  X   |  C   |  V   |  B   |LAY 1 |           |LAY 2 |  N   |  M   | ,  < | .  > |  UP  | RSHIFT |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | CTRL |CMD WD| ALT  |CAP LK| /  ? |                                       | [  { | ]  } | LEFT | DOWN |RIGHT |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,---------------.
 *                                        | HOME | END  |       |PG UP | DELETE |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | SHIFT|       |PG DN |        |      |
 *                                 | Space| TAB  |------|       |------|  BACK  |ENTER |
 *                                 |      |      | CTRL |       |INSERT| SPACE  |      |
 *                                 `--------------------'       `----------------------'Arrows+TraditionalShift
 */

 [BASE] = KEYMAP(  // layer 0 : default
        // left hand
        KC_ESC,  KC_1,    KC_2,   KC_3,   KC_4,   KC_5, KC_MINS,
        KC_GRV,  KC_Q,    KC_W,   KC_E,   KC_R,   KC_T, KC_LPRN,
        KC_FN1,  KC_A,    KC_S,   KC_D,   KC_F,   KC_G,
        KC_LSFT, KC_Z,    KC_X,   KC_C,   KC_V,   KC_B, TG(SYMB),
        KC_LCTL, KC_LGUI, KC_LALT,KC_CAPS,KC_SLSH,
                                                         
                                                  KC_HOME,KC_END,
                                                          KC_LSFT,
                                           KC_SPC,KC_TAB, KC_LCTL,
        

        // right hand
                 KC_EQL,   KC_6, KC_7,    KC_8,    KC_9,    KC_0,    ALT_T(KC_APP),
                 KC_RPRN,  KC_Y, KC_U,    KC_I,    KC_O,    KC_P,    GUI_T(KC_BSLS),
                           KC_H, KC_J,    KC_K,    KC_L,    KC_SCLN, CTL_T(KC_QUOT),
                 TG(MDIA), KC_N, KC_M,    KC_COMM, KC_DOT,  KC_UP,   KC_RSFT,
                                 KC_LBRC, KC_RBRC, KC_LEFT, KC_DOWN, KC_RIGHT,
             
                 KC_PGUP,KC_DELT,
                 KC_PGDN,
                 KC_INS, KC_BSPC,KC_ENT
    ),



 /* Keymap 1: Symbol Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |  <   |           |   >  |  F6  |  F7  |  F8  |  F9  | F10  |  F11   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |  !   |  @   |  #   |   $  |  %   |      |           |      |  ^   |  7   |  8   |  9   |  *   |   /    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |  '   |  "   |  {   |   }  |  ;   |------|           |------|  :   |  4   |  5   |  6   |  +   | -   _  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        | \  | |  &   |  [   |   ]  |  ?   |      |           |      | CALC |  1   |  2   |  3   |      |   =    |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |  ,   | F12  |                                       |  0   |  .   |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,---------------.
 *                                        |      |      |       |      |        |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      |      |       |      |        |      |
 *                                 |      |      |------|       |------|        |      |
 *                                 |      |      |      |       |      |        |      |
 *                                 `--------------------'       `----------------------'
 */
 [SYMB] = KEYMAP(
       // left hand
       KC_TRNS, KC_F1,   KC_F2,         KC_F3,   KC_F4,   KC_F5,         LSFT(KC_COMM),
       KC_TRNS, KC_EXLM, KC_AT,         KC_HASH, KC_DLR,  KC_PERC,       KC_TRNS,
       KC_TRNS, KC_QUOT, LSFT(KC_QUOT), KC_LCBR, KC_RCBR, KC_SCLN,
       KC_TRNS, KC_BSLS, KC_AMPR,       KC_LBRC, KC_RBRC, LSFT(KC_SLSH), KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS,       KC_COMM, KC_F12,
                                                         
                                                         KC_TRNS, KC_TRNS,
                                                                  KC_TRNS,
                                                KC_TRNS, KC_TRNS, KC_TRNS,
       

       // right hand
       LSFT(KC_DOT), KC_F6,   KC_F7, KC_F8,  KC_F9,  KC_F10,  KC_F11,
       KC_TRNS,      KC_CIRC, KC_7,  KC_8,   KC_9,   KC_ASTR, KC_SLSH,
                     KC_COLN, KC_4,  KC_5,   KC_6,   KC_PLUS, KC_MINS,
       KC_TRNS,      KC_CALC, KC_1,  KC_2,   KC_3,   KC_TRNS, KC_EQL,
                              KC_0,  KC_DOT, KC_TRNS,KC_TRNS, KC_TRNS,
       
       KC_TRNS,KC_TRNS,
       KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS
),



/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |  BB  |<-Browser->|  BF  |      |      |      |      |      |  favs  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |Pause Br|P Scrn|      | MsUp | 4clk |      |      |           |      |      |      | Stop |      | find |Web Src |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght| 5clk |------|           |------|      | Prev | Play | Next |      |refresh |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      | Lclk | 3clk | Rclk |      |      |           |      |      |VolDn | Mute |VolUp |      | paste  |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       | cut  | copy |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      | 
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[MDIA] = KEYMAP(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_WBAK,
       KC_PAUS, KC_PSCR, KC_TRNS, KC_MS_U, KC_BTN4, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_BTN5,
       KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN3, KC_BTN2, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                                   
                                                   KC_TRNS, KC_TRNS,
                                                            KC_TRNS,
                                          KC_TRNS, KC_TRNS, KC_TRNS,
    
    
    // right hand
       KC_WFWD,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_WFAV,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_MSTP, KC_TRNS, KC_FIND, KC_WSCH,
                 KC_TRNS, KC_MPRV, KC_MPLY, KC_MNXT, KC_TRNS, KC_WREF,
       KC_TRNS,  KC_TRNS, KC_VOLD, KC_MUTE, KC_VOLU, KC_TRNS, KC_PASTE,
                          KC_CUT,  KC_COPY, KC_TRNS, KC_TRNS, KC_TRNS,
       
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
        if (record->event.pressed) {
          register_code(KC_RSFT);
        } else {
          unregister_code(KC_RSFT);
        }
        break;
      }
    return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void * matrix_init_user(void) {

};

// Runs constantly in the background, in a loop.
void * matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      // TODO: Make this relevant to the ErgoDox EZ.
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        default:
            // none
            break;
    }

};
