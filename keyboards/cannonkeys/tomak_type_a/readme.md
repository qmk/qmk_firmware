# CannonKeys x Syryan Tomak Type-A

*A tented split TKL keyboard*

* Keyboard Maintainer: [awkannan](https://github.com/awkannan)
* Hardware Supported: RP2040
* Hardware Availability: *https://cannonkeys.com* 

Make example for this keyboard (after setting up your build environment):

```sh
    make cannonkeys/tomak_type_a:default
```

Flashing example for this keyboard:

```sh
    make cannonkeys/tomak_type_a:default:flash
```
See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the upper left key on the left hand keyboard half or the upper left key on the right hand keyboard half while plugging in USB
* **Physical reset button**: Press the REBOOT button twice, rapidly. Or hold the BOOTMODE button while pressing the REBOOT button.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available