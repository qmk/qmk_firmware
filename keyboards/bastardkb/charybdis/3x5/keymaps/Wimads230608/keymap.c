//*********WIMADS SKELETYL-CHARYBDIS MOD**********//
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
    _DEF = 0, //default qwerty
    _EXP = 1, //experimental layer for trying out alternative layouts
    _NUM = 2, //numbers and symbols
    _NAV = 3, //navigation and miscelaneous keys
    _RST = 4, //reset keyboard
};

enum custom_keycodes {
        CLEARKB = SAFE_RANGE,   //clears all keys and/or layers that might be stuck
        DRGZOOM,                //ctrl + drgscrl (defined in macro, since C(DRGSCRL) doesn't work)
};
//Custom keycodes:
#define DRGcTOG DRG_TOG         //DRG_TOG for combos (for some reason DRG_TOG keycode doesn't work in combos.def)
#define DOTCOMM LT(10, KC_DOT)  //KC_DOT, KC_COMM on shif; swap behavoiur by double tap (further defined in macro)
#define DEL_RLT RALT_T(KC_DEL)  //DEL _ Left Windows
#define BSP_GUI LGUI_T(KC_BSPC) //BSPC _ Right Alt
#define XXX_NUM LT(_NUM, KC_X)  //S _ Num layer
#define FFF_NAV LT(_NAV, KC_F)  //F _ Nav layer
#define DOT_NUM LT(_NUM, KC_DOT)  //L _ Num layer
#define JJJ_NAV LT(_NAV, KC_J)  //J _ Nav layer
#define UUU_DRG LT(10, KC_U)    //U _ dragscroll

#include "g/keymap_combo.h"     //include combo dictionary after custom keycodes, so custom keycodes can be used in combos.def

//Keymaps
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_DEF] = LAYOUT_Wimads( //default layer
      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,             KC_Y,    UUU_DRG, KC_I,    KC_O,    KC_P,
      KC_A,    KC_S,    KC_D,    FFF_NAV, KC_G,             KC_H,    JJJ_NAV, KC_K,    KC_L,    KC_QUOT,
      KC_Z,    XXX_NUM, KC_C,    KC_V,    KC_B,             KC_N,    KC_M,    KC_COMM, DOT_NUM, KC_EXLM,
                        KC_LCTL, KC_LSFT, KC_LALT,          DEL_RLT, KC_SPC,  BSP_GUI  //trackball: default
  ),
/*[_EXP] = LAYOUT_Wimads( //experimental layer, for trying out alternative layouts like dvorak
      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,             KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
      KC_A,    XXX_NUM, KC_D,    FFF_NAV, KC_G,             KC_H,    JJJ_NAV, KC_K,    DOT_NUM, KC_QUOT,
      KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_EXLM,
                        KC_LALT, KC_LSFT, KC_LCTL,          DEL_RLT, KC_SPC,  BSP_GUI  //trackball mode: default
  ),*/
  [_NUM] = LAYOUT_Wimads( //number and symbol layer
      KC_AT,   KC_DLR,  KC_AMPR, KC_PIPE, KC_TILD,          KC_CIRC, KC_7,    KC_8,    KC_9,    KC_PERC,
      KC_LCBR, KC_LPRN, KC_RPRN, KC_RCBR, KC_GRV,           KC_PLUS, KC_4,    KC_5,    KC_6,    KC_MINS,
      KC_LBRC, KC_LT,   KC_GT,   KC_RBRC, KC_HASH,          KC_ASTR, KC_1,    KC_2,    KC_3,    KC_SLSH,
                        _______, _______, _______,          KC_UNDS, KC_0,    DOTCOMM  //trackball: snipe
  ),
  [_NAV] = LAYOUT_Wimads( //navigation and misc layer
      KC_PSCR, KC_BRK,  KC_INS,  XXXXXXX, KC_BTN5,          KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_VOLU,
      XXXXXXX, KC_SCRL, XXXXXXX, XXXXXXX, KC_F5,            KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_VOLD,
      XXXXXXX, XXXXXXX, KC_CAPS, XXXXXXX, KC_BTN4,          KC_NUM,  KC_MENU, KC_BTN4, KC_BTN5, KC_MUTE,
                        _______, _______, _______,          _______, KC_F5,   _______  //trackball: dragscroll
  ),
  [_RST] = LAYOUT_Wimads( //reset layer
      QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      XXXXXXX, XXXXXXX, CLEARKB, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                        XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX  //trackball: default
  ),
};

/*********CUSTOM KEY BEHAVIOURS********/
//customshift keycodes:
typedef struct _customshift_keycode_t { //define customshift functions
    uint16_t keycode_record;  //unmodified keycode
    uint16_t keycode_shifted; //alternate keycode to output on shift
} customshift_keycode_t;

#define KEY_MAP_SIZE 20 //amount of instances in customshift map

customshift_keycode_t keymap[KEY_MAP_SIZE] = { // customshift mapping, format: {keycode_record, keycode_shifted}
    //Numbers and F-keys
    {KC_CIRC, KC_F12},   {KC_7,    KC_F7},    {KC_8,    KC_F8},    {KC_9,    KC_F9}, //F12  F7  F8  F9
    {KC_PLUS, KC_F11},   {KC_4,    KC_F4},    {KC_5,    KC_F5},    {KC_6,    KC_F6}, //F11  F4  F5  F6
    {KC_ASTR, KC_F10},   {KC_1,    KC_F1},    {KC_2,    KC_F2},    {KC_3,    KC_F3}, //F10  F1  F2  F3
    //punctuation
    {KC_EXLM, KC_QUES},  {KC_COMM, KC_SCLN},  {KC_DOT,  S(KC_SCLN)}, // !?  ,;  .:
    //symbols
    {KC_SLSH, KC_BSLS},  {KC_PIPE, KC_BSLS},  {KC_DLR,  RALT(KC_5)}, // /\  |\  $€
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

