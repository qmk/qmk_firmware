#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"
#include "action_code.h"
#include "keymap_bepo.h"
#include "keymap_french.h"

#define BASE 0 // dvorak layout (default)
#define BEPO 1 // Bepo
#define SYMB 2 // symbols and numbers
#define MDIA 3 // mouse knd media eys
#define XMONAD 4 // xmonad keys

#define KP_00 0
#define CA_Fx 1

// MACROS
/* #define OBRACE 0 // key { or shift */
/* #define CBRACE 1 // key } or shift */
/* #define OBRACK 2 // key [ or left alt */
/* #define CBRACK 3 // key ] or left alt */
/* #define CAPS   4 // caps lock */

// LEDS
#define USB_LED_NUM_LOCK    0
#define USB_LED_CAPS_LOCK   1
#define USB_LED_SCROLL_LOCK 2
#define USB_LED_COMPOSE     3
#define USB_LED_KANA        4

// TIMERS
#define KEY_TAP_FAST 85
#define KEY_TAP_SLOW 95

//Tap Dance Declarations
enum {
  TD_ESC_CAPS = 0,
  TD_TAB_BKTAB = 1
};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Esc, twice for Caps Lock
  [TD_ESC_CAPS]  = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS),
  [TD_TAB_BKTAB]  = ACTION_TAP_DANCE_DOUBLE(KC_TAB, LSFT(KC_TAB))
  // Other declarations would go here, separated by commas, if you have them
};


#define SFTGUI_T(kc) {                          \
    MT(MOD_LGUI | MOD_LSFT, kc)                 \
      }


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap 0: Base layer
   * Keys with double values (like Esc/Ctrl) correspond to the 'tapped' key and the 'held' key, respectively
   *
   * ,--------------------------------------------------.           ,--------------------------------------------------.
   * |        |   1  |   2  |   3  |   4  |   5  | Base |           | Bepo |   6  |   7  |   8  |   9  |   0  | = / +  |
   * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
   * |   ~    |" / ' |, / < |. / > |   P  |   Y  |   [  |           |   ]  |   F  |   G  |   C  |   H  |   L  | / / ?  |
   * |--------+------+------+------+------+------|   {  |           |   }  |------+------+------+------+------+--------|
   * |  Tab   |   A  |   O  |   E  |U/LSft| I/L1 |------|           |------|D/SYMB|H/RSft|   T  |   N  |   S  | - / _  |
   * |--------+------+------+------+------+------|  (   |           | )    |------+------+------+------+------+--------|
   * | {/LSft |; / : |   Q  |   J  |   K  |   X  |      |           |      |   B  |   M  |   W  |   V  |   Z  | }/RSft |
   * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
   *   | CTL-C | CTL-V | SYMB | left | Right |                                  | Up | Down | MDIA | \ / ||  KC_NO |
   *   `----------------------------------'                                       `----------------------------------'
   *                                        ,-------------.       ,-------------.
   *                                        | hold-GUI| TAB       |      |        |
   *                                        | tap-ESC | dbl-tap|  |      |        |
   *                                        |         |S-tab|     | MDIA | XMONAD |
   *                                 ,------|------|------|       |------+--------+------.
   *                                 | BSPC |  DEL | Home/MDIA|   | PGUP/SYMB | Enter  |SPACE |
   *                                 |  /   |  /   |------    |   |------     |   /    |  /   |
   *                                 | LCTL | LALT | End/LSHFt|   |PGDN/SHFT  | LALT   | LCTL |
   *                                 `--------------------'       `----------------------'
  *
  */

  [BASE] = KEYMAP(
                  // left hand
                  KC_GRV,                       KC_1,     KC_2,   KC_3,   KC_4,          KC_5,           TO(BASE),
                  KC_TILD,                      KC_QUOTE, KC_COMM,KC_DOT, KC_P,          KC_Y,           KC_LBRC,
                  TD(TD_TAB_BKTAB),     KC_A,     KC_O,   KC_E,   SFT_T(KC_U),   LT(SYMB, KC_I),
                  SFT_T(KC_CAPSLOCK),           KC_SCLN,  KC_Q,   KC_J,   KC_K,          KC_X,           KC_LPRN,
                  LCTL(KC_C), LCTL(KC_V), TG(SYMB), KC_LEFT, KC_RIGHT,
                  GUI_T(KC_ESC), TD(TD_TAB_BKTAB),
                  LT(MDIA, KC_HOME),
                  CTL_T(KC_BSPC), ALT_T(KC_DEL), SFT_T(KC_END),
                  // right hand
                  TG(BEPO),        KC_6,           KC_7,         KC_8,   KC_9,   KC_0, KC_EQL,
                  KC_RBRC,         KC_F,           KC_G,         KC_C,   KC_R,   KC_L, KC_SLASH,
                  LT(SYMB, KC_D),  SFT_T(KC_H),    KC_T,         KC_N,   KC_S,   KC_MINUS,
                  KC_RPRN,         KC_B,           KC_M,         KC_W,   KC_V,   KC_Z, OSM(MOD_LSFT),
                  KC_UP, KC_DOWN,  TG(MDIA), KC_BSLASH, KC_NO,
                  TG(MDIA), LT(XMONAD, OSL(XMONAD)),
                  LT(SYMB,KC_PGUP),
                  SFT_T(KC_PGDN), ALT_T(KC_ENT), CTL_T(KC_SPC)
                  ),

  /* Keymap: Bepo
   *
   * ,--------------------------------------------------.        ,--------------------------------------------------.
   * |   $    |   "  |   <  |   >  |   (  |   )  |      |        |      |   @  |   +  |   -  |   /  |   *  |   =    |
   * |--------+------+------+------+------+-------------|        |------+------+------+------+------+------+--------|
   * |   %    |   B  |E_ACUT|   P  |   O  |E_GRAV|      |        |      |   ^  |   V  |   D  |   L  |   J  |   Z    |
   * |--------+------+------+------+------+------|      |        |      |------+------+------+------+------+--------|
   * |   W    |   A  |   U  |   I  |   E  |   ,  |------|        |------|   C  |   T  |   S  |   R  |   N  |   M    |
   * |--------+------+------+------+------+------|      |        |      |------+------+------+------+------+--------|
   * | E_CIRC |A_GRAV|   Y  |   X  |   .  |   K  |      |        |      |   '  |   Q  |   G  |   H  |   F  | C_CEDIL|
   * `--------+------+------+------+------+-------------,        `-------------+------+------+------+------+--------'
   */
  [BEPO] = KEYMAP(
                  // Left hand
                  BP_DOLLAR,	BP_DQOT,	BP_LGIL,	BP_RGIL,	BP_LPRN,	BP_RPRN,	KC_TRNS,
                  BP_PERCENT,	BP_B,		BP_E_ACUTE,	BP_P,		BP_O,		BP_E_GRAVE,	KC_TRNS,
                  BP_W,		BP_A,		BP_U,		BP_I,		BP_E,		BP_COMMA,
                  BP_ECRC,	BP_A_GRAVE,	BP_Y,		BP_X,		BP_DOT,		BP_K,		KC_TRNS,
                  KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
                  KC_TRNS,		KC_TRNS,
                  KC_TRNS,
                  KC_TRNS,		KC_TRNS,	KC_TRNS,
                  // Right hand
                  KC_TRNS,	BP_AT,		BP_PLUS,	BP_MINUS,	BP_SLASH,	BP_ASTR,	BP_EQUAL,
                  KC_TRNS,	BP_DCRC,	BP_V,		BP_D,		BP_L,		BP_J,		BP_Z,
                  BP_C,		BP_T,		BP_S,		BP_R,		BP_N,		BP_M,
                  KC_TRNS,	BP_APOS,	BP_Q,		BP_G,		BP_H,		BP_F,		BP_CCED,
                  KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
                  KC_TRNS,		KC_TRNS,
                  KC_TRNS,
                  KC_TRNS,	KC_TRNS,	KC_TRNS),

  /* Keymap : Symbol Layer
   *
   * ,--------------------------------------------------.           ,--------------------------------------------------.
   * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
   * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
   * |        |   !  |   @  |   {  |   }  |   |  |      |           |      |   Up |   7  |   8  |   9  |   *  |   F12  |
   * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
   * |        |   #  |   $  |   (  |   )  |   `  |------|           |------| Down |   4  |   5  |   6  |   +  |        |
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
  [SYMB] = KEYMAP(
                  // left hand
                  KC_TRNS,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_TRNS,
                  KC_TRNS, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE, KC_TRNS,
                  KC_TRNS, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,
                  KC_TRNS, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD, KC_TRNS,
                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                  KC_TRNS,KC_TRNS,
                  KC_TRNS,
                  KC_TRNS,KC_TRNS,KC_TRNS,
                  // right hand
                  KC_TRNS, KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,
                  KC_TRNS, KC_UP,   KC_7,   KC_8,    KC_9,    KC_PSLS, KC_F12,
                  KC_DOWN, KC_4,   KC_5,    KC_6,    KC_PAST, KC_TRNS,
                  KC_TRNS, KC_AMPR, KC_1,   KC_2,    KC_3,    KC_PMNS, KC_PENT,
                  KC_TRNS, KC_0,  KC_DOT,   KC_PPLS,  KC_TRNS,
                  KC_TRNS, KC_TRNS,
                  KC_TRNS,
                  KC_TRNS, KC_TRNS, KC_TRNS
                  ),


  /* Keymap: Media and mouse keys
   *
   * ,--------------------------------------------------.           ,--------------------------------------------------.
   * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
   * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
   * |        |      | Lclk | MsUp | Rclk |      |      |           |      |      |VolDwn| Mute |VolUp |      |   F12  |
   * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
   * |        | Btn4 |MsLeft|MsDown|MsRght| Btn5 |------|           |------|      | Prev | Stop | Play | Next |        |
   * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
   * |        |WhRght|WhDown| WhUp |WhLeft|WhClk |      |           |      |BwSrch|BwBack|BwHome|BwRefr|BwFwd |        |
   * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
   *   |      |      |MsAcl0|MsAcl1|MsAcl2|                                       |      |      |      |      |      |
   *   `----------------------------------'                                       `----------------------------------'
   *                                        ,-------------.       ,-------------.
   *                                        |      |      |       |      |      |
   *                                 ,------|------|------|       |------+------+------.
   *                                 |      |      |      |       |      |Brwser|Brwser|
   *                                 | Lclk | Rclk |------|       |------|Back  |Forwd |
   *                                 |      |      |      |       |      |      |      |
   *                                 `--------------------'       `--------------------'
   */
  // MEDIA AND MOUSE
    [MDIA] = KEYMAP(
                    KC_TRNS, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_TRNS,
                    KC_TRNS,
                    KC_WSCH, KC_WBAK, KC_WHOM, KC_WREF, KC_WFWD, KC_TRNS,
                    KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_TRNS,
                    KC_TRNS, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, KC_TRNS, KC_TRNS,
                    KC_TRNS, KC_TRNS, KC_ACL0, KC_ACL1, KC_ACL2,
                    KC_TRNS, KC_TRNS,
                    KC_TRNS,
                    KC_TRNS, KC_TRNS, KC_TRNS,
                    // right hand
                    KC_TRNS, KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11,
                    KC_VOLU, KC_MUTE, KC_MPRV, KC_MSTP, KC_MPLY, KC_MNXT, KC_F12,
                    KC_PGUP, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_TRNS,
                    KC_VOLD, KC_PGDN, KC_BTN1, KC_BTN2, KC_BTN3, KC_BTN4, KC_BTN5,
                    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                    KC_TRNS, KC_TRNS,
                    KC_TRNS,
                    KC_TRNS, KC_TRNS, KC_TRNS
                    ),


  /* Keymap: XMonad
   * Keys with double values (like Esc/Ctrl) correspond to the 'tapped' key and the 'held' key, respectively
   *
   * ,--------------------------------------------------.           ,--------------------------------------------------.
   * |        |   1  |   2  |   3  |   4  |   5  |      |           |      |   6  |   7  |   8  |   9  |   0  | = / +  |
   * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
   * |   ~    |" / ' |, / < |. / > |   P  |   Y  |   [  |           |   ]  |   F  |   G  |   C  |   H  |   L  | / / ?  |
   * |--------+------+------+------+------+------|   {  |           |   }  |------+------+------+------+------+--------|
   * |        |   A  |   O  |   E  |U     | I    |------|           |------|D     |H     |   T  |   N  |   S  | - / _  |
   * |--------+------+------+------+------+------|  (   |           | )    |------+------+------+------+------+--------|
   * |        |; / : |   Q  |   J  |   K  |   X  |      |           |      |   B  |   M  |   W  |   V  |   Z  |      |
   * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
   *   |      |      |      |      |      |                                       |      |      |      |      |      |
   *   `----------------------------------'                                       `----------------------------------'
   *                                        ,-------------.       ,-------------.
   *                                        |      |      |       |      |        |
   *                                        |      |      |       |      |        |
   *                                        |      |      |       |      |        |
   *                                 ,------|------|------|       |------+--------+------.
   *                                 |      |      |      |       |      |        |  |
   *                                 |      |      |------|       |------|        |  |
   *                                 |      |      |      |       |      |        |  |
   *                                 `--------------------'       `----------------------'
   *
   */

  // Xmonad
    [XMONAD] = KEYMAP(
                      // left hand
                      KC_TRNS,   LGUI(KC_1),     LGUI(KC_2),   LGUI(KC_3),   LGUI(KC_4),  LGUI(KC_5), KC_TRNS,
                      KC_TILD,    KC_QUOTE, KC_COMM,KC_DOT, LGUI(KC_P), LGUI(KC_Y),  KC_LBRC,
                      KC_TRNS,   LGUI(KC_A),     LGUI(KC_O),   LGUI(KC_E),   LGUI(KC_U),  LGUI(KC_I),
                      KC_TRNS,   KC_SCLN,  LGUI(KC_Q),   LGUI(KC_J),   LGUI(KC_K), LGUI(KC_X),  KC_LPRN,
                      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                      KC_TRNS, KC_TRNS,
                      KC_TRNS,
                      KC_TRNS, KC_TRNS, KC_TRNS,
                      // right hand
                      KC_TRNS,        LGUI(KC_6),  LGUI(KC_7), LGUI(KC_8),   LGUI(KC_9),   LGUI(KC_0), KC_EQL,
                      KC_RBRC,         LGUI(KC_F),  LGUI(KC_G), LGUI(KC_C),   LGUI(KC_R),   LGUI(KC_L), KC_SLASH,
                      LGUI(KC_D),  LGUI(KC_H),    LGUI(KC_T),  LGUI(KC_N),   LGUI(KC_S),   KC_MINUS,
                      KC_RPRN,        LGUI(KC_B), LGUI(KC_M),  LGUI(KC_W),   LGUI(KC_V),   LGUI(KC_Z), KC_TRNS,
                      KC_TRNS, KC_TRNS,  KC_TRNS, KC_BSLASH, KC_NO,
                      KC_TRNS, KC_TRNS,
                      KC_TRNS,
                      KC_TRNS, KC_TRNS, KC_TRNS
                      )
};



const uint16_t PROGMEM fn_actions[] = {
  [1] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols)
};


const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
  switch(id) {

  /* case 0: */
  /*   if (record->event.pressed) { */
  /*     register_code(KC_RSFT); */
  /*   } else { */
  /*     unregister_code(KC_RSFT); */
  /*   } */
  /*   break; */

  case KP_00:
    if (record->event.pressed) {
      return MACRO( T(KP_0), D(KP_0), END );
    } else {
      return MACRO( U(KP_0), END );
    }
    break;
  case CA_Fx:
    if (record->event.pressed) {
      layer_on(MDIA);
      return MACRO( D(LALT), D(LCTL), END );
    } else {
      layer_off(MDIA);
      return MACRO( U(LCTL), U(LALT), END );
    }
    break;
  }
  return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

  uint8_t layer = biton32(layer_state);

  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();
  switch (layer) {
  case BASE:
    ergodox_right_led_1_on();
    break;
  case BEPO:
    ergodox_right_led_2_on();
    break;
  case SYMB:
    ergodox_right_led_1_on();
    break;
  case MDIA:
    ergodox_right_led_2_on();
    break;
  default:
    ergodox_board_led_off();
    break;

    /* default: */
    /*   // none */
  /*   break; */

  }
}
