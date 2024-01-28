# ibm_6746

![ibm_6746](https://i.imgur.com/mrXTFi9.png)
![circuit board:](https://i.imgur.com/QPzkDhs.png)

This is a project to convert the IBM 6746 Typewriter into a USB-C compatible keyboard. The project uses an Elite-Pi RP2040 microcontroller, in pro micro form factor.
Primary purpose of the RP2040 over a pro micro is twofold: One, to increase the number of IO pins to suit this archaic board layout, and two, the relative lack of 
available USB-C microcontrollers at the time of creation (start of 2023).

Note that this 6746 board is very rudimentary and has massive ghosting issues. It types really nice though, and has a unique layout. There may be one or two keys that do not function due to the nature of the board's circuitry.

* Keyboard Maintainer: [Justin](https://github.com/Justin-sandwich)
* Hardware Supported: *The PCBs, controllers supported*
* Hardware Availability: *Links to where you can find this hardware*

Make example for this keyboard (after setting up your build environment):

    make ibm_6746:default

Flashing example for this keyboard:

    make ibm_6746:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
