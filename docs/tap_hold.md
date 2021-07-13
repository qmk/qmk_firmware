# Tap-Hold Configuration Options

While Tap-Hold options are fantastic, they are not without their issues.  We have tried to configure them with reasonable defaults, but that may still cause issues for some people.

These options let you modify the behavior of the Tap-Hold keys.

## Tapping Term

The crux of all of the following features is the tapping term setting.  This determines what is a tap and what is a hold.  The exact timing for this to feel natural can vary from keyboard to keyboard, from switch to switch, and from key to key.

?> `TAP_TERM_KEYS_ENABLE` enables three special keys that can help you quickly find a comfortable tapping term for you. See "Tapping Term Keys" for more details.

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

### Tapping Term Keys :id=tapping-term-keys

Not to be confused with `TAPPING_TERM_PER_KEY`, `TAP_TERM_KEYS_ENABLE` is a feature you can enable in `rules.mk` that lets you use three special keys in your keymap to configure the tapping term on the fly.

| Key         | Description                                                                                             |
|-------------|---------------------------------------------------------------------------------------------------------|
| `TK_PRINT`  | "Tapping Term Keys Print": Types the current tapping term, in milliseconds                              |
| `TK_UP`     | "Tapping Term Keys Up": Increases the current tapping term by `TAP_TERM_INCREMENT`ms (5ms by default)   |
| `TK_DOWN`   | "Tapping Term Keys Down": Decreases the current tapping term by `TAP_TERM_INCREMENT`ms (5ms by default) |

Set the tapping term as usual with `#define TAPPING_TERM <value>` in `config.h` and add `TAP_TERM_KEYS_ENABLE = yes` in `rules.mk`. Then, place the above three keys somewhere in your keymap and flash the new firmware onto your board.

Now, you can try using your dual-role keys, such as layer-taps and mod-taps, and use `TK_DOWN` and `TK_UP` to adjust the tapping term immediately. If you find that you frequently trigger the modifier of your mod-tap(s) by accident for example, that's a sign that your tapping term may be too low so, tap `TK_UP` a few times to increase the tapping term until that no longer happens. On the flip side, if you get superfluous characters when you actually intended to momentarily activate a layer, tap `TK_DOWN` to lower the tapping term. Do note that these keys affect the *global* tapping term, you cannot change the tapping term of a specific key on the fly.

Once you're satisfied with the current tapping term value, open `config.h` and replace whatever value you first wrote for the tapping term by the output of the `TK_PRNT` key.

It's important to update `TAPPING_TERM` with the new value because the adjustments made using `TK_UP` and `TK_DOWN` are not persistent.

The value by which the tapping term increases or decreases when you tap `TK_UP` and `TK_DOWN` can be configured in `config.h` with `#define TAP_TERM_INCREMENT <new value>`.

In order for this feature to be effective if you use per-key tapping terms, you need to make a few changes to the syntax of the `get_tapping_term` function. All you need to do is replace every occurrence of `TAPPING_TERM` in the `get_tapping_term` function by lowercase `tapping_term`.

The reason being that `TAPPING_TERM` is a macro that expands to a constant integer and thus cannot be changed at runtime whereas `tapping_term` is a variable whose value can be changed at runtime. If you want, you can temporarily enable `TAP_TERM_KEYS_ENABLE` to find a suitable tapping term value and then disable that feature and revert back to using the classic syntax for per-key tapping term settings.

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

Similar to Permissive Hold, this alters how the firmware processes inputs for fast typists. If you press a Mod Tap key, press another key, release the Mod Tap key, and then release the normal key, it would normally output the Mod plus the normal key, even if pressed within the `TAPPING_TERM`. This may not be desirable for rolling combo keys, or for fast typists who have a Mod Tap on a frequently used key (`RCTL_T(KC_QUOT)`, for example).

Setting `Ignore Mod Tap Interrupt` requires  holding both keys for the `TAPPING_TERM` to trigger the hold function (the mod).

For Instance:

- `SFT_T(KC_A)` Down
- `KC_X` Down
- `SFT_T(KC_A)` Up
- `KC_X` Up

Normally, this would send a capital `X` (`SHIFT`+`x`), or, Mod + key. With `Ignore Mod Tap Interrupt` enabled, holding both keys are required for the `TAPPING_TERM` to register the hold action. A quick tap will output `ax` in this case, while a hold on both will still output capital `X` (`SHIFT`+`x`).


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
