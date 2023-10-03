# Wave

![Wave pcb](https://i.imgur.com/oWF1Fnr.png)

_The Wave is a small, reversible keyboard inspired by the [Ferris](https://github.com/pierrechevalier83/ferris), the [Ferris Sweep](https://github.com/davidphilipbarr/Sweep), the [Swoop](https://github.com/jimmerricks/swoop) and the [Sweep36](https://github.com/sadekbaroudi/sweep36). It aims to solve a few issues I found with the keyboards._

-   Keyboard Maintainer: [Etienne Collin](https://github.com/etiennecollin)
-   Hardware Supported: [Wave](https://github.com/etiennecollin/wave)
-   Hardware Availability: Print the PCB with gerber files from [latest release in the repository](https://github.com/etiennecollin/wave/releases/latest)

Make example for this keyboard (after setting up your build environment):

    make etiennecollin/wave:default

Flashing example for this keyboard:

    make etiennecollin/wave:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Recommended Keymap

For an everyday keyboard, it is recommended to use the `feature` keymap, as the default keymap is extremely barebone. Here is a make example:

    make etiennecollin/wave:feature

Flashing example:

    make etiennecollin/wave:feature:flash

## Bootloader

Enter the bootloader in 3 ways:

-   **Bootmagic reset**: Hold down the top left key of the left half of the keyboard and plug in the keyboard
-   **Physical reset button**: Briefly press the reset button on the front of the PCB or short the GND and RST pins on the controller
-   **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
