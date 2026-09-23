# sculpt

MS Sculpt Keyboard ISO-layout wired to AT90USB1286

* Keyboard Maintainer: [Chad Austin](https://github.com/chadaustin/qmk_firmware) Ported by Winston Burbank
* Hardware Supported: MS Sculpt Keyboard ISO-layout, AT90USB1286  (https://github.com/chadaustin/wired-sculpt-pcb)
* Hardware Availability: Ebay and PCBWay

Make example for this keyboard (after setting up your build environment):

    qmk compile -kb handwired/ms_sculpt_us -km default

Flashing example for this keyboard:

    qmk flash -kb handwired/ms_sculpt_us -km default

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the development board
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
