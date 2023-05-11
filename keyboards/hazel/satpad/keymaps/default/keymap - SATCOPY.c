#include QMK_KEYBOARD_H


enum satpad_layers {
    _WORKMAN,
    _LOWER
};



// COMBO DECLARATIONS  ============================================================================
enum satpad_combos {
    COMBO_SHIFT,
    COMBO_LENGTH
};


// TAP DANCE DECLARATIONS  ============================================================================
enum satpad_tapdances {
    TD_ZLOWER,
    TD_QESC, 
    TD_ATAB,
    TD_XCTL,
    TD_MGUI,
    TD_CALT,
    TD_KSPC,
    TD_VENT,
    TD_XSCLN,       // ; , :
    TD_IQUOT,       // Letter "i", quote
    TD_UPRT,         // up, right
    TD_CP           // copy, paste
};

#define ZLOWER LT(_LOWER, KC_Z)      //Tap for 'Z', Hold for Lower layer
#define QESC TD(TD_QESC)   	         //Tap for 'Q', Twice for 'ESC'
#define ATAB TD(TD_ATAB)	        //Tap for 'A', Twice for 'Tab'
#define KSPC TD(TD_KSPC)	        //Tap for 'Space', Twice for 'K'
#define VENT TD(TD_VENT)	        //Tap for 'Enter', Twice for 'V'
#define XSCLN TD(TD_XSCLN)	        //Tap for ';', Twice for ':'
#define IQUOT TD(TD_IQUOT)	        //Tap for 'I', Twice for Quotes
#define UPRT TD(TD_UPRT)	        // up, right
#define CP TD(TD_CP)	        //Tap for Copy, Twice for Paste
#define XCTL LCTL_T(KC_X)       //Tap for 'X', Hold for 'Left Ctrl'
#define MGUI LGUI_T(KC_M)       //Tap for 'M', Hold for 'Windows Key'
#define CALT LALT_T(KC_C)       //Tap for 'C', Hold for 'Left Alt'
#define OSM_SFT OSM(MOD_LSFT)


uint16_t COMBO_LEN = COMBO_LENGTH;
const uint16_t PROGMEM combo_shift[]        = { KC_W, KC_B, COMBO_END };


combo_t key_combos[] = { 
    [COMBO_SHIFT]   = COMBO(combo_shift, OSM_SFT)
};


//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_QESC]   = ACTION_TAP_DANCE_DOUBLE(KC_Q, KC_ESC),
    [TD_ATAB]   = ACTION_TAP_DANCE_DOUBLE(KC_A, KC_TAB),
    [TD_KSPC]   = ACTION_TAP_DANCE_DOUBLE(KC_SPC, KC_K),
    [TD_VENT]   = ACTION_TAP_DANCE_DOUBLE(KC_ENT, KC_V),
    [TD_XSCLN]   = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_COLN),
    [TD_IQUOT]   = ACTION_TAP_DANCE_DOUBLE(KC_I, KC_QUOT),
    [TD_UPRT]    = ACTION_TAP_DANCE_DOUBLE(KC_UP, KC_RGHT),
    [TD_CP]      = ACTION_TAP_DANCE_DOUBLE(LCTL(KC_C), LCTL(KC_V))
};

const key_override_t **key_overrides = (const key_override_t *[]) {
    NULL
};

#define ______ KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 /* WORKMAN
 *  ,---------------------------------------------------------------------------------------.
 *  |   Q   |   D   |   R   |   W   |   B   |       |   J   |   F   |   U   |   P   |BKSPACE|
 *  |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 *  |   A   |   S   |   H   |   T   |   G   |       |   Y   |   N   |   E   |   O   |  I "  |
 *  |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 *  |   Z   |   X   |   M   |   C   |   V   |  M20  |   K   |   L   |   ,   |   .   |Cpy/Pst|
 *  `---------------------------------------------------------------------------------------'
 */

    [_WORKMAN] = LAYOUT_3x11(
        QESC,   KC_D,   KC_R,   KC_W,   KC_B,   ______,     KC_J,   KC_F,   KC_U,       KC_P,   KC_BSPC,       \
        ATAB,   KC_S,   KC_H,   KC_T,   KC_G,   ______,     KC_Y,   KC_N,   KC_E,       KC_O,   IQUOT,         \
        ZLOWER, XCTL,   MGUI,   CALT,   VENT,   KC_ENT,     KSPC,   KC_L,   KC_COMM,    KC_DOT, CP
    ),


 /* LOWER
 *  ,---------------------------------------------------------------------------------------.
 *  | RESET | BOOT  |       |       |       |       |  ; :  |   7   |   8   |   9   | DEL   |
 *  |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 *  |       |       |       |       |       |       |       |   4   |   5   |   6   |UP/RT  |
 *  |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 *  |       |       |       |       |       |  M20  |   0   |   1   |   2   |   3   |  /\   |
 *  `---------------------------------------------------------------------------------------'
 */
    [_LOWER] = LAYOUT_3x11(
        QK_RBT,   QK_BOOT,   XXXXXXX,   XXXXXXX,   XXXXXXX,   _______,  XSCLN,    KC_7,   KC_8,    KC_9,   KC_DEL,       \
        XXXXXXX, XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   _______,  XXXXXXX,   KC_4,   KC_5,    KC_6,   UPRT,    \
        _______, XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,     KC_0,   KC_1,   KC_2,    KC_3,   KC_SLSH
    ),
};

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_WORKMAN] = { ENCODER_CCW_CW(KC_SPC, OSM_SFT) },
    [_LOWER] = { ENCODER_CCW_CW(KC_SPC, OSM_SFT) },
};
 
oled_rotation_t oled_init_user(oled_rotation_t rotation){   
    return OLED_ROTATION_270;
}

bool oled_task_user(void) {
    uint8_t modifiers = get_mods() | get_oneshot_mods();

    oled_set_cursor(0, 11); 
    oled_write_P(PSTR("SHIFT"), (modifiers & MOD_MASK_SHIFT) || is_caps_word_on());
    oled_write_P(PSTR("CNTRL"), (modifiers & MOD_MASK_CTRL));

    return true;
}




