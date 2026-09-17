# ziyoulang_k3_mod

![ziyoulang_k3_mod](https://i.imgur.com/z9mUvIoh.jpg)


This base keyboard has  SX83099 IC causes some problems. I needed QMK as an alternative, especially since the controller freezes when the backlight is off.

* Keyboard Maintainer: [Coom](https://github.com/coomstoolbox)
* Hardware Supported: Ziyoulang K3,Blue Pill
* Hardware Availability: [Base Keyboard](https://www.aliexpress.com/item/1005005458088199.html), [Blue Pill Board](https://www.aliexpress.com/item/32812837487.html)

Make example for this keyboard (after setting up your build environment):

    make handwired/ziyoulang_k3_mod:default

Flashing example for this keyboard:

    make handwired/ziyoulang_k3_mod:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Requires hand wired

[KiCAD wiring diagram](https://github.com/coomstoolbox/ZK3-BP-MOD-wiring-diagram)

![explanation](https://i.imgur.com/thGIdOth.png)

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
