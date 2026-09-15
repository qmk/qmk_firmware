# splithie

![splithie](https://raw.githubusercontent.com/makkomise/splithie/refs/heads/main/src/Splithie_pcb.png)

*Ortho-split keyboard with 56 keys and RGB-per key lighting*

* Keyboard Maintainer: [makkomise](https://github.com/makkomise)
* Hardware Availability: [github/makkomise/splithie](https://github.com/makkomise/splithie)

Make example for this keyboard (after setting up your build environment):

    make makkomise/splithie:default

Flashing example for this keyboard:

    make makkomise/splithie:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press FN + Esc
