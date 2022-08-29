# CHORD ZERO Stenographic Keyboard

![CHORD ZERO](https://i.imgur.com/aS2MPQ2h.jpg)

CHORD ZERO is a stenographic keyboard that can be used with
[Plover](https://www.openstenoproject.org/plover/) or any other application
that supports the [TX
Bolt](https://docs.qmk.fm/#/feature_stenography?id=tx-bolt) or
[GeminiPR](https://docs.qmk.fm/#/feature_stenography?id=geminipr) protocol.

* Keyboard Maintainer: [Simon Hengel](https://github.com/sol)
* Hardware Supported: REV 0, REV 1
* Hardware Availability: https://github.com/sol/chord-zero#readme

Make example for this keyboard (after setting up your build environment):

    make chord/zero:default

or

    qmk compile -kb chord/zero -km default

This will generate `chord_zero_default.uf2`.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Reset key combo**: Press the six keys at the outer columns on each side of the keyboard simultaneously while it is plugged in 
* **Bootmagic reset**: Hold down the top left key and plug in the keyboard
* **Physical reset button**: Press the button on the back of the PCB and plug in the keyboard

Once the keyboard is in bootloader mode you can mount it as a USB mass storage
device and copy the firmware (the file `chord_zero_default.uf2`) onto it.  Once
copying is completed the keyboard will reboot automatically.
