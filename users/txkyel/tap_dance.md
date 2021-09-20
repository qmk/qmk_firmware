# Tap Hold Custom Tap Dance

This custom tap dance functions similarly to the single tap and hold functionality of '[Quad Function Tap-Dance](https://docs.qmk.fm/#/feature_tap_dance?id=example-4)' by [DanielGGordon](https://github.com/danielggordon) with a reduced size per tap dance declared.

## Motivation

I first discovered tap dancing through [Ben Vallack](https://www.youtube.com/c/BenVallack) and was interested in the functionality of tap dancing demonstrated in his [tap dancing video](https://www.youtube.com/watch?v=pTMbzmf2sz8). And so I set off to implement my own tap dances emulating this functionality.

## Custom Tap Dance Action

Similar to the the action definitions in [`process_tap_dance.h`](../../quantum/process_keycode/process_tap_dance.h); I have created a custom macro and data structure used to declare tap dance actions:

```c
typedef struct {
    uint16_t t;
    uint16_t h;
    bool     tapped;
} qk_tap_dance_tap_hold_t;

#define ACTION_TAP_HOLD(t, h) \
    { .fn = {qk_tap_dance_tap_hold_on_each_tap, qk_tap_dance_tap_hold_on_finish, qk_tap_dance_tap_hold_on_reset}, .user_data = (void *)&((qk_tap_dance_tap_hold_t){t, h, true}), }
```

This allows the user to set the keycode registered when tapping `t`, the keycode registered when holding `h`, as well as prepares a boolean storing logic allowing the the reset function to determine whether a tap or hold was registered `tapped`.

## Custom Tap Dance Functions

The three handlers backing Tap Hold are really simple.

The `on_each_tap` handler triggers a tap if a second tap is made within the tapping term. Following that it performs a pseudo reset, setting the count back to 1 and resetting the timer.

```c
void qk_tap_dance_tap_hold_on_each_tap(qk_tap_dance_state_t *state, void *user_data) {
    qk_tap_dance_tap_hold_t *kc = (qk_tap_dance_tap_hold_t *)user_data;

    if (state->count == 2) {
        tap_code16(kc->t);
        state->count = 1;
        state->timer = timer_read();
    }
}
```

The `on_finished` handler determines whether the dance was a tap or a hold, saving the result in `kc->tapped` for `on_reset` later. After, the handler registers the respctive keycode. 

```c
void qk_tap_dance_tap_hold_on_finish(qk_tap_dance_state_t *state, void *user_data) {
    qk_tap_dance_tap_hold_t *kc = (qk_tap_dance_tap_hold_t *)user_data;

    kc->tapped = state->interrupted || !state->pressed;
    if (kc->tapped) {
        register_code16(kc->t);
    } else {
        register_code16(kc->h);
    }
}
```

Finally, the `on_reset` handler unregisters the corresponding keycode, and resets `kc->tapped` for subsequent tap dances.

```c
void qk_tap_dance_tap_hold_on_reset(qk_tap_dance_state_t *state, void *user_data) {
    qk_tap_dance_tap_hold_t *kc = (qk_tap_dance_tap_hold_t *)user_data;

    if (kc->tapped) {
        unregister_code16(kc->t);
    } else {
        unregister_code16(kc->h);
    }
    kc->tapped = true;
}
```

## Tap: keycode; Hold: control + keycode (or any modifier + keycode)

The macro `ACTION_TAP_HOLD` allows a user to select the keycode for both the tap and hold action of the tap dance. It goes without saying that you can also send keycodes with modifiers so instead of having to write out `ACTION_TAP_HOLD(kc, C(kc))` for each keycode, we can use more macros:

```c
#define ACTION_TAP_HOLD_CTL(t) ACTION_TAP_HOLD(t, LCTL(t))
```

Macros are rock.

# The Journey to Lower Sized Tap Dancing

As I said earlier, I had set out to create my own tap dancing functions with little knowledge of how QMK works. Just as a bonus, I thought I'd share my journey through making my own custom tap dance.

## Research

When looking through the [tap dance documentation](https://beta.docs.qmk.fm/using-qmk/software-features/feature_tap_dance), it was apparent to me that [complex example 4](https://docs.qmk.fm/#/feature_tap_dance?id=example-4) by [DanielGGordon](https://github.com/danielggordon), had the functionality I so desired, I would have to do at least three things. 

However, in order to make all the tap dances for at least all of the alpha keys I would have to do the following three things:

1. Write a `on_dance_finished` function
2. Write a `on_reset` function
3. And create a static struct instance storing a `boolean` and `td_state_t`

The most outrageous part was that I would have to repeat these three steps for **each and every tap dance!**

Unable to see how I could reduce the number of functions and data structures. I decided to follow through with making functions for each keycode.

## Naive Implementation 1: Macros with `ACTION_TAP_DANCE_FN_ADVANCED`

For my initial implementation, I set out to make use of macros to reduce the amount of apparent duplicate code in my keymap files.

Copying the functions by DanielGGordon, reducing its functionality to single tap and single hold, and converting them into macros, I was able to create all the necessary functions for each tap dance without having to write out the same functions dozens of times.

My issues with this implementation were that, when compiling, this was no different from me writing the same function dozens of time. This meant that the resulting firmware was **HUGE** decreasing the amount of additional features the user is able to enable.

## Naive Implementation 2: Custom Quantum Keycode

Searching for another solution I searched through the files in the qmk repository and stumbled across the implementation of several quantum keycode processing files in [`process_keycode`](../../quantum/process_keycode), namely the files [`process_unicode.h`](../../quantum/process_keycode/process_unicode.h), [`process_unicode.c`](../../quantum/process_keycode/process_unicode.c), and [`process_unicode_common.h`](../../quantum/process_keycode/process_unicode_common.h).

And so I set off to implement my own **custom quantum keycodes** overriding Unicode keycode ranges and [implementing `process_record_user()`](https://docs.qmk.fm/#/custom_quantum_functions?id=custom-keycodes).

Upon initial testing with a single key, it appeared functional save for the fact that keys would only register when releasing the key. Additionally it saved plenty of space due to reuse of functions when processing input.

I was really proud of my implementation and had even shown it off to several of my friends.

Unfortunately, when testing it out on all alpha, everything started to come apart. Because keystrokes would only register when releasing the switch, faster typists would actually actuate some keystrokes in the incorrect order; particularly with space appearing before the final letter of most words.

## Current Implementation: Custom Tap Dance Actions

Upset that I would have to go back to naive implementation 1, I went back to digging for answers. Maybe there was something I was missing, some extra details on how tap dancing gets processed.

Looking again in [`process_keycode`](../../quantum/process_keycode), I found [`process_tap_dance.h`](../../quantum/process_keycode/process_tap_dance.h) and [`process_tap_dance.c`](../../quantum/process_keycode/process_tap_dance.c). And in those files, I found the miracle working struct `qk_tap_dance_action_t`.

Looking more closely, each tap dance action a user defines constructs a `qk_tap_dance_action_t` with the following:

-   Three handler functions
    -   An `on_each_tap` function that runs when the tap dance key is pressed within the `TAPPING_TERM`
    -   An `on_dance_finished` function that runs when the `TAPPING_TERM` is complete
    -   An `on_reset` function that runs after finishing the dance
-   A `custom_tapping_term` for the tap dance action
-   Last but not least, the my saving grace: `void *user_data`. A user defined struct that gets passed to each of the handler functions.

With this discovery, I set out to implement my own custom tap dance action in my [personal userspace](.) as seen [`tap_dance.c`](tap_dance.c) and [`tap_dance.h`](tap_dance.h) which I named ACTION_TAP_HOLD.

## Updates and Thoughts

### 08/08/2021

Initially, I thought of allowing the user to hold the hold tap dance action (`KC_LCTL` + `KC_<keycode>`). Unfortunately, I ran into several issues (likely due to my lack of understanding on the runtime flow) causing control to be held indefinitely until the computer is restarted. This is why, I had handler functions perform `tap_code16` opposed to `register_code16` and `unregister_code16`.

When handling a double tap within the `TAPPING_TERM`, the tap keycode gets sent with `tap_code16`, the status timer gets reset, and the counter gets set back to 1 in case the user wishes to tap again or to hold the second tap.

### 09/08/2021

Generalized tap and hold `user_data` struct to store two keycodes; one for the tap action, the other for the hold action. 

This way the user can define the tap and hold functionality separately.

### 09/08/2021

Reworked utilizing, `register_code16` and `unregister_code16`. The issues previously experienced were due to my ignorance of the runtime flow for tap dancing.

Previously in both the `on_dance_finished` and `on_reset` functions, I checked if the key was being tapped or held using this statement:

```
state->interrupted || !state->pressed
```

In the case of a hold, when accessing the `on_dance_finished` function, `state->interrupted` would be false and `state->pressed` would be true making the above statement false making the statement work as intended.

However, when it comes to `on_reset` the statement no longer works.

In the runtime flow for tap dancing, `on_reset` gets called in the function [`reset_tap_dance`](../../quantum/process_keycode/process_tap_dance.c#L186). In order for the `on_reset` function to be called, **state->pressed must be false**.

This means that the above statement is no longer reliable in determining if a key has been held in this function. In fact, the function will always act as though a tap occured, meaning the hold reset will never be reached.

There were signs of this in [complex examples](https://docs.qmk.fm/#/feature_tap_dance?id=complex-examples) that I hadn't taken into mind when designing this custom tap dance action (mainly through the static variables used to store the state instead of using `state` in both functions).

As such, the fix was as simple as adding a boolean to the `user_data` struct that stores the state of the tap dance, thus allowing us to now be able to properly hold the hold key without any worry of the hold action of a key being stuck on.
