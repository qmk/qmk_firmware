#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#define _DVORAK 0 // Dvorak layer
#define _QWERTY 1 // Qwerty layer
#define _COLEMAK 2 // Colemak layer
#define _MEDIA 3 // Media Layer
#define _KEYPAD 4 // Keypad Layer

enum custom_keycodes {
  DVORAK = SAFE_RANGE,
  QWERTY,
  COLEMAK,
  MEDIA,
  KEYPAD
};

// Aliases to make the keymap more uniform
#define GUI_END GUI_T(KC_END)
#define MED_DEL LT(_MEDIA, KC_DEL)
#define KPD_ENT LT(_KEYPAD, KC_ENT)

/*

        Function Keys on All Layers (Keypad toggles):
	,-----------------------------------------------------------------.
	|  ESC |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   F7   |  F8   |
 	`-----------------------------------------------------------------'
        ,-----------------------------------------------------------------.
        |  F9  |  F10 |  F11 |  F12 | PScr | SLck | Paus | Keypad | RESET |
        `-----------------------------------------------------------------'

        Dvorak layer:
	,-------------------------------------------.,-------------------------------------------.
	|   ]    |   1  |   2  |   3  |   4  |   5  ||   6  |   7  |   8  |   9  |   0  |   [    |
	|--------+------+------+------+------+------||------+------+------+------+------+--------|
	| Tab    |   '  |   ,  |   .  |   P  |   Y  ||   F  |   G  |   C  |   R  |   L  |   \    |
	|--------+------+------+------+------+------||------+------+------+------+------+--------|
	| CapsLk |   A  |   O  |   E  |   U  |   I  ||   D  |   H  |   T  |   N  |   S  |   -    |
	|--------+------+------+------+------+------||------+------+------+------+------+--------|
	| LShift |   Z  |   X  |   C  |   V  |   X  ||   B  |   M  |   W  |   V  |   Z  | RShift |
	`--------+------+------+------+------+------'`------+------+------+------+------+--------'
	         |   `  |  INS | Left | Rght |              |  Up  |  Dn  |   /  |   =  |
	         `---------------------------'              `---------------------------'
	                             ,--------------.,--------------.
	                             | LCtl  | LAlt || RGUI | RCtl  |
	                      ,------|-------|------||------+-------+-------.
	                      |      |  Del  | Home || PgUp | Enter |       |
	                      | BkSp |   /   |------||------|   /   | Space |
	                      |      | Media | End  || PgDn | KeyPd |       |
	                      `---------------------'`----------------------'

        QWERTY layer:
	,-------------------------------------------.,-------------------------------------------.
	|   =    |   1  |   2  |   3  |   4  |   5  ||   6  |   7  |   8  |   9  |   0  |   -    |
	|--------+------+------+------+------+------||------+------+------+------+------+--------|
	| Tab    |   Q  |   W  |   E  |   R  |   T  ||   Y  |   U  |   I  |   O  |   P  |   \    |
	|--------+------+------+------+------+------||------+------+------+------+------+--------|
	| CapsLk |   A  |   S  |   D  |   F  |   G  ||   H  |   J  |   K  |   L  |   ;  |   '    |
	|--------+------+------+------+------+------||------+------+------+------+------+--------|
	| LShift |   Z  |   X  |   C  |   V  |   B  ||   N  |   M  |   ,  |   .  |   /  | RShift |
	`--------+------+------+------+------+------'`------+------+------+------+------+--------'
	         |   `  |  INS | Left | Rght |              |  Up  |  Dn  |   [  |   ]  |
	         `---------------------------'              `---------------------------'
	                             ,--------------.,--------------.
	                             | LCtl  | LAlt || RGUI | RCtl  |
	                      ,------|-------|------||------+-------+-------.
	                      |      |  Del  | Home || PgUp | Enter |       |
	                      | BkSp |   /   |------||------|   /   | Space |
	                      |      | Media | End  || PgDn | KeyPd |       |
	                      `---------------------'`----------------------'

        Colemak layer:
	,-------------------------------------------.,-------------------------------------------.
	|   =    |   1  |   2  |   3  |   4  |   5  ||   6  |   7  |   8  |   9  |   0  |   -    |
	|--------+------+------+------+------+------||------+------+------+------+------+--------|
	| Tab    |   Q  |   W  |   F  |   P  |   G  ||   J  |   L  |   U  |   Y  |   ;  |   \    |
	|--------+------+------+------+------+------||------+------+------+------+------+--------|
	| BkSpc  |   A  |   R  |   S  |   T  |   D  ||   H  |   N  |   E  |   I  |   O  |   '    |
	|--------+------+------+------+------+------||------+------+------+------+------+--------|
	| LShift |   Z  |   X  |   C  |   V  |   B  ||   K  |   M  |   ,  |   .  |   /  | RShift |
	`--------+------+------+------+------+------'`------+------+------+------+------+--------'
	         |   `  |  INS | Left | Rght |              |  Up  |  Dn  |   [  |   ]  |
	         `---------------------------'              `---------------------------'
	                             ,--------------.,--------------.
	                             | LCtl  | LAlt || RGUI | RCtl  |
	                      ,------|-------|------||------+-------+-------.
	                      |      |  Del  | Home || PgUp | Enter |       |
	                      | BkSp |   /   |------||------|   /   | Space |
	                      |      | Media | End  || PgDn | KeyPd |       |
	                      `---------------------'`----------------------'

        Media layer:
	,-------------------------------------------.,-------------------------------------------.
	|   F11  |  F1  |  F2  |  F3  |  F4  |  F5  ||  F6  |  F7  |  F8  |  F9  |  F10 |  F12   |
	|--------+------+------+------+------+------||------+------+------+------+------+--------|
	|        |      |      |      |      |      ||      |      |      |      |      |        |
	|--------+------+------+------+------+------||------+------+------+------+------+--------|
	|        |      | Mute | Vol- | Vol+ |      ||      |      |      |      |      |        |
	|--------+------+------+------+------+------||------+------+------+------+------+--------|
	|        | Stop | Prev | Play | Next | Sel  ||      |      |      |      |      |        |
	`--------+------+------+------+------+------'`------+------+------+------+------+--------'
	         |      |      |      |      |              |      |      |      |      |
	         `---------------------------'              `---------------------------'
	                              ,-------------.,-------------.
	                              |      |      ||      |      |
	                       ,------|------|------||------+------+------.
	                       |      |      |      ||      |      |      |
	                       |      |      |------||------|      |      |
	                       |      |      |      ||      |      |      |
	                       `--------------------'`--------------------'

        Keypad layer:
	,-------------------------------------------.,-------------------------------------------.
	| Power  |      |      |      |      |      ||      | NmLk | KP = | KP / | KP * |        |
	|--------+------+------+------+------+------||------+------+------+------+------+--------|
	| Sleep  |      |      |      |      |      ||      | KP 7 | KP 8 | KP 9 | KP - |        |
	|--------+------+------+------+------+------||------+------+------+------+------+--------|
	| Wake   |      | Mute | Vol- | Vol+ |      ||      | KP 4 | KP 5 | KP 6 | KP + |        |
	|--------+------+------+------+------+------||------+------+------+------+------+--------|
	|        | Stop | Prev | Play | Next | Sel  ||      | KP 1 | KP 2 | KP 3 |KP Ent|        |
	`--------+------+------+------+------+------'`------+------+------+------+------+--------'
	         |      |QWERTY|Colemk|Dvorak|              |      |      | KP . |KP Ent|
	         `---------------------------'              `---------------------------'
	                              ,-------------.,-------------.
	                              |      |      ||      |      |
	                       ,------|------|------||------+------+------.
	                       |      |      |      ||      |      |      |
	                       |      |      |------||------|      | KP 0 |
	                       |      |      |      ||      |      |      |
	                       `--------------------'`--------------------'
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_DVORAK] = LAYOUT (
           // Left Hand
           KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,
           KC_RBRC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,
           KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,
           KC_CAPS, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,
           KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,
                    KC_GRV,  KC_INS,  KC_LEFT, KC_RGHT,
           // Left Thumb
                    KC_LCTL, KC_LALT,
                             KC_HOME,
           KC_BSPC, MED_DEL, GUI_END,

           // Right Hand
           KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_SLCK, KC_PAUS, TG(_KEYPAD),  RESET,
           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_LBRC,
           KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_BSLS,
           KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS,
           KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT,
                    KC_UP,   KC_DOWN, KC_SLSH, KC_EQL,
           // Right Thumb
           KC_RGUI, KC_RCTL,
           KC_PGUP,
           KC_PGDN, KPD_ENT, KC_SPC
    ),

[_QWERTY] = LAYOUT (
           // Left Hand
           KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,
           KC_EQL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,
           KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,
           KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
           KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,
                    KC_GRV,  KC_INS,  KC_LEFT, KC_RGHT,
           // Left Thumb
                    KC_LCTL, KC_LALT,
                             KC_HOME,
           KC_BSPC, MED_DEL, KC_END,

           // Right Hand
           KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_SLCK, KC_PAUS, TG(_KEYPAD),  RESET,
           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS,
           KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL ,
           KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
           KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                    KC_UP,   KC_DOWN, KC_LBRC, KC_RBRC,
           // Right Thumb
           KC_RGUI, KC_RCTL,
           KC_PGUP,
           KC_PGDN, KPD_ENT, KC_SPC
    ),

[_COLEMAK] = LAYOUT (
           // Left Hand
           KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,
           KC_EQL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,
           KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,
           KC_BSPC, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,
           KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,
                    KC_GRV,  KC_INS,  KC_LEFT, KC_RGHT,
           // Left Thumb
                    KC_LCTL, KC_LALT,
                             KC_HOME,
           KC_BSPC, MED_DEL, KC_END,

           // Right Hand
           KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_SLCK, KC_PAUS, TG(_KEYPAD),  RESET,
           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
           KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_DEL,
           KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
           KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                    KC_UP,   KC_DOWN, KC_LBRC, KC_RBRC,
           // Right Thumb
           KC_RGUI, KC_RCTL,
           KC_PGUP,
           KC_PGDN, KPD_ENT, KC_SPC
    ),

[_MEDIA] = LAYOUT (
           // Left Hand
           _______, _______, _______, _______, _______, _______, _______, _______, _______,
           KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,
           _______, _______, _______, _______, _______, _______,
           _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______,
           _______, KC_MSTP, KC_MPRV, KC_MPLY, KC_MNXT, KC_MSEL,
                    _______, _______, _______, _______,
           // Left Thumb
                    _______, _______,
                             _______,
           _______, _______, _______,

           // Right Hand
           _______, _______, _______, _______, _______, _______, _______, _______, _______,
           KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12,
           _______, _______, _______, _______, _______, _______,
           _______, _______, _______, _______, _______, _______,
           _______, _______, _______, _______, _______, _______,
                    _______, _______, _______, _______,
           // Right Thumb
           _______, _______,
           _______,
           _______, _______, _______
    ),

[_KEYPAD] = LAYOUT (
           // Left Hand
           _______, _______, _______, _______, _______, _______, _______, _______, _______,
           KC_PWR,  _______, _______, _______, _______, _______,
           KC_SLEP, _______, _______, _______, _______, _______,
           KC_WAKE, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______,
           _______, KC_MSTP, KC_MPRV, KC_MPLY, KC_MNXT, KC_MSEL,
                    _______, QWERTY,  COLEMAK, DVORAK,
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
                    _______, _______, KC_PDOT, KC_PENT,
           // Right Thumb
           _______, _______,
           _______,
           _______, _______, KC_P0
    )

};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
        case DVORAK:
          if (record->event.pressed) {
            persistent_default_layer_set(1UL<<_DVORAK);
          }
          return false;
          break;
        case QWERTY:
          if (record->event.pressed) {
            persistent_default_layer_set(1UL<<_QWERTY);
          }
          return false;
          break;
        case COLEMAK:
          if (record->event.pressed) {
            persistent_default_layer_set(1UL<<_COLEMAK);
          }
          return false;
          break;
      }
    return true;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
};
