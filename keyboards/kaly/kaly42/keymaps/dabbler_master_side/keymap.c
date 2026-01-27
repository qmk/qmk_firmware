#include QMK_KEYBOARD_H
#include "features/casemodes.h"
#include "send_string.h"


enum custom_keycodes {
    UK_COLEDH_MOS = SAFE_RANGE,
    UK_COLEDH_WOS,
    UK_QWERTY_MOS,
    UK_QWERTY_WOS
};



enum layers_enum {
  COLEDH_MOS,
  COLEDH_WOS,
  QWERTY_MOS,
  QWERTY_WOS,
  _SYMBOL,
  _NAVIGATION,
  _NUMBER,
  _FUNCTION,
  _NUMPAD,
  _ADMIN
};

// enum custom_keycodes {
//     UK_COLEDH_MOS = SAFE_RANGE,
//     UK_COLEDH_WOS,
//     UK_QWERTY_MOS,
//     UK_QWERTY_WOS
// };



// left Mac
#define U_LCTL      LCTL_T(KC_A)
#define U_LALT      LALT_T(KC_R)
#define U_LGUI      LGUI_T(KC_S)
#define U_LSFT    LSFT_T(KC_T)
// right Mac
#define U_RSFT  RSFT_T(KC_N)
#define U_RGUI    GUI_T(KC_E)
#define U_RALT    RALT_T(KC_I)
#define U_RCTL    RCTL_T(KC_O)
// Num Pad for MacOS
#define U_RSFT_NPAD  RSFT_T(KC_KP_4)
#define U_GUI_NPAD   GUI_T(KC_KP_5)
#define U_RALT_NPAD  RALT_T(KC_KP_6)
#define U_RCTL_NPAD  RCTL_T(KC_KP_PLUS)


// UL means User Layer Toggle.
#define UL_TG_NUMPAD   TG(_NUMPAD)
#define UL_LT_NUM   LT(_NUMBER, KC_SPC)

// #define DF(layer) default_layer_set(layer)
// #define TO(layer) layer_move(layer)


/*
    
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

     /*
      * ┌──────┬───┬───┬───┬───┬───┐       ┌───┬───┬────┬────┬────┬─────┐
      * | Exit │ Q │ W │ F │ P │ B │       │ J │ L │ U  │ Y  │ ;: │ Bsp │
      * ├──────┼───┼───┼───┼───┼───┤       ├───┼───┼────┼────┼────┼─────┤
      * │ Tab  │ A │ R │ S │ T │ G │       │ M │ N │ E  │ I  │  O │ ' " │
      * ├──────┼───┼───┼───┼───┼───┤       ├───┼───┼────┼────┼────┼─────┤
      * │ Sft  │ Z │ X │ C │ D │ V │       │ K │ H │ ,< │ .> │ /? │ Sft │
      * └──────┴───┴───┴───┴───┴───┘       └───┴───┴────┴────┴────┴─────┘
      *               ┌───┐                   ┌────┐
      *               │NAV├───┐           ┌───┤NPAD│
      *               └───┤Ins├───┐   ┌───┤Del├────┘
      *                   └───┤Spc│   │Ent├───┘
      *                       └───┘   └───┘
      *               ┌───┐                   ┌────┐
      *               │   ├───┐           ┌───┤    │
      *               └───┤Sym├───┐   ┌───┤Fun├────┘
      *                   └───┤Num│   │Nav├───┘
      *                       └───┘   └───┘
      */
    [COLEDH_MOS] = LAYOUT_split_3x6_3(
        KC_ESC,   KC_Q,    KC_W,      KC_F,    KC_P,    KC_B,          KC_J,  KC_L,    KC_U,     KC_Y,      KC_SCLN,  KC_BSPC,
        KC_TAB,   U_LCTL,  U_LALT,    U_LGUI,  U_LSFT,  KC_G,          KC_M,  U_RSFT,  U_RGUI,   U_RALT,    U_RCTL,   KC_QUOT, 
        KC_LSFT,  KC_Z,    KC_X,      KC_C,    KC_D,    KC_V,          KC_K,  KC_H,    KC_COMM,  KC_DOT,    KC_SLSH,  KC_RSFT, 
        TG(_NAVIGATION),  LT(_SYMBOL,KC_INSERT),  UL_LT_NUM,                   LT(_NAVIGATION, KC_ENT),  LT(_FUNCTION, KC_DELETE),  UL_TG_NUMPAD
    ),

    [COLEDH_WOS] = LAYOUT_split_3x6_3(
        KC_ESC,   KC_Q,          KC_W,          KC_F,           KC_P,          KC_B,                KC_J,  KC_L,          KC_U,          KC_Y,           KC_SCLN,        KC_BSPC,
        KC_TAB,   LGUI_T(KC_A),  LALT_T(KC_R),  LCTL_T(KC_S),   LSFT_T(KC_T),  KC_G,                KC_M,  RSFT_T(KC_N),  RCTL_T(KC_E),  RALT_T(KC_I),   RGUI_T(KC_O),   KC_QUOT, 
        KC_LSFT,  KC_Z,          KC_X,          KC_C,           KC_D,          KC_V,                KC_K,  KC_H,          KC_COMM,       KC_DOT,         KC_SLSH,        KC_RSFT, 
        TG(_NAVIGATION),  LT(_SYMBOL,KC_INSERT),  UL_LT_NUM,                                                LT(_NAVIGATION, KC_ENT),  LT(_FUNCTION, KC_DELETE),  UL_TG_NUMPAD
    ),

    [QWERTY_MOS] = LAYOUT_split_3x6_3(
        KC_ESC,   KC_Q,          KC_W,          KC_E,          KC_R,          KC_T,                 KC_Y,  KC_U,          KC_I,           KC_O,          KC_P,             KC_BSPC,
        KC_TAB,   LCTL_T(KC_A),  LALT_T(KC_S),  LGUI_T(KC_D),  LSFT_T(KC_F),  KC_G,                 KC_H,  RSFT_T(KC_J),  RGUI_T(KC_K),   RALT_T(KC_L),  RCTL_T(KC_SCLN),  KC_QUOT, 
        KC_LSFT,  KC_Z,          KC_X,          KC_C,          KC_V,          KC_B,                 KC_N,  KC_M,          KC_COMM,        KC_DOT,        KC_SLSH,          KC_RSFT, 
        TG(_NAVIGATION),  LT(_SYMBOL,KC_INSERT),  UL_LT_NUM,                                                LT(_NAVIGATION, KC_ENT),  LT(_FUNCTION, KC_DELETE),  UL_TG_NUMPAD
    ),

    [QWERTY_WOS] = LAYOUT_split_3x6_3(
        KC_ESC,   KC_Q,          KC_W,           KC_E,          KC_R,          KC_T,                KC_Y,  KC_U,          KC_I,          KC_O,          KC_P,             KC_BSPC,
        KC_TAB,   LGUI_T(KC_A),  LALT_T(KC_S),   LCTL_T(KC_D),  RSFT_T(KC_F),  KC_G,                KC_H,  RSFT_T(KC_J),  RCTL_T(KC_K),  RALT_T(KC_L),  RGUI_T(KC_SCLN),  KC_QUOT, 
        KC_LSFT,  KC_Z,          KC_X,           KC_C,          KC_V,          KC_B,                KC_N,  KC_M,          KC_COMM,       KC_DOT,        KC_SLSH,          KC_RSFT, 
        TG(_NAVIGATION),  LT(_SYMBOL,KC_INSERT),  UL_LT_NUM,                                                LT(_NAVIGATION, KC_ENT),  LT(_FUNCTION, KC_DELETE),  UL_TG_NUMPAD
    ),

     /*
      * ┌──────┬───┬───┬───┬───┬───┐       ┌───┬───┬────┬────┬────┬─────┐
      * | Exit │   │   │   │   │   │       │   │   │    │    │    │ Bsp │
      * ├──────┼───┼───┼───┼───┼───┤       ├───┼───┼────┼────┼────┼─────┤
      * │ Tab  │   │   │   │   │   │       │   │   │    │    │    │     │
      * ├──────┼───┼───┼───┼───┼───┤       ├───┼───┼────┼────┼────┼─────┤
      * │ Sft  │   │   │   │   │   │       │   │   │    │    │    │ Sft │
      * └──────┴───┴───┴───┴───┴───┘       └───┴───┴────┴────┴────┴─────┘
      *               ┌───┐                   ┌───┐
      *               │   ├───┐           ┌───┤   │
      *               └───┤   ├───┐   ┌───┤   ├───┘
      *                   └───┤   │   │   ├───┘
      *                       └───┘   └───┘
      */
    [_NAVIGATION] = LAYOUT_split_3x6_3(
        _______,  KC_HOME,   KC_PGDN,  KC_PGUP,  KC_END,  XXXXXXX,       XXXXXXX,  QK_MOUSE_CURSOR_LEFT,  QK_MOUSE_CURSOR_UP,  QK_MOUSE_CURSOR_DOWN,  QK_MOUSE_CURSOR_RIGHT,  _______,
        _______,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  XXXXXXX,       XXXXXXX,  _______,  _______,  _______,  _______,  XXXXXXX,
        _______,  MS_WHLL,  MS_WHLD,  MS_WHLU,  MS_WHLR,  XXXXXXX,       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, 
        _______,  XXXXXXX,  XXXXXXX,                              XXXXXXX,  XXXXXXX,  XXXXXXX
    ),
     /*
      * ┌──────┬─────┬─────────────┬─────┬─────┬───┐       ┌─────┬───┬───┬───┬───┬─────┐
      * | Exit │     │ KC_NUM_LOCK │ Ent │     │   │       │  /  │ 7 │ 8 │ 9 │ * │ Bsp │
      * ├──────┼─────┼─────────────┼─────┼─────┼───┤       ├─────┼───┼───┼───┼───┼─────────────┤
      * │ Tab  │ Ctl |    Sft      │ Alt │ GUI │   │       │  -  │ 4 │ 5 │ 6 | + │ KC_KP_EQUAL │
      * ├──────┼─────┼─────────────┼─────┼─────┼───┤       ├─────┼───┼───┼───┼───┼─────────────┤
      * │ Sft  │     │             │     │     │   │       │  .  │ 1 │ 2 │ 3 │ 0 │ Sft │
      * └──────┴─────┴─────────────┴─────┴─────┴───┘       └─────┴───┴───┴───┴───┴─────┘
      *                         ┌───┐                       ┌───┐
      *                         │   ├───┐               ┌───┤   │
      *                         └───┤   ├───┐       ┌───┤   ├───┘
      *                             └───┤   │       │Ent├───┘
      *                                 └───┘       └───┘
      */
    [_NUMBER] = LAYOUT_split_3x6_3(
        _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,         XXXXXXX,   KC_7,     KC_8,  KC_9,    XXXXXXX,  KC_BSPC,
        _______,  _______,  _______,  _______,  _______,  XXXXXXX,         KC_MINUS,  KC_4,     KC_5,  KC_6,    KC_PLUS,  XXXXXXX,
        _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,         KC_DOT,    KC_1,     KC_2,  KC_3,    KC_0,     KC_RSFT,
        XXXXXXX,  XXXXXXX,  _______,                                       _______,   XXXXXXX,  XXXXXXX
    ),

     /*
      * ┌──────┬───┬───┬───┬───┬───┐       ┌───┬───┬────┬────┬────┬─────┐
      * |      │   │   │   │   │   │       │   │   │    │    │    │ Bsp │
      * ├──────┼───┼───┼───┼───┼───┤       ├───┼───┼────┼────┼────┼─────┤
      * │      │   │   │   │   │   │       │   │   │    │    │    │     │
      * ├──────┼───┼───┼───┼───┼───┤       ├───┼───┼────┼────┼────┼─────┤
      * │      │   │   │   │   │   │       │   │   │    │    │    │ Sft │
      * └──────┴───┴───┴───┴───┴───┘       └───┴───┴────┴────┴────┴─────┘
      *               ┌───┐                   ┌───┐
      *               │   ├───┐           ┌───┤   │
      *               └───┤   ├───┐   ┌───┤   ├───┘
      *                   └───┤   │   │   ├───┘
      *                       └───┘   └───┘
      */
    [_FUNCTION] = LAYOUT_split_3x6_3(
        KC_F15,  KC_F9,    KC_F10,   KC_F11,  KC_F12,  KC_F18,              XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
        KC_F14,  KC_F5,    KC_F6,    KC_F7,   KC_F8,   KC_F17,              XXXXXXX,  _______,  _______,  _______,  _______,  XXXXXXX, 
        KC_F13,  KC_F1,    KC_F2,    KC_F3,   KC_F4,   KC_F16,              XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, 
        XXXXXXX,  XXXXXXX,  XXXXXXX,                                        XXXXXXX,  XXXXXXX,  XXXXXXX
    ),

     /*
      * ┌──────┬───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┬─────┐
      * | Exit │ ~ │ ` │ _ │   │   │       │   │   │ ( │ ) │   │ Bsp │
      * ├──────┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼─────┤
      * │ Tab  │ ! │ # │ : │ & │ % │       │ ^ │ $ │ * │ = │ ; │     │
      * ├──────┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼─────┤
      * │ Sft  │ [ │ @ │ - │ ] │   │       │   │ { │ | │ \ │ } │ Sft |
      * └──────┴───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┴─────┘
      *               ┌───┐                   ┌───┐
      *               │   ├───┐           ┌───┤   │
      *               └───┤   ├───┐   ┌───┤   ├───┘
      *                   └───┤   │   │   ├───┘
      *                       └───┘   └───┘
      */
    [_SYMBOL] = LAYOUT_split_3x6_3(
        _______,    KC_TILD,  KC_GRV,   KC_UNDS,  XXXXXXX,  XXXXXXX,        XXXXXXX,    XXXXXXX,  KC_LPRN,  KC_RPRN,  XXXXXXX,  _______,
        _______,    KC_EXLM,  KC_HASH,  KC_COLN,  KC_AMPR,  KC_PERC,        KC_CIRC,    KC_DLR,   KC_ASTR,  KC_EQL,   KC_SCLN,  XXXXXXX, 
        _______,    KC_LBRC,  KC_AT,    KC_MINS,  KC_RBRC,  XXXXXXX,        XXXXXXX,    KC_LCBR,  KC_PIPE,  KC_BSLS,  KC_RCBR,  _______, 
        XXXXXXX,    XXXXXXX,  XXXXXXX,                                      XXXXXXX,    XXXXXXX,  XXXXXXX
    ),
     /*
      * ┌──────┬─────┬─────┬─────┬─────┬───┐       ┌─────┬───┬───┬───┬───┬─────┐
      * | Exit │     │     │ Ent │     │   │       │  /  │ 7 │ 8 │ 9 │ * │ Bsp │
      * ├──────┼─────┼─────┼─────┼─────┼───┤       ├─────┼───┼───┼───┼───┼─────┤
      * │ Tab  │ Ctl | Sft │ Alt │ GUI │   │       │  -  │ 4 │ 5 │ 6 | + │     │
      * ├──────┼─────┼─────┼─────┼─────┼───┤       ├─────┼───┼───┼───┼───┼─────┤
      * │ Sft  │     │     │     │     │   │       │  .  │ 1 │ 2 │ 3 │ 0 │ Sft │
      * └──────┴─────┴─────┴─── ─┴─────┴───┘       └─────┴───┴───┴───┴───┴─────┘
      *               ┌───┐                   ┌───┐
      *               │   ├───┐           ┌───┤   │
      *               └───┤   ├───┐   ┌───┤   ├───┘
      *                   └───┤   │   │Ent├───┘
      *                       └───┘   └───┘
      */
    [_NUMPAD] = LAYOUT_split_3x6_3(
        XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_KP_ENTER,  XXXXXXX,  XXXXXXX,         KC_KP_SLASH,  KC_KP_7,     KC_KP_8,      KC_KP_9,      KC_KP_ASTERISK,  KC_BSPC,
        XXXXXXX,  _______,  _______,  _______,      _______,  XXXXXXX,         KC_KP_MINUS,  KC_KP_4,     KC_KP_5,      KC_KP_6,      KC_KP_PLUS,      XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,      XXXXXXX,  XXXXXXX,         KC_PDOT,      KC_KP_1,     KC_KP_2,      KC_KP_3,      KC_KP_0,         KC_RSFT,
        XXXXXXX,  XXXXXXX,  _______,                                           _______,    XXXXXXX,     _______
    ),

    [_ADMIN] = LAYOUT_split_3x6_3(
        XXXXXXX,  UK_COLEDH_MOS,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,         XXXXXXX,  XXXXXXX,     XXXXXXX,      XXXXXXX,      UK_QWERTY_MOS,  XXXXXXX,
        XXXXXXX,  UK_COLEDH_WOS,  XXXXXXX,  XXXXXXX,      XXXXXXX,  XXXXXXX,      XXXXXXX,  XXXXXXX,     XXXXXXX,      XXXXXXX,     UK_QWERTY_WOS,      XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,      XXXXXXX,  XXXXXXX,         XXXXXXX,      XXXXXXX,     XXXXXXX,      XXXXXXX,      XXXXXXX,         XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,                                             XXXXXXX,    XXXXXXX,     XXXXXXX
    )

  /*
      * ┌──────┬───┬───┬───┬───┬───┐       ┌───┬───┬────┬────┬────┬─────┐
      * | Exit │   │   │   │   │   │       │   │   │    │    │    │ Bsp │
      * ├──────┼───┼───┼───┼───┼───┤       ├───┼───┼────┼────┼────┼─────┤
      * │ Tab  │   │   │   │   │   │       │   │   │    │    │    │     │
      * ├──────┼───┼───┼───┼───┼───┤       ├───┼───┼────┼────┼────┼─────┤
      * │ Sft  │   │   │   │   │   │       │   │   │    │    │    │ Sft │
      * └──────┴───┴───┴───┴───┴───┘       └───┴───┴────┴────┴────┴─────┘
      *               ┌───┐                   ┌───┐
      *               │   ├───┐           ┌───┤   │
      *               └───┤   ├───┐   ┌───┤   ├───┘
      *                   └───┤   │   │   ├───┘
      *                       └───┘   └───┘
      */
};



void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  debug_keyboard=true;
  //debug_mouse=true;
}

//  using safe renge raise an error. Why?
// process will compile w/wo last comma.
enum ComboActions{
    UC_NAV,
    UC_NAV_EXIT,
    UC_XCASE,
    UC_XCASECAP,
    UC_XCASEWITH,
    UC_CAPWORD,
    UC_COLNEQL,
    UC_COPY_XSD, 
    UC_PASTE_HEDOT,   
    UC_LBRC_AWFT,
    UC_RBRC_NUYO,
    UC_LPRN_WFT,
    UC_LCBR_AWT,
    UC_RPRN_NUY,
    UC_RCBR_UYO,
    UC_ADMIN_LAYER,
    UC_LBOOT,
    UC_RBOOT,
    UC_CAP_LOCK,
    UC_ENTER
};
 

const uint16_t PROGMEM l_nav[] = {U_LCTL, U_LSFT, U_LALT, U_LGUI, COMBO_END};
const uint16_t PROGMEM l_nav_exit[] = {U_RGUI, U_RSFT, U_RCTL, COMBO_END};
// sanke case
const uint16_t PROGMEM l_xcase[] = {KC_W, KC_F, COMBO_END};   
const uint16_t PROGMEM l_xcasecap[] = {KC_U, KC_Y, COMBO_END};
const uint16_t PROGMEM l_xcasewith[] = {KC_W, KC_F, KC_U, KC_Y, COMBO_END};
const uint16_t PROGMEM l_capword[] = {KC_F, KC_U, COMBO_END};
// for ":= "
const uint16_t PROGMEM l_colneql[] = {KC_W, KC_Y, COMBO_END};
//Copy and Paste
const uint16_t PROGMEM l_copy[] = {KC_X, KC_D, COMBO_END};
const uint16_t PROGMEM l_paste[] = {KC_H, KC_DOT, COMBO_END};
// const uint16_t PROGMEM l_copy[] = {KC_X, U_LGUI, KC_D, COMBO_END};
// const uint16_t PROGMEM l_paste[] = {KC_H, U_RGUI, KC_DOT, COMBO_END};
// Parenthesis
const uint16_t PROGMEM l_lprn[] = {KC_W, KC_F, U_LSFT, COMBO_END};
const uint16_t PROGMEM l_rprn[] = {U_RSFT, KC_U, KC_Y, COMBO_END};
// Curly Bracker
const uint16_t PROGMEM l_lcbr[] = {KC_Q, KC_W, KC_F, U_LSFT, COMBO_END};
const uint16_t PROGMEM l_rcbr[] = {U_RSFT, KC_U, KC_Y, KC_SCLN, COMBO_END};
// Square Bracker
const uint16_t PROGMEM l_lbrc[] = {KC_Q, KC_W, KC_F, COMBO_END};
const uint16_t PROGMEM l_rbrc[] = {KC_U, KC_Y, KC_SCLN, COMBO_END};
// Admin layer e.g. change default layer.
// const uint16_t PROGMEM l_admin_layer[] = {KC_ESC, TG(_NAVIGATION), KC_BSPC, UL_TG_NUMPAD, COMBO_END};
const uint16_t PROGMEM l_admin_layer[] = {KC_ESC, TG(_NAVIGATION), UL_TG_NUMPAD, COMBO_END};
// for boot mode
const uint16_t PROGMEM l_lboot[] = {KC_ESC, KC_B, UL_LT_NUM, COMBO_END};
const uint16_t PROGMEM l_rboot[] = {KC_J, KC_BSPC, LT(_NAVIGATION, KC_ENT), COMBO_END};

// others usefull
const uint16_t PROGMEM l_cap_lock[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM l_enter[] = {KC_COMM, KC_DOT, COMBO_END};


combo_t key_combos[] = {
    [UC_NAV] = COMBO(l_nav, TG(_NAVIGATION)),
    [UC_NAV_EXIT] = COMBO(l_nav_exit, TG(_NAVIGATION)),
    [UC_XCASE] = COMBO_ACTION(l_xcase),
    [UC_XCASECAP] = COMBO_ACTION(l_xcasecap),
    [UC_XCASEWITH] = COMBO_ACTION(l_xcasewith),
    [UC_CAPWORD] = COMBO_ACTION(l_capword),
    [UC_COLNEQL] = COMBO_ACTION(l_colneql),
    [UC_COPY_XSD] = COMBO_ACTION(l_copy), 
    [UC_PASTE_HEDOT] = COMBO_ACTION(l_paste), 
    [UC_LPRN_WFT] = COMBO(l_lprn, KC_LPRN),
    [UC_RPRN_NUY] =  COMBO(l_rprn, KC_RPRN),
    [UC_LCBR_AWT] = COMBO(l_lcbr, KC_LCBR),
    [UC_RCBR_UYO] =  COMBO(l_rcbr, KC_RCBR),
    [UC_LBRC_AWFT] = COMBO(l_lbrc, KC_LBRC),
    [UC_RBRC_NUYO] = COMBO(l_rbrc, KC_RBRC),
    [UC_ADMIN_LAYER] = COMBO(l_admin_layer, TO(_ADMIN)),
    [UC_LBOOT] = COMBO(l_lboot, QK_BOOT),
    [UC_RBOOT] = COMBO(l_rboot, QK_BOOT),  
    [UC_CAP_LOCK] = COMBO(l_cap_lock, KC_CAPS),  
    [UC_ENTER] = COMBO(l_enter, KC_ENT)
};



// Simplified helper function for the paste action
void handle_combo_paste(bool pressed) {
    if (pressed) {
        switch ((uint16_t)get_highest_layer(default_layer_state)) { 
            case COLEDH_MOS:
            case QWERTY_MOS:
                tap_code16(G(KC_V));
                break;
            
            case COLEDH_WOS:
            case QWERTY_WOS: 
                tap_code16(C(KC_V)); 
                break;
        }
    } 
}


// Simplified helper function for the copy action
void handle_combo_copy(bool pressed) {
    if (pressed) {
        // Determine the correct modifier only on press
        switch ((uint16_t)get_highest_layer(default_layer_state)) { 
            case COLEDH_MOS:
            case QWERTY_MOS:
                tap_code16(G(KC_C)); 
                break;
            case COLEDH_WOS:
            case QWERTY_WOS:
                tap_code16(C(KC_C)); 
                break;
        }
    }
}

// // Helper function for the paste action
// void handle_paste_action(bool pressed) {
//     if (pressed) {
//         switch ((uint16_t)get_highest_layer(default_layer_state)) { 
//             case UK_COLEDH_MOS: LGUID(KC_V); break;
//             case UK_QWERTY_MOS: LCTL(KC_V);  break;
//         }
//     }
//     // Note: Modifier release is automatically handled by QMK for these simple macros (LGUID/LCTL)
// }

// // Helper function for the copy action
// void handle_copy_action(bool pressed) {
//     if (pressed) {
//         switch ((uint16_t)get_highest_layer(default_layer_state)) { 
//             case UK_COLEDH_MOS: LGUID(KC_C); break;
//             case UK_QWERTY_MOS: LCTL(KC_C);  break;
//         }
//     }
// }


// static uint8_t paste_mod = 0;

// // Simplified helper function for the paste action
// void handle_combo_paste(bool pressed) {
//     if (pressed) {
//         switch ((uint16_t)get_highest_layer(default_layer_state)) { 
//             case COLEDH_MOS:
//             case QWERTY_MOS:
//                 paste_mod = MOD_BIT(KC_LGUI);
//                 break;
            
//             case COLEDH_WOS:
//             case QWERTY_WOS: 
//                 paste_mod = MOD_BIT(KC_LCTL);
//                 break;

//             default:
//                 paste_mod = 0; // No specific mod for other layers
//                 break;
//         }

//         if (paste_mod) {
//             register_mods(paste_mod);
//             tap_code(KC_V);
//             // register_code(KC_V);
//         }

//     } else {
//         // Unregister ONLY the modifier that was set during the press event
//         // unregister_code(KC_V);
//         if (paste_mod) {
//             unregister_mods(paste_mod);
//             paste_mod = 0; // Reset the tracker
//         }
//     }
// }


// static uint8_t copy_mod = 0;

// // Simplified helper function for the copy action
// void handle_combo_copy(bool pressed) {
//     if (pressed) {
//         // Determine the correct modifier only on press
//         switch ((uint16_t)get_highest_layer(default_layer_state)) { 
//             case COLEDH_MOS:
//             case QWERTY_MOS:
//                 copy_mod = MOD_BIT(KC_LGUI);
//                 break;
//             case COLEDH_WOS:
//             case QWERTY_WOS:
//                 copy_mod = MOD_BIT(KC_LCTL);
//                 break;
//             default:
//                 copy_mod = 0; // No specific mod for other layers
//                 break;
//         }
//         if (copy_mod) {
//             register_mods(copy_mod);
//             tap_code(KC_C);
//             // register_code(KC_C);
//         }
//     } else {
//         // Unregister ONLY the modifier that was set during the press event
//         // unregister_code(KC_C);
//         if (copy_mod) {
//             unregister_mods(copy_mod);
//             copy_mod = 0; // Reset the tracker
//         }
//     }
// }



bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) return true; // only act on key press
    // Process case modes
    if (!process_case_modes(keycode, record)) {
        return false;
    }

    switch (keycode) {
        case UK_COLEDH_MOS:

            default_layer_set(1U << COLEDH_MOS);
            layer_move(COLEDH_MOS);
            SEND_STRING("Layout: COLEDH_MOS");
            // DF(COLEDH_MOS);
            // TO(COLEDH_MOS);
            return false;

        case UK_COLEDH_WOS:
            // DF(_COLEDH_WOS);
            // TO(_COLEDH_WOS);
            default_layer_set(1U << COLEDH_WOS);
            layer_move(COLEDH_WOS);
            SEND_STRING("Layout: COLEDH_WOS");
            return false;

        case UK_QWERTY_MOS:
            // DF(_QWERTY_MOS);
            // TO(_QWERTY_MOS);
            default_layer_set(1U << QWERTY_MOS);
            layer_move(QWERTY_MOS);
            SEND_STRING("Layout: QWERTY_MOS");
            return false; 

        case UK_QWERTY_WOS:
            // DF(_QWERTY_WOS);
            // TO(_QWERTY_WOS);
            default_layer_set(1U << QWERTY_WOS);
            layer_move(QWERTY_WOS);
            SEND_STRING("Layout: QWERTY_WOS");
            return false;
    }
    return true;
}


void process_combo_event(uint16_t combo_index, bool pressed) {
    switch (combo_index) {
        case UC_XCASE:
            if (pressed) {
                enable_xcase_with(KC_UNDS);
            }
            break;
        case UC_XCASECAP:
            if (pressed) {
                toggle_caps_word();
                enable_xcase_with(KC_UNDS);
            }
            break;
        case UC_XCASEWITH:
            if (pressed) {
                enable_xcase();
            }
            break;
        case UC_CAPWORD:
            if (pressed) {
                toggle_caps_word();
            }
            break;
        case UC_COLNEQL:
            if (pressed) {
                tap_code16(KC_COLN);
                tap_code16(KC_EQL);
                tap_code(KC_SPC);
            }
            break; 
        case UC_COPY_XSD:
            handle_combo_copy(pressed);
            break;
        case UC_PASTE_HEDOT:
            // This is the call:
            handle_combo_paste(pressed); 
            break;
    }
}