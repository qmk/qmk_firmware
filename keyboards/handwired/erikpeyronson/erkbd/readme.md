# handwired/erikpeyronson/erkbd

![Erkbd](https://i.imgur.com/VViiXIN.jpeg)

3D printed, handwired 44 key split keyboard featuring two encoders, two 1.3" 128x64 oled displays using the waveshare rp2040zero development board.

* Keyboard Maintainer: [Erik Peyronson](https://github.com/erikpeyronson)
* Hardware Supported: See keyboard repository on [github](https://github.com/erikpeyronson/erkbd)
* Hardware Availability: See keyboard repository on [github](https://github.com/erikpeyronson/erkbd)

Make example for this keyboard (after setting up your build environment):

    make handwired/erikpeyronson/erkbd:default

Flashing example for this keyboard:
    
    Enter bootloader, drag and drop .uft2 file on the removable storage

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader
Enter the bootloader in 3 ways:

* **Bootmagic reset**: For left half hold down the key at (0,0)  in the matrix (correspons with the tab key) and plug in the keyboard.
For left half half the key is (4,5) (corresponds with the backspace key)
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
Enter the bootloader in 3 ways:
