// This is the personal keymap of Ian Sterling (@xyverz). It is based on the keymap by
// Chris Gerber (@gerbercj), with the addition of persistent layers like the Planck and
// Preonic keyboards by Jack Humbert.

#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum layer_names {
  _DVORAK,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum planck_keycodes {
  LOWER = SAFE_RANGE,
  RAISE,
  ADJUST
};

// Adding macros to make the keymaps below much easier to read.
#define SFTSCLN SFT_T(KC_SCLN)
#define SFTZED SFT_T(KC_Z)
#define ALTENT ALT_T(KC_ENT)
#define DELGUI GUI_T(KC_DEL)
#define ESCTRL CTL_T(KC_ESC)
#define TABALT ALT_T(KC_TAB)
#define ADJUST MO(_ADJUST)
#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define MACLOCK LGUI(LCTL(KC_Q))
#define WINLOCK LGUI(KC_L)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Dvorak Layer
	,----------------------------------.              ,----------------------------------.
	|   '  |   ,  |   .  |   P  |   Y  |              |   F  |   G  |   C  |   R  |   L  |
	|------+------+------+------+------|              |------+------+------+------+------|
	|   A  |   O  |   E  |   U  |   I  |              |   D  |   H  |   T  |   N  |   S  |
	|------+------+------+------+------|------.,------|------+------+------+------+------|
	|SFT/ ;|   Q  |   J  |   K  |   X  |Delete||Enter |   B  |   M  |   W  |   V  |SFT/ Z|
	|------+------+------+------+------| / GUI|| / ALT|------+------+------+------+------|
	|  Esc |  Tab |  GUI | LOWER| BkSp |------'`------|  Spc | RAISE|   -  |   /  |   \  |
	`----------------------------------'              `----------------------------------' */
  [_DVORAK] = LAYOUT(
    KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,                      KC_F,    KC_G,    KC_C,    KC_R,    KC_L   ,
    KC_A,    KC_O,    KC_E,    KC_U,    KC_I,                      KC_D,    KC_H,    KC_T,    KC_N,    KC_S   ,
    SFTSCLN, KC_Q,    KC_J,    KC_K,    KC_X,                      KC_B,    KC_M,    KC_W,    KC_V,    SFTZED ,
    ESCTRL,  TABALT,  KC_LGUI, LOWER,   KC_BSPC, DELGUI, ALTENT,  KC_SPC,  RAISE,   KC_MINS, KC_SLSH, KC_BSLS
  ),

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
  [_LOWER] = LAYOUT(
    KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
    KC_CAPS, _______, KC_UP,   _______, KC_HOME,                   KC_PGUP, _______, KC_PLUS, KC_LCBR, KC_RCBR,
    _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,                    KC_PGDN, KC_MUTE, KC_VOLD, KC_VOLU, _______,
    KC_TILD, _______, _______, _______, KC_DEL,  _______, _______, KC_INS,  ADJUST,  _______, _______, _______
  ),

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
  [_RAISE] = LAYOUT(
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0   ,
    KC_CAPS, _______, KC_UP,   _______, KC_HOME,                   KC_PGUP, _______, KC_EQL,  KC_LBRC, KC_RBRC,
    _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,                    KC_PGDN, KC_MPRV, KC_MPLY, KC_MNXT, _______,
    KC_GRV,  _______, _______, ADJUST,  KC_DEL,  _______, _______, KC_INS,  _______, _______, _______, _______
  ),

  /* ADJUST Layer
	,----------------------------------.              ,----------------------------------.
	|  F1  |  F2  |  F3  |  F4  |  F5  |              |  F6  |  F7  |  F8  |  F9  | F10  |
	|------+------+------+------+------|              |------+------+------+------+------|
	|  F11 |      |      |      |      |              |      | PrSc | ScLk | Paus | F12  |
	|------+------+------+------+------|------.,------|------+------+------+------+------|
	|      |      |      |      |      |      ||      |      |      |      |      |      |
	|------+------+------+------+------|MACLCK||WINLCK|------+------+------+------+------|
	|      |      |      |      |      |------'`------|      |      |      |      |QKBOOT|
	`----------------------------------'              `----------------------------------'*/
  [_ADJUST] = LAYOUT(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10 ,
    KC_F11,  _______, _______, _______, _______,                   _______, KC_PSCR, KC_SCRL, KC_PAUS, KC_F12 ,
    _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, MACLOCK, WINLOCK, _______, _______, _______, _______, QK_BOOT  
  ),
};