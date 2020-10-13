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


## Permissive Hold

As of [PR#1359](https://github.com/qmk/qmk_firmware/pull/1359/), there is a new `config.h` option:

```c
#define PERMISSIVE_HOLD
```

This makes tap and hold keys (like Mod Tap) work better for fast typists, or for high `TAPPING_TERM` settings.

If you press a Mod Tap key, tap another key (press and release) and then release the Mod Tap key, all within the tapping term, it will output the tapping function for both keys.

For Instance:

- `SFT_T(KC_A)` Down
- `KC_X` Down
- `KC_X` Up
- `SFT_T(KC_A)` Up

Normally, if you do all this within the `TAPPING_TERM` (default: 200ms) this will be registered as `ax` by the firmware and host system. With permissive hold enabled, this modifies how this is handled by considering the Mod Tap keys as a Mod if another key is tapped, and would registered as `X` (`SHIFT`+`x`).

?> If you have `Ignore Mod Tap Interrupt` enabled, as well, this will modify how both work. The regular key has the modifier added if the first key is released first or if both keys are held longer than the `TAPPING_TERM`.

For more granular control of this feature, you can add the following to your `config.h`:

```c
#define PERMISSIVE_HOLD_PER_KEY
```

You can then add the following function to your keymap:

```c
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(1, KC_BSPC):
            return true;
        default:
            return false;
    }
}
```

## Ignore Mod Tap Interrupt

To enable this setting, add this to your `config.h`:

```c
#define IGNORE_MOD_TAP_INTERRUPT
```

Similar to Permissive Hold, this alters how the firmware processes inputs for fast typists. If you press a Mod Tap key, press another key, release the Mod Tap key, and then release the normal key, it would normally output the tapping function for both keys. This may not be desirable for rolling combo keys.

Setting `Ignore Mod Tap Interrupt` requires  holding both keys for the `TAPPING_TERM` to trigger the hold function (the mod).

For Instance:

- `SFT_T(KC_A)` Down
- `KC_X` Down
- `SFT_T(KC_A)` Up
- `KC_X` Up

Normally, this would send `X` (`SHIFT`+`x`). With `Ignore Mod Tap Interrupt` enabled, holding both keys are required for the `TAPPING_TERM` to register the hold action. A quick tap will output `ax` in this case, while a hold on both will still output `X`  (`SHIFT`+`x`).


?> __Note__: This only concerns modifiers and not layer switching keys.

?> If you have `Permissive Hold` enabled, as well, this will modify how both work. The regular key has the modifier added if the first key is released first or if both keys are held longer than the `TAPPING_TERM`.

For more granular control of this feature, you can add the following to your `config.h`:

```c
#define IGNORE_MOD_TAP_INTERRUPT_PER_KEY
```

You can then add the following function to your keymap:

```c
bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SFT_T(KC_SPC):
            return true;
        default:
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

## Why do we include the key record for the per key functions?

One thing that you may notice is that we include the key record for all of the "per key" functions, and may be wondering why we do that.

Well, it's simple really: customization.  But specifically, it depends on how your keyboard is wired up.  For instance, if each row is actually using a row in the keyboard's matrix, then it may be simpler to use `if (record->event.row == 3)` instead of checking a whole bunch of keycodes.  Which is especially good for those people using the Tap Hold type keys on the home row. So you could fine tune those to not interfere with your normal typing.

## Why is there no `*_kb` or `*_user` functions?!

Unlike many of the other functions here, there isn't a need (or even reason) to have a quantum or keyboard level function. Only user level functions are useful here, so no need to mark them as such.
