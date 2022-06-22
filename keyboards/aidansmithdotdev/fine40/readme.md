# Fine!40 PCB (For Mochi40)

![aidansmithdotdev/fine40](https://i.imgur.com/2JMorvxh.png)

The PCB for the Mochi40, a spiritual successor to the unreleased Whimsy recreated from scratch and made completely open source! With an OLED, Rotary Encoder, and headers for both the Elite-C and Nice!Nano, this board gives you all you could want in a 40%.

* Keyboard Maintainer: [Aidan Smith](https://github.com/Aidan-OS)
* Hardware Supported: Fine!40
* Hardware Availability: https://github.com/Aidan-OS/Mochi40

Make example for this keyboard (after setting up your build environment):

    make aidansmithdotdev/fine40:default

Flashing example for this keyboard:

    make aidansmithdotdev/fine40:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (top left key) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
