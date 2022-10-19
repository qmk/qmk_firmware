#include QMK_KEYBOARD_H
#include "action_layer.h"

#define _BL 0
#define _AL 1
#define _FL 2
#define _UL 3

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
   /*
   *  ISO Base, Mac style
   * ,-----------------------------------------------------------------------------.
   * |Esc   |  1|   2|   3|   4|   5|   6|   7|   8|   9|   0|   -|   = |   Backsp |
   * |-----------------------------------------------------------------------------|
   * |Tab    |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I|   O|  P|  [|  ]|      |
   * |-----------------------------------------------------------------------      |
   * |Caps/Fn      |    A|    S|    D|    F|   G|  H|  J|  K|  L|  ;|  '|   #|Enter|
   * |-----------------------------------------------------------------------------|
   * |Shift|    \|    Z|     X|    C|     V|  B|  N|  M|  ,|  .|  /|     Shift     |
   * |-----------------------------------------------------------------------------|
   * |Fn|Alt |Gui | Space(tapped), Fn(held) |Gui |Alt  |Menu(tapped, Fn2(held)|Ctrl|
   * `-----------------------------------------------------------------------------'
   */
	[_BL] = LAYOUT_60_iso(
        KC_ESC,KC_1,KC_2,KC_3,KC_4,KC_5,KC_6,KC_7,KC_8,KC_9,KC_0,KC_MINS,KC_EQL,KC_BSPC, \
	      KC_TAB,KC_Q,KC_W,KC_E,KC_R,KC_T,KC_Y,KC_U,KC_I,KC_O,KC_P,KC_LBRC,KC_RBRC, \
        KC_LCTL,KC_A,KC_S,KC_D,KC_F,KC_G,KC_H,KC_J,KC_K,KC_L,KC_SCLN,KC_QUOT,KC_NUHS,KC_ENT,  \
        KC_LSFT,KC_NUBS,KC_Z,KC_X,KC_C,KC_V,KC_B,KC_N,KC_M,KC_COMM,KC_DOT,KC_SLSH,KC_RSFT, \
        MO(1),KC_LALT,KC_LGUI,        LT(1,KC_SPACE),      KC_RGUI, KC_RALT, LT(2,KC_MENU), KC_RCTL),

   /*
   * Pok3r style arrow cluster
   * ,-----------------------------------------------------------.
   * |`~ | F1| F2| F3| F4| F5| F6| F7| F8| F9| F10| F11| F12|DEL |
   * |-----------------------------------------------------------|
   * |     |   |    |   |   |   |   |   |Up|   |   |   |   |     |
   * |-------------------------------------------------------    |
   * |       |   |   |   |   |   |   |Left|Down|Right|   |   |   |
   * |-----------------------------------------------------------|
   * |        |   |   |   |   |   |   |   |   |   |   |          |
   * |-----------------------------------------------------------|
   * |    |    |    |                        |    |    |    |    |
   * `-----------------------------------------------------------'
   */
	[_AL] = LAYOUT_60_iso(
        KC_GRV,KC_F1,KC_F2,KC_F3,KC_F4,KC_F5,KC_F6,KC_F7,KC_F8,KC_F9,KC_F10,KC_F11,KC_F12,KC_DELETE, \
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_UP,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, \
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_LEFT,KC_DOWN,KC_RGHT,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, \
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,   \
        KC_TRNS,KC_TRNS,KC_TRNS,          KC_TRNS,               KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS),


   /*
   * Secondary function layer
   * ,-------------------------------------------------------------.
   * | | |  |  |  | | | RW|Play|FF| Mute| Vol Down | Vol up |Reset |
   * |-------------------------------------------------------------|
   * |    |   |   |   |  |  |  |   |    |PgUp|    |    |   |       |
   * |--------------------------------------------------------     |
   * |      |   |   |   |   |   |  |Home|PgDown|End|  |   |   |    |
   * |-------------------------------------------------------------|
   * |        |   |   |   |   |   |   |    |    |    |   |         |
   * |-------------------------------------------------------------|
   * |    |    |    |                          |    |    |    |    |
   * `-------------------------------------------------------------'
   */
	[_FL] = LAYOUT_60_iso(
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_MPRV,KC_MPLY,KC_MNXT,KC_MUTE,KC_VOLD,KC_VOLU,QK_BOOT, \
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_PGUP,KC_TRNS,KC_TRNS,KC_TRNS, \
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_HOME,KC_TRNS,KC_HOME,KC_PGDN,KC_END,KC_TRNS,KC_TRNS,KC_TRNS, \
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, \
        KC_TRNS,KC_TRNS,KC_TRNS,          KC_TRNS,               KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS),

   /*
   * Locking layer for controlling the underglow.
   * NOTE: currently unused.
   *
   * ,-----------------------------------------------------------.
   * |    |  |   |   |   |   |   |   |   |   |   |   |   |       |
   * |-----------------------------------------------------------|
   * |     |   |   |   |   |   |   |   |   |   |   |   |   |     |
   * |-------------------------------------------------------    |
   * |       |On|Mode|   |   |   |   |   |   |   |   |   |   |   |
   * |-----------------------------------------------------------|
   * |        |   |Hue+|Hue-|Sat+|Sat-|Val+|Val-|  |  |   |      |
   * |-----------------------------------------------------------|
   * |    |    |    |                        |    |    |    |    |
   * `-----------------------------------------------------------'
   */
	[_UL] = LAYOUT_60_iso(
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, \
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, \
        KC_TRNS,RGB_TOG,RGB_MOD,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, \
        KC_TRNS,KC_TRNS,KC_TRNS,RGB_HUI,RGB_HUD,RGB_SAI,RGB_SAD,RGB_VAI,RGB_VAD,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,   \
        KC_TRNS,KC_TRNS,KC_TRNS,          KC_TRNS,               KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS),
};

void matrix_scan_user(void) {
// Layer LED indicators
// ESC led on when in function layer, WASD cluster leds enabled when on arrow cluster
  #ifdef KEYBOARD_gh60
    uint32_t layer = layer_state;
    if (layer & (1<<1)) {
        gh60_wasd_leds_on();
    } else {
        gh60_wasd_leds_off();
    }

    if (layer & (1<<2)) {
        gh60_esc_led_on();
    } else {
        gh60_esc_led_off();
    }
  #endif
};
