# macroboard

![macroboard](https://i.imgur.com/AY5Y1Ez.png)

3D printable half preonic (5x6 OLKB) with purpose of being macroboard or if you want to have different switches for gaming while having normal full keyboard for typing.

* Keyboard Maintainer: [Michał Szczepaniak](https://github.com/Michal-Szczepaniak)
* Hardware Supported: Blackpill
* Hardware Availability: [OpenSCAD files](https://github.com/Michal-Szczepaniak/macroboard-openscad)

Make example for this keyboard (after setting up your build environment):

    make handwired/macroboard:default

Flashing example for this keyboard:

    make handwired/macroboard:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available, by default 5th column, 5th row
