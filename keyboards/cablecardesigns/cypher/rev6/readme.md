# cypher rev6

PCB for the cypher keyboard, this is rev6 of this PCB

* Keyboard Maintainer: [westfoxtrot](https://github.com/westfoxtrot)
* Hardware Supported: Cypher PCB revisions 6 (Rev # is printed on PCB)
* Hardware Availability: with keyboard release + [Files released here](https://github.com/westfoxtrot/Cypher_PCB)

Make example for this keyboard (after setting up your build environment):

    make cablecardesigns/cypher/rev6:default

Flashing example for this keyboard:

    make cablecardesigns/cypher/rev6:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: There are 2 holes underneath the spacebar position that if shorted will enter bootloader
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
