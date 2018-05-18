#include QMK_KEYBOARD_H
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

#define _DV 0 // Dvorak layer
#define _QW 1 // Qwerty layer
#define _CM 2 // Colemak layer
#define _MD 3 // Media Layer
#define _KP 4 // Keypad Layer

// Macro name shortcuts
#define DVORAK M(_DV)
#define QWERTY M(_QW)
#define COLEMAK M(_CM)

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

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
	|        |      |      |      |      |      ||      | Mute | Vol- | Vol+ |      |        |
	|--------+------+------+------+------+------||------+------+------+------+------+--------|
	|        |      |      |      |      |      || Stop | Prev | Play | Next | Sel  |        |
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
	| Wake   |      |QWERTY|Colemk|Dvorak|      ||      | KP 4 | KP 5 | KP 6 | KP + |        |
	|--------+------+------+------+------+------||------+------+------+------+------+--------|
	|        |      |      |      |      |      ||      | KP 1 | KP 2 | KP 3 |KP Ent|        |
	`--------+------+------+------+------+------'`------+------+------+------+------+--------'
	         |      |      |      |      |              |      |      | KP . |KP Ent|      |
	         `---------------------------'              `----------------------------------'
	                              ,-------------.,-------------.
	                              |      |      ||      |      |
	                       ,------|------|------||------+------+------.
	                       |      |      |      ||      |      |      |
	                       |      |      |------||------|      | KP 0 |
	                       |      |      |      ||      |      |      |
	                       `--------------------'`--------------------'
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_DV] = LAYOUT (
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
           KC_BSPC, LT(_MD, KC_DEL),  KC_END,

           // Right Hand
           KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_SLCK, KC_PAUS, TG(_KP),  RESET,
           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_LBRC,
           KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_BSLS,
           KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS,
           KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT,
                    KC_UP,   KC_DOWN, KC_SLSH, KC_EQL,
           // Right Thumb
           KC_RGUI, KC_RCTL,
           KC_PGUP,
           KC_PGDN, LT(_KP, KC_ENT),  KC_SPC
    ),

[_QW] = LAYOUT (
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
           KC_BSPC, LT(_MD, KC_DEL),  KC_END,

           // Right Hand
           KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_SLCK, KC_PAUS, TG(_KP),  RESET,
           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS,
           KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL ,
           KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
           KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                    KC_UP,   KC_DOWN, KC_LBRC, KC_RBRC,
           // Right Thumb
           KC_RGUI, KC_RCTL,
           KC_PGUP,
           KC_PGDN, LT(_KP, KC_ENT),  KC_SPC
    ),

[_CM] = LAYOUT (
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
           KC_BSPC, LT(_MD, KC_DEL),  KC_END,

           // Right Hand
           KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_SLCK, KC_PAUS, TG(_KP),  RESET,
           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
           KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_DEL,
           KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
           KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                    KC_UP,   KC_DOWN, KC_LBRC, KC_RBRC,
           // Right Thumb
           KC_RGUI, KC_RCTL,
           KC_PGUP,
           KC_PGDN, LT(_KP, KC_ENT),  KC_SPC
    ),

[_MD] = LAYOUT (
           // Left Hand
           _______, _______, _______, _______, _______, _______, _______, _______, _______,
           KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,
           _______, _______, _______, _______, _______, _______,
           _______, _______, _______, _______, _______, _______,
           _______, _______, _______, _______, _______, _______,
                    _______, _______, _______, _______,
           // Left Thumb
                    _______, _______,
                             _______,
           _______, _______, _______,

           // Right Hand
           _______, _______, _______, _______, _______, _______, _______, _______, _______,
           KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12,
           _______, _______, _______, _______, _______, _______,
           _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______,
           KC_MSTP, KC_MPRV, KC_MPLY, KC_MNXT, KC_MSEL, _______,
                    _______, _______, _______, _______,
           // Right Thumb
           _______, _______,
           _______,
           _______, _______, _______
    ),

[_KP] = LAYOUT (
           // Left Hand
           _______, _______, _______, _______, _______, _______, _______, _______, _______,
           KC_PWR,  _______, _______, _______, _______, _______,
           KC_SLEP, _______, _______, _______, _______, _______,
           KC_WAKE, _______, QWERTY,  COLEMAK, DVORAK,  _______,
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
                    _______, _______, KC_PDOT, KC_PENT,
           // Right Thumb
           _______, _______,
           _______,
           _______, _______, KC_P0
    )

};


const uint16_t PROGMEM fn_actions[] = {

};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
      switch(id) {
        case _DV:
          if (record->event.pressed) {
            persistent_default_layer_set(1UL<<_DV);
          }
          break;
        case _QW:
          if (record->event.pressed) {
            persistent_default_layer_set(1UL<<_QW);
          }
          break;
        case _CM:
          if (record->event.pressed) {
            persistent_default_layer_set(1UL<<_CM);
          }
          break;
      }
    return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};

void led_set_user(uint8_t usb_led) {
    if (usb_led & (1<<USB_LED_NUM_LOCK)) {
        PORTF |= (1<<2);
    } else {
        PORTF &= ~(1<<2);
    }
    if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
        PORTF |= (1<<3);
    } else {
        PORTF &= ~(1<<3);
    }
    if (usb_led & (1<<USB_LED_SCROLL_LOCK)) {
        PORTF |= (1<<1);
    } else {
        PORTF &= ~(1<<1);
    }
}
