# Caps Word

It is often useful to type a single word in all capitals, for instance
abbreviations like "QMK", or in code, identifiers like `KC_SPC`. "Caps Word" is
a modern alternative to Caps Lock:

* Letters are capitalized while active, and Caps Word automatically disables
  itself at the end of the word. That is, it stops by default once a space or
  any key other than `a`--`z`, `0`--`9`, `-`, `_`, delete, or backspace is
  pressed. Caps Word also disables itself if the keyboard is idle for 5 seconds.
  This is configurable, see below.

* To avoid requiring a dedicated key for Caps Word, there is an option
  (`BOTH_SHIFTS_TURNS_ON_CAPS_WORD`) to activate Caps Word by simultaneously
  pressing both shift keys. See below for other options.

* The implementation does not use the Caps Lock (`KC_CAPS`) keycode. Caps Word
  works even if you're remapping Caps Lock at the OS level to Ctrl or something
  else, as Emacs and Vim users often do.


## How do I enable Caps Word :id=how-do-i-enable-caps-word

In your `rules.mk`, add:

```make
CAPS_WORD_ENABLE = yes
```

Next, use one the following methods to activate Caps Word:

* **Activate by pressing a key**: Use the `CAPS_WORD` keycode (short
  alias `CAPSWRD`) in your keymap.

* **Activate by pressing Left Shift + Right Shift**: Add `#define
  BOTH_SHIFTS_TURNS_ON_CAPS_WORD` to config.h. You may also need to disable or
  reconfigure Command, details below. Then, simultaneously pressing both left
  and right shifts turns on Caps Word. This method works with the plain
  `KC_LSFT` and `KC_RSFT` keycodes as well as one-shot shifts and Space Cadet
  shifts. If your shift keys are mod-taps, hold both shift mod-tap keys until
  the tapping term, then release them.

* **Activate by double tapping Left Shift**: Add `#define
  DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD` config.h. Then, double tapping Left Shift
  turns on Caps Word. This method works with `KC_LSFT` or one-shot Left Shift
  `OSM(MOD_LSFT)`. To count as a double tap, the maximum time in milliseconds
  between taps is `TAPPING_TERM`, or if using `TAPPING_TERM_PER_KEY`, the time
  returned by `get_tapping_term()` for the shift keycode being tapped.

* **Custom activation**: You can activate Caps Word from code by calling
  `caps_word_on()`. This may be used to activate Caps Word through [a
  combo](feature_combo.md) or [tap dance](feature_tap_dance.md) or any means
  you like.

### Troubleshooting: Command :id=troubleshooting-command

When using `BOTH_SHIFTS_TURNS_ON_CAPS_WORD`, you might see a compile message
**"BOTH_SHIFTS_TURNS_ON_CAPS_WORD and Command should not be enabled at the same
time, since both use the Left Shift + Right Shift key combination."**

Many keyboards enable the [Command feature](feature_command.md), which by
default is also activated using the Left Shift + Right Shift key combination. To
fix this conflict, please disable Command by adding in rules.mk: 

```make
COMMAND_ENABLE = no
```

Or configure Command to use another key combination like Left Ctrl + Right Ctrl
by defining `IS_COMMAND()` in config.h:

```c
// Activate Command with Left Ctrl + Right Ctrl.
#define IS_COMMAND() (get_mods() == MOD_MASK_CTRL)
```


## Customizing Caps Word :id=customizing-caps-word

### Idle timeout :id=idle-timeout

Caps Word turns off automatically if no keys are pressed for
`CAPS_WORD_IDLE_TIMEOUT` milliseconds. The default is 5000 (5 seconds).
Configure the timeout duration in config.h, for instance 

```c
#define CAPS_WORD_IDLE_TIMEOUT 3000  // 3 seconds.
```

Setting `CAPS_WORD_IDLE_TIMEOUT` to 0 configures Caps Word to never time out.
Caps Word then remains active indefinitely until a word breaking key is pressed.


### Functions :id=functions

Functions to manipulate Caps Word:

| Function                | Description                                    |
|-------------------------|------------------------------------------------|
| `caps_word_on()`        | Turns Caps Word on.                            |
| `caps_word_off()`       | Turns Caps Word off.                           |
| `caps_word_toggle()`    | Toggles Caps Word.                             |
| `is_caps_word_on()`     | Returns true if Caps Word is currently on.     |


### Configure which keys are "word breaking" :id=configure-which-keys-are-word-breaking

You can define the `caps_word_press_user(uint16_t keycode)` callback to
configure which keys should be shifted and which keys are considered "word
breaking" and stop Caps Word.

The callback is called on every key press while Caps Word is active. When the
key should be shifted (that is, a letter key), the callback should call
`add_weak_mods(MOD_BIT(KC_LSFT))` to shift the key. Returning true continues the
current "word," while returning false is "word breaking" and deactivates Caps
Word. The default callback is

```c
bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        case KC_MINS:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
}
```


### Representing Caps Word state :id=representing-caps-word-state

Define `caps_word_set_user(bool active)` to get callbacks when Caps Word turns
on or off. This is useful to represent the current Caps Word state, e.g. by
setting an LED or playing a sound. In your keymap, define

```c
void caps_word_set_user(bool active) {
    if (active) {
        // Do something when Caps Word activates.
    } else {
        // Do something when Caps Word deactivates.
    }
}
```

