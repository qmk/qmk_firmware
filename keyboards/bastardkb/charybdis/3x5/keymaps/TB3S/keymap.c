//*********WIMADS SKELETYL-CHARYBDIS MOD**********//
/* TO DO:
* trackball behaniour on layers (snipe/scroll)
* Fn keys
* clean up customshift
* explore quantum modifier idea
* wrap deadhold feature into customshift code
*/

#include QMK_KEYBOARD_H

////KEYMAP DEFINITIONS////
//Override charybdis layout:
#define LAYOUT_Wimads(                                   \
  k00, k01, k02, k03, k04,      k44, k43, k42, k41, k40, \
  k10, k11, k12, k13, k14,      k54, k53, k52, k51, k50, \
  k20, k21, k22, k23, k24,      k64, k63, k62, k61, k60, \
            k32, k33, k30,      k70, k73, k72            \
)                                                        \
{                                                        \
  {   k00,   k01,   k02,   k03,   k04 },                 \
  {   k10,   k11,   k12,   k13,   k14 },                 \
  {   k20,   k21,   k22,   k23,   k24 },                 \
  {   k30, KC_NO,   k32,   k33, KC_NO },                 \
  {   k40,   k41,   k42,   k43,   k44 },                 \
  {   k50,   k51,   k52,   k53,   k54 },                 \
  {   k60,   k61,   k62,   k63,   k64 },                 \
  {   k70, KC_NO,   k72,   k73, KC_NO },                 \
}

enum charybdis_keymap_layers {
    _QAI = 0, //qwertai
    _NUM = 1, //numbers and symbols
    _NAV = 2, //navigation
    _CTL = 3, //simplified common ctrl short cuts
};

enum custom_keycodes {
        CLEARKB = SAFE_RANGE,   //clears all keys and/or layers that might be stuck
        DRGZOOM, //ctrl + drgscrl (defined in macro, since C(DRGSCRL) doesn't work)
};

//Custom keycodes:
#define DOTCOMM LT(10, KC_DOT)    //KC_DOT or KC_COMM depending on state (further defined in macro)
#define BSP_NUM LT(_NUM, KC_BSPC) //backspace, _NUM layer on hold
#define SPC_SFT LSFT_T(KC_SPC)    //space, shift on hold

//Dead-hold keys:               //normal on tap, dead key on hold; requires "English(US)"+"Qwerty US" language+kbd settings in windows
#define DH_QUOT LT(11, KC_QUOT) //further defined in macro
#define DH_GRV  LT(11, KC_GRV)  //further defined in macro
#define DH_TILD LT(12, KC_TILD) //further defined in macro
#define DH_CIRC LT(12, KC_CIRC) //further defined in macro

//Combo keycodes:       //workaround for using charybdis keycodes in combos.def
#define DRGTOGc DRG_TOG //toggle dragscroll
#define DRGSCRc DRGSCRL //dragscroll
#define SNIPINc SNIPING //sniping


#include "g/keymap_combo.h" //include combo dictionary after custom keycodes, so custom keycodes can be used in combos.def

//Keymaps:
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QAI] = LAYOUT_Wimads( //default layer
      SNIPINc, KC_BTN2, DRGSCRc, KC_BTN1, XXXXXXX,          XXXXXXX, KC_BTN1, DRGSCRc, KC_BTN2, DRGSCRL,
      KC_R,    KC_O,    KC_I,    KC_T,    XXXXXXX,          XXXXXXX, KC_T,    KC_I,    KC_O,    KC_R,
      KC_A,    KC_S,    KC_E,    KC_N,    XXXXXXX,          XXXXXXX, KC_N,    KC_E,    KC_S,    KC_A,
                        BSP_NUM, SPC_SFT, XXXXXXX,          XXXXXXX, SPC_SFT, BSP_NUM  //trackball: default
  ),
  [_NUM] = LAYOUT_Wimads( //number and symbol layer
      XXXXXXX, KC_BTN4, KC_F5,   KC_BTN5, XXXXXXX,          XXXXXXX, KC_BTN4, KC_F5,   KC_BTN5, XXXXXXX,
      DOTCOMM, KC_9,    KC_8,    KC_7,    XXXXXXX,          XXXXXXX, KC_7,    KC_8,    KC_9,    DOTCOMM,
      KC_0,    KC_3,    KC_2,    KC_1,    XXXXXXX,          XXXXXXX, KC_1,    KC_2,    KC_3,    KC_0,
                        _______, _______, XXXXXXX,          XXXXXXX, _______, _______  //trackball: snipe
  ),
  [_NAV] = LAYOUT_Wimads( //navigation
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      KC_PGUP, KC_HOME, KC_UP,   KC_END,  XXXXXXX,          XXXXXXX, KC_HOME, KC_UP,   KC_END,  KC_PGUP,
      KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX,          XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,
                        _______, _______, XXXXXXX,          XXXXXXX, _______, _______  //trackball: dragscroll
  ),
  [_CTL] = LAYOUT_Wimads( //short cuts
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      C(KC_Z), KC_BTN4, KC_BTN5, C(KC_Y), XXXXXXX,          XXXXXXX, C(KC_Y), KC_BTN4, KC_BTN5, C(KC_Z),
      C(KC_A), C(KC_X), C(KC_C), C(KC_V), XXXXXXX,          XXXXXXX, C(KC_V), C(KC_C), C(KC_X), C(KC_A),
                        _______, _______, XXXXXXX,          XXXXXXX, _______, _______  //trackball: default
  ),
};

////CUSTOM KEY BEHAVIOURS////
//Tap-hold configuration:
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SPC_SFT:   return 150;
        case BSP_NUM:   return 130;
        default:        return TAPPING_TERM;
    }
}

//Customshift feature:
typedef struct _customshift_keycode_t { //define customshift functions
    uint16_t keycode_record;  //unmodified keycode
    uint16_t keycode_shifted; //alternate keycode to output on shift
} customshift_keycode_t;

#define KEY_MAP_SIZE 22 //amount of instances in customshift map

customshift_keycode_t keymap[KEY_MAP_SIZE] = { // customshift mapping, format: {keycode_record, keycode_shifted}
    //Numbers and F-keys:
    {KC_CIRC, KC_F12},   {KC_7,    KC_F7},    {KC_8,    KC_F8},    {KC_9,    KC_F9}, //F12  F7  F8  F9
    {KC_PLUS, KC_F11},   {KC_4,    KC_F4},    {KC_5,    KC_F5},    {KC_6,    KC_F6}, //F11  F4  F5  F6
    {KC_ASTR, KC_F10},   {KC_1,    KC_F1},    {KC_2,    KC_F2},    {KC_3,    KC_F3}, //F10  F1  F2  F3
    //punctuation:
    {KC_EXLM, KC_QUES},  {KC_COMM, KC_SCLN},  {KC_DOT,  S(KC_SCLN)}, // !?  ,;  .:
    //symbols:
    {KC_SLSH, KC_BSLS},  {KC_PIPE, KC_BSLS},  {KC_DLR,  RALT(KC_5)}, // /\  |\  $€
    {KC_LCBR, KC_LBRC},  {KC_RCBR, KC_RBRC},  //brackets for qwertai
    //Volume and brightness:
    {KC_VOLU, KC_BRIU},  {KC_VOLD, KC_BRID},
};

int get_index_customshift(uint16_t keycode_record) { //find corresponding item in customshift map for pressed key
    for (int i = 0; i < KEY_MAP_SIZE; i++) {
        if (keymap[i].keycode_record == keycode_record) return i;
    }
    return -1; //return -1 if pressed key is not in customshift map
};

///Macros:
bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    int index = get_index_customshift(keycode);// check if keycode is in customshift map
    const uint16_t mod_shift = get_mods() & MOD_MASK_SHIFT; //track shift state for customshift behaviours
    static bool dotcomm_state = true; //true = dot; false = comma;
    switch(keycode) {
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
            if (record->event.pressed && record->tap.count) { //if tapped, behave as normal key
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

        //trackball behaviours:
        case DRGZOOM: //LCTL(DRGSCRL)
            if (record->event.pressed) {
                register_code16(KC_LCTL);
                wait_ms(10);
                charybdis_set_pointer_dragscroll_enabled(true);
            } else {
                charybdis_set_pointer_dragscroll_enabled(false);
                wait_ms(10);
                unregister_code16(KC_LCTL);
            } return false;

        //customshift:
        default:
            if (index != -1) { //if key is in customshift map, then:
                if (record->event.pressed && mod_shift) { //shifted action
                    unregister_mods(mod_shift);
                    tap_code16(keymap[index].keycode_shifted); //custom shift key
                    register_mods(mod_shift);
                    return false; //ignore default shift behaviour
                } return true; //return as normal when not shifted
            }//.if(index != -1)
    }//.switch(keycode)
    return true; //if key is not in customshift map or other macro, return normal key behaviour
};
