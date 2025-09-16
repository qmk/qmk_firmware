# equals

![equals](https://i.imgur.com/c3adFqsh.jpeg)

* Keyboard Maintainer: [Cole Smith](https://github.com/boardsource)
* Hardware Supported: Equals PCB w/ RP2040 or Equals Kit w/ Pro Micro
* Hardware Availability: [boardsource](https://boardsource.xyz)

Make example for this keyboard (after setting up your build environment):

    make boardsource/equals/48:default
    make boardsource/equals/60:default
    make boardsource/equals/avr:default
    
Flashing example for this keyboard:

    make boardsource/equals/48:default:flash
    make boardsource/equals/60:default:flash
    make boardsource/equals/avr:default:flash
    
Compile `avr` firmware if your PCB uses a drop-in microcontroller like Pro Micro.


See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).


## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
