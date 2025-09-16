# DecenTKL NumPad

*A numeric pad to go with the DecenTKL keyboard*

This numeric pad also includes a 3-port USB hub, enabling the connection of the TKL
keyboard on the back of the pad.

The pad also has two Atari joystick ports.

* Keyboard Maintainer: [Bertrand Le roy](https://github.com/bleroy/3d-junkyard/blob/main/DecenTKL/)
* Hardware Supported: DecenTKL (RP2040-based)
* Hardware Availability: Custom built but open-source

Make example for this keyboard (after setting up your build environment):

    make decent/numpad:default

Flashing example for this keyboard:

    make decent/numpad:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Press the Num key or the button on the back of the board while connecting the pad.

## Special commands

Num + Enter: go into bootloader mode without unplugging the keyboard

## Layout
```C
/*
 *    /─────/─────/
 *   /F11  /F12  /
 *  /─────/─────/
 * ┌───┬───┬───┬───┐
 * │Num│ / │ * │ - │
 * ├───┼───┼───┼───┤
 * │ 7 │ 8 │ 9 │ + │
 * ├───┼───┼───┤   │
 * │ 4 │ 5 │ 6 │   │
 * ├───┼───┼───┼───┤
 * │ 1 │ 2 │ 3 │Ent│
 * ├───┴───┼───┤ er│
 * │ 0     │ . │   │
 * └───────┴───┴───┘
 */
```

While holding the Num key:

```C
/*
 *            /─────────/─────────/
 *           /Shift+F11/Shift+F12/
 *          /─────────/─────────/
 * ┌───────┬───────┬───────┬───────┐
 * │       │       │       │Bright-│
 * ├───────┼───────┼───────┼───────┤
 * │       │ Hue + │       │Bright+│
 * ├───────┼───────┼───────┤       │
 * │Speed -│ Swirl │Speed +│       │
 * ├───────┼───────┼───────┼───────┤
 * │Mode - │ Hue - │Mode + │       │
 * ├───────┴───────┼───────┤BootSel│
 * │ on / off      │       │       │
 * └───────────────┴───────┴───────┘
 */
```
