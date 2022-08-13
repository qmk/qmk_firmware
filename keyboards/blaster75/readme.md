# Blaster 75

Blaster 75 is a 75% ANSI layout Custom Keyboard designed and manufactured by Altain. 

* Keyboard Maintainer : ALTAiN
* Hardware Supported : Blaster 75
* Hardware Availability : Produced and Sold by ALTAiN
* Mount : Top-Mount System
* Typing Angle : 6 Degree
* Front Height : 20.2mm

## How to enter Bootloader Mode

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard.
We strongly recommend this method. If the PCB is not soldered with switches at the moment, use anything that's metal (twizzers for example)
to short the (0,0) position key ("ESC" in our PCB) while plugging the USB in. 

* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `RESET` if it is available

Make example for this keyboard (after setting up your build environment):

    make blaster75:default

Flashing example for this keyboard:

    make blaster75:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
