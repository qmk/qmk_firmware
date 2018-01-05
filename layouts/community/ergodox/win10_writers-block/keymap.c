#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"
#include "wait.h"

#define BASE 0 // default layer  -  helpful for writing in Office-style word processors. 
#define SYMB 1 // symbol layer   -  NumPad, etc. - same as Ergodox EZ default but no EEPROM or Version key 
#define RIMW 2 // rimworld layer -  made for the game RimWorld, by Tynan Sylvester | feel free to remap for your favorite game!
#define MDIA 3 // media layer    -  mouse and music - close to Ergodox EZ default media layer

#define CO_PA M(0)                  // hold copy, tap paste

#define W_CUT    LCTL(KC_X)         // C-x Cut
#define W_COPY   LCTL(KC_C)         // C-c Copy
#define W_PASTE  LCTL(KC_V)         // C-v Paste
#define W_UNDO   LCTL(KC_Z)         // C-z Undo
#define W_FIND   LCTL(KC_F)         // C-v Find
#define W_CAD    LCTL(LALT(KC_DEL)) // one-tap ctrl-alt-del



//Tap Dance Declarations
enum {
  CAKEWARP,
  CTRLALTMDIA,
};

void cake_count (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 2) {         
    layer_on (SYMB);        //define double tap here
    layer_off (MDIA);
  } 
  else {    
    layer_off (SYMB);       //define single tap or hold here
    layer_off (MDIA);
  }
  if (state->count == 3) {         
     layer_on (RIMW);       //define triple tap here
     layer_off (MDIA);
  } 
  else {    
   	layer_off (RIMW);       //define single tap or hold here
	layer_off (MDIA);
    reset_tap_dance (state);
  }
}

void dance_cad_mdia_fin (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code (KC_LCTL);
    register_code (KC_LALT);
	register_code (KC_DEL);
  } else {
    layer_on (MDIA);
  }
}

void dance_cad_mdia_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (KC_DEL);
    unregister_code (KC_LALT);
	unregister_code (KC_LCTL);
  } else {
    ;
  }
}

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  // tap for Layer 0, tap twice to switch to symbol layer, and tap three times to switch to rimworld layer.
  [CAKEWARP] = ACTION_TAP_DANCE_FN(cake_count)
  // tap for ctrl-alt-del, tap twice for media layer
  ,[CTRLALTMDIA] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_cad_mdia_fin, dance_cad_mdia_reset)
  // Other declarations would go here, separated by commas, if you have them
};

//In Layer declaration, add tap dance item in place of a key code

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer - TD(one_tap, two_taps, three_taps...)
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   `    |   1  |   2  |   3  |   4  |   5  | 6    |           |  7   |   7  |   8  |   9  |   0  |   -  |   =    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | F12/L1 |   Q  |   W  |   E  |   R  |   T  |  {/[ |           |TD(L0 |   Y  |   U  |   I  |   O  |   P  |   \    | 
 * |--------+------+------+------+------+------|      |           |L1 L2)|------+------+------+------+------+--------|
 * |Caps/Win|   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |   '    |
 * |--------+------+------+------+------+------|  }/] |           TD(ctrl|------+------+------+------+------+--------|
 * |LShift/(|Z/Ctrl|   X  |   C  |   V  |   B  |      |           |altdel|   N  |   M  |   ,  |   .  |  /   |RShift/)|
 * `--------+------+------+------+------+-------------'           |L3)   |------+------+------+------+------+--------'
 * |  Undo  |  Cut |CopyPa| Meh  | LGui |                         '------|      | Enter| Left | Up   | Down | Right  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | Esc  | VolUp|       | F4   | Mute |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | VolDn|       | F5   |        |      |
 *                                 |Backsp|Delete|------|       |------|  Tab / |Space |
 *                                 |ace   |      | Find |       | Alt  |  CTRL  |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
          KC_GRV,         KC_1,         KC_2,         KC_3,        KC_4,   KC_5,   KC_6,
LT(SYMB, KC_F12),         KC_Q,         KC_W,         KC_E,        KC_R,   KC_T,   KC_LBRC,
  GUI_T(KC_CAPS),         KC_A,         KC_S,         KC_D,        KC_F,   KC_G,
         KC_LSPO,  CTL_T(KC_Z),         KC_X,         KC_C,        KC_V,   KC_B,   KC_RBRC,
          W_UNDO,        W_CUT,        CO_PA, MEH_T(KC_NO),     KC_LGUI,
                                                                         KC_ESC, KC_VOLU,
                                                                                 KC_VOLD,
                                                             KC_BSPC, KC_DELETE,  W_FIND,
        // right hand
                       KC_7,   KC_7,   KC_8,   KC_9,    KC_0,   KC_MINS,          KC_EQL,
               TD(CAKEWARP),   KC_Y,   KC_U,   KC_I,    KC_O,   KC_P,            KC_BSLS,
                               KC_H,   KC_J,   KC_K,    KC_L,   KC_SCLN,         KC_QUOT,
            TD(CTRLALTMDIA),   KC_N,   KC_M,   KC_COMM, KC_DOT, KC_SLSH,         KC_RSPC,
                                       KC_ENT, KC_LEFT, KC_UP,  KC_DOWN,        KC_RIGHT,
                      KC_F4,        KC_MUTE,
                      KC_F5,
                    KC_RALT, CTL_T(KC_TAB), KC_SPC
    ),

/* Keymap 1: Symbol Layer | No EEPROM Or Version keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |   xx |           | xx   |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   !  |   @  |   {  |   }  |   |  |      |           |TD(L0 |   Up |   7  |   8  |   9  |   *  |   F12  |
 * |--------+------+------+------+------+------|      |           |L1 L2)|------+------+------+------+------+--------|
 * |        |   #  |   $  |   (  |   )  |   `  |------|           |------| Down |   4  |   5  |   6  |   +  |   -    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   \  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |    . |   0  |   =  |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[SYMB] = LAYOUT_ergodox(
       // left hand
       KC_TRNS,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_NO,
       KC_TRNS,KC_EXLM,KC_AT,  KC_LCBR,KC_RCBR,KC_PIPE,KC_TRNS,
       KC_TRNS,KC_HASH,KC_DLR, KC_LPRN,KC_RPRN,KC_GRV,
       KC_TRNS,KC_PERC,KC_CIRC,KC_LBRC,KC_RBRC,KC_TILD,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                       KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                               KC_TRNS,KC_TRNS,KC_TRNS,
       // right hand
         KC_NO, KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,
       KC_TRNS, KC_UP,   KC_7,   KC_8,    KC_9,    KC_ASTR, KC_F12,
                KC_DOWN, KC_4,   KC_5,    KC_6,    KC_PLUS, KC_MINS,
       KC_TRNS, KC_AMPR, KC_1,   KC_2,    KC_3,    KC_BSLS, KC_TRNS,
                         KC_TRNS,KC_DOT,  KC_0,    KC_EQL,    KC_NO,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),	
	
/* Keymap 2: RimWorld Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  ESC   |   1  |   2  |   3  |   4  |   5  |  6   |           |   7  |   7  |   8  |   9  |   0  |   -  |   =    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |  TAB   |   C  |  ,<  |   W  |   >. |   R  |      |           |TD(L0 |  U   |  B   |   N  |  J   |  M   |   PGUP |
 * |--------+------+------+------+------+------| F10  |           |L1 L2)|------+------+------+------+------+--------|
 * |   I    |   F  |   A  |   S  |   D  |   8  |------|           |------|  X   |  L   |   P  |  Y   |  H   |  ENTER |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |   K    |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |           |  F7  |  F8  |  F9  |  F10 |  F11 | F12  |   PGDN |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |  F   |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |SPACE |  C   |------|       |------|  E   |SPACE |
 *                                 |      |      |  Q   |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// RIMWORLD 
[RIMW] = LAYOUT_ergodox(
       // left hand
        KC_ESC,   KC_1,    KC_2,     KC_3,    KC_4,    KC_5,    KC_6,
        KC_TAB,   KC_C, KC_COMM,     KC_W,  KC_DOT,    KC_R,  KC_F10,
          KC_I,   KC_F,    KC_A,     KC_S,    KC_D,    KC_8,
          KC_K,  KC_F1,   KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,
       KC_TRNS,KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,
                                       KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                                     KC_C,KC_Q,KC_TRNS,
       // right hand
          KC_7,    KC_7,    KC_8,        KC_9,    KC_0,    KC_MINS,  KC_EQL,
       KC_TRNS,    KC_U,    KC_B,        KC_N,    KC_J,       KC_M, KC_PGUP,
                   KC_X,    KC_L, SFT_T(KC_P),    KC_Y,       KC_H,  KC_ENT,
         KC_F7,   KC_F8,   KC_F9,      KC_F10,  KC_F11,     KC_F12, KC_PGDN,
                            KC_F,     KC_LEFT,   KC_UP,    KC_DOWN,KC_RIGHT,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS,    KC_E, KC_TRNS
),
/* Keymap 3: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      |      |      |      |      |  Play  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      | Prev | Next |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | Lclk | Rclk |                                       |VolUp |VolDn | Mute |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |Brwser|
 *                                 | Lclk | Rclk |------|       |------|      |Back  |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
[MDIA] = LAYOUT_ergodox(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_BTN1, KC_BTN2, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS,
                          KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_WBAK
),
};

static uint16_t key_timer;

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
      switch(id) {
        case 0: {
            if (record->event.pressed) {
                key_timer = timer_read(); // if the key is being pressed, we start the timer.
            }
            else { // this means the key was just released, so we can figure out how long it was pressed for (tap or "held down").
                if (timer_elapsed(key_timer) > 150) { // 150 being 150ms, the threshhold we pick for counting something as a tap.
                    return MACRO( D(LCTL), T(C), U(LCTL), END  );
                }
                else {
                    return MACRO( D(LCTL), T(V), U(LCTL), END  );
                }
            }
            break;
        }
      }
    return MACRO_NONE;
};

// Anything you want to do once when the keyboard initializes.
// Tests LED function when the keyboard initializes.
void matrix_init_user(void) {

  wait_ms(500);
  ergodox_board_led_on();
  wait_ms(200);
  ergodox_right_led_1_on();
  wait_ms(200);
  ergodox_right_led_2_on();
  wait_ms(200);
  ergodox_right_led_3_on();
  wait_ms(200);
  ergodox_board_led_off();
  wait_ms(200);
  ergodox_right_led_1_off();
  wait_ms(200);
  ergodox_right_led_2_off();
  wait_ms(200);
  ergodox_right_led_3_off();

};


// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        case 3:
            ergodox_right_led_3_on();
            break;			
        default:
            // none
            break;
    }

};
