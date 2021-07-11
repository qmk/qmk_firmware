# `tdth`
## Tap dance tap hold

`tdth` is  an extension to tap dance that lets keys do different things depending on how many times they are tapped and whether they were held or just tapped. For example, you could make a letter key type the letter when tapped normally and type the letter twice when you double tap it, but hold down control when you double tap and hold it.

I use this instead of mod-tap keys to reduce accidental actuation and on my Ploopy trackball to allow one button to do many different things. See the examples section below for more details.

## Usage

To use `tdth`, add the following to your keymap's `rules.mk`:

```
TAP_DANCE_ENABLE = yes
```

You may also want to define a `TAPPING_TERM` and enable `IGNORE_MOD_TAP_INTERRUPT` in your `config.h`.

Then, at the very top of your keymap, add these definitions:

```c
//  The number of keys that you are using tdth for
#define TD_TH_COUNT 1
// The maximum number of taps you want to define actions for on
#define TD_TH_MAX_TAP 4
```

Then, below the include for `QMK_KEYBOARD_H`, add the following:

```c
#include "tdth/tdth_macros.h"
```

This will include macros necessary to set up `tdth`.

Now, you can start defining the configuration. First, create an enum with keycodes to include in your keymap (I'm only defining one key here, but you can add as many as you want):

```c
enum {
    TD_FN
};
```

Then, add this to set up the state variable for `tdth`:

```c
DEFINE_TD_STATES(TD_STATE(TD_FN));
```

Add `TD_STATE`s for each keycode (so if you had `TD_1` and `TD_2`, the arguments to `DEFINE_TD_STATES` would be `TD_STATE(TD_1), TD_STATE(TD_2)`).

Then, you can define the keycodes to be used for each action:

```c
DEFINE_TD_KEYCODES(TD_DEF(TD_FN, ARRAY_LITERAL({
    // Keycode to send when this key is tapped once
    KC_ESC,
    // Keycode to send when this key is tapped twice
    KC_ENTER,
    // etc...
    KC_UNDEFINED,
    KC_UNDEFINED
}), ARRAY_LITERAL({
    // Keycode to press and hold when this key is held down
    MO(1),
    // Keycode to press and hold when this key is double tapped and held down
    MO(2),
    // etc...
    KC_LCTL,
    MO(3)
})));
```

Similar to before, add more `TD_DEF`s for each keycode you want to define.

If you include `KC_UNDEFINED` in one of the arrays, `tdth` will tap the first item in the tap list however many times you tapped the key when activating the action - it works the same way when you tap the key more times than `TD_TH_MAX_TAP`.

Finally, include the c file for `tdth`, and add another macro similar to `DEFINE_TD_STATES` to register the tap dance actions with QMK:

```c
#include "tdth/tdth.c"

DEFINE_TD_ACTIONS(TD_ACTION(TD_FN));
```

Now, the keycode `TD_FN` is ready to use in your keymap. For an example of this in use, see [my keymap for the Ploopy trackball](/keyboards/ploopyco/trackball/keymaps/merlin04/keymap.c).

## Examples

- I use this for my Gergoplex to provide similar functionality to mod-tap keys but with less frequent accidental activation. I don't have example code to include here (currently the keymap uses an older version of `tdth`) but the definition would look something like this:

```c
TD_DEF(TD_A, ARRAY_LITERAL({
    KC_A,
    KC_UNDEFINED
}), ARRAY_LITERAL({
    KC_UNDEFINED,
    KC_LCTL
}))
```

- I also use this for my Ploopy trackball so that one FN key can activate three different layers or the control key, and when I tap it it presses escape. See [my keymap for more details](/keyboards/ploopyco/trackball/keymaps/merlin04/keymap.c).
