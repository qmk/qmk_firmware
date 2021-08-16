# Adaptive Keys 

Adaptive keys allow you to change the behavior of a key based on the last key pressed. For example, a key could be W most of the time, but if the user quickly types qw, the adaptive behavior sends qu.

Adaptive keys are especially useful for common [bigrams](https://en.wikipedia.org/wiki/Bigram) that are inconvenient or uncomfortable to type.

There are three components to an adaptive key setup:

1. **Prefix**: the key that precedes an adaptive key and lets QMK know an adaptive key might be coming
2. **Trigger**: the "normal" value of the adaptive key, which should be sent if the adaptive behavior isn't active
3. **Replacement**: the "adaptive" value of the key

## How to Use

First, set `ADAPTIVE_KEYS_ENABLE = yes` in your `rules.mk` file. This will enable the feature.

You can optionally define `ADAPTIVE_KEY_TERM 200` in your `config.h` file. This is the length of the window of time in which the adaptive replacement will be registered instead of the trigger. In other words, in our QW / QU example, tapping Q, then W inside `ADAPTIVE_KEY_TERM` will send `qu`, but waiting until after `ADAPTIVE_KEY_TERM` ends will send `qw` as usual.

Set up an enum to track the indexes of the adaptive keys you'll be using.

Set the variable `uint16_t ADAPTIVE_KEY_LEN` to the number of adaptive keys you are using. If you're using an enum to define the indexes of your adaptive keys, an easy way to declare this variable is is to add a value to the end of your enum and set this variable to that value afterwards. That way, you don't need to worry about counting your keys or changing it each time you add or remove some.

Finally, define the `adaptive_keys` array to hold all the adaptive keys you want to set up. It's easiest to use the `ADAPTIVE_KEY()` macro to do this, which takes the form `ADAPTIVE_KEY(prefix_keycode, trigger_keycode, replacement_keycode)`.

See the [examples](#examples) for fully-realized code snippets.

## Advanced Usage
### Enabling and disabling the feature on the fly

You may want to enable or disable adaptive keys based on some other criteria. To do this, you can use these functions:

```c
void enable_adaptive_keys(void);
void disable_adaptive_keys(void);
void toggle_adaptive_keys(void);
```

For example, here's how you'd disable adaptive keys when entering a layer dedicated to gaming (assume `_GAME` is defined in your layer definitions enum):

```c
layer_state_t layer_state_set_user(layer_state_t state) {
    if (LAYER_ON(state, _GAME)) {
        disable_adaptive_keys();
    }
    else {
        enable_adaptive_keys();
    }
    return state;
}
```
### User callbacks

What if you want a more elaborate adaptive key? Something like, "I want an adaptive key to change its behavior based on whether the last key was a vowel."

Instead of using the `ADAPTIVE_KEY()` macro to create an adaptive key definition, you can use one of the following macros to replace a keycode with a user callback:

* `ADAPTIVE_KEY_PREFIX_FN` (uses a function callback instead of a keycode for the prefix)
* `ADAPTIVE_KEY_TRIGGER_FN` (uses a callback for the trigger)
* `ADAPTIVE_KEY_REPLACE_FN` (uses a callback for the replacement)
* `ADAPTIVE_KEY_FN` (uses callbacks for all three)

The prefix and trigger functions share the same definition. They should return `true` if the keycode in the provided event serves as a prefix or trigger, respectively. Here are some simple implementations:

```c
bool qk_adaptive_key_is_prefix_key(qk_adaptive_key_state_t *state, uint16_t keycode, keyrecord_t *record) {
    return keycode == state->prefix_keycode;
}

bool qk_adaptive_key_is_trigger_key(qk_adaptive_key_state_t *state, uint16_t keycode, keyrecord_t *record) {
    return keycode == state->trigger_keycode;
}
```

The replacement function has a slightly different definition. It doesn't accept a keycode (the keycode in this event is always the trigger keycode), and it doesn't need to return anything. Here's an example:

!> This callback gets called both for key press and key release events. Be sure to handle both cases!

```c
void qk_adaptive_key_on_adaptive_event(qk_adaptive_key_state_t *state, keyrecord_t *record) {
    if (record->event.pressed) {
        register_code16(state->replace_keycode);
    }
    else {
        unregister_code16(state->replace_keycode);
    }
}
```

## Examples

### Simple Examples

Here's the implementation of the QW / QU example described above: 

```c
enum adaptive_key_index {
    QW_QU,
    END_OF_ADAPTIVE_LIST, // This can be named whatever
};

// This one is the name that matters
uint16_t ADAPTIVE_KEY_LEN = END_OF_ADAPTIVE_LIST;

qk_adaptive_key_t adaptive_keys[] = {
    [QW_QU] = ADAPTIVE_KEY(KC_Q, KC_W, KC_U),
};
```

Here, we'll add another adaptive key: H-J -> HI:

```c
enum adaptive_key_index {
    QW_QU,
    HJ_HI,
    END_OF_ADAPTIVE_LIST,
};

uint16_t ADAPTIVE_KEY_LEN = END_OF_ADAPTIVE_LIST;

qk_adaptive_key_t adaptive_keys[] = {
    [QW_QU] = ADAPTIVE_KEY(KC_Q, KC_W, KC_U),
    [HJ_HI] = ADAPTIVE_KEY(KC_H, KC_J, KC_I),
};
```

### Complex examples

Here, the adaptive key uses a callback to define its prefix. This example creates an adaptive key that sends a period normally, but if the last key was a vowel, it sends an exclamation point.

```c
bool user_is_vowel_prefix_key(qk_adaptive_key_state_t *state, uint16_t keycode, keyrecord_t *record) {
    if (keycode == KC_A || keycode == KC_E || keycode == KC_I || keycode == KC_O || keycode == KC_U) {
        return true;
    }

    return false;
}


enum adaptive_key_index {
    VOWEL_EMPHATIC,
    END_OF_ADAPTIVE_LIST,
};

uint16_t ADAPTIVE_KEY_LEN = END_OF_ADAPTIVE_LIST;

qk_adaptive_key_t adaptive_keys[] = {
    [VOWEL_EMPHATIC] = ADAPTIVE_KEY_PREFIX_FN(user_is_vowel_prefix_key, KC_DOT, KC_EXLM)
};

```

## Notes

Remember that an adaptive key cannot change the prefix!

### Adaptive keys and dual-role keys

An `MT()` or `LT()` keycode cannot be used as a replacement keycode in an adaptive key (the key will still work as a tap key, but its hold behavior will never activate). Custom keycodes, macros, or anything else that isn't a [basic keycode](keycodes_basic.md) also cannot be used for replacements.

Adaptive keys can use `MT()` or `LT()` keycodes as a trigger, but you need to include the whole `MT()` or `LT()` definition in the adaptive key definition in order for the adaptive keys code to recognize the keycode. The adaptive key will not be recognized if you include only the inner "tap" keycode.

When using a dual-role key as a trigger for an adaptive key, be aware that the hold behavior will not trigger if the adaptive behavior happens. For example, consider this snippet:

```c
qk_adaptive_key_t adaptive_keys[] = {
    [DOT_COMM] = ADAPTIVE_KEY(KC_DOT, ALT_T(KC_COMM), KC_SPC),
};
```

Now, assuming there's really a `ALT_T(KC_COMM)` in the keymap, here's how this could play out:

* Tapping `KC_DOT`, then pressing and releasing `ALT_T(KC_COMM)` inside `ADAPTIVE_KEY_TERM` will cause `. ` (dot space) to be sent.
* Tapping `KC_DOT`, then pressing and holding `ALT_T(KC_COMM)` inside `ADAPTIVE_KEY_TERM` will **still** cause `. ` (dot space) to be sent, even if you hold the mod-tap longer than `TAPPING_TERM`.
* Tapping `KC_DOT`, waiting until after `ADAPTIVE_KEY_TERM`, and tapping or holding `ALT_T(KC_COMM)` will cause the mod-tap key to use its normal behavior.
