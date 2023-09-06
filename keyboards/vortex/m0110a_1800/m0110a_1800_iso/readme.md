# M0110A_1800_ISO
![m0110a_1800_iso](https://imgur.com/bWpBa8t.png)


An 80 keys keyboard, Equipped with the WestBerry Q95 microcontroller.

* Keyboard Maintainer: [GSKY](https://github.com/gksygithub)
* Hardware Supported: M0110A_1800
* Hardware Availability: [GSKY](https://github.com/gskygithub/M0110A_1800)

Make example for this keyboard (after setting up your build environment):

    make vortex/m0110a_1800/m0110a_1800_iso:default

Flashing example for this keyboard:

    make vortex/m0110a_1800/m0110a_1800_iso:default:flash

## Bootloader
Enter the bootloader in 3 ways:
* **Bootmagic reset**: Hold down the key at (1,6) in the matrix, top left key/Escape, and plug in the keyboard
* **Physical reset button**: Hold the Reset switch mounted on the surface of the PCB's rear side after the USB cable is connected
* **Fn+Tab**: Press the key will reset the board to bootloader mode

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
