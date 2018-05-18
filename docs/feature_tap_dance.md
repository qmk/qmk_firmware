# Tap Dance: A Single Key Can Do 3, 5, or 100 Different Things

<!-- FIXME: Break this up into multiple sections -->

Hit the semicolon key once, send a semicolon. Hit it twice, rapidly -- send a colon. Hit it three times, and your keyboard's LEDs do a wild dance. That's just one example of what Tap Dance can do. It's one of the nicest community-contributed features in the firmware, conceived and created by [algernon](https://github.com/algernon) in [#451](https://github.com/qmk/qmk_firmware/pull/451). Here's how algernon describes the feature:

With this feature one can specify keys that behave differently, based on the amount of times they have been tapped, and when interrupted, they get handled before the interrupter.

To make it clear how this is different from `ACTION_FUNCTION_TAP`, lets explore a certain setup! We want one key to send `Space` on single tap, but `Enter` on double-tap.

With `ACTION_FUNCTION_TAP`, it is quite a rain-dance to set this up, and has the problem that when the sequence is interrupted, the interrupting key will be send first. Thus, `SPC a` will result in `a SPC` being sent, if they are typed within `TAPPING_TERM`. With the tap dance feature, that'll come out as `SPC a`, correctly.

The implementation hooks into two parts of the system, to achieve this: into `process_record_quantum()`, and the matrix scan. We need the latter to be able to time out a tap sequence even when a key is not being pressed, so `SPC` alone will time out and register after `TAPPING_TERM` time.

But lets start with how to use it, first!

First, you will need `TAP_DANCE_ENABLE=yes` in your `rules.mk`, because the feature is disabled by default. This adds a little less than 1k to the firmware size. Next, you will want to define some tap-dance keys, which is easiest to do with the `TD()` macro, that - similar to `F()`, takes a number, which will later be used as an index into the `tap_dance_actions` array.

This array specifies what actions shall be taken when a tap-dance key is in action. Currently, there are three possible options:

* `ACTION_TAP_DANCE_DOUBLE(kc1, kc2)`: Sends the `kc1` keycode when tapped once, `kc2` otherwise. When the key is held, the appropriate keycode is registered: `kc1` when pressed and held, `kc2` when tapped once, then pressed and held.
* `ACTION_TAP_DANCE_DUAL_ROLE(kc, layer)`: Sends the `kc` keycode when tapped once, or moves to `layer`. (this functions like the `TO` layer keycode).
* `ACTION_TAP_DANCE_FN(fn)`: Calls the specified function - defined in the user keymap - with the final tap count of the tap dance action.
* `ACTION_TAP_DANCE_FN_ADVANCED(on_each_tap_fn, on_dance_finished_fn, on_dance_reset_fn)`: Calls the first specified function - defined in the user keymap - on every tap, the second function on when the dance action finishes (like the previous option), and the last function when the tap dance action resets.
** `ACTION_TAP_DANCE_FN_ADVANCED_TIME(on_each_tap_fn, on_dance_finished_fn, on_dance_reset_fn, tap_specific_tapping_term)`: This functions identically to the `ACTION_TAP_DANCE_FN_ADVANCED` function, but uses a custom tapping term for it, instead of the predefined `TAPPING_TERM`.

The first option is enough for a lot of cases, that just want dual roles. For example, `ACTION_TAP_DANCE_DOUBLE(KC_SPC, KC_ENT)` will result in `Space` being sent on single-tap, `Enter` otherwise.

And that's the bulk of it!

And now, on to the explanation of how it works!

The main entry point is `process_tap_dance()`, called from `process_record_quantum()`, which is run for every keypress, and our handler gets to run early. This function checks whether the key pressed is a tap-dance key. If it is not, and a tap-dance was in action, we handle that first, and enqueue the newly pressed key. If it is a tap-dance key, then we check if it is the same as the already active one (if there's one active, that is). If it is not, we fire off the old one first, then register the new one. If it was the same, we increment the counter and the timer.

This means that you have `TAPPING_TERM` time to tap the key again, you do not have to input all the taps within that timeframe. This allows for longer tap counts, with minimal impact on responsiveness.

Our next stop is `matrix_scan_tap_dance()`. This handles the timeout of tap-dance keys.

For the sake of flexibility, tap-dance actions can be either a pair of keycodes, or a user function. The latter allows one to handle higher tap counts, or do extra things, like blink the LEDs, fiddle with the backlighting, and so on. This is accomplished by using an union, and some clever macros.

# Examples

## Simple Example

Here's a simple example for a single definition:

1. In your `rules.mk`, add `TAP_DANCE_ENABLE = yes`
2. In your `config.h` (which you can copy from `qmk_firmware/keyboards/planck/config.h` to your keymap directory), add `#define TAPPING_TERM 200`
3. In your `keymap.c` file, define the variables and definitions, then add to your keymap:

```c
//Tap Dance Declarations
enum {
  TD_ESC_CAPS = 0
};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Esc, twice for Caps Lock
  [TD_ESC_CAPS]  = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS)
// Other declarations would go here, separated by commas, if you have them
};

//In Layer declaration, add tap dance item in place of a key code
TD(TD_ESC_CAPS)
```

## Complex Examples

This section details several complex tap dance examples.
All the enums used in the examples are declared like this:

```c
// Enums defined for all examples:
enum {
 CT_SE = 0,
 CT_CLN,
 CT_EGG,
 CT_FLSH,
 X_TAP_DANCE
};
```
### Example 1: Send `:` on Single Tap, `;` on Double Tap
```c
void dance_cln_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code (KC_RSFT);
    register_code (KC_SCLN);
  } else {
    register_code (KC_SCLN);
  }
}

void dance_cln_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (KC_RSFT);
    unregister_code (KC_SCLN);
  } else {
    unregister_code (KC_SCLN);
  }
}

//All tap dance functions would go here. Only showing this one.
qk_tap_dance_action_t tap_dance_actions[] = {
 [CT_CLN] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_cln_finished, dance_cln_reset)
};
```
### Example 2: Send "Safety Dance!" After 100 Taps
```c
void dance_egg (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count >= 100) {
    SEND_STRING ("Safety dance!");
    reset_tap_dance (state);
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
 [CT_EGG] = ACTION_TAP_DANCE_FN (dance_egg)
};
```

### Example 3: Turn LED Lights On Then Off, One at a Time

```c
// on each tap, light up one led, from right to left
// on the forth tap, turn them off from right to left
void dance_flsh_each(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
  case 1:
    ergodox_right_led_3_on();
    break;
  case 2:
    ergodox_right_led_2_on();
    break;
  case 3:
    ergodox_right_led_1_on();
    break;
  case 4:
    ergodox_right_led_3_off();
    _delay_ms(50);
    ergodox_right_led_2_off();
    _delay_ms(50);
    ergodox_right_led_1_off();
  }
}

// on the fourth tap, set the keyboard on flash state
void dance_flsh_finished(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count >= 4) {
    reset_keyboard();
    reset_tap_dance(state);
  }
}

// if the flash state didn't happen, then turn off LEDs, left to right
void dance_flsh_reset(qk_tap_dance_state_t *state, void *user_data) {
  ergodox_right_led_1_off();
  _delay_ms(50);
  ergodox_right_led_2_off();
  _delay_ms(50);
  ergodox_right_led_3_off();
}

//All tap dances now put together. Example 3 is "CT_FLASH"
qk_tap_dance_action_t tap_dance_actions[] = {
  [CT_SE]  = ACTION_TAP_DANCE_DOUBLE (KC_SPC, KC_ENT)
 ,[CT_CLN] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_cln_finished, dance_cln_reset)
 ,[CT_EGG] = ACTION_TAP_DANCE_FN (dance_egg)
 ,[CT_FLSH] = ACTION_TAP_DANCE_FN_ADVANCED (dance_flsh_each, dance_flsh_finished, dance_flsh_reset)
};
```

### Example 4: 'Quad Function Tap-Dance'

By [DanielGGordon](https://github.com/danielggordon)

Allow one key to have 4 (or more) functions, depending on number of presses, and if the key is held or tapped.
Below is a specific example:
*  Tap = Send `x`
*  Hold = Send `Control`
*  Double Tap = Send `Escape`
*  Double Tap and Hold = Send `Alt`

## Setup

You will need a few things that can be used for 'Quad Function Tap-Dance'. The suggested setup is to create a user directory for yourself. This directory will contain rules.mk `<your_name>.c` and `<your_name>.h`. This directory should be called `<your_name>`, and located in the top level `users` directory. There should already be a few examples to look at there.

### In `/qmk_firmware/users/<your_name>/rules.mk`

Put the following:
```c
TAP_DANCE_ENABLE = yes
SRC += your_name.c
```

Pretty simple. It is a nice way to keep some rules common on all your keymaps.


### In `/qmk_firmware/users/<your_name>/<you_name>.h`

You will need a few things in this file:

```c
#ifndef YOUR_NAME
#define YOUR_NAME

#include "quantum.h"
#include "process_keycode/process_tap_dance.h"


typedef struct {
  bool is_press_action;
  int state;
} xtap;

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  DOUBLE_SINGLE_TAP = 5, //send two single taps
  TRIPLE_TAP = 6,
  TRIPLE_HOLD = 7
};

//Tap dance enums
enum {
    CTL_X = 0,
    SOME_OTHER_DANCE
}

int cur_dance (qk_tap_dance_state_t *state);

//for the x tap dance. Put it here so it can be used in any keymap
void x_finished (qk_tap_dance_state_t *state, void *user_data);
void x_reset (qk_tap_dance_state_t *state, void *user_data);
```

### In `/qmk_firmware/users/<your_name>/<your_name>.c`

And then in your user's `.c` file you implement the functions above:

```c
#include "gordon.h"
#include "quantum.h"
#include "action.h"
#include "process_keycode/process_tap_dance.h"

/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicitive that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */
int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed)  return SINGLE_TAP;
    //key has not been interrupted, but they key is still held. Means you want to send a 'HOLD'.
    else return SINGLE_HOLD;
  }
  else if (state->count == 2) {
    /*
     * DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
     * action when hitting 'pp'. Suggested use case for this return value is when you want to send two
     * keystrokes of the key, and not the 'double tap' action/macro.
    */
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  //Assumes no one is trying to type the same letter three times (at least not quickly).
  //If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
  //an exception here to return a 'TRIPLE_SINGLE_TAP', and define that enum just like 'DOUBLE_SINGLE_TAP'
  if (state->count == 3) {
    if (state->interrupted || !state->pressed)  return TRIPLE_TAP;
    else return TRIPLE_HOLD;
  }
  else return 8; //magic number. At some point this method will expand to work for more presses
}

//instanalize an instance of 'tap' for the 'x' tap dance.
static tap xtap_state = {
  .is_press_action = true,
  .state = 0
};

void x_finished (qk_tap_dance_state_t *state, void *user_data) {
  xtap_state.state = cur_dance(state);
  switch (xtap_state.state) {
    case SINGLE_TAP: register_code(KC_X); break;
    case SINGLE_HOLD: register_code(KC_LCTRL); break;
    case DOUBLE_TAP: register_code(KC_ESC); break;
    case DOUBLE_HOLD: register_code(KC_LALT); break;
    case DOUBLE_SINGLE_TAP: register_code(KC_X); unregister_code(KC_X); register_code(KC_X);
    //Last case is for fast typing. Assuming your key is `f`:
    //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
  }
}

void x_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (xtap_state.state) {
    case SINGLE_TAP: unregister_code(KC_X); break;
    case SINGLE_HOLD: unregister_code(KC_LCTRL); break;
    case DOUBLE_TAP: unregister_code(KC_ESC); break;
    case DOUBLE_HOLD: unregister_code(KC_LALT);
    case DOUBLE_SINGLE_TAP: unregister_code(KC_X);
  }
  xtap_state.state = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [X_CTL]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL,x_finished, x_reset)
};
```

And then simply use TD(X_CTL) anywhere in your keymap.
