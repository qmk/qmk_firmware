# Repeat Key

The Repeat Key performs the action of the last pressed key. For instance,
tapping the Repeat Key after tapping the <kbd>Z</kbd> key types another "`z`."
The Repeat Key is useful for hotkeys, for instance repeating Ctrl+Shift+Right to
select by word. It can also be useful for typing doubled letters, like the `z`
in "`dazzle`": a double tap on <kbd>Z</kbd> can instead be a roll from
<kbd>Z</kbd> to <kbd>Repeat</kbd>, which is potentially faster and more
comfortable. 

Repeat Key remembers mods that were active with the last key press. These mods
are combined with any additional mods while pressing the Repeat Key. If the last
press key was <kbd>Ctrl</kbd> + <kbd>Z</kbd>, then <kbd>Shift</kbd> +
<kbd>Repeat</kbd> performs Ctrl + Shift + `Z`.

## How do I enable Repeat Key

First, enable Repeat Key by setting `REPEAT_KEY_ENABLE = yes` in your rules.mk.
Then pick a key in your keymap and assign it the keycode `QK_REPEAT_KEY` (short
alias `QK_REP`).

## Customizing Repeat Key

### Handle how a key is repeated

By default, pressing the Repeat Key will simply behave as if the last key
were pressed again. This also works with macro keys with custom handlers,
invoking the macro again. In case fine-tuning is needed for sensible repetition,
you can handle how a key is repeated with `get_repeat_key_count()` within
`process_record_user()`. 

When a key is pressed as usual, `get_repeat_key_count()` is 0. On the first
repeat, it is 1, then the second repeat, 2, and so on. For instance supposing
`MY_MACRO` is a custom keycode used in the layout:

```c
bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
      case MY_MACRO:
          if (get_repeat_key_count() > 0) { // MY_MACRO is being repeated!
              if (record->event.pressed) {
                  SEND_STRING("repeat!");    
              }
          } else {                          // MY_MACRO is being used normally.
              if (record->event.pressed) {  
                  SEND_STRING("macro");
              }
          }
          return false;
   
      // Other macros...
    }
    return true;
}
```

### Ignoring certain keys

By default, the Repeat Key ignores modifier and layer switch keys in tracking
what the "last" key was. This enables possibly setting some mods and changing
layers between pressing a key and repeating it. To customize which keys are
ignored, define `get_repeat_key_eligible()` in your keymap.c. The default
implementation is

```c
bool get_repeat_key_eligible(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        // Ignore MO, TO, TG, and TT layer switch keys.
        case QK_MOMENTARY ... QK_MOMENTARY_MAX:
        case QK_TO ... QK_TO_MAX:
        case QK_TOGGLE_LAYER ... QK_TOGGLE_LAYER_MAX:
        case QK_LAYER_TAP_TOGGLE ... QK_LAYER_TAP_TOGGLE_MAX:
        // Ignore mod keys.
        case KC_LCTL ... KC_RGUI:
        case KC_HYPR:
        case KC_MEH:
        // Ignore one-shot keys.
#ifndef NO_ACTION_ONESHOT
        case QK_ONE_SHOT_LAYER ... QK_ONE_SHOT_LAYER_MAX:
        case QK_ONE_SHOT_MOD ... QK_ONE_SHOT_MOD_MAX:
#endif  // NO_ACTION_ONESHOT
            return false;

        // Ignore hold events on tap-hold keys.
#ifndef NO_ACTION_TAPPING
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
#ifndef NO_ACTION_LAYER
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
#endif  // NO_ACTION_LAYER
            if (record->tap.count == 0) {
                return false;
            }
            break;
#endif  // NO_ACTION_TAPPING

#ifdef SWAP_HANDS_ENABLE
        case QK_SWAP_HANDS ... QK_SWAP_HANDS_MAX:
            if (IS_SWAP_HANDS_KEYCODE(keycode) || record->tap.count == 0) {
                return false;
            }
            break;
#endif  // SWAP_HANDS_ENABLE
    }

    return true;
}
```

This callback is called on every key press. Returning true indicates the key
is eligible for repeating, while false means it is ignored.

### Functions

There are a few functions for interacting with the Repeat Key from user code:

| Function                      | Description                                 |
|-------------------------------|---------------------------------------------|
| `get_repeat_key_count()`      | How many times the current key has been repeated: 0 &rArr; key is pressed normally, 1 &rArr; first repeat, 2 &rArr; second repeat, etc. |
| `get_repeat_key_keycode()`    | The last key's keycode, the key to be repeated.   |
| `get_repeat_key_mods()`       | Mods to apply when repeating.                     |
| `set_repeat_key_keycode(kc)`  | Set the keycode to be repeated.                   |
| `set_repeat_key_mods(mods)`   | Set the mods to apply when repeating.             |

