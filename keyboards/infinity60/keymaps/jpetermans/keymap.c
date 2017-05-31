#include "infinity60.h"
#include "led_controller.h"

//Helpful Defines
#define _______ KC_TRNS

//Define Layer Names
#define _BASE 0
#define _NUMPAD 1
#define _FNAV 2
#define _MEDIA 3
#define _TILDE 4

//IS31 chip has 8 available led pages, using 0 for all leds and 7 for single toggles
#define max_pages 6

enum ic60_keycodes {
  NUMPAD,
  FNAV,
  MEDIA,
  TILDE,
  CTLALTDEL,
  BACKLIGHT,
  BRIGHT,
  DIM,
  ALL,
  GAME,
  MODE_SINGLE,
  MODE_PAGE,
  MODE_FLASH
};

uint8_t current_layer_global = 0;
uint8_t led_mode_global = MODE_SINGLE;
uint8_t backlight_status_global = 1; //init on/off state of backlight
uint32_t led_layer_state = 0;

/* ==================================
 *             KEYMAPS
 * ==================================*/

const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Layer 0: Default Layer
     * ,-----------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  Backs|
     * |-----------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|
     * |-----------------------------------------------------------|
     * |CapsLo|  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Enter   |
     * |-----------------------------------------------------------|
     * |Shif|   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift     |
     * |-----------------------------------------------------------|
     * |Ctrl|Gui |Alt |         Space    |Alt |Gui |  FN  | Ctrl   |
     * `-----------------------------------------------------------'
     */
    /* default */
    [_BASE] = KEYMAP( \
        KC_ESC,    KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, KC_BSLS,KC_NO,\
        KC_TAB,    KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,KC_RBRC,KC_BSPC,   \
        TT(_FNAV), KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,KC_ENT,         \
        KC_LSFT,   KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,F(TILDE),KC_NO,          \
        KC_LCTL,   KC_LGUI,KC_LALT,            LT(_FNAV, KC_SPC),       KC_RALT,TG(_NUMPAD),MO(_MEDIA), KC_RCTL         \
    ),

    /* numpad */
    [_NUMPAD] = KEYMAP( \
        _______,_______,_______,_______,_______,_______,_______, KC_P7, KC_P8, KC_P9, KC_PSLS, _______,_______,_______,KC_NO,\
        _______,_______,_______,_______,_______,_______,_______, KC_P4, KC_P5, KC_P6, KC_PAST, _______,_______,_______, \
        MO(_FNAV),_______,_______,_______,_______,_______,_______, KC_P1, KC_P2, KC_P3, KC_PMNS, _______,_______,      \
        _______,_______,_______,_______,_______,_______,_______, KC_P0,KC_COMM,KC_PDOT,KC_PPLS, _______,KC_NO,      \
        _______,_______,_______,               TO(_BASE),           _______,_______,_______,_______   \
    ),

    /* F-, arrow, and media keys */
    [_FNAV] = KEYMAP( \
        KC_GRV, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, _______,KC_NO,\
        KC_CAPS,_______,_______,_______,_______,_______,_______,KC_PGUP,KC_UP,KC_PGDN,KC_PSCR,_______,_______,KC_DEL,  \
        _______,_______,KC_BTN2,_______,_______,_______,KC_HOME,KC_LEFT,KC_DOWN,KC_RGHT,KC_INS,_______,_______,     \
        _______,KC_APP,KC_BTN1,KC_CALC,_______,_______,KC_END,_______,_______,_______,_______,_______,KC_NO,         \
        _______,_______,_______,               _______,         F(CTLALTDEL),KC_NLCK,_______,_______   \
    ),

    /* media */
    [_MEDIA] = KEYMAP( \
        _______,F(MODE_SINGLE),F(MODE_PAGE),F(MODE_FLASH),_______,_______,_______, _______, _______, _______,KC_MUTE, KC_VOLD, KC_VOLU,_______,KC_NO,\
        _______,_______,_______,_______,_______,_______,_______, _______, _______, _______,_______, _______,_______,_______,\
        _______,_______,_______,_______,_______,F(GAME),_______, _______, _______, _______,_______, _______,_______,     \
        _______,_______,F(ALL) ,F(BRIGHT),F(DIM),F(BACKLIGHT),_______, _______, KC_MPRV, KC_MNXT,KC_MSTP, _______,KC_NO,       \
        _______,_______,_______,               KC_MPLY,             _______,_______, _______,_______      \
    ),
    /* ~ */
    [_TILDE] = KEYMAP( \
        KC_GRV,_______,_______,_______,_______,_______,_______, _______, _______, _______,_______, _______,_______,_______,KC_NO,\
        _______,_______,_______,_______,_______,_______,_______, _______, _______, _______,_______, _______,_______,_______,\
        _______,_______,_______,_______,_______,_______,_______, _______, _______, _______,_______, _______,_______,     \
        _______,_______,_______,_______,_______,_______,_______, _______, _______, _______,_______, _______,KC_NO,       \
        _______,_______,_______,               _______,             _______,_______, _______,_______      \
    ),
    /* template */
    [5] = KEYMAP( \
        _______,_______,_______,_______,_______,_______,_______, _______, _______, _______,_______, _______,_______,_______,KC_NO,\
        _______,_______,_______,_______,_______,_______,_______, _______, _______, _______,_______, _______,_______,_______,\
        _______,_______,_______,_______,_______,_______,_______, _______, _______, _______,_______, _______,_______,     \
        _______,_______,_______,_______,_______,_______,_______, _______, _______, _______,_______, _______,KC_NO,       \
        _______,_______,_______,               _______,             _______,_______, _______,_______      \
    ),
};

//id for user defined functions and macros
enum function_id {
    NONE,
};

enum macro_id {
    ACTION_LEDS_ALL,
    ACTION_LEDS_GAME,
    ACTION_LEDS_BACKLIGHT,
    ACTION_LEDS_BRIGHT,
    ACTION_LEDS_DIM,
    ACTION_LEDS_SINGLE,
    ACTION_LEDS_PAGE,
    ACTION_LEDS_FLASH
};

/* ==================================
 *          LED MAPPING
 * ==================================*/

/*
    Infinity60 LED MAP
    11 12 13 14 15 16 17 18 21 22 23 24 25  26 27*
     28 31 32 33 34 35 36 37 38 41 42 43 44 45
     46 47 48 51 52 53 54 55 56 57 58 61    62
      63 64 65 66 67 68 71 72 73 74 75      76 77*
    78  81  82       83         84  85  86  87
    *Unused in Alphabet Layout
*/

//======== full page arrays =========
//any change in array size needs to be mirrored in matrix_init_user
uint8_t led_numpad[16] = {
  18,21,22,23,
  37,38,41,42,
  55,56,57,58,
  72,73,74,75
};
//LED Page 2 - _Nav
uint8_t led_nav[12] = {
                        38,
  47,48,              55,56,57,
     64,65,66
};
//LED Page 3 - _Media
uint8_t led_media[15] = {
  12,13,14,           23,24,25,
     65,66,67,68,    73,74,75,
           83,          86
};
//LED Page 4 - _Game "WASD"
uint8_t led_game[5] = {
  11,
        32,
     47,48,51
};

//======== qmk functions =========
const uint16_t fn_actions[] = {
    [CTLALTDEL] = ACTION_KEY(LALT(LCTL(KC_DEL))),
    [TILDE] = ACTION_LAYER_MODS(_TILDE, MOD_LSFT),
    [ALL] = ACTION_FUNCTION(ACTION_LEDS_ALL),
    [GAME] = ACTION_FUNCTION(ACTION_LEDS_GAME),
    [BACKLIGHT] = ACTION_FUNCTION(ACTION_LEDS_BACKLIGHT),
    [BRIGHT] = ACTION_FUNCTION(ACTION_LEDS_BRIGHT),
    [DIM] = ACTION_FUNCTION(ACTION_LEDS_DIM),
    [MODE_SINGLE] = ACTION_FUNCTION(ACTION_LEDS_SINGLE),
    [MODE_PAGE] = ACTION_FUNCTION(ACTION_LEDS_PAGE),
    [MODE_FLASH] = ACTION_FUNCTION(ACTION_LEDS_FLASH),
};

/* custom action function */
void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
  msg_t msg;

  switch(id) {
    case ACTION_LEDS_ALL:
      if(record->event.pressed) {
        led_mode_global = led_mode_global == ALL ? MODE_SINGLE : ALL;
        msg=TOGGLE_ALL;
        chMBPost(&led_mailbox, msg, TIME_IMMEDIATE);
      }
      break;

    case ACTION_LEDS_BACKLIGHT:
      if(record->event.pressed) {
        backlight_status_global ^= 1;
        msg=(backlight_status_global << 8) | TOGGLE_BACKLIGHT;
        chMBPost(&led_mailbox, msg, TIME_IMMEDIATE);
      }
      break;

    case ACTION_LEDS_GAME:
      if(record->event.pressed) {
        led_mode_global = led_mode_global == GAME ? MODE_SINGLE : GAME;

        msg=(4 << 8) | DISPLAY_PAGE;
        chMBPost(&led_mailbox, msg, TIME_IMMEDIATE);
      }
      break;

    case ACTION_LEDS_BRIGHT:
      if(record->event.pressed) {
        msg=(1 << 8) | STEP_BRIGHTNESS;
        chMBPost(&led_mailbox, msg, TIME_IMMEDIATE);
      }
      break;

    case ACTION_LEDS_DIM:
      if(record->event.pressed) {
        msg=(0 << 8) | STEP_BRIGHTNESS;
        chMBPost(&led_mailbox, msg, TIME_IMMEDIATE);
      }
      break;

    //set led_mode for matrix_scan to toggle leds
    case ACTION_LEDS_SINGLE:
      led_mode_global = MODE_SINGLE;
      break;
    case ACTION_LEDS_PAGE:
      led_mode_global = MODE_PAGE;
      break;
    case ACTION_LEDS_FLASH:
      led_mode_global = MODE_FLASH;
      break;

  }
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    return MACRO_NONE;
};


bool process_record_user (uint16_t keycode, keyrecord_t *record) {
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

    led_controller_init();

    // Write predefined led pages.
    write_led_page(_NUMPAD, led_numpad, 16);
    chThdSleepMilliseconds(10);

    write_led_page(_FNAV, led_nav, 12);
    chThdSleepMilliseconds(10);

    write_led_page(_MEDIA, led_media, 15);
    chThdSleepMilliseconds(10);

    write_led_page(4, led_game, 5);
    chThdSleepMilliseconds(1000);
};

// Loops constantly in the background.
void matrix_scan_user(void) {
  uint8_t page;
  uint8_t led_pin_byte;
  msg_t msg;

  if (backlight_status_global == 0) {//backlight is off, skip the rest
    return;
  }

  if (led_layer_state != layer_state && led_mode_global != GAME && led_mode_global != ALL) {
    //check mode
    //Turn on layer indicator or page depending on mode
    switch(led_mode_global) {
      case MODE_FLASH: //flash preset page leds then single indicator
        page = biton32(layer_state) > max_pages ? 7 : biton32(layer_state);
        msg=(page << 8) | DISPLAY_PAGE;
        chMBPost(&led_mailbox, msg, TIME_IMMEDIATE);
        chThdSleepMilliseconds(500);
        //flow to display single layer leds

      case MODE_SINGLE: //light layer indicators for all active layers
        led_pin_byte = layer_state & 0xFF;
        msg=(7 << 8) | DISPLAY_PAGE;
        chMBPost(&led_mailbox, msg, TIME_IMMEDIATE);
        msg=(1 << 16) | (led_pin_byte << 8) | SET_FULL_ROW;
        chMBPost(&led_mailbox, msg, TIME_IMMEDIATE);
        break;

      case MODE_PAGE: //display pre-defined led page
        page = biton32(layer_state) > max_pages ? 7 : biton32(layer_state);
        msg=(page << 8) | DISPLAY_PAGE;
        chMBPost(&led_mailbox, msg, TIME_IMMEDIATE);
        break;
      }
  led_layer_state = layer_state;
  }
}
