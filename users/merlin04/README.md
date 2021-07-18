# Merlin04's userspace

- `tdth`: Tap dance tap hold, an extension to tap dance that lets keys do different things depending on how many times they are tapped and whether they were held or just tapped. For example, you could make a letter key type the letter when tapped normally and type the letter twice when you double tap it, but hold down control when you double tap and hold it. I use this instead of mod-tap keys to reduce accidental actuation and on my Ploopy trackball to allow one button to do many different things. See more in at `tdth/README.md`.
- `register_any`: an alternative to the `register_code` and `register_code16` functions that allows you to set any keycode (even QMK ones, like MO) as enabled or disabled. 

## `register_any` usage guide

First, include `register_any` in your keymap:

```c
#include "register_any.h"
```

Then, you can use it like this:

```c
// Go to layer 1
register_any(MO(1), true);
```

Instead of having two separate functions for `register`ing and `unregister`ing, you can control whether the keycode should be pressed or released through the second parameter (true is pressed, false is released).

You can also use the `tap_any` function as an alternative to `tap_code` and `tap_code16`:

```c
// Set the default layer to layer 2
tap_any(DF(2));
```

I built this to use in `tdth` because I wanted to be able to use any keycode for the various actions. There are separate functions to enable and disable layers but that would introduce a lot of complexity into the code and make it more complicated to configure.

The way `register_any` works is by generating a fake `keyrecord_t` for a keypress, using part of a function in `/tmk_core/common/action.c` to get the `action_t` for the provided keycode, and providing both of those objects to QMK's `process_action` function. I'm not sure how well this will work in more complex scenarios (especially those involving multiple keys, as I have the key position hardcoded in the fake `keyrecord_t` to row 99 col 99) but it seems to work for me.
