# T Rex

![t_rex](https://github.com/SylivanKenobi/t-rex/blob/main/assets/pcb.png)

* Keyboard Maintainer: [Sylivan Kenobi](https://github.com/SylivanKenobi)
* Hardware Supported: 
    * [PCB](https://github.com/SylivanKenobi/t-rex)
    * Pro Micro Controller or derivates(e.g. elite-pi,puci-c)
    * WS2812 Led stripes
* Hardware Availability: Order yourself with the [gerber files](https://github.com/SylivanKenobi/t-rex/tree/main/kiCad/gerbers)

Make example for this keyboard (after setting up your build environment):

    make t_rex:default

Flashing example for this keyboard:

    make t_rex:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the lower + raise and q or the key mapped to `QK_BOOT`
