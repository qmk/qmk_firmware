# GPAD8-2R

![GPAD8-2R](https://i.imgur.com/jAaO7gYh.png)

8 Keys Custom Macro Pad, 2 Encoders, with USB Type-C, RGB underglow, RGB Per Key Lighting. 

* Keyboard Maintainer: [gkeyboard](https://github.com/gkeyboard)
* Hardware Supported: GPAD8-2R PCB
* Hardware Availability: http://www.mltelectronic.com

Make example for this keyboard (after setting up your build environment):

    make gkeyboard/gpad8_2r:default

Flashing example for this keyboard:

    make gkeyboard/gpad8_2r:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
