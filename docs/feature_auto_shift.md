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
normal pressed state time. When you press a key, a timer starts and then stops
when you release the key. If the time depressed is greater than or equal to the
`AUTO_SHIFT_TIMEOUT`, then a shifted version of the key is emitted. If the time
is less than the `AUTO_SHIFT_TIMEOUT` time, then the normal state is emitted.

## Are There Limitations to Auto Shift?

Yes, unfortunately.

1. Key repeat will cease to work. For example, before if you wanted 20 'a'
   characters, you could press and hold the 'a' key for a second or two. This no
   longer works with Auto Shift because it is timing your depressed time instead
   of emitting a depressed key state to your operating system.
2. You will have characters that are shifted when you did not intend on shifting, and
   other characters you wanted shifted, but were not. This simply comes down to
   practice. As we get in a hurry, we think we have hit the key long enough
   for a shifted version, but we did not. On the other hand, we may think we are
   tapping the keys, but really we have held it for a little longer than
   anticipated.

## How Do I Enable Auto Shift?

Add to your `rules.mk` in the keymap folder:

    AUTO_SHIFT_ENABLE = yes

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

?> Auto Shift has three special keys that can help you get this value right very quick. See "Auto Shift Setup" for more details!

### NO_AUTO_SHIFT_SPECIAL (simple define)

Do not Auto Shift special keys, which include -\_, =+, [{, ]}, ;:, '", ,<, .>,
and /?

### NO_AUTO_SHIFT_NUMERIC (simple define)

Do not Auto Shift numeric keys, zero through nine.

### NO_AUTO_SHIFT_ALPHA (simple define)

Do not Auto Shift alpha characters, which include A through Z.

## Using Auto Shift Setup

Add `AUTO_SHIFT_SETUP` to your `config.h` to enable you to define three keys temporarily to increase, decrease and report your `AUTO_SHIFT_TIMEOUT`.

### Setup


Map three keys temporarily in your keymap:

| Key Name | Description                                         |
|----------|-----------------------------------------------------|
| KC_ASDN  | Lower the Auto Shift timeout variable (down)        |
| KC_ASUP  | Raise the Auto Shift timeout variable (up)          |
| KC_ASRP  | Report your current Auto Shift timeout value        |
| KC_ASON  | Turns on the Auto Shift Function                    |
| KC_ASOFF | Turns off the Auto Shift Function                   |
| KC_ASTG  | Toggles the state of the Auto Shift feature         |

Compile and upload your new firmware.

### Use

It is important to note that during these tests, you should be typing
completely normal and with no intention of shifted keys.

1. Type multiple sentences of alphabetical letters.
2. Observe any upper case letters.
3. If there are none, press the key you have mapped to `KC_ASDN` to decrease
   time Auto Shift timeout value and go back to step 1.
4. If there are some upper case letters, decide if you need to work on tapping
   those keys with less down time, or if you need to increase the timeout.
5. If you decide to increase the timeout, press the key you have mapped to
   `KC_ASUP` and go back to step 1.
6. Once you are happy with your results, press the key you have mapped to
   `KC_ASRP`. The keyboard will type by itself the value of your
   `AUTO_SHIFT_TIMEOUT`.
7. Update `AUTO_SHIFT_TIMEOUT` in your `config.h` with the value reported.
8. Remove `AUTO_SHIFT_SETUP` from your `config.h`.
9. Remove the key bindings `KC_ASDN`, `KC_ASUP` and `KC_ASRP`.
10. Compile and upload your new firmware.

#### An Example Run

    hello world. my name is john doe. i am a computer programmer playing with
    keyboards right now.

    [PRESS KC_ASDN quite a few times]

    heLLo woRLd. mY nAMe is JOHn dOE. i AM A compUTeR proGRaMMER PlAYiNG witH
    KEYboArDS RiGHT NOw.

    [PRESS KC_ASUP a few times]

    hello world. my name is john Doe. i am a computer programmer playing with
    keyboarDs right now.

    [PRESS KC_ASRP]

    115

The keyboard typed `115` which represents your current `AUTO_SHIFT_TIMEOUT`
value. You are now set! Practice on the *D* key a little bit that showed up
in the testing and you'll be golden.
