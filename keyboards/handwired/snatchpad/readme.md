# snatchpad

![snatchpad etch-a-sketch macropad](https://i.imgur.com/aRIM8Nah.jpg)

A 6-key macropad with 2 rotary encoders intended for use as a pointing device.

In addition to the 3d printed parts and microcontroller, the following hardware is required:
* 4 * 3x3 mm threaded inserts
* 4 * 4mm M3 bolt
* USB daughter board

---

* Keyboard Maintainer: [xia0](https://github.com/xia0)
* Hardware Supported: e.g. Arduino Pro Micro
* Hardware Availability: [github](https://github.com/xia0/keeb_files/tree/main/snatchpad)

Make example for this keyboard (after setting up your build environment):

    make handwired/snatchpad:default

Flashing example for this keyboard:

    make handwired/snatchpad:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
