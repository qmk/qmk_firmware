# Tap Dance: A single key can do 3, 5, or 100 different things

<!-- FIXME: Break this up into multiple sections -->

Hit the semicolon key once, send a semicolon. Hit it twice, rapidly -- send a colon. Hit it three times, and your keyboard's LEDs do a wild dance. That's just one example of what Tap Dance can do. It's one of the nicest community-contributed features in the firmware, conceived and created by [algernon](https://github.com/algernon) in [#451](https://github.com/qmk/qmk_firmware/pull/451). Here's how algernon describes the feature:

With this feature one can specify keys that behave differently, based on the amount of times they have been tapped, and when interrupted, they get handled before the interrupter.

To make it clear how this is different from `ACTION_FUNCTION_TAP`, lets explore a certain setup! We want one key to send `Space` on single tap, but `Enter` on double-tap.

With `ACTION_FUNCTION_TAP`, it is quite a rain-dance to set this up, and has the problem that when the sequence is interrupted, the interrupting key will be send first. Thus, `SPC a` will result in `a SPC` being sent, if they are typed within `TAPPING_TERM`. With the tap dance feature, that'll come out as `SPC a`, correctly.

The implementation hooks into two parts of the system, to achieve this: into `process_record_quantum()`, and the matrix scan. We need the latter to be able to time out a tap sequence even when a key is not being pressed, so `SPC` alone will time out and register after `TAPPING_TERM` time.

But lets start with how to use it, first!

First, you will need `TAP_DANCE_ENABLE=yes` in your `Makefile`, because the feature is disabled by default. This adds a little less than 1k to the firmware size. Next, you will want to define some tap-dance keys, which is easiest to do with the `TD()` macro, that - similar to `F()`, takes a number, which will later be used as an index into the `tap_dance_actions` array.

This array specifies what actions shall be taken when a tap-dance key is in action. Currently, there are three possible options:

* `ACTION_TAP_DANCE_DOUBLE(kc1, kc2)`: Sends the `kc1` keycode when tapped once, `kc2` otherwise. When the key is held, the appropriate keycode is registered: `kc1` when pressed and held, `kc2` when tapped once, then pressed and held.
* `ACTION_TAP_DANCE_FN(fn)`: Calls the specified function - defined in the user keymap - with the final tap count of the tap dance action.
* `ACTION_TAP_DANCE_FN_ADVANCED(on_each_tap_fn, on_dance_finished_fn, on_dance_reset_fn)`: Calls the first specified function - defined in the user keymap - on every tap, the second function on when the dance action finishes (like the previous option), and the last function when the tap dance action resets.

The first option is enough for a lot of cases, that just want dual roles. For example, `ACTION_TAP_DANCE(KC_SPC, KC_ENT)` will result in `Space` being sent on single-tap, `Enter` otherwise.

And that's the bulk of it!

And now, on to the explanation of how it works!

The main entry point is `process_tap_dance()`, called from `process_record_quantum()`, which is run for every keypress, and our handler gets to run early. This function checks whether the key pressed is a tap-dance key. If it is not, and a tap-dance was in action, we handle that first, and enqueue the newly pressed key. If it is a tap-dance key, then we check if it is the same as the already active one (if there's one active, that is). If it is not, we fire off the old one first, then register the new one. If it was the same, we increment the counter and the timer.

This means that you have `TAPPING_TERM` time to tap the key again, you do not have to input all the taps within that timeframe. This allows for longer tap counts, with minimal impact on responsiveness.

Our next stop is `matrix_scan_tap_dance()`. This handles the timeout of tap-dance keys.

For the sake of flexibility, tap-dance actions can be either a pair of keycodes, or a user function. The latter allows one to handle higher tap counts, or do extra things, like blink the LEDs, fiddle with the backlighting, and so on. This is accomplished by using an union, and some clever macros.

# Examples

## Simple Example

Here's a simple example for a single definition:

1. In your `makefile`, add `TAP_DANCE_ENABLE = yes`
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

## Complex Example

Here's a more complex example involving custom actions:

```c
enum {
 CT_SE = 0,
 CT_CLN,
 CT_EGG,
 CT_FLSH,
};

/* Have the above three on the keymap, TD(CT_SE), etc... */

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

void dance_egg (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count >= 100) {
    SEND_STRING ("Safety dance!");
    reset_tap_dance (state);
  }
}

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

// if the flash state didnt happen, then turn off leds, left to right
void dance_flsh_reset(qk_tap_dance_state_t *state, void *user_data) {
  ergodox_right_led_1_off();
  _delay_ms(50);
  ergodox_right_led_2_off();
  _delay_ms(50);
  ergodox_right_led_3_off();
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [CT_SE]  = ACTION_TAP_DANCE_DOUBLE (KC_SPC, KC_ENT)
 ,[CT_CLN] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_cln_finished, dance_cln_reset)
 ,[CT_EGG] = ACTION_TAP_DANCE_FN (dance_egg)
 ,[CT_FLSH] = ACTION_TAP_DANCE_FN_ADVANCED (dance_flsh_each, dance_flsh_finished, dance_flsh_reset)
};
```
