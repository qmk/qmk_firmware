# mecxlabs mp1

* Keyboard Maintainer: [Patrykf03](https://github.com/Patrykf03)
* Hardware Supported: Mecx Labs mp1 macropad (STM32/APM32F072)
* Hardware Availability: [mecxlabs.com](https://mecxlabs.com/products/mp1-framework)

Make example for this keyboard (after setting up your build environment):

    make mecxlabs/mp1:default

Flashing example for this keyboard:

    make mecxlabs/mp1:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (encoder in top left) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `RESET` if it is available	
