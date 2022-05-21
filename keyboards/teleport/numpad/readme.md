# The Teleport NumPad

* Keyboard Maintainer: [ebastler](https://github.com/ebastler)
* Hardware Supported: Teleport NumPad
* Hardware Availability: [TheTeleport.de](https://www.theteleport.de/)

Make example for this keyboard (after setting up your build environment):

    make teleport/numpad:default

Flash example for this keyboard:

    make teleport/numpad:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader Enter the bootloader in 3 ways: 
* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (In this case NumLock) and plug in the keyboard 
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `RESET` (With the default keymap, hold NumLock, then press Enter)