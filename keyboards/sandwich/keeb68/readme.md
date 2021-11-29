# keeb68

![keeb68](https://imgur.com/b3ftFIKh.jpg)

A small-batch run of 68 key goodness

* Keyboard Maintainer: [sandwich](https://github.com/SandwichRising)
* Hardware Supported: Sandwich's Keeb68 Patron Saint Edition
* Hardware Availability: Limited Run

Make example for this keyboard (after setting up your build environment):

    make sandwich/keeb68:default

Flashing example for this keyboard:

    make sandwich/keeb68:default:flash
    
Toggle NRKO on/off by holding space+n and then inserting the keyboard's USB cable. 
Some BIOSs may not detect keypresses properly while NRKO is enabled according to QMK documentation.
    
## Bootloader

Enter the bootloader in 2 ways (all keys assume default layout):

* **Keycode in layout**:  Hold Fn key and press the Windows(GUI) key (mapped to `RESET`)
* **Physical reset button**: Briefly press the button on the back of the PCB (labeled sw1)

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
