#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _SYMB 1
#define _NAV 2
#define _ADJUST 3

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  SYMB,
  NAV,
  ADJUST,
};

// Shortcut to make keymap more readable
#define SYM_L   MO(_SYMB)

//CYE Custom macros
#define KC_LYR3 LT(_NAV, KC_SCLN)
#define KC_LYR4 MO(_ADJUST)

#define KC_UNDO LCTL(KC_Z) //undo
#define KC_LGOFF LGUI(KC_L) //log out of comp
#define KC_LGON LCTL(LALT(KC_DEL)) //log into work comp

// #define KC_ALAS LALT_T(KC_PAST)
// #define KC_CTPL LCTL_T(KC_BSLS)
// #define KC_NAGR LT(_NAV, KC_GRV)
// #define KC_NAMI LT(_NAV, KC_MINS)
// #define KC_ADEN LT(_ADJUST, KC_END)
// #define KC_ADPU LT(_ADJUST, KC_PGUP)

// Windows virtual desktop switching functions. Downloaded software called SylphyHornEx
#define KC_WS0 LCTL(LGUI(KC_0))
#define KC_WS1 LCTL(LGUI(KC_1))
#define KC_WS2 LCTL(LGUI(KC_2))
#define KC_WS3 LCTL(LGUI(KC_3))
#define KC_WS4 LCTL(LGUI(KC_4))
#define KC_WS5 LCTL(LGUI(KC_5))
#define KC_WS6 LCTL(LGUI(KC_6))
#define KC_WS7 LCTL(LGUI(KC_7))
#define KC_WS8 LCTL(LGUI(KC_8))
#define KC_WS9 LCTL(LGUI(KC_9))
#define KC_WSL LCTL(LGUI(KC_LEFT))
#define KC_WSR LCTL(LGUI(KC_RIGHT))
#define KC_WSWAPL LCTL(LGUI(LSFT(KC_LEFT))) // swap desktop with left one (move this desktop to the left)
#define KC_WSWAPR LCTL(LGUI(LSFT(KC_RIGHT))) // swap desktop with right one (move this desktop to the right)
#define KC_WSMAWL LGUI(LALT(KC_LEFT)) // move active window to desktop on the left
#define KC_WSMAWR LGUI(LALT(KC_RIGHT)) // move active window to desktop on the Right
#define KC_WSPIN LCTL(LGUI(LALT(KC_P))) // pin active window to all desktops
#define KC_WSNEW LCTL(LGUI(KC_D)) // move active window to created new desktop
#define KC_WSRNAME LCTL(LGUI(KC_R)) // rename current desktop

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_GRV  ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,                                            KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,KC_EQL  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB  ,KC_Q    ,KC_W    ,KC_E    ,KC_R    ,KC_T    ,SYM_L   ,                          SYM_L   ,KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,KC_BSLS ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_BSPC ,KC_A    ,KC_S    ,KC_D    ,KC_F    ,KC_G    ,KC_LBRC ,                          KC_RBRC ,KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_LYR3 ,KC_QUOT ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_ESC  ,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B    , KC_LYR4,KC_LALT ,        KC_HOME, KC_END  ,KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,KC_RSFT ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     KC_LCTRL,KC_UNDO ,KC_LALT ,KC_LGUI ,     SYM_L   ,    KC_LSFT ,KC_DEL  ,        KC_ENT  ,KC_SPC  ,    SYM_L   ,     KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RGHT
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_SYMB] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,                                            KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_F11  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_EXLM ,KC_AT   ,KC_LCBR ,KC_RCBR ,KC_PIPE ,_______ ,                          _______ ,KC_LT   ,KC_P7 	,KC_P8 	 ,KC_P9   ,KC_PAST ,KC_F12  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_UNDS ,KC_HASH ,KC_DLR  ,KC_LPRN ,KC_RPRN ,KC_GRV  ,_______ ,                          _______ ,KC_GT   ,KC_P4 	,KC_P5   ,KC_P6   ,KC_MINS ,KC_EQL  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_PERC ,KC_CIRC ,KC_LBRC ,KC_RBRC ,KC_TILD ,_______ ,_______ ,        _______ ,_______ ,KC_AMPR ,KC_P1 	,KC_P2   ,KC_P3   ,KC_PPLS ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,     _______ ,    _______ ,_______ ,        _______ ,_______ ,    _______ ,     KC_P0   ,KC_PDOT ,KC_PSLS ,KC_NLCK 
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_NAV] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,KC_MS_U ,XXXXXXX ,XXXXXXX ,_______ ,                          _______ ,XXXXXXX ,XXXXXXX ,KC_WH_U ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,KC_MS_L ,KC_MS_D ,KC_MS_R ,XXXXXXX ,_______ ,                          _______ ,XXXXXXX ,KC_WH_L ,KC_WH_D  ,KC_WH_R,XXXXXXX ,KC_MPLY ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,_______ ,        _______ ,XXXXXXX ,KC_MPRV ,KC_MNXT ,KC_VOLD ,KC_VOLU ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,     _______ ,    KC_BTN1 ,KC_BTN2 ,        _______ ,_______ ,    _______ ,     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_ADJUST] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     XXXXXXX ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,                                            KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_WSNEW ,KC_WSPIN   ,KC_WS7 ,KC_WS8 ,KC_WS9 ,KC_WSRNAME ,XXXXXXX ,                       XXXXXXX ,XXXXXXX ,KC_WS7  ,KC_WS8  ,KC_WS9  ,KC_WSPIN,KC_WSNEW,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_WSL ,KC_WSR ,KC_WS4 ,KC_WS5 ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                          XXXXXXX ,XXXXXXX ,KC_WS4  ,KC_WS5  ,KC_WS6  ,KC_WSL  ,KC_WSR  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_WSWAPL ,KC_WSWAPR ,KC_WS1 ,KC_WS2 ,KC_WS3 ,XXXXXXX ,_______ ,XXXXXXX ,        XXXXXXX ,_______ ,XXXXXXX ,KC_WS1  ,KC_WS2  ,KC_WS3  ,KC_WSWAPL,KC_WSWAPR,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     KC_WSMAWL ,KC_WSMAWR ,XXXXXXX ,KC_WS0 ,     _______ ,    XXXXXXX ,XXXXXXX ,        XXXXXXX ,XXXXXXX ,    _______ ,     KC_WS0  ,XXXXXXX ,KC_WSMAWL,KC_WSMAWR
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  )

};

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _QWERTY:
            set_led_off;
            break;
        case _SYMB:
            set_led_green;
            break;
        case _NAV:
            set_led_blue;
            break;
        case _ADJUST:
            set_led_red;
            break;
        default:
            break;
    }
  return state;
}


