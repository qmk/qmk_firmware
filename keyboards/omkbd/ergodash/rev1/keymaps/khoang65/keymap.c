#include QMK_KEYBOARD_H

bool isLeader = false;
bool onMac = false;

enum layer_names { // Enum over macro definition, i.e. #define BASE 0, to optimize memory
    _BASE = 0,
    _FN, // = 1
    _NUM, // = 2
    _VIM, // = 3
    _NAV, // = 4
    _SYM, // = 5
    _ADJUST // = 6
};

#define MEH_F13  MEH_T(KC_F13)
#define FNT_PSCR LT(_FN,KC_PSCR)
#define FNT_BSLS LT(_FN,KC_BSLS)
#define NAVM_CTL LM(_NAV, MOD_LCTL)
#define NAVM_SFT LM(_NAV, MOD_LSFT)
#define NUMT_SCLN LT(_NUM, KC_SCLN)
#define CS_F14   C_S_T(KC_F14)
#define ALL_     ALL_T(KC_NO) 
//#define MEH_     MEH(KC_NO)

#define CTLRT    LCTL(KC_RGHT)
#define CTLLFT   LCTL(KC_LEFT)
#define CTLC     LCTL(KC_C)
#define CTLZ     LCTL(KC_Z)
#define CTLV     LCTL(KC_V)
#define CTLX     LCTL(KC_X)
#define CTLF     LCTL(KC_F)
#define CTLY     LCTL(KC_Y)

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE,
  BASE_ESC,
  /* VIM Cursor Movement */
  KC_SOL, 
  /* VIM Visual/Cut and Paste */
  KC_yy_COPY_LINE,
  KC_Y_COPY_TO_EOL, // Worth?
  KC_dd_CUT_LINE,
  KC_D_CUT_TO_EOL,  // Worth?
};

// ** TAP DANCE Definitions ** //
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_DOUBLE_TAP,
    TD_TRIPLE_TAP
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

enum custom_tapdance_actions{
    VIM_d,
    VIM_y,
    QUOT_CW, // KC_QUOT + CAPS_WORD
};

td_state_t cur_dance(qk_tap_dance_state_t *state);

void d_finished(qk_tap_dance_state_t *state, void *user_data);
void d_reset(qk_tap_dance_state_t *state, void *user_data); 
void y_finished(qk_tap_dance_state_t *state, void *user_data);
void y_reset(qk_tap_dance_state_t *state, void *user_data);
void quote_capsword_finished(qk_tap_dance_state_t *state, void *user_data);
void quote_capsword_reset(qk_tap_dance_state_t *state, void *user_data);

// NOTE: NEEDS TO BE REFACTORED / ADDED TO USERSPACE
// ** Functions for sending custom keycodes ** //
/* 
 * QMK functions can't register custom keycodes, but we can setup a keyrecord_t and call process_record_kb() directly.
 * Unknowns:
 *  Do we need to set the column and row for each keycode?
 *  Could reusing the same keyrecord_t struct cause problems with keycodes clobbering each other?
*/
// Dummy keyrecord_t for hooking process_record_kb() with custom keycodes
static keyrecord_t dummy_record = {
    .event = {
        .key = {
            .col = 0,
            .row = 0,
            },
        .pressed = false,
        .time = 0,
    },
    .tap = {0},
};

// Setup dummy_record for process_record_kb()
void setup_dummy_record(uint8_t col, uint8_t row, bool pressed) {
    dummy_record.event.key.col = col;
    dummy_record.event.key.row = row;
    dummy_record.event.pressed = pressed;
    dummy_record.event.time = timer_read();
}

// Register a custom keycode with process_record_kb()
void register_custom_keycode(uint16_t keycode, uint8_t col, uint8_t row) {
    setup_dummy_record(col, row, true);
    process_record_kb(keycode, &dummy_record);
}

// Unregister a custom keycode with process_record_kb()
void unregister_custom_keycode(uint16_t keycode, uint8_t col, uint8_t row) {
    setup_dummy_record(col, row, false);
    process_record_kb(keycode, &dummy_record);
}

// Tap a custom keycode with process_record_kb()
void tap_custom_keycode(uint16_t keycode, uint8_t col, uint8_t row) {
    register_custom_keycode(keycode, col, row);
    wait_ms(10);
    unregister_custom_keycode(keycode, col, row);
};
/* End functions for sending custom keycodes */


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
   /* Keymap 0: BASE layer
   * ,-----------------------------------------------------------.                              ,-----------------------------------------------------------.
   * | ESC     | !1      | @2      | #3      | $4      | %5      |---------.          ,---------| ^6      | &7      | *8      | (9      | )0      | _-      |
   * |---------+---------+---------+---------+---------+---------| {[      |          | }]      |---------+---------+---------+---------+---------+---------|
   * | Tab     | Q       | W       | E       | R       | T       |---------|          |---------| Y       | U       | I       | O       | P       | LEADER  |
   * |---------+---------+---------+---------+---------+---------| F4      |          | +=      |---------+---------+---------+---------+---------+---------|
   * | ~`      | A       | S       | D       | F       | G       |---------|          |---------| H       | J       | K       | L       | NUM(:;) | "'/CapsW|
   * |---------+---------+---------+---------+---------+---------|LT1(PSCR)|          | LT1(|\) |---------+---------+---------+---------+---------|---------|
   * | LShift  | Z       | X       | C       | V       | B       |---------'          `---------| N       | M       | <,      | >.      | ?/      | RShift  |
   * |---------+---------+---------+-----------------------------'                              `-----------------------------+---------+---------+---------|
   * | LCtrl   | Meh(F13)| OS      |  | LAlt    |      ,-------------------.          ,-------------------.      | All()   |  | F15     | F16     | TT(NUM) |
   * `-----------------------------'  `---------'      |         |         |          |         |         |      `---------'  `-----------------------------'
   *                                                   | Del     | CS(F14) |          | MO(VIM) | Enter   |
   *                                         ,---------|         |         |          |         |         +---------.
   *                                         | Space   |         |         |          |         |         | BckSpc  |
   *                                         `-----------------------------'          `-----------------------------'                                      */
  [_BASE] = LAYOUT_4key_2u_inner(
      KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_LBRC,             KC_RBRC,  KC_6,     KC_7,     KC_8,      KC_9,     KC_0,    KC_MINS, 
      KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_F4,               KC_EQL,   KC_Y,     KC_U,     KC_I,      KC_O,     KC_P,    KC_LEAD, 
      KC_GRV,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     FNT_PSCR,            FNT_BSLS, KC_H,     KC_J,     KC_K,      KC_L,     NUMT_SCLN, TD(QUOT_CW),
      KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_NO,               KC_NO,    KC_N,     KC_M,     KC_COMM,   KC_DOT,   KC_SLSH, KC_RSFT, 
      KC_LCTL,  MEH_F13,  KC_LGUI,  KC_LALT,  KC_SPC,   KC_DEL,   CS_F14,              MO(_VIM), KC_ENT,   KC_BSPC,  ALL_,      KC_F15,   KC_F16,  TT(_NUM)
      ),
  

   /* Keymap 1: FUNCTION layer
   * ,-----------------------------------------------------------.                              ,-----------------------------------------------------------.
   * | TRNS    | F1      | F2      | F3      | F4      | F5      |---------.          ,---------| F6      | F7      | F8      | F9      | F10     | TRNS    |
   * |---------+---------+---------+---------+---------+---------| F11     |          | F12     |---------+---------+---------+---------+---------+---------|
   * | TRNS    | TRNS    | TRNS    | TRNS    | TRNS    | TRNS    |---------|          |---------| TRNS    | TRNS    | TRNS    | TRNS    | TRNS    | TRNS    |
   * |---------+---------+---------+---------+---------+---------| TRNS    |          | TRNS    |---------+---------+---------+---------+---------+---------|
   * | TRNS    | TRNS    | TRNS    | TRNS    | TRNS    | TRNS    |---------|          |---------| TRNS    | TRNS    | TRNS    | TRNS    | TRNS    | TRNS    |
   * |---------+---------+---------+---------+---------+---------| TRNS    |          | TRNS    |---------+---------+---------+---------+---------|---------|
   * | TRNS    | TRNS    | TRNS    | TRNS    | TRNS    | TRNS    |---------'          `---------| TRNS    | TRNS    | TRNS    | TRNS    | TRNS    | TRNS    |
   * |---------+---------+---------+-----------------------------'                              `-----------------------------+---------+---------+---------|
   * | TRNS    | TRNS    | TRNS    |  | TRNS    |      ,-------------------.          ,-------------------.      | TRNS    |  | TRNS    | TRNS    | TO(BASE)|
   * `-----------------------------'  `---------'      |         |         |          |         |         |      `---------'  `-----------------------------'
   *                                                   | TRNS    | TRNS    |          | TRNS    | TRNS    |        
   *                                         ,---------|         |         |          |         |         +---------.
   *                                         | TRNS    |         |         |          |         |         | TRNS    |
   *                                         `-----------------------------'          `-----------------------------'                                      */
	[_FN] = LAYOUT_4key_2u_inner(
      KC_TRNS,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F11,              KC_F12,   KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,    KC_TRNS, 
      KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,             KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS, 
      KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,             KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS, 
      KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,             KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS, 
      KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,             KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   TO(_BASE)
      ),
      

   /* Keymap 2: NUMPAD Layer
   * ,-----------------------------------------------------------.                              ,-----------------------------------------------------------.
   * | TRNS    | !       | @       | #       | $       | %       |---------.          ,---------| ^       | &       |  *      |  /      |  -      | TRNS    |
   * |---------+---------+---------+---------+---------+---------| {[      |          | }]      |---------+---------+---------+---------+---------+---------|
   * | TRNS    |         |         | PgUp    |         |         |---------|          |---------|  +      |  7      |  8      |  9      |  +      |         |
   * |---------+---------+---------+---------+---------+---------| TT(ADJ) |          | TRNS    |---------+---------+---------+---------+---------+---------|
   * | TRNS    |         | Home    | PgDn    | End     |         |---------|          |---------|  =      |  4      |  5      |  6      | TRNS    | "'      |
   * |---------+---------+---------+---------+---------+---------| PrtScr  |          | |\      |---------+---------+---------+---------+---------|---------|
   * | TRNS    |         |         |         |         |         |---------'          `---------|  0      |  1      |  2      |  3      | TRNS    | TRNS    |
   * |---------+---------+---------+-----------------------------'                              `-----------------------------+---------+---------+---------|
   * | TRNS    | TRNS    | TRNS    |  | TRNS    |      ,-------------------.          ,-------------------.      | 0       |  | .       | TRNS    | TO(BASE)|
   * `-----------------------------'  `---------'      |         |         |          |         |         |      `---------'  `-----------------------------'
   *                                                   | TRNS    | TRNS    |          | TRNS    | TRNS    |
   *                                         ,---------|         |         |          |         |         +---------.
   *                                         | TRNS    |         |         |          |         |         | TRNS    |
   *                                         `-----------------------------'          `-----------------------------'                                      */
	[_NUM] = LAYOUT_4key_2u_inner(
      KC_TRNS,  KC_EXLM,   KC_AT,    KC_HASH,   KC_DLR,   KC_PERC, KC_LBRC,             KC_RBRC,  KC_CIRC,  KC_AMPR,  KC_PAST,  KC_PSLS,  KC_PMNS,  KC_TRNS, 
      KC_TRNS,  KC_NO,     KC_NO,    KC_PGUP,   KC_NO,    KC_NO,   TT(_ADJUST),         KC_TRNS,  KC_PPLS,  KC_P7,    KC_P8,    KC_P9,    KC_PPLS,  KC_NO, 
      KC_TRNS,  KC_NO,     KC_HOME,  KC_PGDOWN, KC_END,   KC_NO,   KC_PSCR,             KC_BSLS,  KC_PEQL,  KC_P4,    KC_P5,    KC_P6,    KC_TRNS,  KC_QUOT,
      KC_TRNS,  KC_NO,     KC_NO,    KC_NO,     KC_NO,    KC_NO,   KC_TRNS,             KC_NO,    KC_P0,    KC_P1,    KC_P2,    KC_P3,    KC_TRNS,  KC_TRNS, 
      KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS, KC_TRNS,             KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_P0,    KC_PDOT,  KC_TRNS,  TO(_BASE)
      ),


   /* Keymap 3: VIM layer (Cursor and Visual commands)
   * ,-----------------------------------------------------------.                              ,-----------------------------------------------------------.
   * | TRNS    |         |         |         |         |         |---------.          ,---------| Rewind  |         |         | Fastfwd | sol     |         |
   * |---------+---------+---------+---------+---------+---------|         |          | Calc    |---------+---------+---------+---------+---------+---------|
   * | TRNS    |         |Ctrl+RT  |         |         |         |---------|          |---------| TD_y/y  |         | Ins     |         | Ctrl+V  |         |
   * |---------+---------+---------+---------+---------+---------|         |          | Mute    |---------+---------+---------+---------+---------+---------|
   * |         |         |         | TD_d/d  |         |         |---------|          |---------| Left    | Down    | Up      | Right   |         |         |
   * |---------+---------+---------+---------+---------+---------| PrtScr  |          | Play    |---------+---------+---------+---------+---------|---------|
   * | TRNS    |         | Del     |         |         |Ctrl+LFT |---------'          `---------| Prev Tra| Vol -   | Vol +   | Next Tra| Ctrl+F  | NAV(SFT)|
   * |---------+---------+---------+-----------------------------'                              `-----------------------------+---------+---------+---------|
   * | LM4+CTL | TRNS    | TRNS    |  | TRNS    |      ,-------------------.          ,-------------------.      |         |  | TRNS    | TRNS    | TO(BASE)|
   * `-----------------------------'  `---------'      |         | TRNS    |          | TRNS    |         |      `---------'  `-----------------------------'
   *                                                   | TRNS    |_________|          |_________| TRNS    |        
   *                                         ,---------|         | TRNS    |          | TRNS    |         +---------.
   *                                         | TRNS    |         |         |          |         |         | TRNS    |
   *                                         `-----------------------------'          `-----------------------------'                                      */
	[_VIM] = LAYOUT_4key_2u_inner(
      KC_TRNS,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,               KC_CALC,  KC_MRWD,  KC_NO,    KC_NO,    KC_MFFD,   KC_NO,   KC_NO, 
      KC_TRNS,  KC_NO,    CTLRT,    KC_NO,    KC_NO,    KC_NO,    KC_NO,               KC_MUTE,  TD(VIM_y),KC_NO,    KC_INS,   KC_NO,     CTLV,    KC_NO, 
      KC_NO,    KC_NO,    KC_NO,    TD(VIM_d),KC_NO,    KC_NO,    KC_PSCR,             KC_MPLY,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,   KC_NO,   KC_NO, 
      KC_TRNS,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    CTLLFT,   KC_TRNS,             KC_TRNS,  KC_MPRV,  KC_VOLD,  KC_VOLU,  KC_MNXT,   CTLF,    NAVM_SFT, 
      NAVM_CTL, KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,             KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_NO,    KC_TRNS,   KC_TRNS, TO(_BASE)
      ),


   /* Keymap 4: NAVIGATION/RAISED vim layer 
   * ,-----------------------------------------------------------.                               ,-----------------------------------------------------------.
   * | TRNS    |         |         | End     |         |         |---------.          ,---------|         |         |         |         |         |         |
   * |---------+---------+---------+---------+---------+---------|         |          |         |---------+---------+---------+---------+---------+---------|
   * | TRNS    |         |         |         | Ctrl+Y  |         |---------|          |---------|         | PgUp    |         |         |         |         |
   * |---------+---------+---------+---------+---------+---------|         |          |         |---------+---------+---------+---------+---------+---------|
   * | TRNS    |         |         | PgDn    |         |         |---------|          |---------| TRNS    | TRNS    | TRNS    | TRNS    |         |         |
   * |---------+---------+---------+---------+---------+---------|         |          |         |---------+---------+---------+---------+---------|---------|
   * | TRNS    |         |         |         |         |         |---------'          `---------|         |         |         |         |         | TRNS    |
   * |---------+---------+---------+-----------------------------'                              `-----------------------------+---------+---------+---------|
   * | TRNS    | TRNS    | TRNS    |  | TRNS    |      ,-------------------.          ,-------------------.      |         |  |         |         | TO(BASE)|
   * `-----------------------------'  `---------'      |         | TRNS    |          | TRNS    |         |      `---------'  `-----------------------------'
   *                                                   | TRNS    |_________|          |_________| TRNS    |
   *                                         ,---------|         | TRNS    |          | TRNS    |         +---------.
   *                                         | TRNS    |         |         |          |         |         | TRNS    |
   *                                         `-----------------------------'          `-----------------------------'                                      */

  [_NAV] = LAYOUT_4key_2u_inner(
      KC_TRNS,  KC_NO,    KC_NO,    KC_END,   KC_NO,    KC_NO,    KC_NO,               KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO, 
      KC_TRNS,  KC_NO,    KC_NO,    KC_NO,    CTLY,     KC_NO,    KC_NO,               KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO, 
      KC_TRNS,  KC_NO,    KC_NO,    KC_PGDN,  KC_NO,    KC_NO,    KC_TRNS,             KC_NO,    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_NO,    KC_NO, 
      KC_TRNS,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_TRNS,             KC_TRNS,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_TRNS, 
      KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,             KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_NO,    KC_NO,    KC_NO,    TO(_BASE)
      ),


   /* Keymap 5: SYMBOL Layer
   * ,-----------------------------------------------------------.                              ,-----------------------------------------------------------.
   * |_BASE+ESC| !       | @       | #       | $       | %       |---------.          ,---------|         |         |         |         |         |         |
   * |---------+---------+---------+---------+---------+---------| [       |          |         |---------+---------+---------+---------+---------+---------|
   * |         | ^       | &       | *       | -       | _       |---------|          |---------|         |         |         |         |         |         |
   * |---------+---------+---------+---------+---------+---------| '       |          |         |---------+---------+---------+---------+---------+---------|
   * | ~       | "       | <       | {       | (       | `       |---------|          |---------|         |         |         |         |         |         |
   * |---------+---------+---------+---------+---------+---------| :       |          |         |---------+---------+---------+---------+---------|---------|
   * |         | .       | +       | =       | /       | \       |---------'          `---------|         |         |         |         |         |         |
   * |---------+---------+---------+-----------------------------'                              `-----------------------------+---------+---------+---------|
   * |         |         |         |  |         |      ,-------------------.          ,-------------------.      |         |  |         |         | TO(0)   |
   * `-----------------------------'  `---------'      |         | TRNS    |          |         |         |      `---------'  `-----------------------------'
   *                                                   |         |_________|          |_________|         |
   *                                         ,---------|         | TRNS    |          |         |         +---------.
   *                                         |         |         |         |          |         |         |         |
   *                                         `-----------------------------'          `-----------------------------'                                      */
  [_SYM] = LAYOUT_4key_2u_inner(
      BASE_ESC, KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,  KC_LBRC,             KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO, 
      KC_NO,    KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_MINS,  KC_UNDS,  KC_QUOT,             KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO, 
      KC_TILD,  KC_DQUO,  KC_LT,    KC_LCBR,  KC_LPRN,  KC_DQUO,  KC_COLN,             KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO, 
      KC_NO,    KC_PDOT,  KC_PLUS,  KC_EQL,   KC_PSLS,  KC_BSLS,  KC_TRNS,             KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO, 
      KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_TRNS,             KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    TO(_BASE)
      ),


   /* Keymap 6: ADJUST Layer
   * ,-----------------------------------------------------------.                              ,-----------------------------------------------------------.
   * | TRNS    |         |         |         |         |         |---------.          ,---------|         | NumLock |         |         |         |         |
   * |---------+---------+---------+---------+---------+---------|         |          | EEP_RST |---------+---------+---------+---------+---------+---------|
   * |         |         |         |         |         |         |---------|          |---------|         |         |         |         |         |         |
   * |---------+---------+---------+---------+---------+---------|         |          |         |---------+---------+---------+---------+---------+---------|
   * |         |         |         |         |         |         |---------|          |---------|         |         |         |         |         |         |
   * |---------+---------+---------+---------+---------+---------|         |          |         |---------+---------+---------+---------+---------|---------|
   * |         |         |         |         |         |         |---------'          `---------|         |         |         |         |         |         |
   * |---------+---------+---------+-----------------------------'                              `-----------------------------+---------+---------+---------|
   * |         |         |         |  |         |      ,-------------------.          ,-------------------.      |         |  |         |         | TO(0)   |
   * `-----------------------------'  `---------'      |         |         |          |         |         |      `---------'  `-----------------------------'
   *                                                   |         |_________|          |_________|         |
   *                                         ,---------|         | CS(F14) |          |         |         +---------.
   *                                         |         |         |         |          |         |         |         |
   *                                         `-----------------------------'          `-----------------------------'                                      */
  [_ADJUST] = LAYOUT_4key_2u_inner(
      KC_TRNS,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,               EEP_RST,  KC_NO,    KC_NUM,   KC_NO,    KC_NO,    KC_NO,    KC_NO, 
      KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,               KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO, 
      KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,               KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO, 
      KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,               KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO, 
      KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    CS_F14,              KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    TO(_BASE)
      )
};

// ************** CUSTOM KEY HANDLING ************* //
// ************************************************ //
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool pressed = record->event.pressed;
    switch (keycode) {
      case BASE_ESC:
        if (pressed) {
          // Do something when pressed
          register_code(KC_ESC);
          layer_move(_BASE);
        } else {
          // Do something else when released
          unregister_code(KC_ESC);
        }
        return false; // Skip all further processing of this key
      case KC_dd_CUT_LINE:
        if (pressed) {
          tap_code(KC_HOME);
          tap_code(KC_HOME);
          register_code(KC_LSFT);
          tap_code(KC_END);
          unregister_code(KC_LSFT);
          register_code(KC_LCTL);
          register_code(KC_X); 
        } else {
          unregister_code(KC_X);
          unregister_code(KC_LCTL);
        }
        return false;
      case KC_yy_COPY_LINE:
        if (pressed) {
          tap_code(KC_HOME);
          tap_code(KC_HOME);
          register_code(KC_LSFT);
          tap_code(KC_END);
          unregister_code(KC_LSFT);
          register_code(KC_LCTL);
          tap_code(KC_C);
          register_code(KC_LEFT);
        } else {
          unregister_code(KC_LEFT);
          unregister_code(KC_LCTL);
        }
        return false;
      case KC_SOL:
        if (pressed) {
          tap_code(KC_HOME);
          register_code(KC_HOME);
        } else {
          unregister_code(KC_HOME);
        }
        return false;
      default:
        return true;
    }
} 

// ************ DYNAMIC TAPPING TERMS ************* //
// ************************************************ //
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case FNT_PSCR:
            return TAPPING_TERM + 40;
        default:
            return TAPPING_TERM;
    }
}

// *********** KEYBOARD PRE/POST INIT ************* //
// ************************************************ //
void keyboard_pre_init_user(void) {
  // rgblight_disable_noeeprom(); // ideally disables RBG on startup, prevents LED flash on plugin; needs to be moved to POST
}

// Numlock on boot <https://github.com/qmk/qmk_firmware/issues/10890#issuecomment-927222187>
void numlock_on(void) {
  led_t led_state = host_keyboard_led_state();
  bool isNumlock = led_state.num_lock;
  if (!isNumlock) {
      register_code(KC_NUMLOCK);
      unregister_code(KC_NUMLOCK);
  }
}
void keyboard_post_init_user() {
  numlock_on();
  rgblight_disable_noeeprom();
}

// ************* LAYER RGB INDICATORS ************* //
// ************************************************ //
#ifdef RGB_MATRIX_ENABLE
/* Leader Key per-key LED  */
/*
void rgb_matrix_indicators_user(void) { 
    if (isLeader) {
        rgb_matrix_set_color_hsv(14, 999, 999, 999, 1); // CONFIG
        rgb_matrix_set_color_hsv(30, 999, 999, 999, 1); // CONFIG
    } else {
        rgb_matrix_set_color_hsv(14, 999, 999, 999, led_dim_ratio); // CONFIG
    }  
}
*/
#endif // !RGB_MATRIX_ENABLE

#ifdef RGBLIGHT_ENABLE
/* WIP Code for layer state LED underglow */
/*
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _BASE:
        rgblight_sethsv_noeeprom(HSV_GOLD);
        break;
    case _ADJUST:
        rgblight_sethsv_noeeprom(HSV_RED);
        break;
    default: //  for any other layers, or the default layer
        rgblight_sethsv_noeeprom(HSV_OFF);
        break;
    }
  return state;
}
*/
#endif // !RGBLIGHT_ENABLE

// ************** LEADER KEY FUNCTIONS ************ //
// ************************************************ //
#ifdef LEADER_ENABLE
// ***** Cursor Wrap Functions ***** //
/* (▌) PARENTHESIS */
void ldr_send_parenthesis_cursor_wrap(void) {
    SEND_STRING("()" SS_TAP(X_LEFT));
}
/* [▌] SQUARE BRACKET */
void ldr_send_bracket_cursor_wrap(void) {
    SEND_STRING("[]" SS_TAP(X_LEFT));
}
/* '▌' SINGLE QUOTE */
void ldr_send_quotesingle_cursor_wrap(void) {
    SEND_STRING("''" SS_TAP(X_LEFT));
}
/* "▌" DOUBLE QUOTE */
void ldr_send_quotedouble_cursor_wrap(void) {
    SEND_STRING("\"\"" SS_TAP(X_LEFT));
}
/* {▌} CURLY BRACE */
void ldr_send_curly_brace_cursor_wrap(void) {
    SEND_STRING("{}" SS_TAP(X_LEFT));
}
/* [▌] SQUARE BRACKET */
void ldr_send_squarebracket_cursor_wrap(void) {
    SEND_STRING("[]" SS_TAP(X_LEFT));
}
/* <▌> ANGLE BRACKET */
void ldr_send_angle_bracket_cursor_wrap(void) {
    SEND_STRING("<>" SS_TAP(X_LEFT));
}
/* `▌` GRAVE */
void ldr_send_grave_cursor_wrap(void) {
    SEND_STRING("``" SS_TAP(X_LEFT));
}
/* /▌/ FORWARD SLASH */
void ldr_send_forward_slash_cursor_wrap(void) {
    SEND_STRING("//" SS_TAP(X_LEFT));
}
/* *▌* ASTERISK */
void ldr_send_asterisk_cursor_wrap(void) {
    SEND_STRING("**" SS_TAP(X_LEFT));
}
/* @▌@ AT */
void ldr_send_at_cursor_wrap(void) {
    SEND_STRING("@@" SS_TAP(X_LEFT));
}
/* %▌% PERCENT */
void ldr_send_percent_cursor_wrap(void) {
    SEND_STRING("%%" SS_TAP(X_LEFT));
}

LEADER_EXTERNS(); // Keep this line above matrix_scan_user

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    /* Capslock */
    // Double tap LDR for CAPS
    SEQ_ONE_KEY(KC_LEAD) {
      tap_code(KC_CAPS);
      #ifdef RGBLIGHT_ENABLE
      if(IS_HOST_LED_ON(USB_LED_CAPS_LOCK)) { // Used to counter a CAPS and LED desync
        rgblight_enable_noeeprom();
      } else {
        rgblight_disable_noeeprom();
      }
      #endif // !RGBLIGHT_ENABLE
    }
    
    // ***** Cursor Wrap Macros by Symbol ***** //
    /* (▌) PARENTHESIS */
    SEQ_TWO_KEYS(KC_LSFT, KC_9) {
      ldr_send_parenthesis_cursor_wrap();
    }
    /* [▌] SQUARE BRACKET */
    SEQ_ONE_KEY(KC_LBRC) {
      ldr_send_bracket_cursor_wrap();
    }
    /* '▌' SINGLE QUOTE */
    SEQ_ONE_KEY(KC_QUOT) {
      ldr_send_quotesingle_cursor_wrap();
    }
    /* "▌" DOUBLE QUOTE */
    SEQ_TWO_KEYS(KC_LSFT, KC_QUOT) {
      ldr_send_quotedouble_cursor_wrap();
    }
    
    // ***** Cursor Wrap Macros by Comfort ***** //
    // NOTE: Use the Symbol Layer as a Reference
    
    /* R4; Number Row*/
    /* @▌@ AT */
    SEQ_ONE_KEY(KC_2) {
      ldr_send_at_cursor_wrap();
    }
    /* %▌% PERCENT */
    SEQ_ONE_KEY(KC_5) {
      ldr_send_percent_cursor_wrap();
    }
    
    /* R3; Alpha */
    /* *▌* ASTERISK */
    SEQ_ONE_KEY(KC_E) {
      ldr_send_asterisk_cursor_wrap();
    }
    
    /* R2; Home Row */
    /* '▌' SINGLE QUOTE */
    SEQ_ONE_KEY(KC_F4) {
      ldr_send_quotesingle_cursor_wrap();
    }
    /* `▌` GRAVE */
    SEQ_ONE_KEY(KC_G) {
      ldr_send_grave_cursor_wrap();
    }
    /* (▌) PARENTHESIS */
    SEQ_ONE_KEY(KC_F) {
      ldr_send_parenthesis_cursor_wrap();
    }
    /* {▌} CURLY BRACE */
    SEQ_ONE_KEY(KC_D) {
      ldr_send_curly_brace_cursor_wrap();
    }
    /* <▌> ANGLE BRACKET */
    SEQ_ONE_KEY(KC_S) {
      ldr_send_angle_bracket_cursor_wrap();
    }
    /* "▌" DOUBLE QUOTE */
    SEQ_ONE_KEY(KC_A) {
      ldr_send_quotedouble_cursor_wrap();
    }
    
    /* R1; Alpha */
    /* /▌/ FORWARD SLASH */
    SEQ_ONE_KEY(KC_V) {
      ldr_send_forward_slash_cursor_wrap();
    }
    
    /* R0; Mod */
    
    leader_end();
  }
}

void leader_start(void) {
    isLeader = true;
}

void leader_end(void) {
    isLeader = false;
}
#endif // !LEADER_ENABLE


// ************** TAP DANCE FUNCTIONS ************ //
// ************************************************ //
td_state_t cur_dance(qk_tap_dance_state_t *state) {
  if (state->count == 1) return TD_SINGLE_TAP;
  else if (state->count == 2) return TD_DOUBLE_TAP;
  else return TD_UNKNOWN;
}

td_tap_t dtap_state = {
  .is_press_action = true,
  .state = TD_NONE
};

void d_finished(qk_tap_dance_state_t *state, void *user_data) {
  dtap_state.state = cur_dance(state);
  switch (dtap_state.state) {
    case TD_SINGLE_TAP:
      register_code16(CTLX);
      break;
    case TD_DOUBLE_TAP:
      register_custom_keycode(KC_dd_CUT_LINE, 12, 5);
      break;
    default: break;
  }
}

void d_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (dtap_state.state) {
    case TD_SINGLE_TAP:
      unregister_code16(CTLX); 
      break;
    case TD_DOUBLE_TAP:
      unregister_custom_keycode(KC_dd_CUT_LINE, 12, 5);
      break;
    default: break;
  }
  dtap_state.state = TD_NONE;
}

td_tap_t ytap_state = {
  .is_press_action = true,
  .state = TD_NONE
};

void y_finished(qk_tap_dance_state_t *state, void *user_data) {
  dtap_state.state = cur_dance(state);
  switch (dtap_state.state) {
    case TD_SINGLE_TAP:
      register_code16(CTLC);
      break;
    case TD_DOUBLE_TAP:
      register_custom_keycode(KC_yy_COPY_LINE, 12 ,5);
      break;
    default: break;
  }
}

void y_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (dtap_state.state) {
    case TD_SINGLE_TAP:
      unregister_code16(CTLC); 
      break;
    case TD_DOUBLE_TAP: 
      unregister_custom_keycode(KC_yy_COPY_LINE, 12, 5);
      break;
    default: break;
  }
  dtap_state.state = TD_NONE;
}

td_tap_t quotetap_state = {
  .is_press_action = true,
  .state = TD_NONE
};

void quote_capsword_finished(qk_tap_dance_state_t *state, void *user_data) {
  quotetap_state.state = cur_dance(state);
  switch (quotetap_state.state) {
    case TD_SINGLE_TAP:
      register_code(KC_QUOTE);
      break;
    case TD_DOUBLE_TAP:
      // caps_word_on();
      break;
    default: break;
  }
}

void quote_capsword_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (quotetap_state.state) {
    case TD_SINGLE_TAP:
      unregister_code(KC_QUOTE);
      break;
    case TD_DOUBLE_TAP:
      break;
    default: break;
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [VIM_d] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, d_finished, d_reset, 175),
    [VIM_y] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, y_finished, y_reset, 175),
    [QUOT_CW] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, quote_capsword_finished, quote_capsword_reset, 175)
};

