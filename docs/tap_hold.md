# Tap-Hold Configuration Options

While Tap-Hold options are fantastic, they are not without their issues.  We have tried to configure them with reasonable defaults, but that may still cause issues for some people.

These options let you modify the behavior of the Tap-Hold keys.

## Tapping Term

The crux of all of the following features is the tapping term setting.  This determines what is a tap and what is a hold.  And the exact timing for this to feel natural can vary from keyboard to keyboard, from switch to switch, and from key to key.

You can set the global time for this by adding the following setting to your `config.h`:

```c
#define TAPPING_TERM 200
```

This setting is defined in milliseconds, and does default to 200ms.  This is a good average for a majority of people.

For more granular control of this feature, you can add the following to your `config.h`:
```c
#define TAPPING_TERM_PER_KEY
```

You can then add the following function to your keymap:

```c
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SFT_T(KC_SPC):
            return TAPPING_TERM + 1250;
        case LT(1, KC_GRV):
            return 130;
        default:
            return TAPPING_TERM;
    }
}
```

## Tap-Or-Hold Decision Modes

The code which decides between the tap and hold actions of dual-role keys supports three different modes, in increasing order of preference for the hold action:

1. The default mode selects the hold action only if the dual-role key is held down longer than the tapping term.  In this mode pressing other keys while the dual-role key is held down does not influence the tap-or-hold decision.

2. The “permissive hold” mode, in addition to the default behavior, immediately selects the hold action when another key is tapped (pressed and then released) while the dual-role key is held down, even if this happens earlier than the tapping term.  If another key is just pressed, but then the dual-role key is released before that other key (and earlier than the tapping term), this mode will still select the tap action.

3. The “hold on other key press” mode, in addition to the default behavior, immediately selects the hold action when another key is pressed while the dual-role key is held down, even if this happens earlier than the tapping term.

Note that until the tap-or-hold decision completes (which happens when either the dual-role key is released, or the tapping term has expired, or the extra condition for the selected decision mode is satisfied), key events are delayed and not transmitted to the host immediately.  The default mode gives the most delay (if the dual-role key is held down, this mode always waits for the whole tapping term), and the other modes may give less delay when other keys are pressed, because the hold action may be selected earlier.

### Permissive Hold

The “permissive hold” mode can be enabled for all dual-role keys by adding the corresponding option to `config.h`:

```c
#define PERMISSIVE_HOLD
```

This makes tap and hold keys (like Layer Tap) work better for fast typists, or for high `TAPPING_TERM` settings.

If you press a dual-role key, tap another key (press and release) and then release the dual-role key, all within the tapping term, by default the dual-role key will perform its tap action.  If the `PERMISSIVE_HOLD` option is enabled, the dual-role key will perform its hold action instead.

An example of a sequence which is affected by the “permissive hold” mode:

- `LT(2, KC_A)` Down
- `KC_L` Down (the `L` key is also mapped to `KC_RGHT` on layer 2)
- `KC_L` Up
- `LT(2, KC_A)` Up

Normally, if you do all this within the `TAPPING_TERM` (default: 200ms), this will be registered as `al` by the firmware and host system.  With the `PERMISSIVE_HOLD` option enabled, the Layer Tap key is considered as a layer switch if another key is tapped, and the above sequence would be registered as `KC_RGHT` (the mapping of `L` on layer 2).

However, this slightly different sequence will not be affected by the “permissive hold” mode:

- `LT(2, KC_A)` Down
- `KC_L` Down (the `L` key is also mapped to `KC_RGHT` on layer 2)
- `LT(2, KC_A)` Up
- `KC_L` Up

In the sequence above the dual-role key is released before the other key is released, and if that happens within the tapping term, the “permissive hold” mode will still choose the tap action for the dual-role key, and the sequence will be registered as `al` by the host.

?> The `PERMISSIVE_HOLD` option also affects Mod Tap keys, but this may not be noticeable if you do not also enable the `IGNORE_MOD_TAP_INTERRUPT` option for those keys, because the default handler for Mod Tap keys also considers both the “nested press” and “rolling press” sequences like shown above as a modifier hold, not the tap action.  If you do not enable `IGNORE_MOD_TAP_INTERRUPT`, the effect of `PERMISSIVE_HOLD` on Mod Tap keys would be limited to reducing the delay before the key events are made visible to the host.

For more granular control of this feature, you can add the following to your `config.h`:

```c
#define PERMISSIVE_HOLD_PER_KEY
```

You can then add the following function to your keymap:

```c
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(1, KC_BSPC):
            // Immediately select the hold action when another key is tapped.
            return true;
        default:
            // Do not select the hold action when another key is tapped.
            return false;
    }
}
```

### Hold On Other Key Press

The “hold on other key press” mode can be enabled for all dual-role keys by adding the corresponding option to `config.h`:

```c
#define HOLD_ON_OTHER_KEY_PRESS
```

This mode makes tap and hold keys (like Layer Tap) work better for fast typists, or for high `TAPPING_TERM` settings.  Compared to the “permissive hold” mode, this mode selects the hold action in more cases.

If you press a dual-role key, press another key, and then release the dual-role key, all within the tapping term, by default the dual-role key will perform its tap action.  If the `HOLD_ON_OTHER_KEY_PRESS` option is enabled, the dual-role key will perform its hold action instead.

An example of a sequence which is affected by the “hold on other key press” mode, but not by the “permissive hold” mode:

- `LT(2, KC_A)` Down
- `KC_L` Down (the `L` key is also mapped to `KC_RGHT` on layer 2)
- `LT(2, KC_A)` Up
- `KC_L` Up

Normally, if you do all this within the `TAPPING_TERM` (default: 200ms), this will be registered as `al` by the firmware and host system.  With the `HOLD_ON_OTHER_KEY_PRESS` option enabled, the Layer Tap key is considered as a layer switch if another key is pressed, and the above sequence would be registered as `KC_RGHT` (the mapping of `L` on layer 2).

?> The `HOLD_ON_OTHER_KEY_PRESS` option also affects Mod Tap keys, but this may not be noticeable if you do not also enable the `IGNORE_MOD_TAP_INTERRUPT` option for those keys, because the default handler for Mod Tap keys also considers the “rolling press” sequence like shown above as a modifier hold, not the tap action.  If you do not enable `IGNORE_MOD_TAP_INTERRUPT`, the effect of `HOLD_ON_OTHER_KEY_PRESS` on Mod Tap keys would be limited to reducing the delay before the key events are made visible to the host.

For more granular control of this feature, you can add the following to your `config.h`:

```c
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY
```

You can then add the following function to your keymap:

```c
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(1, KC_BSPC):
            // Immediately select the hold action when another key is pressed.
            return true;
        default:
            // Do not select the hold action when another key is pressed.
            return false;
    }
}
```


## Ignore Mod Tap Interrupt

To enable this setting, add this to your `config.h`:

```c
#define IGNORE_MOD_TAP_INTERRUPT
```

?> This option affects only the Mod Tap keys; it does not affect other dual-role keys such as Layer Tap.

By default the tap-or-hold decision for Mod Tap keys strongly prefers the hold action.  If you press a Mod Tap key, then press another key while still holding the Mod Tap key down, the Mod Tap press will be handled as a modifier hold even if the Mod Tap key is then released within the tapping term, and irrespective of the order in which those keys are released.  Using options such as `PERMISSIVE_HOLD` or `HOLD_ON_OTHER_KEY_PRESS` will not affect the functionality of Mod Tap keys in a major way (these options would still affect the delay until the common code for dual-role keys finishes its tap-or-hold decision, but then the special code for Mod Tap keys will override the result of that decision and choose the hold action if another key was pressed).  In fact, by default the tap-or-hold decision for Mod Tap keys is done in the same way as if the `HOLD_ON_OTHER_KEY_PRESS` option was enabled, but without the decreased delay provided by `HOLD_ON_OTHER_KEY_PRESS`.

If the `IGNORE_MOD_TAP_INTERRUPT` option is enabled, Mod Tap keys are no longer treated as a special case, and their behavior will match the behavior of other dual-role keys such as Layer Tap.  Then the behavior of Mod Tap keys can be further tuned using other options such as `PERMISSIVE_HOLD` or `HOLD_ON_OTHER_KEY_PRESS`.

An example of a sequence which will be affected by the `IGNORE_MOD_TAP_INTERRUPT` option (assuming that options like `PERMISSIVE_HOLD` or `HOLD_ON_OTHER_KEY_PRESS` are not enabled):

- `SFT_T(KC_A)` Down
- `KC_X` Down
- `SFT_T(KC_A)` Up
- `KC_X` Up

Normally, this would send a capital `X` (`SHIFT`+`x`), even if the sequence is performed faster than the `TAPPING_TERM`.  However, if the `IGNORE_MOD_TAP_INTERRUPT` option is enabled, the `SFT_T(KC_A)` key must be held longer than the `TAPPING_TERM` to register the hold action.  A quick tap will output `ax` in this case, while a hold will still output a capital `X` (`SHIFT`+`x`).

However, if the `HOLD_ON_OTHER_KEY_PRESS` option is enabled in addition to `IGNORE_MOD_TAP_INTERRUPT`, the above sequence will again send a capital `X` (`SHIFT`+`x`) even if performed faster that the `TAPPING_TERM`.  The difference from the default configuration is that by default the host will receive the key events only after the `SFT_T(KC_A)` key is released, but with the `HOLD_ON_OTHER_KEY_PRESS` option the host will start receiving key events when the `KC_X` key is pressed.

For more granular control of this feature, you can add the following to your `config.h`:

```c
#define IGNORE_MOD_TAP_INTERRUPT_PER_KEY
```

You can then add the following function to your keymap:

```c
bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SFT_T(KC_SPC):
            // Do not force the mod-tap key press to be handled as a modifier
            // if any other key was pressed while the mod-tap key is held down.
            return true;
        default:
            // Force the mod-tap key press to be handled as a modifier if any
            // other key was pressed while the mod-tap key is held down.
            return false;
    }
}
```

## Tapping Force Hold

To enable `tapping force hold`, add the following to your `config.h`:

```c
#define TAPPING_FORCE_HOLD
```

When the user holds a key after tapping it, the tapping function is repeated by default, rather than activating the hold function. This allows keeping the ability to auto-repeat the tapping function of a dual-role key. `TAPPING_FORCE_HOLD` removes that ability to let the user activate the hold function instead, in the case of holding the dual-role key after having tapped it.

Example:

- `SFT_T(KC_A)` Down
- `SFT_T(KC_A)` Up
- `SFT_T(KC_A)` Down
- wait until the tapping term expires...
- `SFT_T(KC_A)` Up

With default settings, `a` will be sent on the first release, then `a` will be sent on the second press allowing the computer to trigger its auto repeat function.

With `TAPPING_FORCE_HOLD`, the second press will be interpreted as a Shift, allowing to use it as a modifier shortly after having used it as a tap.

!> `TAPPING_FORCE_HOLD` will break anything that uses tapping toggles (Such as the `TT` layer keycode, and the One Shot Tap Toggle).

For more granular control of this feature, you can add the following to your `config.h`:

```c
#define TAPPING_FORCE_HOLD_PER_KEY
```

You can then add the following function to your keymap:

```c
bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(1, KC_BSPC):
            return true;
        default:
            return false;
    }
}
```

## Retro Tapping

To enable `retro tapping`, add the following to your `config.h`:

```c
#define RETRO_TAPPING
```

Holding and releasing a dual function key without pressing another key will result in nothing happening. With retro tapping enabled, releasing the key without pressing another will send the original keycode even if it is outside the tapping term.

For instance, holding and releasing `LT(2, KC_SPACE)` without hitting another key will result in nothing happening. With this enabled, it will send `KC_SPACE` instead.

For more granular control of this feature, you can add the following to your `config.h`:

```c
#define RETRO_TAPPING_PER_KEY
```

You can then add the following function to your keymap:

```c
bool get_retro_tapping(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(2, KC_SPACE):
            return true;
        default:
            return false;
    }
}
```

## Why do we include the key record for the per key functions?

One thing that you may notice is that we include the key record for all of the "per key" functions, and may be wondering why we do that.

Well, it's simple really: customization.  But specifically, it depends on how your keyboard is wired up.  For instance, if each row is actually using a row in the keyboard's matrix, then it may be simpler to use `if (record->event.row == 3)` instead of checking a whole bunch of keycodes.  Which is especially good for those people using the Tap Hold type keys on the home row. So you could fine tune those to not interfere with your normal typing.

## Why is there no `*_kb` or `*_user` functions?!

Unlike many of the other functions here, there isn't a need (or even reason) to have a quantum or keyboard level function. Only user level functions are useful here, so no need to mark them as such.
