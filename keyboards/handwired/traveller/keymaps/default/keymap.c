#include "traveller.h"
#include "mousekey.h"
#include "action_layer.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
#define _QW 0
#define _LW 1
#define _HI 2
#define _NAV 4
#define _CUR 5
#define _FKEYS 6 
#define _TRNS 8

// We do the same trick for functions
#define  RGBLED_TOGGLE 10
#define _HIOUT 15
#define _LWOUT 16
// Macros
#define  MDL 4
#define  MDR 5
#define  MUR 6
#define  MUL 3 



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Qwerty
 * ,-----------------------------------------.      .-----------------------------------------.
 * | NAV  | ` ~  |   W  |   E  |   R  |   T  |      |  Y   |   U  |   I  |   O  |  -   |  =   |
 * |------+------+------+------+------+------|      |------+------+------+------+------+------|
 * | Tab  |   Q  |   S  |   D  |   F  |   G  |      |  H   |  J   |   K  |   L  |   P  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------+------|
 *|ctrl/esc|  A  |   X  |   C  |   V  |   B  |Ctrl /|   N  |   M  |   ,  |   .  |   ;  |  '   |
 * |------+------+------+------+------+------+  //  +------+------+------+------+------+------|
 * | Shift|   Z  | Del  | GUI  | Low  | Bspc |/Enter| Spc  | Hi   | GUI  | Alt  |  /   |Shift |
 * `------------------------------------------------------------------------------------------'
 * 
 */
[_QW] = KEYMAP( 
  F(_NAV),          KC_GRV, KC_W,    KC_E,    KC_R,    KC_T,             KC_Y,    KC_U,    KC_I,    KC_O,    KC_MINS,  KC_EQL,
  KC_TAB,           KC_Q,    KC_S,    KC_D,    KC_F,    KC_G,            KC_H,    KC_J,    KC_K,    KC_L,    KC_P, 	KC_BSLS,
  CTL_T(KC_ESC),    KC_A,    KC_X,    KC_C,    KC_V,    KC_B,    KC_RCTL,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SCLN, 	KC_QUOT,
  KC_LSFT, KC_Z,    KC_DEL, KC_LGUI, MO(_LW), KC_BSPC, KC_ENTER, KC_SPC,  MO(_HI), KC_RGUI, KC_RALT,    KC_SLSH,   KC_RSFT
 ),

/* LOW  - numbers, missing or awkward programming keys
 Doubled 1 key allows lazy reach with ring finger. 
 * ,-----------------------------------------.      .-----------------------------------------.
 * | FKeys|   1  |   2  |  3   |   4  |   5  |      |  6   |  7   |   8  |   9  |   0  |Ctrl-alt-del|
 * |------+------+------+------+------+------|      +------+------+------+------+------+------|
 * | Tab  |   1  |  ]   |  (   |  )   |      |      |   *  |   (  |   )  |   [  |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------+------|
 * | Caps |  [   |      |  {   |   }  |  `   |     /|   #  |   {  |   }  |      | ]    |      |
 * |------+------+------+------+------+------+  //  +------+------+------+------+------+------|
 * | Shift|      |      |      | Low  |      |/     |      |  Hi  |      |      |      |Shift |
 * `------------------------------------------------------------------------------------------'
 * 
 */

[_LW] = KEYMAP( 
  F(_FKEYS),   KC_1,     KC_2,      KC_3,     KC_4,    KC_5,             KC_6,    KC_7,       KC_8,      KC_9,    KC_0,  LCTL(LALT(KC_DEL)) ,
  KC_TRNS,  KC_1,     KC_RBRC,   KC_LPRN,  KC_RPRN, KC_NO,               KC_ASTR, KC_LPRN,    KC_RPRN,    KC_LBRC,    KC_NO, KC_NO,
  KC_CAPS,   KC_LBRC,  KC_NO,     KC_LCBR,  KC_RCBR, KC_TILD,   KC_TRNS,  KC_HASH, KC_LCBR,    KC_RCBR,   KC_NO,    KC_RBRC,   KC_NO,
  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,    KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS
),

/* HI - Punctuation, shell and 
url ://@.com  row on bottom,    && is opposite ||       ^$ are in regex order: ^.*$    
Right hand nav keys work pretty well chorded with the Right hand Hi Key
 * ,-----------------------------------------.      .-----------------------------------------.
 * |FKEYS |   !  |   @  |   #  |   $  |   %  |      |  ^   |   &  |   *  |   (  |   )  |   +  |
 * |------+------+------+------+------+------|      |------+------+------+------+------+------|
 * |      |  !   |  &   |  "|" |   $  |   %  |      |  Vol+|  Mute|      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------+------|
 * | CAPS |  ^   |   :  |   .  |   *  |   -  |     /|  Vol-| Play | PgUp | Home | Up   | End  |
 * |------+------+------+------+------+------+  //  +------+------+------+------+------+------|
 * |      |   /  |      |      | Low  |      |/     |      |  Hi  | PgDn | Left| Down | Right |
 * `------------------------------------------------------------------------------------------'
 * 
 */

[_HI] = KEYMAP( 
 F(_FKEYS), KC_EXLM,  KC_AT,   KC_HASH,  KC_DLR,   KC_PERC,           KC_CIRC,  KC_AMPR,    KC_ASTR,   KC_LPRN,  KC_RPRN,  KC_PLUS,
 KC_TRNS, KC_EXLM,  KC_AMPR, KC_PIPE,  KC_DLR,   KC_PERC,             KC_VOLU, KC_MUTE,    KC_NO,     KC_NO,    KC_NO,    KC_NO, 
 KC_CAPS, KC_CIRC,  KC_COLN,  KC_DOT,  KC_ASTR,  KC_MINS,   KC_TRNS,  KC_VOLD, KC_PPLS,    KC_PGUP,   KC_HOME,  KC_UP,    KC_END,
 KC_TRNS, KC_SLSH,  KC_TRNS,  KC_TRNS, F(_LW),   KC_TRNS,   KC_TRNS,  KC_TRNS, KC_TRNS,    KC_PGDN,   KC_LEFT,  KC_DOWN,  KC_RIGHT 
),	

/* NAV - mouse &  navigation
//gui left and right are line home/end, or fore & back in browser
// Mouse buttons are reversed for comfort - bigger stretch is to the right button. 

 * ,-----------------------------------------.      .-----------------------------------------.
* | NAV  |      |      | Up   |      |Gui-> |      | MwU  | MS_UL| MS_U |MS_UR |      |Ms Norm|
* |------+------+------+------+------+------|      |------+------+------+------+------+--------|
* |      |Gui<- | Left | Down |Right | C^E  |      | BTN3 | MS_L |MS Up | MS_R |      |Ms Fast |
* |------+------+------+------+------+------|------|------+------+------+------+------+--------|
* |      | C^A  | GUI X| GUI C| GUI_V|      |Enter/| MWD  | M_DL |MS Dwn|MS_DR | Up   |Ms Slow |
* |------+------+------+------+------+------+  //  +------+------+------+------+------+------|
* |      | GuiZ |      |      | Low  |      |/ButnR|ButnL |  Hi  |      | Left | Down | Right |
* `------------------------------------------------------------------------------------------'
*/

[_NAV] = KEYMAP( 
  F(_NAV),  KC_NO,         KC_NO,    KC_UP,       KC_NO,     RGUI(KC_RIGHT),            KC_WH_U,  M(MUL), KC_MS_U,   M(MUR), KC_NO, KC_ACL2,
  KC_TRNS, RGUI(KC_LEFT),  KC_LEFT,  KC_DOWN,     KC_RIGHT,  LCTL(KC_E),                KC_BTN3,  KC_MS_L,  KC_MS_U,   KC_MS_R,  KC_NO, KC_ACL1,
  KC_TRNS, LCTL(KC_A),     LGUI(KC_X),RGUI(KC_C), RGUI(KC_V),KC_NO,         KC_ENTER,   KC_WH_D,  M(MDL), KC_MS_D,  M(MDR),  KC_UP, KC_ACL0,
  KC_TRNS, RGUI(KC_Z),     KC_TRNS,  KC_TRNS,     KC_TRNS,   KC_TRNS,       KC_BTN2,   KC_BTN1,  KC_TRNS,  KC_TRNS,   KC_LEFT,   KC_DOWN,   KC_RIGHT
),

/* FKEYS - Funtion keys & mac stuff
 * ,-----------------------------------------.      .-----------------------------------------.
 * | FKEYS| F1   | F2   | F3   |  F4  | F5   |      | F6   | F7   | F8   | F9   | F10  | Ctrl | 
 * |------+------+------+------+------+------|      |------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |  F11 | F12  |  F13 | F14  |  F15 | Alt  |
 * |------+------+------+------+------+------|------+------+------+------+------+------+------|
 * |Qwerty|      |      |      |      |      |     /|      |      |      |      |      | Del  |
 * |------+------+------+------+------+------+  //  +------+------+------+------+------+------|
 * |    . |RGBTog|  .   |      | LO   | Bspc |/     |      | HI   |      |      |      |      |
 * `------------------------------------------------------------------------------------------'
 *
 */ 
 
[_FKEYS] = KEYMAP( 
  F(_FKEYS), KC_F1,    KC_F2,  	KC_F3,      KC_F4,     KC_F5,               KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,    KC_RCTL,
  KC_TRNS,   KC_NO,    KC_NO,   KC_NO,      KC_NO,     KC_NO,               KC_F11,   KC_F12,   KC_F13,    KC_F14,  KC_F15,  	 KC_LALT ,
  F(_QW),   KC_NO,     KC_NO,   KC_NO,      KC_NO,     KC_NO,    KC_TRNS,   KC_NO,    KC_NO,    KC_NO,      KC_NO,   KC_NO,    KC_DEL,
  KC_TRNS, F(RGBLED_TOGGLE),    KC_TRNS,    KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,   KC_TRNS
),


/* TRNS - skeleton for laters
 * ,-----------------------------------------.      .-----------------------------------------.
 * |   .  |   .  |   .  |   .  |   .  |   .  |      |  ^   |   &  |   *  |   (  |   )  |      |
 * |------+------+------+------+------+------|      |------+------+------+------+------+------|
 * |   .  |   .  |   .  |   .  |   .  |   .  |      |  6   |  7   |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------+------|
 * |   .  |   .  |   .  |   .  |   .  |   .  |     /|      |      |      |   .  |   ;  |  "   |
 * |------+------+------+------+------+------+  //  +------+------+------+------+------+------|
 * |    . |   .  |  .   | GUI  |  LO  |   .  |/     | Spc  |  HI  | GUI  |  M0  |  /   |LSFT |
 * `------------------------------------------------------------------------------------------'
 * 
 */

[_TRNS] = {
  {KC_TRNS,  KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,   KC_NO,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,   KC_TRNS},
  {KC_TRNS,  KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,   KC_NO,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, 	KC_TRNS},
  {KC_TRNS,  KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,   KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, 	KC_TRNS},
  {KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,   KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,   KC_TRNS}
 }


};


const uint16_t PROGMEM fn_actions[] = {
    [_QW] = ACTION_LAYER_ON(_QW,ON_RELEASE), // return to QWERTY  layer
    [_LW] = ACTION_LAYER_TAP_TOGGLE(_LW), // Turn on LW when holding, or tap 3 times to switch
    [_HI] = ACTION_LAYER_TAP_TOGGLE(_HI), // Turn on LW when holding, or tap 3 times to switch               
    [_NAV] = ACTION_LAYER_TOGGLE(_NAV),                                   
    [_FKEYS] = ACTION_LAYER_TOGGLE(_FKEYS),  
    [_LWOUT] = ACTION_LAYER_OFF(_LW,ON_RELEASE),
    [_HIOUT] = ACTION_LAYER_OFF(_HI,ON_RELEASE),
    
    // Functions
  [RGBLED_TOGGLE]  = ACTION_FUNCTION(RGBLED_TOGGLE),
 
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
          if (record->event.pressed) {
            register_code(KC_RSFT);
            #ifdef BACKLIGHT_ENABLE
              backlight_step();
            #endif
          } else {
            unregister_code(KC_RSFT);
          }
        break;

   // from  algernon's ErgoDox EZ layout,
       case MUL:
        if (record->event.pressed) {
          mousekey_on(KC_MS_UP);
          mousekey_on(KC_MS_LEFT);
        } else {
          mousekey_off(KC_MS_UP);
          mousekey_off(KC_MS_LEFT);
        }
        mousekey_send();
        break;

      case MUR:
        if (record->event.pressed) {
          mousekey_on(KC_MS_UP);
          mousekey_on(KC_MS_RIGHT);
        } else {
          mousekey_off(KC_MS_UP);
          mousekey_off(KC_MS_RIGHT);
        }
        mousekey_send();
        break;

      case MDL:
        if (record->event.pressed) {
          mousekey_on(KC_MS_DOWN);
          mousekey_on(KC_MS_LEFT);
        } else {
          mousekey_off(KC_MS_DOWN);
          mousekey_off(KC_MS_LEFT);
        }
        mousekey_send();
        break;

      case MDR:
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



void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
  switch (id) {
    case RGBLED_TOGGLE:
      //led operations
      if (record->event.pressed) {
        rgblight_toggle();
      }
        break;
  }
}

 

void LayerLEDSet(uint8_t layr) {

    switch (layr) {
        case _QW:
            rgblight_setrgb(0,20, 0); //  dim green
        break;
        case _LW:
            // deep purple
            rgblight_setrgb(20,0,35); 
            break;  
        case _HI:
            // light blue
           rgblight_setrgb(0,20,20); 
            break;    
        case _NAV:
            // Yellowy orange
            rgblight_setrgb(25,20,0); // brighter
            break;
        case _FKEYS:
         // RED
           rgblight_setrgb(20,0,0); // brighter
            break;  
        default:
            rgblight_setrgb(20,2,20);//error
            break;
    }
 
 return;
  
}

void matrix_init_user(void) {
}

// Bleah globals need to be initialized.
uint8_t old_layer=_QW;

void matrix_scan_user(void) {
         uint8_t layer = biton32(layer_state);
         if (old_layer != layer) {
           LayerLEDSet(layer);
           old_layer=layer;
           }
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void led_set_user(uint8_t usb_led) {

}


