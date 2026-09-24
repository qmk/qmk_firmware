# Planck

A compact 40% (12x4) ortholinear keyboard kit designed by OLKB and sold by Drop. A complete hardware rework of the rev6 Planck PCB, with support for up to 8 rotary encoders. [More info on qmk.fm](http://qmk.fm/planck/)

* Keyboard Maintainer: [Jack Humbert](https://github.com/jackhumbert)
* Hardware Supported: Planck PCB rev7
* Hardware Availability: [Drop](https://drop.com/buy/planck-mechanical-keyboard?mode=guest_open)

Make example for this keyboard (after setting up your build environment):

    make planck/rev7:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Encoders

Encoders must have matching pulse & detent resolutions (e.g. 24/24) for the scanning to work properly. Multiple encoders can be used at the same time.
If an encoder has a switch built-in, it's connected to the key at that location with index number:

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

Planck rev7 supports `ENCODER_ENABLE` and `ENCODER_MAP_ENABLE`. If both `ENCODER_MAP_ENABLE` and `ENCODER_ENABLE` are defined, `ENCODER_MAP_ENABLE` takes precedence. On the default keymap, each encoder will play its own rising/falling tone sequence when rotated, and will reset the pitch after one second of inactivity.

### With ENCODER_ENABLE

Define it as follows in `rules.mk`:

```
ENCODER_ENABLE = yes
```

Zero-indexed (compared to being one-indexed on the PCB's silkscreen) in the `encoder_update_user(uint8_t index, bool clockwise)` function.

### With ENCODER_MAP_ENABLE

Define it as follows in `rules.mk`:

```
ENCODER_ENABLE = yes
ENCODER_MAP_ENABLE = yes
```

If you enable `ENCODER_MAP_ENABLE`, define `const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS]` and configure your keycodes. If you enable `ENCODER_MAP_ENABLE`, `encoder_update_user` is not used directly. 

Additionally, you can use the following `config.h` options:

```c
#define ENCODER_MAP_KEY_DELAY 10
#define ENCODER_RESOLUTION 4
```

## Some Planck-specific config.h options:

```c
// sets the length (in seconds) of the watchdog timer, which will reset the keyboard due to hang/crash in the code
#define PLANCK_WATCHDOG_TIMEOUT 1.0
// disables the watchdog timer - you may want to disable the watchdog timer if you use longer macros
#define PLANCK_WATCHDOG_DISABLE
// Sets the time to wait for the rotary encoder pin state to stabilize while scanning (Default is 20(us))
#define PLANCK_ENCODER_SETTLE_PIN_STATE_DELAY 20
```
