# Tp32

![tp32](https://i.imgur.com/B0D0AmQ.jpg)

![tp32](https://i.imgur.com/Hl8T3rO.jpg)

![tp32](https://i.imgur.com/SL5hpnu.jpg)

![tp32](https://i.imgur.com/hjV2hN1.jpg)

this is trackpoint 32 keys keyboard

* Keyboard Maintainer: [skyjun](https://github.com/skyjun/tp32)
* Hardware Supported: pcb, 3d files, thinkpad trackpoint
* Hardware Availability: [gerber](https://github.com/skyjun/tp32/tree/main/gerber), [stl](https://github.com/skyjun/tp32/tree/main/stl), [at OSHWHUB](https://oshwhub.com/pkerr/keyborard-juk-32-rev-a)

Make example for this keyboard (after setting up your build environment):

    make 7liang/tp32:default


See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the top of the PCB, or the reset pads at the edge of the short
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
