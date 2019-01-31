#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#define _CX 0 // Carpalx layer
#define _QW 1 // Qwerty layer
#define _KP 2 // Keypad + Media Layer

// Macro name shortcuts
#define DVORAK M(_DV)
#define QWERTY M(_QW)
#define COLEMAK M(_CM)

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

/*

        Function Keys on All Layers (Keypad toggles):
        ,---------------------------------------------------------------.
        |  L0  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8   |
        `---------------------------------------------------------------'
        ,---------------------------------------------------------------.
        |  F9  |  F10 |  F11 |  F12 | PSCR |  L1  |  L2  |  L2  | RESET |
        `---------------------------------------------------------------'

        L0 Carpalx layer:
        ,-------------------------------------------.,-------------------------------------------.
        | Del    |   1  |   3  |   5  |   7  |   9  ||   0  |   8  |   6  |   4  |   2  |   -    |
        |--------+------+------+------+------+------||------+------+------+------+------+--------|
        | Tab    |   Q  |   G  |   M  |   L  |   W  ||   B  |   Y  |   U  |   V  |   ;  |   =    |
        |--------+------+------+------+------+------||------+------+------+------+------+--------|
        | ESC    |   D  |   S  |   T  |   N  |   R  ||   I  |   A  |   E  |   O  |   H  |   '    |
        |--------+------+------+------+------+------||------+------+------+------+------+--------|
        | LShift |   Z  |   X  |   C  |   F  |   J  ||   K  |   P  |   ,  |   .  |   /  | RShift |
        `--------+------+------+------+------+------'`------+------+------+------+------+--------'
                 |   `  |   [  | Left | Rght |              |  Dn  |  Up  |   ]  |   \  |
                 `---------------------------'              `---------------------------'
                                   ,----------------.,----------------.
                                   | LCtl  |  LAlt  ||  LAlt  | RCtl  |
                            ,------|-------|--------||--------+-------+-------.
                            |      |       |  RGUI  ||  RGUI  |       |       |
                            | BkSp |  ESC  |--------||--------| Enter | Space |
                            |      |       | MO(L2) || MO(L2) |       |       |
                            `-----------------------'`------------------------'

        L1 QWERTY layer:
        ,-------------------------------------------.,-------------------------------------------.
        | Del    |   1  |   3  |   5  |   7  |   9  ||   0  |   8  |   6  |   4  |   2  |   -    |
        |--------+------+------+------+------+------||------+------+------+------+------+--------|
        | Tab    |   Q  |   W  |   E  |   R  |   T  ||   Y  |   U  |   I  |   O  |   P  |   =    |
        |--------+------+------+------+------+------||------+------+------+------+------+--------|
        | ESC    |   A  |   S  |   D  |   F  |   G  ||   H  |   J  |   K  |   L  |   ;  |   '    |
        |--------+------+------+------+------+------||------+------+------+------+------+--------|
        | LShift |   Z  |   X  |   C  |   V  |   B  ||   N  |   M  |   ,  |   .  |   /  | RShift |
        `--------+------+------+------+------+------'`------+------+------+------+------+--------'
                 |   `  |   [  | Left | Rght |              |  Dn  |  Up  |   ]  |   \  |
                 `---------------------------'              `---------------------------'
                                   ,----------------.,----------------.
                                   | LCtl  |  LAlt  ||  LAlt  | RCtl  |
                            ,------|-------|--------||--------+-------+-------.
                            |      |       |  RGUI  ||  RGUI  |       |       |
                            | BkSp |  ESC  |--------||--------| Enter | Space |
                            |      |       | MO(L1) || MO(L2) |       |       |
                            `-----------------------'`------------------------'

        L2 Keypad + Media layer:
        ,-------------------------------------------.,-------------------------------------------.
        |        |      |      |      |      |      ||      | NmLk | KP = | KP / | KP * |        |
        |--------+------+------+------+------+------||------+------+------+------+------+--------|
        |        |      | Mute | Vol- | Vol+ |      ||      | KP 7 | KP 8 | KP 9 | KP - |        |
        |--------+------+------+------+------+------||------+------+------+------+------+--------|
        |        | Stop | Prev | Play | Next | Sel  ||      | KP 4 | KP 5 | KP 6 | KP + |        |
        |--------+------+------+------+------+------||------+------+------+------+------+--------|
        |        |      |      |      |      |      ||      | KP 1 | KP 2 | KP 3 |KP Ent|        |
        `--------+------+------+------+------+------'`------+------+------+------+------+--------'
                 |      |      |      |      |              |   (  |   )  | KP . |KP Ent|      |
                 `---------------------------'              `----------------------------------'
                                   ,----------------.,----------------.
                                   |       |        ||        |       |
                            ,------|-------|--------||--------+-------+-------.
                            |      |       |        ||        |       |       |
                            |      |       |--------||--------|KP Entr| KP 0  |
                            |      |       |        ||        |       |       |
                            `-----------------------'`------------------------'
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_CX] = LAYOUT(
           // Left Hand
           TO(_CX),  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,
           KC_DEL,   KC_1,    KC_3,    KC_5,    KC_7,    KC_9,
           KC_TAB,   KC_Q,    KC_G,    KC_M,    KC_L,    KC_W,
           KC_ESC,   KC_D,    KC_S,    KC_T,    KC_N,    KC_R,
           KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_F,    KC_J,
                     KC_GRV,  KC_LBRC, KC_LEFT, KC_RGHT,
           // Left Thumb
                     KC_LCTL, KC_LALT,
                              KC_RGUI,
           KC_BSPC,  KC_ESC,  MO(_KP),

           // Right Hand
           KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, TO(_QW), TO(_KP), TO(_KP),  RESET,
           KC_0,    KC_8,    KC_6,    KC_4,    KC_2,    KC_MINS,
           KC_B,    KC_Y,    KC_U,    KC_V,    KC_SCLN, KC_EQL,
           KC_I,    KC_A,    KC_E,    KC_O,    KC_H,    KC_QUOT,
           KC_K,    KC_P,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                    KC_DOWN,   KC_UP, KC_RBRC, KC_BSLS,
           // Right Thumb
           KC_RALT, KC_RCTL,
           KC_RGUI,
           MO(_KP), KC_ENT,  KC_SPC
    ),

[_QW] = LAYOUT(
           // Left Hand
           _______, _______, _______, _______, _______, _______, _______, _______, _______,
           _______, _______, _______, _______, _______, _______,
           _______,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,
           _______,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
           _______,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,
                    _______, _______, _______, _______,
           // Left Thumb
                    _______, _______,
                             _______,
           _______, _______, _______,

           // Right Hand
           _______, _______, _______, _______, _______, _______, _______, _______, _______,
           _______, _______, _______, _______, _______, _______,
           KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    _______,
           KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, _______,
           KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, _______,
                    _______, _______, _______, _______,
           // Right Thumb
           _______, _______,
           _______,
           _______, _______, _______
    ),

[_KP] = LAYOUT(
           // Left Hand
           _______, _______, _______, _______, _______, _______, _______, _______, _______,
           _______, _______, _______, _______, _______, _______,
           _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______,
           _______, KC_MSTP, KC_MPRV, KC_MPLY, KC_MNXT, KC_MSEL,
           _______, _______, _______, _______, _______, _______,
                    _______, _______, _______, _______,
           // Left Thumb
                    _______, _______,
                             _______,
           _______, _______, _______,

           // Right Hand */
           _______, _______, _______, _______, _______, _______, _______, _______, _______,
           _______, KC_NLCK, KC_PEQL, KC_PSLS, KC_PAST, _______,
           _______, KC_P7,   KC_P8,   KC_P9,   KC_PMNS, _______,
           _______, KC_P4,   KC_P5,   KC_P6,   KC_PPLS, _______,
           _______, KC_P1,   KC_P2,   KC_P3,   KC_PENT, _______,
                    KC_LPRN, KC_RPRN, KC_PDOT, KC_PENT,
           // Right Thumb
           _______, _______,
           _______,
           _______, KC_PENT, KC_P0
    )

};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch(id) {
    case _CX:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_CX);
      }
      break;
    case _QW:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QW);
      }
      break;
    }
    return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};
