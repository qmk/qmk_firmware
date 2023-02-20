# AkemiPad

![adpenrose/akemipad](https://i.imgur.com/2q4kJOAl.png)

A numpad powered by a ProMicro (currently ATmega based), with multiple layout options and support for an encoder, a piezo buzzer, an OLED, and per-key RGB lighting.

* Keyboard Maintainer: [Arturo Avila](https://github.com/ADPenrose)
* Hardware Supported: AkemiPad v1 PCB
* Hardware Availability: [Arturo Avila](https://github.com/ADPenrose) 

Make example for this keyboard (after setting up your build environment):

    make adpenrose/akemipad:default

Flashing example for this keyboard:

    make adpenrose/akemipad:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Quickly press two times the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
