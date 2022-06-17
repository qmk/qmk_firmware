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
  OFF_ESC,
  /* VIM Cursor Movement */
  KC_SOL, 
  /* VIM Visual/Cut and Paste */
  KC_yy_COPY_LINE,
  KC_dd_CUT_LINE,

  VIM_A,
  VIM_B,
  VIM_C,
  VIM_CI,
  VIM_D,
  VIM_DI,
  VIM_E,
  VIM_H,
  VIM_I,
  VIM_J,
  VIM_K,
  VIM_L,
  VIM_O,
  VIM_P,
  VIM_R, // IMPLEMENT!!
  VIM_S,
  VIM_U,
  VIM_V,
  VIM_VI,
  VIM_W,
  VIM_X,
  VIM_Y,
  VIM_YI,
};

// **  VIM Definitions ** //
#define PRESS(keycode) register_code16(keycode)
#define RELEASE(keycode) unregister_code16(keycode)

uint16_t VIM_QUEUE = KC_NO;

void VIM_LEFT(void); // repeatable
void VIM_DOWN(void); // repeatable
void VIM_UP(void); // repeatable
void VIM_RIGHT(void); // repeatable

void VIM_APPEND(void);
void VIM_APPEND_LINE(void);
void VIM_BACK(void); // repeat, keep
void VIM_CHANGE_BACK(void);
void VIM_CHANGE_DOWN(void);
void VIM_CHANGE_END(void);
void VIM_CHANGE_INNER_WORD(void);
void VIM_CHANGE_LEFT(void);
void VIM_CHANGE_TO_EOL(void);
void VIM_CHANGE_RIGHT(void);
void VIM_CHANGE_UP(void);
void VIM_CHANGE_WHOLE_LINE(void);
void VIM_CHANGE_WORD(void);
void VIM_CUT(void); // repeatable 
void VIM_DELETE_BACK(void);
void VIM_DELETE_DOWN(void);
void VIM_DELETE_END(void);
void VIM_DELETE_INNER_WORD(void);
void VIM_DELETE_LEFT(void);
void VIM_DELETE_TO_EOL(void);
void VIM_DELETE_RIGHT(void);
void VIM_DELETE_UP(void);
void VIM_DELETE_WHOLE_LINE(void);
void VIM_DELETE_WORD(void);
void VIM_END(void); // repeatable
void VIM_JOIN(void);
void VIM_OPEN(void);
void VIM_OPEN_ABOVE(void);
void VIM_PUT_AFTER(void); 
void VIM_PUT_BEFORE(void); // repeatable
void VIM_SUBSTITUTE(void);
void VIM_UNDO(void); // repeatable
void VIM_VISUAL_BACK(void);
void VIM_VISUAL_DOWN(void);
void VIM_VISUAL_END(void);
void VIM_VISUAL_INNER_WORD(void);
void VIM_VISUAL_LEFT(void);
void VIM_VISUAL_RIGHT(void);
void VIM_VISUAL_UP(void);
void VIM_VISUAL_WORD(void);
void VIM_WORD(void);
void VIM_YANK(void);
void VIM_YANK_BACK(void);
void VIM_YANK_DOWN(void);
void VIM_YANK_END(void);
void VIM_YANK_INNER_WORD(void);
void VIM_YANK_LEFT(void);
void VIM_YANK_TO_EOL(void);
void VIM_YANK_RIGHT(void);
void VIM_YANK_UP(void);
void VIM_YANK_WHOLE_LINE(void);
void VIM_YANK_WORD(void);

/**
 * Sets the `VIM_QUEUE` variable to the incoming keycode.
 * Pass `KC_NO` to cancel the operation.
 * @param keycode
 */
void VIM_LEADER(uint16_t keycode) {
  VIM_QUEUE = keycode;
  switch(keycode) {
    case VIM_C: print("\e[32mc\e[0m"); break;
    case VIM_CI: print("\e[32mci\e[0m"); break;
    case VIM_D: print("\e[32md\e[0m"); break;
    case VIM_DI: print("\e[32mdi\e[0m"); break;
    case VIM_V: print("\e[32mv\e[0m"); break;
    case VIM_VI: print("\e[32mvi\e[0m"); break;
    case VIM_Y: print("\e[32my\e[0m"); break;
    case VIM_YI: print("\e[32myi\e[0m"); break;
    case KC_NO: print("❎"); break;
  }
}

// ** Press KC Helper Functions ** //
void TAP(uint16_t keycode) {
  PRESS(keycode);
  RELEASE(keycode);
}

void CMD(uint16_t keycode) {
  PRESS(KC_LGUI);
    TAP(keycode);
  RELEASE(KC_LGUI);
}

void CTRL(uint16_t keycode) {
  PRESS(KC_LCTRL);
    TAP(keycode);
  RELEASE(KC_LCTRL);
}

void SHIFT(uint16_t keycode) {
  PRESS(KC_LSHIFT);
    TAP(keycode);
  RELEASE(KC_LSHIFT);
}

void ALT(uint16_t keycode) {
  PRESS(KC_LALT);
    TAP(keycode);
  RELEASE(KC_LALT);
}

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

// NOTE: NEEDS TO BE MOVED TO USERSPACE
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

/****
 *.##....##.########.##....##.##.....##....###....########.
 *.##...##..##........##..##..###...###...##.##...##.....##
 *.##..##...##.........####...####.####..##...##..##.....##
 *.#####....######......##....##.###.##.##.....##.########.
 *.##..##...##..........##....##.....##.#########.##.......
 *.##...##..##..........##....##.....##.##.....##.##.......
 *.##....##.########....##....##.....##.##.....##.##.......
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
   /* Keymap 0: BASE layer
   * ,-----------------------------------------------------------.                              ,-----------------------------------------------------------.
   * | ESC     | !1      | @2      | #3      | $4      | %5      |---------.          ,---------| ^6      | &7      | *8      | (9      | )0      | _-      |
   * |---------+---------+---------+---------+---------+---------| {[      |          | }]      |---------+---------+---------+---------+---------+---------|
   * | Tab     | Q       | W       | E       | R       | T       |---------|          |---------| Y       | U       | I       | O       | P       | LEADER  |
   * |---------+---------+---------+---------+---------+---------| F4      |          | +=      |---------+---------+---------+---------+---------+---------|
   * | ~`      | A       | S       | D       | F       | G       |---------|          |---------| H       | J       | K       | L       | NUM(:;) | "'      | // SYM LAYER ACCESS ("')
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
      OFF_ESC,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_LBRC,             KC_RBRC,  KC_6,     KC_7,     KC_8,      KC_9,     KC_0,    KC_MINS, 
      KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_F4,               KC_EQL,   KC_Y,     KC_U,     KC_I,      KC_O,     KC_P,    KC_LEAD, 
      KC_GRV,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     FNT_PSCR,            FNT_BSLS, KC_H,     KC_J,     KC_K,      KC_L,     NUMT_SCLN,KC_QUOT,
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
      _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F11,              KC_F12,   KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,    _______, 
      _______,  _______,  _______,  _______,  _______,  _______,  _______,             _______,  _______,  _______,  _______,  _______,  _______,   _______, 
      _______,  _______,  _______,  _______,  _______,  _______,  _______,             _______,  _______,  _______,  _______,  _______,  _______,   _______, 
      _______,  _______,  _______,  _______,  _______,  _______,  _______,             _______,  _______,  _______,  _______,  _______,  _______,   _______, 
      _______,  _______,  _______,  _______,  _______,  _______,  _______,             _______,  _______,  _______,  _______,  _______,  _______,   TO(_BASE)
      ),
      

   /* Keymap 2: NUMPAD Layer // LEFT HAND MOUSE?
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
      _______,  KC_EXLM,   KC_AT,    KC_HASH,   KC_DLR,   KC_PERC, KC_LBRC,             KC_RBRC,  KC_CIRC,  KC_AMPR,  KC_PAST,  KC_PSLS,  KC_PMNS,  _______, 
      _______,  KC_NO,     KC_NO,    KC_PGUP,   KC_NO,    KC_NO,   TT(_ADJUST),         _______,  KC_PPLS,  KC_P7,    KC_P8,    KC_P9,    KC_PPLS,  KC_NO, 
      _______,  KC_NO,     KC_HOME,  KC_PGDOWN, KC_END,   KC_NO,   KC_PSCR,             KC_BSLS,  KC_PEQL,  KC_P4,    KC_P5,    KC_P6,    _______,  KC_QUOT,
      _______,  KC_NO,     KC_NO,    KC_NO,     KC_NO,    KC_NO,   _______,             KC_NO,    KC_P0,    KC_P1,    KC_P2,    KC_P3,    _______,  _______, 
      _______,  _______,   _______,  _______,   _______,  _______, _______,             _______,  _______,  _______,  KC_P0,    KC_PDOT,  _______,  TO(_BASE)
      ),


   /* Keymap 3: VIM layer (NORMAL mode)
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
      _______,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,               KC_CALC,  KC_MRWD,  KC_NO,    KC_NO,    KC_MFFD,   KC_NO,   KC_NO, 
      _______,  KC_NO,    VIM_W,    VIM_E,    KC_NO,    KC_NO,    KC_NO,               KC_MUTE,  VIM_Y,    VIM_U,    VIM_I,    VIM_O,     VIM_P,    KC_NO, 
      KC_NO,    VIM_A,    VIM_S,    VIM_D,    KC_NO,    KC_NO,    KC_PSCR,             KC_MPLY,  VIM_H,    VIM_J,    VIM_K,    VIM_L,   KC_NO,   KC_NO, 
      _______,  KC_NO,    VIM_X,    VIM_C,    VIM_V,    VIM_B,    _______,             _______,  KC_MPRV,  KC_VOLD,  KC_VOLU,  KC_MNXT,   CTLF,    NAVM_SFT, 
      NAVM_CTL, _______,  _______,  _______,  _______,  _______,  _______,             _______,  _______,  _______,  KC_NO,    _______,   _______, TO(_BASE)
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
      _______,  KC_NO,    KC_NO,    KC_END,   KC_NO,    KC_NO,    KC_NO,               KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO, 
      _______,  KC_NO,    KC_NO,    KC_NO,    CTLY,     KC_NO,    KC_NO,               KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO, 
      _______,  KC_NO,    KC_NO,    KC_PGDN,  KC_NO,    KC_NO,    _______,             KC_NO,    _______,  _______,  _______,  _______,  KC_NO,    KC_NO, 
      _______,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    _______,             _______,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    _______, 
      _______,  _______,  _______,  _______,  _______,  _______,  _______,             _______,  _______,  _______,  KC_NO,    KC_NO,    KC_NO,    TO(_BASE)
      ),


   /* Keymap 5: SYMBOL Layer
   * ,-----------------------------------------------------------.                              ,-----------------------------------------------------------.
   * | TRNS    | !       | @       | #       | $       | %       |---------.          ,---------|         |         |         |         |         |         |
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
      _______,  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,  KC_LBRC,             KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO, 
      KC_NO,    KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_MINS,  KC_UNDS,  KC_QUOT,             KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO, 
      KC_TILD,  KC_DQUO,  KC_LT,    KC_LCBR,  KC_LPRN,  KC_DQUO,  KC_COLN,             KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO, 
      KC_NO,    KC_PDOT,  KC_PLUS,  KC_EQL,   KC_PSLS,  KC_BSLS,  _______,             KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO, 
      KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    _______,             KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    TO(_BASE)
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
      _______,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,               EEP_RST,  KC_NO,    KC_NUM,   KC_NO,    KC_NO,    KC_NO,    KC_NO, 
      KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,               KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO, 
      KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,               KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO, 
      KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,               KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO, 
      KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    CS_F14,              KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    TO(_BASE)
      )
};

/****
 *..######..##.....##..######..########..#######..##.....##....##....##.########.##....##..######...#######..########..########..######.
 *.##....##.##.....##.##....##....##....##.....##.###...###....##...##..##........##..##..##....##.##.....##.##.....##.##.......##....##
 *.##.......##.....##.##..........##....##.....##.####.####....##..##...##.........####...##.......##.....##.##.....##.##.......##......
 *.##.......##.....##..######.....##....##.....##.##.###.##....#####....######......##....##.......##.....##.##.....##.######....######.
 *.##.......##.....##.......##....##....##.....##.##.....##....##..##...##..........##....##.......##.....##.##.....##.##.............##
 *.##....##.##.....##.##....##....##....##.....##.##.....##....##...##..##..........##....##....##.##.....##.##.....##.##.......##....##
 *..######...#######...######.....##.....#######..##.....##....##....##.########....##.....######...#######..########..########..######.
 */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  bool pressed = record->event.pressed;
  bool SHIFTED = (keyboard_report->mods & MOD_BIT(KC_LSFT)) | (keyboard_report->mods & MOD_BIT(KC_RSFT));
  //bool CTRLED = (keyboard_report->mods & MOD_BIT(KC_LCTL)) | (keyboard_report->mods & MOD_BIT(KC_RCTL));

  switch (keycode) {

    case OFF_ESC:
      if (pressed) {
        switch(VIM_QUEUE){
          case KC_NO:
            register_code(KC_ESC);
            caps_word_off();
            layer_move(_BASE);
            if(IS_HOST_LED_ON(USB_LED_CAPS_LOCK)) {
              TAP(KC_CAPS); // Turn off Capslock
            }
          break;
          case VIM_R: VIM_LEADER(KC_NO); break;
        }
        
      } else {
        // Do something when released; typically unregister code to keep the KC held while pressed
        unregister_code(KC_ESC);
      }
      return false;

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

    /* VIM */
    case VIM_A:
      if (pressed) { SHIFTED ? VIM_APPEND_LINE() : VIM_APPEND(); }
      return false;

    case VIM_B:
      if (pressed) {
        switch(VIM_QUEUE) {
          case KC_NO: VIM_BACK(); break;
          case VIM_C: VIM_CHANGE_BACK(); break;
          case VIM_D: VIM_DELETE_BACK(); break;
          case VIM_V: VIM_VISUAL_BACK(); break;
        }
      }
      return false;

    case VIM_C:
      if (pressed) {
        switch(VIM_QUEUE) {
          case KC_NO: SHIFTED ? VIM_CHANGE_TO_EOL() : VIM_LEADER(VIM_C); break;
          case VIM_C: VIM_CHANGE_WHOLE_LINE(); break;
        }
      }
      return false;

    case VIM_D:
      if (pressed) {
        switch(VIM_QUEUE) {
          case KC_NO: SHIFTED ? VIM_DELETE_TO_EOL() : VIM_LEADER(VIM_D); break;
          case VIM_D: VIM_DELETE_WHOLE_LINE(); break;
        }
      }
      return false;

    case VIM_E:
      if (pressed) {
        switch (VIM_QUEUE) {
          case KC_NO: VIM_END(); break;
          case VIM_C: VIM_CHANGE_END(); break;
          case VIM_D: VIM_DELETE_END(); break;
          case VIM_V: VIM_VISUAL_END(); break;
        }
      }
      return false;

    case VIM_H:
      if (pressed) {
        switch (VIM_QUEUE) {
          case KC_NO: PRESS(KC_LEFT); break;
          case VIM_C: VIM_CHANGE_LEFT(); break;
          case VIM_D: VIM_DELETE_LEFT(); break;
          case VIM_V: VIM_VISUAL_LEFT(); break;
        }
      } else {
        RELEASE(KC_LEFT);
      }
      return false;

    case VIM_I:
      if (pressed) {
        switch (VIM_QUEUE) {
          case KC_NO: layer_move(_BASE); break;
          case VIM_C: VIM_LEADER(VIM_CI); break;
          case VIM_D: VIM_LEADER(VIM_DI); break;
          case VIM_V: VIM_LEADER(VIM_VI); break;
        }
      }
      return false;

    case VIM_J:
      if (pressed) {
        switch (VIM_QUEUE) {
          case KC_NO: SHIFTED ? VIM_JOIN() : PRESS(KC_DOWN); break;
          case VIM_C: VIM_CHANGE_DOWN(); break;
          case VIM_D: VIM_DELETE_DOWN(); break;
          case VIM_V: VIM_VISUAL_DOWN(); break;
        }
      } else {
        RELEASE(KC_DOWN);
      }
      return false;

    case VIM_K:
      if (pressed) {
        switch (VIM_QUEUE) {
          case KC_NO: PRESS(KC_UP); break;
          case VIM_C: VIM_CHANGE_UP(); break;
          case VIM_D: VIM_DELETE_UP(); break;
          case VIM_V: VIM_VISUAL_UP(); break;
        }
      } else {
        RELEASE(KC_UP);
      }
      return false;

    case VIM_L:
      if (pressed) {
        switch (VIM_QUEUE) {
          case KC_NO: PRESS(KC_RIGHT); break;
          case VIM_C: VIM_CHANGE_RIGHT(); break;
          case VIM_D: VIM_DELETE_RIGHT(); break;
          case VIM_V: VIM_VISUAL_RIGHT(); break;
        }
      } else {
        RELEASE(KC_RIGHT);
      }
      return false;

    case VIM_O:
      if (pressed) { SHIFTED ? VIM_OPEN_ABOVE() : VIM_OPEN(); }
      return false;

    case VIM_P:
      if (pressed) { SHIFTED ? VIM_PUT_BEFORE() : VIM_PUT_AFTER(); }
      return false;

    case VIM_S:
      if (pressed) { SHIFTED ? VIM_CHANGE_WHOLE_LINE() : VIM_SUBSTITUTE(); }
      return false;

    case VIM_U:
      if (pressed) { VIM_UNDO(); }
      return false;

    case VIM_V:
      if (pressed) { VIM_LEADER(VIM_V); }
      return false;

    case VIM_W:
      if (pressed) {
        switch (VIM_QUEUE) {
          case KC_NO: VIM_WORD(); break;
          case VIM_C: VIM_CHANGE_WORD(); break;
          case VIM_CI: VIM_CHANGE_INNER_WORD(); break;
          case VIM_D: VIM_DELETE_WORD(); break;
          case VIM_DI: VIM_DELETE_INNER_WORD(); break;
          case VIM_V: VIM_VISUAL_WORD(); break;
          case VIM_VI: VIM_VISUAL_INNER_WORD(); break;
        }
      }
      return false;

    case VIM_X:
      if (pressed) { VIM_CUT(); }
      return false;

    case VIM_Y:
      if (pressed) { SHIFTED ? VIM_YANK_TO_EOL() : VIM_YANK(); }
      return false;

    default:
      return true;
  }
} 

// ************************************************ //
// ******** DYNAMIC TAP HOLD CONFIGURATION ******** //
// ************************************************ //
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case FNT_PSCR:
      return TAPPING_TERM + 40;
    default:
      return TAPPING_TERM;
  }
}
bool get_retro_tapping(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case NUMT_SCLN:
      // Immediately select the hold action when another key is tapped
      return true;
    case CS_F14:
      return true;
    case FNT_PSCR:
      return true;
    case FNT_BSLS:
      return true;
    default:
      return false;
  }
}

// ************************************************ //
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
  #ifdef RGBLIGHT_ENABLE
  rgblight_disable_noeeprom();
  #endif // !RGBLIGHT_ENABLE
}

// ************************************************ //
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

/****
 *.##.......########..########.....########.##.....##.##....##..######..########.####..#######..##....##..######.
 *.##.......##.....##.##.....##....##.......##.....##.###...##.##....##....##.....##..##.....##.###...##.##....##
 *.##.......##.....##.##.....##....##.......##.....##.####..##.##..........##.....##..##.....##.####..##.##......
 *.##.......##.....##.########.....######...##.....##.##.##.##.##..........##.....##..##.....##.##.##.##..######.
 *.##.......##.....##.##...##......##.......##.....##.##..####.##..........##.....##..##.....##.##..####.......##
 *.##.......##.....##.##....##.....##.......##.....##.##...###.##....##....##.....##..##.....##.##...###.##....##
 *.########.########..##.....##....##........#######..##....##..######.....##....####..#######..##....##..######.
 */
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

/****
 *.##.....##....###....########.########..####.##.....##.....######...######.....###....##....##
 *.###...###...##.##......##....##.....##..##...##...##.....##....##.##....##...##.##...###...##
 *.####.####..##...##.....##....##.....##..##....##.##......##.......##........##...##..####..##
 *.##.###.##.##.....##....##....########...##.....###........######..##.......##.....##.##.##.##
 *.##.....##.#########....##....##...##....##....##.##............##.##.......#########.##..####
 *.##.....##.##.....##....##....##....##...##...##...##.....##....##.##....##.##.....##.##...###
 *.##.....##.##.....##....##....##.....##.####.##.....##.....######...######..##.....##.##....##
 */
void matrix_init_user(void) {
  //debug_enable = true;
  VIM_LEADER(KC_NO);
};

LEADER_EXTERNS(); // Keep this line above matrix_scan_user

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    /* Caps Word */
    // Double tap LDR for CAPS_WORD
    SEQ_ONE_KEY(KC_LEAD) {
      caps_word_on();
    }
    /* Caps Lock */
    // Triple tap LDR for CAPSLOCK
    SEQ_TWO_KEYS(KC_LEAD, KC_LEAD) {
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
    // NOTE: Pending removal
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

/****
 *.##.....##.####.##.....##....########.##.....##.##....##..######..########.####..#######..##....##..######.
 *.##.....##..##..###...###....##.......##.....##.###...##.##....##....##.....##..##.....##.###...##.##....##
 *.##.....##..##..####.####....##.......##.....##.####..##.##..........##.....##..##.....##.####..##.##......
 *.##.....##..##..##.###.##....######...##.....##.##.##.##.##..........##.....##..##.....##.##.##.##..######.
 *..##...##...##..##.....##....##.......##.....##.##..####.##..........##.....##..##.....##.##..####.......##
 *...##.##....##..##.....##....##.......##.....##.##...###.##....##....##.....##..##.....##.##...###.##....##
 *....###....####.##.....##....##........#######..##....##..######.....##....####..#######..##....##..######.
 */
// NOTE: Based off ergodox_ez/keymaps/vim/ and modified to work with Windows
/***
 *       ####  #    # ######     ####  #    #  ####  ##### 
 *      #    # ##   # #         #      #    # #    #   #   
 *      #    # # #  # #####      ####  ###### #    #   #   
 *      #    # #  # # #              # #    # #    #   #   
 *      #    # #   ## #         #    # #    # #    #   #   
 *       ####  #    # ######     ####  #    #  ####    #   
 */
/**
 * Vim-like `append` command.
 * Works by sending →
 */
void VIM_APPEND(void) {
  print("\e[31ma\e[0m");
  TAP(KC_RIGHT);
  layer_move(_BASE);
}

/**
 * Vim-like `back` command
 * Simulates vim's `b` command by sending ^←
 */
void VIM_BACK(void) {
  print("\e[31mb\e[0m");
  CTRL(KC_LEFT);
}

/**
 * Vim-like `cut` command
 * Simulates vim's `x` command by sending ⇧→ then ^X
 */
void VIM_CUT(void) {
  print("\e[31mx\e[0m");
  SHIFT(KC_RIGHT);
  CTRL(KC_X);
}

/**
 * Vim-like `down` command
 * Sends ↓
 */
void VIM_DOWN(void) {
  print("\e[31mj\e[0m");
  TAP(KC_DOWN);
}

/**
 * Vim-like `end` command
 * Simulates vim's `e` command by sending ^→
 */
void VIM_END(void) {
  print("\e[31me\e[0m");
  CTRL(KC_RIGHT);
}

/**
 * Vim-like `left` command
 * Sends ←
 */
void VIM_LEFT(void) {
  print("\e[31mh\e[0m");
  VIM_LEADER(KC_NO);
  TAP(KC_LEFT);
}

/**
 * Vim-like `open` command.
 * Works by sending `End` to move to the end of the line, `Enter` to open a new line,
 * then switching to insert mode.
 */
void VIM_OPEN(void) {
  print("\e[31mo\e[0m");
  VIM_LEADER(KC_NO);
  TAP(KC_END);
  TAP(KC_ENTER);
  layer_move(_BASE);
}

/**
 * Vim-like `put after` command
 * Simulates vim's `p` command by sending ^V
 */
void VIM_PUT_AFTER(void) {
  print("\e[31mp\e[0m");
  VIM_LEADER(KC_NO);
  VIM_RIGHT();
  CTRL(KC_V);
}

/**
 * Vim-like `put before` command
 * Simulates vim's `P` command by sending ↑, ^←, then ^V
 */
void VIM_PUT_BEFORE(void) {
  print("\e[31mP\e[0m");
  VIM_LEADER(KC_NO);
  CTRL(KC_V);
}

/**
 * Vim-like `right` command
 * Sends →
 */
void VIM_RIGHT(void) {
  print("\e[31ml\e[0m");
  VIM_LEADER(KC_NO);
  TAP(KC_RIGHT);
}

/**
 * Vim-like `substitute` command
 * Simulates vim's `s` command by sending ⇧→ to select the next character, then
 * ^X to cut it, then entering insert mode.
 */
void VIM_SUBSTITUTE(void) {
  print("\e[31ms\e[0m");
  VIM_LEADER(KC_NO);
  SHIFT(KC_RIGHT);
  CTRL(KC_X);
  layer_move(_BASE);
}

/**
 * Vim-like `undo` command
 * Simulates vim's `u` command by sending ^Z
 */
void VIM_UNDO(void) {
  print("\e[31mu\e[0m");
  VIM_LEADER(KC_NO);
  CTRL(KC_Z);
}

/**
 * Vim-like `up` command
 * Sends ↑
 */
void VIM_UP(void) {
  print("\e[31mk\e[0m");
  VIM_LEADER(KC_NO);
  TAP(KC_UP);
}

/**
 * Vim-like `word` command
 * Simulates vim's `w` command by moving the cursor first to the
 * end of the current word, then to the end of the next word,
 * then to the beginning of that word.
 */
void VIM_WORD(void) {
  print("\e[31mw\e[0m");
  VIM_LEADER(KC_NO);
  PRESS(KC_LCTRL);
    TAP(KC_RIGHT);
    TAP(KC_RIGHT);
    TAP(KC_LEFT);
  RELEASE(KC_LCTRL);
}

/**
 * Vim-like `yank` command
 * Simulates vim's `y` command by sending ^C
 */
void VIM_YANK(void) {
  print("\e[31my\e[0m");
  VIM_LEADER(KC_NO);
  CTRL(KC_C);
}

/***
 *       ####  #    # # ###### ##### ###### #####  
 *      #      #    # # #        #   #      #    # 
 *       ####  ###### # #####    #   #####  #    # 
 *           # #    # # #        #   #      #    # 
 *      #    # #    # # #        #   #      #    # 
 *       ####  #    # # #        #   ###### ##### 
 */
/**
 * Vim-like `append to line` command
 * Simulates vim's `A` command by sending End, 
 * then switching to insert mode
 */
void VIM_APPEND_LINE(void) {
  print("\e[31mA\e[0m");
  VIM_LEADER(KC_NO);
  TAP(KC_END);
  layer_move(_BASE);
}

/**
 * Vim-like `change line` command
 * Simulates vim's `C` command by sending ⇧End, then ^X
 * then switching to insert mode
 */
void VIM_CHANGE_TO_EOL(void) {
  print("\e[31mC\e[0m");
  VIM_LEADER(KC_NO);
  VIM_DELETE_TO_EOL();
  layer_move(_BASE);
}

/**
 * Vim-like 'delete line' command
 * Simulates vim's `D` command by sending ⇧End, then ^X
 */
void VIM_DELETE_TO_EOL(void) {
  print("\e[31mD\e[0m");
  VIM_LEADER(KC_NO);
  PRESS(KC_LSFT);
  TAP(KC_END);
  RELEASE(KC_LSFT);
  PRESS(KC_LCTL);
  TAP(KC_X);
  RELEASE(KC_LCTL); 
}

/**
 * Vim-like 'join lines' command
 * Simulates vim's `J` command by sending ^→ to go to the end of the line, then
 * DELETE to join the lines
 */
void VIM_JOIN(void) {
  print("\e[31mJ\e[0m");
  VIM_LEADER(KC_NO);
  TAP(KC_END);
  TAP(KC_DELETE);
  VIM_LEADER(KC_NO);
}

/**
 * Vim-like 'open above' command
 * Simulates vim's `O` command by sending `Home` to go to the start of the line,
 * `Enter` to move the line down, ↑ to move up to the new line, then switching to
 * insert mode.
 */
void VIM_OPEN_ABOVE(void) {
  print("\e[31mO\e[0m");
  VIM_LEADER(KC_NO);
  TAP(KC_HOME);
  TAP(KC_ENTER);
  TAP(KC_UP);
  layer_move(_BASE);
}

/**
 * Vim-like 'change whole line' command
 * Simulates vim's `S` `cc` or `c$` commands by sending ⌘← to go to the start of the line,
 * ⌃K to kill the line, then switching to insert mode.
 */
void VIM_CHANGE_WHOLE_LINE(void) {
  print("\e[31mS\e[0m");
  VIM_LEADER(KC_NO);
  TAP(KC_HOME);
  TAP(KC_HOME);
  VIM_CHANGE_TO_EOL();
}

/**
 * Vim-like `yank to end of line` command
 * Simulates vim's `Y` command by sending ⇧^→, End, then ^C
 */
void VIM_YANK_TO_EOL(void) {
  print("\e[31mY\e[0m");
  VIM_LEADER(KC_NO);
  PRESS(KC_LSHIFT);
    TAP(KC_END);
  RELEASE(KC_LSHIFT);
  CTRL(KC_C);
  TAP(KC_LEFT);
}

/***
 *      #   #    #####  #####  ###### ###### # #    # 
 *       # #     #    # #    # #      #      #  #  #  
 *        #      #    # #    # #####  #####  #   ##   
 *        #      #####  #####  #      #      #   ##   
 *        #      #      #   #  #      #      #  #  #  
 *        #      #      #    # ###### #      # #    # 
 */
/**
 * Vim-like `yank to end` 
 * Simulates vim's `ye` command
 * Sends ^⇧→ , ^C
 */
void VIM_YANK_END(void) {
  print("\e[31mye\e[0m");
  VIM_LEADER(KC_NO);
  PRESS(KC_LCTL);
    SHIFT(KC_RIGHT); // select to end of this word
  RELEASE(KC_LCTL);
  CTRL(KC_C);
}

/**
 * Vim-like `yank whole line` 
 * Simulates vim's `yy` command 
 * Sends Home, Home, Shift End ^C
 */
void VIM_YANK_WHOLE_LINE(void) {
  print("\e[31myy\e[0m");
  VIM_LEADER(KC_NO);
  TAP(KC_HOME);
  TAP(KC_HOME);
  VIM_YANK_TO_EOL(); 
}

/**
 * Vim-like `yank word` 
 * Simulates vim's `yw` command
 * Sends ^⇧→→←, ^C
 */
void VIM_YANK_WORD(void) {
  print("\e[31myw\e[0m");
  VIM_LEADER(KC_NO);
  PRESS(KC_LCTL);
    SHIFT(KC_RIGHT); // select to end of this word
    SHIFT(KC_RIGHT); // select to end of next word
    SHIFT(KC_LEFT); // select to start of next word
  RELEASE(KC_LCTL);
  CTRL(KC_C); // yank selection
}

/**
 * Vim-like `yank back` 
 * Simulates vim's `yb` command 
 * Sends ^SHIFT LEFT DEL
 */
void VIM_YANK_BACK(void) {
  print("\e[31myb\e[0m");
  VIM_LEADER(KC_NO);
  PRESS(KC_LCTL);
    SHIFT(KC_LEFT); // select to start of word
    SHIFT(KC_DEL); // yank selection
  RELEASE(KC_LCTL);
}

/**
 * Vim-like `yank left` 
 * Simulates vim's `yh` command
 * Sends ⇧←, ^C
 */
void VIM_YANK_LEFT(void) {
  print("\e[31mh\e[0m");
  VIM_LEADER(KC_NO);
  SHIFT(KC_LEFT);
  CTRL(KC_C);
}

/**
 * Vim-like `yank right` 
 * Simulates vim's `yl` command 
 * Sends ⇧→, ^C
 */
void VIM_YANK_RIGHT(void) {
  print("\e[31ml\e[0m");
  VIM_LEADER(KC_NO);
  SHIFT(KC_RIGHT);
  CTRL(KC_C);
}

/**
 * Vim-like `yank up` 
 * Simulates vim's `yk` command 
 * Sends ↑, ⇧^→ End, ^C
 */
void VIM_YANK_UP(void) {
  print("\e[31myk\e[0m");
  VIM_LEADER(KC_NO);
  TAP(KC_UP);
  VIM_YANK_TO_EOL();
}

/**
 * Vim-like `yank down` 
 * Simulates vim's `yj` command 
 * Sends ↓, ⇧^→ End, ^C
 */
void VIM_YANK_DOWN(void) {
  print("\e[31yj\e[0m");
  VIM_LEADER(KC_NO);
  TAP(KC_DOWN);
  VIM_YANK_TO_EOL();
}

/***
 *      #   # #    #####  #####  ###### ###### # #    # 
 *       # #  #    #    # #    # #      #      #  #  #  
 *        #   #    #    # #    # #####  #####  #   ##   
 *        #   #    #####  #####  #      #      #   ##   
 *        #   #    #      #   #  #      #      #  #  #  
 *        #   #    #      #    # ###### #      # #    # 
 *                                                      
 */
/**
 * Vim-like `yank inner word` 
 * Simulates vim's `yiw` command 
 * by moving back then copying to the end of the word.
 */
void VIM_YANK_INNER_WORD(void) {
  print("\e[31myiw\e[0m");
  VIM_LEADER(KC_NO);
  VIM_BACK();
  VIM_YANK_END();
}

/***
*       #####      #####  #####  ###### ###### # #    # 
*       #    #     #    # #    # #      #      #  #  #  
*       #    #     #    # #    # #####  #####  #   ##   
*       #    #     #####  #####  #      #      #   ##   
*       #    #     #      #   #  #      #      #  #  #  
*       #####      #      #    # ###### #      # #    #
*/
/**
 * Vim-like `delete to end` command
 * Simulates vim's `de` command by sending ^⇧→ then ^X.
 */
void VIM_DELETE_END(void) {
  print("\e[31mde\e[0m");
  VIM_LEADER(KC_NO);
  PRESS(KC_LCTL);
    SHIFT(KC_RIGHT); // select to end of this word
  RELEASE(KC_LCTL);
  CTRL(KC_X);
}

/**
 * Vim-like `delete whole line` command
 * Simulates vim's `dd` command by sending `Home` to move to start of line,
 * selecting the whole line, then sending ^X to cut the line.
 */
void VIM_DELETE_WHOLE_LINE(void) {
  print("\e[31mdd\e[0m");
  VIM_LEADER(KC_NO);
  TAP(KC_HOME);
  TAP(KC_HOME);
  VIM_DELETE_TO_EOL(); 
}

/**
 * Vim-like `delete word` command
 * Simulates vim's `dw` command by sending ^⇧→→← then ^X to select to the start
 * of the next word then cut.
 */
void VIM_DELETE_WORD(void) {
  print("\e[31mdw\e[0m");
  VIM_LEADER(KC_NO);
  PRESS(KC_LCTL);
    SHIFT(KC_RIGHT); // select to end of this word
    SHIFT(KC_RIGHT); // select to end of next word
    SHIFT(KC_LEFT); // select to start of next word
  RELEASE(KC_LCTL);
  CTRL(KC_X); // delete selection
}

/**
 * Vim-like `delete back` command
 * Simulates vim's `db` command by selecting to the end of the word then cut.
 */
void VIM_DELETE_BACK(void) {
  print("\e[31mdb\e[0m");
  VIM_LEADER(KC_NO);
  PRESS(KC_LCTL);
    SHIFT(KC_LEFT); // select to start of word
    SHIFT(KC_DEL); // delete selection
  RELEASE(KC_LCTL);
}

/**
 * Vim-like `delete left` command
 * Simulates vim's `dh` command by sending ⇧← then ^X.
 */
void VIM_DELETE_LEFT(void) {
  print("\e[31mdh\e[0m");
  VIM_LEADER(KC_NO);
  SHIFT(KC_LEFT);
  CTRL(KC_X);
}

/**
 * Vim-like `delete right` command
 * Simulates vim's `dl` command by sending ⇧→ then ^X.
 */
void VIM_DELETE_RIGHT(void) {
  print("\e[31mdl\e[0m");
  VIM_LEADER(KC_NO);
  SHIFT(KC_RIGHT);
  CTRL(KC_X);
}

/**
 * Vim-like `delete up` command
 * Simulates vim's `dk` command by sending ↑ then deleting the line.
 */
void VIM_DELETE_UP(void) {
  print("\e[31mdk\e[0m");
  VIM_LEADER(KC_NO);
  TAP(KC_UP);
  VIM_DELETE_TO_EOL();
}

/**
 * Vim-like `delete down` command
 * Simulates vim's `dj` command by sending ↓ then deleting the line.
 */
void VIM_DELETE_DOWN(void) {
  print("\e[31mdj\e[0m");
  VIM_LEADER(KC_NO);
  TAP(KC_DOWN);
  VIM_DELETE_TO_EOL();
}

/***
*       #####  #    #####  #####  ###### ###### # #    # 
*       #    # #    #    # #    # #      #      #  #  #  
*       #    # #    #    # #    # #####  #####  #   ##   
*       #    # #    #####  #####  #      #      #   ##   
*       #    # #    #      #   #  #      #      #  #  #  
*       #####  #    #      #    # ###### #      # #    #
*/
/**
 * Vim-like `delete inner word` command
 * Simulates vim's `diw` command by moving back then cutting to the end of the word.
 */
void VIM_DELETE_INNER_WORD(void) {
  print("\e[31mdiw\e[0m");
  VIM_LEADER(KC_NO);
  VIM_BACK();
  VIM_DELETE_END();
}

/***
*        ####     #####  #####  ###### ###### # #    # 
*       #    #    #    # #    # #      #      #  #  #  
*       #         #    # #    # #####  #####  #   ##   
*       #         #####  #####  #      #      #   ##   
*       #    #    #      #   #  #      #      #  #  #  
*        ####     #      #    # ###### #      # #    # 
*/
/**
 * Vim-like `change back` command
 * Simulates vim's `cb` command by first deleting to the start of the word,
 * then switching to insert mode.
 */
void VIM_CHANGE_BACK(void) {
  print("\e[31mcb\e[0m");
  VIM_LEADER(KC_NO);
  VIM_DELETE_BACK();
  layer_move(_BASE);
}

/**
 * Vim-like `change down` command
 * Simulates vim's `cj` command by sending ↓ then changing the line.
 */
void VIM_CHANGE_DOWN(void) {
  print("\e[31mcj\e[0m");
  VIM_LEADER(KC_NO);
  VIM_DELETE_DOWN();
  layer_move(_BASE);
}

/**
 * Vim-like `change to end` command
 * Simulates vim's `ce` command by first deleting to the end of the word,
 * then switching to insert mode.
 */
void VIM_CHANGE_END(void) {
  print("\e[31mce\e[0m");
  VIM_LEADER(KC_NO);
  VIM_DELETE_END();
  layer_move(_BASE);
}

/**
 * Vim-like `change left` command
 * Simulates vim's `ch` command by deleting left then switching to insert mode.
 */
void VIM_CHANGE_LEFT(void) {
  print("\e[31mch\e[0m");
  VIM_LEADER(KC_NO);
  VIM_DELETE_LEFT();
  layer_move(_BASE);
}

/**
 * Vim-like `change right` command
 * Simulates vim's `cl` command by deleting right then switching to insert mode.
 */
void VIM_CHANGE_RIGHT(void) {
  print("\e[31mcl\e[0m");
  VIM_LEADER(KC_NO);//?  
  VIM_DELETE_RIGHT();
  layer_move(_BASE);
}

/**
 * Vim-like `change up` command
 * Simulates vim's `ck` command by deleting up then switching to insert mode.
 */
void VIM_CHANGE_UP(void) {
  print("\e[31mck\e[0m");
  VIM_LEADER(KC_NO);//?
  VIM_DELETE_UP();
  layer_move(_BASE);
}

/**
 * Vim-like `change word` command
 * Simulates vim's `cw` command by first deleting to the end of the word,
 * then switching to insert mode.
 */
void VIM_CHANGE_WORD(void) {
  print("\e[31mcw\e[0m");
  VIM_LEADER(KC_NO);
  VIM_DELETE_WORD();
  layer_move(_BASE);
}


/***
*        ####  #   #####  #####  ###### ###### # #    # 
*       #    # #   #    # #    # #      #      #  #  #  
*       #      #   #    # #    # #####  #####  #   ##   
*       #      #   #####  #####  #      #      #   ##   
*       #    # #   #      #   #  #      #      #  #  #  
*        ####  #   #      #    # ###### #      # #    # 
*/
/**
 * Vim-like `change inner word` command
 * Simulates vim's `ciw` command by deleting the inner word then switching to insert mode.
 */
void VIM_CHANGE_INNER_WORD(void) {
  print("\e[31mciw\e[0m");
  VIM_LEADER(KC_NO);//?
  VIM_DELETE_INNER_WORD();
  layer_move(_BASE);
}

/***
 *      #    #     #####  #####  ###### ###### # #    # 
 *      #    #     #    # #    # #      #      #  #  #  
 *      #    #     #    # #    # #####  #####  #   ##   
 *      #    #     #####  #####  #      #      #   ##   
 *       #  #      #      #   #  #      #      #  #  #  
 *        ##       #      #    # ###### #      # #    # 
 */
/**
 * Vim-like `visual select back` command
 * Simulates vim's `vb` command by selecting to the enc of the word.
 */
void VIM_VISUAL_BACK(void) {
  print("\e[31mvb\e[0m");
  VIM_LEADER(KC_NO);
  PRESS(KC_LCTL);
    SHIFT(KC_LEFT); // select to start of word
  RELEASE(KC_LCTL);
}

/**
 * Vim-like `visual select to end` command
 * Simulates vim's `ve` command by selecting to the end of the word.
 */
void VIM_VISUAL_END(void) {
  print("\e[31mve\e[0m");
  VIM_LEADER(KC_NO);
  PRESS(KC_LCTL);
    SHIFT(KC_RIGHT); // select to end of this word
  RELEASE(KC_LCTL);
}

/**
 * Vim-like `visual select word` command
 * Simulates vim's `vw` command by selecting to the end of the word.
 */
void VIM_VISUAL_WORD(void) {
  print("\e[31mvw\e[0m");
  VIM_LEADER(KC_NO);
  PRESS(KC_LCTL);
    SHIFT(KC_RIGHT); // select to end of this word
    SHIFT(KC_RIGHT); // select to end of next word
    SHIFT(KC_LEFT); // select to start of next word
  RELEASE(KC_LCTL);
}

/**
 * Vim-like `visual left` command
 * Simulates vim's `vh` command by sending ⇧←.
 */
void VIM_VISUAL_LEFT(void) {
  print("\e[31mvh\e[0m");
  VIM_LEADER(KC_NO);
  SHIFT(KC_LEFT);
}

/**
 * Vim-like `visual right` command
 * Simulates vim's `vl` command by sending ⇧→.
 */
void VIM_VISUAL_RIGHT(void) {
  print("\e[31mvl\e[0m");
  VIM_LEADER(KC_NO);
  SHIFT(KC_RIGHT);
}

/**
 * Vim-like `visual up` command
 * Simulates vim's `vk` command by sending ⇧↑.
 */
void VIM_VISUAL_UP(void) {
  print("\e[31mvk\e[0m");
  VIM_LEADER(KC_NO);
  SHIFT(KC_UP);
}

/**
 * Vim-like `visual down` command
 * Simulates vim's `vj` command by sending ⇧↓.
 */
void VIM_VISUAL_DOWN(void) {
  print("\e[31mdj\e[0m");
  VIM_LEADER(KC_NO);
  SHIFT(KC_DOWN);
}


/***
 *      #    # #    #####  #####  ###### ###### # #    # 
 *      #    # #    #    # #    # #      #      #  #  #  
 *      #    # #    #    # #    # #####  #####  #   ##   
 *      #    # #    #####  #####  #      #      #   ##   
 *       #  #  #    #      #   #  #      #      #  #  #  
 *        ##   #    #      #    # ###### #      # #    # 
 */
/**
 * Vim-like `visual inner word` command
 * Simulates vim's `viw` command by moving back then selecting to the end of the word.
 */
void VIM_VISUAL_INNER_WORD(void) {
  print("\e[31mviw\e[0m");
  VIM_LEADER(KC_NO);
  VIM_BACK();
  VIM_VISUAL_END();
}

/****
 *.########....###....########.....########.....###....##....##..######..########
 *....##......##.##...##.....##....##.....##...##.##...###...##.##....##.##......
 *....##.....##...##..##.....##....##.....##..##...##..####..##.##.......##......
 *....##....##.....##.########.....##.....##.##.....##.##.##.##.##.......######..
 *....##....#########.##...........##.....##.#########.##..####.##.......##......
 *....##....##.....##.##...........##.....##.##.....##.##...###.##....##.##......
 *....##....##.....##.##...........########..##.....##.##....##..######..########
 */
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

qk_tap_dance_action_t tap_dance_actions[] = {
    [VIM_d] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, d_finished, d_reset, 175),
    [VIM_y] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, y_finished, y_reset, 175),
};

