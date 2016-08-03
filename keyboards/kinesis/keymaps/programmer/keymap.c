#include "kinesis.h"
#include "action_layer.h"
#include "mousekey.h"

#define QWERTY 0 // Base qerty
#define SYMB 1// Symbol layer
#define MOUSE 2//




/* Macros */
enum {
  NONE = 0,
  // Diagonal mouse movement
  A_MUL,
  A_MUR,
  A_MDL,
  A_MDR,
};


// Borrowing very heavily from 
// https://github.com/alvicstep/tmk_keyboard 
/****************************************************************************************************
*
* Keymap: Default Layer in Qwerty
*
* ,-------------------------------------------------------------------------------------------------------------------.
* | Esc    |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F8  |  F9  |  F10 |  F12 |  FN0 |  FN1 |  FN2 |      |  bOOT  |
* |--------+------+------+------+------+------+---------------------------+------+------+------+------+------+--------|
* | =+     |  1!  |  2@  |  3#  |  4$  |  5%  |                           |  6^  |  7&  |  8*  |  9(  |  0)  | -_     |
* |--------+------+------+------+------+------|                           +------+------+------+------+------+--------|
* | Tab    |   Q  |   W  |   E  |   R  |   T  |                           |   Y  |   U  |   I  |   O  |   P  | \|     |
* |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
* |MouseFN1|   A  |   S  |   D  |   F  |   G  |                           |   H  |   J  |   K  |   L  |  ;:  | '"     |
* |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
* | Shift  |   Z  |   X  |   C  |   V  |   B  |                           |   N  |   M  |  ,.  |  .>  |  /?  | Shift  |
* `--------+------+------+------+------+-------                           `------+------+------+------+------+--------'
*          | `~   | ESC  |MOUSE1|MOUSE2|                                         | [{   |  ]}  | ESC  | GUI  |
*          `---------------------------'                                         `---------------------------'
*                                        ,-------------.         ,-------------.
*                                        | Ctrl | Alt  |         | Gui  | Ctrl |
*                                 ,------|------|------|         |------+------+------.
*                                 |      |      | Home |         | PgUp |      |      |
*                                 | BkSp | Del  |------|         |------|Return| Space|
*                                 |      |      | End  |         | PgDn |      |      |
*                                 `--------------------'         `--------------------'
*/


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[QWERTY] = KEYMAP(
           KC_ESC, KC_F1  ,KC_F2  ,KC_F3  ,KC_F4  ,KC_F5  ,KC_F6  ,KC_F7  ,KC_F8,
           KC_EQL, KC_1   ,KC_2   ,KC_3   ,KC_4   ,KC_5   ,
           KC_TAB, KC_Q   ,KC_W   ,KC_E   ,KC_R   ,KC_T   ,
           KC_FN1 ,KC_A   ,KC_S   ,KC_D   ,KC_F   ,KC_G   ,
           KC_LSFT,KC_Z   ,KC_X   ,KC_C   ,KC_V   ,KC_B   ,
		KC_GRV  ,KC_ESC,  KC_BTN1,KC_BTN2,
			   KC_LCTL,KC_LALT,
			   KC_HOME,
                           KC_BSPC,KC_DEL ,KC_FN0 ,
        KC_F9  ,KC_F10 ,KC_F11 ,KC_F12 ,KC_FN0 ,KC_FN1  ,KC_FN2, KC_NO, RESET,
	KC_6   ,KC_7   ,KC_8   ,KC_9   ,KC_0   ,KC_MINS,
	KC_Y   ,KC_U   ,KC_I   ,KC_O   ,KC_P   ,KC_BSLS,
	KC_H   ,KC_J   ,KC_K   ,KC_L   ,KC_SCLN,KC_QUOT,
	KC_N   ,KC_M   ,KC_COMM,KC_DOT ,KC_SLSH,KC_RSFT,
		KC_LBRC,KC_RBRC, KC_ESC, KC_RGUI,
           KC_RGUI,KC_RCTL,
           KC_PGUP,
           KC_PGDN,KC_ENTER ,KC_SPC
    ),
[SYMB] = KEYMAP( 
         KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
         KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
         KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
         KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
         KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
                   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
                             KC_TRNS,  KC_TRNS,
                                       KC_TRNS,
                    KC_TRNS, KC_TRNS,  KC_TRNS,
         KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_FN0, KC_2,
         KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
         KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
         KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
         KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
                   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
         KC_TRNS,  KC_TRNS,
         KC_TRNS,
         KC_TRNS,  KC_TRNS,  KC_TRNS
    ),
/* Keymap: Movement and function layer
*
* ,-------------------------------------------------------------------------------------------------------------------.
* | Caps   |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F8  |  F9  |  F10 |  F12 |  FN0 |  FN1 |  FN2 |  Tada |  bOOT  |
* |--------+------+------+------+------+------+---------------------------+------+------+------+------+------+--------|
* | =+     |  !   |   @  |   #  |   $  |   %  |                           |  ^   |   &  |   *  |  (   |   )  |MS Fast |
* |--------+------+------+------+------+------|                           +------+------+------+------+------+--------|
* | Tab    |      |      | Up   |      |PgUp  |                           | MwU  |MS_UL | MS_U |MS_UR |      | Ms Norm| 
* |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
* |MouseFN1| C^A  | Left | Down |Right | C^E  |                           |      | MS_L |Mouse1| MS_R |      |MS Slow |
* |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
* |        | GuiZ | GUI X| GUI C| GUI_V|PgDown|                           | MWD  | MDown|MS Dwn|MS_DR  |  ?  |        |
* `--------+------+------+------+------+-------                           `------+------+------+------+------+--------'
*          | `~   | ESC  |   <  |   >  |                                         |  {   |   }  | ESC  |      |
*          `---------------------------'                                         `---------------------------'
*                                        ,-------------.         ,-------------.
*                                        | Ctrl | Alt  |         | Gui  | Ctrl |
*                                 ,------|------|------|         |------+------+------.
*                                 |      |      | Home |         | PgUp |      |      |
*                                 | BkSp | Del  |------|         |------|Mouse1|Mouse2|
*                                 |      |      | End  |         | PgDn |LClick|Rclick|
*                                 `--------------------'         `--------------------'
*/


[MOUSE] = KEYMAP(
         KC_CAPS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
         KC_TRNS,  KC_EXLM  ,KC_AT,    KC_HASH,  KC_DLR   ,KC_PERC   ,
         KC_TRNS,  KC_NO,    KC_NO,    KC_UP,    KC_NO,    KC_PGUP,
         KC_FN1,  LCTL(KC_A),KC_LEFT,  KC_DOWN,  KC_RIGHT, LCTL(KC_E),
         KC_TRNS, LGUI(KC_Z),LGUI(KC_X),LGUI(KC_C),LGUI(KC_V),KC_PGDN,
                   KC_TRNS,  KC_TRNS,  KC_LABK,  KC_RABK,
                             KC_TRNS,  KC_TRNS,
                                       KC_TRNS,
                    KC_TRNS, KC_TRNS,  KC_TRNS,
         KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_FN0,RESET, 
         KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  KC_ACL2,  
         KC_WH_U,  M(A_MUL), KC_MS_U,  M(A_MUR), KC_NO,  KC_ACL1,
         KC_NO,    KC_MS_L,  KC_MS_D,  KC_MS_R,  KC_NO,  KC_ACL0,
         KC_WH_D,  M(A_MDL), KC_MS_D,  M(A_MDR), KC_TRNS, KC_TRNS,
                   KC_LCBR,  KC_RCBR,  KC_ESC,  KC_TRNS,
         KC_TRNS,  KC_TRNS,
         KC_TRNS,
         KC_TRNS,  KC_BTN1,  KC_BTN2
    ),


};

const uint16_t PROGMEM fn_actions[] = {
   [0] = ACTION_LAYER_TAP_TOGGLE(MOUSE) ,               // FN1 - Momentary Layer 1 (Symbols)
   [1] = ACTION_LAYER_TOGGLE(MOUSE) ,               // FN1 - Momentary Layer 1 (Symbols)
   [2] = ACTION_LAYER_TAP_TOGGLE(SYMB) ,               // FN1 - Momentary Layer 1 (Symbols)


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

	// from  algernon's ErgoDox EZ layout, 
       case A_MUL:
        if (record->event.pressed) {
          mousekey_on(KC_MS_UP);
          mousekey_on(KC_MS_LEFT);
        } else {
          mousekey_off(KC_MS_UP);
          mousekey_off(KC_MS_LEFT);
        }
        mousekey_send();
        break;

      case A_MUR:
        if (record->event.pressed) {
          mousekey_on(KC_MS_UP);
          mousekey_on(KC_MS_RIGHT);
        } else {
          mousekey_off(KC_MS_UP);
          mousekey_off(KC_MS_RIGHT);
        }
        mousekey_send();
        break;

      case A_MDL:
        if (record->event.pressed) {
          mousekey_on(KC_MS_DOWN);
          mousekey_on(KC_MS_LEFT);
        } else {
          mousekey_off(KC_MS_DOWN);
          mousekey_off(KC_MS_LEFT);
        }
        mousekey_send();
        break;

      case A_MDR:
        if (record->event.pressed) {
          mousekey_on(KC_MS_DOWN);
          mousekey_on(KC_MS_RIGHT);
        } else {
          mousekey_off(KC_MS_DOWN);
          mousekey_off(KC_MS_RIGHT);
        }
        mousekey_send();
        break;
     } 
    return MACRO_NONE;
};


void matrix_init_user(void) {


}

void matrix_scan_user(void) {
 int8_t layer = biton32(layer_state);

        switch (layer) {
        case 1:
                all_led_off();
                break;
        case 2:
                if (!(host_keyboard_leds() & (1 << USB_LED_CAPS_LOCK))) {
                        all_led_off();
                        caps_lock_led_on();
                }
                break;
        case 0:
                all_led_off();
                num_lock_led_on();
                break;
        default:
                break;
        }

}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void led_set_user(uint8_t usb_led) {

}
