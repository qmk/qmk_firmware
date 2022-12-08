# Tap Dance: A Single Key Can Do 3, 5, or 100 Different Things

## Introduction :id=introduction

Hit the semicolon key once, send a semicolon. Hit it twice, rapidly -- send a colon. Hit it three times, and your keyboard's LEDs do a wild dance. That's just one example of what Tap Dance can do. It's one of the nicest community-contributed features in the firmware, conceived and created by [algernon](https://github.com/algernon) in [#451](https://github.com/qmk/qmk_firmware/pull/451). Here's how algernon describes the feature:

With this feature one can specify keys that behave differently, based on the amount of times they have been tapped, and when interrupted, they get handled before the interrupter.

## How to Use Tap Dance :id=how-to-use

First, you will need `TAP_DANCE_ENABLE = yes` in your `rules.mk`, because the feature is disabled by default. This adds a little less than 1k to the firmware size. 

Optionally, you might want to set a custom `TAPPING_TERM` time by adding something like this in your `config.h` file:

```c
#define TAPPING_TERM 175
#define TAPPING_TERM_PER_KEY
```

The `TAPPING_TERM` time is the maximum time allowed between taps of your Tap Dance key, and is measured in milliseconds. For example, if you used the above `#define` statement and set up a Tap Dance key that sends `Space` on single-tap and `Enter` on double-tap, then this key will send `ENT` only if you tap this key twice in less than 175ms. If you tap the key, wait more than 175ms, and tap the key again you'll end up sending `SPC SPC` instead. The `TAPPING_TERM_PER_KEY` definition is only needed if you control the tapping term through a [custom `get_tapping_term` function](tap_hold.md#tapping_term), which may be needed because `TAPPING_TERM` affects not just tap-dance keys.

Next, you will want to define some tap-dance keys, which is easiest to do with the `TD()` macro. That macro takes a number which will later be used as an index into the `tap_dance_actions` array and turns it into a tap-dance keycode.

After this, you'll want to use the `tap_dance_actions` array to specify what actions shall be taken when a tap-dance key is in action. Currently, there are five possible options:

* `ACTION_TAP_DANCE_DOUBLE(kc1, kc2)`: Sends the `kc1` keycode when tapped once, `kc2` otherwise. When the key is held, the appropriate keycode is registered: `kc1` when pressed and held, `kc2` when tapped once, then pressed and held.
* `ACTION_TAP_DANCE_LAYER_MOVE(kc, layer)`: Sends the `kc` keycode when tapped once, or moves to `layer`. (this functions like the `TO` layer keycode).
* `ACTION_TAP_DANCE_LAYER_TOGGLE(kc, layer)`: Sends the `kc` keycode when tapped once, or toggles the state of `layer`. (this functions like the `TG` layer keycode).
* `ACTION_TAP_DANCE_FN(fn)`: Calls the specified function - defined in the user keymap - with the final tap count of the tap dance action.
* `ACTION_TAP_DANCE_FN_ADVANCED(on_each_tap_fn, on_dance_finished_fn, on_dance_reset_fn)`: Calls the first specified function - defined in the user keymap - on every tap, the second function when the dance action finishes (like the previous option), and the last function when the tap dance action resets.


The first option is enough for a lot of cases, that just want dual roles. For example, `ACTION_TAP_DANCE_DOUBLE(KC_SPC, KC_ENT)` will result in `Space` being sent on single-tap, `Enter` otherwise. 

!> Keep in mind that only [basic keycodes](keycodes_basic.md) are supported here. Custom keycodes are not supported.

Similar to the first option, the second and third option are good for simple layer-switching cases.

For more complicated cases, like blink the LEDs, fiddle with the backlighting, and so on, use the fourth or fifth option. Examples of each are listed below.

## Implementation Details :id=implementation

Well, that's the bulk of it! You should now be able to work through the examples below, and to develop your own Tap Dance functionality. But if you want a deeper understanding of what's going on behind the scenes, then read on for the explanation of how it all works!

Let's go over the three functions mentioned in `ACTION_TAP_DANCE_FN_ADVANCED` in a little more detail. They all receive the same two arguments: a pointer to a structure that holds all dance related state information, and a pointer to a use case specific state variable. The three functions differ in when they are called. The first, `on_each_tap_fn()`, is called every time the tap dance key is *pressed*. Before it is called, the counter is incremented and the timer is reset. The second function, `on_dance_finished_fn()`, is called when the tap dance is interrupted or ends because `TAPPING_TERM` milliseconds have passed since the last tap. When the `finished` field of the dance state structure is set to `true`, the `on_dance_finished_fn()` is skipped. After `on_dance_finished_fn()` was called or would have been called, but no sooner than when the tap dance key is *released*, `on_dance_reset_fn()` is called. It is possible to end a tap dance immediately, skipping `on_dance_finished_fn()`, but not `on_dance_reset_fn`, by calling `reset_tap_dance(state)`.

To accomplish this logic, the tap dance mechanics use three entry points. The main entry point is `process_tap_dance()`, called from `process_record_quantum()` *after* `process_record_kb()` and `process_record_user()`. This function is responsible for calling `on_each_tap_fn()` and `on_dance_reset_fn()`. In order to handle interruptions of a tap dance, another entry point, `preprocess_tap_dance()` is run right at the beginning of `process_record_quantum()`. This function checks whether the key pressed is a tap-dance key. If it is not, and a tap-dance was in action, we handle that first, and enqueue the newly pressed key. If it is a tap-dance key, then we check if it is the same as the already active one (if there's one active, that is). If it is not, we fire off the old one first, then register the new one. Finally, `tap_dance_task()` periodically checks whether `TAPPING_TERM` has passed since the last key press and finishes a tap dance if that is the case.

This means that you have `TAPPING_TERM` time to tap the key again; you do not have to input all the taps within a single `TAPPING_TERM` timeframe. This allows for longer tap counts, with minimal impact on responsiveness.

## Examples :id=examples

### Simple Example: Send `ESC` on Single Tap, `CAPS_LOCK` on Double Tap :id=simple-example

Here's a simple example for a single definition:

1. In your `rules.mk`, add `TAP_DANCE_ENABLE = yes`
2. In your `keymap.c` file, define the variables and definitions, then add to your keymap:

```c
// Tap Dance declarations
enum {
    TD_ESC_CAPS,
};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_ESC_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS),
};

// Add tap dance item to your keymap in place of a keycode
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // ...
    TD(TD_ESC_CAPS)
    // ...
};
```

### Complex Examples :id=complex-examples

This section details several complex tap dance examples.
All the enums used in the examples are declared like this:

```c
// Enums defined for all examples:
enum {
    TD_ESC_CAPS,
    CT_EGG,
    CT_FLSH,
    CT_CLN,
    X_CTL,
};
```

#### Example 1: Send "Safety Dance!" After 100 Taps :id=example-1

```c
void dance_egg(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count >= 100) {
        SEND_STRING("Safety dance!");
        reset_tap_dance(state);
    }
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [CT_EGG] = ACTION_TAP_DANCE_FN(dance_egg),
};
```

#### Example 2: Turn LED Lights On Then Off, One at a Time :id=example-2

```c
// On each tap, light up one LED, from right to left
// On the fourth tap, turn them off from right to left
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
            wait_ms(50);
            ergodox_right_led_2_off();
            wait_ms(50);
            ergodox_right_led_1_off();
    }
}

// On the fourth tap, set the keyboard on flash state
void dance_flsh_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count >= 4) {
        reset_keyboard();
    }
}

// If the flash state didn't happen, then turn off LEDs, left to right
void dance_flsh_reset(qk_tap_dance_state_t *state, void *user_data) {
    ergodox_right_led_1_off();
    wait_ms(50);
    ergodox_right_led_2_off();
    wait_ms(50);
    ergodox_right_led_3_off();
}

// All tap dances now put together. Example 2 is "CT_FLSH"
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_ESC_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS),
    [CT_EGG] = ACTION_TAP_DANCE_FN(dance_egg),
    [CT_FLSH] = ACTION_TAP_DANCE_FN_ADVANCED(dance_flsh_each, dance_flsh_finished, dance_flsh_reset)
};
```

#### Example 3: Send `:` on Tap, `;` on Hold :id=example-3

With a little effort, powerful tap-hold configurations can be implemented as tap dances. To emit taps as early as possible, we need to act on releases of the tap dance key. There is no callback for this in the tap dance framework, so we use `process_record_user()`.

```c
typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    qk_tap_dance_action_t *action;

    switch (keycode) {
        case TD(CT_CLN):  // list all tap dance keycodes with tap-hold configurations
            action = &tap_dance_actions[TD_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
    }
    return true;
}

void tap_dance_tap_hold_finished(qk_tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (state->pressed) {
        if (state->count == 1
#ifndef PERMISSIVE_HOLD
            && !state->interrupted
#endif
        ) {
            register_code16(tap_hold->hold);
            tap_hold->held = tap_hold->hold;
        } else {
            register_code16(tap_hold->tap);
            tap_hold->held = tap_hold->tap;
        }
    }
}

void tap_dance_tap_hold_reset(qk_tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (tap_hold->held) {
        unregister_code16(tap_hold->held);
        tap_hold->held = 0;
    }
}

#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold) \
    { .fn = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }

qk_tap_dance_action_t tap_dance_actions[] = {
    [CT_CLN] = ACTION_TAP_DANCE_TAP_HOLD(KC_COLN, KC_SCLN),
};
```

#### Example 4: 'Quad Function Tap-Dance' :id=example-4

By [DanielGGordon](https://github.com/danielggordon)

Allow one key to have 4 (or more) functions, depending on number of presses, and if the key is held or tapped.
Below is a specific example:
*  Tap = Send `x`
*  Hold = Send `Control`
*  Double Tap = Send `Escape`
*  Double Tap and Hold = Send `Alt`

You will need a few things that can be used for 'Quad Function Tap-Dance'. 

You'll need to add these to the top of your `keymap.c` file, before your keymap. 

```c
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

// Tap dance enums
enum {
    X_CTL,
    SOME_OTHER_DANCE
};

td_state_t cur_dance(qk_tap_dance_state_t *state);

// For the x tap dance. Put it here so it can be used in any keymap
void x_finished(qk_tap_dance_state_t *state, void *user_data);
void x_reset(qk_tap_dance_state_t *state, void *user_data);
```

Now, at the bottom of your `keymap.c` file, you'll need to add the following: 

```c
/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance is "interrupted", that means that another key has been hit
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
 * For the third point, there does exist the 'TD_DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
        else return TD_TRIPLE_HOLD;
    } else return TD_UNKNOWN;
}

// Create an instance of 'td_tap_t' for the 'x' tap dance.
static td_tap_t xtap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void x_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_X); break;
        case TD_SINGLE_HOLD: register_code(KC_LCTL); break;
        case TD_DOUBLE_TAP: register_code(KC_ESC); break;
        case TD_DOUBLE_HOLD: register_code(KC_LALT); break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_X); register_code(KC_X); break;
        default: break;
    }
}

void x_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_X); break;
        case TD_SINGLE_HOLD: unregister_code(KC_LCTL); break;
        case TD_DOUBLE_TAP: unregister_code(KC_ESC); break;
        case TD_DOUBLE_HOLD: unregister_code(KC_LALT); break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_X); break;
        default: break;
    }
    xtap_state.state = TD_NONE;
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [X_CTL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, x_finished, x_reset)
};
```

And then simply use `TD(X_CTL)` anywhere in your keymap.

If you want to implement this in your userspace, then you may want to check out how [DanielGGordon](https://github.com/qmk/qmk_firmware/tree/master/users/gordon) has implemented this in their userspace.

> In this configuration "hold" takes place **after** tap dance timeout. To achieve instant hold, remove `state->interrupted` checks in conditions. As a result you may use comfortable longer tapping periods to have more time for taps and not to wait too long for holds (try starting with doubled `TAPPING_TERM`).

#### Example 5: Using tap dance for advanced mod-tap and layer-tap keys :id=example-5

Tap dance can be used to emulate `MT()` and `LT()` behavior when the tapped code is not a basic keycode. This is useful to send tapped keycodes that normally require `Shift`, such as parentheses or curly braces—or other modified keycodes, such as `Control + X`.

Below your layers and custom keycodes, add the following:

```c
// Tap Dance keycodes
enum td_keycodes {
    ALT_LP // Our example key: `LALT` when held, `(` when tapped. Add additional keycodes for each tapdance.
};

// Define a type containing as many tapdance states as you need
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_SINGLE_TAP
} td_state_t;

// Create a global instance of the tapdance state type
static td_state_t td_state;

// Declare your tapdance functions:

// Function to determine the current tapdance state
td_state_t cur_dance(qk_tap_dance_state_t *state);

// `finished` and `reset` functions for each tapdance keycode
void altlp_finished(qk_tap_dance_state_t *state, void *user_data);
void altlp_reset(qk_tap_dance_state_t *state, void *user_data);
```

Below your `LAYOUT`, define each of the tapdance functions:

```c
// Determine the tapdance state to return
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    }

    if (state->count == 2) return TD_DOUBLE_SINGLE_TAP;
    else return TD_UNKNOWN; // Any number higher than the maximum state value you return above
}

// Handle the possible states for each tapdance keycode you define:

void altlp_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            register_code16(KC_LPRN);
            break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LALT)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            break;
        case TD_DOUBLE_SINGLE_TAP: // Allow nesting of 2 parens `((` within tapping term
            tap_code16(KC_LPRN);
            register_code16(KC_LPRN);
            break;
        default:
            break;
    }
}

void altlp_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            unregister_code16(KC_LPRN);
            break;
        case TD_SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LALT)); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
            break;
        case TD_DOUBLE_SINGLE_TAP:
            unregister_code16(KC_LPRN);
            break;
        default:
            break;
    }
}

// Define `ACTION_TAP_DANCE_FN_ADVANCED()` for each tapdance keycode, passing in `finished` and `reset` functions
qk_tap_dance_action_t tap_dance_actions[] = {
    [ALT_LP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, altlp_finished, altlp_reset)
};
```

Wrap each tapdance keycode in `TD()` when including it in your keymap, e.g. `TD(ALT_LP)`.

#### Example 6: Using tap dance for momentary-layer-switch and layer-toggle keys :id=example-6

Tap Dance can be used to mimic MO(layer) and TG(layer) functionality. For this example, we will set up a key to function as `KC_QUOT` on single-tap, as `MO(_MY_LAYER)` on single-hold, and `TG(_MY_LAYER)` on double-tap.

The first step is to include the following code towards the beginning of your `keymap.c`:

```c
// Define a type for as many tap dance states as you need
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

enum {
    QUOT_LAYR, // Our custom tap dance key; add any other tap dance keys to this enum 
};

// Declare the functions to be used with your tap dance key(s)

// Function associated with all tap dances
td_state_t cur_dance(qk_tap_dance_state_t *state);

// Functions associated with individual tap dances
void ql_finished(qk_tap_dance_state_t *state, void *user_data);
void ql_reset(qk_tap_dance_state_t *state, void *user_data);
```

Towards the bottom of your `keymap.c`, include the following code:

```c
// Determine the current tap dance state
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) return TD_DOUBLE_TAP;
    else return TD_UNKNOWN;
}

// Initialize tap structure associated with example tap dance key
static td_tap_t ql_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void ql_finished(qk_tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_QUOT);
            break;
        case TD_SINGLE_HOLD:
            layer_on(_MY_LAYER);
            break;
        case TD_DOUBLE_TAP:
            // Check to see if the layer is already set
            if (layer_state_is(_MY_LAYER)) {
                // If already set, then switch it off
                layer_off(_MY_LAYER);
            } else {
                // If not already set, then switch the layer on
                layer_on(_MY_LAYER);
            }
            break;
        default:
            break;
    }
}

void ql_reset(qk_tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (ql_tap_state.state == TD_SINGLE_HOLD) {
        layer_off(_MY_LAYER);
    }
    ql_tap_state.state = TD_NONE;
}

// Associate our tap dance key with its functionality
qk_tap_dance_action_t tap_dance_actions[] = {
    [QUOT_LAYR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ql_finished, ql_reset)
};

// Set a long-ish tapping term for tap-dance keys
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QK_TAP_DANCE ... QK_TAP_DANCE_MAX:
            return 275;
        default:
            return TAPPING_TERM;
    }
}
```

The above code is similar to that used in previous examples. The one point to note is that we need to be able to check which layers are active at any time so we can toggle them if needed. To do this we use the `layer_state_is(layer)` function which returns `true` if the given `layer` is active.

The use of `cur_dance()` and `ql_tap_state` mirrors the above examples.

The `case: TD_SINGLE_TAP` in `ql_finished` is similar to the above examples. The `TD_SINGLE_HOLD` case works in conjunction with `ql_reset()` to switch to `_MY_LAYER` while the tap dance key is held, and to switch away from `_MY_LAYER` when the key is released. This mirrors the use of `MO(_MY_LAYER)`. The `TD_DOUBLE_TAP` case works by checking whether `_MY_LAYER` is the active layer, and toggling it on or off accordingly. This mirrors the use of `TG(_MY_LAYER)`.

`tap_dance_actions[]` works similar to the above examples. Note that, additionally, I set a longer tapping term for the tap dance keys. This is because I like my `TAPPING_TERM` to be short (\~175ms) for my non-tap-dance keys but find that this is too quick for me to reliably complete tap dance actions - thus the increased time of 275ms here. In order for the per-key tapping terms to take effect, `TAPPING_TERM_PER_KEY` must be defined in your `config.h`.

Finally, to get this tap dance key working, be sure to include `TD(QUOT_LAYR)` in your `keymaps[]`.
