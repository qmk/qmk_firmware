# LumPy27

The Lightweight User-Modifiable Pi/Python keyboard is a 26-key ergonomic gaming keyboard running on an RP2040. Originally designed to run CircuitPython and KMK, since QMK supports the RP2040 bootloader this is now an additional option for firmware.

Q: Why is it named the LumPy27 even though it has 26 keys?

A: When originally designing the PCB and coming up with a name, I miscounted the switches. With the name emblazoned on the silkscreen I figured it sounded better than LumPy26.

Q: Why are the keys in the wrong place?

A: For certain games I found it easier instead of remapping them to just change where they are. That's why keys like B and G are not in the right spots. 

* Keyboard Maintainer: [djreisch](https://github.com/djreisch)
* Hardware Availability: [DuckyDebug.org](https://duckydebug.org/products/lumpy27-ergonomic-gaming-keyboard)

qmk compile example for this keyboard (after setting up your build environment):

    qmk compile -kb djreisch/lumpy27 -km default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootloader Reset**: Hold down the bootload button and press the reset button
* **Bootloader Power On**: Hold down the bootloader button and plug in the keyboard


