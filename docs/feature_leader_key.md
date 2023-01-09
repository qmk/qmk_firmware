# The Leader Key: A New Kind of Modifier

If you've ever used Vim, you know what a Leader key is. If not, you're about to discover a wonderful concept. :) Instead of hitting Alt+Shift+W for example (holding down three keys at the same time), what if you could hit a _sequence_ of keys instead? So you'd hit our special modifier (the Leader key), followed by W and then C (just a rapid succession of keys), and something would happen.

That's what `QK_LEAD` does. Here's an example:

1. Pick a key on your keyboard you want to use as the Leader key. Assign it the keycode `QK_LEAD`. This key would be dedicated just for this -- it's a single action key, can't be used for anything else.
2. Include the line `#define LEADER_TIMEOUT 300` in your `config.h`. This sets the timeout for the `QK_LEAD` key.  Specifically, when you press the `QK_LEAD` key, you only have a certain amount of time to complete the Leader Key sequence.  The `300` here sets that to 300ms, and you can increase this value to give you more time to hit the sequence. But any keys pressed during this timeout are intercepted and not sent, so you may want to keep this value low.  
   * By default, this timeout is how long after pressing `QK_LEAD` to complete your entire sequence. This may be very low for some people. So you may want to increase this timeout.  Optionally, you may want to enable the `LEADER_PER_KEY_TIMING` option, which resets the timeout after each key is tapped.  This allows you to maintain a low value here, but still be able to use the longer sequences.   To enable this option, add `#define LEADER_PER_KEY_TIMING` to your `config.h`.
3. Within your `matrix_scan_user` function, add something like this:

```c
LEADER_EXTERNS();

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    SEQ_ONE_KEY(KC_F) {
      // Anything you can do in a macro.
      SEND_STRING("QMK is awesome.");
    }
    SEQ_TWO_KEYS(KC_D, KC_D) {
      SEND_STRING(SS_LCTL("a") SS_LCTL("c"));
    }
    SEQ_THREE_KEYS(KC_D, KC_D, KC_S) {
      SEND_STRING("https://start.duckduckgo.com\n");
    }
    SEQ_TWO_KEYS(KC_A, KC_S) {
      register_code(KC_LGUI);
      register_code(KC_S);
      unregister_code(KC_S);
      unregister_code(KC_LGUI);
    }
  }
}
```

As you can see, you have a few functions. You can use `SEQ_ONE_KEY` for single-key sequences (Leader followed by just one key), and `SEQ_TWO_KEYS`, `SEQ_THREE_KEYS` up to `SEQ_FIVE_KEYS` for longer sequences.

Each of these accepts one or more keycodes as arguments. This is an important point: You can use keycodes from **any layer on your keyboard**. That layer would need to be active for the leader macro to fire, obviously.

## Adding Leader Key Support in the `rules.mk`

To add support for Leader Key you simply need to add a single line to your keymap's `rules.mk`:

```make
LEADER_ENABLE = yes
```

## Per Key Timing on Leader keys

Rather than relying on an incredibly high timeout for long leader key strings or those of us without 200wpm typing skills, we can enable per key timing to ensure that each key pressed provides us with more time to finish our stroke. This is incredibly helpful with leader key emulation of tap dance (read: multiple taps of the same key like C, C, C).

In order to enable this, place this in your `config.h`:
```c
#define LEADER_PER_KEY_TIMING
```

After this, it's recommended that you lower your `LEADER_TIMEOUT` to something less that 300ms.

```c
#define LEADER_TIMEOUT 250
```

Now, something like this won't seem impossible to do without a 1000MS leader key timeout:

```c
SEQ_THREE_KEYS(KC_C, KC_C, KC_C) {
  SEND_STRING("Per key timing is great!!!");
}
```

## Infinite Leader key timeout

Sometimes your leader key is not on a comfortable place as the rest of keys on your sequence. Imagine that your leader key is one of your outer top right keys, you may need to reposition your hand just to reach your leader key.
This can make typing the entire sequence on time hard even if you are able to type most of the sequence fast. For example, if your sequence is `Leader + asd` typing `asd` fast is very easy once you have your hands in your home row. However starting the sequence in time after moving your hand out of the home row to reach the leader key and back is not.
To remove the stress this situation produces to your hands you can enable an infinite timeout just for the leader key. This means that after you hit the leader key you will have an infinite amount of time to start the rest of the sequence, allowing you to proper position your hands on the best position to type the rest of the sequence comfortably.
This infinite timeout only affects the leader key, so in our previous example of `Leader + asd` you will have an infinite amount of time between `Leader` and `a`, but once you start the sequence the timeout you have configured (global or per key) will work normally.
This way you can configure a very short `LEADER_TIMEOUT` but still have plenty of time to position your hands.

In order to enable this, place this in your `config.h`:
```c
#define LEADER_NO_TIMEOUT
```

## Strict Key Processing

By default, the Leader Key feature will filter the keycode out of [`Mod-Tap`](mod_tap.md) and [`Layer Tap`](feature_layers.md#switching-and-toggling-layers) functions when checking for the Leader sequences. That means if you're using `LT(3, KC_A)`, it will pick this up as `KC_A` for the sequence, rather than `LT(3, KC_A)`, giving a more expected behavior for newer users.

While, this may be fine for most, if you want to specify the whole keycode (eg, `LT(3, KC_A)` from the example above) in the sequence, you can enable this by adding `#define LEADER_KEY_STRICT_KEY_PROCESSING` to your `config.h` file.  This will then disable the filtering, and you'll need to specify the whole keycode.

## Customization 

The Leader Key feature has some additional customization to how the Leader Key feature works. It has two functions that can be called at certain parts of the process. Namely `leader_start_user()` and `leader_end_user()`.

The `leader_start_user()` function is called when you tap the `QK_LEAD` key, and the `leader_end_user()` function is called when either the leader sequence is completed, or the leader timeout is hit. 

You can add these functions to your code (`keymap.c` usually) to add feedback to the Leader sequences (such as beeping or playing music).

```c
void leader_start_user(void) {
  // sequence started
}

void leader_end_user(void) {
  // sequence ended (no success/failure detection)
}
```

### Example

This example will play the Mario "One Up" sound when you hit `QK_LEAD` to start the Leader Sequence, and will play "All Star" if it completes successfully or "Rick Roll" you if it fails. 

```c
bool did_leader_succeed;
#ifdef AUDIO_ENABLE
float leader_start[][2] = SONG(ONE_UP_SOUND );
float leader_succeed[][2] = SONG(ALL_STAR);
float leader_fail[][2] = SONG(RICK_ROLL);
#endif
LEADER_EXTERNS();

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    did_leader_succeed = leading = false;

    SEQ_ONE_KEY(KC_E) {
      // Anything you can do in a macro.
      SEND_STRING(SS_LCTL(SS_LSFT("t")));
      did_leader_succeed = true;
    } else 
    SEQ_TWO_KEYS(KC_E, KC_D) {
      SEND_STRING(SS_LGUI("r") "cmd\n" SS_LCTL("c"));
      did_leader_succeed = true;
    }
    leader_end();
  }
}

void leader_start_user(void) {
#ifdef AUDIO_ENABLE
    PLAY_SONG(leader_start);
#endif
}

void leader_end_user(void) {
  if (did_leader_succeed) {
#ifdef AUDIO_ENABLE
    PLAY_SONG(leader_succeed);
#endif
  } else {
#ifdef AUDIO_ENABLE
    PLAY_SONG(leader_fail);
#endif
  }
}
```
