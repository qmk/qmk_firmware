#include "lets_split.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _NORMAN 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3

// To be used in process_record_user
enum custom_keycodes {
  NORMAN = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  SH_SUDO,
  SH_GOUP,
  SH_TERM,
  SPOT,
  SLACK,
  OUTLOOK,
  CHROME
};

// Fillers (to make layering more clear)
#define _______ KC_TRNS
#define XXXXXXX KC_NO

// Mod taps
#define SFT_ENT    SFT_T(KC_ENT)	// Tap for Enter, hold for Shift
#define CTL_ESC    CTL_T(KC_ESC)	// Tap for Escape, hold for Control

// Custom macros
#define SCN_SHT    LSFT(LGUI(KC_4))	// Take a screenshot (MacOS)
#define SCN_LCK    LCTL(LGUI(KC_Q))	// Lock screen (MacOS)
#define SH_HOME    LCTL(KC_A)		// Go to start of line
#define SH_END     LCTL(KC_E)		// Go to end of line
#define SH_RSCH    LCTL(KC_R)		// Search command history
#define SH_CLRH    LCTL(KC_U)		// Erase to beginning of line
#define SH_CLRE    LCTL(KC_K)		// Erase to end of line

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Norman
 * ,-----------------------------------------. ,-----------------------------------------.
 * |  Tab |   Q  |   W  |   D  |   F  |   K  | |   J  |   U  |   R  |   L  |   ;  | Bksp |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * |CtlEsc|   A  |   S  |   E  |   T  |   G  | |   Y  |   N  |   I  |   O  |   H  |  '   |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  | |   P  |   M  |   ,  |   .  |   /  |SftEnt|
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * | Lock | Home |  End | Alt  | Lower| GUI  | | Space| Raise| Left | Down |  Up  | Right|
 * `-----------------------------------------' `-----------------------------------------'
 */
[_NORMAN] = KEYMAP( \
  KC_TAB,  KC_Q,    KC_W,    KC_D,    KC_F,  KC_K,    KC_J,   KC_U,  KC_R,    KC_L,    KC_SCLN, KC_BSPC, \
  CTL_ESC, KC_A,    KC_S,    KC_E,    KC_T,  KC_G,    KC_Y,   KC_N,  KC_I,    KC_O,    KC_H,    KC_QUOT, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,  KC_B,    KC_P,   KC_M,  KC_COMM, KC_DOT,  KC_SLSH, SFT_ENT, \
  SCN_LCK, KC_HOME, KC_END,  KC_LALT, LOWER, KC_LGUI, KC_SPC, RAISE, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Lower
 * ,-----------------------------------------. ,-----------------------------------------.
 * |  Tab |  F1  |  F2  |  F3  |  F4  |      | |NumLck|   7  |   8  |   9  |   =  | Bksp |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * |CtlEsc|  F5  |  F6  |  F7  |  F8  |      | |   *  |   4  |   5  |   6  |   +  |  Del |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * | Shift|  F9  |  F10 |  F11 |  F12 |      | |   /  |   1  |   2  |   3  |   -  |SftEnt|
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * | Lock | Home |  End |  Alt | Lower|  GUI | |   .  | Raise|   0  | Spot |Chrome|      |
 * `-----------------------------------------' `-----------------------------------------'
 */
[_LOWER] = KEYMAP( \
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   XXXXXXX, KC_NLCK, KC_P7,   KC_P8, KC_P9, KC_PEQL, _______, \
  _______, KC_F5,   KC_F6,   KC_F8,   KC_F9,   XXXXXXX, KC_PAST, KC_P4,   KC_P5, KC_P6, KC_PPLS, KC_DEL,  \
  _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  XXXXXXX, KC_PSLS, KC_P1,   KC_P2, KC_P3, KC_PMNS, _______, \
  _______, _______, _______, _______, _______, _______, KC_PDOT, _______, KC_P0, SPOT,  CHROME,  XXXXXXX
),

/* Raise
 * ,-----------------------------------------. ,-----------------------------------------.
 * |  Tab |   !  |   @  |   #  |   $  |   %  | |   ^  |   &  |   *  |   (  |   )  |  Del |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * |CtlEsc| Sudo | UpDir| Slack| Term | OutLk| |   =  |   -  |   \  |   [  |   ]  |   `  |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * | Shift|ClrHom|ClrEnd|ShHome| ShEnd|Search| | Play | Mute | VolDn| VolUp|ScnSht|SftEnt|
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * | Lock | Home |  End |  Alt | Lower|  GUI | | Space| Raise| Left | Down |  Up  | Right|
 * `-----------------------------------------' `-----------------------------------------'
 */
[_RAISE] = KEYMAP( \
  _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,  \
  _______, SH_SUDO, SH_GOUP, SLACK,   SH_TERM, OUTLOOK,    KC_EQL,  KC_MINS, KC_BSLS, KC_LBRC, KC_RBRC, KC_GRV,  \
  _______, SH_CLRH, SH_CLRE, SH_HOME, SH_END,  SH_RSCH, KC_MPLY, KC_MUTE, KC_VOLD, KC_VOLU, SCN_SHT, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------. ,-----------------------------------------.
 * |      |      |      |      |      |      | |      |      |      |      | Reset|      |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * |      |      |      |      | AudOn|AudOff| |      |Norman|      |      |      |      |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * |      |      |      |      |      |      | |      |      |      |      |      |      |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * |      |      |      |      | Lower|      | |      | Raise|      |      |      |      |
 * `-----------------------------------------' `-----------------------------------------'
 */
[_ADJUST] = KEYMAP( \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RESET,   XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, AU_ON,   AU_OFF,  XXXXXXX, NORMAN,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
)

};

#ifdef AUDIO_ENABLE
float tone_norman[][2] = SONG(QWERTY_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch(keycode) {
      case NORMAN:
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_norman);
        #endif
        persistent_default_layer_set(1UL<<_NORMAN);
        return false;
      case LOWER:
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
        return false;
      case RAISE:
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
        return false;
      case ADJUST:
        layer_on(_ADJUST);
        return false;
      case SH_SUDO:
        SEND_STRING("sudo !!"SS_TAP(X_ENTER));					// Elevate last command
        return false;
      case SH_GOUP:
        SEND_STRING("cd .."SS_TAP(X_ENTER));					// Go up a directory
        return false;
      case SH_TERM:
        SEND_STRING(SS_LGUI(SS_TAP(X_SPACE))"terminal"SS_TAP(X_ENTER));		// Open Terminal
        return false;
      case SPOT:
        SEND_STRING(SS_LGUI(SS_TAP(X_SPACE))"spotify app"SS_TAP(X_ENTER));	// Open Spotify
        return false;
      case SLACK:
        SEND_STRING(SS_LGUI(SS_TAP(X_SPACE))"slack"SS_TAP(X_ENTER));		// Open Slack
        return false;
      case OUTLOOK:
        SEND_STRING(SS_LGUI(SS_TAP(X_SPACE))"outlook"SS_TAP(X_ENTER));		// Open Outlook
        return false;
      case CHROME:
        SEND_STRING(SS_LGUI(SS_TAP(X_SPACE))"chrome"SS_TAP(X_ENTER));		// Open Chrome
    }
  } else {
    switch(keycode) {
      case LOWER:
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
        return false;
      case RAISE:
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
        return false;
      case ADJUST:
        layer_off(_ADJUST);
        return false;
    }
  }
  return true;
}
