//*********WIMADS SKELETYL-CHARYBDIS MOD**********//
/* TO DO:
* per key tapping term
*/

#include QMK_KEYBOARD_H

//override charybdis layout
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

/*********KEYMAPS*******/
enum charybdis_keymap_layers {
    _QTY = 1, //default qwerty
    _QAI = 0, //qwertai
    _NUM = 2, //numbers and symbol
    _QNM = 3, //numbers for qwertai
    _NAV = 4, //navigation and miscelaneous keys
    _QNV = 5, //navigation for Qwertai
    _RST = 6, //reset keyboard
};

enum custom_keycodes {
        CLEARKB = SAFE_RANGE,   //clears all keys and/or layers that might be stuck
        DRGZOOM, //ctrl + drgscrl (defined in macro, since C(DRGSCRL) doesn't work)
        SNIPE,
        SETQAI, SETQTY,
};
//Custom keycodes:
#define DRGcTOG DRG_TOG         //DRG_TOG for combos (for some reason DRG_TOG keycode doesn't work in combos.def)
#define DRGcSCR DRGSCRL
#define DOTCOMM LT(10, KC_DOT)  //KC_DOT, KC_COMM on shif; swap behavoiur by double tap (further defined in macro)
#define DEL_RLT RALT_T(KC_DEL)  //DEL _ Left Windows
#define BSP_GUI LGUI_T(KC_BSPC) //BSPC _ Right Alt
#define XXX_NUM LT(_NUM, KC_X)  //S _ Num layer
#define FFF_NAV LT(_NAV, KC_F)  //F _ Nav layer
#define DOT_NUM LT(_NUM, KC_DOT)  //L _ Num layer
#define JJJ_NAV LT(_NAV, KC_J)  //J _ Nav layer
#define UUU_DRG LT(10, KC_U)    //U _ dragscroll
#define DDD_SNI LT(10, KC_D)    //D _ snipe

#define BSP_QNM LT(_QNM, KC_BSPC)
#define SPC_SFT LSFT_T(KC_SPC)
#define SFTLOCK LSFT_T(KC_NO) //further defined in macro
#define QNMLOCK LT(_QNM, KC_NO) //further defined in macro


#include "g/keymap_combo.h"     //include combo dictionary after custom keycodes, so custom keycodes can be used in combos.def

//Keymaps
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QTY] = LAYOUT_Wimads( //default layer
      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,             KC_Y,    UUU_DRG, KC_I,    KC_O,    KC_P,
      KC_A,    KC_S,    DDD_SNI, FFF_NAV, KC_G,             KC_H,    JJJ_NAV, KC_K,    KC_L,    KC_QUOT,
      KC_Z,    XXX_NUM, KC_C,    KC_V,    KC_B,             KC_N,    KC_M,    KC_COMM, DOT_NUM, KC_EXLM,
                        KC_LCTL, KC_LSFT, KC_LALT,          DEL_RLT, KC_SPC,  BSP_GUI  //trackball: default
  ),
  [_QAI] = LAYOUT_Wimads( //default layer
      SNIPE,   KC_BTN2, DRGcSCR, KC_BTN1, XXXXXXX,          XXXXXXX, KC_BTN1, DRGcSCR, KC_BTN2, DRGSCRL,
      KC_R,    KC_O,    KC_I,    KC_T,    XXXXXXX,          XXXXXXX, KC_T,    KC_I,    KC_O,    KC_R,
      KC_A,    KC_S,    KC_E,    KC_N,    XXXXXXX,          XXXXXXX, KC_N,    KC_E,    KC_S,    KC_A,
                        BSP_QNM, SPC_SFT, XXXXXXX,          XXXXXXX, SPC_SFT, BSP_QNM  //trackball: default
  ),
  [_NUM] = LAYOUT_Wimads( //number and symbol layer
      KC_AT,   KC_DLR,  KC_AMPR, KC_PIPE, KC_TILD,          KC_CIRC, KC_7,    KC_8,    KC_9,    KC_PERC,
      KC_LCBR, KC_LPRN, KC_RPRN, KC_RCBR, KC_GRV,           KC_PLUS, KC_4,    KC_5,    KC_6,    KC_MINS,
      KC_LBRC, KC_LT,   KC_GT,   KC_RBRC, KC_HASH,          KC_ASTR, KC_1,    KC_2,    KC_3,    KC_SLSH,
                        _______, _______, _______,          KC_UNDS, KC_0,    DOTCOMM  //trackball: snipe
  ),
  [_QNM] = LAYOUT_Wimads( //number and symbol layer
      XXXXXXX, KC_BTN4, KC_F5,   KC_BTN5, XXXXXXX,          XXXXXXX, KC_BTN4, KC_F5,   KC_BTN5, XXXXXXX,
      KC_0,    KC_9,    KC_8,    KC_7,    XXXXXXX,          XXXXXXX, KC_7,    KC_8,    KC_9,  KC_0,
      DOTCOMM, KC_3,    KC_2,    KC_1,    XXXXXXX,          XXXXXXX, KC_1,    KC_2,    KC_3,  DOTCOMM,
                        _______, _______, XXXXXXX,          XXXXXXX, _______, _______  //trackball: snipe
  ),
  [_NAV] = LAYOUT_Wimads( //navigation and misc layer
      KC_PSCR, KC_BRK,  KC_INS,  XXXXXXX, KC_BTN5,          KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_VOLU,
      XXXXXXX, KC_SCRL, KC_F5,   XXXXXXX, KC_F5,            KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_VOLD,
     DF(_QAI), XXXXXXX, KC_CAPS, XXXXXXX, KC_BTN4,          KC_NUM,  KC_MENU, KC_BTN4, KC_BTN5, KC_MUTE,
                        _______, _______, _______,          _______, KC_F5,   _______  //trackball: dragscroll
  ),
  [_QNV] = LAYOUT_Wimads( //navigation and misc layer
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      KC_DEL,  KC_HOME, KC_UP,   KC_END,  XXXXXXX,          XXXXXXX, KC_HOME, KC_UP,   KC_END,  KC_DEL,
     DF(_QTY), KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX,          XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, DF(_QTY),
                        KC_BSPC, _______, XXXXXXX,          XXXXXXX, _______, KC_BSPC  //trackball: dragscroll
  ),
  [_RST] = LAYOUT_Wimads( //reset layer
      QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
     DF(_QAI), XXXXXXX, CLEARKB, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                        XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX  //trackball: default
  ),
};

/*********CUSTOM KEY BEHAVIOURS********/

//Turn combos on or off per layer:
bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    switch (combo_index) {
        case QTY_CS ... QTYrDRT:
            if (_QAI == get_highest_layer(default_layer_state)){
                return false;
            }
        case QAI_Q ... QAI_DRTG:
            if (_QTY == get_highest_layer(default_layer_state)) {
                return false;
            }
    }
    return true;
}

//Tap-hold configuration
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SPC_SFT:   return 150;
        case BSP_QNM:   return 150;
        case KC_A:
        case KC_S:
        case KC_E:
        case KC_N:      return 250;
        default:        return TAPPING_TERM;
    }
}

//customshift keycodes:
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
    {KC_LPRN, KC_LCBR},  {KC_RPRN, KC_RCBR},  //brackets for qwertai
    //Volume and brightness
    {KC_VOLU, KC_BRIU},  {KC_VOLD, KC_BRID},
};

int get_index_customshift(uint16_t keycode_record) { //find corresponding item in customshift map for pressed key
    for (int i = 0; i < KEY_MAP_SIZE; i++) {
        if (keymap[i].keycode_record == keycode_record) return i;
    }
    return -1; //return -1 if pressed key is not in customshift map
};

//macros:
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

        case SPC_SFT: //send ". " on double tap space
            if (record->event.pressed && record->tap.count == 2) {
                tap_code16(KC_BSPC);
                tap_code16(KC_DOT);
                tap_code16(KC_SPC);
                return false;
            } return true;

        //QWERTAI keycodes:
        case SFTLOCK:
            if (record->event.pressed && !mod_shift && record->tap.count) { //if no shift is active
                add_mods(MOD_MASK_SHIFT); //toggle shiftlock on when tapped
                return false;
            } else if (record->event.pressed && mod_shift) { //if shift is active
                unregister_mods(mod_shift); //turn shiftlock off when tapped or held
                return false;
            } return true; //else behaves as normal lsft key.
        case QNMLOCK:
            if (record->event.pressed && record->tap.count) {
                layer_invert(_QNM); // when tapped invert layer state (toggle)
                return false;
            } return true; //else behaves as normal layer modifier key.


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
        case XXX_NUM: //sniping
        case DDD_SNI:
        case SNIPE:
            if (record->event.pressed) {
                charybdis_set_pointer_sniping_enabled(true);
            } else {
                charybdis_set_pointer_sniping_enabled(false);
            } return true;
        case DOT_NUM: //shiping and custom shift
            if (record->event.pressed && mod_shift) {
                charybdis_set_pointer_sniping_enabled(true);
                unregister_mods(mod_shift);
                tap_code16(S(KC_SCLN));
                register_mods(mod_shift);
                return false;
            } else if (record->event.pressed) {
                charybdis_set_pointer_sniping_enabled(true);
            } else {
                charybdis_set_pointer_sniping_enabled(false);
            } return true;
        case UUU_DRG:
        case FFF_NAV:
        case JJJ_NAV: //dragscroll
            if (record->event.pressed) {
                charybdis_set_pointer_dragscroll_enabled(true);
            } else {
                charybdis_set_pointer_dragscroll_enabled(false);
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
