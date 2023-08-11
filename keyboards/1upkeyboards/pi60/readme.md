# pi60_rgb

The pi60 is a solderable 60% pcb supporting millions of configuration options including standard options like ansi, iso, and tsangan as well as various split-shift and split-space configurations with three possible encoder positions. The board has RGB underglow with 21 leds and is compatible with many o-ring mount cases. The pcb is available with USB and an external i2c connector, or daughterboard connector.

* Keyboard Maintainer: [ziptyze](https://github.com/ziptyze)

Make example for this keyboard (after setting up your build environment):

    make 1upkeyboards/pi60:default

Flashing example for this keyboard:

    make 1upkeyboards/pi60:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Bootloader button**: Hold the button on the back of the PCB and plug in the keyboard
