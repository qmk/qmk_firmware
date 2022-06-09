# Supernova

![Supernova](https://i.imgur.com/4RptTfV.png)

The Supernova is a TKL by Charue Design that draws inspiration from our favorite consoles and video games growing up like *GameCube*, *Super Smash Brothers*, and *Paper Mario*.

Features:
* Isolation Strip Gasket Mount
* WKL or Half WKL
* RGB Front Badge
* Substantial Back Weight
* 6 degree typing angle
* Optional Encoder with Fill-In


* Keyboard Maintainer: [ILWrites](https://github.com/PiKeeb)
* Hardware Supported: [Supernova PCB](https://charue-design.com/collections/supernova/)
* Hardware Availability: [Charue Design](https://charue-design.com/)

Make example for this keyboard (after setting up your build environment):

    make charue/supernova:default

Flashing example for this keyboard:

    make charue/supernova:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
