# 3dortho14u

![3dortho14u](https://i.imgur.com/us16LYTh.jpg)

A symmetrical 14u wide ortholinear keyboard.

In addition to the 3d printed parts and microcontroller, the following hardware is required:
* 8 * 12 mm M3 bolt
* Either:
  * 8 * M3 muts and CA glue
    OR
  * 8 * 3x3 mm threaded insert
* Optional:
  * USB daughter board

---

* Keyboard Maintainer: [xia0](https://github.com/xia0)
* Hardware Supported:
  * Teensy 2.0 (ATmega32u4)
* Hardware Availability: [github](https://github.com/xia0/keeb_files/tree/main/3dortho14u)

Make example for this keyboard (after setting up your build environment):

    make 3dortho14u/rev1:default

Flashing example for this keyboard:

    make 3dortho14u/rev1:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
