# Ergo-V-1

Fork of [Ergo-S-1](https://github.com/wizarddata/Ergo-S-1) from WizardKeyboards

Ergo-S-1 on its part is heavily inspired from Kinesis Advantage

![Ergo-V-1](https://i.imgur.com/eE1l5IV.jpeg)

This keyboard is practically identical to the orignal one with some differences
* Modified thumb cluster with one extra key
* Improved switch cutouts, compatible with kailh style switches
* unlike Ergo-S-1 this is a wired keyboard based on qmk

Make example for this keyboard (after setting up your build environment):

`make handwired/ergo_v_1:default`

Flashing example for this keyboard:

`make handwired/ergo_v_1:default:flash`

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
