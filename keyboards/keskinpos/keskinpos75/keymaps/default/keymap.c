#include QMK_KEYBOARD_H
#include "keymap_turkish_q.h"
#include "sendstring_turkish_q.h"


enum custom_keycodes {
    MACRO01 = SAFE_RANGE,
    MACRO02,
    MACRO03,
    MACRO04,
    MACRO05,
    MACRO06,
    MACRO07,
    MACRO08,
    MACRO09,
    MACRO10,
    MACRO11,
    MACRO12,
    MACRO13,
    MACRO14,
    MACRO15,
    MACRO16,
    MACRO17,
    MACRO18,
    MACRO19,
    MACRO20,
    MACRO21,
    MACRO22,
    MACRO23,
    MACRO24,
    MACRO25,
    MACRO26,
    MACRO27,
    MACRO28,
    MACRO29,
    MACRO30,
    MACRO31,
    MACRO32,
    MACRO33,
    MACRO34,
    MACRO35,
    MACRO36,
    MACRO37,
    MACRO38,
    MACRO39,
    MACRO40,
    MACRO41,
    MACRO42,
    MACRO43,
    KAPAT,
    SERVERAC,
    MASAUSTU,
};



// Defines names for use in layer keycodes and the keymap
//enum layer_names {
//    _BASE,
//    _FN,
//    _FN1,
//    _FN2
//};

    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │ A │ B │ C │ Ç │ D │ E │NUM│  F1   │  F4   │   F10 │       │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │ F │ G │ Ğ │ H │ I │ İ │CAP│  F2   │  F6   │       │       │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │ J │ K │ L │ M │ N │ O │   │  F12  │       │   X   │       │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │ Ö │ P │ Q │ R │ S │ Ş │   │ YUKARI│EN │ 7 │ 8 │ 9 │   F9  │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │ T │ U │ Ü │ V │ W │ X │   │ AŞAGI │TER│ 4 │ 5 │ 6 │   F9  │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │ Y │ Z │   │ ( │ ) │ _ │ F3│ SİLME │ 0 │ 1 │ 2 │ 3 │   F5  │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │ . │ , │ / │ : │ = │ * │   │ SİLME │ 00│ 0 │ . │ 0 │   F5  │
     * └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
     */


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT_ortho_7x15(
        KC_A,    KC_B,    KC_C,    TR_CCED,    KC_D,    KC_E,      KC_NUMLOCK,      KC_F1,       KC_F1,        KC_F4,      KC_F4,     KC_F10,      KC_F10,   _______,   KAPAT,
        KC_F,    KC_G,    TR_GBRV, KC_H,       KC_I,    TR_IDOT,   KC_CAPSLOCK,     KC_F2,       KC_F2,        KC_F6,      KC_F6,     _______,    _______,   SERVERAC,   MASAUSTU,
        KC_J,    KC_K,    KC_L,    KC_M,       KC_N,    KC_O,      _______,     KC_F12,      KC_F12,       _______,    _______,   _______,    KC_PAST,   _______,   _______,
        TR_ODIA, KC_P,    KC_Q,    KC_R,       KC_S,    TR_SCED,  _______,        _______,     KC_UP,        KC_ENT,     KC_P7,     KC_P8,      KC_P9,     KC_F9,     KC_F9,
        KC_T,    KC_U,    TR_UDIA, KC_V,       KC_W,    KC_X,      TERM_ON,          _______,     KC_DOWN,      _______,    KC_P4,     KC_P5,      KC_P6,     KC_F9,     KC_F9,
        KC_Y,    KC_Z,    KC_SPC,  TR_LPRN,    TR_RPRN, TR_UNDS,   KC_F3,           _______,     KC_BSPC,      KC_0,       KC_P1,     KC_P2,      KC_P3,     KC_F5,     KC_F5,
        TR_DOT,  TR_COMM, KC_PSLS, TR_COLN,    TR_EQL,  TR_ASTR,   _______,        _______,     _______,      KC_0,       KC_P0,     TR_DOT,     KC_P0,     KC_F5,     KC_F5
),

        [1] = LAYOUT_ortho_7x15(
       MACRO01, MACRO02,  MACRO03, MACRO04,  MACRO05,   MACRO06,    KC_NUMLOCK,      KC_F1,       KC_F1,        KC_F4,      KC_F4,     KC_F10,      KC_F10,   _______,   _______,
       MACRO07, MACRO08,  MACRO09, MACRO10,  MACRO11,   MACRO12,    KC_CAPSLOCK,     KC_F2,       KC_F2,        KC_F6,      KC_F6,     _______,    _______,   _______,   _______,
       MACRO13, MACRO14,  MACRO15, MACRO16,  MACRO17,   MACRO18,     _______,         KC_F12,      KC_F12,       _______,    _______,   _______,    KC_PAST,   _______,   _______,
       MACRO19, MACRO20,  MACRO21, MACRO22,  MACRO23,   MACRO24,    _______,         _______,     KC_UP,        KC_ENT,     KC_P7,     KC_P8,      KC_P9,     KC_F9,     KC_F9,
       MACRO25, MACRO26,  MACRO27, MACRO28,  MACRO29,   MACRO30,      _______,         _______,     KC_DOWN,      _______,    KC_P4,     KC_P5,      KC_P6,     KC_F9,     KC_F9,
       MACRO31, MACRO32,  MACRO33, MACRO34,  MACRO35,   MACRO36,    KC_F3,           _______,     KC_BSPC,      KC_0,       KC_P1,     KC_P2,      KC_P3,     KC_F5,     KC_F5,
       MACRO37, MACRO38,  MACRO39, MACRO40,  MACRO41,   MACRO42,    _______,         _______,     _______,      KC_0,       KC_P0,     TR_DOT,     KC_P0,     KC_F5,     KC_F5
),
       [2] = LAYOUT_ortho_7x15(
        KC_P3,    KC_B,    KC_C,    TR_CCED,    KC_D,    KC_E,      KC_NUMLOCK,      KC_F1,       KC_F1,        KC_F4,      KC_F4,     KC_F10,      KC_F10,   _______,   _______,
        KC_F,    KC_G,    TR_GBRV, KC_H,       KC_I,    TR_IDOT,   KC_CAPSLOCK,     KC_F2,       KC_F2,        KC_F6,      KC_F6,     _______,    _______,   _______,   _______,
        KC_J,    KC_K,    KC_L,    KC_M,       KC_N,    KC_O,      _______,         KC_F12,      KC_F12,       _______,    _______,   _______,    KC_PAST,   _______,   _______,
        TR_ODIA, KC_P,    KC_Q,    KC_R,       KC_S,    TR_SCED,   _______,         _______,     KC_UP,        KC_ENT,     KC_P7,     KC_P8,      KC_P9,     KC_F9,     KC_F9,
        KC_T,    KC_U,    TR_UDIA, KC_V,       KC_W,    KC_X,      _______,         _______,     KC_DOWN,      _______,    KC_P4,     KC_P5,      KC_P6,     KC_F9,     KC_F9,
        KC_Y,    KC_Z,    KC_SPC,  TR_LPRN,    TR_RPRN, TR_UNDS,   KC_F3,           _______,     KC_BSPC,      KC_0,       KC_P1,     KC_P2,      KC_P3,     KC_F5,     KC_F5,
        TR_DOT,  TR_COMM, KC_PSLS, TR_COLN,    TR_EQL,  TR_ASTR,   _______,         _______,     _______,      KC_0,       KC_P0,     TR_DOT,     KC_P0,     KC_F5,     KC_F5
),
       [3] = LAYOUT_ortho_7x15(
        KC_P4,    KC_B,    KC_C,    TR_CCED,    KC_D,    KC_E,      KC_NUMLOCK,      KC_F1,       KC_F1,        KC_F4,      KC_F4,     KC_F10,      KC_F10,   _______,   _______,
        KC_F,    KC_G,    TR_GBRV, KC_H,       KC_I,    TR_IDOT,   KC_CAPSLOCK,     KC_F2,       KC_F2,        KC_F6,      KC_F6,     _______,    _______,   _______,   _______,
        KC_J,    KC_K,    KC_L,    KC_M,       KC_N,    KC_O,      _______,         KC_F12,      KC_F12,       _______,    _______,   _______,    KC_PAST,   _______,   _______,
        TR_ODIA, KC_P,    KC_Q,    KC_R,       KC_S,    TR_SCED,   _______,         _______,     KC_UP,        KC_ENT,     KC_P7,     KC_P8,      KC_P9,     KC_F9,     KC_F9,
        KC_T,    KC_U,    TR_UDIA, KC_V,       KC_W,    KC_X,      _______,         _______,     KC_DOWN,      _______,    KC_P4,     KC_P5,      KC_P6,     KC_F9,     KC_F9,
        KC_Y,    KC_Z,    KC_SPC,  TR_LPRN,    TR_RPRN, TR_UNDS,   KC_F3,           _______,     KC_BSPC,      KC_0,       KC_P1,     KC_P2,      KC_P3,     KC_F5,     KC_F5,
        TR_DOT,  TR_COMM, KC_PSLS, TR_COLN,    TR_EQL,  TR_ASTR,   _______,         _______,     _______,      KC_0,       KC_P0,     TR_DOT,     KC_P0,     KC_F5,     KC_F5
),
       [4] = LAYOUT_ortho_7x15(
        KC_P5,    KC_B,    KC_C,    TR_CCED,    KC_D,    KC_E,      KC_NUMLOCK,      KC_F1,       KC_F1,        KC_F4,      KC_F4,     KC_F10,      KC_F10,   _______,   _______,
        KC_F,    KC_G,    TR_GBRV, KC_H,       KC_I,    TR_IDOT,   KC_CAPSLOCK,     KC_F2,       KC_F2,        KC_F6,      KC_F6,     _______,    _______,   _______,   _______,
        KC_J,    KC_K,    KC_L,    KC_M,       KC_N,    KC_O,      _______,         KC_F12,      KC_F12,       _______,    _______,   _______,    KC_PAST,   _______,   _______,
        TR_ODIA, KC_P,    KC_Q,    KC_R,       KC_S,    TR_SCED,   _______,         _______,     KC_UP,        KC_ENT,     KC_P7,     KC_P8,      KC_P9,     KC_F9,     KC_F9,
        KC_T,    KC_U,    TR_UDIA, KC_V,       KC_W,    KC_X,      _______,         _______,     KC_DOWN,      _______,    KC_P4,     KC_P5,      KC_P6,     KC_F9,     KC_F9,
        KC_Y,    KC_Z,    KC_SPC,  TR_LPRN,    TR_RPRN, TR_UNDS,   KC_F3,           _______,     KC_BSPC,      KC_0,       KC_P1,     KC_P2,      KC_P3,     KC_F5,     KC_F5,
        TR_DOT,  TR_COMM, KC_PSLS, TR_COLN,    TR_EQL,  TR_ASTR,   _______,         _______,     _______,      KC_0,       KC_P0,     TR_DOT,     KC_P0,     KC_F5,     KC_F5
)


};

void dip_switch_update_user(uint8_t index, bool active) {
	switch (index) {
		case 0:
		if(active) { layer_on(1); } else { layer_off(1); }
		break;
		case 1:
		if(active) { layer_on(2); } else { layer_off(2); }
		break;
        case 2:
        if(active) { layer_on(3); } else { layer_off(3); }
        break;
	}
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch(keycode) {
            case MACRO01:
                SEND_STRING(SS_LSFT("TUS1"));
                register_code(KC_ENT);
                unregister_code(KC_ENT);
                return false;
            case MACRO02:
                SEND_STRING(SS_LSFT("TUS2"));
                register_code(KC_ENT);
                unregister_code(KC_ENT);
                return false;
            case MACRO03:
                SEND_STRING(SS_LSFT("TUS3"));
                register_code(KC_ENT);
                unregister_code(KC_ENT);
                return false;
            case MACRO04:
                SEND_STRING(SS_LSFT("TUS4"));
                register_code(KC_ENT);
                unregister_code(KC_ENT);
                return false;
            case MACRO05:
                SEND_STRING(SS_LSFT("TUS5"));
                register_code(KC_ENT);
                unregister_code(KC_ENT);
                return false;
            case MACRO06:
                SEND_STRING(SS_LSFT("TUS6"));
                register_code(KC_ENT);
                unregister_code(KC_ENT);
                return false;
            case MACRO07:
                SEND_STRING(SS_LSFT("TUS7"));
                register_code(KC_ENT);
                unregister_code(KC_ENT);
                return false;
            case MACRO08:
                SEND_STRING(SS_LSFT("TUS8"));
                register_code(KC_ENT);
                unregister_code(KC_ENT);
                return false;
            case MACRO09:
                SEND_STRING(SS_LSFT("TUS9"));
                register_code(KC_ENT);
                unregister_code(KC_ENT);
                return false;
            case MACRO10:
                SEND_STRING(SS_LSFT("TUS10"));
                register_code(KC_ENT);
                unregister_code(KC_ENT);
                return false;
            case MACRO11:
                SEND_STRING(SS_LSFT("TUS11"));
                register_code(KC_ENT);
                unregister_code(KC_ENT);
                return false;
            case MACRO12:
                SEND_STRING(SS_LSFT("TUS12"));
                register_code(KC_ENT);
                unregister_code(KC_ENT);
                return false;
            case MACRO13:
                SEND_STRING(SS_LSFT("TUS13"));
                return false;
            case MACRO14:
                SEND_STRING(SS_LSFT("TUS14"));
                register_code(KC_ENT);
                unregister_code(KC_ENT);
                return false;
            case MACRO15:
                SEND_STRING(SS_LSFT("TUS15"));
                register_code(KC_ENT);
                unregister_code(KC_ENT);
                return false;
            case MACRO16:
                SEND_STRING(SS_LSFT("TUS16"));
                register_code(KC_ENT);
                unregister_code(KC_ENT);
                return false;
            case MACRO17:
                SEND_STRING(SS_LSFT("TUS17"));
                register_code(KC_ENT);
                unregister_code(KC_ENT);
                return false;
            case MACRO18:
                SEND_STRING(SS_LSFT("TUS18"));
                register_code(KC_ENT);
                unregister_code(KC_ENT);
                return false;
            case MACRO19:
                SEND_STRING(SS_LSFT("TUS19"));
                register_code(KC_ENT);
                unregister_code(KC_ENT);
                return false;
            case MACRO20:
                SEND_STRING(SS_LSFT("TUS20"));
                register_code(KC_ENT);
                unregister_code(KC_ENT);
                return false;
            case MACRO21:
                SEND_STRING(SS_LSFT("TUS21"));
                register_code(KC_ENT);
                unregister_code(KC_ENT);
                return false;
             case MACRO22:
                SEND_STRING(SS_LSFT("TUS22"));
                register_code(KC_ENT);
                unregister_code(KC_ENT);
                return false;
            case MACRO23:
                SEND_STRING(SS_LSFT("TUS23"));
                register_code(KC_ENT);
                unregister_code(KC_ENT);
                return false;
            case MACRO24:
                SEND_STRING(SS_LSFT("TUS24"));
                register_code(KC_ENT);
                unregister_code(KC_ENT);
                return false;
            case MACRO25:
                SEND_STRING(SS_LSFT("TUS25"));
                register_code(KC_ENT);
                unregister_code(KC_ENT);
                return false;
             case MACRO26:
                SEND_STRING(SS_LSFT("TUS26"));
                register_code(KC_ENT);
                unregister_code(KC_ENT);
                return false;
             case MACRO27:
                SEND_STRING(SS_LSFT("TUS27"));
                register_code(KC_ENT);
                unregister_code(KC_ENT);
                return false;
             case MACRO28:
                SEND_STRING(SS_LSFT("TUS28"));
                register_code(KC_ENT);
                unregister_code(KC_ENT);
                return false;
             case MACRO29:
                SEND_STRING(SS_LSFT("TUS29"));
                register_code(KC_ENT);
                unregister_code(KC_ENT);
                return false;
             case MACRO30:
                SEND_STRING(SS_LSFT("TUS30"));
                register_code(KC_ENT);
                unregister_code(KC_ENT);
                return false;
             case MACRO31:
                SEND_STRING(SS_LSFT("TUS31"));
                register_code(KC_ENT);
                unregister_code(KC_ENT);
                return false;
            case MACRO32:
                SEND_STRING(SS_LSFT("TUS32"));
                register_code(KC_ENT);
                unregister_code(KC_ENT);
                return false;
            case MACRO33:
                SEND_STRING(SS_LSFT("TUS33"));
                register_code(KC_ENT);
                unregister_code(KC_ENT);
                return false;
            case MACRO34:
                SEND_STRING(SS_LSFT("TUS34"));
                register_code(KC_ENT);
                unregister_code(KC_ENT);
                return false;
             case MACRO35:
                SEND_STRING(SS_LSFT("TUS35"));
                register_code(KC_ENT);
                unregister_code(KC_ENT);
                return false;
            case MACRO36:
                SEND_STRING(SS_LSFT("TUS36"));
                register_code(KC_ENT);
                unregister_code(KC_ENT);
                return false;
            case MACRO37:
                SEND_STRING(SS_LSFT("TUS37"));
                register_code(KC_ENT);
                unregister_code(KC_ENT);
                return false;
            case MACRO38:
                SEND_STRING(SS_LSFT("TUS38"));
                register_code(KC_ENT);
                unregister_code(KC_ENT);
                return false;
             case MACRO39:
                SEND_STRING(SS_LSFT("TUS39"));
                register_code(KC_ENT);
                unregister_code(KC_ENT);
                return false;
             case MACRO40:
                SEND_STRING(SS_LSFT("TUS40"));
               register_code(KC_ENT);
                unregister_code(KC_ENT);
                return false;
             case MACRO41:
                SEND_STRING(SS_LSFT("TUS41"));
                register_code(KC_ENT);
                unregister_code(KC_ENT);
                return false;
             case MACRO42:
                SEND_STRING(SS_LSFT("TUS42"));
                register_code(KC_ENT);
                unregister_code(KC_ENT);
                return false;
             case MACRO43:
                SEND_STRING(SS_LSFT("TUS43"));
                register_code(KC_ENT);
                unregister_code(KC_ENT);
                return false;
            case KAPAT:
                register_code(KC_LALT);
                register_code(KC_F4);
                unregister_code(KC_LALT);
                unregister_code(KC_F4);
                return false;
            case SERVERAC:
                register_code(KC_LCTRL);
                register_code(KC_LALT);
                register_code(KC_DEL);
                unregister_code(KC_LCTRL);
                unregister_code(KC_LALT);
                unregister_code(KC_DEL);
                return false;
            case MASAUSTU:
                register_code(KC_LALT);
                register_code(KC_TAB);
                unregister_code(KC_LALT);
                unregister_code(KC_TAB);
                return false;
        }
    }
    return true;
};
