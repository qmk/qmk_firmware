# DecenTKL

*A TKL keyboard inspired by the language design of Atari XE and ST computers*

* Keyboard Maintainer: [Bertrand Le roy](https://github.com/bleroy/3d-junkyard/blob/main/DecenTKL/)
* Hardware Supported: DecenTKL (Pi Pico based)
* Hardware Availability: Custom built but open-source

Make example for this keyboard (after setting up your build environment):

    make decent/tkl:default

Flashing example for this keyboard:

    make decent/tkl:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Press the escape key or the button on the back of the Pi while connecting the keyboard.

## Special commands

Fn + F1: Open my computer
Fn + F2: Browser home
Fn + F3: Open calculator
Fn + F4: Open media player
Fn + F5: Previous media
Fn + F6: Next media
Fn + F7: Play media
Fn + F8: Stop media
Fn + F9: Mute
Fn + PgUp: Volume up
Fn + PgDn: Volume down
Fn + 1: Toggle RGB lighting
Fn + Up: Next RGB effect
Fn + Down: Previous RGB effect
Fn + X: Change RGB hue
Fn + S: Lower RGB brightness
Fn + W: Raise RGB brightness
Fn + Left: Lower RGB animation speed
Fn + Right: Raise RGB animation speed

Fn + \: go into bootloader mode without unplugging the keyboard

## Layout
```C
/*
    *   /─────/       /─────/─────/─────/─────/─────/─────/─────/─────/─────/─────/
    *  /Esc  /       /F1   /F2   /F3   /F4   /F5   /F6   /F7   /F8   /F9   /F10  /
    * /─────/       /─────/─────/─────/─────/─────/─────/─────/─────/─────/─────/
    * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐ ┌───┬───┬───┐
    * │ ` │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ Backsp│ │Ins│Hom│PgU│
    * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤ ├───┼───┼───┤
    * │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │  \  │ │Del│End│PgD│
    * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤ └───┴───┴───┘
    * │ Caps │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │  Enter │
    * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤     ┌───┐
    * │ Shift  │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │    Shift │     │ ↑ │
    * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤ ┌───┼───┼───┐
    * │Ctrl│GUI │Alt │                        │ Alt│ Fn │Menu│Ctrl│ │ ← │ ↓ │ → │
    * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘ └───┴───┴───┘
*/
```

When holding Fn down:

```C
/*
    *  /     /       /MyCmp/HomeP/Calc /Media/ ⏮  / ⏭  / ⏯   / ⏹   /Mute /     /
    *
    * │   │💡│   │   │   │   │   │   │   │   │   │   │   │       │ │   │   │V+ │
    * │     │   │🔆│   │   │   │   │   │   │   │   │   │   │BootL│ │   │   │V- │
    * │      │   │🔅│   │   │   │   │   │   │   │   │   │        │
    * │        │   │🎨│   │   │   │   │   │   │   │   │          │     │🗘 │
    * │    │    │    │                        │    │    │    │    │ │㉈ │🗘 │㉏ │
*/
```