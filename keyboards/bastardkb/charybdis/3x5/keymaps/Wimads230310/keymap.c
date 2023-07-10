//*********WIMADS SKELETYL MOD**********//
#include QMK_KEYBOARD_H

//override charybdis layout
#define LAYOUT_Wimads(                                   \
  k00, k01, k02, k03, k04,      k44, k43, k42, k41, k40, \
  k10, k11, k12, k13, k14,      k54, k53, k52, k51, k50, \
  k20, k21, k22, k23, k24,      k64, k63, k62, k61, k60, \
  k34, k31, k32, k33, k30,      k70, k73, k72            \
)                                                        \
{                                                        \
  {   k00,   k01,   k02,   k03,   k04 },                 \
  {   k10,   k11,   k12,   k13,   k14 },                 \
  {   k20,   k21,   k22,   k23,   k24 },                 \
  {   k30,   k31,   k32,   k33,   k34 },                 \
  {   k40,   k41,   k42,   k43,   k44 },                 \
  {   k50,   k51,   k52,   k53,   k54 },                 \
  {   k60,   k61,   k62,   k63,   k64 },                 \
  {   k70, KC_NO,   k72,   k73, KC_NO },                 \
}

/*********KEYMAPS*******/
//layers
enum charybdis_keymap_layers {
    _DEF = 0, //default
    _NAV = 1, //navigation and F-keys
    _NUM = 2, //numbers and symbols
    _RESET = 3, //reset keyboard
    //_NUMLEGACY = 4, //legacy numbers and symbols layer
};

//Custom Keycodes
enum custom_keycodes {
    //Switch windows keyboard language
    CLEARKB = CHARYBDIS_SAFE_RANGE, //clears all registered keycodes, to solve stuck keycodes/layers/modifiers
    ZOOM, //ctrl + drgscrl
    RALTNUM //combo for RALT(_NUM(keycode))
};

#define DEL_NAV LT(_NAV, KC_DEL)
#define BSP_NUM LT(_NUM, KC_BSPC)

#include "g/keymap_combo.h"

//Keymaps
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_DEF] = LAYOUT_Wimads(
  // ╭────────────────────────────────────────────╮                   ╭─────────────────────────────────────────────╮
      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
  // ├────────────────────────────────────────────┤                   ├─────────────────────────────────────────────┤
      KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT,
  // ├────────────────────────────────────────────┤                   ├─────────────────────────────────────────────┤
      KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_EXLM,
  // ╰─────────────────────────────────────────────────────╮  ╭─────────────────────────────────────────────────────╯
             KC_BTN1, KC_BTN2,   KC_LALT, KC_LSFT, KC_LCTL,    DEL_NAV, KC_SPC,  BSP_NUM   //trackball = mouse
  //        ╰─────────────────╯ ╰──────────────────────────╯  ╰──────────────────────────╯
  ),

  [_NUM] = LAYOUT_Wimads(
  // ╭────────────────────────────────────────────╮                   ╭─────────────────────────────────────────────╮
      KC_AT,   KC_DLR,  KC_AMPR, KC_PIPE, KC_PLUS,                      KC_GRV,  KC_UNDS, KC_LPRN, KC_RPRN, KC_PERC,
  // ├────────────────────────────────────────────┤                   ├─────────────────────────────────────────────┤
      KC_1,    KC_2,    KC_3,    KC_4,    KC_MINS,                      KC_HASH, KC_7,    KC_8,    KC_9,    KC_0,
  // ├────────────────────────────────────────────┤                   ├─────────────────────────────────────────────┤
      KC_SLSH, KC_ASTR, KC_CIRC, KC_5,    KC_EQL,                       KC_TILD, KC_6,    KC_LT,   KC_GT,   KC_BSLS,
  // ╰─────────────────────────────────────────────────────╮  ╭─────────────────────────────────────────────────────╯
             KC_COMM,  KC_DOT,   _______, _______, _______,    KC_RCTL, KC_RSFT, _______   //trackball = scroll
  //        ╰─────────────────╯ ╰──────────────────────────╯  ╰──────────────────────────╯
  ),

  [_NAV] = LAYOUT_Wimads(
  // ╭────────────────────────────────────────────╮                   ╭─────────────────────────────────────────────╮
      KC_PSCR, XXXXXXX, KC_INS,  XXXXXXX, XXXXXXX,                      KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_VOLU,
  // ├────────────────────────────────────────────┤                   ├─────────────────────────────────────────────┤
      XXXXXXX, KC_SCRL, XXXXXXX, XXXXXXX, KC_NUM,                       KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_VOLD,
  // ├────────────────────────────────────────────┤                   ├─────────────────────────────────────────────┤
      XXXXXXX, KC_NO,   KC_CAPS, KC_MENU, KC_BRK,                       XXXXXXX, KC_BTN4, KC_F5,   KC_BTN5, KC_MUTE,
  // ╰─────────────────────────────────────────────────────╮  ╭─────────────────────────────────────────────────────╯
             XXXXXXX, XXXXXXX,   _______, _______, _______,    _______, XXXXXXX, DRG_TOG   //trackball = sniping mouse
  //        ╰─────────────────╯ ╰──────────────────────────╯  ╰──────────────────────────╯
  ),

  [_RESET] = LAYOUT_Wimads(
  // ╭────────────────────────────────────────────╮                   ╭─────────────────────────────────────────────╮
      QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├────────────────────────────────────────────┤                   ├─────────────────────────────────────────────┤
      CLEARKB, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├────────────────────────────────────────────┤                   ├─────────────────────────────────────────────┤
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ╰─────────────────────────────────────────────────────╮  ╭─────────────────────────────────────────────────────╯
             XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX   //trackball = mouse
  //        ╰─────────────────╯ ╰──────────────────────────╯  ╰──────────────────────────╯
  ),

  /*[_NUMLEGACY] = LAYOUT_Wimads(
  // ╭────────────────────────────────────────────╮                   ╭─────────────────────────────────────────────╮
      KC_ASTR, KC_7,    KC_8,    KC_9,    KC_PLUS,                      KC_DLR,  KC_UNDS, KC_LPRN, KC_RPRN, KC_PERC,
  // ├────────────────────────────────────────────┤                   ├─────────────────────────────────────────────┤
      KC_SLSH, KC_4,    KC_5,    KC_6,    KC_MINS,                      KC_HASH, KC_LCBR, KC_LBRC, KC_RBRC, KC_RCBR,
  // ├────────────────────────────────────────────┤                   ├─────────────────────────────────────────────┤
      KC_CIRC, KC_1,    KC_2,    KC_3,    KC_EQL,                       KC_PIPE, KC_AMPR, KC_LT,   KC_GT,   KC_BSLS,
  // ╰─────────────────────────────────────────────────────╮  ╭─────────────────────────────────────────────────────╯
             KC_0,    KC_PDOT,   _______, _______, _______,    KC_RCTL, KC_RSFT, _______   //trackball = scroll
  //        ╰─────────────────╯ ╰──────────────────────────╯  ╰──────────────────────────╯
  ),*/

};

/*********CUSTOM KEY BEHAVIOURS********/
//customshift keycodes:
typedef struct _customshift_keycode_t { //define customshift functions
    uint16_t keycode_record;  //key input
    uint16_t keycode_shifted; //key output on shift
} customshift_keycode_t;

#define KEY_MAP_SIZE 22 //amount of keys in customshift map (30 on _DEF, 30 on _NUMLEGACY)

customshift_keycode_t keymap[KEY_MAP_SIZE] = { // customshift mapping, format: {keycode_record, keycode_shifted}
    //Numbers and Fn-keys
    {KC_1,    KC_F1},    {KC_2,    KC_F2},    {KC_3,    KC_F3},
    {KC_4,    KC_F4},    {KC_5,    KC_F5},    {KC_6,    KC_F6},
    {KC_7,    KC_F7},    {KC_8,    KC_F8},    {KC_9,    KC_F9},
    {KC_0,    KC_F10},   {KC_SLSH, KC_F11},   {KC_ASTR, KC_F12},

    //punctuation
    {KC_COMM, KC_SCLN},  {KC_DOT,  KC_COLN},  {KC_EXLM, KC_QUES},

    //brackets
    {KC_LPRN, KC_LCBR},  {KC_RPRN, KC_RCBR},  {KC_LT,   KC_LBRC},  {KC_GT,   KC_RBRC},

    //symbols
    {KC_DLR,  RALT(KC_5)},

    //Volume and brightness
    {KC_VOLU, KC_BRIU},  {KC_VOLD, KC_BRID},
};

int get_index_customshift(uint16_t keycode_record) { //find corresponding item in customshift map for pressed key
    for (int i = 0; i < KEY_MAP_SIZE; i++) {
        if (keymap[i].keycode_record == keycode_record) return i;
    }
    return -1; //return -1 if pressed key is not in customshift map
};

//macros: customshift, custom combos:
bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    int index = get_index_customshift(keycode);// check if keycode is in customshift map
    const uint16_t mod_shift = get_mods() & MOD_MASK_SHIFT; //track shift state for customshift behaviours
    switch(keycode) {
        case CLEARKB:
            if (record->event.pressed) {
                clear_keyboard(); //clears all keys and modifiers that might be stuck
                layer_clear(); //clears all layers that might be stuck
            } return false;
        case RALTNUM: //combo ALT + BSP_NUM
            if (record->event.pressed) {
                register_code16(KC_RALT);
                layer_on(_NUM);
            } else {
                layer_off(_NUM);
                unregister_code16(KC_RALT);
            } return false;

        //trackball behaviours:
        case ZOOM: //combo X + C
            if (record->event.pressed) {
                register_code16(KC_LCTL);
                wait_ms(10);
                charybdis_set_pointer_dragscroll_enabled(true);
            } else {
                charybdis_set_pointer_dragscroll_enabled(false);
                wait_ms(10);
                unregister_code16(KC_LCTL);
            } return false;
        case DEL_NAV:
            if (record->event.pressed) {
                charybdis_set_pointer_sniping_enabled(true);
            } else {
                charybdis_set_pointer_sniping_enabled(false);
            } return true;
        case BSP_NUM:
            if (record->event.pressed) {
                charybdis_set_pointer_dragscroll_enabled(true);
            } else {
                charybdis_set_pointer_dragscroll_enabled(false);
            } return true;

        //execute customshift keys:
        default:
            if (index != -1) { //if key is in customshift map, then:
                if (record->event.pressed && mod_shift) { //shifted action
                    unregister_mods(mod_shift);
                    tap_code16(keymap[index].keycode_shifted); //custom shift key
                    register_mods(mod_shift);
                    return false; //ignore standard shift behaviour
                } return true; //return as normal when not shifted
            }//end of if(index != -1)
    }//end of switch(keycode)
    return true; //if key is not in customshift map or other macro, return normal key behaviour
};

