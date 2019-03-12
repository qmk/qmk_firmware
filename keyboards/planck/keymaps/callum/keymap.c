#pragma message "You may need to add LAYOUT_planck_grid to your keymap layers - see default for an example"
#include "planck.h"
#include "action_layer.h"

extern keymap_config_t keymap_config;

#define AC(X) A(C(X))
#define SC(X) S(C(X))

enum planck_layers {
    _COLEMAK,
    _QWERTY,
    _SYMB,
    _MOVE,
    _FUNC,
    _MOUSE,
};

enum planck_keycodes {
    COLEMAK = SAFE_RANGE,
    QWERTY,
    SYMB,
    MOVE,
    FUNC,
    MOUSE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* COLEMAK
     * ,-----------------------------------------------------------------------.
     * |Tab  |  Q  |  W  |  F  |  P  |  G  |  J  |  L  |  U  |  Y  |  ;  |  -  |
     * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
     * |Bksp |  A  |  R  |  S  |  T  |  D  |  H  |  N  |  E  |  I  |  O  |  '  |
     * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
     * |Shift|  Z  |  X  |  C  |  V  |  B  |  K  |  M  |  ,  |  .  |  /  |Shift|
     * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
     * |Func |Ctrl | Alt |Super|Symb |Enter|Space|Move |Super| Alt |Ctrl |Func |
     * `-----------------------------------------------------------------------'
     */
    [_COLEMAK] = {
        {
            KC_TAB,       KC_Q,         KC_W,         KC_F,
            KC_P,         KC_G,         KC_J,         KC_L,
            KC_U,         KC_Y,         KC_SCLN,      KC_MINS
        },
        {
            KC_BSPC,      KC_A,         KC_R,         KC_S,
            KC_T,         KC_D,         KC_H,         KC_N,
            KC_E,         KC_I,         KC_O,         KC_QUOT
        },
        {
            KC_LSFT,      KC_Z,         KC_X,         KC_C,
            KC_V,         KC_B,         KC_K,         KC_M,
            KC_COMM,      KC_DOT,       KC_SLSH,      KC_RSFT
        },
        {
            FUNC,         KC_LCTL,      KC_LALT,      KC_LGUI,
            SYMB,         KC_ENT,       KC_SPC,       MOVE,
            KC_RGUI,      KC_RALT,      KC_RCTL,      FUNC
        }
    },

    /* QWERTY
     * ,-----------------------------------------------------------------------.
     * |Tab  |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  -  |
     * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
     * |Bksp |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |
     * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
     * |Shift|  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  |Shift|
     * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
     * |Func |Ctrl | Alt |Super|Symb |Enter|Space|Move |Super| Alt |Ctrl |Func |
     * `-----------------------------------------------------------------------'
     */
    [_QWERTY] = {
        {
            KC_TAB,       KC_Q,         KC_W,         KC_E,
            KC_R,         KC_T,         KC_Y,         KC_U,
            KC_I,         KC_O,         KC_P,         KC_MINS
        },
        {
            KC_BSPC,      KC_A,         KC_S,         KC_D,
            KC_F,         KC_G,         KC_H,         KC_J,
            KC_K,         KC_L,         KC_SCLN,      KC_QUOT
        },
        {
            KC_LSFT,      KC_Z,         KC_X,         KC_C,
            KC_V,         KC_B,         KC_N,         KC_M,
            KC_COMM,      KC_DOT,       KC_SLSH,      KC_RSFT
        },
        {
            FUNC,         KC_LCTL,      KC_LALT,      KC_LGUI,
            SYMB,         KC_ENT,       KC_SPC,       MOVE,
            KC_RGUI,      KC_RALT,      KC_RCTL,      FUNC
        }
    },

    /* SYMB
     * ,-----------------------------------------------------------------------.
     * | Esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |     |
     * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
     * | Del |  !  |  @  |  #  |  $  |  %  |  ^  |  &  |  *  |  (  |  )  |     |
     * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
     * |     |  ~  |  `  |  +  |  =  |  |  |  \  |  [  |  ]  |  {  |  }  |     |
     * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
     * |     |     |     |     |     |     |     |Mouse|     |     |     |     |
     * `-----------------------------------------------------------------------'
     */
    [_SYMB] = {
        {
            KC_ESC,       KC_1,         KC_2,         KC_3,
            KC_4,         KC_5,         KC_6,         KC_7,
            KC_8,         KC_9,         KC_0,         _______
        },
        {
            KC_DEL,       KC_EXLM,      KC_AT,        KC_HASH,
            KC_DLR,       KC_PERC,      KC_CIRC,      KC_AMPR,
            KC_ASTR,      KC_LPRN,      KC_RPRN,      _______
        },
        {
            _______,      KC_TILD,      KC_GRV,       KC_PLUS,
            KC_EQL,       KC_PIPE,      KC_BSLS,      KC_LBRC,
            KC_RBRC,      KC_LCBR,      KC_RCBR,      _______
        },
        {
            _______,      _______,      _______,      _______,
            _______,      _______,      _______,      MOUSE,
            _______,      _______,      _______,      _______
        }
    },

    /* MOVE
     * ,-----------------------------------------------------------------------.
     * |     |     |     |     |     |     |CtrUp|Home | Up  | End |Caps | Esc |
     * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
     * |     |     |     |     |     |     |SpaL |Left |Down |Right|SpaR | Del |
     * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
     * |     |     |     |     |     |     |CtrDn|PgDn |PgUp |TabL |TabR |     |
     * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
     * |     |     |     |     |Mouse|     |     |     |     |     |     |     |
     * `-----------------------------------------------------------------------'
     */
    [_MOVE] = {
        {
            AC(KC_A),     AC(KC_B),     AC(KC_C),     AC(KC_D),
            AC(KC_E),     AC(KC_F),     C(KC_UP),     KC_HOME,
            KC_UP,        KC_END,       KC_CAPS,      KC_ESC
        },
        {
            AC(KC_G),     AC(KC_H),     AC(KC_I),     AC(KC_J),
            AC(KC_K),     AC(KC_L),     C(KC_LEFT),   KC_LEFT,
            KC_DOWN,      KC_RGHT,      C(KC_RIGHT),  KC_DEL
        },
        {
            _______,      AC(KC_M),     AC(KC_N),     AC(KC_O),
            AC(KC_P),     AC(KC_Q),     C(KC_DOWN),   KC_PGDN,
            KC_PGUP,      SC(KC_TAB),   C(KC_TAB),    _______
        },
        {
            _______,      _______,      _______,      _______,
            MOUSE,        _______,      _______,      _______,
            _______,      _______,      _______,      _______
        }
    },

    /* FUNC
     * ,-----------------------------------------------------------------------.
     * |Reset| F1  | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9  | F10 |VolUp|
     * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
     * |Power| F11 | F12 | F13 | F14 | F15 | F16 | F17 | F18 | F19 | F20 |VolDn|
     * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
     * |     |     |Home |TabL |TabR |End  |     |     |     |Clmak|Qwrty|     |
     * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
     * |     |     |     |     |Prev |Mute |Play |Next |     |     |     |     |
     * `-----------------------------------------------------------------------'
     */
    [_FUNC] = {
        {
            RESET,        KC_F1,        KC_F2,        KC_F3,
            KC_F4,        KC_F5,        KC_F6,        KC_F7,
            KC_F8,        KC_F9,        KC_F10,       KC_VOLU
        },
        {
            KC_POWER,     KC_F11,       KC_F12,       KC_F13,
            KC_F14,       KC_F15,       KC_F16,       KC_F17,
            KC_F18,       KC_F19,       KC_F20,       KC_VOLD
        },
        {
            _______,      XXXXXXX,      KC_HOME,      SC(KC_TAB),
            C(KC_TAB),    KC_END,       XXXXXXX,      XXXXXXX,
            XXXXXXX,      COLEMAK,      QWERTY,       _______
        },
        {
            _______,      _______,      _______,      _______,
            KC_MPRV,      KC_MUTE,      KC_MPLY,      KC_MNXT,
            _______,      _______,      _______,      _______
        }
    },

    /* MOUSE
     * ,-----------------------------------------------------------------------.
     * |     |     |     |     |     |     |     | ScL |Up   | ScR |     |     |
     * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
     * |     | B4  | B3  | B2  | B1  |     |     |Left |Down |Right|     |     |
     * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
     * |     |     | Ac0 | Ac1 | Ac2 |     |     | ScD | ScU |     |     |     |
     * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
     * |     |     |     |     |     |     |     |     |     |     |     |     |
     * `-----------------------------------------------------------------------'
     */
    [_MOUSE] = {
        {
            _______,      _______,      C(KC_LEFT),   C(KC_UP),
            C(KC_RIGHT),  _______,      _______,      KC_WH_L,
            KC_MS_U,      KC_WH_R,      _______,      _______
        },
        {
            _______,      KC_BTN4,      KC_BTN3,      KC_BTN2,
            KC_BTN1,      _______,      _______,      KC_MS_L,
            KC_MS_D,      KC_MS_R,      _______,      _______
        },
        {
            _______,      _______,      KC_ACL0,      KC_ACL1,
            KC_ACL2,      _______,      _______,      KC_WH_D,
            KC_WH_U,      _______,      _______,      _______
        },
        {
            _______,      _______,      _______,      _______,
            _______,      _______,      _______,      _______,
            _______,      _______,      _______,      _______
        }
    }
};

#ifdef AUDIO_ENABLE
float colemak_song[][2] = SONG(COLEMAK_SOUND);
float qwerty_song[][2] = SONG(QWERTY_SOUND);
#endif

void set_colemak(void) {
#ifdef AUDIO_ENABLE
    stop_all_notes();
    PLAY_SONG(colemak_song);
#endif
    set_single_persistent_default_layer(_COLEMAK);
}

void set_qwerty(void) {
#ifdef AUDIO_ENABLE
    stop_all_notes();
    PLAY_SONG(qwerty_song);
#endif
    set_single_persistent_default_layer(_QWERTY);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case COLEMAK:
            if (record->event.pressed) {
                set_colemak();
            }
            return false;
        case QWERTY:
            if (record->event.pressed) {
                set_qwerty();
            }
            return false;
        case SYMB:
            if (record->event.pressed) {
                layer_on(_SYMB);
            } else {
                layer_off(_SYMB);
            }
            return false;
        case MOVE:
            if (record->event.pressed) {
                layer_on(_MOVE);
            } else {
                layer_off(_MOVE);
            }
            return false;
        case FUNC:
            if (record->event.pressed) {
                layer_on(_FUNC);
            } else {
                layer_off(_FUNC);
            }
            return false;
        case MOUSE:
            if (record->event.pressed) {
                layer_on(_MOUSE);
            } else {
                layer_off(_MOUSE);
            }
            return false;

        // Override the defualt auto shifted symbols to use SEND_STRING
        // See https://github.com/qmk/qmk_firmware/issues/4072
        case KC_EXLM:
            if (record->event.pressed) { SEND_STRING("!"); }
            return false;
        case KC_AT:
            if (record->event.pressed) { SEND_STRING("@"); }
            return false;
        case KC_HASH:
            if (record->event.pressed) { SEND_STRING("#"); }
            return false;
        case KC_DLR:
            if (record->event.pressed) { SEND_STRING("$"); }
            return false;
        case KC_PERC:
            if (record->event.pressed) { SEND_STRING("%"); }
            return false;
        case KC_CIRC:
            if (record->event.pressed) { SEND_STRING("^"); }
            return false;
        case KC_AMPR:
            if (record->event.pressed) { SEND_STRING("&"); }
            return false;
        case KC_ASTR:
            if (record->event.pressed) { SEND_STRING("*"); }
            return false;
        case KC_LPRN:
            if (record->event.pressed) { SEND_STRING("("); }
            return false;
        case KC_RPRN:
            if (record->event.pressed) { SEND_STRING(")"); }
            return false;
        case KC_TILD:
            if (record->event.pressed) { SEND_STRING("~"); }
            return false;
        case KC_GRV:
            if (record->event.pressed) { SEND_STRING("`"); }
            return false;
        case KC_PLUS:
            if (record->event.pressed) { SEND_STRING("+"); }
            return false;
        case KC_EQL:
            if (record->event.pressed) { SEND_STRING("="); }
            return false;
        case KC_PIPE:
            if (record->event.pressed) { SEND_STRING("|"); }
            return false;
        case KC_BSLS:
            if (record->event.pressed) { SEND_STRING("\\"); }
            return false;
        case KC_LBRC:
            if (record->event.pressed) { SEND_STRING("["); }
            return false;
        case KC_RBRC:
            if (record->event.pressed) { SEND_STRING("]"); }
            return false;
        case KC_LCBR:
            if (record->event.pressed) { SEND_STRING("{"); }
            return false;
        case KC_RCBR:
            if (record->event.pressed) { SEND_STRING("}"); }
            return false;
    }
    return true;
}
