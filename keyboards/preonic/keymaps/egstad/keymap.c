/* EGSTAD keymaps
 *
 * Installation
 * 1. Make edits below 
 * 2. Cd into this directory, run npm start
 * 3. Cd into root (../../../../) to locate bin file "preonic_rev3_egstad.bin"
 * 4. Drop that bin into QMK Toolbox and flash Keeb
 *
 * 
 * LEARNINGS
 * - Don't fuck with combos - they make keys feel sticky
 * 
 * 
 * TODO
 * - Convert long key functions into var names
 * —— Right handed delete, zoom in and out, delete
 * —— Left handed command
 * 
 * I put () on Shift tap, [] on Ctrl, and {} on Alt.
 * That, the home row arrows, numpad layer, and macro recording. Oh, and the TrackPoint, of course.
 */

#include QMK_KEYBOARD_H
LEADER_EXTERNS();


// Define layers here and use them in the keymaps matrix below
#define L_QWERTY  0 
#define L_LOWER   1 
#define L_RAISE   2
#define L_DESIGN  3 
#define L_ADJUST  4  




// Tap Dance Declarations
enum {
  TD_BRC = 0,
  TD_MIN,
  TD_GV_ESC,
  TD_BS
};



// Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  // Tap once for Left Brace, twice for Right Brace
  [TD_BRC]  = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_RBRC),
  //Tap once for Minus, twice for Equal
  [TD_MIN]  = ACTION_TAP_DANCE_DOUBLE(KC_MINUS, KC_EQUAL),
  // Tap once for Grave, tap twice for Escape
  [TD_GV_ESC]  = ACTION_TAP_DANCE_DOUBLE(KC_GRAVE, KC_ESCAPE)
};




/*
 * This line indicates the start of the list of Layers.
 * Below that you'll find lines containing either LAYOUT or KEYMAP,
 * and these lines indicate the start of a layer. Below that line
 * is the list of keys that comprise a that particular layer.
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------------------.
 * | ` ESC |  1 !  |  2 @  |  3 #  |  4 $  |  5 %  |  6 ^  |  7 &  |  8 *  |  9 (  |  0 )  | -_ =+ |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * | TB/RS |   Q   |   W   |   E   |   R   |   T   |   Y   |   U   |   I   |   O   |   P   | [{ }] | 
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * | RN/LW |   A   |   S   |   D   |   F   |   G   |   H   |   J   |   K   |   L   |   ;   |   '   |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |  SFT  |   Z   |   X   |   C   |   V   |   B   |   N   |   M   |   ,   |   .   |   /   | SF/RN |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |  LEAD  |  CTL  |  ALT  |  CMD  |  BSP  |      SPC      |  CMD  |   ←   |   ↑   |   ↓   |   →   |
 * `-----------------------------------------------------------------------------------------------
 */

[L_QWERTY] = LAYOUT_preonic_grid( \
/* COL 1                  COL 2           COL 3           COL 4           COL 5                       COL 6           COL 7                   COL 8                          COL 9           COL 10          COL 11          COL 12 */
  TD(TD_GV_ESC),          KC_1,           KC_2,           KC_3,           KC_4,                       KC_5,           KC_6,                   KC_7,                          KC_8,           KC_9,           KC_0,           TD(TD_MIN),            \
  LT(L_RAISE, KC_TAB),    KC_Q,           KC_W,           KC_E,           KC_R,                       KC_T,           KC_Y,                   KC_U,                          KC_I,           KC_O,           KC_P,           TD(TD_BRC),            \
  LT(L_LOWER, KC_BSPACE), KC_A,           KC_S,           KC_D,           KC_F,                       KC_G,           KC_H,                   KC_J,                          KC_K,           KC_L,           KC_SCLN,        KC_QUOT,               \
  KC_LSFT,                KC_Z,           KC_X,           KC_C,           KC_V,                       KC_B,           KC_N,                   KC_M,                          KC_COMM,        KC_DOT,         KC_SLSH,        MT(MOD_RSFT, KC_ENT),  \
  KC_LEAD,                _______,        KC_LCTL,        KC_LALT,        KC_LGUI,                    KC_BSPACE,      MT(MOD_LGUI, KC_SPC),   LT(L_LOWER, KC_BSPACE),        KC_LEFT,        KC_UP,          KC_DOWN,        KC_RGHT                \
),






 /* Lower
 * ,-----------------------------------------------------------------------------------------------.
 * |  F12  |  FN1  |  FN2  |  FN3  |  FN4  |  FN5  |  FN6  |  FN7  |  FN8  |  FN9  |  F10  |  F11  |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |       | CMD+Q | CMD+W |       |       | CMD+T |       |   [   |   ]   |   {   |   }   |  \ |  |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |       | CMD+A | CMD+S | CMD+D | CMD+F | CMD+G |       |   ←   |   ↑   |   ↓   |   →   |       |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |       | CMD+Z | CMD+X | CMD+C | CMD+V |       |       |   -   |   +   |   *   |   /   | M_TOG |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |       |       |       |       |       |               |       |       |       |       |       |    
 * `-----------------------------------------------------------------------------------------------'
 * 
 * TODO
 * • Consider removing command layers.
 * • Perhaps the braces, brackets, and parenths are tap danced?
 * • Hard to reach punctuation beneath arrow keys? (! • # - +)
 * • Press and hold left arrow for raise, and make raise lower
 * • Kinda missing my delete key at top right... 
 * 
 */
[L_LOWER] = LAYOUT_preonic_grid( \
/* COL 1          COL 2           COL 3           COL 4           COL 5           COL 6           COL 7           COL 8           COL 9           COL 10          COL 11          COL 12   */
  _______,        KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          KC_F6,          KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_BSPACE,\
  LGUI(KC_TAB),   LGUI(KC_Q),     LGUI(KC_W),     _______,        _______,        LGUI(KC_T),     _______,        KC_MINUS,       KC_PLUS,        KC_ASTERISK,    KC_KP_SLASH,    _______,\
  _______,        LGUI(KC_A),     LGUI(KC_S),     LGUI(KC_D),     LGUI(KC_F),     LGUI(KC_G),     _______,        KC_LEFT,        KC_UP,          KC_DOWN,        KC_RIGHT,       KC_ENTER, \
  KC_CAPS,        LGUI(KC_Z),     LGUI(KC_X),     LGUI(KC_C),     LGUI(KC_V),     _______,        _______,        KC_LBRC,        KC_RBRC,        KC_LCBR,        KC_RCBR,        KC_BSLASH,   \
  TG(L_DESIGN),   _______,        _______,        _______,        _______,        _______,        _______,        _______,        _______,        _______,        _______,        _______   \
),

/* RAISE
 * ,-----------------------------------------------------------------------------------------------.
 * | ASHFT | BTSDN | BTSUP |       |       |       |       |       |       |       |       |       |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |       |       |       |       |       |       |       |       |       |       |       |       |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |       |       |       |       |       |       |       |       |       |       |       |       |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |  CAP  |       |       |       |       |       |       |       |       |       |       |       |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |       |       |       |       |       |   PLAY/PAUSE  |       |       |  VUP  |  VDN  |       |
 * `-----------------------------------------------------------------------------------------------'
 */
[L_RAISE] = LAYOUT_preonic_grid( \
  KC_ASTG, KC_F1,   KC_F2, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  KC_CAPS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, KC_MPLY, _______, _______, KC__VOLUP, KC__VOLDOWN, _______ \
),


/* DESIGN
 * ,-----------------------------------------------------------------------------------------------.
 * | ASHFT | BTSDN | BTSUP |       |       |       |       |       |       |       |       |       |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |       |       |       |       |       |       |       |       |       |       |       |       |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |       |       |       |       |       |       |       |       |       |       |       |       |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |  CAP  |       |       |       |       |       |       |       |       |       |       |       |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |       |       |       |       |       |   PLAY/PAUSE  |       |       |  VUP  |  VDN  |       |
 * `-----------------------------------------------------------------------------------------------'
 */
[L_DESIGN] = LAYOUT_preonic_grid( \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_BSPACE, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
),







/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Reset|      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|AudOff|AGnorm|AGswap|Qwerty|      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|MusOff|MidiOn|MidOff|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[L_ADJUST] = LAYOUT_preonic_grid( \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  \
  _______, RESET,   DEBUG,   _______, _______, _______, _______, TERM_ON, TERM_OFF,_______, _______, KC_DEL,  \
  _______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, L_QWERTY,  _______, _______,  _______, _______, \
  _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
)


};













/* ==========================================================================
   Leader Key
   ========================================================================== */

LEADER_EXTERNS();

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;

    // Copy
    SEQ_ONE_KEY(KC_C) {
      SEND_STRING(SS_LGUI("c"));
    }

    // Paste
    SEQ_ONE_KEY(KC_V) {
      SEND_STRING(SS_LGUI("v"));
    }

    // Save
    SEQ_ONE_KEY(KC_S) {
      SEND_STRING(SS_LGUI("s"));
    }

    // Select All
    SEQ_ONE_KEY(KC_A) {
      SEND_STRING(SS_LGUI("a"));
    }

    // Duplicate
    SEQ_ONE_KEY(KC_D) {
      SEND_STRING(SS_LGUI("d"));
    }

    // Undo
    SEQ_ONE_KEY(KC_Z) {
      SEND_STRING(SS_LGUI("z"));
    }

    // Cut
    SEQ_ONE_KEY(KC_X) {
      SEND_STRING(SS_LGUI("x"));
    }

    // Find
    SEQ_ONE_KEY(KC_F) {
      SEND_STRING(SS_LGUI("f"));
    }

    // Find All
    SEQ_TWO_KEYS(KC_F, KC_F) {
      register_code(KC_LSHIFT);
      register_code(KC_TAB);
      unregister_code(KC_TAB);
      unregister_code(KC_LSHIFT);
    }

    // Group
    SEQ_ONE_KEY(KC_G) {
      SEND_STRING(SS_LGUI("g"));
    }

    // Tab
    SEQ_ONE_KEY(KC_T) {
      SEND_STRING(SS_LGUI("t"));
    }

    // New
    SEQ_ONE_KEY(KC_N) {
      SEND_STRING(SS_LGUI("n"));
    }

    // Refresh
    SEQ_ONE_KEY(KC_R) {
      SEND_STRING(SS_LGUI("r"));
    } 

    // Zoom Out
    SEQ_ONE_KEY(TD(TD_MIN)) {
      register_code(KC_LGUI);
      register_code(KC_KP_MINUS);
      unregister_code(KC_KP_MINUS);
      unregister_code(KC_LGUI);
    }

    // Zoom In
    SEQ_TWO_KEYS(TD(TD_MIN), TD(TD_MIN)) {
      register_code(KC_LGUI);
      register_code(KC_KP_PLUS);
      unregister_code(KC_KP_PLUS);      
      unregister_code(KC_LGUI);
    }

    // Untab
    SEQ_ONE_KEY(KC_TAB) {
      register_code(KC_LSHIFT);
      register_code(KC_TAB);
      unregister_code(KC_TAB);
      unregister_code(KC_LSHIFT);
    }     

    // Go to beginning of line
    SEQ_ONE_KEY(KC_J) {
      register_code(KC_LGUI);
      register_code(KC_LEFT);
      unregister_code(KC_LEFT);
      unregister_code(KC_LGUI);
    }
    // Go to end of line
    SEQ_ONE_KEY(KC_SCLN) {
      register_code(KC_LGUI);
      register_code(KC_RIGHT);
      unregister_code(KC_RIGHT);
      unregister_code(KC_LGUI);
    }
    // Select text from cursor, back
    SEQ_TWO_KEYS(KC_J, KC_J) {
      register_code(KC_LGUI);
      register_code(KC_LSHIFT);
      register_code(KC_LEFT);
      unregister_code(KC_LEFT);
      unregister_code(KC_LSHIFT);
      unregister_code(KC_LGUI);
    }
    // Select text from cursor, up
    SEQ_TWO_KEYS(KC_K, KC_K) {
      register_code(KC_LGUI);
      register_code(KC_LSHIFT);
      register_code(KC_UP);
      unregister_code(KC_UP);
      unregister_code(KC_LSHIFT);
      unregister_code(KC_LGUI);
    }
    // Select text from cursor, down
    SEQ_TWO_KEYS(KC_L, KC_L) {
      register_code(KC_LGUI);
      register_code(KC_LSHIFT);
      register_code(KC_DOWN);
      unregister_code(KC_DOWN);
      unregister_code(KC_LSHIFT);
      unregister_code(KC_LGUI);
    }
    // Select text from cursor, down
    SEQ_TWO_KEYS(KC_SCLN, KC_SCLN) {
      register_code(KC_LGUI);
      register_code(KC_LSHIFT);
      register_code(KC_RIGHT);
      unregister_code(KC_RIGHT);
      unregister_code(KC_LSHIFT);
      unregister_code(KC_LGUI);
    }


    leader_end();
  }
}
