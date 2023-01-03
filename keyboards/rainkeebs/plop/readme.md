# plop

![plop](https://imgur.com/5zZRGun)

*Plop, designed by Rainkeebs is a 12u stagger layout PCB made to drop into ortho "Planck 19mm grid spacing" cases.*

* Keyboard Maintainer: Rain
* Hardware Supported: Plop PCB
* Hardware Availability: [P3DStore](https://p3dstore.com/products/plop-pcb-only)

Make example for this keyboard (after setting up your build environment):

    make plop:default

Flashing example for this keyboard:

    make plop:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
