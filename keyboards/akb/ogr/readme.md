# akb/ogr

![akb/ogr](https://i.imgur.com/qbolyMah.jpeg)

OGR - Multi-functional keyboard with 75-78 keys for USB systems.

Keyboard designed by [AKB](https://alchemistkeyboards.com/), PCB designed by [martin](https://github.com/arnstadm)

* Keyboard Maintainer: [AKB](https://alchemistkeyboards.com/)
* Hardware Supported: OGR PCB
* Hardware Availability: https://alchemistkeyboards.com/projects/keyboards/ogr/

Make example for this keyboard (after setting up your build environment):

    make akb/ogr:default

Flashing example for this keyboard:

    make akb/ogr:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
