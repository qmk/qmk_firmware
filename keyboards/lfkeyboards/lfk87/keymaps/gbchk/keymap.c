#include "lfk87.h"
#include "issi.h"
#include "lighting.h"
#include "action_layer.h"

//Define a shorter 'transparent' key code to make the keymaps more compact
#define KC_TR KC_TRNS

enum keymap_layout {
    VANILLA = 0,  // matches MF68 layout
    FUNC,         // 0x08
    SETTINGS,     // 0x10
};

// Colors of the layer indicator LED
// This list needs to define layer 0xFFFFFFFF, it is the end of the list, and the unknown layer
const Layer_Info layer_info[] = {
    // Layer     Mask           Red     Green   Blue
    {0x00000000, 0xFFFFFFFF, {0x00, 0x00, 0x00}}, // base layers - off
    {0x00000002, 0xFFFFFFFE, {0x00, 0x00, 0xFF}}, // function layer - blue
    {0x00000004, 0xFFFFFFFC, {0xFF, 0x00, 0xFF}}, // settings layer - magenta
    {0xFFFFFFFF, 0xFFFFFFFF, {0xFF, 0xFF, 0xFF}}, // unknown layer - REQUIRED - white
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[VANILLA] = KEYMAP(
    /* Keymap VANILLA: (Base Layer) Default Layer
    * ,-----------------------------------------------------------------------------.
    * |Esc  |f1| f2| f3| f4|  | f5| f6| f7| f8|   | f9|f10|f11|f12|  |Prnt|ScLk|Paus|
    * |-----------------------------------------------------------|  |--------------|
    * | ~ | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |  0| - | = |Backsp |  | Ins|Home|PgUp|
    * |-----------------------------------------------------------|  |--------------|
    * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|  | Del| End|PgDn|
    * |-----------------------------------------------------------|  `--------------'
    * |CAPS   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |
    * |-----------------------------------------------------------|        ,----.
    * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift     |        | Up |
    * |-----------------------------------------------------------|   ,-------------.
    * |Ctrl|Gui |Alt |      Space            |ALT |GUI |Func|CTRL |   |Lft| Dn |Rig |
    * `-----------------------------------------------------------'   `-------------'
    */
    KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, LGUI(KC_D), KC_F6, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, KC_PSCR, KC_SLCK, KC_PAUS, \
    KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_INS, KC_HOME, KC_PGUP, \
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_DELETE, KC_END, KC_PGDN, \
    KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,  \
    KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, \
    KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, KC_RGUI, MO(FUNC), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT),
    /* Keymap FUNCTION: Function Layer
    * ,-------------------------------------------------------------.  ,--------------.
    * |Esc  |f1| f2| f3| f4|  | f5| f6| f7| f8|   | f9|f10|f11|f12  |  |Prnt|ScLk|Paus|
    * |-------------------------------------------------------------|  |--------------|
    * | ` |F1 |F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|Delete   |  |    |    |    |
    * |-------------------------------------------------------------|  |--------------|
    * |Tab  |   |PgU|   |   |   |   |   | Up|   |   |   |   |       |  |    |    |    |
    * |-------------------------------------------------------------|  `--------------'
    * |Control|Hme|PgD|End|   |   |   |Lft|Dwn|Rgt|   |   |         |
    * |-------------------------------------------------------------|       ,----.
    * |Shift   |   |Del|   |   |   |   |Mute|V- |V+ |  |TG(SETTINGS)|       | Up |
    * |-------------------------------------------------------------'   ,-------------.
    * |Func|Win |Alt |        PgD           |Alt |Ctrl |Func |          |Lft| Dn |Rig |
    * `------------------------------------------------------'          `-------------'
    */
[FUNC] = KEYMAP(
    KC_ESC, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR,                        KC_PSCR, KC_SLCK, KC_PAUS, \
    KC_TR,  KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR, KC_TR,               KC_DEL,  KC_TR, KC_TR, KC_TR, \
    KC_NO,KC_NO, KC_PGUP, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_UP, KC_NO, KC_NO, KC_NO, KC_NO,               KC_NO,   KC_TR, KC_TR, KC_TR, \
    KC_TR, KC_HOME, KC_PGDN, KC_END, KC_NO, KC_NO, KC_NO, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO, KC_NO,            KC_NO, \
    KC_TR,    KC_NO,  KC_DEL,  KC_NO,  KC_NO, KC_NO, KC_NO, KC_MUTE, KC_VOLD, KC_VOLU, KC_NO,   TG(SETTINGS),                 KC_TR, \
    KC_TR,  KC_TR, KC_TR,                  KC_PGDN,                           KC_TR, KC_TR, KC_TR,  KC_TR,            KC_TR,  KC_TR, KC_TR),

    /* Keymap SETTINGS: Settings Layer
    * ,-----------------------------------------------------------.     ,-------------.
    * |Esc  |f1| f2| f3| f4|  | f5| f6| f7| f8|   | f9|f10|f11|f12  |  |Prnt|ScLk|Paus|
    * |-------------------------------------------------------------|  |--------------|
    * |FN0 |   |   |   |   |   |   |   |   |  |   |BL-|BL+|BL Togl|    |RGB Tog |Val+|
    * |-----------------------------------------------------------|    |-------------|
    * |MuMode|   |   |   |   |   |   |   |   |   |   |   |  |LEDTst|    |RGB Mode|Val-|
    * |-----------------------------------------------------------|    `-------------'
    * |AudTgl |Hz+|MS+|   |   |   |   |   |   |   |   |   |  RST  |
    * |-----------------------------------------------------------|      ,----.
    * |ClickTgl|Hz-|MS-|   |   |   |   |   |   |   |   |Layer Clr |      |Hue+|
    * |--------------------------------------------------------------------------.
    * |    |    |    |                       |    |    |    |     | |Sat-|Hue-|Sat+|
    * `----------------------------------------------------------------------------'
    */
[SETTINGS] = KEYMAP(
    KC_FN0,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, BL_DEC,            KC_NO,   KC_NO,   KC_NO,
    KC_FN0,KC_NO,KC_NO,KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, BL_DEC, BL_INC, BL_TOGG,  RGB_TOG, RGB_VAI, KC_NO,
    MU_MOD,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,    KC_FN2,  RGB_MOD, RGB_VAD, KC_NO,
    AU_TOG, KC_F1,KC_FN3, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,            RESET,
    KC_FN5, KC_FN2,KC_FN4, KC_NO, KC_NO, KC_NO, KC_NO, MU_TOG, KC_NO, KC_NO, KC_NO,                 KC_NO,           RGB_HUI,
    KC_NO, KC_NO, KC_NO,                  KC_FN12,                           KC_NO, KC_NO, KC_NO, KC_TR,     RGB_SAD, RGB_HUD, RGB_SAI),
};

const uint16_t PROGMEM fn_actions[] = {
    ACTION_FUNCTION(LFK_CLEAR),                               // FN0 - reset layers
    ACTION_FUNCTION(LFK_CLICK_FREQ_HIGHER),                   // FN1 - Increase Freq of audio click
    ACTION_FUNCTION(LFK_CLICK_FREQ_LOWER),                    // FN2 - Decrease Freq of audio click
    ACTION_FUNCTION(LFK_CLICK_TIME_LONGER),                   // FN3 - Increase length of audio click
    ACTION_FUNCTION(LFK_CLICK_TIME_SHORTER),                  // FN4 - Decrease length of audio click
    ACTION_FUNCTION(LFK_CLICK_TOGGLE),                        // FN5 - Toggle audio click
  };


const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    // MACRODOWN only works in this function
    switch(id) {
    }
    return MACRO_NONE;
};


void matrix_init_user(void) {
    // This keymap only has a single base layer, so reset the default if needed
    if(eeconfig_read_default_layer() > 1){
        eeconfig_update_default_layer(1);
        default_layer_set(1);
    }
}

void matrix_scan_user(void) {

}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void led_set_user(uint8_t usb_led) {

}
