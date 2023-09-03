#ifndef USERS_ZUNGER_LANGUAGE_H__
#define USERS_ZUNGER_LANGUAGE_H__

#include QMK_KEYBOARD_H

// A Language is defined by a 2D array, keyed by keycode and (unshifted, shifted).
// Its array elements should either be Unicode values, or the constants XXXXXX (
// to indicate a dead key) or ______ (to indicate fallthrough to the ordinary behavior
// of the keycode). Note that these have 6 letters, to line up with 0xABCD, and to
// avoid conflict with similar-meaning symbols for keycodes. The default is fallthrough.

#define ______ 0x0000
#define XXXXXX 0x0001

#define MAX_MAPPABLE_CHAR KC_CAPS_LOCK

typedef const uint16_t PROGMEM Language[MAX_MAPPABLE_CHAR][2];

// Standard languages that we have defined. Each of these uses a QWERTY-like keymapping,
// rather than the "native" one used in the respective countries, for ease of typing in
// a primarily QWERTY environment. Exact keymappings are chosen to match my personal
// idiosyncrasies.
extern Language greek;
extern Language symbol;
extern Language yiddish;

// To add a language to your keyboard, you'll need to use tapdances. The steps are:
// (1) Make sure you have the appropriate Language variable defined with your data.
// (2) In your rules.mk, set TAP_DANCE_ENABLE = yes.
// (3) Create an enum of tapdance codes for your keyboard if you don't already have
//     one. Add a value for each language.
// (4) Add an entry to tap_dance_actions[]:
//     tap_dance_action_t tap_dance_actions[] = {
//       [MY_CODE] = LANGUAGE_TAP_DANCE(my_language),
//     }
// (5) On your keymap, set some key to be TD(MY_CODE). This key will be a modifier to
//     select the language when held, or a toggle into the language when double-tapped.
// (6) From process_record_user, call
//     if (!process_language_key(keycode, record)) return false;
#define LANGUAGE_TAP_DANCE(language) \
  { .fn = {NULL, lang_tap_dance_finished, lang_tap_dance_reset}, .user_data = language }

// The main handler function you ought to call that takes care of all the language logic.
bool process_language_key(uint16_t keycode, keyrecord_t *record);

// Implementation details
void lang_tap_dance_finished(tap_dance_state_t *state, Language *user_data);
void lang_tap_dance_reset(tap_dance_state_t *state, Language *user_data);

#endif  // USERS_ZUNGER_LANGUAGE_H__
