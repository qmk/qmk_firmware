# Auto Shift: Why Do We Need a Shift Key?

Tap a key and you get its character. Tap a key, but hold it *slightly* longer
and you get its shifted state. Voilà! No shift key needed!

## Why Auto Shift?

Many people suffer from various forms of RSI. A common cause is stretching your
fingers repetitively long distances. For us on the keyboard, the pinky does that
all too often when reaching for the shift key. Auto Shift looks to alleviate that
problem.

## How Does It Work?

When you tap a key, it stays depressed for a short period of time before it is
then released. This depressed time is a different length for everyone. Auto Shift
defines a constant `AUTO_SHIFT_TIMEOUT` which is typically set to twice your
normal pressed state time. When you press a key, a timer starts, and if you
have not released the key after the `AUTO_SHIFT_TIMEOUT` period, then a shifted
version of the key is emitted. If the time is less than the `AUTO_SHIFT_TIMEOUT`
time, or you press another key, then the normal state is emitted.

If `AUTO_SHIFT_REPEAT` is defined, there is keyrepeat support. Holding the key
down will repeat the shifted key, though this can be disabled with
`AUTO_SHIFT_NO_AUTO_REPEAT`. If you want to repeat the normal key, then tap it
once then immediately (within `TAPPING_TERM`) hold it down again (this works
with the shifted value as well if auto-repeat is disabled).

There are also the `get_auto_shift_repeat` and `get_auto_shift_no_auto_repeat`
functions for more granular control. Neither will have an effect unless
`AUTO_SHIFT_REPEAT_PER_KEY` or `AUTO_SHIFT_NO_AUTO_REPEAT_PER_KEY` respectively
are defined.

## Are There Limitations to Auto Shift?

Yes, unfortunately.

1. You will have characters that are shifted when you did not intend on shifting, and
   other characters you wanted shifted, but were not. This simply comes down to
   practice. As we get in a hurry, we think we have hit the key long enough for a
   shifted version, but we did not. On the other hand, we may think we are tapping
   the keys, but really we have held it for a little longer than anticipated.
2. Additionally, with keyrepeat the desired shift state can get mixed up. It will
   always 'belong' to the last key pressed. For example, keyrepeating a capital
   and then tapping something lowercase (whether or not it's an Auto Shift key)
   will result in the capital's *key* still being held, but shift not.
3. Auto Shift does not apply to Tap Hold keys. For automatic shifting of Tap Hold
   keys see [Retro Shift](#retro-shift).

## How Do I Enable Auto Shift?

Add to your `rules.mk` in the keymap folder:

```
AUTO_SHIFT_ENABLE = yes
```

If no `rules.mk` exists, you can create one.

Then compile and install your new firmware with Auto Key enabled! That's it!

## Modifiers

By default, Auto Shift is disabled for any key press that is accompanied by one or more
modifiers. Thus, Ctrl+A that you hold for a really long time is not the same
as Ctrl+Shift+A.

You can re-enable Auto Shift for modifiers by adding a define to your `config.h`

```c
#define AUTO_SHIFT_MODIFIERS
```

In which case, Ctrl+A held past the `AUTO_SHIFT_TIMEOUT` will be sent as Ctrl+Shift+A


## Configuring Auto Shift

If desired, there is some configuration that can be done to change the
behavior of Auto Shift. This is done by setting various variables the
`config.h` file located in your keymap folder. If no `config.h` file exists, you can create one.

A sample is

```c
#pragma once

#define AUTO_SHIFT_TIMEOUT 150
#define NO_AUTO_SHIFT_SPECIAL
```

### AUTO_SHIFT_TIMEOUT (Value in ms)

This controls how long you have to hold a key before you get the shifted state.
Obviously, this is different for everyone. For the common person, a setting of
135 to 150 works great. However, one should start with a value of at least 175, which
is the default value. Then work down from there. The idea is to have the shortest time required to get the shifted state without having false positives.

Play with this value until things are perfect. Many find that all will work well
at a given value, but one or two keys will still emit the shifted state on
occasion. This is simply due to habit and holding some keys a little longer
than others. Once you find this value, work on tapping your problem keys a little
quicker than normal and you will be set.

::: tip
Auto Shift has three special keys that can help you get this value right very quick. See "Auto Shift Setup" for more details!
:::

For more granular control of this feature, you can add the following to your `config.h`:

```c
#define AUTO_SHIFT_TIMEOUT_PER_KEY
```

You can then add the following function to your keymap:

```c
uint16_t get_autoshift_timeout(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case AUTO_SHIFT_NUMERIC:
            return 2 * get_generic_autoshift_timeout();
        case AUTO_SHIFT_SPECIAL:
            return get_generic_autoshift_timeout() + 50;
        case AUTO_SHIFT_ALPHA:
        default:
            return get_generic_autoshift_timeout();
    }
}
```

Note that you cannot override individual keys that are in one of those groups
if you are using them; trying to add a case for `KC_A` in the above example will
not compile as `AUTO_SHIFT_ALPHA` is there. A possible solution is a second switch
above to handle individual keys with no default case and only referencing the
groups in the below fallback switch.

### NO_AUTO_SHIFT_SPECIAL (simple define)

Do not Auto Shift special keys, which include -\_, =+, [{, ]}, ;:, '", ,<, .>,
/?, and the KC_TAB.

### NO_AUTO_SHIFT_TAB (simple define)

Do not Auto Shift KC_TAB but leave Auto Shift enabled for the other special
characters.

### NO_AUTO_SHIFT_SYMBOLS (simple define)

Do not Auto Shift symbol keys, which include -\_, =+, [{, ]}, ;:, '", ,<, .>,
and /?.

### NO_AUTO_SHIFT_NUMERIC (simple define)

Do not Auto Shift numeric keys, zero through nine.

### NO_AUTO_SHIFT_ALPHA (simple define)

Do not Auto Shift alpha characters, which include A through Z.

### AUTO_SHIFT_ENTER (simple define)

Auto Shift the enter key.

### Auto Shift Per Key

There are functions that allows you to determine which keys should be autoshifted, much like the tap-hold keys.

The first of these, used to simply add a key to Auto Shift, is `get_custom_auto_shifted_key`:

```c
bool get_custom_auto_shifted_key(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case KC_DOT:
            return true;
        default:
            return false;
    }
}
```

For more granular control, there is `get_auto_shifted_key`. The default function looks like this:

```c
bool get_auto_shifted_key(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
# ifndef NO_AUTO_SHIFT_ALPHA
        case AUTO_SHIFT_ALPHA:
# endif
# ifndef NO_AUTO_SHIFT_NUMERIC
        case AUTO_SHIFT_NUMERIC:
# endif
# ifndef NO_AUTO_SHIFT_SPECIAL
# ifndef NO_AUTO_SHIFT_TAB
        case KC_TAB:
#        endif
# ifndef NO_AUTO_SHIFT_SYMBOLS
        case AUTO_SHIFT_SYMBOLS:
#        endif
# endif
# ifdef AUTO_SHIFT_ENTER
        case KC_ENT:
# endif
            return true;
    }
    return get_custom_auto_shifted_key(keycode, record);
}
```

This functionality is enabled by default, and does not need a define.

### AUTO_SHIFT_REPEAT (simple define)

Enables keyrepeat.

### AUTO_SHIFT_NO_AUTO_REPEAT (simple define)

Disables automatically keyrepeating when `AUTO_SHIFT_TIMEOUT` is exceeded.


### AUTO_SHIFT_ALPHA (predefined key group)

A predefined group of keys representing A through Z.

### AUTO_SHIFT_NUMERIC (predefined key group)

A predefined group of keys representing 0 through 9. Note, these are defined as
1 through 0 since that is the order they normally appear in.

### AUTO_SHIFT_SYMBOLS (predefined key group)

A predefined group of keys representing symbolic characters which include -\_, =+, [{, ]}, ;:, '", ,<, .>,
and /?.

### AUTO_SHIFT_SPECIAL (predefined key group)

A predefined group of keys that combines AUTO_SHIFT_SYMBOLS and KC_TAB.

## Custom Shifted Values

Especially on small keyboards, the default shifted value for many keys is not
optimal. To provide more customizability, there are two user-definable
functions, `autoshift_press/release_user`. These register or unregister the
correct value for the passed key. Below is an example adding period to Auto
Shift and making its shifted value exclamation point. Make sure to use weak
mods - setting real would make any keys following it use their shifted values
as if you were holding the key. Clearing of modifiers is handled by Auto Shift,
and the OS-sent shift value if keyrepeating multiple keys is always that of
the last key pressed (whether or not it's an Auto Shift key).

You can also have non-shifted keys for the shifted values (or even no shifted
value), just don't set a shift modifier!

```c
bool get_custom_auto_shifted_key(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case KC_DOT:
            return true;
        default:
            return false;
    }
}

void autoshift_press_user(uint16_t keycode, bool shifted, keyrecord_t *record) {
    switch(keycode) {
        case KC_DOT:
            register_code16((!shifted) ? KC_DOT : KC_EXLM);
            break;
        default:
            if (shifted) {
                add_weak_mods(MOD_BIT(KC_LSFT));
            }
            // & 0xFF gets the Tap key for Tap Holds, required when using Retro Shift
            register_code16((IS_RETRO(keycode)) ? keycode & 0xFF : keycode);
    }
}

void autoshift_release_user(uint16_t keycode, bool shifted, keyrecord_t *record) {
    switch(keycode) {
        case KC_DOT:
            unregister_code16((!shifted) ? KC_DOT : KC_EXLM);
            break;
        default:
            // & 0xFF gets the Tap key for Tap Holds, required when using Retro Shift
            // The IS_RETRO check isn't really necessary here, always using
            // keycode & 0xFF would be fine.
            unregister_code16((IS_RETRO(keycode)) ? keycode & 0xFF : keycode);
    }
}
```

## Retro Shift

Holding and releasing a Tap Hold key without pressing another key will ordinarily
result in only the hold. With `retro shift` enabled this action will instead
produce a shifted version of the tap keycode on release.

It does not require [Retro Tapping](tap_hold#retro-tapping) to be enabled, and
if both are enabled the state of `retro tapping` will only apply if the tap keycode
is not matched by Auto Shift. `RETRO_TAPPING_PER_KEY` and its corresponding
function, however, are checked before `retro shift` is applied.

To enable `retro shift`, add the following to your `config.h`:

```c
#define RETRO_SHIFT
```

If `RETRO_SHIFT` is defined to a value, hold times greater than that value will
not produce a tap on release for Mod Taps, and instead triggers the hold action.
This enables modifiers to be held for combining with mouse clicks without
generating taps on release. For example:

```c
#define RETRO_SHIFT 500
```

Without a value set, holds of any length without an interrupting key will produce the shifted value.

This value (if set) must be greater than one's `TAPPING_TERM`, as the key press
must be designated as a 'hold' by `process_tapping` before we send the modifier.
[Per-key tapping terms](tap_hold#tapping-term) can be used as a workaround.
There is no such limitation in regards to `AUTO_SHIFT_TIMEOUT` for normal keys.

**Note:** Tap Holds must be added to Auto Shift, see [here.](feature_auto_shift#auto-shift-per-key)
`IS_RETRO` may be helpful if one wants all Tap Holds retro shifted.

### Retro Shift and Tap Hold Configurations

Tap Hold Configurations work a little differently when using Retro Shift.
Referencing `TAPPING_TERM` makes little sense, as holding longer would result in
shifting one of the keys.

`RETRO_SHIFT` enables [`PERMISSIVE_HOLD`-like behaviour](tap_hold#permissive-hold) (even if not explicitly enabled) on all mod-taps for which `RETRO_SHIFT` applies.

## Using Auto Shift Setup

This will enable you to define three keys temporarily to increase, decrease and report your `AUTO_SHIFT_TIMEOUT`.

### Setup

Map three keys temporarily in your keymap:

|Keycode               |Aliases  |Description                                 |
|----------------------|---------|--------------------------------------------|
|`QK_AUTO_SHIFT_DOWN`  |`AS_DOWN`|Lower the Auto Shift timeout variable (down)|
|`QK_AUTO_SHIFT_UP`    |`AS_UP`  |Raise the Auto Shift timeout variable (up)  |
|`QK_AUTO_SHIFT_REPORT`|`AS_RPT` |Report your current Auto Shift timeout value|
|`QK_AUTO_SHIFT_ON`    |`AS_ON`  |Turns on the Auto Shift Function            |
|`QK_AUTO_SHIFT_OFF`   |`AS_OFF` |Turns off the Auto Shift Function           |
|`QK_AUTO_SHIFT_TOGGLE`|`AS_TOGG`|Toggles the state of the Auto Shift feature |

Compile and upload your new firmware.

### Use

It is important to note that during these tests, you should be typing
completely normal and with no intention of shifted keys.

1. Type multiple sentences of alphabetical letters.
2. Observe any upper case letters.
3. If there are none, press the key you have mapped to `AS_DOWN` to decrease
   time Auto Shift timeout value and go back to step 1.
4. If there are some upper case letters, decide if you need to work on tapping
   those keys with less down time, or if you need to increase the timeout.
5. If you decide to increase the timeout, press the key you have mapped to
   `AS_UP` and go back to step 1.
6. Once you are happy with your results, press the key you have mapped to
   `AS_RPT`. The keyboard will type by itself the value of your
   `AUTO_SHIFT_TIMEOUT`.
7. Update `AUTO_SHIFT_TIMEOUT` in your `config.h` with the value reported.
8. Add `AUTO_SHIFT_NO_SETUP` to your `config.h`.
9. Remove the key bindings `AS_DOWN`, `AS_UP` and `AS_RPT`.
10. Compile and upload your new firmware.

#### An Example Run

```
hello world. my name is john doe. i am a computer programmer playing with
keyboards right now.

[PRESS AS_DOWN quite a few times]

heLLo woRLd. mY nAMe is JOHn dOE. i AM A compUTeR proGRaMMER PlAYiNG witH
KEYboArDS RiGHT NOw.

[PRESS AS_UP a few times]

hello world. my name is john Doe. i am a computer programmer playing with
keyboarDs right now.

[PRESS AS_RPT]

115
```

The keyboard typed `115` which represents your current `AUTO_SHIFT_TIMEOUT`
value. You are now set! Practice on the *D* key a little bit that showed up
in the testing and you'll be golden.
