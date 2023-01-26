# Nearfield

![Nearfield](https://i.imgur.com/hNj44FYh.jpg)

The LZ ErGO is a classic ergonomic design, predating the alice layout, and drawing inspiration from the "Microsoft natural ergonomic" series.
Nearfield expands on this by increasing the rotation of the two halves of the alpha cluster, each half is rotated 15 degrees towards the center of the board.
This increased angle forces the user to widen their elbow stance, and align their hands straighter with their forearms while typing.

Aesthetic design: Aside from the obvious layout homage to the ergo, retaining the nav cluster,
the case design draws inspiration from the M0110 keyboard series from Apple.

bog standard mx and alps support pcb, uses unified c3 daughterboard. 100mm JST cable recommended.

 
* Keyboard Maintainer: [TJ Campie](https://github.com/tominabox1)
* Hardware Supported: Nearfield
* Hardware Availability: [Cannonkeys](https://cannonkeys.com/collections/nearfield/products/nearfield-extra-pcb-and-daughterboard)

Make example for this keyboard (after setting up your build environment):

    make nearfield:default

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top left key and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
