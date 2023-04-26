# Diablo Tap Dances 

My [Tap Dance](tap_dances.c) file includes the tap dance declarations, and everything needed for them. 

To disable, add `CUSTOM_TAP_DANCE = no` to your `rules.mk`.

This is used for making Diablo 3 much easier to plan, especially at high rift levels. 

This works by using Tap Dances.  The taps don't actually "do anything". Instead, it sets up the interval for how often to send specific keypresses.  As you can tell, this makes automating things very easy. 

For critics that think this is cheating, just search "[diablo 3 num lock auto cast](http://lmgtfy.com/?q=diablo+3+numlock+autocast)".  This is just a simpler method, that doesn't require a numpad. 


## Custom Tap Dance Type 
The real fun here is that the tap dances use a custom defined Tap Dance type: 

```c 
#define ACTION_TAP_DANCE_DIABLO(index, keycode) {  \
    .fn = { NULL, (void *)diablo_tapdance_master, NULL }, \
    .user_data = (void *)&((diable_keys_t) { index, keycode }),  \
  }
```
This lets me set an index and keycode for the tap dance.  This isn't the cool part yet, but this allows for the really cool stuff.  

The Index is needed because I don't know how to handle it otherwise. 

## The Actual Dances

These are the custom defined dances that I'm using.  It sets up everything for later, using the above custom dance type. 

```c
//Tap Dance Definitions, sets the index and the keycode.
tap_dance_action_t tap_dance_actions[] = {
    // tap once to disable, and more to enable timed micros
    [TD_D3_1] = ACTION_TAP_DANCE_DIABLO(0, KC_1),
    [TD_D3_2] = ACTION_TAP_DANCE_DIABLO(1, KC_2),
    [TD_D3_3] = ACTION_TAP_DANCE_DIABLO(2, KC_3),
    [TD_D3_4] = ACTION_TAP_DANCE_DIABLO(3, KC_4),
};
```

## Custom Data Structures

First, to get this all working, there are a couple of things that need to be set up.  In a header file (or you could put it into the keymap), you need to create a couple of custom structures: 

```c
typedef struct {
    uint16_t timer;
    uint8_t key_interval;
    uint8_t keycode;
} diablo_timer_t;

typedef struct {
  uint8_t index;
  uint8_t keycode;
} diable_keys_t;
```

The first structure is for tracking each key that is being used. The second is to pass data from the Tap Dance action array to the actual function that we will need.


## Custom Arrays

To facilitate things, you will need a couple of arrays in your `c` file.

```c
//define diablo macro timer variables
diablo_timer_t diablo_timer[4];

// Set the default intervals.  Always start with 0 so that it will disable on first hit.
// Otherwise, you will need to hit a bunch of times, or hit the "clear" command
uint8_t diablo_times[] = { 0, 1, 3, 5, 10, 30 };
```

The first one (`diablo_timer`) is what keeps track of the timer used for the keys, the interval that it uses, and the actual keycode.  This makes managing it a lot easier.  

The second array is a list of predefined intervals, in seconds.  You can add more here, or remove entries.  It doesn't matter how long the array is, as this is computed automatically. 

## The Magic - Part 1: Master function

The first part of the magic here is the `diablo_tapdance_master` function.  The Tap Dance feature calls this function, directly, and passes some data to the function.  Namely, it passes the array of the index and the keycode (`diablo_keys_t` from above).  This sets the keycode and the interval for the specific index of `diabolo_timer` based on the number of taps. If you hit it more than the number of items in the array, then it zeroes out the interval, disabling it.  

```c
// Cycle through the times for the macro, starting at 0, for disabled.
void diablo_tapdance_master(tap_dance_state_t *state, void *user_data) {
    diable_keys_t *diablo_keys = (diable_keys_t *)user_data;
    // Sets the keycode based on the index
    diablo_timer[diablo_keys->index].keycode = diablo_keys->keycode;

    // if the tapdance is hit more than the number of elemints in the array, reset
    if (state->count >= ARRAY_SIZE(diablo_times) ) {
        diablo_timer[diablo_keys->index].key_interval = 0;
        reset_tap_dance(state);
    }  else { // else set the interval (tapdance count starts at 1, array starts at 0, so offset by one)
        diablo_timer[diablo_keys->index].key_interval = diablo_times[state->count - 1];
    }
}
```

## The Magic - Part 2: The Coup de Grace

The real core here is the `run_diablo_macro_check()` function.  You need to call this from `matrix_scan_user`, as this handles the timer check.  

Specifically, it runs a check for each index of the timer.  It checks to see if it's enabled, and if enough time has passed. If enough time has passed, it resets the timer, and will tap the keycode that you set for that index, but only if the Diablo layer is enabled.  

```c
// Checks each of the 4 timers/keys to see if enough time has elapsed
void run_diablo_macro_check(void) {
    for (uint8_t index = 0; index < NUM_OF_DIABLO_KEYS; index++) {
        // if key_interval is 0, it's disabled, so only run if it's set.  If it's set, check the timer.
        if ( diablo_timer[index].key_interval && timer_elapsed( diablo_timer[index].timer ) > ( diablo_timer[index].key_interval * 1000 ) ) {
            // reset the timer, since enough time has passed
            diablo_timer[index].timer = timer_read();
            // send keycode ONLY if we're on the diablo layer.
            if (IS_LAYER_ON(_DIABLO)) {
                tap_code(diablo_timer[index].keycode);
            }
        }
    }
}
```
