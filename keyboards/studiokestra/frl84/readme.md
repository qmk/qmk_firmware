# studiokestra/frl84

![studiokestra/frl84](https://i.imgur.com/XzO7Ly0h.png)

FRL84 is a hotswap, via-compatible 65+Numpad layout. 

* Keyboard Maintainer: [studiokestra](https://github.com/studiokestra)
* Hardware Supported: FRL84 Invisibolt Case
* Hardware Availability: [FRL84 Invisibolt Case and PCB Group Buy](https://p3dstore.com/products/frl84-invisibolt-case-and-pcb-group-buy)

Make example for this keyboard (after setting up your build environment):

    make studiokestra/frl84:default

Flashing example for this keyboard:

    make studiokestra/frl84:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
