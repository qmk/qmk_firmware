#include QMK_KEYBOARD_H
#include "features/casemodes.h"

enum layers_enum {
  _COLEMAKDH,
  _SYMBOL,
  _NAVIGATION,
  _NUMBER,
  _FUNCTION,
  _NUMPAD,
};

// left
#define U_LCTL      LCTL_T(KC_A)
#define U_LSHIFT    LSFT_T(KC_R)
#define U_LALT      LALT_T(KC_S)
#define U_LGUI      LGUI_T(KC_T)

// right
#define U_RGUI    GUI_T(KC_N)
#define U_RALT    RALT_T(KC_E)
#define U_RSHIFT  RSFT_T(KC_I)
#define U_RCTL    RCTL_T(KC_O)

// Used in Number Pad layer.
#define U_GUI_NPAD   GUI_T(KC_KP_4)
#define U_RALT_NPAD  RALT_T(KC_KP_5)
#define U_RSFT_NPAD  RSFT_T(KC_KP_6)
#define U_RCTL_NPAD  RCTL_T(KC_KP_PLUS)


// UL means User Layer Toggle.
#define UL_TO_NUMPAD   TO(_NUMPAD)
#define UL_LT_NUM   LT(_NUMBER, KC_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

     /*
      * ┌──────┬───┬───┬───┬───┬───┐       ┌───┬───┬────┬────┬────┬─────┐
      * | Exit │ Q │ W │ F │ P │ B │       │ Y │ U │ I  │ O  │ ;: │ Bsp │
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
    [_COLEMAKDH] = LAYOUT_split_3x6_3(
        KC_ESC,   KC_Q,    KC_W,      KC_F,    KC_P,    KC_B,          KC_J,  KC_L,    KC_U,     KC_Y,      KC_SCLN,  KC_BSPC,
        KC_TAB,   U_LCTL,  U_LSHIFT,  U_LALT,  U_LGUI,  KC_G,          KC_M,  U_RGUI,  U_RALT,   U_RSHIFT,  U_RCTL,   KC_QUOT, 
        KC_LSFT,  KC_Z,    KC_X,      KC_C,    KC_D,    KC_V,          KC_K,  KC_H,    KC_COMM,  KC_DOT,    KC_SLSH,  KC_RSFT, 
        TO(_NAVIGATION), LT(_SYMBOL,KC_INSERT), UL_LT_NUM,             LT(_NAVIGATION, KC_ENT), LT(_FUNCTION, KC_DEL), UL_TO_NUMPAD
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
        _______,  KC_END,   KC_PGDN,  KC_PGUP,  KC_HOME,  XXXXXXX,       XXXXXXX,  QK_MOUSE_CURSOR_LEFT,  QK_MOUSE_CURSOR_UP,  QK_MOUSE_CURSOR_DOWN,  QK_MOUSE_CURSOR_RIGHT,  _______,
        _______,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  XXXXXXX,       XXXXXXX,  KC_RALT,  KC_RGUI,  KC_RSFT,  KC_RCTL,  XXXXXXX, 
        _______,  MS_WHLL,  MS_WHLD,  MS_WHLU,  MS_WHLR,  XXXXXXX,       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, 
        TO(_COLEMAKDH),  _______,  _______,                              XXXXXXX,  XXXXXXX,  _______
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
        _______,  KC_LCTL,  KC_LSFT,  KC_LALT,  KC_LGUI,  XXXXXXX,         KC_MINUS,  KC_4,     KC_5,  KC_6,    KC_PLUS,  XXXXXXX,
        _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,         KC_DOT,    KC_1,     KC_2,  KC_3,    KC_0,     KC_RSFT,
        XXXXXXX,  XXXXXXX,  _______,                                       _______,   XXXXXXX,  TO(_COLEMAKDH)
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
        KC_F14,  KC_F5,    KC_F6,    KC_F7,   KC_F8,   KC_F17,              XXXXXXX,  KC_RALT,  KC_RGUI,  KC_RSFT,  KC_RCTL,  XXXXXXX, 
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
        XXXXXXX,  KC_LCTL,  KC_LSFT,  KC_LALT,      KC_LGUI,  XXXXXXX,         KC_KP_MINUS,  U_GUI_NPAD,  U_RALT_NPAD,  U_RSFT_NPAD,  U_RCTL_NPAD,     XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,      XXXXXXX,  XXXXXXX,         KC_PDOT,      KC_KP_1,     KC_KP_2,      KC_KP_3,      KC_KP_0,         KC_RSFT,
        XXXXXXX,  XXXXXXX,  _______,                                             _______,    XXXXXXX,     TO(_COLEMAKDH)
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
    UC_LPRN_WFT,
    UC_LCBR_AWT,
    UC_LBRC_AWFT,
    UC_RPRN_NUY,
    UC_RCBR_UYO,
    UC_RBRC_NUYO,
    UC_LBOOT,
    UC_RBOOT
};


const uint16_t PROGMEM l_nav[] = {U_LCTL, U_LSHIFT, U_LALT, U_LGUI, COMBO_END};
const uint16_t PROGMEM l_nav_exit[] = {U_RGUI, U_RSHIFT, U_RCTL, COMBO_END};
// sanke case
const uint16_t PROGMEM l_xcase[] = {KC_W, KC_F, COMBO_END};
const uint16_t PROGMEM l_xcasecap[] = {KC_U, KC_Y, COMBO_END};
const uint16_t PROGMEM l_xcasewith[] = {KC_W, KC_F, KC_U, KC_Y, COMBO_END};
const uint16_t PROGMEM l_capword[] = {KC_F, KC_U, COMBO_END};
// for ":= "
const uint16_t PROGMEM l_colneql[] = {KC_W, KC_Y, COMBO_END};
// Parenthesis
const uint16_t PROGMEM l_lprn[] = {KC_W, KC_F, U_LGUI, COMBO_END};
const uint16_t PROGMEM l_rprn[] = {U_RGUI, KC_U, KC_Y, COMBO_END};
// Curly Bracker
const uint16_t PROGMEM l_lcbr[] = {U_LCTL, KC_W, KC_F, COMBO_END};
const uint16_t PROGMEM l_rcbr[] = {KC_U, KC_Y, U_RCTL, COMBO_END};
// Square Bracker
const uint16_t PROGMEM l_lbrc[] = {U_LCTL, KC_W, KC_F, U_LGUI, COMBO_END};
const uint16_t PROGMEM l_rbrc[] = {U_RGUI, KC_U, KC_Y, U_RCTL, COMBO_END};
// for boot mode
const uint16_t PROGMEM l_lboot[] = {KC_ESC, KC_B, UL_LT_NUM, COMBO_END};
const uint16_t PROGMEM l_rboot[] = {KC_J, KC_BSPC, UL_TO_NUMPAD, COMBO_END};


combo_t key_combos[] = {
    [UC_NAV] = COMBO(l_nav, TO(_NAVIGATION)),
    [UC_NAV_EXIT] = COMBO(l_nav_exit, TO(_NAVIGATION)),
    [UC_XCASE] = COMBO_ACTION(l_xcase),
    [UC_XCASECAP] = COMBO_ACTION(l_xcasecap),
    [UC_XCASEWITH] = COMBO_ACTION(l_xcasewith),
    [UC_CAPWORD] = COMBO_ACTION(l_capword),
    [UC_COLNEQL] = COMBO_ACTION(l_colneql),
    [UC_LPRN_WFT] = COMBO(l_lprn, KC_LPRN),
    [UC_RPRN_NUY] =  COMBO(l_rprn, KC_RPRN),
    [UC_LCBR_AWT] = COMBO(l_lcbr, KC_LCBR),
    [UC_RCBR_UYO] =  COMBO(l_rcbr, KC_RCBR),
    [UC_LBRC_AWFT] = COMBO(l_lbrc, KC_LBRC),
    [UC_RBRC_NUYO] = COMBO(l_rbrc, KC_RBRC),
    [UC_LBOOT] = COMBO(l_lboot, QK_BOOT),
    [UC_RBOOT] = COMBO(l_rboot, QK_BOOT)    
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Process case modes
    if (!process_case_modes(keycode, record)) {
        return false;
    }
    return true;
};

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
    }
}

