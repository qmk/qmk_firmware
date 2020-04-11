# Tap-Hold Configuration Options

While Tap-Hold options are fantastic, they are not without their issues.  We have tried to configure them with reasonable defaults, but that may still cause issues for some people. 

These options let you modify the behavior of the Tap-Hold keys.

## Permissive Hold

As of [PR#1359](https://github.com/qmk/qmk_firmware/pull/1359/), there is a new `config.h` option:

```c
#define PERMISSIVE_HOLD
```

This makes tap and hold keys (like Mod Tap) work better for fast typist, or for high `TAPPING_TERM` settings. 

If you press a Mod Tap key, tap another key (press and release) and then release the Mod Tap key, all within the tapping term, it will output the "tapping" function for both keys.

For Instance:

- `SFT_T(KC_A)` Down
- `KC_X` Down
- `KC_X` Up
- `SFT_T(KC_A)` Up

Normally, if you do all this within the `TAPPING_TERM` (default: 200ms) this will be registered as `ax` by the firmware and host system. With permissive hold enabled, this modifies how this is handled by considering the Mod Tap keys as a Mod if another key is tapped, and would registered as `X` (`SHIFT`+`x`). 

?> If you have `Ignore Mod Tap Interrupt` enabled, as well, this will modify how both work. The regular key has the modifier added if the first key is released first or if both keys are held longer than the `TAPPING_TERM`.

## Ignore Mod Tap Interrupt

To enable this setting, add this to your `config.h`:

```c
#define IGNORE_MOD_TAP_INTERRUPT
```

Similar to Permissive Hold, this alters how the firmware processes input for fast typist. If you press a Mod Tap key, press another key, release the Mod Tap key, and then release the normal key, it would normally output the "tapping" function for both keys. This may not be desirable for rolling combo keys. 

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
bool get_ignore_mod_tap_interrupt(uint16_t keycode) {
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

When the user holds a key after tap, this repeats the tapped key rather to hold a modifier key.  This allows to use auto repeat for the tapped key.  

Example:

- SFT_T(KC_A) Down
- SFT_T(KC_A) Up
- SFT_T(KC_A) Down
- wait more than tapping term...
- SFT_T(KC_A) Up

With default settings, `a` will be sent on the first release, then `a` will be sent on the second press allowing the computer to trigger its auto repeat function.

With `TAPPING_FORCE_HOLD`, the second press will be interpreted as a Shift, allowing to use it as a modifier shortly after having used it as a tap.

!> `TAPPING_FORCE_HOLD` will break anything that uses tapping toggles (Such as the `TT` layer keycode, and the One Shot Tapping Toggle).

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
