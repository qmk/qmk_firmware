# Synth Labs Solo

![Synth Labs Solo](https://i.imgur.com/uVUtfksh.png)

The Solo Macropad by Synth Labs.

* Keyboard Maintainer: [Nostril](https://github.com/hongaaronc)
* Hardware Supported: Synth Labs Solo
* Hardware Availability: [https://solo.synthlabs.io/](https://solo.synthlabs.io/)

Make example for this keyboard (after setting up your build environment):

    make synthlabs/solo:default
    
Flashing example for this keyboard:

    make synthlabs/solo:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (1,1) in the matrix (the rotary encoder button) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
* 
