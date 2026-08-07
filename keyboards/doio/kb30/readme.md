# Megalodon DOIO 30% Designer Keyboard

![Megalodon DOIO 30% Designer Keyboard](https://raw.githubusercontent.com/noroadsleft/qmk_images/master/keyboards/doio/kb30/KB30-01-_0000_778b3a43-228a-433d-94ae-9129f20b2ede_1024xc.jpg)

A hotswappable 30-key macropad with 3 rotary encoders (2 are clickable), an OLED screen, and RGB lighting.

* Keyboard Maintainer: [DOIO2022](https://github.com/DOIO2022)
* Hardware Supported: Megalodon DOIO 30% Designer Keyboard with STM32F103
* Hardware Availability: [KeebMonkey](https://www.keebmonkey.com/products/megalodon-doio-30-designer-keyboard)

Make example for this keyboard (after setting up your build environment):

    make doio/kb30:default

## Accessing Bootloader Mode and Flashing

To access Bootloader Mode, do one of the following:

* **Bootmagic reset**: Hold the top left key of the keyboard while connecting the USB cable.
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available.

Flashing example for this keyboard:

    make doio/kb30:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
