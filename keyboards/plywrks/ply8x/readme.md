# Plywrks ply8x

![ply8x](https://i.imgur.com/SYY9eKih.png)

F12 coreless keyboard PCB.

* Keyboard Maintainer: [Ramon Imbao](https://github.com/ramonimbao)
* Hardware Supported: STM32F072

Make example for this keyboard (after setting up your build environment):

    make plywrks/ply8x:default

Flashing example for this keyboard:

    make plywrks/ply8x:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Set the slide switch to `BOOTLOADER`, then briefly press the button on the back of the PCB.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
