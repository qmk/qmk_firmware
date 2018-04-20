#include "../../m6_a.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum layers {
  _LAYER0,
  _LAYER1,
  _LAYER2
};

enum custom_keycodes {
  GIT_ADD = SAFE_RANGE,
  GIT_COMMIT,
  GIT_PUSH,
  MUTE,
  DEAFEN
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	if (record->event.pressed) {
		switch(keycode) {
			case GIT_ADD:
				SEND_STRING("git add ."SS_TAP(X_ENTER));
        break;
      case GIT_COMMIT:
        SEND_STRING("git commit -m "SS_DOWN(X_LSHIFT)SS_TAP(X_QUOTE)SS_UP(X_LSHIFT));
        break;
      case GIT_PUSH:
        SEND_STRING("git push"SS_TAP(X_ENTER));
        break;
      case MUTE:
        SEND_STRING(SS_LGUI(SS_LSFT("M")));
        break;
      case DEAFEN:
        SEND_STRING(SS_LGUI(SS_LSFT("D")));
        break;
      return false;
		}
	}
	return true;
};

#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_LAYER0] = KEYMAP(
    MUTE,    DEAFEN,     TO(_LAYER1),
    GIT_ADD, GIT_COMMIT, GIT_PUSH
  ),
  [_LAYER1] = KEYMAP(
    KC_VOLD, KC_VOLU, TO(_LAYER2),
    KC_MRWD, KC_MPLY, KC_MNXT
  ),
  [_LAYER2] = KEYMAP(
    KC_ESC,  KC_UP,   TO(_LAYER0),
    KC_Z,    KC_X,    KC_SPACE
  )
};

void matrix_init_user(void) {
  #ifdef BACKLIGHT_ENABLE
    backlight_level(0);
  #endif
}
