# arc

![arc](https://i.imgur.com/HQdls1nh.png)

ARC PCB, An ergonomic 65% keyboard PCB.
* Keyboard Maintainer: [shostudios](https://shostudios.co/)
* Hardware Supported: ARC, APM32F103
* Hardware Availability: [shostudios](https://shostudios.co/)

Make example for this keyboard (after setting up your build environment):

    make shostudio/arc:default

Flashing example for this keyboard:

    make shostudio/arc:default:flash

## Bootloader

Enter the bootloader in 4 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
* **Bootloader**: Hold down the key at (0,13) in the matrix (Backspace) and plug in the keyboard 

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
