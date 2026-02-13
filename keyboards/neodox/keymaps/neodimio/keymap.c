// Copyright 2022 MatteoDM <matteodalmo@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

/**
*  Each layer gets a name for readability, which is then used in the keymap matrix below.
*  The underscores don't mean anything - you can have a layer called STUFF or any other name.
*  Layer names don't all need to be of the same length, obviously, and you can also skip them
*  entirely and just use numbers.
*/

#ifdef QUANTUM_PAINTER_ENABLE
#  include <qp.h>
#  include "imgs/logo.qgf.h"
#  include "imgs/big_font.qff.h"
#endif

#include "quantum.h"
#include <string.h>
#include <ctype.h>
#include <printf.h>
#include "color.h"

#ifdef BACKLIGHT_ENABLE
  #include "backlight.h"
#endif


#define _QWERTY  0
#define _SYMB    1
#define _MOUSE   2
#define _NAV     3
#define _FUNC    4
#define _GAMING  5
#define _ADJUST  6

// custom keycodes
enum custom_keycodes {
    ASC_MAJOR = SAFE_RANGE,
    ASC_MINOR,
    FD_TIME,
    FD_HUE,
    FD_SAT,
    FD_VAL
};

// limit time to reach fade_rgb.end
#define FADE_TIME_OPTIONS_NUMBER 10
uint8_t fade_time_option_index = 2;
uint16_t fade_time_options[] = { 0, 50, 100, 175, 250, 500, 750, 1000, 1500, 2500};
uint16_t fade_time = 100;
uint16_t fade_timer = 0;

HSV fade_default_hsv = {0, 255, 255};

typedef struct {
    uint16_t cur;     // current RGB value
    uint16_t end;     // RGB value to reach
    uint16_t step;    // RGB value to add/subtract at every step
    // uint16_t speed;   // how often to step (fade_time / fade_rgb.step)
    // uint16_t timer;   // timers
    // uint16_t time;    // time to reach end
} fade_color_t;

typedef struct {
    fade_color_t r;
    fade_color_t g;
    fade_color_t b;
} fade_rgb_t;

fade_rgb_t fade_rgb; // fader: current RGB, end RGB, step RGB
HSV fade_hsv;        // current HSV

// #define SPLIT_USB_TIMEOUT 10000


#ifdef QUANTUM_PAINTER_ENABLE

static painter_font_handle_t my_font;
static painter_image_handle_t logo;
painter_device_t lcd;
#endif

const char *current_layer_name(void);
// tap dance buttons
enum {
    _BOOT_TAP, //
    _TD_L_LAYERS,
    _TD_R_LAYERS,
    _TD_R_ENTER,
    _TD_LBRS,
    _TD_RBRS,
};

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP,
    TD_TRIPLE_TAP,
    TD_TRIPLE_SINGLE_TAP,
    TD_TRIPLE_HOLD,
    TD_QUAD_TAP,
    TD_QUAD_HOLD,
    TD_QUAD_SINGLE_TAP
} td_state_t;

static td_state_t td_state_l_layers;
static td_state_t td_state_r_layers;
static td_state_t td_state_lbrs;
static td_state_t td_state_rbrs;

// Tap dance keycodes
// enum tap_dance{
//   _BOOT_TAP, //
//   _TD_LAYERS_1,
//   _TD_LAYERS_2

// };


// Tap dance keys:
#define KC_BOTAP  TD(_BOOT_TAP)     //6 tap get to bootloader

// #define LAYERS_R  TD(_TD_LAYERS_1)     //6 tap get to bootloader
// #define LAYERS_L  TD(_TD_LAYERS_2)     //6 tap get to bootloader

#define TD_L_LAY    TD(_TD_L_LAYERS)
#define TD_R_LAY    TD(_TD_R_LAYERS)
#define TD_LBRS     TD(_TD_LBRS)
#define TD_RBRS     TD(_TD_RBRS)
#define TD_ENT      TD(_TD_R_ENTER)


// Shortcut to make keymap more readable
#define QWERTY_L  DF(_QWERTY)
#define SYM_L     MO(_SYMB)
#define NAV_L     MO(_NAV)
#define GAM_L     DF(_GAMING)

#define KC_LAF4     LALT(KC_F4)
#define KC_LSGR     LSFT_T(KC_GRV)
#define KC_RSGQT    RSFT_T(KC_QUOT)
#define KC_RCC      RCTL(KC_C)
#define KC_RCV      RCTL(KC_V)
#define KC_RCX      RCTL(KC_X)

#define OSM_LCLS    OSM(MOD_LCTL|MOD_LSFT)
#define OSM_RCRS    OSM(MOD_RCTL|MOD_RSFT)

#define KC_ALAS     LALT_T(KC_PAST)
#define KC_CTPL     LCTL_T(KC_BSLS)
#define KC_LADEL    LALT_T(KC_DEL)
#define KC_LCAT     LCA(KC_TAB)

#define KC_LGTAB    LGUI(KC_TAB)
#define KC_LCLGL    LCTL(LGUI(KC_LEFT))
#define KC_LCLGR    LCTL(LGUI(KC_RIGHT))
#define KC_LGTAB    LGUI(KC_TAB)
#define KC_RSGS     RSG(KC_S)

#define KC_NAGR     LT(_NAV, KC_GRV)
#define KC_NAMI     LT(_NAV, KC_MINS)
#define KC_FUESC    LT(_FUNC,KC_ESC)
#define KC_MOUEN    LT(_MOUSE,KC_ENT)// non usato

#define KC_ADEN     LT(_ADJUST, KC_END)
#define KC_ADPU     LT(_ADJUST, KC_PGUP)



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_ESC  ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,                                            KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,KC_MINS ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼                                           ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB  ,KC_Q    ,KC_W    ,KC_E    ,KC_R    ,KC_T    ,                                            KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,KC_EQL  ,
  //├────────┼────────┼────────┼────────┼────────┼────────                                            ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSGR ,KC_A    ,KC_S    ,KC_D    ,KC_F    ,KC_G    ,                                            KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_SCLN ,KC_RSGQT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┬────────┐       ┌────────┬────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LCTL ,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B    ,KC_PGUP ,KC_PGDN ,        KC_HOME ,KC_ADEN ,KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,KC_RCTL ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     KC_BSLS ,KC_LGUI ,KC_BOTAP,KC_FUESC,     KC_BSPC ,    KC_LADEL,SYM_L   ,        NAV_L   ,KC_MOUEN,    KC_SPC  ,     TD_L_LAY,KC_BOTAP,KC_CAPS ,KC_RALT
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),


  [_SYMB] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_TRNS ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,                                            KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_NO   ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                                           ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TRNS ,KC_EXLM ,KC_EQL  ,KC_LCBR ,KC_RCBR ,KC_PIPE ,                                            KC_PAST ,KC_7    ,KC_8    ,KC_9    ,KC_PPLS ,KC_NO   ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                                           ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TRNS ,KC_HASH ,KC_DLR  ,KC_LBRC ,KC_RBRC ,KC_AMPR ,                                            KC_PSLS ,KC_4    ,KC_5    ,KC_6    ,KC_PMNS ,KC_NO   ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┬────────┐       ┌────────┬────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TRNS ,KC_PERC ,KC_CIRC ,KC_LPRN ,KC_RPRN ,KC_TILD ,KC_TRNS ,KC_TRNS ,        KC_TRNS ,KC_TRNS ,KC_NO   ,KC_1    ,KC_2    ,KC_3    ,KC_EQL  ,KC_NO   ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,     KC_TRNS ,    KC_TRNS ,KC_TRNS ,        KC_TRNS ,KC_TRNS ,    KC_TRNS ,     KC_0    ,KC_PDOT ,KC_PENT ,KC_NO
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),


  [_MOUSE] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,                                            KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                                           ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_NO   ,KC_RCX   ,KC_RCC  ,KC_MS_U ,KC_RCV  ,KC_NO  ,                                            KC_NO   ,KC_NO   ,KC_WH_U ,KC_NO   ,KC_NO   ,KC_NO   ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                                           ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_NO   ,KC_RSGS ,KC_MS_L ,KC_MS_D ,KC_MS_R ,KC_NO   ,                                            KC_ENT  ,KC_WH_L ,KC_WH_D ,KC_WH_R ,KC_NO   ,KC_NO   ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┬────────┐       ┌────────┬────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TRNS ,KC_NO   ,KC_BTN4 ,KC_BTN3 ,KC_BTN5 ,KC_NO   ,KC_TRNS ,KC_TRNS ,        KC_TRNS ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_TRNS ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     KC_LGTAB,KC_NO   ,KC_NO   ,KC_TRNS ,     KC_BTN1 ,    KC_BTN2 ,KC_TRNS,         KC_TRNS ,KC_TRNS ,    KC_TRNS ,     TD_L_LAY,KC_NO   ,KC_NO   ,KC_NO
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),


  [_NAV] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_TRNS ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,                                            KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_NO   ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                                           ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TRNS ,KC_RCX  ,KC_RCC  ,KC_UP   ,KC_RCV  ,KC_PGUP ,                                            KC_NO   ,KC_VOLD ,KC_VOLU ,KC_MUTE ,KC_NO   ,KC_NO   ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                                           ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TRNS ,KC_LCAT ,KC_LEFT ,KC_DOWN ,KC_RGHT ,KC_PGDN ,                                            KC_ENT  ,KC_LSFT ,KC_LCTL ,KC_LALT ,KC_LGUI ,KC_NO   ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┬────────┐       ┌────────┬────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TRNS ,KC_LCLGL,KC_HOME ,KC_END  ,KC_LCLGR,KC_NO   ,KC_NO   ,KC_NO   ,        KC_NO   ,KC_NO   ,KC_NO   ,KC_MPRV ,KC_MNXT ,KC_MSTP ,KC_MPLY ,KC_NO   ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     KC_LGTAB,KC_NO   ,KC_NO   ,KC_NO   ,     KC_TRNS ,    KC_TRNS ,KC_TRNS ,       KC_TRNS  ,KC_TRNS ,    KC_TRNS ,     TD_L_LAY,KC_NO   ,KC_NO   ,KC_NO
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_FUNC] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_TRNS ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,                                            BL_TOGG ,BL_INC  ,BL_DEC  ,KC_NO   ,KC_NO   ,KC_NO   ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                                           ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TRNS ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,                                            KC_NO   ,KC_F9   ,KC_F10  ,KC_F11  ,KC_F12  ,KC_NO   ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                                           ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TRNS ,KC_LGUI ,KC_LALT ,KC_LCTL ,KC_LSFT ,KC_NO   ,                                            KC_NO   ,KC_F5   ,KC_F6   ,KC_F7   ,KC_F8   ,KC_NO   ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┬────────┐       ┌────────┬────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TRNS ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO    ,KC_NO  ,KC_NO   ,KC_NO   ,        KC_NO   ,KC_NO   ,KC_NO   ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_NO   ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     KC_NO   ,KC_TRNS ,KC_TRNS ,KC_TRNS ,     KC_NO   ,    KC_NO   ,KC_TRNS ,        KC_TRNS ,KC_NO   ,    KC_NO   ,     TD_L_LAY,KC_NO   ,KC_NO   ,KC_NO
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_GAMING] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,                                            KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                                           ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,                                            KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                                           ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,                                            KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┬────────┐       ┌────────┬────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,        KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,     KC_SPC  ,    KC_TRNS ,KC_ENT  ,        KC_NO   ,KC_NO   ,    KC_BSPC ,     TD_L_LAY,KC_NO   ,KC_NO   ,KC_NO
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ) ,




  [_ADJUST] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,                                            KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                                           ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,                                            RGB_M_X ,RGB_M_SW,RGB_M_K ,RGB_M_G ,RGB_M_SN,RGB_M_B ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                                           ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TRNS ,FD_TIME ,FD_HUE  ,FD_SAT  ,FD_VAL  ,KC_NO   ,                                            RGB_TOG ,RGB_HUI ,RGB_SAI ,RGB_VAI ,RGB_MOD ,RGB_M_P ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┬────────┐       ┌────────┬────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,        KC_NO   ,KC_NO   ,RGB_M_T ,RGB_HUD ,RGB_SAD ,RGB_VAD ,RGB_RMOD,RGB_M_R ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,     KC_NO   ,    KC_NO   ,KC_NO   ,        KC_NO   ,KC_NO   ,    KC_NO   ,     TD_L_LAY,KC_NO   ,KC_NO   ,KC_NO
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  )
};
//----------------------------------------------------------

void keyboard_post_init_kb(void) {

#ifdef QUANTUM_PAINTER_ENABLE
    // Initialise the display
    logo = qp_load_image_mem(gfx_logo);
    my_font = qp_load_font_mem(big_font);
    lcd = qp_gc9a01_make_spi_device(240, 240, LCD_CS_PIN, LCD_DC_PIN, LCD_RST_PIN, 4, 0);         // Create the display
    qp_init(lcd, QP_ROTATION_0);


    if (is_keyboard_master()) {

        // Turn on the LCD and clear the display
        qp_power(lcd, true);
        qp_rect(lcd, 0, 0, 240, 240 ,HSV_WHITE, true);
        qp_drawimage(lcd, 5, 10, logo);

        // Turn on the LCD backlight
        rgblight_enable();
        rgblight_sethsv_noeeprom(128, 240, 240);
        backlight_level(5);
        backlight_enable();

    }else
    {
        qp_rect(lcd, 0, 0, 240, 240 ,HSV_WHITE, true);
        qp_drawimage(lcd, 5, 10, logo);

    }



#endif

}




// Fine tuning of TAPPING_TERM valuer on some home row modifiers to avoid errors during typing.
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {

//   // Ring fingers
//   case KC_AL_I:
//   case KC_AL_R:
//   case KC_AR_X:
//   case KC_AR_DO:
//     return TAPPING_TERM + 200;

//   // Pinkies
  case TD_L_LAY:
    return TAPPING_TERM + 0 ;
  case TD_R_LAY:
    return TAPPING_TERM - 80;
  case TD_ENT:
    return TAPPING_TERM - 80;

//   // Middle fingers
//   case KC_CT_S:
//   case KC_CT_E:
//     return TAPPING_TERM - 30;

//   // Right thumb for "symbols" layer
//   case KC_SYBS:
//     return TAPPING_TERM - 50;

//   // Left thumb for delete/gui/mouse combo
//   case KC_CTTA:
//   case KC_FUEN:
//     return TAPPING_TERM - 20;

  // All other keys
  default:
    return TAPPING_TERM;
  }
}


// bootloader
void bootloader (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count >= 6)
  {
    reset_keyboard();
  }
}

// reset
// void layer_rot (qk_tap_dance_state_t *state, void *user_data) {
//   if (state->count == 1)
//   {
//     reset_keyboard();
//   }
// }

// Start Tap Dance

td_state_t cur_dance(qk_tap_dance_state_t *state){
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;

    } else if (state->count == 2) {
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;

    }else if (state->count == 3) {
        if (state->interrupted) return TD_TRIPLE_SINGLE_TAP;
        else if (state->pressed) return TD_TRIPLE_HOLD;
        else return TD_TRIPLE_TAP;
    }else if (state->count == 4) {
        if (state->interrupted) return TD_QUAD_SINGLE_TAP;
        else if (state->pressed) return TD_QUAD_HOLD;
        else return TD_QUAD_TAP;
    } else return TD_UNKNOWN;
}


void td_l_layers_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state_l_layers = cur_dance(state);
    switch(td_state_l_layers){
        default:  break;

        case TD_SINGLE_TAP:
            layer_clear();
            break;

        case TD_SINGLE_HOLD:
            layer_on(_SYMB);
            break;

        case TD_DOUBLE_TAP:
            layer_move(_MOUSE);
        break;
        case TD_DOUBLE_SINGLE_TAP:
        break;
        case TD_DOUBLE_HOLD:
            layer_on(_FUNC);
            break;

        case TD_TRIPLE_TAP:
        case TD_TRIPLE_SINGLE_TAP:
             layer_move(_GAMING);
            break;
        case TD_TRIPLE_HOLD:

            break;
        case TD_QUAD_TAP:
        case TD_QUAD_SINGLE_TAP:
             layer_move(_ADJUST);
            break;
        case TD_QUAD_HOLD:
            break;
    }
}

void td_l_layers_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch(td_state_l_layers){
        case TD_SINGLE_HOLD:
            // if(no_layer_clear){
            //     no_layer_clear = 0;
            //     break; // avoid layer_clear()
            // }
            layer_off(_SYMB);
        case TD_DOUBLE_HOLD:
            layer_off(_FUNC);
        case TD_TRIPLE_HOLD:
            layer_clear();
        break;
        default: break;
    }
    td_state_l_layers = TD_NONE;
}

void td_r_layers_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state_r_layers = cur_dance(state);
    switch(td_state_r_layers){
        default:  break;

        case TD_SINGLE_TAP:
            layer_clear();
            break;

        case TD_SINGLE_HOLD:
            layer_move(_NAV);
            break;

        case TD_DOUBLE_TAP:
            layer_move(_MOUSE);
            break;
        case TD_DOUBLE_SINGLE_TAP:
            break;
        case TD_DOUBLE_HOLD:
            // layer_move(_FUNC);
            break;

        case TD_TRIPLE_TAP:
        break;
        case TD_TRIPLE_SINGLE_TAP:
            //  layer_move(_GAMING);
             break;
        case TD_TRIPLE_HOLD:
            break;
    }
}

void td_r_layers_reset(qk_tap_dance_state_t *state, void *user_data) {
    // wait_ms(10);
    switch(td_state_r_layers){
        case TD_SINGLE_HOLD:
        case TD_DOUBLE_HOLD:
        case TD_TRIPLE_HOLD:
            layer_clear();
            break;
        default: break;
    }
    td_state_r_layers = TD_NONE;
}

void td_r_enter_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state_r_layers = cur_dance(state);
    switch(td_state_r_layers){
        default:  break;

        case TD_SINGLE_TAP:
            register_code16(KC_ENT); break;


        case TD_SINGLE_HOLD:
            layer_move(_MOUSE);
            break;

        case TD_DOUBLE_TAP:
            register_code16(KC_ENT); break;

        case TD_DOUBLE_SINGLE_TAP:
            register_code16(KC_ENT); break;

        case TD_DOUBLE_HOLD:
            break;
        case TD_TRIPLE_TAP:
            register_code16(KC_ENT); break;

        case TD_TRIPLE_SINGLE_TAP:
            register_code16(KC_ENT); break;

        case TD_TRIPLE_HOLD:
            break;
    }
}

void td_r_enter_reset(qk_tap_dance_state_t *state, void *user_data) {

    switch(td_state_r_layers){
        case TD_SINGLE_TAP:
            unregister_code16(KC_ENT); break;
        case TD_SINGLE_HOLD:
        case TD_DOUBLE_HOLD:
        case TD_TRIPLE_HOLD:
            layer_clear();
            break;
        case TD_DOUBLE_TAP:
            unregister_code16(KC_ENT); break;

        case TD_DOUBLE_SINGLE_TAP:
            unregister_code16(KC_ENT); break;

        case TD_TRIPLE_TAP:
            unregister_code16(KC_ENT); break;

        case TD_TRIPLE_SINGLE_TAP:
            unregister_code16(KC_ENT); break;

        default: break;
    }
    td_state_r_layers = TD_NONE;
}


void td_lbrs_finished(qk_tap_dance_state_t *state, void *user_data){
    td_state_lbrs = cur_dance(state);
    switch(td_state_lbrs){
        case TD_SINGLE_TAP:
        case TD_SINGLE_HOLD:
            register_code16(KC_LPRN); break;
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_DOUBLE_HOLD:
            register_code16(KC_LBRC); break;
        case TD_TRIPLE_TAP:
        case TD_TRIPLE_SINGLE_TAP:
        case TD_TRIPLE_HOLD:
            register_code16(KC_LCBR); break;
        default: break;
    }
}

void td_lbrs_reset(qk_tap_dance_state_t *state, void *user_data){
    switch(td_state_lbrs){
        case TD_SINGLE_TAP:
        case TD_SINGLE_HOLD:
            unregister_code16(KC_LPRN); break;
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_DOUBLE_HOLD:
            unregister_code16(KC_LBRC); break;
        case TD_TRIPLE_TAP:
        case TD_TRIPLE_SINGLE_TAP:
        case TD_TRIPLE_HOLD:
            unregister_code16(KC_LCBR); break;
        default: break;
    }
    td_state_lbrs = TD_NONE;
}

void td_rbrs_finished(qk_tap_dance_state_t *state, void *user_data){
    td_state_rbrs = cur_dance(state);
    switch(td_state_rbrs){
        case TD_SINGLE_TAP:
        case TD_SINGLE_HOLD:
            register_code16(KC_RPRN); break;
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_DOUBLE_HOLD:
            register_code16(KC_RBRC); break;
        case TD_TRIPLE_TAP:
        case TD_TRIPLE_SINGLE_TAP:
        case TD_TRIPLE_HOLD:
            register_code16(KC_RCBR); break;
        default: break;
    }
}

void td_rbrs_reset(qk_tap_dance_state_t *state, void *user_data){
    switch(td_state_rbrs){
        case TD_SINGLE_TAP:
        case TD_SINGLE_HOLD:
            unregister_code16(KC_RPRN); break;
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_DOUBLE_HOLD:
            unregister_code16(KC_RBRC); break;
        case TD_TRIPLE_TAP:
        case TD_TRIPLE_SINGLE_TAP:
        case TD_TRIPLE_HOLD:
            unregister_code16(KC_RCBR); break;
        default: break;
    }
    td_state_rbrs = TD_NONE;
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [_BOOT_TAP]  = ACTION_TAP_DANCE_FN(bootloader),
    [_TD_L_LAYERS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_l_layers_finished, td_l_layers_reset),
    [_TD_R_LAYERS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_r_layers_finished, td_r_layers_reset),
    [_TD_R_ENTER] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_r_enter_finished, td_r_enter_reset),
    // [_TD_LBRS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_lbrs_finished, td_lbrs_reset),
    // [_TD_RBRS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_rbrs_finished, td_rbrs_reset),
};



static uint8_t last_backlight = 255;
void suspend_power_down_user(void) {
    if (last_backlight == 255) {
        last_backlight = get_backlight_level();
    }
    backlight_set(0);
    // rgb_matrix_set_suspend_state(true);
    qp_power(lcd, false);
}

void suspend_wakeup_init_user(void) {
    qp_power(lcd, true);
    // rgb_matrix_set_suspend_state(false);
    if (last_backlight != 255) {
        backlight_set(last_backlight);
    }
    last_backlight = 255;
}

#ifdef OLED_ENABLE

// // #ifdef OLED_ENABLE
oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}



void oled_write_wpm(void) {
#ifdef WPM_ENABLE
     // print WPM
     oled_write_P(PSTR("\nWPM: "), false);
     oled_write(get_u8_str(get_current_wpm(), ' '), false);
 #endif
 }

bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }
    if (is_keyboard_master()) {
        // QMK Logo and version information
        // clang-format off
        static const char PROGMEM qmk_logo[] = {
            0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
            0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
            0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};
        // clang-format on

        oled_write_P(qmk_logo, false);
        oled_write_P(PSTR("Redox "), false);

        // Host Keyboard Layer Status
        oled_write_P(PSTR("Layer: "), false);
        switch (get_highest_layer(layer_state | default_layer_state)) {
            case _QWERTY:
                oled_write_P(PSTR("QWERTY\n"), false);
                break;
            // case 1:
            //     oled_write_P(PSTR("Dvorak\n"), false);
            //     break;
            // case 2:
            //     oled_write_P(PSTR("Colemak-DH\n"), false);
            //     break;
            case _NAV:
                oled_write_P(PSTR("Nav\n"), false);
                break;
            case _SYMB:
                oled_write_P(PSTR("Sym\n"), false);
                break;
            case _FUNC:
                oled_write_P(PSTR("Function\n"), false);
                break;
            case _MOUSE:
                oled_write_P(PSTR("Mouse\n"), false);
                break;
            case _GAMING:
                oled_write_P(PSTR("Gaming\n"), false);
                break;
            default:
                oled_write_P(PSTR("Undefined\n"), false);

        }
        #ifdef WPM_ENABLE
            oled_write_wpm();
        #endif

        oled_write_P(PSTR("\n"), false);

        // Host Keyboard LED Status
        led_t led_usb_state = host_keyboard_led_state();
        oled_write_P(led_usb_state.num_lock ? PSTR("NUMLCK ") : PSTR("       "), false);
        oled_write_P(led_usb_state.caps_lock ? PSTR("CAPLCK ") : PSTR("       "), false);
        oled_write_P(led_usb_state.scroll_lock ? PSTR("SCRLCK ") : PSTR("       "), false);
    } else {
        // clang-format off
        static const char PROGMEM redox_logo[] = {

// 'Hylian , 128x64px


0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0xe0, 0xe0, 0xc0, 0xc0,
0xc0, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xf0, 0xf8, 0xfe,
0xfc, 0xf8, 0xe0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xc0, 0xc0,
0xc0, 0xc0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x0f, 0x7f, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfc, 0xfc, 0xf8, 0xf8, 0xf8, 0xf0,
0xf0, 0xf0, 0xe0, 0xe0, 0xc0, 0xc0, 0xc0, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0xc0, 0xe0, 0xf0,
0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x90, 0x1c, 0x1e, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f,
0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1e, 0x98, 0xd0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x18,
0xf0, 0xe0, 0xc0, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0xc0, 0xc0, 0xe0, 0xe0, 0xe0, 0xf0, 0xf0,
0xf0, 0xf8, 0xf8, 0xf8, 0xfc, 0xfc, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0x7f, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,
0x07, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x1f, 0x1f, 0x1f, 0xff, 0xff, 0xff, 0xff, 0x00,
0x00, 0x80, 0xe0, 0xf0, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xf8, 0xe0, 0xc0, 0x00, 0x00,
0x00, 0x80, 0xc0, 0xf0, 0xf8, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xf8, 0xf0, 0xc0, 0x80, 0x00,
0x01, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x1f, 0x1f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x07,
0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x0c, 0x3c, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe,
0xfe, 0xfe, 0xfe, 0x7f, 0x7f, 0x7f, 0x3f, 0x3f, 0x3f, 0x1f, 0x1f, 0x1f, 0xff, 0xff, 0xff, 0xfe,
0xf3, 0xe3, 0xc3, 0x83, 0x83, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0xe0,
0xc2, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x83, 0xc3, 0xc3, 0xe3, 0xfa,
0xfe, 0xff, 0xff, 0xff, 0x1f, 0x1f, 0x1f, 0x3f, 0x3f, 0x3f, 0x7f, 0x7f, 0x7f, 0xfe, 0xfe, 0xfe,
0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0x7c, 0x3c, 0x04, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x0f, 0x0f, 0x07, 0x07, 0x03, 0x03, 0x03, 0x01, 0x01,
0x01, 0x80, 0x80, 0xc0, 0xe0, 0xf0, 0xf0, 0xf8, 0xfc, 0xfe, 0xfe, 0x7f, 0x3f, 0x1f, 0x0f, 0x0f,
0xdf, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x7f, 0x7e, 0x7e, 0x1c, 0x00, 0x80, 0xf0, 0xfc, 0xff, 0xff,
0xff, 0xfc, 0xf8, 0xe0, 0x00, 0x00, 0x3c, 0x7e, 0x7f, 0x7f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0x9f,
0x0f, 0x0f, 0x1f, 0x3f, 0x7f, 0xfe, 0xfc, 0xfc, 0xf8, 0xf0, 0xf0, 0xe0, 0xc0, 0x80, 0x80, 0x01,
0x01, 0x01, 0x03, 0x03, 0x07, 0x07, 0x07, 0x0f, 0x0f, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x0c, 0x1e,
0x1f, 0x3f, 0x7f, 0xff, 0xff, 0x3f, 0x1f, 0x0f, 0x07, 0x01, 0x00, 0x00, 0x80, 0xe0, 0xf8, 0xff,
0xff, 0xff, 0xff, 0x3f, 0x01, 0x00, 0x00, 0x00, 0x08, 0x1c, 0x1e, 0x3f, 0x7f, 0xff, 0xff, 0xff,
0xff, 0xff, 0x7f, 0x3f, 0x3f, 0x1c, 0x08, 0x00, 0x00, 0x00, 0x00, 0x03, 0x3f, 0xff, 0xff, 0xff,
0xfe, 0xf8, 0xe0, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0xff, 0x7f, 0x7f, 0x3f, 0x1f,
0x1e, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x03, 0x03, 0x03, 0x07,
0x07, 0x07, 0x03, 0x00, 0x80, 0xe0, 0xf8, 0xfe, 0x3f, 0x1f, 0x06, 0x00, 0x60, 0xff, 0xff, 0xff,
0xff, 0xff, 0xf0, 0x00, 0x00, 0x0f, 0x1f, 0x7f, 0xfe, 0xf8, 0xc0, 0x00, 0x00, 0x07, 0x07, 0x07,
0x07, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x0f, 0x0f, 0x1f,
0x3f, 0x23, 0x03, 0x03, 0x03, 0x13, 0x1f, 0x0f, 0x07, 0x03, 0x00, 0x00, 0x00, 0x01, 0x0f, 0x7f,
0x3f, 0x03, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x0f, 0x1f, 0x03, 0x03, 0x03, 0x03, 0x33, 0x3f,
0x1f, 0x0f, 0x07, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00



//Aperture science logo

// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// 0x00, 0x00, 0x00, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfc, 0xfc, 0xfc, 0x7b, 0x77, 0x77, 0x6f, 0x4f,
// 0x1f, 0x3f, 0x3f, 0x7f, 0xff, 0xfc, 0x06, 0x7e, 0xfc, 0xf8, 0xf8, 0xf0, 0xe0, 0x80, 0x00, 0x00,
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// 0x00, 0xf8, 0xfd, 0xfd, 0xfd, 0xfd, 0x7d, 0x1c, 0x0e, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x7f, 0x3f, 0x8f, 0xe7, 0xf1, 0x7c, 0x1e,
// 0x1e, 0xfe, 0xfe, 0x80, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xfc, 0xfe, 0xfe, 0xce, 0xc6, 0xee, 0xfe,
// 0xfc, 0x7c, 0x00, 0x00, 0x00, 0xc0, 0xfc, 0xfe, 0xfe, 0x6e, 0x66, 0x66, 0x66, 0x06, 0x06, 0x00,
// 0x00, 0x00, 0xf8, 0xfe, 0xfe, 0xde, 0xc6, 0xc6, 0xee, 0xfe, 0x3c, 0x00, 0x00, 0x00, 0x04, 0x06,
// 0x86, 0xfe, 0xfe, 0x7e, 0x0e, 0x06, 0x06, 0x06, 0x00, 0xc0, 0xfc, 0xfe, 0x7e, 0x0e, 0x00, 0x00,
// 0x00, 0xe0, 0xfe, 0xfe, 0x1e, 0x00, 0x00, 0x00, 0xe0, 0xfc, 0xfe, 0xfe, 0xc6, 0xc6, 0xee, 0xfe,
// 0x3c, 0x1c, 0x00, 0x00, 0x00, 0xf0, 0xfe, 0xfe, 0x7e, 0x66, 0x66, 0x66, 0x66, 0x06, 0x00, 0x00,
// 0x00, 0x1f, 0x1f, 0xe7, 0xf3, 0xfc, 0xfe, 0xff, 0xf0, 0x00, 0xc0, 0x80, 0x80, 0x00, 0x00, 0x00,
// 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x98, 0xdc, 0xdf, 0xcf, 0xc3, 0xe3, 0x03, 0x03,
// 0x03, 0x1f, 0x9f, 0x1f, 0x00, 0x00, 0x00, 0x1e, 0x1f, 0x0f, 0x03, 0x41, 0xc1, 0x01, 0x00, 0x00,
// 0x00, 0x00, 0xc0, 0x40, 0x5e, 0x5f, 0x1f, 0x1f, 0x1c, 0x1c, 0x9c, 0x5c, 0x44, 0x40, 0x80, 0x00,
// 0x18, 0x1f, 0x1f, 0xc7, 0x40, 0x40, 0x4f, 0x1f, 0x1f, 0x0f, 0x00, 0x00, 0x00, 0xc0, 0x80, 0x1c,
// 0x1f, 0x0f, 0x07, 0x40, 0x40, 0xc0, 0x40, 0x40, 0x00, 0x07, 0x0f, 0x8f, 0x5c, 0x5c, 0x5c, 0x9c,
// 0x0f, 0x0f, 0x07, 0x00, 0xc0, 0x40, 0x48, 0x5f, 0x1f, 0x0f, 0x01, 0x00, 0x80, 0x1f, 0x1f, 0x1f,
// 0x00, 0x40, 0x40, 0x48, 0x5f, 0x1f, 0x1f, 0x1c, 0x1c, 0xdc, 0x5c, 0x4c, 0x80, 0x00, 0x00, 0x00,
// 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x1f, 0x3e, 0x01, 0x3f, 0x7f, 0x7f, 0x7e, 0x7e,
// 0x7c, 0x79, 0x7b, 0x77, 0x67, 0x2f, 0x1f, 0x1f, 0x1f, 0x0f, 0x0f, 0x07, 0x03, 0x00, 0x00, 0x00,
// 0x00, 0x00, 0x07, 0x04, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x02, 0x03, 0x00, 0x00,
// 0x00, 0x00, 0x07, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x04, 0x04, 0x06, 0x00,
// 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x06, 0x03, 0x00, 0x03, 0x06,
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x04, 0x04, 0x06,
// 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00,
// 0x00, 0x04, 0x05, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x04, 0x06, 0x00, 0x00, 0x00,
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

};
        // clang-format on
        oled_write_raw_P(redox_logo, sizeof(redox_logo));
    }
    return false;
}
#endif


void housekeeping_task_user(void) {

#ifdef QUANTUM_PAINTER_ENABLE

    static uint32_t last_draw = 0;
    static uint8_t  last_wpm = 0;
    static uint8_t first_draw =1;
    char buf[20] = "wpm:    ";


    if (timer_elapsed32(last_draw) > 33) { // Throttle to 15fps
        last_draw = timer_read32();
        if (is_keyboard_master()) {

            bool            layer_state_redraw = false;
            static uint32_t last_layer_state   = 0;
                if (last_layer_state != layer_state) {
                    last_layer_state   = layer_state;
                    layer_state_redraw = true;
                }




            uint8_t wpm = get_current_wpm();
            if (last_wpm!=wpm || first_draw)
            {
                qp_rect(lcd, 115, 65,143 ,65 + my_font->line_height ,HSV_WHITE, true);
                last_wpm = wpm;
                snprintf(&buf[5], 4, "%d", wpm);
                qp_drawtext_recolor(lcd, 80, 65, my_font, buf,HSV_BLACK,HSV_WHITE);

            }


            if (layer_state_redraw || first_draw)
            {
                const char        *layer_name;
                layer_name = current_layer_name();
                qp_rect(lcd, 100, 80,161 ,80 + my_font->line_height ,HSV_WHITE, true);
                snprintf(&buf[0],20, "layer: %s", layer_name);

                qp_drawtext_recolor(lcd, 63, 80, my_font, buf,HSV_BLACK,HSV_WHITE);
            }



        }
        else
        {
            /* code */
        }

    }

    qp_flush(lcd);
    first_draw = 0;

#endif

}



// Layer naming
const char *current_layer_name(void) {
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            return "qwerty";
        case _SYMB:
            return "symbols";
        case _MOUSE:
            return "mouse";
        case _NAV:
            return "nav";
        case _FUNC:
            return "function";
        case _GAMING:
            return "gaming";
        case _ADJUST:
            return "adjust";
    }
    return "unknown";
}




bool process_record_user(uint16_t keycode, keyrecord_t *record){
    // process custom keycodes
    if (record->event.pressed) {
        switch(keycode) {
            case ASC_MAJOR:
                SEND_STRING(">");
                return false;
            case ASC_MINOR:
                SEND_STRING("<");
            	return false;

            case FD_TIME:
                if(++fade_time_option_index>=FADE_TIME_OPTIONS_NUMBER)
                    fade_time_option_index = 0;
                fade_time = fade_time_options[fade_time_option_index];
                return false;
            case FD_HUE:
                // fade_default_hsv.h+=16;
                // if(fade_default_hsv.h == 0)
                //     fade_default_hsv.h = 255;
                // else if(fade_default_hsv.h == 15)
                //         fade_default_hsv.h = 0;
                return false;
            case FD_SAT:
                fade_default_hsv.s+=16;
                if(fade_default_hsv.s == 0)
                    fade_default_hsv.s = 255;
                else if(fade_default_hsv.s == 15)
                        fade_default_hsv.s = 0;
                return false;
            case FD_VAL:
                fade_default_hsv.v+=16;
                if(fade_default_hsv.v == 0)
                    fade_default_hsv.v = 255;
                else if(fade_default_hsv.v == 15)
                        fade_default_hsv.v = 0;
                return false;
        }
    }
    return true;
};



#ifdef RGBLIGHT_ENABLE
/*
const uint8_t quadratic_curve[256] = {
  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   1,   1,   1,
  1,   1,   1,   1,   2,   2,   2,   2,   2,   2,   3,   3,   3,   3,   4,   4,
  4,   4,   5,   5,   5,   5,   6,   6,   6,   7,   7,   7,   8,   8,   8,   9,
  9,   9,  10,  10,  11,  11,  11,  12,  12,  13,  13,  14,  14,  15,  15,  16,
 16,  17,  17,  18,  18,  19,  19,  20,  20,  21,  21,  22,  23,  23,  24,  24,
 25,  26,  26,  27,  28,  28,  29,  30,  30,  31,  32,  32,  33,  34,  35,  35,
 36,  37,  38,  38,  39,  40,  41,  42,  42,  43,  44,  45,  46,  47,  47,  48,
 49,  50,  51,  52,  53,  54,  55,  55,  56,  57,  58,  59,  60,  61,  62,  63,
 64,  65,  66,  67,  68,  69,  70,  71,  72,  74,  75,  76,  77,  78,  79,  80,
 81,  82,  84,  85,  86,  87,  88,  89,  91,  92,  93,  94,  95,  97,  98,  99,
100, 102, 103, 104, 105, 107, 108, 109, 111, 112, 113, 115, 116, 117, 119, 120,
121, 123, 124, 126, 127, 128, 130, 131, 133, 134, 136, 137, 139, 140, 141, 143,
144, 146, 147, 149, 151, 152, 154, 155, 157, 158, 160, 161, 163, 165, 166, 168,
170, 171, 173, 174, 176, 178, 179, 181, 183, 185, 186, 188, 190, 191, 193, 195,
197, 198, 200, 202, 204, 206, 207, 209, 211, 213, 215, 216, 218, 220, 222, 224,
226, 228, 229, 231, 233, 235, 237, 239, 241, 243, 245, 247, 249, 251, 253, 255
};

const uint8_t exp_curve[256] =
{
   0,   0,   0,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
   1,   1,   1,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,
   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   3,   3,   3,   3,   3,
   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,   4,   4,   4,   4,   4,   4,
   4,   4,   4,   4,   4,   4,   5,   5,   5,   5,   5,   5,   5,   5,   5,   6,
   6,   6,   6,   6,   6,   6,   6,   7,   7,   7,   7,   7,   7,   8,   8,   8,
   8,   8,   8,   9,   9,   9,   9,   9,  10,  10,  10,  10,  10,  11,  11,  11,
  11,  12,  12,  12,  12,  13,  13,  13,  14,  14,  14,  14,  15,  15,  15,  16,
  16,  16,  17,  17,  18,  18,  18,  19,  19,  20,  20,  21,  21,  21,  22,  22,
  23,  23,  24,  24,  25,  25,  26,  27,  27,  28,  28,  29,  30,  30,  31,  32,
  32,  33,  34,  35,  35,  36,  37,  38,  39,  39,  40,  41,  42,  43,  44,  45,
  46,  47,  48,  49,  50,  51,  52,  53,  55,  56,  57,  58,  59,  61,  62,  63,
  65,  66,  68,  69,  71,  72,  74,  76,  77,  79,  81,  82,  84,  86,  88,  90,
  92,  94,  96,  98, 100, 102, 105, 107, 109, 112, 114, 117, 119, 122, 124, 127,
 130, 133, 136, 139, 142, 145, 148, 151, 155, 158, 162, 165, 169, 172, 176, 180,
 184, 188, 192, 196, 201, 205, 210, 214, 219, 224, 229, 234, 239, 244, 250, 255
};
*/

void rgb_to_hsv(fade_rgb_t *rgb, HSV *hsv){
    int32_t min, max, delta, hue;
    int32_t R = rgb->r.cur>>8;
    int32_t G = rgb->g.cur>>8;
    int32_t B = rgb->b.cur>>8;

    // find min
    min = (R < G ? R : G);
    min = (min < B ? min : B);
    // find max
    max = (R > G ? R : G);
    max = (max > B ? max : B);
    // calculate delta
    delta = max - min;

    // calculate HUE
    if(R == max)
        hue = ((G - B)*60/delta);

    else if(G == max)
        hue = (120 + ((B - R)*60/delta));

    else if(B == max)
        hue = (240 + ((R - G)*60/delta));

    if(hue < 0)
        hue += 360;
    hsv->h = hue*255/360;

    // calculate Saturation
    hsv->s = 0;
    if( max != 0 )
        hsv->s = ((delta*255) / max);
    // check max saturation
    if( hsv->s > fade_default_hsv.s )
        hsv->s = fade_default_hsv.s;

    // set Value
    hsv->v = max * fade_default_hsv.v / 255;
    // hsv->v = quadratic_curve[hsv->v];
    // hsv->v = exp_curve[hsv->v];
}

void fade_color_scan(fade_color_t *c){
    if(fade_timer < fade_time ){
        // do step
        if(c->cur < c->end){
            if(c->cur >= c->end-c->step){
                c->cur = c->end;
            }else{
                c->cur += c->step;
            }
        }else{
            // cur > end
            if(c->cur <= c->end+c->step){
                c->cur = c->end;
            }else{
                c->cur -= c->step;
            }
        }
    }else{
        c->cur = c->end;
    }
}

void fade_rgb_scan(void){
    // increment fade_timer
    if(fade_timer < fade_time)
        fade_timer++;

    // fade current to end
    fade_color_scan(&fade_rgb.r);
    fade_color_scan(&fade_rgb.g);
    fade_color_scan(&fade_rgb.b);

    // set hsv
    rgb_to_hsv(&fade_rgb, &fade_hsv);
    rgblight_sethsv_noeeprom(fade_hsv.h, fade_hsv.s, fade_hsv.v);
}

#define FADE_CALC_STEP(cur, end, ft) (((cur>end ? cur-end : end-cur)/ft)+1)

void fade_goto(uint8_t end_r, uint8_t end_g, uint8_t end_b){

    if( (fade_rgb.r.end>>8 == end_r) &&
        (fade_rgb.g.end>>8 == end_g) &&
        (fade_rgb.b.end>>8 == end_b) ) return;

    fade_rgb.r.end = end_r<<8;
    fade_rgb.g.end = end_g<<8;
    fade_rgb.b.end = end_b<<8;

    fade_rgb.r.step = FADE_CALC_STEP(fade_rgb.r.cur, fade_rgb.r.end, fade_time);
    fade_rgb.g.step = FADE_CALC_STEP(fade_rgb.g.cur, fade_rgb.g.end, fade_time);
    fade_rgb.b.step = FADE_CALC_STEP(fade_rgb.b.cur, fade_rgb.b.end, fade_time);

    fade_timer = 0;
}

void fade_init(void){
    rgblight_sethsv_noeeprom(0, 0, 0); // set leds off
    fade_time = fade_time_options[fade_time_option_index];
}

//         Led Scheme
//    left             right


void set_current_layer_color_leds(layer_state_t state){
    // Keyboard Layer Status
    switch (get_highest_layer(state)) {
        case _QWERTY:
            fade_goto(RGB_WHITE);
            break;
        case _SYMB:
            fade_goto(RGB_BLUE);
            break;
        case _MOUSE:
            fade_goto(RGB_GREEN);
            break;
        case _NAV:
            fade_goto(RGB_YELLOW);
            break;
        case _FUNC:
            fade_goto(RGB_PURPLE);
            break;
        case _GAMING:
            fade_goto(RGB_RED);
            break;
        case _ADJUST:
            fade_goto(RGB_ORANGE);
            break;
        default:
            fade_goto(RGB_PINK);
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    set_current_layer_color_leds(state);
    return state;
}

#endif

void matrix_scan_user(){ // called every 1ms
    fade_rgb_scan();
}

void keyboard_pre_init_user(){
    fade_init();
    fade_goto(RGB_WHITE);
}
