# Razer BlackWidow 2019

![Razer BlackWidow
2019](https://assets.razerzone.com/eeimages/support/products/1501/1501-blackwidow2019.png)

Full-size ANSI mechanical keyboard. Powered by an STM32L151RCT6 with dual
IS31FL3733 per-key RGB.

- Keyboard Maintainer: [htv04](https://github.com/htv04)
- Hardware Supported: Razer BlackWidow 2019
- Hardware Availability: [Razer](https://www.razer.com/)

Make example for this keyboard (after setting up your build environment):

```sh
make razer/blackwidow_2019:default
```

Flashing example for this keyboard:

```sh
make razer/blackwidow_2019:default:flash
```

Note that this keyboard does not support QMK's flashing procedures with its
stock firmware. The [razer-qmk](https://github.com/htv04/razer-qmk) project has
instructions and setup to allow QMK firmware installation.

See the [build environment setup](https://docs.qmk.fm/newbs_getting_started)
and the [make instructions](https://docs.qmk.fm/getting_started_make_guide) for
more information. Brand new to QMK? Start with our [Complete Newbs
Guide](https://docs.qmk.fm/newbs).

## Keymap

The default keymap follows the stock Fn legends, except:

- `Fn`+`F8`/`F9`: Respectively play and record a [dynamic
  macro](https://docs.qmk.fm/features/dynamic_macros) instead of Razer's
  assign-to-key macro system.
- `Fn`+`Menu`: Cycle to the next [RGB matrix
  effect](https://docs.qmk.fm/features/rgb_matrix#rgb-matrix-effects). With the
  stock firmware, this would be the on-keyboard profile switch. However, this
  keymap only has one layer (+ Fn), so this is the most appropriate remapping.

## Bootloader

Enter the bootloader by holding down the Escape key and plugging in the
keyboard.
