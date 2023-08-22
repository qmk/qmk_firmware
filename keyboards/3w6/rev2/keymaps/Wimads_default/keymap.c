#include QMK_KEYBOARD_H

////BASIC DEFINITIONS////
//Layers//
enum layers {
    _QTY = 0, //default qwerty
    _NUM = 2, //numbers and symbol
    _NAV = 4, //navigation and miscelaneous keys
    _RST = 6, //reset keyboard
};

//Custom keycodes//
//Tap-hold keys:
#define DEL_RLT RALT_T(KC_DEL)  //DEL _ Left Windows
#define BSP_GUI LGUI_T(KC_BSPC) //BSPC _ Right Alt
#define XXX_NUM LT(_NUM, KC_X)  //S _ Num layer
#define DOT_NUM LT(_NUM, KC_DOT)//L _ Num layer
//Dead-hold keys:               //normal on tap, dead key on hold; requires "English(US)"+"Qwerty US" language+kbd settings in windows
#define DH_QUOT LT(11, KC_QUOT) //further defined in macro
#define DH_GRV  LT(11, KC_GRV)  //further defined in macro
#define DH_TILD LT(12, KC_TILD) //further defined in macro
#define DH_CIRC LT(12, KC_CIRC) //further defined in macro
//Other:
#define DOTCOMM LT(10, KC_DOT)  //KC_DOT, KC_COMM on shif; swap behavoiur by double tap (further defined in macro)
//Macros:
enum custom_keycodes {
        CLEARKB = SAFE_RANGE,   //clears all keys and/or layers that might be stuck
};

//Combos//
#include "g/keymap_combo.h" //included after custom keycodes, so custom keycodes can be used in combos.def

//Keymaps//
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  //Qwerty:
  [_QTY] = LAYOUT_Wimads(
      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,             KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
      KC_A,    KC_S,    KC_D,    KC_F,    KC_G,             KC_H,    KC_J,    KC_K,    KC_L,    DH_QUOT,
      KC_Z,    XXX_NUM, KC_C,    KC_V,    KC_B,             KC_N,    KC_M,    KC_COMM, DOT_NUM, KC_EXLM,
                        KC_LCTL, KC_LSFT, KC_LALT,          DEL_RLT, KC_SPC,  BSP_GUI
  ),
  //Numbers and symbols:
  [_NUM] = LAYOUT_Wimads(
      KC_AT,   KC_DLR,  KC_AMPR, KC_PIPE, DH_TILD,          DH_CIRC, KC_7,    KC_8,    KC_9,    KC_PERC,
      KC_LCBR, KC_LPRN, KC_RPRN, KC_RCBR, DH_GRV,           KC_PLUS, KC_4,    KC_5,    KC_6,    KC_MINS,
      KC_LBRC, KC_LT,   KC_GT,   KC_RBRC, KC_HASH,          KC_ASTR, KC_1,    KC_2,    KC_3,    KC_SLSH,
                        _______, _______, _______,          KC_UNDS, KC_0,    DOTCOMM
  ),
  //Navigation: //unused for now; experimenting with vertical combos for navigation
  [_NAV] = LAYOUT_Wimads(
      KC_PSCR, KC_BRK,  KC_INS,  XXXXXXX, KC_BTN5,          KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_VOLU,
      XXXXXXX, KC_SCRL, KC_F5,   XXXXXXX, KC_F5,            KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_VOLD,
      XXXXXXX, XXXXXXX, KC_CAPS, XXXXXXX, KC_BTN4,          KC_NUM,  KC_MENU, KC_BTN4, KC_BTN5, KC_MUTE,
                        _______, _______, _______,          _______, KC_F5,   _______
  ),
  //Reset/miscelaneous:
  [_RST] = LAYOUT_Wimads(
      QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, KC_INS,  XXXXXXX, KC_PSCR,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, KC_BTN4, KC_F5,   KC_BTN5, KC_BRK,
      XXXXXXX, XXXXXXX, CLEARKB, XXXXXXX, XXXXXXX,          KC_NUM,  KC_SCRL, KC_CAPS, XXXXXXX, XXXXXXX,
                        XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX
  ),
};//.keymaps

////CUSTOM KEY BEHAVIOURS////
//Tap-hold per key config:
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case DH_QUOT:
        case DH_GRV:
        case DH_TILD:
        case DH_CIRC:   return 200; //to be tweaked still
        case BSP_GUI:   return 300; //to reduce annoying accidental GUI presses
        default:        return TAPPING_TERM;
    }
};

//Customshift keycodes//
typedef struct _customshift_keycode_t { //define customshift functions
    uint16_t keycode_record;  //unmodified keycode
    uint16_t keycode_shifted; //alternate keycode to output on shift
} customshift_keycode_t;

#define KEY_MAP_SIZE 22 //amount of instances in customshift map

customshift_keycode_t keymap[KEY_MAP_SIZE] = { // customshift mapping, format: {keycode_record, keycode_shifted}
    //Numbers and F-keys
    {KC_CIRC, KC_F12},   {KC_7,    KC_F7},    {KC_8,    KC_F8},    {KC_9,    KC_F9}, //F12  F7  F8  F9
    {KC_PLUS, KC_F11},   {KC_4,    KC_F4},    {KC_5,    KC_F5},    {KC_6,    KC_F6}, //F11  F4  F5  F6
    {KC_ASTR, KC_F10},   {KC_1,    KC_F1},    {KC_2,    KC_F2},    {KC_3,    KC_F3}, //F10  F1  F2  F3
    //punctuation
    {KC_EXLM, KC_QUES},  {KC_COMM, KC_SCLN},  {KC_DOT,  S(KC_SCLN)}, // !?  ,;  .:
    //symbols
    {KC_SLSH, KC_BSLS},  {KC_PIPE, KC_BSLS},  {KC_DLR,  RALT(KC_5)}, // /\  |\  $€
    {KC_LCBR, KC_LBRC},  {KC_RCBR, KC_RBRC},  //brackets for qwertai
    //Volume and brightness
    {KC_VOLU, KC_BRIU},  {KC_VOLD, KC_BRID},
};

int get_index_customshift(uint16_t keycode_record) { //find corresponding item in customshift map for pressed key
    for (int i = 0; i < KEY_MAP_SIZE; i++) {
        if (keymap[i].keycode_record == keycode_record) return i;
    }
    return -1; //return -1 if pressed key is not in customshift map
};

//Macros//
bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    int index = get_index_customshift(keycode);// check if keycode is in customshift map
    const uint16_t mod_shift = get_mods() & MOD_MASK_SHIFT; //track shift state for customshift behaviours
    static bool dotcomm_state = true; //true = dot; false = comma;
    switch(keycode) {
        //general keycodes
        case CLEARKB:
            if (record->event.pressed) {
                clear_keyboard(); //clears all keys and modifiers that might be stuck
                layer_clear();    //clears all layers that might be stuck
            } return false;
        case DOTCOMM:
            if (record->event.pressed && record->tap.count == 2) {//swap DOTCOMM state on double tap
                dotcomm_state = !dotcomm_state; //swap state
                tap_code16(KC_BSPC);            //remove character output from first tap
            } else if (record->event.pressed && dotcomm_state) {//when state is true
                if (mod_shift) { //send comm when shifted
                    unregister_mods(mod_shift);
                    tap_code16(KC_COMM);
                    register_mods(mod_shift);
                } else { //send dot by default
                    tap_code16(KC_DOT);
                }
            } else if (record->event.pressed) {//when state is false
                if (mod_shift) { //send dot when shifted
                    unregister_mods(mod_shift);
                    tap_code16(KC_DOT);
                    register_mods(mod_shift);
                } else { //send comm by default
                    tap_code16(KC_COMM);
                }
            } return false;

        //Dead-hold keys:
        case DH_QUOT:
            if (record->event.pressed && !record->tap.count) { //if tapped, behave as normal key
                tap_code16(KC_QUOT); tap_code16(KC_SPC);
            } else if (record->event.pressed) { //if held, behave as dead key
                tap_code16(KC_QUOT);
                if (mod_shift) {unregister_mods(mod_shift);} //unregister shift to resolve conflict of holding shifted dead key
            } return false;
        case DH_GRV:
            if (record->event.pressed && record->tap.count) {
                tap_code16(KC_GRV); tap_code16(KC_SPC);
            } else if (record->event.pressed) {
                tap_code16(KC_GRV); layer_off(_NUM);
            } return false;
        case DH_TILD:
            if (record->event.pressed && record->tap.count) {
                tap_code16(S(KC_GRV)); tap_code16(KC_SPC);
            } else if (record->event.pressed) {
                tap_code16(S(KC_GRV)); layer_off(_NUM);
            } return false;
        case DH_CIRC:
            if (record->event.pressed && record->tap.count) {
                tap_code16(S(KC_6)); tap_code16(KC_SPC);
            } else if (record->event.pressed) {
                tap_code16(S(KC_6)); layer_off(_NUM);
            } return false;

        case DOT_NUM: //customshift
            if (record->event.pressed && mod_shift) {
                unregister_mods(mod_shift);
                tap_code16(S(KC_SCLN));
                register_mods(mod_shift);
                return false;
            } return true;

        //customshift:
        default:
            if (index != -1) { //if key is in customshift map, then:
                if (record->event.pressed && mod_shift) { //shifted action
                    unregister_mods(mod_shift);
                    tap_code16(keymap[index].keycode_shifted); //custom shift key
                    register_mods(mod_shift);
                    return false; //ignore default shift behaviour
                } return true; //return as normal when not shifted
            }//end of if(index != -1)
    }//end of switch(keycode)
    return true; //if key is not in customshift map or other macro, return normal key behaviour
};

////LED INDICATORS////
//TBD
