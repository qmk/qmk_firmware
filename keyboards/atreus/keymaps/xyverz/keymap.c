// This is the personal keymap of Ian Sterling (@xyverz). It is based on the keymap by
// Chris Gerber (@gerbercj), with the addition of persistent layers like the Planck and
// Preonic keyboards by Jack Humbert.

#include "atreus.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _DVORAK 0
#define _QWERTY 1
#define _COLEMAK 2
#define _DVORMAC 3
#define _LOWER 4
#define _RAISE 5
#define _ADJUST 16

enum planck_keycodes {
  DVORAK = SAFE_RANGE,
  QWERTY,
  COLEMAK,
  DVORMAC,
  LOWER,
  RAISE,
  BACKLIT
};

// Adding macros to make the keymaps below much easier to read.
#define SFTSCLN SFT_T(KC_SCLN)
#define SFTSLSH SFT_T(KC_SLSH)
#define SFTZED SFT_T(KC_Z)
#define ALTENT ALT_T(KC_ENT)
#define ESCTRL CTL_T(KC_ESC)
#define TABALT ALT_T(KC_TAB)

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Dvorak Layer
	,----------------------------------.              ,----------------------------------.
	|   '  |   ,  |   .  |   P  |   Y  |              |   F  |   G  |   C  |   R  |   L  |
	|------+------+------+------+------|              |------+------+------+------+------|
	|   A  |   O  |   E  |   U  |   I  |              |   D  |   H  |   T  |   N  |   S  |
	|------+------+------+------+------|------.,------|------+------+------+------+------|
	|SFT/ ;|   Q  |   J  |   K  |   X  | CTRL ||Alt / |   B  |   M  |   W  |   V  |SFT/ Z|
	|------+------+------+------+------|      ||Enter |------+------+------+------+------|
	|  Esc |  Tab |  GUI | LOWER| BkSp |------'`------|  Spc | RAISE|   -  |   /  |   \  |
	`----------------------------------'              `----------------------------------' */
  [_DVORAK] = {
    {KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    XXXXXXX, KC_F,    KC_G,    KC_C,    KC_R,    KC_L   },
    {KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    XXXXXXX, KC_D,    KC_H,    KC_T,    KC_N,    KC_S   },
    {SFTSCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_LCTL, KC_B,    KC_M,    KC_W,    KC_V,    SFTZED },
    {ESCTRL,  TABALT,  KC_LGUI, LOWER,   KC_BSPC, ALTENT,  KC_SPC,  RAISE,   KC_MINS, KC_SLSH, KC_BSLS}
  },

/* QWERTY Layer
	,----------------------------------.              ,----------------------------------.
	|   Q  |   W  |   E  |   R  |   T  |              |   Y  |   U  |   I  |   O  |   P  |
	|------+------+------+------+------|              |------+------+------+------+------|
	|   A  |   S  |   D  |   F  |   G  |              |   H  |   J  |   K  |   L  |   ;  |
	|------+------+------+------+------|------.,------|------+------+------+------+------|
	|SFT/ Z|   X  |   C  |   V  |   B  | CTRL ||Alt / |   N  |   M  |   ,  |   .  |SFT/ /|
	|------+------+------+------+------|      ||Enter |------+------+------+------+------|
	|  Esc |  Tab |  GUI | LOWER| BkSp |------'`------|  Spc | RAISE|   -  |   '  |   \  |
	`----------------------------------'              `----------------------------------' */
  [_QWERTY] = {
    {KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    XXXXXXX, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P   },
    {KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    XXXXXXX, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN},
    {SFTZED,  KC_X,    KC_C,    KC_V,    KC_B,    KC_LCTL, KC_N,    KC_M,    KC_COMM, KC_DOT,  SFTSLSH},
    {ESCTRL,  TABALT,  KC_LGUI, LOWER,   KC_BSPC, ALTENT,  KC_SPC,  RAISE,   KC_MINS, KC_QUOT, KC_BSLS}
  },

/* Colemak Layer
	,----------------------------------.              ,----------------------------------.
	|   Q  |   W  |   F  |   P  |   G  |              |   J  |   L  |   U  |   Y  |   L  |
	|------+------+------+------+------|              |------+------+------+------+------|
	|   A  |   R  |   S  |   T  |   D  |              |   H  |   N  |   E  |   I  |   S  |
	|------+------+------+------+------|------.,------|------+------+------+------+------|
	|SFT/ Z|   X  |   C  |   V  |   B  | CTRL ||Alt / |   K  |   M  |   ,  |   .  |SFT/ /|
	|------+------+------+------+------|      ||Enter |------+------+------+------+------|
	|  Esc |  Tab |  GUI | LOWER| BkSp |------'`------|  Spc | RAISE|   -  |   '  |   \  |
	`----------------------------------'              `----------------------------------'*/
  [_COLEMAK] = {
    {KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    XXXXXXX, KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN},
    {KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    XXXXXXX, KC_H,    KC_N,    KC_E,    KC_I,    KC_O   },
    {SFTZED,  KC_X,    KC_C,    KC_V,    KC_B,    KC_LCTL, KC_K,    KC_M,    KC_COMM, KC_DOT,  SFTSLSH},
    {ESCTRL,  TABALT,  KC_LGUI, LOWER,   KC_BSPC, ALTENT,  KC_SPC,  RAISE,   KC_MINS, KC_QUOT, KC_BSLS}
  },

/* Dvorak Layer with Command key on left thumb instead of Control
	,----------------------------------.              ,----------------------------------.
	|   '  |   ,  |   .  |   P  |   Y  |              |   F  |   G  |   C  |   R  |   L  |
	|------+------+------+------+------|              |------+------+------+------+------|
	|   A  |   O  |   E  |   U  |   I  |              |   D  |   H  |   T  |   N  |   S  |
	|------+------+------+------+------|------.,------|------+------+------+------+------|
	|SFT/ ;|   Q  |   J  |   K  |   X  | CMD  ||Alt / |   B  |   M  |   W  |   V  |SFT/ Z|
	|------+------+------+------+------|      ||Enter |------+------+------+------+------|
	|  Esc |  Tab |  GUI | LOWER| BkSp |------'`------|  Spc | RAISE|   -  |   /  |   \  |
	`----------------------------------'              `----------------------------------' */
  [_DVORMAC] = {
    {KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    XXXXXXX, KC_F,    KC_G,    KC_C,    KC_R,    KC_L   },
    {KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    XXXXXXX, KC_D,    KC_H,    KC_T,    KC_N,    KC_S   },
    {SFTSCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_LGUI, KC_B,    KC_M,    KC_W,    KC_V,    SFTZED },
    {ESCTRL,  TABALT,  KC_LGUI, LOWER,   KC_BSPC, ALTENT,  KC_SPC,  RAISE,   KC_MINS, KC_SLSH, KC_BSLS}
  },

/* LOWER Layer
	,----------------------------------.              ,----------------------------------.
	|   !  |   @  |   #  |   $  |   %  |              |   ^  |   &  |   *  |   (  |   )  |
	|------+------+------+------+------|              |------+------+------+------+------|
	| CAPS |      |  UP  |      | Home |              | PgDn |      |   +  |   {  |   }  |
	|------+------+------+------+------|------.,------|------+------+------+------+------|
	|      | Left | Down | Right| End  |      ||      | PgUp | Mute | Vol- | Vol+ |      |
	|------+------+------+------+------|      ||      |------+------+------+------+------|
	|   ~  |      |      |      | Del  |------'`------| Ins  |      |      |      |      |
	`----------------------------------'              `----------------------------------'*/
  [_LOWER] = {
    {KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, XXXXXXX, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN},
    {KC_CAPS, _______, KC_UP,   _______, KC_HOME, XXXXXXX, KC_PGUP, _______, KC_PLUS, KC_LCBR, KC_RCBR},
    {_______, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,  _______, KC_PGDN, KC_MUTE, KC_VOLD, KC_VOLU, _______},
    {KC_TILD, _______, _______, _______, KC_DEL,  _______, KC_INS,  _______, _______, _______, _______}
  },

/* RAISE Layer
	,----------------------------------.              ,----------------------------------.
	|   1  |   2  |   3  |   4  |   5  |              |   6  |   7  |   8  |   9  |   0  |
	|------+------+------+------+------|              |------+------+------+------+------|
	| CAPS |      |  UP  |      | Home |              | PgDn |      |   =  |   [  |   ]  |
	|------+------+------+------+------|------.,------|------+------+------+------+------|
	|      | Left | Down | Right| End  |      ||      | PgUp | Prev | Play | Next |      |
	|------+------+------+------+------|      ||      |------+------+------+------+------|
	|   `  |      |      |      | Del  |------'`------| Ins  |      |      |      |      |
	`----------------------------------'              `----------------------------------'*/
  [_RAISE] = {
    {KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    XXXXXXX, KC_6,    KC_7,    KC_8,    KC_9,    KC_0   },
    {KC_CAPS, _______, KC_UP,   _______, KC_HOME, XXXXXXX, KC_PGUP, _______, KC_EQL,  KC_LBRC, KC_RBRC},
    {_______, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,  _______, KC_PGDN, KC_MPRV, KC_MPLY, KC_MNXT, _______},
    {KC_GRV,  _______, _______, _______, KC_DEL,  _______, KC_INS,  _______, _______, _______, _______}
  },

/* ADJUST Layer
	,----------------------------------.              ,----------------------------------.
	|  F1  |  F2  |  F3  |  F4  |  F5  |              |  F6  |  F7  |  F8  |  F9  | F10  |
	|------+------+------+------+------|              |------+------+------+------+------|
	|  F11 |      |      |      |      |              |      | PrSc | ScLk | Paus | F12  |
	|------+------+------+------+------|------.,------|------+------+------+------+------|
	|      |QWERTY|COLEMK|DVORAK|DVORMC|      ||      |      |      |      |      |      |
	|------+------+------+------+------|      ||      |------+------+------+------+------|
	|      |      |      |      |      |------'`------|      |      |      |      | RESET|
	`----------------------------------'              `----------------------------------'*/
  [_ADJUST] = {
    {KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   XXXXXXX, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10 },
    {KC_F11,  _______, _______, _______, _______, XXXXXXX, _______, KC_PSCR, KC_SLCK, KC_PAUS, KC_F12 },
    {_______, QWERTY,  COLEMAK, DVORAK,  DVORMAC, _______, _______, _______, _______, _______, _______},
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RESET  }
  }

};

const uint16_t PROGMEM fn_actions[] = {

};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
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
        case DVORAK:
          if (record->event.pressed) {
            persistent_default_layer_set(1UL<<_DVORAK);
          }
          return false;
          break;
        case DVORMAC:
          if (record->event.pressed) {
            persistent_default_layer_set(1UL<<_DVORMAC);
          }
          return false;
          break;
        case LOWER:
          if (record->event.pressed) {
            layer_on(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
        case RAISE:
          if (record->event.pressed) {
            layer_on(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
      }
    return true;
};
