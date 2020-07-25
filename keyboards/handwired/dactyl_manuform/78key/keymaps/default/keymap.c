#include QMK_KEYBOARD_H


// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layers {
    _QWERTY,
    _FN,
    _NUMPAD,
};

// Some basic macros
#define TASK    LCTL(LSFT(KC_ESC))
#define TAB_R   LCTL(KC_TAB)
#define TAB_L   LCTL(LSFT(KC_TAB))
#define TAB_RO  LCTL(LSFT(KC_T))

enum unicode_names {
    nTILDE,
    NTILDE,
    aACUTE,
    eACUTE,
    iACUTE,
    oACUTE,
    uACUTE,
    AACUTE,
    EACUTE,
    IACUTE,
    OACUTE,
    UACUTE
};

const uint32_t PROGMEM unicode_map[] = {
    [nTILDE] = 241,
    [NTILDE] = 209,
    [aACUTE] = 225,
    [eACUTE] = 233,
    [iACUTE] = 237,
    [oACUTE] = 243,
    [uACUTE] = 250,
    [AACUTE] = 193,
    [EACUTE] = 201,
    [IACUTE] = 205,
    [OACUTE] = 211,
    [UACUTE] = 218
};

void matrix_init_user(void) {
  set_unicode_input_mode(UC_WINC);
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT_78key(
  // left hand
   KC_ESC,          KC_1,    KC_2,    KC_3,   KC_4,   KC_5,   KC_6,
   KC_TAB,          KC_Q,    KC_W,    KC_E,   KC_R,   KC_T,   TT(1),
   KC_CAPS,         KC_A,    KC_S,    KC_D,   KC_F,   KC_G,   TT(2),
   OSM(MOD_LSFT),   KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,   LCTL(LALT(KC_DEL)),
   KC_LCTL,         KC_LALT, KC_LGUI, KC_RALT,KC_APP,
                                   KC_BSPC,
                                   KC_DEL,
                               KC_END, KC_HOME,
                               KC_PGDN, KC_PGUP,
        // right hand
                     KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,   KC_GRV,
                     KC_Y,    KC_U,    KC_I,    KC_O,     KC_P,     KC_SLSH,  KC_PAUS,
                     KC_H,    KC_J,    KC_K,    KC_L,     KC_SCLN,  KC_QUOT,  KC_PSCR,
                     KC_N,    KC_M,    KC_COMM,  KC_DOT,  KC_LBRC,  KC_RBRC,  KC_INS,
                                       KC_LEFT, KC_UP,    KC_DOWN,  KC_RGHT,  KC_BSLS,
            KC_SPC,
            KC_ENT,
        OSM(MOD_RSFT), KC_CAPS,
        KC_RCTL, KC_RALT),

[_FN] = LAYOUT_78key(
  // left hand
   _______,   KC_F1,     KC_F2,      KC_F3,    KC_F4,     KC_F5,    KC_F6,
   _______,   _______,   _______,    XP(eACUTE,EACUTE),    _______,   _______,  _______,
   _______,   XP(aACUTE,AACUTE),   _______,    _______,  _______,   _______,  _______,
   _______,   _______,   _______,    _______,  _______,   _______,  RESET,
   _______,   _______,   _______,    _______,  _______,
                                   _______,
                                   _______,
                               _______, _______,
                               _______, _______,
        // right hand
                     KC_F7,     KC_F8,     KC_F9,     KC_F10,    KC_F11,    KC_F12,    _______,
                     _______,   XP(uACUTE,UACUTE),   XP(iACUTE,IACUTE),   XP(oACUTE,OACUTE),   _______,   _______,   _______,
                     _______,   _______,   _______,   _______,   _______,   _______,   _______,
                     XP(nTILDE,NTILDE),   _______,   _______,   _______,   _______,   _______,   _______,
                                           _______,   _______,   _______,   _______,   _______,
            _______,
            _______,
        _______, _______,
        _______, _______),

[_NUMPAD] = LAYOUT_78key(
  // left hand
   _______,   _______,   _______,   _______,   _______,   _______,  _______,
   _______,   _______,   _______,   _______,   _______,   _______,  _______,
   _______,   _______,   _______,   _______,   _______,   _______,  _______,
   _______,   _______,   _______,   _______,   _______,   _______,  _______,
   _______,   _______,   _______,   _______,   _______,
                                    _______,
                                    _______,
                               _______, _______,
                               _______, _______,
        // right hand
                     _______,   _______,   KC_NLCK,   _______,   KC_PMNS,   KC_PPLS,   _______,
                     _______,   _______,   KC_P7,     KC_P8,     KC_P9,     _______,   _______,
                     _______,   _______,   KC_P4,     KC_P5,     KC_P6,     KC_PAST,   _______,
                     _______,   _______,   KC_P1,     KC_P2,     KC_P3,     KC_PSLS,   _______,
                                           _______,   KC_P0,     KC_PDOT,   _______,   _______,
            _______,
            KC_PENT,
        _______, _______,
        _______, _______),

};
