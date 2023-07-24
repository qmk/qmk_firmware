# Planck

A compact 40% (12x4) ortholinear keyboard kit designed by OLKB and sold by Drop. A complete hardware rework of the rev6 Planck PCB, with support for up to 8 rotary encoders. [More info on qmk.fm](http://qmk.fm/planck/)

* Keyboard Maintainer: [Jack Humbert](https://github.com/jackhumbert)
* Hardware Supported: Planck PCB rev7
* Hardware Availability: [Drop](https://drop.com/buy/planck-mechanical-keyboard?mode=guest_open)

Make example for this keyboard (after setting up your build environment):

    make planck/rev7:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Encoders

Encoders must have matching pulse & detent resolutions (e.g. 24/24) for the scanning to work properly. Multiple encoders can be used at the same time, and are zero-indexed (compared to being one-indexed on the PCB's silkscreen) in the `encoder_update_user(uint8_t index, bool clockwise)` function:

```
,-----------------------------------------------------------------------------------.
|   0  |      |      |      |      |      |      |      |      |      |      |   4  |
|------+------+------+------+------+------+------+------+------+------+------+------|
|   1  |      |      |      |      |      |      |      |      |      |      |   5  |
|------+------+------+------+------+------+------+------+------+------+------+------|
|   2  |      |      |      |      |      |      |      |      |      |      |   6  |
|------+------+------+------+------+------+------+------+------+------+------+------|
|   3  |      |      |      |      |             |      |      |      |      |   7  |
`-----------------------------------------------------------------------------------'
```

If an encoder has a switch built-in, it's connected to the key at that location. On the default keymap, each encoder will play its own rising/falling tone sequence when rotated, and will reset the pitch after one second of inactivity. The encoder map feature is not currently supported.

## Some Planck-specific config.h options:

```c
// sets the length (in seconds) of the watchdog timer, which will reset the keyboard due to hang/crash in the code
#define PLANCK_WATCHDOG_TIMEOUT 1.0
// disables the watchdog timer - you may want to disable the watchdog timer if you use longer macros
#define PLANCK_WATCHDOG_DISABLE
// the resolution of the encoders used in the encoder matrix
#define PLANCK_ENCODER_RESOLUTION 4
```
