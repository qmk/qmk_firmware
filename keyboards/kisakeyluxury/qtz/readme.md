# qtz

35% keyboard designed by Iceage

![pcb image](https://i.imgur.com/D2OmIkUh.png)

* Keyboard Maintainer: [kisakey-luxury](https://github.com/kisakey-luxury)
* Hardware Supported: *not released yet*
* Hardware Availability: *not released yet*

Make example for this keyboard (after setting up your build environment):

    make kisakeyluxury/qtz:default

Flashing example for this keyboard:

    make kisakeyluxury/qtz:default:flash
    
## Bootloader

Enter the bootloader in 2 ways:

* **Physical reset button**: Briefly press the button on the back of the PCB under the "Z" key
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available (default is bottom-right most key)